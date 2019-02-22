//================================================================================
//!	@file	 CameraState_HomingTarget.cpp
//!	@brief	 �^�[�Q�b�g�ǐՃJ�����X�e�[�gClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../CameraState_HomingTarget.h"
#include "../../../GameObject/GameObjectBase.h"
#include "../../../Input/InputManager/InputManager.h"

#include <Tool/Vector3D.h>
#include <Tool/MeterToFrame.h>



//****************************************
// �萔��`
//****************************************
const Vec3 CameraState_HomingTarget::DEFAULT_LENGHT(0.0f, 20.0f, -10.0f);
const float CameraState_HomingTarget::GAZING_POINT_Y = -5.0f;
const float CameraState_HomingTarget::DEFAULT_ROTATION_SPEED
= MeterToFrame::MeterPerSecondToMeterPerFlame(90.0f);
const float CameraState_HomingTarget::MAX_ANGLE_OF_AXIS_RIGHT = 70.0f;
const float CameraState_HomingTarget::MIN_ANGLE_OF_AXIS_RIGHT = 20.0f;



//****************************************
// �v���p�e�B��`
//****************************************
void CameraState_HomingTarget::setTargetObject(GameObjectBase* value)
{
	target_object_ = value;
	*getpCamera()->getpPosition() = *target_object_->getpTransform()->getpPosition();
	*getpCamera()->getpPosition() += lenght_;
	*getpCamera()->getpGazingPoint() = *target_object_->getpTransform()->getpPosition();
	getpCamera()->getpGazingPoint()->y += DEFAULT_LENGHT.y + GAZING_POINT_Y;
	CalculationForward();
	Update();
}



void CameraState_HomingTarget::setLength(Vec3 value)
{
	lenght_ = value;
}



void CameraState_HomingTarget::setRotationSpeed(float value)
{
	rotation_speed_ = value;
}



//****************************************
// �֐���`
//****************************************
void CameraState_HomingTarget::Init()
{
	lenght_ = DEFAULT_LENGHT;
	rotation_speed_ = DEFAULT_ROTATION_SPEED;
}



void CameraState_HomingTarget::Uninit()
{
}



void CameraState_HomingTarget::Update()
{
	if (target_object_ == nullptr) return;

	InputRotationAroundGazingPoint();

	CalculationPosition();
	CalculationGazingPoint();
	CalculationForward();
}



void CameraState_HomingTarget::CalculationPosition()
{
	*getpCamera()->getpPosition() = *target_object_->getpTransform()->getpPosition();
	Vector3D Forward = -(*getpCamera()->getpAxis()->getpForward());
	*getpCamera()->getpPosition() += *Forward.ChangeAnyLength(lenght_.getLength());
}



void CameraState_HomingTarget::CalculationGazingPoint()
{
	Vector3D Forward = *getpCamera()->getpAxis()->getpForward();
	*getpCamera()->getpGazingPoint() = *getpCamera()->getpPosition() + *Forward.ChangeAnyLength(lenght_.getLength());
}



void CameraState_HomingTarget::CalculationForward()
{
	Vector3D gazing_point_to_position = *getpCamera()->getpGazingPoint()
		- *getpCamera()->getpPosition();
	getpCamera()->getpAxis()->setForward(gazing_point_to_position);
}



void CameraState_HomingTarget::InputRotationAroundGazingPoint()
{
	// ��
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_J) ||
		InputManager::getpInstance()->getpController()->getHoldRStick(0, Controller::Direction::LEFT))
	{
		// �t�O�x�N�g�����Z�o����]
		Vector3D position_to_gazing_point = *getpCamera()->getpPosition()
			- *getpCamera()->getpGazingPoint();
		getpCamera()->getpAxis()->setForward(position_to_gazing_point);
		getpCamera()->getpAxis()->RotationAxisY(D3DXToRadian(-rotation_speed_));

		// ���W�̎Z�o
		float length = position_to_gazing_point.getLength();
		position_to_gazing_point = *getpCamera()->getpAxis()->getpForward();
		position_to_gazing_point.ChangeAnyLength(length);
		*getpCamera()->getpPosition() = *getpCamera()->getpGazingPoint()
			+ position_to_gazing_point;

		// �O�x�N�g�����Z�o
		CalculationForward();
	}

	// �E
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_L) ||
		InputManager::getpInstance()->getpController()->getHoldRStick(0, Controller::Direction::RIGHT))
	{
		// �t�O�x�N�g�����Z�o����]
		Vector3D position_to_gazing_point = *getpCamera()->getpPosition()
			- *getpCamera()->getpGazingPoint();
		getpCamera()->getpAxis()->setForward(position_to_gazing_point);
		getpCamera()->getpAxis()->RotationAxisY(D3DXToRadian(rotation_speed_));

		// ���W�̎Z�o
		float length = position_to_gazing_point.getLength();
		position_to_gazing_point = *getpCamera()->getpAxis()->getpForward();
		position_to_gazing_point.ChangeAnyLength(length);
		*getpCamera()->getpPosition() = *getpCamera()->getpGazingPoint()
			+ position_to_gazing_point;

		// �O�x�N�g�����Z�o
		CalculationForward();
	}

	// ��
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_I) ||
		InputManager::getpInstance()->getpController()->getHoldRStick(0, Controller::Direction::UP))
	{
		// �t�O�x�N�g�����Z�o����]
		Vector3D position_to_gazing_point = *getpCamera()->getpPosition()
			- *getpCamera()->getpGazingPoint();
		getpCamera()->getpAxis()->setForward(position_to_gazing_point);
		getpCamera()->getpAxis()->RotationAxisRight(D3DXToRadian(-rotation_speed_));

		// �ő�̊m�F
		Vector3D standard_vector = *getpCamera()->getpAxis()->getpForward();
		standard_vector.y = 0.0f;
		standard_vector.ChangeNormalize();
		float angle = Vector3D::CreateAngleDegree(&standard_vector, getpCamera()->getpAxis()->getpForward());
		if (angle >= MAX_ANGLE_OF_AXIS_RIGHT)
		{
			angle += -MAX_ANGLE_OF_AXIS_RIGHT;
			getpCamera()->getpAxis()->RotationAxisRight(D3DXToRadian(angle));
		}

		// ���W�̎Z�o
		float length = position_to_gazing_point.getLength();
		position_to_gazing_point = *getpCamera()->getpAxis()->getpForward();
		position_to_gazing_point.ChangeAnyLength(length);
		*getpCamera()->getpPosition() = *getpCamera()->getpGazingPoint()
			+ position_to_gazing_point;

		// �O�x�N�g�����Z�o
		CalculationForward();
	}

	// ��
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_K) ||
		InputManager::getpInstance()->getpController()->getHoldRStick(0, Controller::Direction::DOWN))
	{
		// �t�O�x�N�g�����Z�o����]
		Vector3D position_to_gazing_point = *getpCamera()->getpPosition()
			- *getpCamera()->getpGazingPoint();
		getpCamera()->getpAxis()->setForward(position_to_gazing_point);
		getpCamera()->getpAxis()->RotationAxisRight(D3DXToRadian(rotation_speed_));

		// �ŏ��̊m�F
		Vector3D standard_vector = *getpCamera()->getpAxis()->getpForward();
		standard_vector.y = 0.0f;
		standard_vector.ChangeNormalize();
		float angle = Vector3D::CreateAngleDegree(&standard_vector, getpCamera()->getpAxis()->getpForward());
		if (angle <= MIN_ANGLE_OF_AXIS_RIGHT)
		{
			angle = MIN_ANGLE_OF_AXIS_RIGHT - angle;
			getpCamera()->getpAxis()->RotationAxisRight(D3DXToRadian(-angle));
		}

		// ���W�̎Z�o
		float length = position_to_gazing_point.getLength();
		position_to_gazing_point = *getpCamera()->getpAxis()->getpForward();
		position_to_gazing_point.ChangeAnyLength(length);
		*getpCamera()->getpPosition() = *getpCamera()->getpGazingPoint()
			+ position_to_gazing_point;

		// �O�x�N�g�����Z�o
		CalculationForward();
	}
}