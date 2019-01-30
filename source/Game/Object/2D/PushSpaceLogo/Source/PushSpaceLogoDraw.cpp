//================================================================================
//!	@file	 PushSpaceLogoDraw.cpp
//!	@brief	 �v�b�V���X�y�[�X���S�`��Class
//! @details 
//!	@author  Kai Araki									@date 2018/09/02
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../PushSpaceLogoDraw.h"
#include "../PushSpaceLogo.h"

#include <Resource/Polygon/PlanePolygon.h>
#include <Tool/SafeRelease.h>



//****************************************
// �萔��`
//****************************************
const std::string PushSpaceLogoDraw::TEXTURE_NAME = "UI/PushSpace_Rogo.png";
const float PushSpaceLogoDraw::SCALE = 0.5f;



//****************************************
// �v���p�e�B��`
//****************************************
unsigned PushSpaceLogoDraw::getMeshNum(unsigned object_index)
{
	object_index = object_index;

	return plane_polygon_->getMeshNum();
}



MATRIX* PushSpaceLogoDraw::getpMatrix(unsigned object_index)
{
	object_index = object_index;

	return getpGameObject()->getpTransform()->getpWorldMatrix();
}



D3DMATERIAL9* PushSpaceLogoDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return plane_polygon_->getpMaterial();
}



LPDIRECT3DTEXTURE9 PushSpaceLogoDraw::getpDiffuseTexture(unsigned object_index,
													 unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return diffuse_texture_->getpHandler();
}



//****************************************
// �֐���`
//****************************************
void PushSpaceLogoDraw::Init()
{
	// �I�[�_�[���X�g�ݒ�
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::TWO_DIMENSIONAL);
	getpDrawOrderList()->getpRenderTargetFlag()->setFlag(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::FIXED);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::FIXED);

	// �_�E���L���X�g
	push_space_logo_ = (PushSpaceLogo*)getpGameObject();

	// �e�N�X�`���̓o�^
	diffuse_texture_ = TextureManager::getpInstance()->getpObject(&TEXTURE_NAME);

	// ���ʃ|���S���쐬
	plane_polygon_ = new PlanePolygon();
	plane_polygon_->Init();

	// �g�k&�ړ�
	getpGameObject()->getpTransform()->getpScale()->x = diffuse_texture_->getWidth() * SCALE;
	getpGameObject()->getpTransform()->getpScale()->y = diffuse_texture_->getHeight() * SCALE;
	getpGameObject()->getpTransform()->getpPosition()->y += -300.0f;
	getpGameObject()->getpTransform()->CreateWorldMatrix();
}



void PushSpaceLogoDraw::Uninit()
{
	SafeRelease::PlusRelease(&diffuse_texture_);
	SafeRelease::PlusUninit(&plane_polygon_);
}



void PushSpaceLogoDraw::Update()
{
	if (!*push_space_logo_->getpIsColorChange()) return;
	*push_space_logo_->getpIsColorChange() = true;
	plane_polygon_->setColor(*push_space_logo_->getpColor());
}



void PushSpaceLogoDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	plane_polygon_->Draw();
}