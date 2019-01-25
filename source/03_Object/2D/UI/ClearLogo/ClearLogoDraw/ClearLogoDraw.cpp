//================================================================================
//
//    �N���A���S�`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/06/19
//
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "ClearLogoDraw.h"

#include <Polygon\PlanePolygon\PlanePolygon.h>
#include <SafeRelease/SafeRelease.h>



//****************************************
// �萔��`
//****************************************
const std::string ClearLogoDraw::TEXTURE_NAME = "UI/Clear.png";
const float ClearLogoDraw::SCALE = 1.25f;



//****************************************
// ��ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +�������֐�
//--------------------------------------------------
void ClearLogoDraw::Init()
{
	// �I�[�_�[���X�g�ݒ�
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::TWO_DIMENSIONAL);
	getpDrawOrderList()->getpRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::FIXED);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::FIXED);

	// �_�E���L���X�g
	clear_logo_ = (ClearLogo*)getpGameObject();

	// �e�N�X�`���̓o�^
	diffuse_texture_ = TextureManager::getpInstance()->getpObject(&TEXTURE_NAME);

	// �g�k&�ړ�
	clear_logo_->GetTransform()->GetScale()->x = diffuse_texture_->getWidth() * SCALE;
	clear_logo_->GetTransform()->GetScale()->y = diffuse_texture_->getHeight() * (SCALE + 0.2f);
	*clear_logo_->GetTransform()->GetPosition() = Vec3(0.0f, 0.0f, 0.0f);
	clear_logo_->GetTransform()->UpdateWorldMatrixSRT();
}



//--------------------------------------------------
// +�I���֐�
//--------------------------------------------------
void ClearLogoDraw::Uninit()
{
	SafeRelease::PlusRelease(&diffuse_texture_);
}



//--------------------------------------------------
// +�`��֐�
//--------------------------------------------------
void ClearLogoDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	clear_logo_->plane_polygon_->Draw();
}



//--------------------------------------------------
// +���b�V�����擾�֐�
//--------------------------------------------------
unsigned ClearLogoDraw::getMeshNum(unsigned object_index)
{
	object_index = object_index;

	return clear_logo_->plane_polygon_->getMeshNum();
}



//--------------------------------------------------
// +�s��擾�֐�
//--------------------------------------------------
MATRIX* ClearLogoDraw::getpMatrix(unsigned object_index)
{
	object_index = object_index;

	return getpGameObject()->GetTransform()->getpWorldMatrix();
}



//--------------------------------------------------
// +�}�e���A���擾�֐�
//--------------------------------------------------
D3DMATERIAL9* ClearLogoDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return clear_logo_->plane_polygon_->GetMaterial();
}



//--------------------------------------------------
// +�f�B�q���[�Y�e�N�X�`���擾�֐�
//--------------------------------------------------
LPDIRECT3DTEXTURE9 ClearLogoDraw::getpDiffuseTexture(unsigned object_index,
													unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return diffuse_texture_->getpHandler();
}