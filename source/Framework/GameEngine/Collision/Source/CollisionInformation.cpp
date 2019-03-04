//================================================================================
//!	@file	 CollisionInformation.cpp
//!	@brief	 衝突情報Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/14
//================================================================================


//****************************************
// インクルード文
//****************************************
#include "../CollisionInformation.h"
#include "../CollisionBase.h"



//****************************************
// プロパティ定義
//****************************************
Vector3D* CollisionInformation::getpCollisionPoint()
{
	return &collision_point_;
}



void CollisionInformation::setCollisionPoint(Vector3D value)
{
	collision_point_ = value;
}



Vector3D* CollisionInformation::getpCollisionPointNormal()
{
	return &collision_normal_;
}



void CollisionInformation::setCollisionPointNormal(Vector3D value)
{
	collision_normal_ = value;
}



LineSegment* CollisionInformation::getpCollisionLineSegment()
{
	return collision_line_segment_;
}



void CollisionInformation::setCollisionLineSegment(LineSegment* value)
{
	collision_line_segment_ = value;
}



Vector3D* CollisionInformation::getpNestingVector()
{
	return &nesting_vector_;
}



void CollisionInformation::setNestingVector(Vector3D value)
{
	nesting_vector_ = value;
}



CollisionBase* CollisionInformation::getpOpponentCollisionBase()
{
	return opponent_base_;
}



void CollisionInformation::setOpponentCollisionBase(CollisionBase* value)
{
	opponent_base_ = value;
}



GameObjectBase* CollisionInformation::getpOpponentGameObject()
{
	if (opponent_base_ == nullptr) return nullptr;
	return opponent_base_->getpGameObject();
}



CollisionObject* CollisionInformation::getpMyObject()
{
	return my_object_;
}



void CollisionInformation::setMyObject(CollisionObject* value)
{
	my_object_ = value;
}



CollisionObject* CollisionInformation::getpOpponentObject()
{
	return opponent_object_;
}



void CollisionInformation::setOpponentObject(CollisionObject* value)
{
	opponent_object_ = value;
}



CollisionObject::Shape* CollisionInformation::getpMyShape()
{
	return my_shape_;
}



void CollisionInformation::setMyShape(CollisionObject::Shape* value)
{
	my_shape_ = value;
}



CollisionObject::Shape* CollisionInformation::getpOpponentShape()
{
	return opponent_shape_;
}



void CollisionInformation::setOpponentShape(CollisionObject::Shape* value)
{
	opponent_shape_ = value;
}