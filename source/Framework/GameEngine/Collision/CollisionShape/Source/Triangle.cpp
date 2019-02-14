//================================================================================
//!	@file	 Triangle.cpp
//!	@brief	 三角形平面Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../Triangle.h"



//****************************************
// プロパティ定義
//****************************************
Vector3D* Triangle::getpPoint(unsigned index)
{
	return &point_[index]; 
}



Plane* Triangle::getpPlane()
{
	return &plane_; 
}



//****************************************
// 関数定義
//****************************************
Triangle::~Triangle()
{
}



void Triangle::Init(Vec3 point0, Vec3 point1, Vec3 point2)
{
	CollisionShapeBase::setType(CollisionShapeBase::Type::TRIANGLE);

	// 3点
	point_[0] = point0;
	point_[1] = point1;
	point_[2] = point2;

	// 平面
	plane_.Init(point0, point1, point2);

	CalculationMinAndMax();
}



void Triangle::Update()
{
	// 最小最大更新
	CalculationMinAndMax();
}



void Triangle::CalculationMinAndMax()
{
	Vector3D max;
	Vector3D min;

	for (int i = 0; i < MAX_POINT_NUM; i++)
	{
		if (max < point_[i]) max = point_[i];
		if (min > point_[i]) min = point_[i];
	}

	*getpMax() = max;
	*getpMin() = min;
}