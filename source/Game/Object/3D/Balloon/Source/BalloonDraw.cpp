//================================================================================
//!	@file	 BalloonDraw.cpp
//!	@brief	 風船描画Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/05
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../BalloonDraw.h"
#include "../Balloon.h"

#include <Resource/ModelX/ModelXManager/ModelXManager.h>
#include <Tool/SafeRelease.h>
#include <Tool/Random.h>



//****************************************
// 定数定義
//****************************************
const std::string BalloonDraw::BALLOON_MODEL_NAME = "Balloon/Balloon.x";
const std::string BalloonDraw::BALLOON_LINE_MODEL_NAME = "Balloon/Line.x";



//****************************************
// プロパティ定義
//****************************************
unsigned BalloonDraw::getObjectNum()
{
	return balloon_->getAllObjectNum();
}



unsigned BalloonDraw::getMeshNum(unsigned object_index)
{
	if (object_index == (unsigned)balloon_->getAllObjectNum() - 1)
	{
		return balloon_object_->getMeshNum();
	}
	else
	{
		return balloon_line_object_->getMeshNum();
	}
}



MATRIX* BalloonDraw::getpMatrix(unsigned object_index)
{
	return balloon_->getpObjectTransform(object_index)->getpWorldMatrix();
}



D3DMATERIAL9* BalloonDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	if (object_index == (unsigned)balloon_->getAllObjectNum() - 1)
	{
		balloon_object_->setMaterialColor(mesh_index, color_);
		return balloon_object_->getpMaterial(mesh_index);
	}
	else
	{
		return balloon_line_object_->getpMaterial(mesh_index);
	}
}



//****************************************
// 関数定義
//****************************************
void BalloonDraw::Init()
{
	// ダウンキャスト
	balloon_ = (Balloon*)getpGameObject();

	// オーダーリスト設定
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::TRANSPARENCY);
	getpDrawOrderList()->getpRenderTargetFlag()->setFlag(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::FIXED);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::FIXED);

	// オブジェクト取得
	balloon_object_ = ModelXManager::getpInstance()->getpObject(&BALLOON_MODEL_NAME);
	balloon_line_object_ = ModelXManager::getpInstance()->getpObject(&BALLOON_LINE_MODEL_NAME);

	int random = Random::getpInstance()->getInt(0, 2);
	for (unsigned i = 0; i < balloon_object_->getMeshNum(); i++)
	{
		if (random == 0)
		{
			color_ = XColor4(0.3f, 1.0f, 1.0f, 1.0f);
		}
		else if (random == 1)
		{
			color_ = XColor4(1.0f, 1.0f, 0.5f, 1.0f);
		}
		else
		{
			color_ = XColor4(1.0f, 0.3f, 0.5f, 1.0f);
		}
	}
}



void BalloonDraw::Uninit()
{
	SafeRelease::PlusRelease(&balloon_line_object_);
	SafeRelease::PlusRelease(&balloon_object_);
}



void BalloonDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	if (object_index <= 1) return;

	if (object_index == (unsigned)balloon_->getAllObjectNum() - 1)
	{
		balloon_object_->getpMesh()->DrawSubset(mesh_index);
	}
	else
	{
		balloon_line_object_->getpMesh()->DrawSubset(mesh_index);
	}
}