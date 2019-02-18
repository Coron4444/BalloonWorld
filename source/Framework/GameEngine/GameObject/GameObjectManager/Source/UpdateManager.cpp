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
#include "../../GameObjectBase.h"



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
	all_object_.Reset();
}



void UpdateManager::UninitWhenChangeScene()
{
	// �ǉ��҂��z��̃��Z�b�g
	await_add_.Reset();

	// ����҂��z��̃��Z�b�g
	await_release_.Reset();

	// �S�X�V�z��̃��Z�b�g
	all_object_.Reset();
}



void UpdateManager::Update()
{
	// �ǉ��҂��z��̒��g��ǉ�
	AddContentsOfAwaitAddArray();

	// ����҂��z��̒��g�����
	ReleaseContentsOfAwaitReleaseArray();

	// �����X�V
	for (unsigned i = 0; i < all_object_.getEndIndex(); i++)
	{
		if (all_object_.getObject(i)->getpPhysics() == nullptr) continue;
		all_object_.getObject(i)->getpPhysics()->Update();
	}

	// �X�V
	for (unsigned i = 0; i < all_object_.getEndIndex(); i++)
	{
		if (all_object_.getObject(i) == nullptr) continue;
		all_object_.getObject(i)->Update();
	}

	// ��X�V
	for (unsigned i = 0; i < all_object_.getEndIndex(); i++)
	{
		if (all_object_.getObject(i) == nullptr) continue;
		all_object_.getObject(i)->LateUpdate();
	}

	// �f�o�b�O
#ifdef _DEBUG
	for (unsigned i = 0; i < all_object_.getEndIndex(); i++)
	{
		if (all_object_.getObject(i) == nullptr) continue;
		all_object_.getObject(i)->DebugDisplay();
	}
#endif
}



void UpdateManager::AddGameObjectBase(GameObjectBase* update)
{
	// �ǉ��҂��z��ɒǉ�
	await_add_.AddToArray(update);
}



void UpdateManager::ReleaseGameObjectBase(GameObjectBase* update)
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
		all_object_.AddToArray(await_add_.getObject(i));
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
		all_object_.DeleteFromArrayAndSort(await_release_.getObject(i));
	}

	// ����҂��z������Z�b�g
	await_release_.Reset();
}