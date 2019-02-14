//================================================================================
//!	@file	 LineSegment.cpp
//!	@brief	 ����Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../LineSegment.h"



//****************************************
// �v���p�e�B��`
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
// �֐���`
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
	// �ŏ��ő�X�V
	CalculationMinAndMax();
}



void LineSegment::CalculationMinAndMax()
{
	Vec3 min_position;
	Vec3 max_position;

	// ���W�����A�����x�N�g�����Z�ςݍ��W���E�̏ꍇ
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