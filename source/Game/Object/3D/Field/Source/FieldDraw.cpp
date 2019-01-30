//================================================================================
//!	@file	 FieldDraw.cpp
//!	@brief	 �n�ʕ`��Class
//! @details 
//!	@author  Kai Araki									@date 2018/05/15
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../FieldDraw.h"
#include "../Field.h"

#include <Tool/SafeRelease.h>



//****************************************
// �萔��`
//****************************************
const std::string FieldDraw::TEXTURE_NAME = "Field.png";



//****************************************
// �v���p�e�B��`
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
// �֐���`
//****************************************
void FieldDraw::Init()
{
	// �I�[�_�[���X�g�ݒ�
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::OPACITY);
	getpDrawOrderList()->getpRenderTargetFlag()->setFlag(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::FIXED);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::FIXED);

	// �_�E���L���X�g
	field_ = (Field*)getpGameObject();

	// �e�N�X�`���̓o�^
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