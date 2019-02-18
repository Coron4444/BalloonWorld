//================================================================================
//!	@file	 Field.cpp
//!	@brief	 �n��Class
//! @details 
//!	@author  Kai Araki									@date 2018/05/15
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../Field.h"

#include <Tool/SafeRelease.h>



//****************************************
// �v���p�e�B��`
//****************************************
MeshPlanePolygon* Field::getpMeshPlanePolygon()
{
	return mesh_plane_polygon_;
}



//****************************************
// �֐���`
//****************************************
void Field::Init(DrawBase* draw)
{
	// ���b�V���v���[���|���S���̍쐬
	mesh_plane_polygon_ = new MeshPlanePolygon();
	mesh_plane_polygon_->Init(Vec2(100.0f, 100.0f),
							  Vec2(1.0f, 1.0f),
							  XColor4(1.0f, 1.0f, 1.0f, 1.0f));
	// ���N���X�̏�����
	setIsUpdate(false);
	GameObjectBase::Init(draw, nullptr);
}



void Field::Uninit()
{
	SafeRelease::PlusUninit(&mesh_plane_polygon_);

	UninitComponent();
}