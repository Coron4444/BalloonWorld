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
	return Balloon::MAX_BULLET_OBJECT;
}



unsigned BalloonDraw::getMeshNum(unsigned object_index)
{
	if (object_index != 0)
	{
		return balloon_line_object_->getMeshNum();
	}
	else
	{
		return balloon_object_->getMeshNum();
	}
}



MATRIX* BalloonDraw::getpMatrix(unsigned object_index)
{
	return balloon_->bullet_transform_[object_index].getpWorldMatrix();
}



D3DMATERIAL9* BalloonDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	if (object_index != 0)
	{
		return balloon_line_object_->getpMaterial(mesh_index);
	}
	else
	{
		return balloon_object_->getpMaterial(mesh_index);
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
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::OPACITY);
	getpDrawOrderList()->getpRenderTargetFlag()->setFlag(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::FIXED);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::FIXED);

	// オブジェクト取得
	balloon_object_ = ModelXManager::getpInstance()->getpObject(&BALLOON_MODEL_NAME);
	balloon_line_object_ = ModelXManager::getpInstance()->getpObject(&BALLOON_LINE_MODEL_NAME);

}



void BalloonDraw::Uninit()
{
	SafeRelease::PlusRelease(&balloon_line_object_);
	SafeRelease::PlusRelease(&balloon_object_);
}



void BalloonDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	if (object_index >= Balloon::MAX_BULLET_OBJECT - 2) return;

	if (object_index != 0)
	{
		balloon_line_object_->getpMesh()->DrawSubset(mesh_index);
	}
	else
	{
		balloon_object_->getpMesh()->DrawSubset(mesh_index);
	}
}