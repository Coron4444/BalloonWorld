//================================================================================
//!	@file	 CameraState_CrawlUp.cpp
//!	@brief	 這いつくばりカメラステートClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../CameraState_CrawlUp.h"
#include "../../../Input/InputManager/InputManager.h"

#include <Tool/MeterToFrame.h>


//****************************************
// 定数定義
//****************************************
const float CameraState_CrawlUp::TRANSLATION_SPEED
= MeterToFrame::MeterPerSecondToMeterPerFlame(10.0f);
const float CameraState_CrawlUp::ROTATION_SPEED
= MeterToFrame::MeterPerSecondToMeterPerFlame(60.0f);
const float CameraState_CrawlUp::POSITION_Y = 8.0f;
const float CameraState_CrawlUp::GAZING_POINT_Y = POSITION_Y - 5.0f;



//****************************************
// 関数定義
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

	// 前
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_I))
	{
		velocity += *getpCamera()->getpAxis()->getpForawrd();
	}

	// 後ろ
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_K))
	{
		velocity += -(*getpCamera()->getpAxis()->getpForawrd());
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
	velocity.y = 0.0f;
	velocity.ChangeAnyLength(TRANSLATION_SPEED);
	*getpCamera()->getpPositon() += velocity;
	*getpCamera()->getpGazingPoint() += velocity;
}



void CameraState_CrawlUp::InputRotation()
{
	// 右
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_O))
	{
		// 前ベクトルを算出し回転
		Vector3D gazing_point_to_position = *getpCamera()->getpGazingPoint()
			- *getpCamera()->getpPositon();
		getpCamera()->getpAxis()->setForward(gazing_point_to_position);
		getpCamera()->getpAxis()->RotationAxisY(D3DXToRadian(ROTATION_SPEED));

		// 注視点の算出
		float length = gazing_point_to_position.getLength();
		gazing_point_to_position = *getpCamera()->getpAxis()->getpForawrd();
		gazing_point_to_position.ChangeAnyLength(length);
		*getpCamera()->getpGazingPoint() = *getpCamera()->getpPositon()
			+ gazing_point_to_position;

		// 前ベクトルを算出
		CalculationForward();
	}

	// 左
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_U))
	{
		// 前ベクトルを算出し回転
		Vector3D gazing_point_to_position = *getpCamera()->getpGazingPoint()
			- *getpCamera()->getpPositon();
		getpCamera()->getpAxis()->setForward(gazing_point_to_position);
		getpCamera()->getpAxis()->RotationAxisY(D3DXToRadian(-ROTATION_SPEED));

		// 注視点の算出
		float length = gazing_point_to_position.getLength();
		gazing_point_to_position = *getpCamera()->getpAxis()->getpForawrd();
		gazing_point_to_position.ChangeAnyLength(length);
		*getpCamera()->getpGazingPoint() = *getpCamera()->getpPositon()
			+ gazing_point_to_position;

		// 前ベクトルを算出
		CalculationForward();
	}

	// 上
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_Y))
	{
		// 前ベクトルを算出し回転
		Vector3D gazing_point_to_position = *getpCamera()->getpGazingPoint()
			- *getpCamera()->getpPositon();
		getpCamera()->getpAxis()->setForward(gazing_point_to_position);
		getpCamera()->getpAxis()->RotationAxisRight(D3DXToRadian(-ROTATION_SPEED));

		// 注視点の算出
		float length = gazing_point_to_position.getLength();
		gazing_point_to_position = *getpCamera()->getpAxis()->getpForawrd();
		gazing_point_to_position.ChangeAnyLength(length);
		*getpCamera()->getpGazingPoint() = *getpCamera()->getpPositon()
			+ gazing_point_to_position;

		// 前ベクトルを算出
		CalculationForward();
	}

	// 下
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_H))
	{
		// 前ベクトルを算出し回転
		Vector3D gazing_point_to_position = *getpCamera()->getpGazingPoint()
			- *getpCamera()->getpPositon();
		getpCamera()->getpAxis()->setForward(gazing_point_to_position);
		getpCamera()->getpAxis()->RotationAxisRight(D3DXToRadian(ROTATION_SPEED));

		// 注視点の算出
		float length = gazing_point_to_position.getLength();
		gazing_point_to_position = *getpCamera()->getpAxis()->getpForawrd();
		gazing_point_to_position.ChangeAnyLength(length);
		*getpCamera()->getpGazingPoint() = *getpCamera()->getpPositon()
			+ gazing_point_to_position;

		// 前ベクトルを算出
		CalculationForward();
	}
}



void CameraState_CrawlUp::InputRotationAroundGazingPoint()
{
	// 右
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_M))
	{
		// 逆前ベクトルを算出し回転
		Vector3D position_to_gazing_point = *getpCamera()->getpPositon() 
			- *getpCamera()->getpGazingPoint();
		getpCamera()->getpAxis()->setForward(position_to_gazing_point);
		getpCamera()->getpAxis()->RotationAxisY(D3DXToRadian(ROTATION_SPEED));

		// 座標の算出
		float length = position_to_gazing_point.getLength();
		position_to_gazing_point = *getpCamera()->getpAxis()->getpForawrd();
		position_to_gazing_point.ChangeAnyLength(length);
		*getpCamera()->getpPositon() = *getpCamera()->getpGazingPoint()
			+ position_to_gazing_point;

		// 前ベクトルを算出
		CalculationForward();
	}

	// 左
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_N))
	{
		// 逆前ベクトルを算出し回転
		Vector3D position_to_gazing_point = *getpCamera()->getpPositon()
			- *getpCamera()->getpGazingPoint();
		getpCamera()->getpAxis()->setForward(position_to_gazing_point);
		getpCamera()->getpAxis()->RotationAxisY(D3DXToRadian(-ROTATION_SPEED));

		// 座標の算出
		float length = position_to_gazing_point.getLength();
		position_to_gazing_point = *getpCamera()->getpAxis()->getpForawrd();
		position_to_gazing_point.ChangeAnyLength(length);
		*getpCamera()->getpPositon() = *getpCamera()->getpGazingPoint()
			+ position_to_gazing_point;

		// 前ベクトルを算出
		CalculationForward();
	}
}