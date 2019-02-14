//================================================================================
//!	@file	 Axis.cpp
//!	@brief	 軸Class
//! @details 
//!	@author  Kai Araki									@date 2018/01/08
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../Axis.h"



//****************************************
// 定数定義
//****************************************
const Vector3D Axis::DEFAULT_FORWARD(0.0f, 0.0f, 1.0f);
const Vector3D Axis::DEFAULT_UP(0.0f, 1.0f, 0.0f);
const Vector3D Axis::DEFAULT_RIGHT(1.0f, 0.0f, 0.0f);



//****************************************
// プロパティ定義
//****************************************
Vector3D* Axis::getpForawrd()
{
	return &forward_; 
}



void Axis::setForward(Vec3 value)
{
	forward_ = value;
	CalculationUpAndRightVector();
	NormalizeAllVector();
}



Vector3D* Axis::getpDefaultForawrd()
{
	return &default_forward_;
}



Vector3D* Axis::getpUp()
{
	return &up_;
}



Vector3D* Axis::getpDefaultUp()
{
	return &default_up_;
}



Vector3D* Axis::getpRight()
{
	return &right_;
}



Vector3D* Axis::getpDefaultRight()
{
	return &default_right_;
}



//****************************************
// 関数定義
//****************************************
void Axis::Reset()
{
	forward_ = DEFAULT_FORWARD;
	up_ = DEFAULT_UP;
	right_ = DEFAULT_RIGHT;
}



void Axis::RotationAxisX(float radian)
{
	forward_.RotationAxisX(radian);
	up_.RotationAxisX(radian);
	CalculationUpAndRightVector();
	NormalizeAllVector();
}



void Axis::RotationAxisY(float radian)
{
	forward_.RotationAxisY(radian);
	up_.RotationAxisY(radian);
	CalculationUpAndRightVector();
	NormalizeAllVector();
}



void Axis::RotationAxisZ(float radian)
{
	forward_.RotationAxisZ(radian);
	up_.RotationAxisZ(radian);
	CalculationUpAndRightVector();
	NormalizeAllVector();
}



void Axis::RotationAxisForward(float radian)
{
	up_.RotationAxisAny(forward_, radian);
	CalculationUpAndRightVector();
	NormalizeAllVector();
}



void Axis::RotationAxisUp(float radian)
{
	forward_.RotationAxisAny(up_, radian);
	CalculationUpAndRightVector();
	NormalizeAllVector();
}



void Axis::RotationAxisRight(float radian)
{
	forward_.RotationAxisAny(right_, radian);
	CalculationUpAndRightVector();
	NormalizeAllVector();
}



void Axis::RotationAxisAny(Vec3 axis, float radian)
{
	forward_.RotationAxisAny(axis, radian);
	up_.RotationAxisAny(axis, radian);
	CalculationUpAndRightVector();
	NormalizeAllVector();
}



void Axis::RotationMatrix(MATRIX* rotation_matrix)
{
	forward_.RotationMatrix(rotation_matrix);
	up_.RotationMatrix(rotation_matrix);
	CalculationUpAndRightVector();
	NormalizeAllVector();
}



void Axis::RotationQuaternion(Quaternion* quaternion)
{
	forward_.RotationQuaternion(quaternion);
	up_.RotationQuaternion(quaternion);
	CalculationUpAndRightVector();
	NormalizeAllVector();
}
void Axis::CalculationUpAndRightVector()
{
	right_ = Vector3D::CreateCross(&up_, &forward_);
	up_ = Vector3D::CreateCross(&forward_, &right_);
}



void Axis::NormalizeAllVector()
{
	forward_.ChangeNormalize();
	up_.ChangeNormalize();
	right_.ChangeNormalize();
}