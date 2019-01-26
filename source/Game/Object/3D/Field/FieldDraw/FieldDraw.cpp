//================================================================================
//
//    �n�ʕ`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/05/15
//
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "FieldDraw.h"

#include <Polygon\MeshPlanePolygon\MeshPlanePolygon.h>
#include <Texture/TextureManager/TextureManager.h>
#include <SafeRelease/SafeRelease.h>



//****************************************
// �萔��`
//****************************************
const std::string FieldDraw::TEXTURE_NAME = "Field.png";



//****************************************
// ��ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +�������֐�
//--------------------------------------------------
void FieldDraw::Init()
{
	// �I�[�_�[���X�g�ݒ�
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::OPACITY);
	getpDrawOrderList()->getpRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::FIXED);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::FIXED);

	// �e�N�X�`���̓o�^
	diffuse_texture_ = TextureManager::getpInstance()->getpObject(&TEXTURE_NAME);

	// �_�E���L���X�g
	field_ = (Field*)getpGameObject();
}



//--------------------------------------------------
// +�I���֐�
//--------------------------------------------------
void FieldDraw::Uninit()
{
	SafeRelease::PlusRelease(&diffuse_texture_);
}



//--------------------------------------------------
// +�`��֐�
//--------------------------------------------------
void FieldDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	field_->mesh_plane_polygon_->Draw();
}



//--------------------------------------------------
// +���b�V�����擾�֐�
//--------------------------------------------------
unsigned FieldDraw::getMeshNum(unsigned object_index)
{
	object_index = object_index;

	return field_->mesh_plane_polygon_->getMeshNum();
}



//--------------------------------------------------
// +�s��擾�֐�
//--------------------------------------------------
MATRIX* FieldDraw::getpMatrix(unsigned object_index)
{
	object_index = object_index;

	return field_->GetTransform()->getpWorldMatrix();
}



//--------------------------------------------------
// +�}�e���A���擾�֐�
//--------------------------------------------------
D3DMATERIAL9* FieldDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return field_->mesh_plane_polygon_->GetMaterial();
}



//--------------------------------------------------
// +�f�B�q���[�Y�e�N�X�`���擾�֐�
//--------------------------------------------------
LPDIRECT3DTEXTURE9 FieldDraw::getpDiffuseTexture(unsigned object_index,
												unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return diffuse_texture_->getpHandler();
}