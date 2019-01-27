//================================================================================
//!	@file	 TextureManager.cpp
//!	@brief	 �e�N�X�`���}�l�[�W��Class
//! @details Singleton
//!	@author  Kai Araki									@date 2019/1/11
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../TextureManager.h"

#include <Tool/SafeRelease.h>



//****************************************
// �萔��`
//****************************************
const std::string TextureManager::DEFAULT_PATH = "Resource/Texture/";



//****************************************
// static�ϐ���`
//****************************************
TextureManager* TextureManager::instance_ = nullptr;



//****************************************
// static�v���p�e�B��`
//****************************************
TextureManager* TextureManager::getpInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new TextureManager();
	}
	return instance_;
}



//****************************************
// static�֐���`
//****************************************
void TextureManager::ReleaseInstance()
{
	SafeRelease::Normal(&instance_);
}



//****************************************
// �v���p�e�B��`
//****************************************
TextureObject* TextureManager::getpObject(const std::string* key_name,
										  const std::string* file_path)
{
	// �}�b�v�ɂ��邩�̊m�F
	auto iterator = object_map_.find(*key_name);
	if (iterator != object_map_.end())
	{
		// �Q�ƃJ�E���^��UP
		iterator->second->AddReferenceCounter();
		
		return iterator->second;
	}

	// �V�K�쐬
	std::string path = CreateFilePath(key_name, file_path);
	TextureObject* object = new TextureObject();
	object->Init(&path, key_name);
	object->AddReferenceCounter();
	object_map_.insert(std::make_pair(*key_name, object));
	return object;
}



//****************************************
// �֐���`
//****************************************
TextureManager::TextureManager()
{
}



void TextureManager::Init()
{
	// �}�b�v�̏�����
	object_map_.clear();
}



void TextureManager::Uninit()
{
	// �e�I�u�W�F�N�g�̋������
	auto iterator = object_map_.begin();
	while (iterator != object_map_.end())
	{
		iterator->second->ForcedRelease();
		iterator = object_map_.begin();
	}
	object_map_.clear();
}



void TextureManager::ReleaseFromTheMap(std::string* key_name)
{
	// �}�b�v������
	auto iterator = object_map_.find(*key_name);
	if (iterator != object_map_.end())
	{
		object_map_.erase(iterator);
	}
}



std::string TextureManager::CreateFilePath(const std::string* key_name,
										   const std::string* file_path)
{
	// �f�t�H���g�̃p�X���g�p
	if (file_path == nullptr) return DEFAULT_PATH + *key_name;

	// �C�ӂ̃p�X���g�p
	return *file_path + *key_name;
}