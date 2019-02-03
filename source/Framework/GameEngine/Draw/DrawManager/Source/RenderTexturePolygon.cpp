//================================================================================
//!	@file	 RenderTexturePolygonPolygon.cpp
//!	@brief	 レンダーテクスチャポリゴンClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../RenderTexturePolygon.h"
#include "../../../Renderer/Renderer.h"

#include <Resource/Polygon/PlanePolygon.h>
#include <Tool/SafeRelease.h>
#include <Tool/Transform.h>



//****************************************
// プロパティ定義
//****************************************
MATRIX* RenderTexturePolygon::getpMatrix(unsigned object_index)
{
	object_index = object_index;
	return transform_->getpWorldMatrix();
}



D3DMATERIAL9* RenderTexturePolygon::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;
	return plane_polygon_->getpMaterial();
}



//****************************************
// 関数定義
//****************************************
void RenderTexturePolygon::Init()
{
	plane_polygon_ = new PlanePolygon();
	plane_polygon_->Init();
	transform_ = new Transform();
}



void RenderTexturePolygon::Uninit()
{
	SafeRelease::PlusUninit(&plane_polygon_);
	SafeRelease::Normal(&transform_);
}



void RenderTexturePolygon::Update(float position_x, float position_y, 
								  float scale_x, float scale_y, XColor4 color)
{
	transform_->getpPosition()->x = position_x;
	transform_->getpPosition()->y = position_y;
	transform_->getpScale()->x = scale_x;
	transform_->getpScale()->y = scale_y;
	transform_->CreateWorldMatrix();

	plane_polygon_->setColor(color);
}



void RenderTexturePolygon::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;
	plane_polygon_->Draw();
}