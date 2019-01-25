//================================================================================
//
//    �Q�[���I�u�W�F�N�g���N���X
//    Author : Araki Kai                                �쐬�� : 2018/03/22
//
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "GameObjectBase.h"

#include <GameObjectManager/GameObjectManager.h>
#include <ComponentManager/UpdateManager/UpdateManager.h>
#include <ComponentManager/DrawManager/DrawManager.h>
#include <ComponentManager/CollisionManager/CollisionManager.h>



//****************************************
// ��ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +�R���X�g���N�^
//--------------------------------------------------
GameObjectBase::GameObjectBase(bool is_registration)
	: is_registration_(is_registration),
	physics_(nullptr),
	update_(nullptr),
	draw_(nullptr),
	collision_(nullptr)
{
}



//--------------------------------------------------
// +�f�X�g���N�^
//--------------------------------------------------
GameObjectBase::~GameObjectBase()
{
	// �e��J��
	SafeRelease::Normal(&update_);
	SafeRelease::Normal(&draw_);
	SafeRelease::Normal(&collision_);
	SafeRelease::Normal(&physics_);
}



//--------------------------------------------------
// +�I���֐�
//--------------------------------------------------
void GameObjectBase::Uninit()
{
	// �R���|�[�l���g�̏I������
	UninitComponent();
}



//--------------------------------------------------
// +���̐����֐�
//--------------------------------------------------
void GameObjectBase::CreatePhysics()
{
	if (physics_ != nullptr) return;
	physics_ = new Physics(this);
}



//--------------------------------------------------
// #���N���X�������֐�
//--------------------------------------------------
void GameObjectBase::Init(UpdateBase* update, DrawBase* draw, CollisionBase* collision)
{
	// �R���|�[�l���g���Z�b�g
	SetAllComponent(update, draw, collision);

	// �R���|�[�l���g�̏�����
	InitComponent();

	// �I�u�W�F�N�g�}�l�[�W���[�ɓo�^
	if (!is_registration_) return;
	GameObjectManager::AddGameObjectBaseToArray(this);
}



//--------------------------------------------------
// -�R���|�[�l���g�������֐�
//--------------------------------------------------
void GameObjectBase::InitComponent()
{
	if (update_ != nullptr)
	{
		update_->setGameObject(this);
		update_->Init();
	}

	if (draw_ != nullptr)
	{
		draw_->setGameObject(this);
		draw_->Init();
	}

	if (collision_ != nullptr)
	{
		collision_->setGameObject(this);
		collision_->Init();
	}
}



//--------------------------------------------------
// -�R���|�[�l���g�I���֐�
//--------------------------------------------------
void GameObjectBase::UninitComponent()
{
	if (update_ != nullptr)
	{
		update_->Uninit();
	}

	if (draw_ != nullptr)
	{
		draw_->Uninit();
	}

	if (collision_ != nullptr)
	{
		collision_->Uninit();
	}
}