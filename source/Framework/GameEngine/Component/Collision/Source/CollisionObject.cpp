//================================================================================
//!	@file	 CollisionObject.cpp
//!	@brief	 �Փ˃I�u�W�F�N�gClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================


//****************************************
// �C���N���[�h��
//****************************************
#include "CollisionObject.h"

#include <SafeRelease/SafeRelease.h>



//****************************************
// �v���p�e�B��`
//****************************************
int	CollisionObject::getTag()
{ 
	return tag_; 
}



CollisionShapeBase* CollisionObject::getpCollisionShape()
{ 
	return collision_shape_; 
}



Vector3D* CollisionObject::getpHitVector()
{ 
	return &hit_vector_;
}



void CollisionObject::setHitVector(Vector3D value)
{
	hit_vector_ = value;
}



bool CollisionObject::getIsJudgment()
{ 
	return is_judgment_; 
}



void CollisionObject::setIsJudgment(bool value)
{ 
	is_judgment_ = value;
}



//****************************************
// �֐���`
//****************************************
CollisionObject::CollisionObject(CollisionShapeBase* collision_shape, int tag)
	: collision_shape_(collision_shape),
	tag_(tag),
	is_judgment_(true)
{
}



CollisionObject::~CollisionObject()
{
	switch (collision_shape_->getType())
	{
		case CollisionShapeBase::Type::AABB:
		{
			AABB* temp = (AABB*)collision_shape_;
			SafeRelease::Normal(&temp);
			break;
		}
		case CollisionShapeBase::Type::CAPSULE:
		{
			Capsule* temp = (Capsule*)collision_shape_;
			SafeRelease::Normal(&temp);
			break;
		}
		case CollisionShapeBase::Type::CYLINDER:
		{
			Cylinder* temp = (Cylinder*)collision_shape_;
			SafeRelease::Normal(&temp);

			break;
		}
		case CollisionShapeBase::Type::OBB:
		{
			OBB* temp = (OBB*)collision_shape_;
			SafeRelease::Normal(&temp);

			break;
		}
		case CollisionShapeBase::Type::PLANE:
		{
			Plane* temp = (Plane*)collision_shape_;
			SafeRelease::Normal(&temp);

			break;
		}
		case CollisionShapeBase::Type::LINE_SEGMENT:
		{
			LineSegment* temp = (LineSegment*)collision_shape_;
			SafeRelease::Normal(&temp);

			break;
		}
		case CollisionShapeBase::Type::SPHERE:
		{
			Sphere* temp = (Sphere*)collision_shape_;
			SafeRelease::Normal(&temp);

			break;
		}
		case CollisionShapeBase::Type::TRIANGLE:
		{
			Triangle* temp = (Triangle*)collision_shape_;
			SafeRelease::Normal(&temp);

			break;
		}
	}
}



void CollisionObject::ResetHitData()
{
	hit_vector_.ResetVector();
	is_judgment_ = true;
}