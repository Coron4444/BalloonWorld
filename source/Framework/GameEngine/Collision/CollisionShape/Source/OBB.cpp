//================================================================================
//!	@file	 OBB.cpp
//!	@brief	 OBBClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../OBB.h"



//****************************************
// プロパティ定義
//****************************************
Vector3D* OBB::getpPosition()
{
	return &position_; 
}



Axis* OBB::getpAxis()
{
	return &axis_;
}



void OBB::setAxis(Axis* value)
{
	axis_ = *value;
}



Vector3D* OBB::getpForward()
{
	return axis_.getpForward();
}



void OBB::setForward(Vector3D value)
{
	return axis_.setForward(value);
}



Vector3D* OBB::getpUp()
{
	return axis_.getpUp();
}



Vector3D* OBB::getpRight()
{
	return axis_.getpRight();
}



Vector3D* OBB::getpLength()
{
	return &length_;
}



Vector3D OBB::getRightLengthVector()
{
	Vector3D right_length_vector_(*axis_.getpRight());
	right_length_vector_.ChangeAnyLength(length_.x);
	return right_length_vector_;
}



Vector3D OBB::getUpLengthVector()
{
	Vector3D up_length_vector_(*axis_.getpUp());
	up_length_vector_.ChangeAnyLength(length_.y);
	return up_length_vector_;
}



Vector3D OBB::getForwardLengthVector()
{
	Vector3D forward_length_vector_(*axis_.getpForward());
	forward_length_vector_.ChangeAnyLength(length_.z);
	return forward_length_vector_;
}



Vector3D OBB::getRightLengthVectorHalf()
{
	return getRightLengthVector() / 2;
}



Vector3D OBB::getUpLengthVectorHalf()
{
	return getUpLengthVector() / 2;
}



Vector3D OBB::getForwardLengthVectorHalf()
{
	return getForwardLengthVector() / 2;
}



Plane* OBB::getpPlaneRight()
{
	return &plane_right_;
}



Plane* OBB::getpPlaneUp()
{
	return &plane_up_;
}



Plane* OBB::getpPlaneForward()
{
	return &plane_forward_;
}



Plane* OBB::getpPlaneInverseRight()
{
	return &plane_inverse_right_;
}



Plane* OBB::getpPlaneInverseUp()
{
	return &plane_inverse_up_;
}



Plane* OBB::getpPlaneInverseForward()
{
	return &plane_inverse_forward_;
}



//****************************************
// 関数定義
//****************************************
OBB::~OBB()
{
}



void OBB::Init(Vector3D position, Vector3D length)
{
	CollisionShapeBase::setType(CollisionShapeBase::Type::OBB);

	position_ = position;
	length_ = length;

	CalculationPlane();
	CalculationMinAndMax();
}



void OBB::Update()
{
	// 面作成
	CalculationPlane();

	// 最小最大更新
	CalculationMinAndMax();
}



void OBB::RotationAxisX(float radian)
{
	axis_.RotationAxisX(radian);
}



void OBB::RotationAxisY(float radian)
{
	axis_.RotationAxisY(radian);
}



void OBB::RotationAxisZ(float radian)
{
	axis_.RotationAxisZ(radian);
}



void OBB::RotationAxisForward(float radian)
{
	axis_.RotationAxisForward(radian);
}



void OBB::RotationAxisUp(float radian)
{
	axis_.RotationAxisUp(radian);
}



void OBB::RotationAxisRight(float radian)
{
	axis_.RotationAxisRight(radian);
}



void OBB::RotationAxisAny(Vector3D axis, float radian)
{
	axis_.RotationAxisAny(axis, radian);
}



void OBB::RotationMatrix(Matrix* matrix)
{
	axis_.Reset();
	axis_.RotationMatrix(matrix);
}



void OBB::RotationQuaternion(Quaternion* quaternion)
{
	axis_.RotationQuaternion(quaternion);
}



void OBB::CalculationMinAndMax()
{
	Vector3D point[MAX_POINT_NUM];
	point[0] = position_ + getRightLengthVectorHalf() + getUpLengthVectorHalf() + getForwardLengthVectorHalf();
	point[1] = position_ + getRightLengthVectorHalf() + getUpLengthVectorHalf() + -getForwardLengthVectorHalf();
	point[2] = position_ + -getRightLengthVectorHalf() + getUpLengthVectorHalf() + getForwardLengthVectorHalf();
	point[3] = position_ + -getRightLengthVectorHalf() + getUpLengthVectorHalf() + -getForwardLengthVectorHalf();
	point[4] = position_ + getRightLengthVectorHalf() + -getUpLengthVectorHalf() + getForwardLengthVectorHalf();
	point[5] = position_ + getRightLengthVectorHalf() + -getUpLengthVectorHalf() + -getForwardLengthVectorHalf();
	point[6] = position_ + -getRightLengthVectorHalf() + -getUpLengthVectorHalf() + getForwardLengthVectorHalf();
	point[7] = position_ + -getRightLengthVectorHalf() + -getUpLengthVectorHalf() + -getForwardLengthVectorHalf();

	Vector3D max = point[0];
	Vector3D min = point[0];
	for (int i = 0; i < MAX_POINT_NUM; i++)
	{
		if (max.x < point[i].x) max.x = point[i].x;
		if (max.y < point[i].y) max.y = point[i].y;
		if (max.z < point[i].z) max.z = point[i].z;
		if (min.x > point[i].x) min.x = point[i].x;
		if (min.y > point[i].y) min.y = point[i].y;
		if (min.z > point[i].z) min.z = point[i].z;
	}

	*getpMax() = max;
	*getpMin() = min;
}



void OBB::CalculationPlane()
{
	// 右方向
	Vector3D plane_point = position_ + getRightLengthVectorHalf();
	plane_right_.Init(*axis_.getpRight(), plane_point);

	// 上方向
	plane_point = position_ + getUpLengthVectorHalf();
	plane_up_.Init(*axis_.getpUp(), plane_point);

	// 前方向
	plane_point = position_ + getForwardLengthVectorHalf();
	plane_forward_.Init(*axis_.getpForward(), plane_point);

	// 逆右方向
	plane_point = position_ + -getRightLengthVectorHalf();
	plane_inverse_right_.Init(-(*axis_.getpRight()), plane_point);

	// 逆上方向
	plane_point = position_ + -getUpLengthVectorHalf();
	plane_inverse_up_.Init(-(*axis_.getpUp()), plane_point);

	// 逆前方向
	plane_point = position_ + -getForwardLengthVectorHalf();
	plane_inverse_forward_.Init(-(*axis_.getpForward()), plane_point);
}