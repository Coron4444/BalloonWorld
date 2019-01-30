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
	ReleaseAllCollisionObjectsFromArray();
}



void CollisionNull::Init()
{
}



void CollisionNull::Uninit()
{
	// �����Փ˃I�u�W�F�N�g�̔���OFF
	for (unsigned i = 0; i < getEndIndexOfArray(); i++)
	{
		getpCollisionObjects(i)->setIsJudgment(false);
	}
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



void CollisionNull::HitCollision(CollisionBase* hit_collision,
								 CollisionObject*  hit_object,
								 CollisionObject*  hit_my_object)
{
	// �g���Ă��Ȃ������̏���
	hit_collision = hit_collision;
	hit_object = hit_object;
	hit_my_object = hit_my_object;
}



void CollisionNull::NotHitCollision(CollisionBase*	hit_collision,
					 CollisionObject*  hit_object,
					 CollisionObject*  hit_my_object)
{
	// �g���Ă��Ȃ������̏���
	hit_collision = hit_collision;
	hit_object = hit_object;
	hit_my_object = hit_my_object;
}



void CollisionNull::HitGround(float position_y) 
{
	position_y = position_y; 
}



void CollisionNull::NotHitGround(float position_y)
{
	position_y = position_y; 
}