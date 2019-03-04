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



void Triangle::Init(Vector3D point0, Vector3D point1, Vector3D point2)
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
		if (max.x < point_[i].x) max.x = point_[i].x;
		if (max.y < point_[i].y) max.y = point_[i].y;
		if (max.z < point_[i].z) max.z = point_[i].z;
		if (min.x > point_[i].x) min.x = point_[i].x;
		if (min.y > point_[i].y) min.y = point_[i].y;
		if (min.z > point_[i].z) min.z = point_[i].z;
	}

	*getpMax() = max;
	*getpMin() = min;
}