//================================================================================
//!	@file	 PushSpaceLogoDraw.cpp
//!	@brief	 プッシュスペースロゴ描画Class
//! @details 
//!	@author  Kai Araki									@date 2018/09/02
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../PushSpaceLogoDraw.h"
#include "../PushSpaceLogo.h"

#include <Resource/Polygon/PlanePolygon.h>
#include <Tool/SafeRelease.h>



//****************************************
// 定数定義
//****************************************
const std::string PushSpaceLogoDraw::TEXTURE_NAME = "UI/PushSpace_Rogo.png";
const float PushSpaceLogoDraw::SCALE = 0.5f;



//****************************************
// プロパティ定義
//****************************************
unsigned PushSpaceLogoDraw::getMeshNum(unsigned object_index)
{
	object_index = object_index;

	return plane_polygon_->getMeshNum();
}



MATRIX* PushSpaceLogoDraw::getpMatrix(unsigned object_index)
{
	object_index = object_index;

	return getpGameObject()->getpTransform()->getpWorldMatrix();
}



D3DMATERIAL9* PushSpaceLogoDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return plane_polygon_->getpMaterial();
}



LPDIRECT3DTEXTURE9 PushSpaceLogoDraw::getpDiffuseTexture(unsigned object_index,
													 unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return diffuse_texture_->getpHandler();
}



//****************************************
// 関数定義
//****************************************
void PushSpaceLogoDraw::Init()
{
	// オーダーリスト設定
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::TWO_DIMENSIONAL);
	getpDrawOrderList()->getpRenderTargetFlag()->setFlag(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::FIXED);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::FIXED);

	// ダウンキャスト
	push_space_logo_ = (PushSpaceLogo*)getpGameObject();

	// テクスチャの登録
	diffuse_texture_ = TextureManager::getpInstance()->getpObject(&TEXTURE_NAME);

	// 平面ポリゴン作成
	plane_polygon_ = new PlanePolygon();
	plane_polygon_->Init();

	// 拡縮&移動
	getpGameObject()->getpTransform()->getpScale()->x = diffuse_texture_->getWidth() * SCALE;
	getpGameObject()->getpTransform()->getpScale()->y = diffuse_texture_->getHeight() * SCALE;
	getpGameObject()->getpTransform()->getpPosition()->y += -300.0f;
	getpGameObject()->getpTransform()->CreateWorldMatrix();
}



void PushSpaceLogoDraw::Uninit()
{
	SafeRelease::PlusRelease(&diffuse_texture_);
	SafeRelease::PlusUninit(&plane_polygon_);
}



void PushSpaceLogoDraw::Update()
{
	if (!*push_space_logo_->getpIsColorChange()) return;
	*push_space_logo_->getpIsColorChange() = true;
	plane_polygon_->setColor(*push_space_logo_->getpColor());
}



void PushSpaceLogoDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	plane_polygon_->Draw();
}