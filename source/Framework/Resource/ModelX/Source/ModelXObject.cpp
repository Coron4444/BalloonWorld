//================================================================================
//!	@file	 ModelXObject.cpp
//!	@brief	 X���f���I�u�W�F�N�gClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/01
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../ModelXObject.h"
#include "../ModelXManager/ModelXManager.h"
#include "../../Texture/TextureManager/TextureManager.h"

#include <Tool/SafeRelease.h>



//****************************************
// �v���p�e�B��`
//****************************************
LPD3DXMESH ModelXObject::getpMesh()
{
	return mesh_;
}



unsigned ModelXObject::getMeshNum()
{
	return mesh_num_;
}



D3DMATERIAL9* ModelXObject::getpMaterial(unsigned index)
{
	return &material_[index];
}



void ModelXObject::setMaterialColor(unsigned index, XColor4 color)
{
	material_[index].Diffuse.r = color.r;
	material_[index].Diffuse.g = color.g;
	material_[index].Diffuse.b = color.b;
	material_[index].Diffuse.a = color.a;
}



TextureObject* ModelXObject::getpDiffuseTextureObject(unsigned index)
{
	return diffuse_texture_object_[index];
}



//****************************************
// �֐���`
//****************************************
void ModelXObject::Init(std::string* file_path, const std::string* map_key_name)
{
	// �}�e���A���o�b�t�@
	LPD3DXBUFFER material_buffer = nullptr;

	// ���b�V������
	CreateMesh(file_path, &material_buffer);

	// �}�e���A������
	CreateMaterial(file_path, &material_buffer);

	// �L�[���ۑ�
	map_key_name_ = *map_key_name;
}



void ModelXObject::Release()
{
	reference_counter_--;
	if (reference_counter_ > 0) return;

	SafeRelease::PlusRelease(&mesh_);

	for (auto& contents : diffuse_texture_object_)
	{
		SafeRelease::PlusRelease(&contents);
	}

	ModelXManager::getpInstance()->ReleaseFromTheMap(&map_key_name_);
	delete this;
}



void ModelXObject::ForcedRelease()
{
	reference_counter_ = 0;
	Release();
}



void ModelXObject::AddReferenceCounter()
{
	reference_counter_++;
}



void ModelXObject::UpdateMeshDeclaration(const D3DVERTEXELEMENT9* declaration)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 device = nullptr;
	Renderer::getpInstance()->getDevice(&device);
	if (device == nullptr)
	{
		MessageBox(nullptr, "NotGetDevice!(ModelXObject.cpp)", "Error", MB_OK);
		return;
	}

	// ���_���̕ύX
	LPD3DXMESH temp_mesh;
	mesh_->CloneMesh(mesh_->GetOptions(),
					 declaration,
					 device,
					 &temp_mesh);

	SafeRelease::PlusRelease(&mesh_);

	mesh_ = temp_mesh;
}



void ModelXObject::CreateMesh(std::string* file_path, LPD3DXBUFFER* material_buffer)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 device = nullptr;
	Renderer::getpInstance()->getDevice(&device);
	if (device == nullptr)
	{
		MessageBox(nullptr, "NotGetDevice!(ModelXObject.cpp)", "Error", MB_OK);
		return;
	}

	HRESULT hr = D3DXLoadMeshFromX(file_path->c_str(),	// �t�@�C����
								   D3DXMESH_SYSTEMMEM,	// ��xCPU�ōœK���������̂�VRAM�ɓn��
								   device,				// �f�o�C�X
								   nullptr,				// �אڐ����
								   material_buffer,		// �}�e���A�����
								   NULL,				// �G�t�F�N�g�̏�����
								   &mesh_num_,			// ���b�V����
								   &mesh_);				// ���b�V��
	if (FAILED(hr))
	{
		MessageBox(nullptr, "���b�V���̐����Ɏ��s(TextureObject.cpp)", "Error", MB_OK);
		return;
	}
}



void ModelXObject::CreateMaterial(std::string* file_path, LPD3DXBUFFER* material_buffer)
{
	// �}�e���A���T�C�Y�ύX
	material_.resize(mesh_num_);

	// �}�e���A���̏����̃|�C���^�擾
	LPD3DXMATERIAL temp_material = (LPD3DXMATERIAL)(*material_buffer)->GetBufferPointer();

	// �}�e���A���ŕ��������p�[�c����
	for (DWORD i = 0; i < mesh_num_; i++)
	{
		ZeroMemory(&material_[i], sizeof(D3DMATERIAL9));

		// �f�q���[�Y�J���[�̐ݒ�
		material_[i].Diffuse.r = temp_material[i].MatD3D.Diffuse.r;
		material_[i].Diffuse.g = temp_material[i].MatD3D.Diffuse.g;
		material_[i].Diffuse.b = temp_material[i].MatD3D.Diffuse.b;
		material_[i].Diffuse.a = temp_material[i].MatD3D.Diffuse.a;

		// �A���r�G���g�J���[�̐ݒ�
		material_[i].Ambient.r = temp_material[i].MatD3D.Ambient.r;
		material_[i].Ambient.g = temp_material[i].MatD3D.Ambient.g;
		material_[i].Ambient.b = temp_material[i].MatD3D.Ambient.b;
		material_[i].Ambient.a = temp_material[i].MatD3D.Ambient.a;

		// �e�N�X�`���̓ǂݍ���
		if (temp_material[i].pTextureFilename == NULL) continue;
		std::string key_name = temp_material[i].pTextureFilename;
		std::string path = *file_path;
		CreateFilePathAndKeyName(&path, &key_name);

		TextureObject* texture_object = TextureManager::getpInstance()->getpObject(&key_name, &path);
		diffuse_texture_object_.push_back(texture_object);
	}

	// �}�e���A���o�b�t�@�̉��
	SafeRelease::PlusRelease(material_buffer);
}



void ModelXObject::CreateFilePathAndKeyName(std::string* file_path,
											std::string* key_name)
{
	// �t�@�C���p�X����t�H���_����/�t���Ŏ擾
	auto slash_index = file_path->rfind("/");
	auto slash_index2 = file_path->rfind("/", slash_index - 1);
	unsigned temp_num = (unsigned)(slash_index - slash_index2);
	std::string temp_strign = file_path->substr(slash_index2 + 1, temp_num);

	// �L�[�l�[���̍쐬
	*key_name = temp_strign + *key_name;

	// �t�@�C���p�X�̍쐬
	*file_path = file_path->substr(0, slash_index2 + 1);
}