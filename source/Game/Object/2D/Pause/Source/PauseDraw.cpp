//================================================================================
//!	@file	 ClearLogoDraw.cpp
//!	@brief	 �N���A���S�`��Class
//! @details 
//!	@author  Kai Araki									@date 2018/06/19
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../ClearLogoDraw.h"

#include <Resource/Polygon/PlanePolygon.h>
#include <Tool/SafeRelease.h>



//****************************************
// �萔��`
//****************************************
const std::string ClearLogoDraw::TEXTURE_NAME = "UI/Clear.png";
const float ClearLogoDraw::SCALE = 1.25f;



//****************************************
// �v���p�e�B��`
//****************************************
unsigned ClearLogoDraw::getMeshNum(unsigned object_index)
{
	object_index = object_index;

	return plane_polygon_->getMeshNum();
}



MATRIX* ClearLogoDraw::getpMatrix(unsigned object_index)
{
	object_index = object_index;

	return getpGameObject()->getpTransform()->getpWorldMatrix();
}



D3DMATERIAL9* ClearLogoDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return plane_polygon_->getpMaterial();
}



LPDIRECT3DTEXTURE9 ClearLogoDraw::getpDiffuseTexture(unsigned object_index,
													 unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return diffuse_texture_->getpHandler();
}



//****************************************
// �֐���`
//****************************************
void ClearLogoDraw::Init()
{
	// �I�[�_�[���X�g�ݒ�
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::TWO_DIMENSIONAL);
	getpDrawOrderList()->getpRenderTargetFlag()->setFlag(DrawOrderList::RENDER_TARGET_MAIN);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::FIXED);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::FIXED);

	// �e�N�X�`���̓o�^
	diffuse_texture_ = TextureManager::getpInstance()->getpObject(&TEXTURE_NAME);

	// ���ʃ|���S���쐬
	plane_polygon_ = new PlanePolygon();
	plane_polygon_->Init();

	// �g�k&�ړ�
	getpGameObject()->getpTransform()->getpScale()->x = diffuse_texture_->getWidth() * SCALE;
	getpGameObject()->getpTransform()->getpScale()->y = diffuse_texture_->getHeight() * (SCALE + 0.2f);
	*getpGameObject()->getpTransform()->getpPosition() = Vec3(0.0f, 0.0f, 0.0f);
	getpGameObject()->getpTransform()->CreateWorldMatrix();
}



void ClearLogoDraw::Uninit()
{
	SafeRelease::PlusUninit(&plane_polygon_);
	SafeRelease::PlusRelease(&diffuse_texture_);
}



void ClearLogoDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	plane_polygon_->Draw();
}