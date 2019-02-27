//================================================================================
//!	@file	 CameraState_Normal.cpp
//!	@brief	 �m�[�}���J�����X�e�[�gClass
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../CameraState_Normal.h"



//****************************************
// �萔��`
//****************************************
const float CameraState_Normal::TRANSLATION_SPEED
= MeterToFrame::MeterPerSecondToMeterPerFlame(10.0f);
const float CameraState_Normal::ROTATION_SPEED
= MeterToFrame::MeterPerSecondToMeterPerFlame(60.0f);
const float CameraState_Normal::POSITION_Y = 8.0f;
const float CameraState_Normal::GAZING_POINT_Y = POSITION_Y - 5.0f;



//****************************************
// �֐���`
//****************************************
void CameraState_Normal::Init()
{
	getpCamera()->getpPosition()->y = POSITION_Y;
	getpCamera()->getpGazingPoint()->y = GAZING_POINT_Y;
}



void CameraState_Normal::Uninit()
{
}



void CameraState_Normal::Update()
{
	InputTranslation();
	InputRotation();
}



void CameraState_Normal::InputTranslation()
{
	Vector3D velocity;

	// �O
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_I))
	{
		velocity += *getpCamera()->getpForward();
	}

	// ���
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_K))
	{
		velocity += -(*getpCamera()->getpForward());
	}

	// �E
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_L))
	{
		velocity += *getpCamera()->getpRight();
	}

	// ��
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_J))
	{
		velocity += -(*getpCamera()->getpRight());
	}

	// ���x�Z�o
	velocity.ChangeAnyLength(TRANSLATION_SPEED);
	*getpCamera()->getpPosition() += velocity;
	*getpCamera()->getpGazingPoint() += velocity;
}



void CameraState_Normal::InputRotation()
{
	// �E
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_O))
	{
		// �O�x�N�g�����Z�o����]
		Vector3D gazing_point_to_position = *getpCamera()->getpGazingPoint()
			- *getpCamera()->getpPosition();
		gazing_point_to_position.RotationAxisY(D3DXToRadian(ROTATION_SPEED));

		// �����_�̎Z�o
		*getpCamera()->getpGazingPoint() = *getpCamera()->getpPosition()
			+ gazing_point_to_position;
	}

	// ��
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_U))
	{
		// �O�x�N�g�����Z�o����]
		Vector3D gazing_point_to_position = *getpCamera()->getpGazingPoint()
			- *getpCamera()->getpPosition();
		gazing_point_to_position.RotationAxisY(D3DXToRadian(-ROTATION_SPEED));

		// �����_�̎Z�o
		*getpCamera()->getpGazingPoint() = *getpCamera()->getpPosition()
			+ gazing_point_to_position;
	}

	// ��
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_Y))
	{
		// �O�x�N�g�����Z�o����]
		Vector3D gazing_point_to_position = *getpCamera()->getpGazingPoint()
			- *getpCamera()->getpPosition();
		gazing_point_to_position.RotationAxisAny(*getpCamera()->getpRight(),
												 D3DXToRadian(-ROTATION_SPEED));

		// �����_�̎Z�o
		*getpCamera()->getpGazingPoint() = *getpCamera()->getpPosition()
			+ gazing_point_to_position;
	}

	// ��
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_H))
	{
		// �O�x�N�g�����Z�o����]
		Vector3D gazing_point_to_position = *getpCamera()->getpGazingPoint()
			- *getpCamera()->getpPosition();
		gazing_point_to_position.RotationAxisAny(*getpCamera()->getpRight(),
												 D3DXToRadian(ROTATION_SPEED));

		// �����_�̎Z�o
		*getpCamera()->getpGazingPoint() = *getpCamera()->getpPosition()
			+ gazing_point_to_position;
	}
}