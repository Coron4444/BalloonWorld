//================================================================================
//!	@file	 NeedleDraw.cpp
//!	@brief	 棘描画Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../NeedleDraw.h"



//****************************************
// 定数定義
//****************************************
const std::string NeedleDraw::MODEL_NAME = "Needle/Needle.x";



//****************************************
// プロパティ定義
//****************************************
unsigned NeedleDraw::getMeshNum(unsigned object_index)
{
	object_index = object_index;

	return needle_model_->getMeshNum();
}



MATRIX* NeedleDraw::getpMatrix(unsigned object_index)
{
	object_index = object_index;

	return getpGameObject()->getpTransform()->getpWorldMatrix();
}



D3DMATERIAL9* NeedleDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;

	return needle_model_->getpMaterial(mesh_index);
}



//****************************************
// 関数定義
//****************************************
void NeedleDraw::Init()
{
	// オーダーリスト設定
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::OPACITY);
	getpDrawOrderList()->getpRenderTargetFlag()->setFlag(DrawOrderList::RENDER_TARGET_MAIN);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::BLINN_PHONG);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::BLINN_PHONG);

	// Xモデル登録
	needle_model_ = ModelXManager::getpInstance()->getpObject(&MODEL_NAME);
}



void NeedleDraw::Uninit()
{
	SafeRelease::PlusRelease(&needle_model_);
}



void NeedleDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	needle_model_->getpMesh()->DrawSubset(mesh_index);
}