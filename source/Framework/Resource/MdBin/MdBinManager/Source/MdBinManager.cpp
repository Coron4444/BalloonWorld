//================================================================================
//!	@file	 MdBinManager.cpp
//!	@brief	 �o�C�i���[���f���}�l�[�W��Class
//! @details Singleton
//!	@author  Kai Araki									@date 2019/1/11
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../MdBinManager.h"



//****************************************
// �萔��`
//****************************************
const std::string MdBinManager::DEFAULT_PATH = "Resource/MdBin/";



//****************************************
// static�ϐ���`
//****************************************
MdBinManager* MdBinManager::instance_ = nullptr;



//****************************************
// static�v���p�e�B��`
//****************************************
MdBinManager* MdBinManager::getpInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new MdBinManager();
	}
	return instance_;
}



//****************************************
// static�֐���`
//****************************************
void MdBinManager::ReleaseInstance()
{
	SafeRelease::Normal(&instance_);
}



//****************************************
// �v���p�e�B��`
//****************************************
MdBinObject* MdBinManager::getpObject(const std::string* key_name,
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
	MdBinObject* object = new MdBinObject();
	object->Init(&path, key_name);
	object->AddReferenceCounter();
	object_map_.insert(std::make_pair(*key_name, object));
	return object;
}



//****************************************
// �֐���`
//****************************************
MdBinManager::MdBinManager()
{
}



void MdBinManager::Init()
{
	// �}�b�v�̏�����
	object_map_.clear();
}



void MdBinManager::Uninit()
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



void MdBinManager::ReleaseFromTheMap(std::string* key_name)
{
	// �}�b�v������
	auto iterator = object_map_.find(*key_name);
	if (iterator != object_map_.end())
	{
		object_map_.erase(iterator);
	}
}



std::string MdBinManager::CreateFilePath(const std::string* key_name,
										 const std::string* file_path)
{
	// �f�t�H���g�̃p�X���g�p
	if (file_path == nullptr) return DEFAULT_PATH + *key_name;

	// �C�ӂ̃p�X���g�p
	return *file_path + *key_name;
}