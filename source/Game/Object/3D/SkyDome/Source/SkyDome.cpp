//================================================================================
//!	@file	 SkyDome.cpp
//!	@brief	 天球Class
//! @details 
//!	@author  Kai Araki									@date 2018/05/15
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../SkyDome.h"



//****************************************
// 関数定義
//****************************************
void SkyDome::Init(DrawBase* draw)
{
	// 基底クラスの初期化
	GameObjectBase::Init(draw, nullptr);
}



void SkyDome::Update()
{
	*getpTransform()->getpAngleYaw() += 0.0005f;
	getpTransform()->CreateWorldMatrix();
}