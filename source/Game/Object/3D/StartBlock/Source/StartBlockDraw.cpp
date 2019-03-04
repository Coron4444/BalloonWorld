//================================================================================
//!	@file	 StartBlockDraw.cpp
//!	@brief	 �X�^�[�g�u���b�N�`��Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/13
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../StartBlockDraw.h"



//****************************************
// �v���p�e�B��`
//****************************************
unsigned StartBlockDraw::getMeshNum(unsigned object_index)
{
	object_index = object_index;

	return cube_polygon_->getMeshNum();
}



MATRIX* StartBlockDraw::getpMatrix(unsigned object_index)
{
	object_index = object_index;

	return getpGameObject()->getpTransform()->getpWorldMatrix();
}



D3DMATERIAL9* StartBlockDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return cube_polygon_->getpMaterial();
}



//****************************************
// �֐���`
//****************************************
void StartBlockDraw::Init()
{
	// �I�[�_�[���X�g�ݒ�
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::OPACITY);
	getpDrawOrderList()->getpRenderTargetFlag()->setFlag(DrawOrderList::RENDER_TARGET_MAIN);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::COOK_TORRANCE);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::COOK_TORRANCE);
	//getpDrawOrderList()->getpRenderTargetFlag()->setFlag(DrawOrderList::RENDER_TARGET_MAIN | DrawOrderList::RENDER_TARGET_SHADOW_MAP);
	//getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::DEFAULT_SHADOW);
	//getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::DEFAULT_SHADOW);

	// �L���[�u�|���S���̐���
	cube_polygon_ = new CubePolygon();
	cube_polygon_->Init();
	cube_polygon_->setColor(XColor4(1.0f, 1.0f, 0.0f, 1.0f));
}



void StartBlockDraw::Uninit()
{
	SafeRelease::PlusUninit(&cube_polygon_);
}



void StartBlockDraw::Update()
{
}



void StartBlockDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	cube_polygon_->Draw();
}