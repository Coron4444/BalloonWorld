//================================================================================
//!	@file	 RenderTargetShadowMap.cpp
//!	@brief	 レンダーターゲットシャドウマップClass
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../RenderTargetShadowMap.h"
#include "../../Shader/ShaderManager/ShaderManager.h"
#include "../../../DrawBase.h"
#include "../../../Camera/Camera.h"
#include "../../../../GameObject/GameObjectBase.h"



//****************************************
// プロパティ定義
//****************************************
void RenderTargetShadowMap::setCamera(Camera* value)
{
	camera_ = value;
}



void RenderTargetShadowMap::setDrawCommonData(DrawCommonData* value)
{
	common_data_ = value;
}



void RenderTargetShadowMap::setShaderManager(ShaderManager* value)
{
	shader_manager_ = value;
}



//****************************************
// 関数定義
//****************************************
void RenderTargetShadowMap::Init()
{
	Reset();
}



void RenderTargetShadowMap::Uninit()
{
	Reset();
}



void RenderTargetShadowMap::UninitWhenChangeScene()
{
	Reset();
}



void RenderTargetShadowMap::Update()
{
	// ビルボード更新
	AllBillboardUpdate();
}



void RenderTargetShadowMap::Draw()
{
	// レンダーターゲットの切り替え
	common_data_->getpRenderTextureShadowMap()->setRenderTarget(0);
	common_data_->getpRenderTextureShadowMap()->setStencilSurfaceAndViewPort();
	bool is_begin = Renderer::getpInstance()->DrawBegin(XColor4(0.0f, 0.0f, 0.0f, 1.0f));

	// カメラ設定
	ChangeCameraType(Camera::Type::PERSPECTIVE);

	for (unsigned i = 0; i < draw_.getEndIndex(); i++)
	{
		// シェーダーセット
		if (draw_.getObject(i)->getpDrawOrderList()->getIsAnimation())
		{
			shader_manager_->ShaderSetToDevice(draw_.getObject(i),
											   ShaderManager::VertexShaderType::SHADOW_MAP,
											   ShaderManager::PixelShaderType::SHADOW_MAP);
		}
		else
		{
			shader_manager_->ShaderSetToDevice(draw_.getObject(i),
											   ShaderManager::VertexShaderType::SHADOW_MAP,
											   ShaderManager::PixelShaderType::SHADOW_MAP);
			//shader_manager_->ShaderSetToDevice(draw_.getObject(i),
			//								   ShaderManager::VertexShaderType::NONE,
			//								   ShaderManager::PixelShaderType::NONE);
		}
		
		// 各オブジェクト描画
		for (unsigned j = 0; j < draw_.getObject(i)->getObjectNum(); j++)
		{
			// オブジェクト前設定
			draw_.getObject(i)->ObjectSettingBefore(j);
			shader_manager_->ObjectSetting(draw_.getObject(i), camera_, j);

			// 各メッシュ描画
			for (unsigned k = 0; k < draw_.getObject(i)->getMeshNum(j); k++)
			{
				// メッシュ設定
				shader_manager_->MeshSetting(draw_.getObject(i), camera_, j, k);

				draw_.getObject(i)->Draw(j, k);
			}

			// オブジェクト後設定
			draw_.getObject(i)->ObjectSettingAfter(j);
		}
	}

	Renderer::getpInstance()->DrawEnd(is_begin);
}



void RenderTargetShadowMap::AddDrawBaseToArray(DrawBase* draw)
{
	switch (draw->getpDrawOrderList()->getDrawType())
	{
		case DrawOrderList::DrawType::OPACITY:
		case DrawOrderList::DrawType::TRANSPARENCY:
		{
			draw_.AddToArray(draw);
			break;
		}
	}
}



void RenderTargetShadowMap::Reset()
{
	draw_.Reset();
}



void RenderTargetShadowMap::ChangeBillboardMatrix(DrawBase* draw)
{
	// ビュー行列の転置行列をセット
	draw->getpGameObject()->getpTransform()->setTransposeMatrix(camera_->getpViewMatrix(),
																true);
	// ワールド行列の更新
	draw->getpGameObject()->getpTransform()->CreateWorldMatrixPlusTranspose();
}



void RenderTargetShadowMap::AllBillboardUpdate()
{
	camera_->setType(Camera::Type::PERSPECTIVE);

	for (unsigned i = 0; i < draw_.getEndIndex(); i++)
	{
		if (!draw_.getObject(i)->getpDrawOrderList()->getIsBillboard()) continue;
		ChangeBillboardMatrix(draw_.getObject(i));
	}
}



void RenderTargetShadowMap::ChangeCameraType(Camera::Type camera_type)
{
	save_camera_type_ = camera_type;
	camera_->setType(camera_type);
}