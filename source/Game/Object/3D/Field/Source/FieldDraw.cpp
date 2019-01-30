//================================================================================
//!	@file	 FieldDraw.cpp
//!	@brief	 地面描画Class
//! @details 
//!	@author  Kai Araki									@date 2018/05/15
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../FieldDraw.h"
#include "../Field.h"

#include <Tool/SafeRelease.h>



//****************************************
// 定数定義
//****************************************
const std::string FieldDraw::TEXTURE_NAME = "Field.png";



//****************************************
// プロパティ定義
//****************************************
unsigned FieldDraw::getMeshNum(unsigned object_index)
{
	object_index = object_index;

	return field_->getpMeshPlanePolygon()->getMeshNum();
}



MATRIX* FieldDraw::getpMatrix(unsigned object_index)
{
	object_index = object_index;

	return getpGameObject()->getpTransform()->getpWorldMatrix();
}



D3DMATERIAL9* FieldDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return field_->getpMeshPlanePolygon()->getpMaterial();
}



LPDIRECT3DTEXTURE9 FieldDraw::getpDiffuseTexture(unsigned object_index,
												 unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return diffuse_texture_->getpHandler();
}



//****************************************
// 関数定義
//****************************************
void FieldDraw::Init()
{
	// オーダーリスト設定
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::OPACITY);
	getpDrawOrderList()->getpRenderTargetFlag()->setFlag(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::FIXED);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::FIXED);

	// ダウンキャスト
	field_ = (Field*)getpGameObject();

	// テクスチャの登録
	diffuse_texture_ = TextureManager::getpInstance()->getpObject(&TEXTURE_NAME);
}



void FieldDraw::Uninit()
{
	SafeRelease::PlusRelease(&diffuse_texture_);
}



void FieldDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	field_->getpMeshPlanePolygon()->Draw();
}