//================================================================================
//!	@file	 GameObjectManager.cpp
//!	@brief	 �Q�[���I�u�W�F�N�g�}�l�[�W��Class
//! @details Singleton
//!	@author  Kai Araki									@date 2018/07/13
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../GameObjectManager.h"
#include "../../GameObjectBase.h"

#include <Tool/SafeRelease.h>



//****************************************
// static�ϐ���`
//****************************************
GameObjectManager* GameObjectManager::instance_ = nullptr;



//****************************************
// static�v���p�e�B��`
//****************************************
GameObjectManager* GameObjectManager::getpInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new GameObjectManager();
	}
	return instance_;
}



//****************************************
// static�֐���`
//****************************************
void GameObjectManager::ReleaseInstance()
{
	SafeRelease::Normal(&instance_);
}



//****************************************
// �v���p�e�B��`
//****************************************
UpdateManager* GameObjectManager::getpUpdateManager()
{
	return &update_manager_;
}



DrawManager* GameObjectManager::getpDrawManager()
{
	return &draw_manager_;
}



CollisionManager* GameObjectManager::getpCollisionManager()
{
	return &collision_manager_;
}



//****************************************
// �֐���`
//****************************************
GameObjectManager::GameObjectManager()
{
}



void GameObjectManager::Init()
{
	// �e��}�l�[�W���̏�����
	update_manager_.Init();
	draw_manager_.Init();
	collision_manager_.Init();
}



void GameObjectManager::Uninit()
{
	// �Q�[���I�u�W�F�N�g�̉��
	Release();

	// �e��}�l�[�W���̏I������
	collision_manager_.Uninit();
	draw_manager_.Uninit();
	update_manager_.Uninit();
}



void GameObjectManager::UninitWhenChangeScene()
{
	// �Q�[���I�u�W�F�N�g�̉��
	Release();

	// �e��}�l�[�W���̃V�[���ύX���̏I������
	collision_manager_.UninitWhenChangeScene();
	draw_manager_.UninitWhenChangeScene();
	update_manager_.UninitWhenChangeScene();
}



void GameObjectManager::Update()
{
	// �ǉ��҂��z��̒��g��ǉ�
	AddContentsOfAwaitAddArray();

	// ����҂��z��̒��g�����
	ReleaseContentsOfAwaitReleaseArray();

	// �X�V
	update_manager_.Update();
	collision_manager_.Update();
	draw_manager_.Update();
}



void GameObjectManager::Draw()
{
	draw_manager_.Draw();
}



void GameObjectManager::Reset()
{
	// �o�^����Ă���I�u�W�F�N�g��S�ă��Z�b�g
	for (unsigned i = 0; i < all_game_object_.getEndIndex(); i++)
	{
		all_game_object_.getObject(i)->Reset();
	}
}



void GameObjectManager::AddGameObjectBaseToArray(GameObjectBase* game_object)
{
	await_add_.AddToArray(game_object);
}



void GameObjectManager::ReleaseGameObjectBaseFromArray(GameObjectBase* game_object)
{
	// �Q�[���I�u�W�F�N�g�I������
	game_object->Uninit();

	// �R���|�[�l���g���}�l�[�W��������
	ReleaseComponentFromManager(game_object);

	// ����҂��z��ɒǉ�
	await_release_.AddToArray(game_object);
}



void GameObjectManager::AddContentsOfAwaitAddArray()
{
	// �ǉ��҂������邩�ǂ���
	if (await_add_.getEndIndex() <= 0) return;

	// �ǉ�
	for (unsigned i = 0; i < await_add_.getEndIndex(); i++)
	{
		// �S�̔z��֒ǉ�
		all_game_object_.AddToArray(await_add_.getObject(i));

		// �R���|�[�l���g���}�l�[�W���ɃZ�b�g
		AddComponentToManager(await_add_.getObject(i));
	}

	// �ǉ��҂��z������Z�b�g
	await_add_.Reset();
}



void GameObjectManager::ReleaseContentsOfAwaitReleaseArray()
{
	// ����҂������邩�ǂ���
	if (await_release_.getEndIndex() <= 0) return;

	// ����ƃ\�[�g
	for (unsigned i = 0; i < await_release_.getEndIndex(); i++)
	{
		// �S�̔z�񂩂�̏���
		all_game_object_.DeleteFromArrayAndSort(await_release_.getObject(i));

		// �I�u�W�F�N�g�̏���
		GameObjectBase* temp = await_release_.getObject(i);
		SafeRelease::Normal(&temp);
	}

	// ����҂��z������Z�b�g
	await_release_.Reset();
}



void GameObjectManager::AddComponentToManager(GameObjectBase* game_object)
{
	if (game_object->getpUpdate() != nullptr)
	{
		update_manager_.AddUpdateBaseToArray(game_object->getpUpdate());
	}

	if (game_object->getpDraw() != nullptr)
	{
		draw_manager_.AddDrawBaseToArray(game_object->getpDraw());
	}

	if (game_object->getpCollision() != nullptr)
	{
		collision_manager_.AddCollisionBaseToArray(game_object->getpCollision());
	}
}



void GameObjectManager::ReleaseComponentFromManager(GameObjectBase* game_object)
{
	if (game_object->getpUpdate() != nullptr)
	{
		update_manager_.ReleaseUpdateBaseFromArray(game_object->getpUpdate());
	}

	if (game_object->getpDraw() != nullptr)
	{
		draw_manager_.ReleaseDrawBaseFromArray(game_object->getpDraw());
	}

	if (game_object->getpCollision() != nullptr)
	{
		collision_manager_.ReleaseCollisionBaseFromArray(game_object->getpCollision());
	}
}



void GameObjectManager::Release()
{
	// ����҂��z��̒��g�����
	ReleaseContentsOfAwaitReleaseArray();

	// �c��̃I�u�W�F�N�g��S�ĉ���҂��ɓo�^
	for (unsigned i = 0; i < await_add_.getEndIndex(); i++)
	{
		ReleaseGameObjectBaseFromArray(await_add_.getObject(i));
	}

	for (unsigned i = 0; i < all_game_object_.getEndIndex(); i++)
	{
		ReleaseGameObjectBaseFromArray(all_game_object_.getObject(i));
	}

	// ����҂��z��̒��g�����
	ReleaseContentsOfAwaitReleaseArray();
	
	// �I�u�W�F�N�g�z������Z�b�g
	all_game_object_.Reset();
}