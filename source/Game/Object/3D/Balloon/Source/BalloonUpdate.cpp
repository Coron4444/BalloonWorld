//================================================================================
//!	@file	 BalloonUpdate.cpp
//!	@brief	 風船更新Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/05
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../BalloonUpdate.h"
#include "../Balloon.h"

#include <GameEngine/Input/InputManager/InputManager.h>
#include <GameEngine/Collision/BulletPhysics/BulletPhysicsManager/BulletPhysicsManager.h>
#include <Tool/MeterToFrame.h>
#include <Tool/Random.h>


//****************************************
// 定数定義
//****************************************
const float BalloonUpdate::SPEED = MeterToFrame::MeterPerSecondSquaredToMeterPerFrameSquared(50.0f);



//****************************************
// 関数定義
//****************************************
void BalloonUpdate::Init()
{
	// ダウンキャスト
	balloon_ = (Balloon*)getpGameObject();
	acc_z = Random::getpInstance()->getFloat(-1.0f, 1.0f);
}



void BalloonUpdate::Update()
{
	balloon_->getpObject(balloon_->getAllObjectNum() - 1)->getpRigidBody()->activate();
	balloon_->getpObject(balloon_->getAllObjectNum() - 1)->AddAcceleration(Vec3(0.0f, 250.0f, 0.0f),
																		   Vec3(0.0f, 1.0f, 0.0f));

	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_A))
	{
		Vector3D acceleration(-1.0f, 0.0f, acc_z);
		acceleration.ChangeAnyLength(150.0f);
		balloon_->getpObject(balloon_->getAllObjectNum() - 1)->getpRigidBody()->activate();
		balloon_->getpObject(balloon_->getAllObjectNum() - 1)->AddAcceleration(acceleration);
	}

	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_D))
	{
		Vector3D acceleration(1.0f, 0.0f, acc_z);
		acceleration.ChangeAnyLength(100.0f);
		balloon_->getpObject(balloon_->getAllObjectNum() - 1)->getpRigidBody()->activate();
		balloon_->getpObject(balloon_->getAllObjectNum() - 1)->AddAcceleration(acceleration);
	}

	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_W))
	{
		balloon_->getpObject(balloon_->getAllObjectNum() - 1)->getpRigidBody()->activate();
		balloon_->getpObject(balloon_->getAllObjectNum() - 1)->AddAcceleration(Vec3(0.0f, 50.0f, 0.0f),
																			   Vec3(0.0f, 1.0f, 0.0f));
	}

	if (InputManager::getpInstance()->getpKeyboard()->getTrigger(DIK_S))
	{
		if (balloon_->getpObjectConstraint(0) != nullptr)
		{
			balloon_->ReleaseConstraint(0);
		}
		else if (balloon_->getpObjectConstraint(1) != nullptr)
		{
			balloon_->ReleaseConstraint(1);
		}
	}

	// 行列更新
	for (int i = 0; i < balloon_->getAllObjectNum(); i++)
	{
		*balloon_->getpObjectTransform(i)->getpPosition() = balloon_->getpObject(i)->getPosition();
		if (i != balloon_->getAllObjectNum() - 1)
		{
			Vector3D temp_vector(0.0f, -Balloon::OBB_EDGE_LENGTH_HALF.y, 0.0f);
			Quaternion temp_quaternion = balloon_->getpObject(i)->getQuaternion();
			temp_vector.RotationQuaternion(&temp_quaternion);
			*balloon_->getpObjectTransform(i)->getpPosition() += temp_vector;
		}
		balloon_->getpObjectTransform(i)->ResetAddQuaternion();
		balloon_->getpObjectTransform(i)->setAddQuaternion(balloon_->getpObject(i)
														   ->getQuaternion());
		balloon_->getpObjectTransform(i)->CreateAxisAndWorldMatrix();
	}
}