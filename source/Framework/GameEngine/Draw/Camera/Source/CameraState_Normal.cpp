//================================================================================
//!	@file	 CameraState_Normal.cpp
//!	@brief	 ノーマルカメラステートClass
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../CameraState_Normal.h"
#include "../../../Input/InputManager/InputManager.h"

#include <Tool/Vector3D.h>
#include <Tool/MeterToFrame.h>



//****************************************
// 定数定義
//****************************************
const float CameraState_Normal::TRANSLATION_SPEED
= MeterToFrame::MeterPerSecondToMeterPerFlame(10.0f);
const float CameraState_Normal::ROTATION_SPEED
= MeterToFrame::MeterPerSecondToMeterPerFlame(60.0f);
const float CameraState_Normal::POSITION_Y = 8.0f;
const float CameraState_Normal::GAZING_POINT_Y = POSITION_Y - 5.0f;



//****************************************
// 関数定義
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



void CameraState_Normal::CalculationForward()
{
	Vector3D gazing_point_to_position = *getpCamera()->getpGazingPoint()
		- *getpCamera()->getpPosition();
	getpCamera()->getpAxis()->setForward(gazing_point_to_position);
}



void CameraState_Normal::InputTranslation()
{
	Vector3D velocity;

	// 前
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_I))
	{
		velocity += *getpCamera()->getpAxis()->getpForward();
	}

	// 後ろ
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_K))
	{
		velocity += -(*getpCamera()->getpAxis()->getpForward());
	}

	// 右
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_L))
	{
		velocity += *getpCamera()->getpAxis()->getpRight();
	}

	// 左
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_J))
	{
		velocity += -(*getpCamera()->getpAxis()->getpRight());
	}

	// 速度算出
	velocity.ChangeAnyLength(TRANSLATION_SPEED);
	*getpCamera()->getpPosition() += velocity;
	*getpCamera()->getpGazingPoint() += velocity;
}



void CameraState_Normal::InputRotation()
{
	// 右
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_O))
	{
		// 前ベクトルを算出し回転
		Vector3D gazing_point_to_position = *getpCamera()->getpGazingPoint()
			- *getpCamera()->getpPosition();
		getpCamera()->getpAxis()->setForward(gazing_point_to_position);
		getpCamera()->getpAxis()->RotationAxisY(D3DXToRadian(ROTATION_SPEED));

		// 注視点の算出
		float length = gazing_point_to_position.getLength();
		gazing_point_to_position = *getpCamera()->getpAxis()->getpForward();
		gazing_point_to_position.ChangeAnyLength(length);
		*getpCamera()->getpGazingPoint() = *getpCamera()->getpPosition()
			+ gazing_point_to_position;

		// 前ベクトルを算出
		CalculationForward();
	}

	// 左
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_U))
	{
		// 前ベクトルを算出し回転
		Vector3D gazing_point_to_position = *getpCamera()->getpGazingPoint()
			- *getpCamera()->getpPosition();
		getpCamera()->getpAxis()->setForward(gazing_point_to_position);
		getpCamera()->getpAxis()->RotationAxisY(D3DXToRadian(-ROTATION_SPEED));

		// 注視点の算出
		float length = gazing_point_to_position.getLength();
		gazing_point_to_position = *getpCamera()->getpAxis()->getpForward();
		gazing_point_to_position.ChangeAnyLength(length);
		*getpCamera()->getpGazingPoint() = *getpCamera()->getpPosition()
			+ gazing_point_to_position;

		// 前ベクトルを算出
		CalculationForward();
	}

	// 上
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_Y))
	{
		// 前ベクトルを算出し回転
		Vector3D gazing_point_to_position = *getpCamera()->getpGazingPoint()
			- *getpCamera()->getpPosition();
		getpCamera()->getpAxis()->setForward(gazing_point_to_position);
		getpCamera()->getpAxis()->RotationAxisRight(D3DXToRadian(-ROTATION_SPEED));

		// 注視点の算出
		float length = gazing_point_to_position.getLength();
		gazing_point_to_position = *getpCamera()->getpAxis()->getpForward();
		gazing_point_to_position.ChangeAnyLength(length);
		*getpCamera()->getpGazingPoint() = *getpCamera()->getpPosition()
			+ gazing_point_to_position;

		// 前ベクトルを算出
		CalculationForward();
	}

	// 下
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_H))
	{
		// 前ベクトルを算出し回転
		Vector3D gazing_point_to_position = *getpCamera()->getpGazingPoint()
			- *getpCamera()->getpPosition();
		getpCamera()->getpAxis()->setForward(gazing_point_to_position);
		getpCamera()->getpAxis()->RotationAxisRight(D3DXToRadian(ROTATION_SPEED));

		// 注視点の算出
		float length = gazing_point_to_position.getLength();
		gazing_point_to_position = *getpCamera()->getpAxis()->getpForward();
		gazing_point_to_position.ChangeAnyLength(length);
		*getpCamera()->getpGazingPoint() = *getpCamera()->getpPosition()
			+ gazing_point_to_position;

		// 前ベクトルを算出
		CalculationForward();
	}
}