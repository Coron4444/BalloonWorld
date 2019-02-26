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

#include <Tool/Axis.h>



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
	Vector3D max;
	Vector3D min;

	// XY座標
	Axis axis;
	axis.RotationAxisZ(D3DXToRadian(-45.0f));
	Vector3D up = *axis.getpUp();
	Vector3D right = *axis.getpRight();
	up.ChangeAnyLength(getpVector()->getLength());
	right.ChangeAnyLength(radius_);
	
	Vector3D temp_max = *getpPosition() + up + right;
	max.x = temp_max.x;
	temp_max = *getpPosition() + up + -right;
	max.y = temp_max.y;

	Vector3D temp_min = *getpPosition() + -right;
	min.x = temp_min.x;
	temp_min = *getpPosition() + right;
	min.y = temp_min.y;

	// Z座標
	axis.Reset();
	axis.RotationAxisX(D3DXToRadian(45.0f));
	up = *axis.getpUp();
	Vector3D forward = *axis.getpForward();
	up.ChangeAnyLength(getpVector()->getLength());
	forward.ChangeAnyLength(radius_);

	temp_max = *getpPosition() + up + forward;
	max.z = temp_max.z;
	
	temp_min = *getpPosition() + -forward;
	min.z = temp_min.z;
	
	*getpMax() = max;
	*getpMin() = min;
}