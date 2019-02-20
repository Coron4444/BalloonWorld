//================================================================================
//!	@file	 ScaffoldDraw.cpp
//!	@brief	 足場描画Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../ScaffoldDraw.h"
#include "../Scaffold.h"

#include <Resource/Polygon/CubePolygon.h>
#include <Tool/SafeRelease.h>



//****************************************
// 定数定義
//****************************************



//****************************************
// プロパティ定義
//****************************************
unsigned ScaffoldDraw::getMeshNum(unsigned object_index)
{
	object_index = object_index;

	return cube_polygon_->getMeshNum();
}



MATRIX* ScaffoldDraw::getpMatrix(unsigned object_index)
{
	object_index = object_index;

	return getpGameObject()->getpTransform()->getpWorldMatrix();
}



D3DMATERIAL9* ScaffoldDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return cube_polygon_->getpMaterial();
}



//****************************************
// 関数定義
//****************************************
void ScaffoldDraw::Init()
{
	// オーダーリスト設定
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::OPACITY);
	getpDrawOrderList()->getpRenderTargetFlag()->setFlag(DrawOrderList::RENDER_TARGET_MAIN);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::COOK_TORRANCE);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::COOK_TORRANCE);

	// ダウンキャスト
	scaffolod_ = (Scaffold*)getpGameObject();
	
	// キューブポリゴンの生成
	cube_polygon_ = new CubePolygon();
	cube_polygon_->Init();
	cube_polygon_->setColor(*scaffolod_->getpColor());
}



void ScaffoldDraw::Uninit()
{
	SafeRelease::PlusUninit(&cube_polygon_);
}



void ScaffoldDraw::Update()
{
	cube_polygon_->setColor(*scaffolod_->getpColor());
}



void ScaffoldDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	cube_polygon_->Draw();
}