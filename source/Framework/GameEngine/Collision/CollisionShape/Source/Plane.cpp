//================================================================================
//!	@file	 Plane.cpp
//!	@brief	 平面Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../Plane.h"



//****************************************
// プロパティ定義
//****************************************
Vector3D* Plane::getpNormal()
{ 
	return &normal_; 
}



float Plane::getAdjustmetD()
{ 
	return adjustmet_d_; 
}



//****************************************
// 関数定義
//****************************************
Plane::~Plane()
{
}



void Plane::Init(Vector3D normal, Vector3D point)
{
	CollisionShapeBase::setType(CollisionShapeBase::Type::PLANE);

	// 法線
	normal_ = normal;
	normal_.ChangeNormalize();

	// D成分
	adjustmet_d_ = -((normal_.x * point.x) + (normal_.y * point.y) 
					 + (normal_.z * point.z));
}



void Plane::Init(Vector3D point0, Vector3D point1, Vector3D point2)
{
	// 法線の作成
	Vector3D temp_normal_vector = Vector3D::CreateCrossPoint3(&point0, &point1, &point2);

	// 初期化
	Init(temp_normal_vector, point0);

	CalculationMinAndMax();
}



void Plane::Update()
{
}



void Plane::CalculationMinAndMax()
{
}