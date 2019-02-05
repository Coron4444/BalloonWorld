//================================================================================
//!	@file	 BalloonUpdate.cpp
//!	@brief	 ���D�X�VClass
//! @details 
//!	@author  Kai Araki									@date 2019/02/05
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../BalloonUpdate.h"
#include "../Balloon.h"

#include <GameEngine/Input/InputManager/InputManager.h>
#include <GameEngine/GameObject/GameObjectManager/GameObjectManager.h>
#include <Tool/MeterToFrame.h>
#include <Resource/Effekseer/EffekseerManager/EffekseerManager.h>



//****************************************
// �萔��`
//****************************************
const float BalloonUpdate::SPEED = MeterToFrame::MeterPerSecondSquaredToMeterPerFrameSquared(50.0f);



//****************************************
// �֐���`
//****************************************
void BalloonUpdate::Init()
{
	// �_�E���L���X�g
	balloon_ = (Balloon*)getpGameObject();

	// ���̐ݒ�
	//balloon_->CreatePhysics();
	//balloon_->getpPhysics()->setMaxVelocity(MeterToFrame::MeterPerSecondToMeterPerFlame(300.0f));
	//balloon_->getpPhysics()->setMass(8.0f);
	//balloon_->getpPhysics()->setMyFriction(1.0f);
	//balloon_->getpPhysics()->setMyBounciness(1.0f);
}



void BalloonUpdate::Update()
{
	
}