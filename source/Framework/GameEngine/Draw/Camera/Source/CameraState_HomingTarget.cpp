//================================================================================
//!	@file	 CameraState_HomingTarget.cpp
//!	@brief	 ターゲット追跡カメラステートClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../CameraState_HomingTarget.h"
#include "../../../GameObject/GameObjectBase.h"



//****************************************
// 定数定義
//****************************************
const Vector3D CameraState_HomingTarget::DEFAULT_LENGHT(0.0f, 20.0f, -10.0f);
const float CameraState_HomingTarget::GAZING_POINT_Y = -5.0f;
const float CameraState_HomingTarget::DEFAULT_ROTATION_SPEED
= MeterToFrame::MeterPerSecondToMeterPerFlame(90.0f);
const float CameraState_HomingTarget::MAX_ANGLE_OF_AXIS_RIGHT = 70.0f;
const float CameraState_HomingTarget::MIN_ANGLE_OF_AXIS_RIGHT = 20.0f;



//****************************************
// プロパティ定義
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
// 関数定義
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
	// 左
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_J) ||
		InputManager::getpInstance()->getpController()->getHoldRStick(0, Controller::Direction::LEFT))
	{
		// 逆前ベクトルを算出し回転
		Vector3D position_to_gazing_point = *getpCamera()->getpPosition()
			- *getpCamera()->getpGazingPoint();
		position_to_gazing_point.RotationAxisY(D3DXToRadian(-rotation_speed_));

		// 座標の算出
		*getpCamera()->getpPosition() = *getpCamera()->getpGazingPoint()
			+ position_to_gazing_point;
	}

	// 右
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_L) ||
		InputManager::getpInstance()->getpController()->getHoldRStick(0, Controller::Direction::RIGHT))
	{
		// 逆前ベクトルを算出し回転
		Vector3D position_to_gazing_point = *getpCamera()->getpPosition()
			- *getpCamera()->getpGazingPoint();
		position_to_gazing_point.RotationAxisY(D3DXToRadian(rotation_speed_));

		// 座標の算出
		*getpCamera()->getpPosition() = *getpCamera()->getpGazingPoint()
			+ position_to_gazing_point;
	}

	// 上
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_I) ||
		InputManager::getpInstance()->getpController()->getHoldRStick(0, Controller::Direction::UP))
	{
		// 逆前ベクトルを算出し回転
		Vector3D position_to_gazing_point = *getpCamera()->getpPosition()
			- *getpCamera()->getpGazingPoint();
		position_to_gazing_point.RotationAxisAny(*getpCamera()->getpRight(),
												 D3DXToRadian(rotation_speed_));

		// 最大の確認
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

		// 座標の算出
		*getpCamera()->getpPosition() = *getpCamera()->getpGazingPoint()
			+ position_to_gazing_point;
	}

	// 下
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_K) ||
		InputManager::getpInstance()->getpController()->getHoldRStick(0, Controller::Direction::DOWN))
	{
		// 逆前ベクトルを算出し回転
		Vector3D position_to_gazing_point = *getpCamera()->getpPosition()
			- *getpCamera()->getpGazingPoint();
		position_to_gazing_point.RotationAxisAny(*getpCamera()->getpRight(),
												 D3DXToRadian(-rotation_speed_));

		// 最小の確認
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

		// 座標の算出
		*getpCamera()->getpPosition() = *getpCamera()->getpGazingPoint()
			+ position_to_gazing_point;
	}
}