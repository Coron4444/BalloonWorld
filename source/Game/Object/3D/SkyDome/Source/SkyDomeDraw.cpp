//================================================================================
//!	@file	 SkyDomeDraw.cpp
//!	@brief	 天球描画Class
//! @details 
//!	@author  Kai Araki									@date 2018/05/15
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../SkyDomeDraw.h"

#include <Resource/ModelX/ModelXManager/ModelXManager.h>
#include <Tool/SafeRelease.h>



//****************************************
// 定数定義
//****************************************
const std::string SkyDomeDraw::MODEL_NAME = "SkyDome/SkyDome.x";
const float SkyDomeDraw::SCALE = 130.0f;



//****************************************
// プロパティ定義
//****************************************
unsigned SkyDomeDraw::getMeshNum(unsigned object_index)
{
	object_index = object_index;

	return sky_dome_model_->getMeshNum();
}



MATRIX* SkyDomeDraw::getpMatrix(unsigned object_index)
{
	object_index = object_index;

	return getpGameObject()->getpTransform()->getpWorldMatrix();
}



D3DMATERIAL9* SkyDomeDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;

	return sky_dome_model_->getpMaterial(mesh_index);
}



LPDIRECT3DTEXTURE9 SkyDomeDraw::getpDiffuseTexture(unsigned object_index,
												   unsigned mesh_index)
{
	object_index = object_index;

	return sky_dome_model_->getpDiffuseTextureObject(mesh_index)->getpHandler();
}



//****************************************
// 関数定義
//****************************************
void SkyDomeDraw::Init()
{
	// オーダーリスト設定
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::OPACITY);
	getpDrawOrderList()->getpRenderTargetFlag()->setFlag(DrawOrderList::RENDER_TARGET_MAIN);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::FIXED);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::FIXED);
	getpDrawOrderList()->setIsLighting(false);

	// Xモデル登録
	sky_dome_model_ = ModelXManager::getpInstance()->getpObject(&MODEL_NAME);

	// 拡縮の変更
	*getpGameObject()->getpTransform()->getpScale() *= SCALE;
	getpGameObject()->getpTransform()->CreateWorldMatrix();
}



void SkyDomeDraw::Uninit()
{
	SafeRelease::PlusRelease(&sky_dome_model_);
}



void SkyDomeDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	sky_dome_model_->getpMesh()->DrawSubset(mesh_index);
}