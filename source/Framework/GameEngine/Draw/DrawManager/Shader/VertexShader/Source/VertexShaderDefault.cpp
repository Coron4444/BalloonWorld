//================================================================================
//!	@file	 VertexShaderDefault.h
//!	@brief	 �f�t�H���g���_�V�F�[�_�[Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/19
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../VertexShaderDefault.h"



//****************************************
// �萔��`
//****************************************
const char* VertexShaderDefault::PATH = "resource/HLSL/Effect/VertexShader/Default.vsh";



//****************************************
// �֐���`
//****************************************
void VertexShaderDefault::Init()
{
	// �f�o�C�X������
	InitDevice();

	// �V�F�[�_�[�̃R���p�C��
	VertexShaderCompile(PATH, "MainVertexShader", "vs_3_0");
}



void VertexShaderDefault::Uninit()
{
	// �V�F�[�_�[�̉��
	ReleaseVertexShader();
}



void VertexShaderDefault::ObjectSetting(DrawBase* draw, Camera* camera,
											unsigned object_index)
{
	// �s��
	getpConstantTable()->SetMatrix(getpDevice(), "MATRIX_WORLD",
								   draw->getpMatrix(object_index));
	getpConstantTable()->SetMatrix(getpDevice(), "MATRIX_VIEW",
								   camera->getpViewMatrix());
	getpConstantTable()->SetMatrix(getpDevice(), "MATRIX_PROJECTION",
								   camera->getpProjectionMatrix());

	// �f�B���N�V���i�����C�g�x�N�g��(�I�u�W�F�N�g�̃��[�J�����W�n�֕ϊ������)
	Vec4 light_vector = (Vec4)*getpDrawCommonData()
		->getpDirectionalLightVector();
	light_vector.w = 0.0f;
	D3DXMatrixIdentity(&math_matrix_);
	D3DXMatrixInverse(&math_matrix_, nullptr, draw->getpMatrix(object_index));
	D3DXVec4Transform(&light_vector, &light_vector, &math_matrix_);
	D3DXVec3Normalize((Vector3D*)&light_vector, (Vector3D*)&light_vector);
	light_vector.w = 0.9f;	// �����̔䗦
	getpConstantTable()->SetVector(getpDevice(), "DIRECTIONAL_LIGHT_VECTOR", 
								   &light_vector);
}



//--------------------------------------------------
// +�ŗL�ݒ�֐�
//--------------------------------------------------
void VertexShaderDefault::MeshSetting(DrawBase* draw, Camera* camera,
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