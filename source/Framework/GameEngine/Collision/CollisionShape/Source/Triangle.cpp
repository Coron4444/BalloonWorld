//================================================================================
//!	@file	 Triangle.cpp
//!	@brief	 �O�p�`����Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../Triangle.h"



//****************************************
// �v���p�e�B��`
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
// �֐���`
//****************************************
Triangle::~Triangle()
{
}



void Triangle::Init(Vec3 point0, Vec3 point1, Vec3 point2)
{
	CollisionShapeBase::setType(CollisionShapeBase::Type::TRIANGLE);

	// 3�_
	point_[0] = point0;
	point_[1] = point1;
	point_[2] = point2;

	// ����
	plane_.Init(point0, point1, point2);

	CalculationMinAndMax();
}



void Triangle::Update()
{
	// �ŏ��ő�X�V
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