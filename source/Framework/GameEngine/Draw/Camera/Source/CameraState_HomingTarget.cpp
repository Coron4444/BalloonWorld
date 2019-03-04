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



//****************************************
// �萔��`
//****************************************
const Vector3D CameraState_HomingTarget::DEFAULT_LENGHT(0.0f, 20.0f, -10.0f);
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
	getpCamera()->getpGazingPoint()->y += lenght_.y + GAZING_POINT_Y;
	getpCamera()->CreateViewMatrix();
	CalculationPosition();
	CalculationGazingPoint();
}



void CameraState_HomingTarget::setLength(Vector3D value)
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

	getpCamera()->CreateViewMatrix();
	CalculationPosition();
	CalculationGazingPoint();
}



void CameraState_HomingTarget::CalculationPosition()
{
	*getpCamera()->getpPosition() = *target_object_->getpTransform()->getpPosition();
	Vector3D forward = -(*getpCamera()->getpForward());
	*getpCamera()->getpPosition() += *forward.ChangeAnyLength(lenght_.getLength());
}



void CameraState_HomingTarget::CalculationGazingPoint()
{
	Vector3D forward = *getpCamera()->getpForward();
	*getpCamera()->getpGazingPoint() = *getpCamera()->getpPosition() + *forward.ChangeAnyLength(lenght_.getLength());
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
		position_to_gazing_point.RotationAxisY(D3DXToRadian(-rotation_speed_));

		// ���W�̎Z�o
		*getpCamera()->getpPosition() = *getpCamera()->getpGazingPoint()
			+ position_to_gazing_point;
	}

	// �E
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_L) ||
		InputManager::getpInstance()->getpController()->getHoldRStick(0, Controller::Direction::RIGHT))
	{
		// �t�O�x�N�g�����Z�o����]
		Vector3D position_to_gazing_point = *getpCamera()->getpPosition()
			- *getpCamera()->getpGazingPoint();
		position_to_gazing_point.RotationAxisY(D3DXToRadian(rotation_speed_));

		// ���W�̎Z�o
		*getpCamera()->getpPosition() = *getpCamera()->getpGazingPoint()
			+ position_to_gazing_point;
	}

	// ��
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_I) ||
		InputManager::getpInstance()->getpController()->getHoldRStick(0, Controller::Direction::UP))
	{
		// �t�O�x�N�g�����Z�o����]
		Vector3D position_to_gazing_point = *getpCamera()->getpPosition()
			- *getpCamera()->getpGazingPoint();
		position_to_gazing_point.RotationAxisAny(*getpCamera()->getpRight(),
												 D3DXToRadian(rotation_speed_));

		// �ő�̊m�F
		Vector3D standard_vector = -position_to_gazing_point;
		standard_vector.y = 0.0f;
		standard_vector.ChangeNormalize();
		Vector3D forward_vector = -position_to_gazing_point;
		forward_vector.ChangeNormalize();
		float angle = Vector3D::CreateAngleDegree(&standard_vector, 
												  &forward_vector);
		if (angle >= MAX_ANGLE_OF_AXIS_RIGHT)
		{
			angle += -MAX_ANGLE_OF_AXIS_RIGHT;
			position_to_gazing_point.RotationAxisAny(*getpCamera()->getpRight(),
													 D3DXToRadian(-angle));
		}

		// ���W�̎Z�o
		*getpCamera()->getpPosition() = *getpCamera()->getpGazingPoint()
			+ position_to_gazing_point;
	}

	// ��
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_K) ||
		InputManager::getpInstance()->getpController()->getHoldRStick(0, Controller::Direction::DOWN))
	{
		// �t�O�x�N�g�����Z�o����]
		Vector3D position_to_gazing_point = *getpCamera()->getpPosition()
			- *getpCamera()->getpGazingPoint();
		position_to_gazing_point.RotationAxisAny(*getpCamera()->getpRight(),
												 D3DXToRadian(-rotation_speed_));

		// �ŏ��̊m�F
		Vector3D standard_vector = -position_to_gazing_point;
		standard_vector.y = 0.0f;
		standard_vector.ChangeNormalize();
		Vector3D forward_vector = -position_to_gazing_point;
		forward_vector.ChangeNormalize();
		float angle = Vector3D::CreateAngleDegree(&standard_vector,
												  &forward_vector);
		if (angle <= MIN_ANGLE_OF_AXIS_RIGHT)
		{
			angle = MIN_ANGLE_OF_AXIS_RIGHT - angle;
			position_to_gazing_point.RotationAxisAny(*getpCamera()->getpRight(),
													 D3DXToRadian(angle));
		}

		// ���W�̎Z�o
		*getpCamera()->getpPosition() = *getpCamera()->getpGazingPoint()
			+ position_to_gazing_point;
	}
}