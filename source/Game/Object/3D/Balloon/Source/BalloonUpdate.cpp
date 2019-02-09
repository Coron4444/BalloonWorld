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

}



void BalloonUpdate::Update()
{
	balloon_->bullet_object_[0]->getpRigidBody()->activate();
	balloon_->bullet_object_[0]->AddAcceleration(Vec3(0.0f, 250.0f, 0.0f),
												 Vec3(0.0f, 1.0f, 0.0f));

	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_A))
	{
		balloon_->bullet_object_[0]->getpRigidBody()->activate();
		balloon_->bullet_object_[0]->AddAcceleration(Vec3(-150.0f, 0.0f, 0.0f));
	}

	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_D))
	{
		balloon_->bullet_object_[0]->getpRigidBody()->activate();
		balloon_->bullet_object_[0]->AddAcceleration(Vec3(50.0f, 0.0f, 0.0f));
	}

	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_W))
	{
		balloon_->bullet_object_[0]->getpRigidBody()->activate();
		balloon_->bullet_object_[0]->AddAcceleration(Vec3(0.0f, 50.0f, 0.0f),
													 Vec3(0.0f, 1.0f, 0.0f));
	}

	if (InputManager::getpInstance()->getpKeyboard()->getTrigger(DIK_S))
	{
		if (balloon_->bullet_constraint_[Balloon::MAX_BULLET_CONSTRAINT - 1] != nullptr)
		{
			balloon_->bullet_constraint_[Balloon::MAX_BULLET_CONSTRAINT - 1]->Release();
			balloon_->bullet_constraint_[Balloon::MAX_BULLET_CONSTRAINT - 1] = nullptr;
		}
		else if (balloon_->bullet_constraint_[Balloon::MAX_BULLET_CONSTRAINT - 2] != nullptr)
		{
			balloon_->bullet_constraint_[Balloon::MAX_BULLET_CONSTRAINT - 2]->Release();
			balloon_->bullet_constraint_[Balloon::MAX_BULLET_CONSTRAINT - 2] = nullptr;
		}
	}

	// 行列更新
	for (int i = 0; i < Balloon::MAX_BULLET_OBJECT; i++)
	{
		*balloon_->bullet_transform_[i].getpPosition() = balloon_->bullet_object_[i]->getPosition();
		if (i != 0)
		{
			Vector3D temp_vector(0.0f, -Balloon::OBB_EDGE_LENGTH_HALF.y, 0.0f);
			Quaternion temp_quaternion = balloon_->bullet_object_[i]->getQuaternion();
			temp_vector.RotationQuaternion(&temp_quaternion);
			*balloon_->bullet_transform_[i].getpPosition() += temp_vector;
		}
		balloon_->bullet_transform_[i].ResetAddQuaternion();
		balloon_->bullet_transform_[i].setAddQuaternion(balloon_
														->bullet_object_[i]
														->getQuaternion());
		balloon_->bullet_transform_[i].CreateAxisAndWorldMatrix();
	}
}