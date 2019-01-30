//================================================================================
//!	@file	 TutorialLogoDraw.cpp
//!	@brief	 �`���[�g���A�����S�`��Class
//! @details 
//!	@author  Kai Araki									@date 2018/09/02
//================================================================================


//****************************************
// �C���N���[�h��
//****************************************
#include "../TutorialLogoDraw.h"
#include "../TutorialLogo.h"

#include <Resource/Polygon/PlanePolygon.h>
#include <Tool/SafeRelease.h>



//****************************************
// �萔��`
//****************************************
const std::string TutorialLogoDraw::TEXTURE_NAME[TEXTURE_NUM] =
{
	"UI/Tutorial01.png",
	"UI/Tutorial02.png"
};

const float TutorialLogoDraw::SCALE = 1.25f;



//****************************************
// �v���p�e�B��`
//****************************************
unsigned TutorialLogoDraw::getMeshNum(unsigned object_index)
{
	object_index = object_index;

	return plane_polygon_->getMeshNum();
}



MATRIX* TutorialLogoDraw::getpMatrix(unsigned object_index)
{
	object_index = object_index;

	return getpGameObject()->getpTransform()->getpWorldMatrix();
}



D3DMATERIAL9* TutorialLogoDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return plane_polygon_->getpMaterial();
}



LPDIRECT3DTEXTURE9 TutorialLogoDraw::getpDiffuseTexture(unsigned object_index,
													 unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return diffuse_texture_[tutorial_logo_->getLogoNum()]->getpHandler();
}



//****************************************
// �֐���`
//****************************************
void TutorialLogoDraw::Init()
{
	// �I�[�_�[���X�g�ݒ�
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::TWO_DIMENSIONAL);
	getpDrawOrderList()->getpRenderTargetFlag()->setFlag(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::FIXED);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::FIXED);

	// �_�E���L���X�g
	tutorial_logo_ = (TutorialLogo*)getpGameObject();

	// ���ʃ|���S���쐬
	plane_polygon_ = new PlanePolygon();
	plane_polygon_->Init();

	// �e�N�X�`���̓o�^
	for (unsigned i = 0; i < TEXTURE_NUM; i++)
	{
		diffuse_texture_[i] = TextureManager::getpInstance()->getpObject(&TEXTURE_NAME[i]);
	}

	// �g�k
	getpGameObject()->getpTransform()->getpScale()->x = diffuse_texture_[0]->getWidth() * SCALE;
	getpGameObject()->getpTransform()->getpScale()->y = diffuse_texture_[0]->getHeight() * (SCALE + 0.2f);
	*getpGameObject()->getpTransform()->getpPosition() = Vec3(0.0f, 0.0f, 0.0f);
	getpGameObject()->getpTransform()->CreateWorldMatrix();
}



void TutorialLogoDraw::Uninit()
{
	SafeRelease::PlusUninit(&plane_polygon_);

	for (unsigned i = 0; i < TEXTURE_NUM; i++)
	{
		SafeRelease::PlusRelease(&diffuse_texture_[i]);
	}
}



void TutorialLogoDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	plane_polygon_->Draw();
}