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
	getpCamera()->getpPosition()->y = POSITION_Y;
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



void CameraState_CrawlUp::InputTranslation()
{
	Vector3D velocity;
	
	// 前
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_I))
	{
		velocity += *getpCamera()->getpForward();
	}
	
	// 後ろ
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_K))
	{
		velocity += -(*getpCamera()->getpForward());
	}
	
	// 右
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_L))
	{
		velocity += *getpCamera()->getpRight();
	}
	
	// 左
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_J))
	{
		velocity += -(*getpCamera()->getpRight());
	}
	
	// 速度算出
	velocity.y = 0.0f;
	velocity.ChangeAnyLength(TRANSLATION_SPEED);
	*getpCamera()->getpPosition() += velocity;
	*getpCamera()->getpGazingPoint() += velocity;
}



void CameraState_CrawlUp::InputRotation()
{
	// 右
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_O))
	{
		// 前ベクトルを算出し回転
		Vector3D gazing_point_to_position = *getpCamera()->getpGazingPoint()
			- *getpCamera()->getpPosition();
		gazing_point_to_position.RotationAxisY(D3DXToRadian(ROTATION_SPEED));
	
		// 注視点の算出
		*getpCamera()->getpGazingPoint() = *getpCamera()->getpPosition()
			+ gazing_point_to_position;
	}
	
	// 左
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_U))
	{
		// 前ベクトルを算出し回転
		Vector3D gazing_point_to_position = *getpCamera()->getpGazingPoint()
			- *getpCamera()->getpPosition();
		gazing_point_to_position.RotationAxisY(D3DXToRadian(-ROTATION_SPEED));
	
		// 注視点の算出
		*getpCamera()->getpGazingPoint() = *getpCamera()->getpPosition()
			+ gazing_point_to_position;
	}
	
	// 上
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_Y))
	{
		// 前ベクトルを算出し回転
		Vector3D gazing_point_to_position = *getpCamera()->getpGazingPoint()
			- *getpCamera()->getpPosition();
		gazing_point_to_position.RotationAxisAny(*getpCamera()->getpRight(),
												 D3DXToRadian(-ROTATION_SPEED));
	
		// 注視点の算出
		*getpCamera()->getpGazingPoint() = *getpCamera()->getpPosition()
			+ gazing_point_to_position;
	}
	
	// 下
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_H))
	{
		// 前ベクトルを算出し回転
		Vector3D gazing_point_to_position = *getpCamera()->getpGazingPoint()
			- *getpCamera()->getpPosition();
		gazing_point_to_position.RotationAxisAny(*getpCamera()->getpRight(),
												 D3DXToRadian(ROTATION_SPEED));
	
		// 注視点の算出
		*getpCamera()->getpGazingPoint() = *getpCamera()->getpPosition()
			+ gazing_point_to_position;
	}
}



void CameraState_CrawlUp::InputRotationAroundGazingPoint()
{
	// 左
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_N))
	{
		// 逆前ベクトルを算出し回転
		Vector3D position_to_gazing_point = *getpCamera()->getpPosition()
			- *getpCamera()->getpGazingPoint();
		position_to_gazing_point.RotationAxisY(D3DXToRadian(-ROTATION_SPEED));

		// 座標の算出
		*getpCamera()->getpPosition() = *getpCamera()->getpGazingPoint()
			+ position_to_gazing_point;
	}

	// 右
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_M))
	{
		// 逆前ベクトルを算出し回転
		Vector3D position_to_gazing_point = *getpCamera()->getpPosition() 
			- *getpCamera()->getpGazingPoint();
		position_to_gazing_point.RotationAxisY(D3DXToRadian(ROTATION_SPEED));

		// 座標の算出
		*getpCamera()->getpPosition() = *getpCamera()->getpGazingPoint()
			+ position_to_gazing_point;
	}
}