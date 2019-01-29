//================================================================================
//!	@file	 GameObjectBase.cpp
//!	@brief	 �Q�[���I�u�W�F�N�gBaseClass
//! @details 
//!	@author  Kai Araki									@date 2018/03/22
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../GameObjectBase.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../../Update/UpdateManager/UpdateManager.h"
#include "../../Draw/DrawManager/DrawManager.h"
#include "../../Collision/CollisionManager/CollisionManager.h"

#include <Tool/SafeRelease.h>



//****************************************
// �v���p�e�B��`
//****************************************
Transform* GameObjectBase::getpTransform()
{
	return &transform_;
}



Physics* GameObjectBase::getpPhysics()
{
	return physics_;
}



void GameObjectBase::setAllComponent(UpdateBase* update, DrawBase* draw,
									 CollisionBase* collision)
{
	setUpdate(update);
	setDraw(draw);
	setCollision(collision);
}



UpdateBase* GameObjectBase::getpUpdate()
{
	return update_;
}



void GameObjectBase::setUpdate(UpdateBase* value)
{
	update_ = value;
}



DrawBase* GameObjectBase::getpDraw()
{
	return draw_;
}



void GameObjectBase::setDraw(DrawBase* value)
{
	draw_ = value;
}



CollisionBase* GameObjectBase::getpCollision()
{
	return collision_;
}



void GameObjectBase::setCollision(CollisionBase* value)
{
	collision_ = value;
}



//****************************************
// �֐���`
//****************************************
GameObjectBase::GameObjectBase(bool is_registration)
	: is_registration_(is_registration),
	physics_(nullptr),
	update_(nullptr),
	draw_(nullptr),
	collision_(nullptr)
{
}



GameObjectBase::~GameObjectBase()
{
	SafeRelease::Normal(&update_);
	SafeRelease::Normal(&draw_);
	SafeRelease::Normal(&collision_);
	SafeRelease::Normal(&physics_);
}



void GameObjectBase::Uninit()
{
	UninitComponent();
}



void GameObjectBase::CreatePhysics()
{
	if (physics_ != nullptr) return;
	physics_ = new Physics();
	physics_->setGameObject(this);
}



void GameObjectBase::Init(UpdateBase* update, DrawBase* draw, CollisionBase* collision)
{
	// �`�拤�ʃf�[�^�ݒ�
	AddDrawCommonData(draw);

	// �R���|�[�l���g������
	setAllComponent(update, draw, collision);
	InitComponent();

	// �I�u�W�F�N�g�}�l�[�W���[�ɓo�^
	if (!is_registration_) return;
	GameObjectManager::getpInstance()->AddGameObjectBaseToArray(this);
}



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



void GameObjectBase::AddDrawCommonData(DrawBase* draw)
{
	if (draw == nullptr) return;
	*draw->getpDrawCommonData() = *GameObjectManager::getpInstance()
		->getpDrawManager()->getpDrawCommonData();
}