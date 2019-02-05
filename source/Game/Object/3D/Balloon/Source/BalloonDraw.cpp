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

#include <GameEngine/Draw/DrawManager/Shader/VertexShader/VertexShaderBumpMapping.h>
#include <Resource/MdBin/MdBinManager/MdBinManager.h>
#include <Resource/ModelX/ModelXManager/ModelXManager.h>
#include <Resource/Texture/TextureManager/TextureManager.h>
#include <Tool/SafeRelease.h>



//****************************************
// 定数定義
//****************************************
const std::string BalloonDraw::MODEL_NAME = "sen/sen.x";



//****************************************
// プロパティ定義
//****************************************
unsigned BalloonDraw::getMeshNum(unsigned object_index)
{
	object_index = object_index;

	return object_->getMeshNum();
}



MATRIX* BalloonDraw::getpMatrix(unsigned object_index)
{
	object_index = object_index;

	return getpGameObject()->getpTransform()->getpWorldMatrix();
}



D3DMATERIAL9* BalloonDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;

	return object_->getpMaterial(mesh_index);
}



LPDIRECT3DTEXTURE9 BalloonDraw::getpDiffuseTexture(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return nullptr;// object_->getpDiffuseTextureObject(mesh_index)->getpHandler();
}



//****************************************
// 関数定義
//****************************************
void BalloonDraw::Init()
{
	// オーダーリスト設定
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::OPACITY);
	getpDrawOrderList()->getpRenderTargetFlag()->setFlag(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::FIXED);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::FIXED);

	// オブジェクト取得
	object_ = ModelXManager::getpInstance()->getpObject(&MODEL_NAME);
}



void BalloonDraw::Uninit()
{
	SafeRelease::PlusRelease(&object_);
}



void BalloonDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	object_->getpMesh()->DrawSubset(mesh_index);
}