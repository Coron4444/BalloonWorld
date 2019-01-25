//================================================================================
//
//    FBX���f���}�l�[�W���N���X�w�b�_
//    Author : Araki Kai                                �쐬�� : 2018/01/21
//
//================================================================================



//**********************************************************************
//
// �C���N���[�h��
//
//**********************************************************************

#include "ModelFBXManager.h"

#include <ModelFBX\ModelFBXObject\ModelFBXObject.h>

#include <Texture\TextureManager\TextureManager.h>


//**********************************************************************
//
// ��ÓI�����o�֐���`
//
//**********************************************************************

//================================================================================
//
// [ �R���X�g���N�^ ]
//
//================================================================================

ModelFBXManager::ModelFBXManager(TextureManager* texture_manager)
	: texture_manager_(texture_manager)
{
}



//================================================================================
//
// [ �f�X�g���N�^ ]
//
//================================================================================

ModelFBXManager::~ModelFBXManager()
{
	// �eFBX���f���̉��
	for(auto& contents : model_map_)
	{
		if (contents.second != nullptr)
		{
			delete contents.second;
			contents.second = nullptr;
		}
	}

	// �}�b�v�̑S����
	model_map_.clear();
}



//================================================================================
//
// [ FBX���f���I�u�W�F�N�g�o�^�֐� ]
//
//================================================================================

void ModelFBXManager::RegistrationModelFBXObject(const std::string* key_name, const std::string* file_path)
{
	// �o�^�̊m�F
	auto itr = model_map_.find(*key_name);

	if(itr != model_map_.end())
	{
		// �ݒ肳��Ă���ꍇ
		return;
	}
	else
	{
		// �ݒ肳��Ă��Ȃ��ꍇ
		model_map_.insert(std::make_pair(*key_name, new ModelFBXObject(texture_manager_, key_name, file_path)));
	}
}



//================================================================================
//
// [ FBX���f���擾�֐� ]
//
//================================================================================

ModelFBXObject* ModelFBXManager::GetModelFBXObject(const std::string* key_name)
{
	// �o�^�̊m�F
	auto itr = model_map_.find(*key_name);

	if(itr != model_map_.end())
	{
		// �ݒ肳��Ă���ꍇ
		return itr->second;
	}
	else
	{
		// �ݒ肳��Ă��Ȃ��ꍇ
		return nullptr;
	}
}



//================================================================================
//
// [ FBX���f���Z�b�g�֐� ]
//
//================================================================================

void ModelFBXManager::SetModelFBXObject(const std::string* key_name)
{
	// �o�^�̊m�F
	auto itr = model_map_.find(*key_name);

	if(itr != model_map_.end())
	{
		// �ݒ肳��Ă���ꍇ
		itr->second->SetModelFBXObject();
		return;
	}
}