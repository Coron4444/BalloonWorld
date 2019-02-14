//================================================================================
//!	@file	 Cylinder.cpp
//!	@brief	 円柱Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../Cylinder.h"



//****************************************
// プロパティ定義
//****************************************
LineSegment* Cylinder::getpLineSegment()
{
	return &line_segment_;
}



Vector3D* Cylinder::getpPosition()
{
	return line_segment_.getpPosition();
}



Vector3D* Cylinder::getpVector()
{
	return line_segment_.getpVector();
}



void Cylinder::setVector(Vector3D value)
{
	*line_segment_.getpVector() = value;
	axis_.setForward(*line_segment_.getpVector());
}



Vector3D Cylinder::getAddVectorToPosition()
{
	return line_segment_.getAddVectorToPosition();
}



float Cylinder::getRadius()
{
	return radius_;
}



void Cylinder::setRadius(float value)
{
	radius_ = value;
}



//****************************************
// 関数定義
//****************************************
Cylinder::~Cylinder()
{
}



void Cylinder::Init(Vector3D position, Vector3D vector, float radius)
{
	CollisionShapeBase::setType(CollisionShapeBase::Type::CYLINDER);

	// 線分
	line_segment_.Init(position, vector);
	axis_.setForward(*line_segment_.getpVector());

	// 半径
	radius_ = radius;

	CalculationMinAndMax();
}


void Cylinder::Update()
{
	// 最小最大更新
	CalculationMinAndMax();
}



void Cylinder::CalculationMinAndMax()
{
	line_segment_.Update();
	Vector3D length = *axis_.getpRight();
	length.ChangeAnyLength(radius_);
	Vec3 max0 = *line_segment_.getpMax() + length;
	Vec3 max1 = *line_segment_.getpMax() + -length;
	Vec3 min0 = *line_segment_.getpMin() + length;
	Vec3 min1 = *line_segment_.getpMin() + -length;

	*getpMax() = max0 > max1 ? max0 : max1;
	*getpMin() = min0 < min1 ? min0 : min1;
}