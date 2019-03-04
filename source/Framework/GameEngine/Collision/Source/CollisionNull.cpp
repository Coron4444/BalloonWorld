//================================================================================
//!	@file	 Collision.cpp
//!	@brief	 �󔒏Փ�Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================


//****************************************
// �C���N���[�h��
//****************************************
#include "../CollisionNull.h"



//****************************************
// �֐���`
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
	// �g���Ă��Ȃ������̏���
	information = information;
}



void CollisionNull::HitGround(float position_y) 
{
	position_y = position_y; 
}