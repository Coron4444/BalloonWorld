//================================================================================
//!	@file	 EnemyDraw.cpp
//!	@brief	 �G�`��Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../EnemyDraw.h"
#include "../Enemy.h"

#include <Resource/Polygon/CubePolygon.h>
#include <Tool/SafeRelease.h>



//****************************************
// �v���p�e�B��`
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
// �֐���`
//****************************************
void EnemyDraw::Init()
{
	// �I�[�_�[���X�g�ݒ�
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::TRANSPARENCY);
	getpDrawOrderList()->getpRenderTargetFlag()->setFlag(DrawOrderList::RENDER_TARGET_MAIN);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::FIXED);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::FIXED);
	//getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::DEFAULT_SHADOW);
	//getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::DEFAULT_SHADOW);

	// �_�E���L���X�g
	enemy_ = (Enemy*)getpGameObject();

	// �l�p�`�|���S���쐬
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