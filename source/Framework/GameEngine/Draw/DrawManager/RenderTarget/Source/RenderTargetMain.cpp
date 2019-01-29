//================================================================================
//!	@file	 RenderTargetMain.cpp
//!	@brief	 レンダーターゲットメインClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../RenderTargetMain.h"
#include "../../Shader/ShaderManager/ShaderManager.h"
#include "../../../DrawBase.h"
#include "../../../Camera/Camera.h"
#include "../../../../GameObject/GameObjectBase.h"

#include <Resource/Effekseer/EffekseerManager/EffekseerManager.h>
#include <Tool/SafeRelease.h>



//****************************************
// プロパティ定義
//****************************************
void RenderTargetMain::setCamera(Camera* value)
{
	camera_ = value;
}



void RenderTargetMain::setDrawCommonData(DrawCommonData* value)
{
	common_data_ = value;
}



void RenderTargetMain::setShaderManager(ShaderManager* value)
{
	shader_manager_ = value;
}



//****************************************
// 関数定義
//****************************************
void RenderTargetMain::Init()
{
	Reset();
}



void RenderTargetMain::Uninit()
{
	Reset();
}



void RenderTargetMain::UninitWhenChangeScene()
{
	Reset();
}



void RenderTargetMain::Update()
{
	// ソート
	SortTransparent();
	Sort2D();

	// ビルボード更新
	AllBillboardUpdate();

	// エフェクシアの更新
	EffekseerManager::getpInstance()->CreateViewMatrix(*camera_->getpPositon(),
													   *camera_->getpLookAtPoint(),
													   *camera_->getpUp());
	EffekseerManager::getpInstance()->CreateProjectionMatrix(camera_->getAngleOfView());
	EffekseerManager::getpInstance()->Update();
}



void RenderTargetMain::Draw()
{
	// レンダーターゲットの切り替え
	LPDIRECT3DDEVICE9 device;
	Renderer::getpInstance()->getDevice(&device);
	common_data_->getpRenderTextureMain()->setRenderTarget(0);
	bool is_begin = Renderer::getpInstance()->DrawBegin();

	// 描画
	DrawOpacity();
	DrawTransparent();
	EffekseerManager::getpInstance()->Draw();
	Draw2D();

	Renderer::getpInstance()->DrawEnd(is_begin);
}



void RenderTargetMain::AddDrawBaseToArray(DrawBase* draw)
{
	switch (draw->getpDrawOrderList()->getDrawType())
	{
		case DrawOrderList::DrawType::OPACITY:
		{
			draw_opacity_.AddToArray(draw);
			break;
		}
		case DrawOrderList::DrawType::TRANSPARENCY:
		{
			draw_transparent_.AddToArray(draw);
			break;
		}
		case DrawOrderList::DrawType::TWO_DIMENSIONAL:
		{
			draw_2D_.AddToArray(draw);
			break;
		}
	}
}



void RenderTargetMain::Reset()
{
	draw_opacity_.Reset();
	draw_transparent_.Reset();
	draw_2D_.Reset();
}



void RenderTargetMain::SortTransparent()
{
	// 透明オブジェクトがあるかどうか
	if (draw_transparent_.getEndIndex() <= 0) return;

	for (unsigned i = 0; i < draw_transparent_.getEndIndex() - 1; i++)
	{
		// 深度値を算出
		Vector3D temp_vector0 = *draw_transparent_.getObject(i)->getpGameObject()
			->getpTransform()->getpPosition() - *camera_->getpPositon();

		float depth_value0 = temp_vector0.getLengthSquare();

		for (unsigned j = i + 1; j < draw_transparent_.getEndIndex(); j++)
		{
			// 深度値を算出
			Vector3D temp_vector1 = *draw_transparent_.getObject(j)->getpGameObject()
				->getpTransform()->getpPosition() - *camera_->getpPositon();

			float depth_value1 = temp_vector1.getLengthSquare();

			// 深度値を比較
			if (depth_value0 < depth_value1)
			{
				// 並び替え
				draw_transparent_.SortTheTwoObject(i, j);
			}
		}
	}
}



void RenderTargetMain::Sort2D()
{
	// 2Dオブジェクトがあるかどうか
	if (draw_2D_.getEndIndex() <= 0) return;

	for (unsigned i = 0; i < draw_2D_.getEndIndex() - 1; i++)
	{
		for (unsigned j = i + 1; j < draw_2D_.getEndIndex(); j++)
		{
			if (draw_2D_.getObject(i)->getpDrawOrderList()->getLayerNum()
				> draw_2D_.getObject(j)->getpDrawOrderList()->getLayerNum())
			{
				// 並び替え
				draw_2D_.SortTheTwoObject(i, j);
			}
		}
	}
}



void RenderTargetMain::ChangeBillboardMatrix(DrawBase* draw)
{
	// ビュー行列の転置行列をセット
	draw->getpGameObject()->getpTransform()->setTransposeMatrix(camera_->getpViewMatrix(),
																true);
	// ワールド行列の更新
	draw->getpGameObject()->getpTransform()->CreateAxisAndWorldMatrixPlusTranspose();
}



void RenderTargetMain::AllBillboardUpdate()
{
	camera_->setType(Camera::Type::PERSPECTIVE);

	// 不透明オブジェクト
	for (unsigned i = 0; i < draw_opacity_.getEndIndex(); i++)
	{
		if (!draw_opacity_.getObject(i)->getpDrawOrderList()->getIsBillboard()) continue;
		ChangeBillboardMatrix(draw_opacity_.getObject(i));
	}

	// 透明オブジェクト
	for (unsigned i = 0; i < draw_transparent_.getEndIndex(); i++)
	{
		if (!draw_transparent_.getObject(i)->getpDrawOrderList()->getIsBillboard()) continue;
		ChangeBillboardMatrix(draw_transparent_.getObject(i));
	}
}



void RenderTargetMain::ChangeCameraType(Camera::Type camera_type)
{
	save_camera_type_ = camera_type;
	camera_->setType(camera_type);
}



void RenderTargetMain::TempChangeCameraType(DrawBase* draw)
{
	switch (draw->getpDrawOrderList()->getTempChangeDrawType())
	{
		case DrawOrderList::DrawType::OPACITY:
		case DrawOrderList::DrawType::TRANSPARENCY:
		{
			camera_->setType(Camera::Type::PERSPECTIVE);
			break;
		}
		case DrawOrderList::DrawType::TWO_DIMENSIONAL:
		{
			camera_->setType(Camera::Type::TWO_DIMENSIONAL);
			break;
		}
	}
}


void RenderTargetMain::RevertTempChangeCameraType(DrawBase* draw)
{
	if (draw->getpDrawOrderList()
		->getTempChangeDrawType() == DrawOrderList::DrawType::NONE) return;

	camera_->setType(save_camera_type_);
	draw->getpDrawOrderList()
		->setTempChangeDrawType(DrawOrderList::DrawType::NONE);
}



void RenderTargetMain::DrawOpacity()
{
	// カメラ設定
	ChangeCameraType(Camera::Type::PERSPECTIVE);
	
	for (unsigned i = 0; i < draw_opacity_.getEndIndex(); i++)
	{
		// シェーダーセット
		shader_manager_->ShaderSetToDevice(draw_opacity_.getObject(i),
										   ShaderManager::VertexShaderType::NONE,
										   ShaderManager::PixelShaderType::NONE);

		// 各オブジェクト描画
		for (unsigned j = 0; j < draw_opacity_.getObject(i)->getObjectNum(); j++)
		{
			// オブジェクト前設定
			draw_opacity_.getObject(i)->ObjectSettingBefore(j);
			TempChangeCameraType(draw_opacity_.getObject(i));
			shader_manager_->ObjectSetting(draw_opacity_.getObject(i), camera_, j);

			// 各メッシュ描画
			for (unsigned k = 0; k < draw_opacity_.getObject(i)->getMeshNum(j); k++)
			{
				// メッシュ設定
				shader_manager_->MeshSetting(draw_opacity_.getObject(i), camera_, j, k);

				draw_opacity_.getObject(i)->Draw(j, k);
			}

			// オブジェクト後設定
			RevertTempChangeCameraType(draw_opacity_.getObject(i));
			draw_opacity_.getObject(i)->ObjectSettingAfter(j);
		}
	}
}



void RenderTargetMain::DrawTransparent()
{
	for (unsigned i = 0; i < draw_transparent_.getEndIndex(); i++)
	{
		// シェーダーをセット
		shader_manager_->ShaderSetToDevice(draw_transparent_.getObject(i),
										   ShaderManager::VertexShaderType::NONE,
										   ShaderManager::PixelShaderType::NONE);

		// 各オブジェクト描画
		for (unsigned j = 0; j < draw_transparent_.getObject(i)->getObjectNum(); j++)
		{
			// オブジェクト前設定
			draw_transparent_.getObject(i)->ObjectSettingBefore(j);
			TempChangeCameraType(draw_transparent_.getObject(i));
			shader_manager_->ObjectSetting(draw_transparent_.getObject(i), camera_, j);

			// 各メッシュ描画
			for (unsigned k = 0; k < draw_transparent_.getObject(i)->getMeshNum(j); k++)
			{
				// メッシュ設定
				shader_manager_->MeshSetting(draw_transparent_.getObject(i),
											 camera_, j, k);

				draw_transparent_.getObject(i)->Draw(j, k);
			}

			// オブジェクト後設定
			RevertTempChangeCameraType(draw_transparent_.getObject(i));
			draw_transparent_.getObject(i)->ObjectSettingAfter(j);
		}
	}
}



void RenderTargetMain::Draw2D()
{
	// カメラ設定
	ChangeCameraType(Camera::Type::TWO_DIMENSIONAL);

	for (unsigned i = 0; i < draw_2D_.getEndIndex(); i++)
	{
		// シェーダーセット
		shader_manager_->ShaderSetToDevice(draw_2D_.getObject(i),
										   ShaderManager::VertexShaderType::NONE,
										   ShaderManager::PixelShaderType::NONE);

		// 各オブジェクト描画
		for (unsigned j = 0; j < draw_2D_.getObject(i)->getObjectNum(); j++)
		{
			// オブジェクト前設定
			draw_2D_.getObject(i)->ObjectSettingBefore(j);
			TempChangeCameraType(draw_2D_.getObject(i));
			shader_manager_->ObjectSetting(draw_2D_.getObject(i), camera_, j);

			// 各メッシュ描画
			for (unsigned k = 0; k < draw_2D_.getObject(i)->getMeshNum(j); k++)
			{
				// メッシュ設定
				shader_manager_->MeshSetting(draw_2D_.getObject(i),
											 camera_, j, k);

				draw_2D_.getObject(i)->Draw(j, k);
			}

			// オブジェクト後設定
			RevertTempChangeCameraType(draw_2D_.getObject(i));
			draw_2D_.getObject(i)->ObjectSettingAfter(j);
		}
	}
}