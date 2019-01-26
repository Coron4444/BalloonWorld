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

#include <GameObjectBase/GameObjectBase.h>



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



void Physics::AddFriction(float friction)
{
	bounciness_ += bounciness;
}



//--------------------------------------------------------------------------------
//
// [ ���Z�b�g�֐� ]
//
//--------------------------------------------------------------------------------

void Physics::Reset()
{
	// �n�ʔ���
	is_on_tha_ground_ = false;

	// ���C��
	friction_ = 0.0f;

	// ������
	bounciness_ = 0.0f;

	// �����x
	acceleration_.ResetVector();
}



//--------------------------------------------------------------------------------
//
// [ �����x�X�V�֐� ]
//
//--------------------------------------------------------------------------------

void Physics::UpdateAcceleration()
{
	// �d�͂̒ǉ�
	SetGravity();

	// �n�ʏ�̏���
	SetGround();
}



//--------------------------------------------------------------------------------
//
// [ ���x�X�V�֐� ]
//
//--------------------------------------------------------------------------------

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



//--------------------------------------------------------------------------------
//
// [ ���W�X�V�֐� ]
//
//--------------------------------------------------------------------------------

void Physics::UpdatePosition()
{
	// ���x�����W�ɍ�p
	*game_object_->GetTransform()->GetPosition() += velocity_;

	// �s��̍X�V(�r���{�[�h�ɂ��Ή�)
	game_object_->GetTransform()->UpdateWorldMatrixISRT();
}



//--------------------------------------------------------------------------------
//
// [ �d�͒ǉ��֐� ]
//
//--------------------------------------------------------------------------------

void Physics::SetGravity()
{
	// �d�͂���p�����邩�ǂ���
	if (!is_gravity_) return;

	// �d�͂̑傫���Z�o
	gravity_direction_.AnyLengthVector(mass_ * gravity_acceleration_);

	// �I�u�W�F�N�g�̉����x�ɏd�͂�ǉ�
	acceleration_ += gravity_direction_;
}



//--------------------------------------------------------------------------------
//
// [ �n�ʂ̏����֐� ]
//
//--------------------------------------------------------------------------------

void Physics::SetGround()
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



//--------------------------------------------------------------------------------
//
// [ ���x�̍ŏ��l�E�ő�l�`�F�b�N�֐� ]
//
//--------------------------------------------------------------------------------

void Physics::CheckVelocityMinMax()
{
	// �ŏ��l
	if (velocity_.GetLength() <= VELOCITY_MIN)
	{
		velocity_.ResetVector();
	}

	// �ő�l
	if (velocity_.GetLength() >= max_velocity_)
	{
		velocity_.AnyLengthVector(max_velocity_);
	}
}