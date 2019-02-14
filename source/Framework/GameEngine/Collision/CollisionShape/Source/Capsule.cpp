//================================================================================
//!	@file	 Capsule.h
//!	@brief	 カプセルClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../Capsule.h"



//****************************************
// プロパティ定義
//****************************************
Sphere* Capsule::getpSphere0() 
{ 
	return &sphere0_;
}



Sphere* Capsule::getpSphere1() 
{ 
	return &sphere1_; 
}



Cylinder* Capsule::getpCylinder() 
{
	return &cylinder_;
}



LineSegment* Capsule::getpLineSegment()
{ 
	return cylinder_.getpLineSegment();
}



Vector3D* Capsule::getpPosition() 
{
	return cylinder_.getpPosition();
}



Vector3D* Capsule::getpVector()
{ 
	return cylinder_.getpVector();
}



Vector3D Capsule::getAddVectorToPosition() 
{
	return cylinder_.getAddVectorToPosition(); 
}



float Capsule::getRadius() 
{ 
	return cylinder_.getRadius(); 
}



void Capsule::setRadius(float value) 
{ 
	cylinder_.setRadius(value); 
}



//****************************************
// 関数定義
//****************************************
Capsule::~Capsule()
{
}



void Capsule::Init(Vector3D position, Vector3D vector, float radius)
{
	CollisionShapeBase::setType(CollisionShapeBase::Type::CAPSULE);

	// 円柱
	cylinder_.Init(position, vector, radius);

	// 球
	sphere0_.Init(*cylinder_.getpPosition(), radius);
	sphere1_.Init(cylinder_.getAddVectorToPosition(), radius);

	CalculationMinAndMax();
}



void Capsule::Update()
{
	// 球の更新
	*sphere0_.getpPosition() = *cylinder_.getpPosition();
	sphere0_.setRadius(cylinder_.getRadius());
	*sphere1_.getpPosition() = cylinder_.getAddVectorToPosition();
	sphere1_.setRadius(cylinder_.getRadius());

	// 最小最大更新
	CalculationMinAndMax();
}



void Capsule::CalculationMinAndMax()
{
	Vector3D length(1.0f, 1.0f, 1.0f);
	length.ChangeAnyLength(sphere0_.getRadius());

	*getpMax() = *cylinder_.getpLineSegment()->getpMax() + length;
	*getpMin() = *cylinder_.getpLineSegment()->getpMin() + -length;
}