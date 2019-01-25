//================================================================================
//
//    �Q�[���I�u�W�F�N�g�̎Q�ƃ}�l�[�W���N���X
//    Author : Araki Kai                                �쐬�� : 2018/07/15
//
//================================================================================



//**********************************************************************
//
// �C���N���[�h��
//
//**********************************************************************

#include "GameObjectReferenceManager.h"
#include "../../GameObjectBase/GameObjectBase.h"
#include <SafeRelease/SafeRelease.h>



//**********************************************************************
//
// ��ÓI�����o�֐���`
//
//**********************************************************************

//================================================================================
//
// [ �f�t�H���g�R���X�g���N�^ ]
//
//================================================================================

GameObjectReferenceManager::GameObjectReferenceManager()
{
}



//================================================================================
//
// [ �f�X�g���N�^ ]
//
//================================================================================

GameObjectReferenceManager::~GameObjectReferenceManager()
{
	// �S�ĉ��
	AllReleaseReference();
}



//================================================================================
//
// [ �Q�ƃf�[�^�o�^�֐� ]
//
//================================================================================

void GameObjectReferenceManager::RegistrationReference(GameObjectBase* source, void* pointer, 
													   GameObjectBase* destination)
{
	// �Q�ƌ��}�b�v�ւ̓o�^�̊m�F
	RegistrationReference_Source(source, pointer, destination);

	// �Q�Ɛ�}�b�v�ւ̓o�^
	RegistrationReference_Source(source, pointer, destination);
}



//================================================================================
//
// [ �Q�Ɛ�f�[�^����֐� ]
//
//================================================================================

void GameObjectReferenceManager::ReleaseReference(GameObjectBase* object)
{
	// �Q�ƌ��}�b�v�������
	ReleaseReference_Source(object);

	// �Q�Ɛ�}�b�v��������y��nullptr����
	ReleaseReference_Destination(object);
}



//================================================================================
//
// [ �S�Ă̎Q�ƃf�[�^����֐� ]
//
//================================================================================

void GameObjectReferenceManager::AllReleaseReference()
{
	// �Q�ƌ��}�b�v�̉��
	for(auto& contents : reference_map_.source_map_)
	{
		if (contents.second == nullptr) return;
		
		for (unsigned i = 0; i < contents.second->GetEndPointer(); i++)
		{
			ReferenceData* temp = contents.second->GetArrayObject(i);
			SafeRelease::Normal(&temp);
		}

		SafeRelease::Normal(&contents.second);
	}

	// �Q�Ɛ�}�b�v�̉��
	for(auto& contents : reference_map_.destination_map_)
	{
		if (contents.second == nullptr) return;
		
		for (unsigned i = 0; i < contents.second->GetEndPointer(); i++)
		{
			ReferenceData* temp = contents.second->GetArrayObject(i);
			SafeRelease::Normal(&temp);
		}

		SafeRelease::Normal(&contents.second);
	}
}



//================================================================================
//
// [ �Q�ƌ��o�^�֐� ]
//
//================================================================================

void GameObjectReferenceManager::RegistrationReference_Source(GameObjectBase* source, void* pointer, 
															  GameObjectBase* destination)
{
	// �Q�ƌ��̌���
	auto iterator = reference_map_.source_map_.find(source);

	// �o�^����Ă��Ȃ��ꍇ
	if (iterator == reference_map_.source_map_.end())
	{
		// �Q�ƃf�[�^�z����쐬
		LimitedPointerArray<ReferenceData*, ARRAY_NUM>* temp_array = new LimitedPointerArray<ReferenceData*, ARRAY_NUM>;
		temp_array->AddToArray(new ReferenceData(source, pointer, destination));
		
		// �Q�ƌ��}�b�v�ɎQ�ƃf�[�^�z���o�^
		reference_map_.source_map_.insert(std::make_pair(source, temp_array));
	}
	else
	{
		// �o�^����Ă���ꍇ
		unsigned index;
		for (index = 0; index < iterator->second->GetEndPointer(); index++)
		{
			// �����Q�Ɛ悪���邩�ǂ���
			if (iterator->second->GetArrayObject(index)->reference_destination_ != destination) continue;
			
			break;
		}

		// �����Q�Ɛ悪�Ȃ��̂œo�^
		if (index != iterator->second->GetEndPointer())
		{
			// �ǉ�
			iterator->second->AddToArray(new ReferenceData(source, pointer, destination));
		}
	}
}



//================================================================================
//
// [ �Q�Ɛ�o�^�֐� ]
//
//================================================================================

void GameObjectReferenceManager::RegistrationReference_Destination(GameObjectBase* source, void* pointer, 
																   GameObjectBase* destination)
{
	// �Q�Ɛ�̌���
	auto iterator = reference_map_.destination_map_.find(destination);

	// �o�^����Ă��Ȃ��ꍇ
	if (iterator == reference_map_.destination_map_.end())
	{
		// �Q�ƃf�[�^�z����쐬
		LimitedPointerArray<ReferenceData*, ARRAY_NUM>* temp_array = new LimitedPointerArray<ReferenceData*, ARRAY_NUM>;
		temp_array->AddToArray(new ReferenceData(source, pointer, destination));
		
		// �Q�ƌ��}�b�v�ɎQ�ƃf�[�^�z���o�^
		reference_map_.destination_map_.insert(std::make_pair(destination, temp_array));
	}
	else
	{
		// �o�^����Ă���ꍇ
		unsigned index;
		for (index = 0; index < iterator->second->GetEndPointer(); index++)
		{
			// �����Q�Ɛ悪���邩�ǂ���
			if (iterator->second->GetArrayObject(index)->reference_source_ != source) continue;
			
			break;
		}

		// �����Q�Ɛ悪�Ȃ��̂œo�^
		if (index != iterator->second->GetEndPointer())
		{
			// �ǉ�
			iterator->second->AddToArray(new ReferenceData(source, pointer, destination));
		}
	}
}



//================================================================================
//
// [ �Q�ƌ��f�[�^����֐� ]
//
//================================================================================

void GameObjectReferenceManager::ReleaseReference_Source(GameObjectBase* object)
{
	auto iterator = reference_map_.source_map_.find(object);

	// �o�^����Ă���ꍇ
	if (iterator != reference_map_.source_map_.end())
	{
		for (unsigned i = 0; i < iterator->second->GetEndPointer(); i++)
		{
			// ���
			ReferenceData* temp = iterator->second->GetArrayObject(i);
			SafeRelease::Normal(&temp);
		}

		// �z��̉��
		SafeRelease::Normal(&iterator->second);

		// �Q�ƌ��}�b�v�������
		reference_map_.source_map_.erase(object);
	}
}



//================================================================================
//
// [ �Q�Ɛ�f�[�^����֐� ]
//
//================================================================================

void GameObjectReferenceManager::ReleaseReference_Destination(GameObjectBase* object)
{
	auto iterator = reference_map_.destination_map_.find(object);

	// �o�^����Ă���ꍇ
	if (iterator != reference_map_.destination_map_.end())
	{
		for (unsigned i = 0; i < iterator->second->GetEndPointer(); i++)
		{
			// nullptr�̑}��
			iterator->second->GetArrayObject(i)->reference_pointer_ = nullptr;

			// ���
			ReferenceData* temp = iterator->second->GetArrayObject(i);
			SafeRelease::Normal(&temp);
		}

		// �z��̉��
		SafeRelease::Normal(&iterator->second);

		// �Q�ƌ��}�b�v�������
		reference_map_.destination_map_.erase(object);
	}
}