//================================================================================
//
//    �X�J�C�h�[���`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/05/15
//
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "SkyDomeDraw.h"

#include <SafeRelease/SafeRelease.h>
#include <ModelX/ModelXManager/ModelXManager.h>



//****************************************
// �萔��`
//****************************************
const std::string SkyDomeDraw::MODEL_NAME = "SkyDome/SkyDome.x";



//****************************************
// ��ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +�������֐�
//--------------------------------------------------
void SkyDomeDraw::Init()
{
	// �I�[�_�[���X�g�ݒ�
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::OPACITY);
	getpDrawOrderList()->getpRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::FIXED);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::FIXED);
	getpDrawOrderList()->setIsLighting(false);

	// X���f���o�^
	sky_dome_model_ = ModelXManager::getpInstance()->getpObject(&MODEL_NAME);
}



//--------------------------------------------------
// +�I���֐�
//--------------------------------------------------
void SkyDomeDraw::Uninit()
{
	SafeRelease::PlusRelease(&sky_dome_model_);
}



//--------------------------------------------------
// +�`��֐�
//--------------------------------------------------
void SkyDomeDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	// ���݂̃��b�V���̕`��
	sky_dome_model_->getpMesh()->DrawSubset(mesh_index);
}



//--------------------------------------------------
// +���b�V�����擾�֐�
//--------------------------------------------------
unsigned SkyDomeDraw::getMeshNum(unsigned object_index)
{
	object_index = object_index;

	return sky_dome_model_->getMeshNum();
}



//--------------------------------------------------
// +�s��擾�֐�
//--------------------------------------------------
MATRIX* SkyDomeDraw::getpMatrix(unsigned object_index)
{
	object_index = object_index;

	return getpGameObject()->GetTransform()->getpWorldMatrix();
}



//--------------------------------------------------
// +�}�e���A���擾�֐�
//--------------------------------------------------
D3DMATERIAL9* SkyDomeDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;

	return sky_dome_model_->getpMaterial(mesh_index);
}



//--------------------------------------------------
// +�f�B�q���[�Y�e�N�X�`���擾�֐�
//--------------------------------------------------
LPDIRECT3DTEXTURE9 SkyDomeDraw::getpDiffuseTexture(unsigned object_index,
												  unsigned mesh_index)
{
	object_index = object_index;

	return sky_dome_model_->getpDiffuseTextureObject(mesh_index)->getpHandler();
}