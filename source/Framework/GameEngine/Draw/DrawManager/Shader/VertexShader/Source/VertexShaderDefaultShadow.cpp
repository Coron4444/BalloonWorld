//================================================================================
//!	@file	 VertexShaderDefaultShadow.h
//!	@brief	 �f�t�H���g�e���_�V�F�[�_�[Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../VertexShaderDefaultShadow.h"



//****************************************
// �萔��`
//****************************************
const char* VertexShaderDefaultShadow::PATH = "resource/HLSL/Effect/VertexShader/DefaultShadow.vsh";
const float VertexShaderDefaultShadow::OFF_SET_X = 0.5f + (0.5f / GameEngine::SCREEN_WIDTH);
const float VertexShaderDefaultShadow::OFF_SET_Y = 0.5f + (0.5f / GameEngine::SCREEN_HEIGHT);
const MATRIX VertexShaderDefaultShadow::TEXTURE_PROJECTION =
{
	0.5f, 0.0f, 0.0f, 0.0f,
	0.0f, -0.5f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 0.0f,
	OFF_SET_X, OFF_SET_Y, 0.0f, 1.0f,
};



//****************************************
// �֐���`
//****************************************
void VertexShaderDefaultShadow::Init()
{
	// �f�o�C�X������
	InitDevice();

	// �V�F�[�_�[�̃R���p�C��
	VertexShaderCompile(PATH, "MainVertexShader", "vs_3_0");
}



void VertexShaderDefaultShadow::Uninit()
{
	// �V�F�[�_�[�̉��
	ReleaseVertexShader();
}



void VertexShaderDefaultShadow::ObjectSetting(DrawBase* draw, Camera* camera,
											unsigned object_index)
{
	// �s��
	getpConstantTable()->SetMatrix(getpDevice(), "MATRIX_WORLD",
								   draw->getpMatrix(object_index));
	getpConstantTable()->SetMatrix(getpDevice(), "MATRIX_VIEW",
								   camera->getpViewMatrix());
	getpConstantTable()->SetMatrix(getpDevice(), "MATRIX_PROJECTION",
								   camera->getpProjectionMatrix());
	getpConstantTable()->SetMatrix(getpDevice(), "LIGHT_VIEW",
								   getpDrawCommonData()->getpCameraShadowMap()
								   ->getpViewMatrix());
	getpConstantTable()->SetMatrix(getpDevice(), "LIGHT_PROJECTION",
								   getpDrawCommonData()->getpCameraShadowMap()
								   ->getpProjectionMatrix());
	getpConstantTable()->SetMatrix(getpDevice(), "TEXTURE_PROJECTION",
								   &TEXTURE_PROJECTION);

	// �f�B���N�V���i�����C�g�x�N�g��(�I�u�W�F�N�g�̃��[�J�����W�n�֕ϊ������)
	Vec4 light_vector = (Vec4)*getpDrawCommonData()
		->getpDirectionalLightVector();
	light_vector.w = 0.0f;
	D3DXMatrixIdentity(&math_matrix_);
	D3DXMatrixInverse(&math_matrix_, nullptr, draw->getpMatrix(object_index));
	D3DXVec4Transform(&light_vector, &light_vector, &math_matrix_);
	D3DXVec3Normalize((Vector3D*)&light_vector, (Vector3D*)&light_vector);
	light_vector.w = 0.5f;	// �����̔䗦
	getpConstantTable()->SetVector(getpDevice(), "DIRECTIONAL_LIGHT_VECTOR", 
								   &light_vector);
}



//--------------------------------------------------
// +�ŗL�ݒ�֐�
//--------------------------------------------------
void VertexShaderDefaultShadow::MeshSetting(DrawBase* draw, Camera* camera,
										  unsigned object_index, unsigned mesh_index)
{
	camera = camera;

	// �f�B�q���[�Y�F�̐ݒ�
	Vec4 material_diffuse_;
	material_diffuse_.x = draw->getpMaterial(object_index, mesh_index)->Diffuse.r;
	material_diffuse_.y = draw->getpMaterial(object_index, mesh_index)->Diffuse.g;
	material_diffuse_.z = draw->getpMaterial(object_index, mesh_index)->Diffuse.b;
	material_diffuse_.w = draw->getpMaterial(object_index, mesh_index)->Diffuse.a;
	getpConstantTable()->SetVector(getpDevice(), "MATERIAL_DIFFUSE",
								   &material_diffuse_);
}