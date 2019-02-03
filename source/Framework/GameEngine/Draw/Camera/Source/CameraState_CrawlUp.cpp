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



//****************************************
// 定数定義
//****************************************
const float CameraState_CrawlUp::TRANSLATION_SPEED = 0.1f;
const float CameraState_CrawlUp::ROTATION_SPEED = 0.8f;
const float CameraState_CrawlUp::POSITION_Y = 8.0f;
const float CameraState_CrawlUp::LOOK_AT_POSITION_Y = POSITION_Y - 5.0f;



//****************************************
// 関数定義
//****************************************
void CameraState_CrawlUp::Init()
{
	getpCamera()->getpPositon()->y     = POSITION_Y;
	getpCamera()->getpLookAtPoint()->y = LOOK_AT_POSITION_Y;
}



void CameraState_CrawlUp::Uninit()
{
}



void CameraState_CrawlUp::Update()
{
	// 前
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_I))
	{
		// 前ベクトルを保存
		Vector3D temp_vector = *getpCamera()->getpAxis()->getpForawrd();

		// 地をはう準備
		temp_vector.y = 0.0f;

		temp_vector.ChangeAnyLength(TRANSLATION_SPEED);

		*getpCamera()->getpPositon() += temp_vector;
		*getpCamera()->getpLookAtPoint() += temp_vector;
	}

	// 後ろ
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_K))
	{
		// 前ベクトルを保存
		Vector3D temp_vector = *getpCamera()->getpAxis()->getpForawrd();

		// 地をはう準備
		temp_vector.y = 0.0f;

		temp_vector.ChangeAnyLength(TRANSLATION_SPEED);

		*getpCamera()->getpPositon() += -temp_vector;
		*getpCamera()->getpLookAtPoint() += -temp_vector;
	}


	// 右
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_L))
	{
		// 右ベクトルを保存
		Vector3D temp_vector = *getpCamera()->getpAxis()->getpRight();

		// 地をはう準備
		temp_vector.y = 0.0f;

		temp_vector.ChangeAnyLength(TRANSLATION_SPEED);

		*getpCamera()->getpPositon() += temp_vector;
		*getpCamera()->getpLookAtPoint() += temp_vector;
	}


	// 左
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_J))
	{
		// 右ベクトルを保存
		Vector3D temp_vector = *getpCamera()->getpAxis()->getpRight();

		// 地をはう準備
		temp_vector.y = 0.0f;

		temp_vector.ChangeAnyLength(TRANSLATION_SPEED);

		*getpCamera()->getpPositon() += -temp_vector;
		*getpCamera()->getpLookAtPoint() += -temp_vector;
	}


	// 右周り
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_E))
	{
		// 前ベクトルの作成
		Vector3D temp_vector = *getpCamera()->getpLookAtPoint() 
			- *getpCamera()->getpPositon();
		
		getpCamera()->getpAxis()->setForward(temp_vector);

		// 軸ベクトルの回転
		getpCamera()->getpAxis()->RotationAxisY(D3DXToRadian(ROTATION_SPEED));

		// 注視点の作成
		float length = temp_vector.getLength();
		temp_vector = *getpCamera()->getpAxis()->getpForawrd();
		temp_vector.ChangeAnyLength(length);

		*getpCamera()->getpLookAtPoint() = *getpCamera()->getpPositon() + temp_vector;

		// 前ベクトルを作成( 前ベクトル = 視点座標 - カメラ座標 )
		getpCamera()->getpAxis()->setForward(*getpCamera()->getpLookAtPoint() 
											 - *getpCamera()->getpPositon());
	}


	// 左周り
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_Q))
	{
		// 前ベクトルの作成
		Vector3D temp_vector = *getpCamera()->getpLookAtPoint() 
			- *getpCamera()->getpPositon();
		
		getpCamera()->getpAxis()->setForward(temp_vector);

		// 軸ベクトルの回転
		getpCamera()->getpAxis()->RotationAxisY(D3DXToRadian(-ROTATION_SPEED));

		// 注視点の作成
		float length = temp_vector.getLength();
		temp_vector = *getpCamera()->getpAxis()->getpForawrd();
		temp_vector.ChangeAnyLength(length);

		*getpCamera()->getpLookAtPoint() = *getpCamera()->getpPositon() + temp_vector;

		// 前ベクトルを作成( 前ベクトル = 視点座標 - カメラ座標 )
		getpCamera()->getpAxis()->setForward(*getpCamera()->getpLookAtPoint() 
											 - *getpCamera()->getpPositon());
	}

	// 上周り
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_T))
	{
		// 前ベクトルの作成
		Vector3D temp_vector = *getpCamera()->getpLookAtPoint() 
			- *getpCamera()->getpPositon();
		
		getpCamera()->getpAxis()->setForward(temp_vector);

		// 軸ベクトルの回転
		getpCamera()->getpAxis()->RotationAxisRight(D3DXToRadian(-ROTATION_SPEED));

		// 注視点の作成
		float length = temp_vector.getLength();
		temp_vector = *getpCamera()->getpAxis()->getpForawrd();
		temp_vector.ChangeAnyLength(length);

		*getpCamera()->getpLookAtPoint() = *getpCamera()->getpPositon() + temp_vector;

		// 前ベクトルを作成( 前ベクトル = 視点座標 - カメラ座標 )
		getpCamera()->getpAxis()->setForward(*getpCamera()->getpLookAtPoint() 
											 - *getpCamera()->getpPositon());
	}

	// 下周り
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_G))
	{
		// 前ベクトルの作成
		Vector3D temp_vector = *getpCamera()->getpLookAtPoint() 
			- *getpCamera()->getpPositon();
	
		getpCamera()->getpAxis()->setForward(temp_vector);

		// 軸ベクトルの回転
		getpCamera()->getpAxis()->RotationAxisRight(D3DXToRadian(ROTATION_SPEED));

		// 注視点の作成
		float length = temp_vector.getLength();
		temp_vector = *getpCamera()->getpAxis()->getpForawrd();
		temp_vector.ChangeAnyLength(length);

		*getpCamera()->getpLookAtPoint() = *getpCamera()->getpPositon() + temp_vector;

		// 前ベクトルを作成( 前ベクトル = 視点座標 - カメラ座標 )
		getpCamera()->getpAxis()->setForward(*getpCamera()->getpLookAtPoint() 
											 - *getpCamera()->getpPositon());
	}


	// 右周り( 視点中心 )
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_Y))
	{
		// 逆前ベクトルの作成
		Vector3D temp_vector = *getpCamera()->getpPositon() 
			- *getpCamera()->getpLookAtPoint();
		
		getpCamera()->getpAxis()->setForward(temp_vector);

		// 軸ベクトルの回転
		getpCamera()->getpAxis()->RotationAxisY(D3DXToRadian(ROTATION_SPEED));

		// カメラ座標の作成
		float length = temp_vector.getLength();
		temp_vector = *getpCamera()->getpAxis()->getpForawrd();
		temp_vector.ChangeAnyLength(length);

		*getpCamera()->getpPositon() = *getpCamera()->getpLookAtPoint() + temp_vector;

		// 前ベクトルを作成( 前ベクトル = 視点座標 - カメラ座標 )
		getpCamera()->getpAxis()->setForward(*getpCamera()->getpLookAtPoint() 
											 - *getpCamera()->getpPositon());
	}
	
	// 左周り( 視点中心 )
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_H))
	{
		// 逆前ベクトルの作成
		Vector3D temp_vector = *getpCamera()->getpPositon() 
			- *getpCamera()->getpLookAtPoint();
		
		getpCamera()->getpAxis()->setForward(temp_vector);

		// 軸ベクトルの回転
		getpCamera()->getpAxis()->RotationAxisY(D3DXToRadian(-ROTATION_SPEED));

		// カメラ座標の作成
		float length = temp_vector.getLength();
		temp_vector = *getpCamera()->getpAxis()->getpForawrd();
		temp_vector.ChangeAnyLength(length);

		*getpCamera()->getpPositon() = *getpCamera()->getpLookAtPoint()  + temp_vector;

		// 前ベクトルを作成( 前ベクトル = 視点座標 - カメラ座標 )
		getpCamera()->getpAxis()->setForward(*getpCamera()->getpLookAtPoint() 
											 - *getpCamera()->getpPositon());
	}
}