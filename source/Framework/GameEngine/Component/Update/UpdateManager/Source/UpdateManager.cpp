//================================================================================
//!	@file	 UpdateManager.cpp
//!	@brief	 �X�V�}�l�[�W���[Class
//! @details 
//!	@author  Kai Araki									@date 2019/01/19
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "UpdateManager.h"

#include <Component/Update/UpdateBase/UpdateBase.h>
#include <GameObjectBase/GameObjectBase.h>
#include <SafeRelease/SafeRelease.h>



//****************************************
// �֐���`
//****************************************
void UpdateManager::Init()
{
}



void UpdateManager::Uninit()
{
	// �ǉ��҂��z��̃��Z�b�g
	await_add_.ResetArray();

	// ����҂��z��̃��Z�b�g
	await_release_.ResetArray();

	// �S�X�V�z��̃��Z�b�g
	all_update_.ResetArray();
}



void UpdateManager::UninitWhenChangeScene()
{
	// �ǉ��҂��z��̃��Z�b�g
	await_add_.ResetArray();

	// ����҂��z��̃��Z�b�g
	await_release_.ResetArray();

	// �S�X�V�z��̃��Z�b�g
	all_update_.ResetArray();
}



void UpdateManager::Update()
{
	// �ǉ��҂��z��̒��g��ǉ�
	AddContentsOfAwaitAddArray();

	// ����҂��z��̒��g�����
	ReleaseContentsOfAwaitReleaseArray();

	// �X�V
	for (unsigned i = 0; i < all_update_.GetEndPointer(); i++)
	{
		if (all_update_.GetArrayObject(i) == nullptr) continue;
		all_update_.GetArrayObject(i)->Update();
	}

	// ��X�V
	for (unsigned i = 0; i < all_update_.GetEndPointer(); i++)
	{
		if (all_update_.GetArrayObject(i) == nullptr) continue;
		all_update_.GetArrayObject(i)->LateUpdate();
	}

	// �����X�V
	for (unsigned i = 0; i < all_update_.GetEndPointer(); i++)
	{
		if (all_update_.GetArrayObject(i)->getpGameObject()->GetPhysics() == nullptr) continue;
		all_update_.GetArrayObject(i)->getpGameObject()->GetPhysics()->Update();
	}


	// �f�o�b�O
#ifdef _DEBUG
	for (unsigned i = 0; i < all_update_.GetEndPointer(); i++)
	{
		if (all_update_.GetArrayObject(i) == nullptr) continue;
		all_update_.GetArrayObject(i)->DebugDisplay();
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
		ReleaseUpdateBaseFromArray(game_object->GetUpdate());

		// �Â��X�V���N���X�̏���
		UpdateBase* temp = game_object->GetUpdate();
		SafeRelease::Normal(&temp);

		// nullptr�̑��
		game_object->SetUpdate(new_update);
	}
	else
	{
		// �z��̏㏑��
		all_update_.OverwriteArray(game_object->GetUpdate(), new_update);

		// �Â��X�V���N���X�̏���
		UpdateBase* temp = game_object->GetUpdate();
		SafeRelease::Normal(&temp);

		// �V�K�X�V���N���X�̏�����
		game_object->SetUpdate(new_update);
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
	if(await_add_.GetEndPointer() <= 0) return;

	// �ǉ�
	for (unsigned i = 0; i < await_add_.GetEndPointer(); i++)
	{
		all_update_.AddToArray(await_add_.GetArrayObject(i));
	}

	// �ǉ��҂��z������Z�b�g
	await_add_.ResetArray();
}



void UpdateManager::ReleaseContentsOfAwaitReleaseArray()
{
	// ����҂������邩�ǂ���
	if(await_release_.GetEndPointer() <= 0) return;

	// ����ƃ\�[�g
	for (unsigned i = 0; i < await_release_.GetEndPointer(); i++)
	{
		all_update_.DeleteFromArrayAndSortArray(await_release_.GetArrayObject(i));
	}

	// ����҂��z������Z�b�g
	await_release_.ResetArray();
}