//================================================================================
//!	@file	 Field.cpp
//!	@brief	 地面Class
//! @details 
//!	@author  Kai Araki									@date 2018/05/15
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../Field.h"

#include <Tool/SafeRelease.h>



//****************************************
// プロパティ定義
//****************************************
MeshPlanePolygon* Field::getpMeshPlanePolygon()
{
	return mesh_plane_polygon_;
}



//****************************************
// 関数定義
//****************************************
void Field::Init(DrawBase* draw)
{
	// メッシュプレーンポリゴンの作成
	mesh_plane_polygon_ = new MeshPlanePolygon();
	mesh_plane_polygon_->Init(Vec2(100.0f, 100.0f),
							  Vec2(1.0f, 1.0f),
							  XColor4(1.0f, 1.0f, 1.0f, 1.0f));
	// 基底クラスの初期化
	setIsUpdate(false);
	GameObjectBase::Init(draw, nullptr);
}



void Field::Uninit()
{
	SafeRelease::PlusUninit(&mesh_plane_polygon_);

	UninitComponent();
}