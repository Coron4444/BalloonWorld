//================================================================================
//!	@file	 EnemyDraw.cpp
//!	@brief	 敵描画Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../EnemyDraw.h"
#include "../Enemy.h"

#include <Resource/Polygon/CubePolygon.h>
#include <Tool/SafeRelease.h>



//****************************************
// プロパティ定義
//****************************************
unsigned EnemyDraw::getMeshNum(unsigned object_index)
{
	object_index = object_index;

	return cube_polygon_->getMeshNum();
}



MATRIX* EnemyDraw::getpMatrix(unsigned object_index)
{
	object_index = object_index;

	return getpGameObject()->getpTransform()->getpWorldMatrix();
}



D3DMATERIAL9* EnemyDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return cube_polygon_->getpMaterial();
}



//****************************************
// 関数定義
//****************************************
void EnemyDraw::Init()
{
	// オーダーリスト設定
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::TRANSPARENCY);
	getpDrawOrderList()->getpRenderTargetFlag()->setFlag(DrawOrderList::RENDER_TARGET_MAIN);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::FIXED);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::FIXED);
	//getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::DEFAULT_SHADOW);
	//getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::DEFAULT_SHADOW);

	// ダウンキャスト
	enemy_ = (Enemy*)getpGameObject();

	// 四角形ポリゴン作成
	cube_polygon_ = new CubePolygon();
	cube_polygon_->Init();
	cube_polygon_->setColor(XColor4(1.0f, 0.0f, 0.0f, 1.0f));
}



void EnemyDraw::Uninit()
{
	SafeRelease::PlusUninit(&cube_polygon_);
}



void EnemyDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	cube_polygon_->Draw();
}