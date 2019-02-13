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
const Vec3 CameraState_HomingTarget::DEFAULT_LENGHT(0.0f, 13.0f, -15.0f);
const float CameraState_HomingTarget::GAZING_POINT_Y = -1.0f;
const float CameraState_HomingTarget::DEFAULT_ROTATION_SPEED
= MeterToFrame::MeterPerSecondToMeterPerFlame(70.0f);



//****************************************
// �v���p�e�B��`
//****************************************
void CameraState_HomingTarget::setTargetObject(GameObjectBase* value)
{
	target_object_ = value;
	*getpCamera()->getpPositon() = *target_object_->getpTransform()->getpPosition();
	*getpCamera()->getpPositon() += lenght_;
	*getpCamera()->getpGazingPoint() = *target_object_->getpTransform()->getpPosition();
	getpCamera()->getpGazingPoint()->y += GAZING_POINT_Y;
	CalculationForward();
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
	*getpCamera()->getpPositon() = *target_object_->getpTransform()->getpPosition();
	Vector3D forawrd = -(*getpCamera()->getpAxis()->getpForawrd());
	*getpCamera()->getpPositon() += *forawrd.ChangeAnyLength(lenght_.getLength());
}



void CameraState_HomingTarget::CalculationGazingPoint()
{
	Vector3D forawrd = *getpCamera()->getpAxis()->getpForawrd();
	*getpCamera()->getpGazingPoint() = *getpCamera()->getpPositon() + *forawrd.ChangeAnyLength(lenght_.getLength());
}



void CameraState_HomingTarget::CalculationForward()
{
	Vector3D gazing_point_to_position = *getpCamera()->getpGazingPoint()
		- *getpCamera()->getpPositon();
	getpCamera()->getpAxis()->setForward(gazing_point_to_position);
}



void CameraState_HomingTarget::InputRotationAroundGazingPoint()
{
	// �E
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_L))
	{
		// �t�O�x�N�g�����Z�o����]
		Vector3D position_to_gazing_point = *getpCamera()->getpPositon()
			- *getpCamera()->getpGazingPoint();
		getpCamera()->getpAxis()->setForward(position_to_gazing_point);
		getpCamera()->getpAxis()->RotationAxisY(D3DXToRadian(-rotation_speed_));

		// ���W�̎Z�o
		float length = position_to_gazing_point.getLength();
		position_to_gazing_point = *getpCamera()->getpAxis()->getpForawrd();
		position_to_gazing_point.ChangeAnyLength(length);
		*getpCamera()->getpPositon() = *getpCamera()->getpGazingPoint()
			+ position_to_gazing_point;

		// �O�x�N�g�����Z�o
		CalculationForward();
	}

	// ��
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_J))
	{
		// �t�O�x�N�g�����Z�o����]
		Vector3D position_to_gazing_point = *getpCamera()->getpPositon()
			- *getpCamera()->getpGazingPoint();
		getpCamera()->getpAxis()->setForward(position_to_gazing_point);
		getpCamera()->getpAxis()->RotationAxisY(D3DXToRadian(rotation_speed_));

		// ���W�̎Z�o
		float length = position_to_gazing_point.getLength();
		position_to_gazing_point = *getpCamera()->getpAxis()->getpForawrd();
		position_to_gazing_point.ChangeAnyLength(length);
		*getpCamera()->getpPositon() = *getpCamera()->getpGazingPoint()
			+ position_to_gazing_point;

		// �O�x�N�g�����Z�o
		CalculationForward();
	}

	// ��
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_I))
	{
		// �t�O�x�N�g�����Z�o����]
		Vector3D position_to_gazing_point = *getpCamera()->getpPositon()
			- *getpCamera()->getpGazingPoint();
		getpCamera()->getpAxis()->setForward(position_to_gazing_point);
		getpCamera()->getpAxis()->RotationAxisRight(D3DXToRadian(-rotation_speed_));

		// ���W�̎Z�o
		float length = position_to_gazing_point.getLength();
		position_to_gazing_point = *getpCamera()->getpAxis()->getpForawrd();
		position_to_gazing_point.ChangeAnyLength(length);
		*getpCamera()->getpPositon() = *getpCamera()->getpGazingPoint()
			+ position_to_gazing_point;

		// �O�x�N�g�����Z�o
		CalculationForward();
	}

	// ��
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_K))
	{
		// �t�O�x�N�g�����Z�o����]
		Vector3D position_to_gazing_point = *getpCamera()->getpPositon()
			- *getpCamera()->getpGazingPoint();
		getpCamera()->getpAxis()->setForward(position_to_gazing_point);
		getpCamera()->getpAxis()->RotationAxisRight(D3DXToRadian(rotation_speed_));

		// ���W�̎Z�o
		float length = position_to_gazing_point.getLength();
		position_to_gazing_point = *getpCamera()->getpAxis()->getpForawrd();
		position_to_gazing_point.ChangeAnyLength(length);
		*getpCamera()->getpPositon() = *getpCamera()->getpGazingPoint()
			+ position_to_gazing_point;

		// �O�x�N�g�����Z�o
		CalculationForward();
	}
}