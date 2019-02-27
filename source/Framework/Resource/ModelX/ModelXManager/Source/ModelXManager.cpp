//================================================================================
//!	@file	 ModelXManager.cpp
//!	@brief	 X���f���}�l�[�W��Class
//! @details Singleton
//!	@author  Kai Araki									@date 2019/1/11
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../ModelXManager.h"



//****************************************
// �萔��`
//****************************************
const std::string ModelXManager::DEFAULT_PATH = "Resource/ModelX/";



//****************************************
// static�ϐ���`
//****************************************
ModelXManager* ModelXManager::instance_ = nullptr;



//****************************************
// static�v���p�e�B��`
//****************************************
ModelXManager* ModelXManager::getpInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new ModelXManager();
	}
	return instance_;
}



//****************************************
// static�֐���`
//****************************************
void ModelXManager::ReleaseInstance()
{
	SafeRelease::Normal(&instance_);
}



//****************************************
// �v���p�e�B��`
//****************************************
ModelXObject* ModelXManager::getpObject(const std::string* key_name,
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
	ModelXObject* object = new ModelXObject();
	object->Init(&path, key_name);
	object->AddReferenceCounter();
	object_map_.insert(std::make_pair(*key_name, object));
	return object;
}



//****************************************
// �֐���`
//****************************************
ModelXManager::ModelXManager()
{
}



void ModelXManager::Init()
{
	// �}�b�v�̏�����
	object_map_.clear();
}



void ModelXManager::Uninit()
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



void ModelXManager::ReleaseFromTheMap(std::string* key_name)
{
	// �}�b�v������
	auto iterator = object_map_.find(*key_name);
	if (iterator != object_map_.end())
	{
		object_map_.erase(iterator);
	}
}



std::string ModelXManager::CreateFilePath(const std::string* key_name,
										  const std::string* file_path)
{
	// �f�t�H���g�̃p�X���g�p
	if (file_path == nullptr) return DEFAULT_PATH + *key_name;

	// �C�ӂ̃p�X���g�p
	return *file_path + *key_name;
}