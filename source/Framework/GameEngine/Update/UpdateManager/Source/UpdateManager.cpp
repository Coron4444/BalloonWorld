//================================================================================
//!	@file	 UpdateManager.cpp
//!	@brief	 �X�V�}�l�[�W���[Class
//! @details 
//!	@author  Kai Araki									@date 2019/01/19
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../UpdateManager.h"
#include "../../UpdateBase.h"
#include "../../../GameObject/GameObjectBase.h"

#include <Tool/SafeRelease.h>



//****************************************
// �֐���`
//****************************************
void UpdateManager::Init()
{
}



void UpdateManager::Uninit()
{
	// �ǉ��҂��z��̃��Z�b�g
	await_add_.Reset();

	// ����҂��z��̃��Z�b�g
	await_release_.Reset();

	// �S�X�V�z��̃��Z�b�g
	all_update_.Reset();
}



void UpdateManager::UninitWhenChangeScene()
{
	// �ǉ��҂��z��̃��Z�b�g
	await_add_.Reset();

	// ����҂��z��̃��Z�b�g
	await_release_.Reset();

	// �S�X�V�z��̃��Z�b�g
	all_update_.Reset();
}



void UpdateManager::Update()
{
	// �ǉ��҂��z��̒��g��ǉ�
	AddContentsOfAwaitAddArray();

	// ����҂��z��̒��g�����
	ReleaseContentsOfAwaitReleaseArray();

	// �X�V
	for (unsigned i = 0; i < all_update_.getEndIndex(); i++)
	{
		if (all_update_.getObject(i) == nullptr) continue;
		all_update_.getObject(i)->Update();
	}

	// ��X�V
	for (unsigned i = 0; i < all_update_.getEndIndex(); i++)
	{
		if (all_update_.getObject(i) == nullptr) continue;
		all_update_.getObject(i)->LateUpdate();
	}

	// �����X�V
	for (unsigned i = 0; i < all_update_.getEndIndex(); i++)
	{
		if (all_update_.getObject(i)->getpGameObject()->getpPhysics() == nullptr) continue;
		all_update_.getObject(i)->getpGameObject()->getpPhysics()->Update();
	}


	// �f�o�b�O
#ifdef _DEBUG
	for (unsigned i = 0; i < all_update_.getEndIndex(); i++)
	{
		if (all_update_.getObject(i) == nullptr) continue;
		all_update_.getObject(i)->DebugDisplay();
	}
#endif
}



void UpdateManager::AddUpdateBaseToArray(UpdateBase* update)
{
	// �ǉ��҂��z��ɒǉ�
	await_add_.AddToArray(update);
}



void UpdateManager::OverwriteArrayUpdateBase(GameObjectBase* game_object,
											 UpdateBase* new_update)
{
	// �V�K��nullptr�̏ꍇ
	if (new_update == nullptr)
	{
		// �Â��X�V���N���X�̉��
		ReleaseUpdateBaseFromArray(game_object->getpUpdate());

		// �Â��X�V���N���X�̏���
		UpdateBase* temp = game_object->getpUpdate();
		SafeRelease::Normal(&temp);

		// nullptr�̑��
		game_object->setUpdate(new_update);
	}
	else
	{
		// �z��̏㏑��
		all_update_.OverwriteArray(game_object->getpUpdate(), new_update);

		// �Â��X�V���N���X�̏���
		UpdateBase* temp = game_object->getpUpdate();
		SafeRelease::Normal(&temp);

		// �V�K�X�V���N���X�̏�����
		game_object->setUpdate(new_update);
		*new_update->getpGameObject() = *game_object;
		new_update->Init();
	}
}



void UpdateManager::ReleaseUpdateBaseFromArray(UpdateBase* update)
{
	// ����҂��z��ɒǉ�
	await_release_.AddToArray(update);
}



void UpdateManager::AddContentsOfAwaitAddArray()
{
	// �ǉ��҂������邩�ǂ���
	if(await_add_.getEndIndex() <= 0) return;

	// �ǉ�
	for (unsigned i = 0; i < await_add_.getEndIndex(); i++)
	{
		all_update_.AddToArray(await_add_.getObject(i));
	}

	// �ǉ��҂��z������Z�b�g
	await_add_.Reset();
}



void UpdateManager::ReleaseContentsOfAwaitReleaseArray()
{
	// ����҂������邩�ǂ���
	if(await_release_.getEndIndex() <= 0) return;

	// ����ƃ\�[�g
	for (unsigned i = 0; i < await_release_.getEndIndex(); i++)
	{
		all_update_.DeleteFromArrayAndSort(await_release_.getObject(i));
	}

	// ����҂��z������Z�b�g
	await_release_.Reset();
}