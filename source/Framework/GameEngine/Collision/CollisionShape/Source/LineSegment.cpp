//================================================================================
//!	@file	 LineSegment.cpp
//!	@brief	 線分Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../LineSegment.h"



//****************************************
// プロパティ定義
//****************************************
Vector3D* LineSegment::getpPosition()
{
	return &position_; 
}



Vector3D* LineSegment::getpVector()
{
	return &vector_; 
}



Vector3D LineSegment::getAddVectorToPosition()
{ 
	return position_ + vector_; 
}



float LineSegment::getSlopeOf2DLineSegment()
{ 
	return vector_.y / vector_.x;
}



//****************************************
// 関数定義
//****************************************
LineSegment::~LineSegment() 
{
}



void LineSegment::Init(Vector3D position, Vector3D vector)
{
	CollisionShapeBase::setType(CollisionShapeBase::Type::LINE_SEGMENT);

	position_ = position;
	vector_ = vector;

	CalculationMinAndMax();
}



void LineSegment::Update()
{
	// 最小最大更新
	CalculationMinAndMax();
}



void LineSegment::CalculationMinAndMax()
{
	Vector3D max;
	Vector3D min;

	if (position_.x > getAddVectorToPosition().x)
	{
		max.x = position_.x;
		min.x = getAddVectorToPosition().x;
	}
	else
	{
		max.x = getAddVectorToPosition().x;
		min.x = position_.x;
	}

	if (position_.y > getAddVectorToPosition().y)
	{
		max.y = position_.y;
		min.y = getAddVectorToPosition().y;
	}
	else
	{
		max.y = getAddVectorToPosition().y;
		min.y = position_.y;
	}

	if (position_.z > getAddVectorToPosition().z)
	{
		max.z = position_.z;
		min.z = getAddVectorToPosition().z;
	}
	else
	{
		max.z = getAddVectorToPosition().z;
		min.z = position_.z;
	}

	*getpMax() = max;
	*getpMin() = min;
}