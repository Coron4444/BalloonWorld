//================================================================================
//!	@file	 ScaffoldDraw.cpp
//!	@brief	 ����`��Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../ScaffoldDraw.h"
#include "../Scaffold.h"

#include <Resource/Polygon/CubePolygon.h>
#include <Tool/SafeRelease.h>



//****************************************
// �萔��`
//****************************************



//****************************************
// �v���p�e�B��`
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
// �֐���`
//****************************************
void ScaffoldDraw::Init()
{
	// �I�[�_�[���X�g�ݒ�
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::OPACITY);
	getpDrawOrderList()->getpRenderTargetFlag()->setFlag(DrawOrderList::RENDER_TARGET_MAIN);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::COOK_TORRANCE);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::COOK_TORRANCE);

	// �_�E���L���X�g
	scaffolod_ = (Scaffold*)getpGameObject();
	
	// �L���[�u�|���S���̐���
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