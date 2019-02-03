//================================================================================
//!	@file	 Physics.cpp
//!	@brief	 物理Class
//! @details 
//!	@author  Kai Araki									@date 2018/08/19
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../Physics.h"
#include "../MeterToFrame.h"

#include <GameEngine/GameObject/GameObjectBase.h>



//****************************************
// 定数定義
//****************************************
const float Physics::VELOCITY_MIN = 0.0001f;



//****************************************
// プロパティ定義
//****************************************
void Physics::setGameObject(GameObjectBase* value)
{
	game_object_ = value;
}



Vector3D* Physics::getpAcceleration()
{
	return &acceleration_;
}



Vector3D* Physics::getpVelocity()
{
	return &velocity_;
}



float Physics::getMaxVelocity()
{
	return max_velocity_;
}



void Physics::setMaxVelocity(float value)
{
	max_velocity_ = value;
}



float Physics::getMass()
{
	return mass_;
}



void Physics::setMass(float value)
{
	mass_ = value;
}



float Physics::getFriction()
{
	return friction_;
}



float Physics::getMyFriction()
{
	return my_friction_;
}



void Physics::setMyFriction(float value)
{
	my_friction_ = value;
}



float Physics::getBounciness()
{
	return bounciness_;
}



float Physics::getMyBounciness()
{
	return my_bounciness_;
}



void Physics::setMyBounciness(float value)
{
	my_bounciness_ = value;
}



bool Physics::getIsGravity()
{
	return is_gravity_;
}



void Physics::setIsGravity(float value)
{
	is_gravity_ = value;
}



void Physics::setOnTheGround()
{
	is_on_tha_ground_ = true;
}



//****************************************
// 関数定義
//****************************************
Physics::Physics()
	: game_object_(nullptr),
	max_velocity_(100.0f),
	mass_(1.0f),
	friction_(0.0f),
	my_friction_(1.0f),
	bounciness_(0.0f),
	my_bounciness_(1.0f),
	is_gravity_(true),
	gravity_acceleration_(MeterToFrame::MeterPerSecondSquaredToMeterPerFrameSquared(9.8f)),
	gravity_direction_(0.0f, -1.0f, 0.0f),
	is_on_tha_ground_(false),
	is_landing_(false)
{
}



void Physics::Update()
{
	UpdateAcceleration();
	UpdateVelocity();
	UpdatePosition();
	Reset();
}



void Physics::AddFriction(float friction)
{
	friction_ += friction;
}



void Physics::AddBounciness(float bounciness)
{
	bounciness_ += bounciness;
}



void Physics::Reset()
{
	friction_ = 0.0f;
	bounciness_ = 0.0f;
	is_on_tha_ground_ = false;
	acceleration_.Reset();
}



void Physics::UpdateAcceleration()
{
	AddGravity();
	UpdateGround();
}



void Physics::UpdateVelocity()
{
	// 加速度を速度に追加
	velocity_ += acceleration_;

	// 摩擦力追加
	if (friction_ > 0.0f)
	{
		velocity_ *= friction_;
	}

	// 反発力を追加
	if (bounciness_ > 0.0f)
	{
		velocity_ *= -bounciness_;
	}

	// 速度の最小値・最大値チェック
	CheckVelocityMinMax();
}



void Physics::UpdatePosition()
{
	// 速度を座標に作用
	*game_object_->getpTransform()->getpPosition() += velocity_;

	// 行列の更新
	game_object_->getpTransform()->CreateWorldMatrix();
}



void Physics::AddGravity()
{
	// 重力を作用させるかどうか
	if (!is_gravity_) return;

	// 重力の大きさ算出
	gravity_direction_.ChangeAnyLength(mass_ * gravity_acceleration_);

	// オブジェクトの加速度に重力を追加
	acceleration_ += gravity_direction_;
}



void Physics::UpdateGround()
{
	// 地面上にいるかどうか
	if (is_on_tha_ground_)
	{
		// 着地処理
		if (!is_landing_)
		{
			is_landing_ = true;

			velocity_.y = 0.0f;
		}

		// 垂直抗力の追加
		acceleration_ += -gravity_direction_;
	}
	else
	{
		// 着地フラグ解放
		if (!is_landing_) return;
		is_landing_ = false;
	}
}



void Physics::CheckVelocityMinMax()
{
	// 最小値
	if (velocity_.getLength() <= VELOCITY_MIN)
	{
		velocity_.Reset();
	}

	// 最大値
	if (velocity_.getLength() >= max_velocity_)
	{
		velocity_.ChangeAnyLength(max_velocity_);
	}
}