//================================================================================
//!	@file	 VertexShaderBumpMapping.cpp
//!	@brief	 �o���v�}�b�s���O���_�V�F�[�_�[Class
//! @details 
//!	@author  Kai Araki									@date 2019/01/19
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../VertexShaderBumpMapping.h"



//****************************************
// �萔��`
//****************************************
const D3DVERTEXELEMENT9 VertexShaderBumpMapping::DECLARATION[] =
{
	{0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
	{0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0},
	{0, 24, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT,  0},
	{0, 36, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
	D3DDECL_END()
};

const char* VertexShaderBumpMapping::PATH = "resource/HLSL/Effect/VertexShader/BumpMapping.vsh";



//****************************************
// static�֐���`
//****************************************
void VertexShaderBumpMapping::UpdateMeshDeclaration(ModelXObject* model_x)
{
	model_x->UpdateMeshDeclaration(DECLARATION);						// ���b�V���̕ύX
	D3DXComputeNormals(model_x->getpMesh(), nullptr);					// �@�����Z�o
	D3DXComputeTangent(model_x->getpMesh(), 0, 0, 0, TRUE, nullptr);	//�ڃx�N�g�����Z�o
}



//****************************************
// �֐���`
//****************************************
void VertexShaderBumpMapping::Init()
{
	// �f�o�C�X������
	InitDevice();

	// ���_�錾�I�u�W�F�N�g�̐���
	getpDevice()->CreateVertexDeclaration(DECLARATION, &declaration_object_);

	// �V�F�[�_�[�̃R���p�C��
	VertexShaderCompile(PATH, "MainVertexShader", "vs_3_0");
}



void VertexShaderBumpMapping::Uninit()
{
	// �V�F�[�_�[�̉��
	ReleaseVertexShader();

	SafeRelease::PlusRelease(&declaration_object_);
}



void VertexShaderBumpMapping::ObjectSetting(DrawBase* draw, Camera* camera,
											unsigned object_index)
{
	// �s��̃Z�b�g
	getpConstantTable()->SetMatrix(getpDevice(),
								   "MATRIX_WORLD",
								   draw->getpMatrix(object_index));
	getpConstantTable()->SetMatrix(getpDevice(),
								   "MATRIX_VIEW",
								   camera->getpViewMatrix());
	getpConstantTable()->SetMatrix(getpDevice(),
								   "MATRIX_PROJECTION",
								   camera->getpProjectionMatrix());

	// ���C�g�������Z�b�g
	Vec4 light_position = (Vec4)*getpDrawCommonData()->getpDirectionalLightVector();
	light_position.w = 0.0f;
	D3DXMatrixIdentity(&math_matrix_);
	D3DXMatrixInverse(&math_matrix_, nullptr, draw->getpMatrix(object_index));
	D3DXVec4Transform(&light_position, &light_position, &math_matrix_);
	D3DXVec3Normalize((Vector3D*)&light_position, (Vector3D*)&light_position);
	light_position.w = -0.7f;		// �����̔䗦
	getpConstantTable()->SetVector(getpDevice(),
								   "LAMBERT_DIFFUSE_LIGHT_VECTOR",
								   &light_position);

	// ���_�̐ݒ�(�I�u�W�F�N�g���Ƃ̃��[�J�����W�ł̃J�����̍��W���擾����)
	D3DXMatrixIdentity(&math_matrix_);
	D3DXMatrixMultiply(&math_matrix_, draw->getpMatrix(object_index),
					   camera->getpViewMatrix());
	D3DXMatrixInverse(&math_matrix_, nullptr, &math_matrix_);
	Vec4 object_local_camera_position(0.0f, 0.0f, 0.0f, 1.0f);
	D3DXVec4Transform(&object_local_camera_position, &object_local_camera_position, &math_matrix_);
	getpConstantTable()->SetVector(getpDevice(),
								   "CAMERA_POSITION",
								   &object_local_camera_position);

	// ���_�錾
	getpDevice()->SetVertexDeclaration(declaration_object_);
}



//--------------------------------------------------
// +�ŗL�ݒ�֐�
//--------------------------------------------------
void VertexShaderBumpMapping::MeshSetting(DrawBase* draw, Camera* camera,
										  unsigned object_index, unsigned mesh_index)
{
	camera = camera;

	// �f�B�q���[�Y�F�̐ݒ�
	Vec4 lambert_diffuse_light_color_;
	lambert_diffuse_light_color_.x = draw->getpMaterial(object_index, mesh_index)->Diffuse.r;
	lambert_diffuse_light_color_.y = draw->getpMaterial(object_index, mesh_index)->Diffuse.g;
	lambert_diffuse_light_color_.z = draw->getpMaterial(object_index, mesh_index)->Diffuse.b;
	lambert_diffuse_light_color_.w = draw->getpMaterial(object_index, mesh_index)->Diffuse.a;
	getpConstantTable()->SetVector(getpDevice(),
								   "LAMBERT_DIFFUSE_LIGHT_COLOR",
								   &lambert_diffuse_light_color_);
}
