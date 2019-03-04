//================================================================================
//!	@file	 VertexShaderAnimatedDefault.cpp
//!	@brief	 �A�j���[�V�����t���f�t�H���g���_�V�F�[�_�[Class
//! @details 
//!	@author  Kai Araki									@date 2019/01/19
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../VertexShaderAnimatedDefault.h"



//****************************************
// �萔��`
//****************************************
const D3DVERTEXELEMENT9 VertexShaderAnimatedDefault::VERTEX_DECLARATION[] =
{
	{0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
	{0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
	{0, 24, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0},
	{0, 28, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
	{0, 36, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDWEIGHT, 0},
	{0, 52, D3DDECLTYPE_UBYTE4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDINDICES, 0},
	D3DDECL_END()
};

const char* VertexShaderAnimatedDefault::PATH = "resource/HLSL/Effect/VertexShader/AnimatedDefault.vsh";



//****************************************
// �֐���`
//****************************************
void VertexShaderAnimatedDefault::Init()
{
	// �f�o�C�X������
	InitDevice();

	// �V�F�[�_�[�̃R���p�C��
	VertexShaderCompile(PATH, "MainVertexShader", "vs_3_0");

	// ���_�錾�̍쐬
	LPDIRECT3DDEVICE9 device;
	Renderer::getpInstance()->getDevice(&device);
	if (device == nullptr)
	{
		MessageBox(nullptr, "NotGetDevice!(MdBinManager.cpp)", "Error", MB_OK);
	}
	device->CreateVertexDeclaration(VERTEX_DECLARATION, &vertex_declaration_);

	// �{�[���s��̏�����
	for (int i = 0; i < MAX_BONE_NUM; i++)
	{
		D3DXMatrixIdentity(&bone_matrix_[i]);
	}
}



void VertexShaderAnimatedDefault::Uninit()
{
	// �V�F�[�_�[�̉��
	ReleaseVertexShader();

	// ���_�錾���
	SafeRelease::PlusRelease(&vertex_declaration_);
}



void VertexShaderAnimatedDefault::ObjectSetting(DrawBase* draw, Camera* camera,
												unsigned object_index)
{
	// ���_�錾
	getpDevice()->SetVertexDeclaration(vertex_declaration_);

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
}



void VertexShaderAnimatedDefault::MeshSetting(DrawBase* draw, Camera* camera,
											  unsigned object_index,
											  unsigned mesh_index)
{
	camera = camera;
	// �{�[���̑��
	int bone_num = draw->getBoneNum(object_index, mesh_index);
	for (int i = 0; i < bone_num; i++)
	{
		bone_matrix_[i] = *draw->getpBoneMatrix(object_index, mesh_index, i);
	}

	// �{�[���s��̃Z�b�g
	getpConstantTable()->SetMatrixArray(getpDevice(), "MATRIX_BONE",
										bone_matrix_, bone_num);
}