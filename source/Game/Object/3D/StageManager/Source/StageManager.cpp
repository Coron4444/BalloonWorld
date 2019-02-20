//================================================================================
//!	@file	 StageManager.h
//!	@brief	 �X�e�[�W�}�l�[�W��Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/13
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../StageManager.h"

#include <GameEngine/Input/InputManager/InputManager.h>

#include <Object/3D/Balloon/BalloonGroupFactory.h>
#include <Object/3D/Player/PlayerFactory.h>
#include <Object/3D/Needle/NeedleFactory.h>
#include <Object/3D/StartBlock/StartBlockFactory.h>
#include <Object/3D/Scaffold/ScaffoldFactory.h>



//****************************************
// �v���p�e�B��`
//****************************************
void StageManager::setPlayerCamera(Camera* value)
{
	player_->setCamera(value);
}



Player* StageManager::getpPlayer()
{
	return player_;
}



//****************************************
// �֐���`
//****************************************
void StageManager::Init()
{
	// ���N���X�̏�����
	//setIsUpdate(false);
	GameObjectBase::Init(nullptr, nullptr);
}



void StageManager::Uninit()
{
	UninitComponent();
}



void StageManager::Update()
{
}



void StageManager::CreateStage()
{
	// ���D�Q�쐬
	BalloonGroupFactory balloon_group_factory;
	balloon_group_ = balloon_group_factory.Create(5, Vec3(0.0f, 313.0f, 0.0f));

	// �v���C���[
	PlayerFactory player_factory;
	player_ = player_factory.Create();
	player_->setPosition(Vec3(0.0f, 303.0f, 0.0f));
	player_->setBalloonGroup(balloon_group_);

	// �X�^�[�g�u���b�N
	StartBlockFactory start_block_factory;
	start_block_ = start_block_factory.Create();
	start_block_->setPosition(Vec3(0.0f, 300.0f, 0.0f));

	// �X�^�[�g�u���b�N
	start_block_ = start_block_factory.Create();
	start_block_->setPosition(Vec3(0.0f, 300.0f, 0.0f));

	// ����
	ScaffoldFactory scaffold_factory;
	scaffold_ = scaffold_factory.Create();
	scaffold_->setPosition(Vec3(30.0f, 250.0f, 0.0f));
	scaffold_->setScale(Vec3(3.0f, 50.0f, 3.0f));
	scaffold_->setColor(XColor4(1.0f, 0.0f, 1.0f, 1.0f));
	
	// ��
	NeedleFactory needle_factory;
	needle_ = needle_factory.Create(new NeedleState_Loop());
	needle_->setPosition(Vec3(-40.0f, 250.0f, -30.0f));
	needle_->setScale(5.0f);

}