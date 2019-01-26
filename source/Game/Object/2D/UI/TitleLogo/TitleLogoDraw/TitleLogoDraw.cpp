//================================================================================
//
//    �^�C�g�����S�`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/07/03
//
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "TitleLogoDraw.h"

#include <Polygon\PlanePolygon\PlanePolygon.h>
#include <SafeRelease/SafeRelease.h>



//****************************************
// �萔��`
//****************************************
const std::string TitleLogoDraw::TEXTURE_NAME = "UI/Title.png";
const float TitleLogoDraw::SCALE = 1.25f;



//****************************************
// ��ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +�������֐�
//--------------------------------------------------
void TitleLogoDraw::Init()
{
	// �I�[�_�[���X�g�ݒ�
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::TWO_DIMENSIONAL);
	getpDrawOrderList()->getpRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::FIXED);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::FIXED);

	// �_�E���L���X�g
	title_logo_ = (TitleLogo*)getpGameObject();

	// �e�N�X�`���̓o�^
	diffuse_texture_ = TextureManager::getpInstance()->getpObject(&TEXTURE_NAME);
	
	// �g�k
	title_logo_->GetTransform()->GetScale()->x = diffuse_texture_->getWidth() * SCALE;
	title_logo_->GetTransform()->GetScale()->y = diffuse_texture_->getHeight() * (SCALE + 0.2f);
	title_logo_->GetTransform()->UpdateWorldMatrixSRT();
}



//--------------------------------------------------
// +�I���֐�
//--------------------------------------------------
void TitleLogoDraw::Uninit()
{
	SafeRelease::PlusRelease(&diffuse_texture_);
}



//--------------------------------------------------
// +�`��֐�
//--------------------------------------------------
void TitleLogoDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	title_logo_->plane_polygon_->Draw();
}



//--------------------------------------------------
// +���b�V�����擾�֐�
//--------------------------------------------------
unsigned TitleLogoDraw::getMeshNum(unsigned object_index)
{
	object_index = object_index;

	return title_logo_->plane_polygon_->getMeshNum();
}



//--------------------------------------------------
// +�s��擾�֐�
//--------------------------------------------------
MATRIX* TitleLogoDraw::getpMatrix(unsigned object_index)
{
	object_index = object_index;

	// ���b�V�����̎擾
	return getpGameObject()->GetTransform()->getpWorldMatrix();
}



//--------------------------------------------------
// +�}�e���A���擾�֐�
//--------------------------------------------------
D3DMATERIAL9* TitleLogoDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return title_logo_->plane_polygon_->GetMaterial();
}



//--------------------------------------------------
// +�f�B�q���[�Y�e�N�X�`���擾�֐�
//--------------------------------------------------
LPDIRECT3DTEXTURE9 TitleLogoDraw::getpDiffuseTexture(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return diffuse_texture_->getpHandler();
}