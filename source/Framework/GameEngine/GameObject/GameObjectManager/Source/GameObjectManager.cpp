//================================================================================
//
//    �Q�[���I�u�W�F�N�g�̃}�l�[�W���N���X(static)
//    Author : Araki Kai                                �쐬�� : 2018/07/13
//
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "GameObjectManager.h"
#include "../GameObjectBase/GameObjectBase.h"
#include <SafeRelease/SafeRelease.h>



//****************************************
// �ÓI�����o�ϐ���`
//****************************************
LimitedPointerArray<GameObjectBase*, GameObjectManager::ARRAY_NUM> GameObjectManager::all_game_object_;
LimitedPointerArray<GameObjectBase*, GameObjectManager::ARRAY_NUM> GameObjectManager::await_add_;
LimitedPointerArray<GameObjectBase*, GameObjectManager::ARRAY_NUM> GameObjectManager::await_release_;

GameObjectReferenceManager GameObjectManager::reference_manager_;
UpdateManager GameObjectManager::update_manager_;
DrawManager GameObjectManager::draw_manager_;
CollisionManager GameObjectManager::collision_manager_;



//****************************************
// �ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +�������֐�
//--------------------------------------------------
void GameObjectManager::Init()
{
	// �e��}�l�[�W���̏�����
	update_manager_.Init();
	draw_manager_.Init();
	collision_manager_.Init();
}



//--------------------------------------------------
// +�I���֐�
//--------------------------------------------------
void GameObjectManager::Uninit()
{
	// �S�Q�[���I�u�W�F�N�g�̉��
	AllRelease();

	// �e��}�l�[�W���̏I������
	collision_manager_.Uninit();
	draw_manager_.Uninit();
	update_manager_.Uninit();

}



//--------------------------------------------------
// +�V�[���ύX���̏I���֐�
//--------------------------------------------------
void GameObjectManager::UninitWhenChangeScene()
{
	// �S�Q�[���I�u�W�F�N�g�̉��
	AllRelease();

	// �e��}�l�[�W���̃V�[���ύX���̏I������
	collision_manager_.UninitWhenChangeScene();
	draw_manager_.UninitWhenChangeScene();
	update_manager_.UninitWhenChangeScene();
	
}



//--------------------------------------------------
// +�X�V�֐�
//--------------------------------------------------
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



//--------------------------------------------------
// +�`��֐�
//--------------------------------------------------
void GameObjectManager::Draw()
{
	draw_manager_.Draw();
}



//--------------------------------------------------
// +�S�Q�[���I�u�W�F�N�g���Z�b�g�֐�
//--------------------------------------------------
void GameObjectManager::AllReset()
{
	// �o�^����Ă���I�u�W�F�N�g��S�ă��Z�b�g
	for (unsigned i = 0; i < all_game_object_.GetEndPointer(); i++)
	{
		all_game_object_.GetArrayObject(i)->Reset();
	}
}



//--------------------------------------------------
// +�Q�[���I�u�W�F�N�g���N���X�̒ǉ��֐�
//--------------------------------------------------
void GameObjectManager::AddGameObjectBaseToArray(GameObjectBase* game_object)
{
	await_add_.AddToArray(game_object);
}



//--------------------------------------------------
// +�Q�[���I�u�W�F�N�g���N���X�̉���֐�
//--------------------------------------------------
void GameObjectManager::ReleaseGameObjectBaseFromArray(GameObjectBase* game_object)
{
	// �Q�[���I�u�W�F�N�g�I������
	game_object->Uninit();

	// �R���|�[�l���g���}�l�[�W��������
	ReleaseComponentFromManager(game_object);

	// �Q�ƃf�[�^���
	reference_manager_.ReleaseReference(game_object);

	// ����҂��z��ɒǉ�
	await_release_.AddToArray(game_object);
}



//--------------------------------------------------
// -�ǉ��҂��z��̒��g��ǉ��֐�
//--------------------------------------------------
void GameObjectManager::AddContentsOfAwaitAddArray()
{
	// �ǉ��҂������邩�ǂ���
	if (await_add_.GetEndPointer() <= 0) return;

	// �ǉ�
	for (unsigned i = 0; i < await_add_.GetEndPointer(); i++)
	{
		// �S�̔z��֒ǉ�
		all_game_object_.AddToArray(await_add_.GetArrayObject(i));

		// �R���|�[�l���g���}�l�[�W���ɃZ�b�g
		SetComponentToManager(await_add_.GetArrayObject(i));
	}

	// �ǉ��҂��z������Z�b�g
	await_add_.ResetArray();
}



//--------------------------------------------------
// -����҂��z��̒��g������֐�
//--------------------------------------------------
void GameObjectManager::ReleaseContentsOfAwaitReleaseArray()
{
	// ����҂������邩�ǂ���
	if (await_release_.GetEndPointer() <= 0) return;

	// ����ƃ\�[�g
	for (unsigned i = 0; i < await_release_.GetEndPointer(); i++)
	{
		// �S�̔z�񂩂�̏���
		all_game_object_.DeleteFromArrayAndSortArray(await_release_.GetArrayObject(i));

		// �I�u�W�F�N�g�̏���
		GameObjectBase* temp = await_release_.GetArrayObject(i);
		SafeRelease::Normal(&temp);
	}

	// ����҂��z������Z�b�g
	await_release_.ResetArray();
}



//--------------------------------------------------
// -�R���|�[�l���g���}�l�[�W���[�֐ݒ�֐�
//--------------------------------------------------
void GameObjectManager::SetComponentToManager(GameObjectBase* game_object)
{
	if (game_object->GetUpdate() != nullptr)
	{
		update_manager_.AddUpdateBaseToArray(game_object->GetUpdate());
	}

	if (game_object->GetDraw() != nullptr)
	{
		draw_manager_.AddDrawBaseToArray(game_object->GetDraw());
	}

	if (game_object->GetCollision() != nullptr)
	{
		collision_manager_.AddCollisionBaseToArray(game_object->GetCollision());
	}
}



//--------------------------------------------------
// -�R���|�[�l���g���}�l�[�W���[�������֐�
//--------------------------------------------------
void GameObjectManager::ReleaseComponentFromManager(GameObjectBase* game_object)
{
	if (game_object->GetUpdate() != nullptr)
	{
		update_manager_.ReleaseUpdateBaseFromArray(game_object->GetUpdate());
	}

	if (game_object->GetDraw() != nullptr)
	{
		draw_manager_.ReleaseDrawBaseFromArray(game_object->GetDraw());
	}

	if (game_object->GetCollision() != nullptr)
	{
		collision_manager_.ReleaseCollisionBaseFromArray(game_object->GetCollision());
	}
}



//--------------------------------------------------
// -�S�Q�[���I�u�W�F�N�g�̉���֐�
//--------------------------------------------------
void GameObjectManager::AllRelease()
{
	// �Q�ƃf�[�^��S�ď���
	reference_manager_.AllReleaseReference();

	// ����҂��z��̒��g�����
	ReleaseContentsOfAwaitReleaseArray();

	// �c��̃I�u�W�F�N�g��S�ĉ���҂��ɓo�^
	for (unsigned i = 0; i < await_add_.GetEndPointer(); i++)
	{
		ReleaseGameObjectBaseFromArray(await_add_.GetArrayObject(i));
	}

	for (unsigned i = 0; i < all_game_object_.GetEndPointer(); i++)
	{
		ReleaseGameObjectBaseFromArray(all_game_object_.GetArrayObject(i));
	}

	// ����҂��z��̒��g�����
	ReleaseContentsOfAwaitReleaseArray();
	
	// �I�u�W�F�N�g�z������Z�b�g
	all_game_object_.ResetArray();
}