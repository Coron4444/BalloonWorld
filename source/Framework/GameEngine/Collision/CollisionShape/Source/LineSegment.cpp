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
	Vec3 min_position;
	Vec3 max_position;

	// 座標が左、方向ベクトル加算済み座標が右の場合
	if (position_ < getAddVectorToPosition())
	{
		min_position = getAddVectorToPosition();
		max_position = position_;
	}
	else
	{
		min_position = position_;
		max_position = getAddVectorToPosition();
	}

	*getpMax() = max_position;
	*getpMin() = min_position;
}