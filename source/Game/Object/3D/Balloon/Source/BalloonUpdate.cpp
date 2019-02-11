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
#include <GameEngine/Collision/BulletPhysics/BulletPhysicsManager/BulletPhysicsManager.h>
#include <Tool/MeterToFrame.h>
#include <Tool/Random.h>


//****************************************
// �萔��`
//****************************************
const float BalloonUpdate::RISING_SPEED = MeterToFrame::MeterPerSecondSquaredToMeterPerFrameSquared(1000000.0f);



//****************************************
// �֐���`
//****************************************
void BalloonUpdate::Init()
{
	// �_�E���L���X�g
	balloon_ = (Balloon*)getpGameObject();
}



void BalloonUpdate::Update()
{
	// �㏸
	balloon_->getpObject(balloon_->getAllObjectNum() - 1)
		->getpRigidBody()->activate();
	balloon_->getpObject(balloon_->getAllObjectNum() - 1)
		->AddAcceleration(Vec3(0.0f, RISING_SPEED, 0.0f),
						  Vec3(0.0f, 1.0f, 0.0f));
}