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

#include <Object/3D/Player/PlayerFactory.h>
#include <Object/3D/Balloon/BalloonGroupFactory.h>



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
	GameObjectBase::Init(nullptr, nullptr, nullptr);
}



void StageManager::Uninit()
{
	GameObjectBase::Uninit();
}



void StageManager::CreateStage()
{
	// ���D�Q�쐬
	BalloonGroupFactory balloon_group_factory;
	balloon_group_ = balloon_group_factory.Create(5);

	// �v���C���[
	PlayerFactory player_factory;
	player_ = player_factory.Create();
	player_->setBalloonGroup(balloon_group_);
}