//================================================================================
//!	@file	 Collision.cpp
//!	@brief	 空白衝突Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================


//****************************************
// インクルード文
//****************************************
#include "../CollisionNull.h"



//****************************************
// 関数定義
//****************************************
CollisionNull::~CollisionNull()
{
}



void CollisionNull::Init()
{
}



void CollisionNull::Uninit()
{
	CollisionBase::ReleaseAllCollisionObject();
}



void CollisionNull::Update()
{
}



void CollisionNull::Reset()
{
}



void CollisionNull::DebugDisplay()
{
}



void CollisionNull::HitCollision(CollisionInformation* information)
{
	// 使われていない引数の処理
	information = information;
}



void CollisionNull::HitGround(float position_y) 
{
	position_y = position_y; 
}