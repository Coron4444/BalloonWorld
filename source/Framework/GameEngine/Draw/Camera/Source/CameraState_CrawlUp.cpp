//================================================================================
//!	@file	 CameraState_CrawlUp.cpp
//!	@brief	 �������΂�J�����X�e�[�gClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../CameraState_CrawlUp.h"
#include "../../../Input/InputManager/InputManager.h"

#include <Tool/MeterToFrame.h>


//****************************************
// �萔��`
//****************************************
const float CameraState_CrawlUp::TRANSLATION_SPEED
= MeterToFrame::MeterPerSecondToMeterPerFlame(10.0f);
const float CameraState_CrawlUp::ROTATION_SPEED
= MeterToFrame::MeterPerSecondToMeterPerFlame(60.0f);
const float CameraState_CrawlUp::POSITION_Y = 8.0f;
const float CameraState_CrawlUp::GAZING_POINT_Y = POSITION_Y - 5.0f;



//****************************************
// �֐���`
//****************************************
void CameraState_CrawlUp::Init()
{
	getpCamera()->getpPositon()->y = POSITION_Y;
	getpCamera()->getpGazingPoint()->y = GAZING_POINT_Y;
}



void CameraState_CrawlUp::Uninit()
{
}



void CameraState_CrawlUp::Update()
{
	InputTranslation();
	InputRotation();
	InputRotationAroundGazingPoint();
}



void CameraState_CrawlUp::CalculationForward()
{
	Vector3D gazing_point_to_position = *getpCamera()->getpGazingPoint()
		- *getpCamera()->getpPositon();
	getpCamera()->getpAxis()->setForward(gazing_point_to_position);
}



void CameraState_CrawlUp::InputTranslation()
{
	Vector3D velocity;

	// �O
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_I))
	{
		velocity += *getpCamera()->getpAxis()->getpForawrd();
	}

	// ���
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_K))
	{
		velocity += -(*getpCamera()->getpAxis()->getpForawrd());
	}

	// �E
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_L))
	{
		velocity += *getpCamera()->getpAxis()->getpRight();
	}

	// ��
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_J))
	{
		velocity += -(*getpCamera()->getpAxis()->getpRight());
	}

	// ���x�Z�o
	velocity.y = 0.0f;
	velocity.ChangeAnyLength(TRANSLATION_SPEED);
	*getpCamera()->getpPositon() += velocity;
	*getpCamera()->getpGazingPoint() += velocity;
}



void CameraState_CrawlUp::InputRotation()
{
	// �E
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_O))
	{
		// �O�x�N�g�����Z�o����]
		Vector3D gazing_point_to_position = *getpCamera()->getpGazingPoint()
			- *getpCamera()->getpPositon();
		getpCamera()->getpAxis()->setForward(gazing_point_to_position);
		getpCamera()->getpAxis()->RotationAxisY(D3DXToRadian(ROTATION_SPEED));

		// �����_�̎Z�o
		float length = gazing_point_to_position.getLength();
		gazing_point_to_position = *getpCamera()->getpAxis()->getpForawrd();
		gazing_point_to_position.ChangeAnyLength(length);
		*getpCamera()->getpGazingPoint() = *getpCamera()->getpPositon()
			+ gazing_point_to_position;

		// �O�x�N�g�����Z�o
		CalculationForward();
	}

	// ��
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_U))
	{
		// �O�x�N�g�����Z�o����]
		Vector3D gazing_point_to_position = *getpCamera()->getpGazingPoint()
			- *getpCamera()->getpPositon();
		getpCamera()->getpAxis()->setForward(gazing_point_to_position);
		getpCamera()->getpAxis()->RotationAxisY(D3DXToRadian(-ROTATION_SPEED));

		// �����_�̎Z�o
		float length = gazing_point_to_position.getLength();
		gazing_point_to_position = *getpCamera()->getpAxis()->getpForawrd();
		gazing_point_to_position.ChangeAnyLength(length);
		*getpCamera()->getpGazingPoint() = *getpCamera()->getpPositon()
			+ gazing_point_to_position;

		// �O�x�N�g�����Z�o
		CalculationForward();
	}

	// ��
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_Y))
	{
		// �O�x�N�g�����Z�o����]
		Vector3D gazing_point_to_position = *getpCamera()->getpGazingPoint()
			- *getpCamera()->getpPositon();
		getpCamera()->getpAxis()->setForward(gazing_point_to_position);
		getpCamera()->getpAxis()->RotationAxisRight(D3DXToRadian(-ROTATION_SPEED));

		// �����_�̎Z�o
		float length = gazing_point_to_position.getLength();
		gazing_point_to_position = *getpCamera()->getpAxis()->getpForawrd();
		gazing_point_to_position.ChangeAnyLength(length);
		*getpCamera()->getpGazingPoint() = *getpCamera()->getpPositon()
			+ gazing_point_to_position;

		// �O�x�N�g�����Z�o
		CalculationForward();
	}

	// ��
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_H))
	{
		// �O�x�N�g�����Z�o����]
		Vector3D gazing_point_to_position = *getpCamera()->getpGazingPoint()
			- *getpCamera()->getpPositon();
		getpCamera()->getpAxis()->setForward(gazing_point_to_position);
		getpCamera()->getpAxis()->RotationAxisRight(D3DXToRadian(ROTATION_SPEED));

		// �����_�̎Z�o
		float length = gazing_point_to_position.getLength();
		gazing_point_to_position = *getpCamera()->getpAxis()->getpForawrd();
		gazing_point_to_position.ChangeAnyLength(length);
		*getpCamera()->getpGazingPoint() = *getpCamera()->getpPositon()
			+ gazing_point_to_position;

		// �O�x�N�g�����Z�o
		CalculationForward();
	}
}



void CameraState_CrawlUp::InputRotationAroundGazingPoint()
{
	// �E
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_M))
	{
		// �t�O�x�N�g�����Z�o����]
		Vector3D position_to_gazing_point = *getpCamera()->getpPositon() 
			- *getpCamera()->getpGazingPoint();
		getpCamera()->getpAxis()->setForward(position_to_gazing_point);
		getpCamera()->getpAxis()->RotationAxisY(D3DXToRadian(ROTATION_SPEED));

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
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_N))
	{
		// �t�O�x�N�g�����Z�o����]
		Vector3D position_to_gazing_point = *getpCamera()->getpPositon()
			- *getpCamera()->getpGazingPoint();
		getpCamera()->getpAxis()->setForward(position_to_gazing_point);
		getpCamera()->getpAxis()->RotationAxisY(D3DXToRadian(-ROTATION_SPEED));

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