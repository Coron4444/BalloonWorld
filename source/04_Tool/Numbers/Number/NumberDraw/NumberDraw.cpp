//================================================================================
//
//    �����`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/06/19
//
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include <assert.h>

#include "NumberDraw.h"

#include <Texture/TextureManager/TextureManager.h>
#include <Polygon\PlanePolygon\PlanePolygon.h>
#include <SafeRelease/SafeRelease.h>



//****************************************
// ��ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +�������֐�
//--------------------------------------------------
void NumberDraw::Init()
{
	// �I�[�_�[���X�g�ݒ�
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::TWO_DIMENSIONAL);
	getpDrawOrderList()->getpRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::FIXED);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::FIXED);

	// �_�E���L���X�g
	number_ = (Number*)getpGameObject();
}



//--------------------------------------------------
// +�I���֐�
//--------------------------------------------------
void NumberDraw::Uninit()
{

}



//--------------------------------------------------
// +�`��֐�
//--------------------------------------------------
void NumberDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	number_->plane_polygon_->Draw();
}



//--------------------------------------------------
// +���b�V�����擾�֐�
//--------------------------------------------------
unsigned NumberDraw::getMeshNum(unsigned object_index)
{
	object_index = object_index;
	return number_->plane_polygon_->getMeshNum();
}



//--------------------------------------------------
// +�s��擾�֐�
//--------------------------------------------------
MATRIX* NumberDraw::getpMatrix(unsigned object_index)
{
	object_index = object_index;

	return getpGameObject()->GetTransform()->getpWorldMatrix();
}



//--------------------------------------------------
// +�}�e���A���擾�֐�
//--------------------------------------------------
D3DMATERIAL9* NumberDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return number_->plane_polygon_->GetMaterial();
}



//--------------------------------------------------
// +�f�B�q���[�Y�e�N�X�`���擾�֐�
//--------------------------------------------------
LPDIRECT3DTEXTURE9 NumberDraw::getpDiffuseTexture(unsigned object_index,
												 unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return number_->diffuse_texture_->getpHandler();
}