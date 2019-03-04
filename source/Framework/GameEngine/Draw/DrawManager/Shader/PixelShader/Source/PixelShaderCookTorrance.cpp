//================================================================================
//!	@file	 PixelShaderCookTorrance.cpp
//!	@brief	 �N�b�N�E�g�����X�̋������˃s�N�Z���V�F�[�_�[Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/18
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../PixelShaderCookTorrance.h"



//****************************************
// �萔��`
//****************************************
const char* PixelShaderCookTorrance::PATH = "resource/HLSL/Effect/PixelShader/CookTorrance.psh";



//****************************************
// �֐���`
//****************************************
void PixelShaderCookTorrance::Init()
{
	// �f�o�C�X������
	InitDevice();

	// �f�t�H���g�e�N�X�`��������
	InitDefaultTexture();

	// �V�F�[�_�[�̃R���p�C��
	PixelShaderCompile(PATH, "MainPixelShader", "ps_3_0");
}



void PixelShaderCookTorrance::Uninit()
{
	// �V�F�[�_�[�̉��
	ReleasePixelShader();
}



void PixelShaderCookTorrance::ObjectSetting(DrawBase* draw, Camera* camera,
										   unsigned object_index)
{
	camera = camera;

	// �f�B���N�V���i�����C�g�x�N�g��(�I�u�W�F�N�g�̃��[�J�����W�n�֕ϊ������)
	Vec4 light_vector = (Vec4)*getpDrawCommonData()
		->getpDirectionalLightVector();
	light_vector.w = 0.0f;
	D3DXMatrixIdentity(&math_matrix_);
	D3DXMatrixInverse(&math_matrix_, nullptr, draw->getpMatrix(object_index));
	D3DXVec4Transform(&light_vector, &light_vector, &math_matrix_);
	D3DXVec3Normalize((Vector3D*)&light_vector, (Vector3D*)&light_vector);
	light_vector.w = 0.7f;	// �����̔䗦
	getpConstantTable()->SetVector(getpDevice(), "DIRECTIONAL_LIGHT_VECTOR",
								   &light_vector);

	// ���_�̐ݒ�(�I�u�W�F�N�g�̃��[�J�����W�ł̃J�������W���擾����)
	D3DXMatrixIdentity(&math_matrix_);
	D3DXMatrixMultiply(&math_matrix_, draw->getpMatrix(object_index),
					   camera->getpViewMatrix());
	D3DXMatrixInverse(&math_matrix_, nullptr, &math_matrix_);
	Vec4 object_local_camera_position(0.0f, 0.0f, 0.0f, 1.0f);
	D3DXVec4Transform(&object_local_camera_position, &object_local_camera_position, &math_matrix_);
	getpConstantTable()->SetVector(getpDevice(),
								   "CAMERA_POSITION",
								   &object_local_camera_position);
}



void PixelShaderCookTorrance::MeshSetting(DrawBase* draw, Camera* camera,
										 unsigned object_index, unsigned mesh_index)
{
	camera = camera;
	
	// �f�B�t�[�Y�e�N�X�`��
	int sampler_index = getpConstantTable()->GetSamplerIndex("DIFFUSE_SAMPLER");
	if (draw->getpDiffuseTexture(object_index, mesh_index) == nullptr)
	{
		getpDevice()->SetTexture(sampler_index, getpDefaultTexture());
	}
	else
	{
		getpDevice()->SetTexture(sampler_index,
								 draw->getpDiffuseTexture(object_index, mesh_index));
	}
}