//================================================================================
//!	@file	 GameObjectReferenceManager.cpp
//!	@brief	 �Q�[���I�u�W�F�N�g�Q�ƃ}�l�[�W��Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/15
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../GameObjectReferenceManager.h"
#include "../../GameObjectBase.h"
#include <Tool/SafeRelease.h>



//****************************************
// �֐���`
//****************************************
GameObjectReferenceManager::ReferenceData::ReferenceData(GameObjectBase* source,
														 void* pointer,
														 GameObjectBase* destination)
{
	reference_source_ = source;
	reference_destination_ = destination;
	reference_pointer_ = pointer;
}



GameObjectReferenceManager::~GameObjectReferenceManager()
{
	AllRelease();
}



void GameObjectReferenceManager::AddReference(GameObjectBase* source, void* pointer,
											  GameObjectBase* destination)
{
	// �Q�ƌ��}�b�v�ւ̓o�^�̊m�F
	AddSource(source, pointer, destination);

	// �Q�Ɛ�}�b�v�ւ̓o�^
	AddDestination(source, pointer, destination);
}



void GameObjectReferenceManager::Release(GameObjectBase* object)
{
	// �Q�ƌ��}�b�v�������
	ReleaseSource(object);

	// �Q�Ɛ�}�b�v��������y��nullptr����
	ReleaseDestination(object);
}



void GameObjectReferenceManager::AllRelease()
{
	// �Q�ƌ��}�b�v�̉��
	for (auto& contents : source_map_)
	{
		if (contents.second == nullptr) return;

		for (unsigned i = 0; i < contents.second->getEndIndex(); i++)
		{
			ReferenceData* temp = contents.second->getObject(i);
			SafeRelease::Normal(&temp);
		}

		SafeRelease::Normal(&contents.second);
	}

	// �Q�Ɛ�}�b�v�̉��
	for (auto& contents : destination_map_)
	{
		if (contents.second == nullptr) return;

		for (unsigned i = 0; i < contents.second->getEndIndex(); i++)
		{
			ReferenceData* temp = contents.second->getObject(i);
			SafeRelease::Normal(&temp);
		}

		SafeRelease::Normal(&contents.second);
	}
}



void GameObjectReferenceManager::AddSource(GameObjectBase* source, void* pointer,
										   GameObjectBase* destination)
{
	// �Q�ƌ��̌���
	auto iterator = source_map_.find(source);

	// �o�^����Ă��Ȃ��ꍇ
	if (iterator == source_map_.end())
	{
		// �Q�ƃf�[�^�z����쐬
		LimitedPointerArray<ReferenceData*, ARRAY_NUM>* temp_array = new LimitedPointerArray<ReferenceData*, ARRAY_NUM>;
		temp_array->AddToArray(new ReferenceData(source, pointer, destination));

		// �Q�ƌ��}�b�v�ɎQ�ƃf�[�^�z���o�^
		source_map_.insert(std::make_pair(source, temp_array));
	}
	else
	{
		// �o�^����Ă���ꍇ
		unsigned index;
		for (index = 0; index < iterator->second->getEndIndex(); index++)
		{
			// �����Q�Ɛ悪���邩�ǂ���
			if (iterator->second->getObject(index)->reference_destination_ != destination) continue;

			break;
		}

		// �����Q�Ɛ悪�Ȃ��̂œo�^
		if (index != iterator->second->getEndIndex())
		{
			// �ǉ�
			iterator->second->AddToArray(new ReferenceData(source, pointer, destination));
		}
	}
}



void GameObjectReferenceManager::AddDestination(GameObjectBase* source, void* pointer,
																   GameObjectBase* destination)
{
	// �Q�Ɛ�̌���
	auto iterator = destination_map_.find(destination);

	// �o�^����Ă��Ȃ��ꍇ
	if (iterator == destination_map_.end())
	{
		// �Q�ƃf�[�^�z����쐬
		LimitedPointerArray<ReferenceData*, ARRAY_NUM>* temp_array = new LimitedPointerArray<ReferenceData*, ARRAY_NUM>;
		temp_array->AddToArray(new ReferenceData(source, pointer, destination));

		// �Q�ƌ��}�b�v�ɎQ�ƃf�[�^�z���o�^
		destination_map_.insert(std::make_pair(destination, temp_array));
	}
	else
	{
		// �o�^����Ă���ꍇ
		unsigned index;
		for (index = 0; index < iterator->second->getEndIndex(); index++)
		{
			// �����Q�Ɛ悪���邩�ǂ���
			if (iterator->second->getObject(index)->reference_source_ != source) continue;

			break;
		}

		// �����Q�Ɛ悪�Ȃ��̂œo�^
		if (index != iterator->second->getEndIndex())
		{
			// �ǉ�
			iterator->second->AddToArray(new ReferenceData(source, pointer, destination));
		}
	}
}



void GameObjectReferenceManager::ReleaseSource(GameObjectBase* object)
{
	auto iterator = source_map_.find(object);

	// �o�^����Ă���ꍇ
	if (iterator != source_map_.end())
	{
		for (unsigned i = 0; i < iterator->second->getEndIndex(); i++)
		{
			// ���
			ReferenceData* temp = iterator->second->getObject(i);
			SafeRelease::Normal(&temp);
		}

		// �z��̉��
		SafeRelease::Normal(&iterator->second);

		// �Q�ƌ��}�b�v�������
		source_map_.erase(object);
	}
}



void GameObjectReferenceManager::ReleaseDestination(GameObjectBase* object)
{
	auto iterator = destination_map_.find(object);

	// �o�^����Ă���ꍇ
	if (iterator != destination_map_.end())
	{
		for (unsigned i = 0; i < iterator->second->getEndIndex(); i++)
		{
			// nullptr�̑}��
			iterator->second->getObject(i)->reference_pointer_ = nullptr;

			// ���
			ReferenceData* temp = iterator->second->getObject(i);
			SafeRelease::Normal(&temp);
		}

		// �z��̉��
		SafeRelease::Normal(&iterator->second);

		// �Q�ƌ��}�b�v�������
		destination_map_.erase(object);
	}
}