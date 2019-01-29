//================================================================================
//!	@file	 VertexShaderFixed.cpp
//!	@brief	 �Œ�@�\���_�V�F�[�_�[Class
//! @details 
//!	@author  Kai Araki									@date 2019/01/19
//================================================================================


//****************************************
// �C���N���[�h��
//****************************************
#include "../VertexShaderFixed.h"



//****************************************
// �֐���`
//****************************************
void VertexShaderFixed::Init()
{
	// �f�o�C�X������
	ShaderBase::InitDevice();

	// �����_�[�X�e�[�g�̐ݒ�( �œK���̏ꍇ�͂��܂�Ă΂Ȃ��悤�ɐ݌v���� )
	((RendererDirectX9*)Renderer::getpInstance()->getpRenderer())->UseAlphaBlending(true);
	((RendererDirectX9*)Renderer::getpInstance()->getpRenderer())->SetAlphaBlending_Linear();

	// �e�N�X�`���[�X�e�[�W�X�e�[�g�̐ݒ�
	// �������e�N�X�`���X�e�[�W�ԍ�
	// ���������l�̉��Z����͏�Z(RG1*RG2�܂�ATEXTURE��DIFFUSE)
	getpDevice()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	getpDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	getpDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	// �T���v���[�X�e�[�g�̐ݒ�
	((RendererDirectX9*)Renderer::getpInstance()->getpRenderer())->SetDefaultSamplerState();
}



void VertexShaderFixed::Uninit()
{
}



void VertexShaderFixed::ObjectSetting(DrawBase* draw, Camera* camera, unsigned object_index)
{
	// �@�������1�ɐ��K��
	getpDevice()->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	// �s��̃Z�b�g
	getpDevice()->SetTransform(D3DTS_VIEW, camera->getpViewMatrix());
	getpDevice()->SetTransform(D3DTS_PROJECTION, camera->getpProjectionMatrix());
	getpDevice()->SetTransform(D3DTS_WORLD, draw->getpMatrix(object_index));

	// ���C�g�Z�b�g
	getpDevice()->SetRenderState(D3DRS_LIGHTING, draw->getpDrawOrderList()->getIsLighting());

	// ���C�g�̍X�V
	UpdateDirectionalLignt();
}



void VertexShaderFixed::MeshSetting(DrawBase* draw, Camera* camera,
									unsigned object_index, unsigned mesh_index)
{
	camera = camera;

	SetTexture(draw, object_index, mesh_index);
	SetMaterial(draw, object_index, mesh_index);
}



void VertexShaderFixed::SetTexture(DrawBase* draw, unsigned object_index,
								   unsigned mesh_index)
{
	LPDIRECT3DTEXTURE9 diffuse_texture = draw->getpDiffuseTexture(object_index,
																  mesh_index);
	getpDevice()->SetTexture(0, diffuse_texture);
}



void VertexShaderFixed::SetMaterial(DrawBase* draw, unsigned object_index,
									unsigned mesh_index)
{
	D3DMATERIAL9* material = draw->getpMaterial(object_index, mesh_index);
	if (material == nullptr) return;
	getpDevice()->SetMaterial(material);
}



void VertexShaderFixed::UpdateDirectionalLignt()
{
	// ���C�g�̐ݒ�
	ZeroMemory(&directional_light_, sizeof(directional_light_));

	directional_light_.Type = D3DLIGHT_DIRECTIONAL;

	// ���C�g������P�ʃx�N�g���ő��
	Vec3 directional_light_vector = *getpDrawCommonData()->getpDirectionalLightVector();
	D3DXVec3Normalize((D3DXVECTOR3*)&directional_light_.Direction, &directional_light_vector);

	// ���C�g�J���[
	directional_light_.Diffuse.r = 1.0f;
	directional_light_.Diffuse.g = 1.0f;
	directional_light_.Diffuse.b = 1.0f;
	directional_light_.Diffuse.a = 1.0f;

	// �A���r�G���g���C�g
	directional_light_.Ambient.r = 0.1f;
	directional_light_.Ambient.g = 0.1f;
	directional_light_.Ambient.b = 0.1f;
	directional_light_.Ambient.a = 1.0f;

	// �O���[�o���A���r�G���g�̐ݒ�
	getpDevice()->SetRenderState(D3DRS_AMBIENT, D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f));

	// ���C�g���f�o�C�X�ɃZ�b�g(��������0�`4�̃��C�g�ԍ�)
	getpDevice()->SetLight(0, &directional_light_);

	// 0�ԃ��C�g���g����悤�ɂ���
	getpDevice()->LightEnable(0, TRUE);
}