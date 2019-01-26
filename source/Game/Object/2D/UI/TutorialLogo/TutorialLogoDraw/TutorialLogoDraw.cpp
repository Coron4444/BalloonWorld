//================================================================================
//
//    �`���[�g���A�����S01�`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/09/02
//
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "TutorialLogoDraw.h"

#include <main.h>
#include <SafeRelease/SafeRelease.h>



//****************************************
// �萔��`
//****************************************
const std::string TutorialLogoDraw::TEXTURE_NAME[TEXTURE_NUM] = {"UI/Tutorial01.png",
																 "UI/Tutorial02.png"};



//****************************************
// ��ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +�������֐�
//--------------------------------------------------
void TutorialLogoDraw::Init()
{
	// �I�[�_�[���X�g�ݒ�
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::TWO_DIMENSIONAL);
	getpDrawOrderList()->getpRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::FIXED);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::FIXED);
	getpDrawOrderList()->setLayerNum(0);

	// �_�E���L���X�g
	tutorial_logo_ = (TutorialLogo*)getpGameObject();

	// ���ʃ|���S���쐬
	plane_polygon_ = new PlanePolygon();

	// �e�N�X�`���̓o�^
	for (unsigned i = 0; i < TEXTURE_NUM; i++)
	{
		diffuse_texture_[i] = TextureManager::getpInstance()->getpObject(&TEXTURE_NAME[i]);
	}

	// �g�k
	tutorial_logo_->GetTransform()->GetScale()->x = SCREEN_WIDTH;
	tutorial_logo_->GetTransform()->GetScale()->y = SCREEN_HEIGHT;
	tutorial_logo_->GetTransform()->UpdateWorldMatrixSRT();

	// �e�N�X�`���C���f�b�N�X
	texture_index_ = 0;
}



//--------------------------------------------------
// +�I���֐�
//--------------------------------------------------
void TutorialLogoDraw::Uninit()
{
	SafeRelease::Normal(&plane_polygon_);

	for (unsigned i = 0; i < TEXTURE_NUM; i++)
	{
		SafeRelease::PlusRelease(&diffuse_texture_[i]);
	}	
}



//--------------------------------------------------
// +�X�V�֐�
//--------------------------------------------------
void TutorialLogoDraw::Update()
{
	// �e�N�X�`���ԍ��ύX
	texture_index_ = tutorial_logo_->GetLogoNum();
}



//--------------------------------------------------
// +�`��֐�
//--------------------------------------------------
void TutorialLogoDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	plane_polygon_->Draw();
}



//--------------------------------------------------
// +���b�V�����擾�֐�
//--------------------------------------------------
unsigned TutorialLogoDraw::getMeshNum(unsigned object_index)
{
	object_index = object_index;

	return plane_polygon_->getMeshNum();
}



//--------------------------------------------------
// +�s��擾�֐�
//--------------------------------------------------
MATRIX* TutorialLogoDraw::getpMatrix(unsigned object_index)
{
	object_index = object_index;

	return tutorial_logo_->GetTransform()->getpWorldMatrix();
}



//--------------------------------------------------
// +�}�e���A���擾�֐�
//--------------------------------------------------
D3DMATERIAL9* TutorialLogoDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return plane_polygon_->GetMaterial();
}



//--------------------------------------------------
// +�f�B�q���[�Y�e�N�X�`���擾�֐�
//--------------------------------------------------
LPDIRECT3DTEXTURE9 TutorialLogoDraw::getpDiffuseTexture(unsigned object_index,
														unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return diffuse_texture_[texture_index_]->getpHandler();
}