//================================================================================
//!	@file	 Physics.cpp
//!	@brief	 ����Class
//! @details 
//!	@author  Kai Araki									@date 2018/08/19
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../Physics.h"
#include "../MeterToFrame.h"

#include <GameEngine/GameObject/GameObjectBase.h>



//****************************************
// �萔��`
//****************************************
const float Physics::VELOCITY_MIN = 0.0001f;



//****************************************
// �v���p�e�B��`
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
// �֐���`
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
	// �����x�𑬓x�ɒǉ�
	velocity_ += acceleration_;

	// ���C�͒ǉ�
	if (friction_ > 0.0f)
	{
		velocity_ *= friction_;
	}

	// �����͂�ǉ�
	if (bounciness_ > 0.0f)
	{
		velocity_ *= -bounciness_;
	}

	// ���x�̍ŏ��l�E�ő�l�`�F�b�N
	CheckVelocityMinMax();
}



void Physics::UpdatePosition()
{
	// ���x�����W�ɍ�p
	*game_object_->getpTransform()->getpPosition() += velocity_;

	// �s��̍X�V
	game_object_->getpTransform()->CreateWorldMatrix();
}



void Physics::AddGravity()
{
	// �d�͂���p�����邩�ǂ���
	if (!is_gravity_) return;

	// �d�͂̑傫���Z�o
	gravity_direction_.ChangeAnyLength(mass_ * gravity_acceleration_);

	// �I�u�W�F�N�g�̉����x�ɏd�͂�ǉ�
	acceleration_ += gravity_direction_;
}



void Physics::UpdateGround()
{
	// �n�ʏ�ɂ��邩�ǂ���
	if (is_on_tha_ground_)
	{
		// ���n����
		if (!is_landing_)
		{
			is_landing_ = true;

			velocity_.y = 0.0f;
		}

		// �����R�͂̒ǉ�
		acceleration_ += -gravity_direction_;
	}
	else
	{
		// ���n�t���O���
		if (!is_landing_) return;
		is_landing_ = false;
	}
}



void Physics::CheckVelocityMinMax()
{
	// �ŏ��l
	if (velocity_.getLength() <= VELOCITY_MIN)
	{
		velocity_.Reset();
	}

	// �ő�l
	if (velocity_.getLength() >= max_velocity_)
	{
		velocity_.ChangeAnyLength(max_velocity_);
	}
}