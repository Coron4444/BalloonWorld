//================================================================================
//!	@file	 CollisionCalculation.cpp
//!	@brief	 �Փˌv�ZClass
//! @details static
//!	@author  Kai Araki									@date 2018/11/06
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../CollisionCalculation.h"
#include "../../CollisionShape/AABB.h"
#include "../../CollisionShape/Capsule.h"
#include "../../CollisionShape/Cylinder.h"
#include "../../CollisionShape/OBB.h"
#include "../../CollisionShape/Plane.h"
#include "../../CollisionShape/LineSegment.h"
#include "../../CollisionShape/Sphere.h"
#include "../../CollisionShape/Triangle.h"
#include "../../CollisionInformation.h"



//****************************************
// �萔��`
//****************************************
const float CollisionCalculation::ERROR_RANGE = 0.000001f;



//****************************************
// static�֐���`
//****************************************
bool CollisionCalculation::CollisionJudgmentOf2DLineSegmentAnd2DLineSegment(CollisionInformation* information0,
																			CollisionInformation* information1,
																			LineSegment* line_segment0,
																			LineSegment* line_segment1)
{
	information1 = information1;

	// X�������̃x�N�g����0���ǂ���
	if (DetermineWhetherXOfEitherLineSegmentIsZero(line_segment0, line_segment1))
	{
		// ������X�x�N�g����0�A�܂蕽�s�ł��� 
		if (DetermineWhetherXOfBothLineSegmentsIsZero(line_segment0,
													  line_segment1)) return false;

		// �ǂ��炩��X��0�̏ꍇ
		if (line_segment0->getpVector()->x == 0)
		{
			return IntersectionCalculationOf2DLineSegmentAnd2DLineSegmentWhenXIsZero(information0->getpCollisionPoint(),
																					 line_segment0,
																					 line_segment1);
		}
		else
		{
			return IntersectionCalculationOf2DLineSegmentAnd2DLineSegmentWhenXIsZero(information0->getpCollisionPoint(),
																					 line_segment1,
																					 line_segment0);
		}

	}
	else
	{
		return IntersectionCalculationOf2DLineSegmentAnd2DLineSegment(information0->getpCollisionPoint(),
																	  line_segment0,
																	  line_segment1);
	}

}



bool CollisionCalculation::CollisionJudgmentOfLineSegmentAndSphere(CollisionInformation* information0,
																   CollisionInformation* information1,
																   LineSegment* line_segment,
																   Sphere* sphere)
{
	// �񎟕������̌v�Z
	QuadraticEquation equation;

	// �񎟕������ɉ������邩
	bool is_calculable = QuadraticEquationCalculationForLineSegmentsAndSpheres(&equation,
																			   line_segment,
																			   sphere);
	if (!is_calculable) return false;

	// ��������1�Ԏ�O�̔䗦�����߂�
	float ratio = CalculateTheRatioOfTheFrontInTheLineSegment(equation.getAnswer0(),
															  equation.getAnswer1());
	if (!DetermineWhetherTheRatioIsBetweenZeroAndOne(ratio)) return false;

	// �Փ˓_�̎Z�o
	*line_segment->getpVector() *= ratio;
	*information0->getpCollisionPoint() = line_segment->getAddVectorToPosition();
	*information1->getpCollisionPoint() = *information0->getpCollisionPoint();
	return true;
}



bool CollisionCalculation::CollisionJudgmentOfLineSegmentAndPlane(CollisionInformation* information0,
																  CollisionInformation* information1,
																  LineSegment* line_segment,
																  Plane* plane)
{
	// �\���`�F�b�N
	float temp_dot = Vector3D::CreateDot(line_segment->getpVector(), plane->getpNormal());
	if (temp_dot >= 0.0f) return false;

	// �����n�_�ƕ��ʂƂ̋������Z�o
	float length = CalculateTheShortestDistanceBetweenPlaneAndPoint(plane, line_segment->getpPosition());

	// �����Ɛ����̔�r
	if (DetermineIfItIsLongerThanVector(line_segment->getpVector(),
										length)) return false;

	// ���������ʂɓ͂��������Z�o
	float temp_length = CalculateTheDistanceTheLineSegmentReachesThePlane(*line_segment->getpVector(),
																		  plane,
																		  length);
	if (DetermineIfItIsLongerThanVector(line_segment->getpVector(),
										temp_length)) return false;

	// �Փ˓_�̎Z�o
	line_segment->getpVector()->ChangeAnyLength(length);
	*information0->getpCollisionPoint() = line_segment->getAddVectorToPosition();
	*information1->getpCollisionPoint() = *information0->getpCollisionPoint();
	return true;
}



bool CollisionCalculation::CollisionJudgmentOfLineSegmentAndTriangle(CollisionInformation* information0,
																	 CollisionInformation* information1,
																	 LineSegment* line_segment,
																	 Triangle* triangle)
{
	// �������ʂƂ̓����蔻��
	CollisionInformation temp_information0;
	CollisionInformation temp_information1;
	if (!CollisionJudgmentOfLineSegmentAndPlane(&temp_information0, &temp_information1,
												line_segment, triangle->getpPlane())) return false;

	// ��_��3�p�`�����̔���
	if (!IsPointsAreIncludedInThePlane(triangle, temp_information0.getpCollisionPoint())) return false;

	// �Փ˓_�̎Z�o
	*information0->getpCollisionPoint() = *temp_information0.getpCollisionPoint();
	*information1->getpCollisionPoint() = *temp_information1.getpCollisionPoint();
	return true;
}



bool CollisionCalculation::CollisionJudgmentOfLineSegmentAndCylinder(CollisionInformation* information0,
																	 CollisionInformation* information1,
																	 LineSegment* line_segment,
																	 Cylinder* cylinder)
{
	// �񎟕������̌v�Z
	QuadraticEquation equation;

	// �񎟕������ɉ������邩
	bool is_calculable = QuadraticEquationCalculationForLineSegmentsAndCylinders(&equation,
																				 line_segment,
																				 cylinder);
	if (!is_calculable) return false;

	// ��������1�Ԏ�O�̔䗦�����߂�
	float ratio = CalculateTheRatioOfTheFrontInTheLineSegment(equation.getAnswer0(),
															  equation.getAnswer1());
	if (!DetermineWhetherTheRatioIsBetweenZeroAndOne(ratio)) return false;

	// �Փ˓_�̎Z�o
	*line_segment->getpVector() *= ratio;
	*information0->getpCollisionPoint() = line_segment->getAddVectorToPosition();
	*information1->getpCollisionPoint() = *information0->getpCollisionPoint();
	return true;
}



bool CollisionCalculation::CollisionJudgmentOfLineSegmentAndCapsule(CollisionInformation* information0,
																	CollisionInformation* information1,
																	LineSegment* line_segment,
																	Capsule* capsule)
{
	CollisionInformation temp_information0;
	CollisionInformation temp_information1;

	// �O�����ƏՓ˂��Ă��邩�H
	if (CollisionJudgmentOfLineSegmentAndSphere(&temp_information0,
												&temp_information1,
												line_segment,
												capsule->getpSphere0()))
	{
		// �݊p���ǂ���
		if (IsObtuseAnglePoint3(capsule->getpSphere1()->getpPosition(),
								capsule->getpSphere0()->getpPosition(),
								temp_information0.getpCollisionPoint()))
		{
			// �Փ˓_�̎Z�o
			*information0->getpCollisionPoint() = *temp_information0.getpCollisionPoint();
			*information1->getpCollisionPoint() = *temp_information1.getpCollisionPoint();
			return true;
		}
	}

	// �㔼���ƏՓ˂��Ă��邩�H
	if (CollisionJudgmentOfLineSegmentAndSphere(&temp_information0, &temp_information1,
												line_segment, capsule->getpSphere1()))
	{
		// �݊p���ǂ���
		if (IsObtuseAnglePoint3(capsule->getpSphere0()->getpPosition(),
								capsule->getpSphere1()->getpPosition(),
								temp_information0.getpCollisionPoint()))
		{
			// �Փ˓_�̎Z�o
			*information0->getpCollisionPoint() = *temp_information0.getpCollisionPoint();
			*information1->getpCollisionPoint() = *temp_information1.getpCollisionPoint();
			return true;
		}
	}

	// �~���ƏՓ˂��Ă��邩�H
	if (CollisionJudgmentOfLineSegmentAndCylinder(&temp_information0,
												  &temp_information1,
												  line_segment,
												  capsule->getpCylinder()))
	{
		// �S�ĉs�p���ǂ���
		if (!IsObtuseAnglePoint3(capsule->getpSphere0()->getpPosition(),
								 capsule->getpSphere1()->getpPosition(),
								 temp_information0.getpCollisionPoint())) return false;
		if (!IsObtuseAnglePoint3(capsule->getpSphere1()->getpPosition(),
								 capsule->getpSphere0()->getpPosition(),
								 temp_information0.getpCollisionPoint())) return false;

		// �Փ˓_�̎Z�o
		*information0->getpCollisionPoint() = *temp_information0.getpCollisionPoint();
		*information1->getpCollisionPoint() = *temp_information1.getpCollisionPoint();
		return true;
	}

	return false;
}



bool CollisionCalculation::CollisionJudgmentOfSphereAndSphere(CollisionInformation* information0,
															  CollisionInformation* information1,
															  Sphere* sphere0,
															  Sphere* sphere1)
{
	// ���S�ԋ����Ɣ��a�̍��v�ɂ��Փ˔���
	Vector3D center_to_center_vector = *sphere0->getpPosition() - *sphere1->getpPosition();
	float two_radius = sphere0->getRadius() + sphere1->getRadius();

	if (!DetermineIfItIsLongerThanVector(&center_to_center_vector,
										 two_radius)) return false;

	// �Փ˃x�N�g���̎Z�o
	float length = two_radius - center_to_center_vector.getLength();
	*information0->getpNestingVector() = *center_to_center_vector.ChangeAnyLength(length);
	*information1->getpNestingVector() = -(*information0->getpNestingVector());
	return true;
}



bool CollisionCalculation::CollisionJudgmentOfSphereAndPlane(CollisionInformation* information0,
															 CollisionInformation* information1,
															 Sphere* sphere,
															 Plane* plane)
{
	// ���ʂƋ��̒��S�����Ɣ��a�Ƃ̔���
	float temp_length = CalculateTheShortestDistanceBetweenPlaneAndPoint(plane, sphere->getpPosition());
	if (!(sphere->getRadius() > temp_length)) return false;

	// �Փ˃x�N�g���̎Z�o
	temp_length = sphere->getRadius() - CalculateTheShortestDistanceBetweenPlaneAndPoint(plane, sphere->getpPosition());
	Vector3D temp_vector = *plane->getpNormal();
	*information0->getpNestingVector() = *temp_vector.ChangeAnyLength(temp_length);
	*information1->getpNestingVector() = -(*information0->getpNestingVector());
	return true;
}



bool CollisionCalculation::CollisionJudgmentOfSphereAndTriangle(CollisionInformation* information0,
																CollisionInformation* information1,
																Sphere* sphere,
																Triangle* triangle)
{
	// �������ʂƂ̏Փ˔���
	CollisionInformation temp_information0;
	CollisionInformation temp_information1;
	if (!CollisionJudgmentOfSphereAndPlane(&temp_information0,
										   &temp_information1,
										   sphere, triangle->getpPlane())) return false;

	// �O�p�`�̊e�ӂ��Փ˂��Ă��邩
	if (DetermineWhetherASphereCollidesAgainstEachSide(sphere, triangle))
	{
		// �Փ˃x�N�g���̎Z�o
		*information0->getpNestingVector() = *temp_information0.getpNestingVector();
		*information1->getpNestingVector() = *temp_information1.getpNestingVector();
		return true;
	}

	// �����O�p�`�̓����ɂ߂荞��ł��邩
	if (DetermineWhetherTheSphereIsSinkingInside(sphere, triangle))
	{
		// �Փ˃x�N�g���̎Z�o
		*information0->getpNestingVector() = *temp_information0.getpNestingVector();
		*information1->getpNestingVector() = *temp_information1.getpNestingVector();
		return true;
	}
	return false;
}



bool CollisionCalculation::CollisionJudgmentOfSphereAndCapsule(CollisionInformation* information0,
															   CollisionInformation* information1,
															   Sphere* sphere,
															   Capsule* capsule)
{
	// ���̒��S�ƃJ�v�Z���Ƃ̋������Z�o
	Vector3D  intersection_point;
	float ratio;
	float length = CalculateTheShortestDistanceBetweenPointsAndLineSegments(&intersection_point,
																			&ratio,
																			sphere->getpPosition(),
																			capsule->getpLineSegment());

	// ������2�̔��a�Ƃ̍��v�̔�r
	float two_radius = sphere->getRadius() + capsule->getRadius();
	if (length > two_radius) return false;

	// �Փ˃x�N�g���̎Z�o
	length = two_radius - length;
	*information0->getpNestingVector() = *sphere->getpPosition() - intersection_point;
	information0->getpNestingVector()->ChangeAnyLength(length);
	*information1->getpNestingVector() = -(*information0->getpNestingVector());
	return true;
}



bool CollisionCalculation::CollisionJudgmentOfSphereAndOBB(CollisionInformation* information0,
														   CollisionInformation* information1,
														   Sphere* sphere,
														   OBB* obb)
{
	// �_��OBB�̍ŒZ�����x�N�g���Z�o
	Vector3D shortest_distance = CalculateTheShortestDistanceVectorBetweenOBBAndPoint(obb, sphere->getpPosition());

	// �����Ɣ��a�̔�r
	if (FroatTruncation(shortest_distance.getLength()) > sphere->getRadius()) return false;

	// �Փ˓_����@�����Z�o
	*information0->getpCollisionPoint() = *sphere->getpPosition() + -shortest_distance;
	*information1->getpCollisionPoint() = *information0->getpCollisionPoint();
	*information0->getpCollisionPointNormal() =
		CalculateOfNormalFromCollisionPointOfOBB(obb, information0->getpCollisionPoint());

	// �Փ˃x�N�g���̎Z�o
	float length = sphere->getRadius() - shortest_distance.getLength();
	*information0->getpNestingVector() = shortest_distance;
	information0->getpNestingVector()->ChangeAnyLength(length);
	*information1->getpNestingVector() = -(*information0->getpNestingVector());
	return true;
}



bool CollisionCalculation::CollisionJudgmentOfPlaneAndPlane(CollisionInformation* information0,
															CollisionInformation* information1,
															Plane* plane0,
															Plane* plane1)
{
	// ���ʂ̖@����p���āA���҂����s�ł��邩�̊m�F������(�Փ˂��邩�̊m�F)
	if (!DetermineWhetherThePlaneIsParallel(plane0, plane1)) return false;

	// �������������߂�
	CalculationOfCollisionLineSegment(information0->getpCollisionLineSegment(), plane0, plane1);
	*information1->getpCollisionLineSegment() = *information0->getpCollisionLineSegment();
	return true;
}



bool CollisionCalculation::CollisionJudgmentOfPlaneAndTriangle(CollisionInformation* information0,
															   CollisionInformation* information1,
															   Plane* plane,
															   Triangle* triangle)
{
	information0 = information0;
	information1 = information1;

	int side0 = (int)CalculateTheShortestDistanceBetweenPlaneAndPoint(plane, triangle->getpPoint(0));
	int side1 = (int)CalculateTheShortestDistanceBetweenPlaneAndPoint(plane, triangle->getpPoint(1));

	// ����2�_��������������
	if ((side0 && !side1) || (!side0 && side1)) return true;

	int side2 = (int)CalculateTheShortestDistanceBetweenPlaneAndPoint(plane, triangle->getpPoint(2));

	// ����2�_��������������
	if ((side1 && !side2) || (!side1 && side2)) return true;

	return false;
}



bool CollisionCalculation::CollisionJudgmentOfTriangleAndTriangle(CollisionInformation* information0,
																  CollisionInformation* information1,
																  Triangle* triangle0,
																  Triangle* triangle1)
{
	information0 = information0;
	information1 = information1;

	bool is_hit_segment_one = false;

	// �Е��̎O�p�`�������Е����т��Ă��邩
	if (DetermineIfATrianglePenetrates(&is_hit_segment_one,
									   triangle0, triangle1)) return true;

	// �����Е����`�F�b�N
	if (DetermineIfATrianglePenetrates(&is_hit_segment_one,
									   triangle1, triangle0)) return true;

	// ���݂���1�ӂ��ђʂ��Ă��邩
	if (is_hit_segment_one) return true;

	return false;
}



bool CollisionCalculation::CollisionJudgmentOfCapsuleAndCapsule(CollisionInformation* information0,
																CollisionInformation* information1,
																Capsule* capsule0,
																Capsule* capsule1,
																Vector3D active_vector)
{
	Vector3D intersection_point0;
	Vector3D intersection_point1;
	float ratio0;
	float ratio1;

	// �����Ԃ̍ŒZ�����Ɣ��a�̍��v���Z�o
	float length = CalculateTheShortestDistanceBetweenLineSegmentAndLineSegment(&intersection_point0, &intersection_point1, &ratio0,
																				&ratio1, capsule0->getpLineSegment(),
																				capsule1->getpLineSegment());
	float center_to_center_length = capsule0->getRadius() + capsule1->getRadius();

	// �����̔�r
	bool is_hit = length <= center_to_center_length;

	if (!is_hit) return false;

	// �Փ˃x�N�g���̎Z�o
	Vector3D temp_vector = intersection_point0 - intersection_point1;
	length = center_to_center_length - length;
	if (temp_vector.getLengthSquare() > 0.0f)
	{
		*information0->getpNestingVector() = *temp_vector.ChangeAnyLength(length);
		*information1->getpNestingVector() = -(*information0->getpNestingVector());
	}
	else
	{
		*information0->getpNestingVector() = *active_vector.ChangeAnyLength(length);
		*information1->getpNestingVector() = -(*information0->getpNestingVector());
	}
	return true;
}



bool CollisionCalculation::CollisionJudgmentOfOBBAndOBB(CollisionInformation* information0,
														CollisionInformation* information1,
														OBB* obb0,
														OBB* obb1)
{
	information0 = information0;
	information1 = information1;

	// �������̊m��(�������̔����̒���)
	Vector3D obb0_separation_axis0 = obb0->getForwardLengthVectorHalf();
	Vector3D obb0_separation_axis1 = obb0->getRightLengthVectorHalf();
	Vector3D obb0_separation_axis2 = obb0->getUpLengthVectorHalf();

	Vector3D obb1_separation_axis0 = obb1->getForwardLengthVectorHalf();
	Vector3D obb1_separation_axis1 = obb1->getRightLengthVectorHalf();
	Vector3D obb1_separation_axis2 = obb1->getUpLengthVectorHalf();

	// �������P�ʃx�N�g���̊m��(���x�N�g��)
	Vector3D obb0_normal_separation_axis0 = *obb0->getpForward();
	Vector3D obb0_normal_separation_axis1 = *obb0->getpRight();
	Vector3D obb0_normal_separation_axis2 = *obb0->getpUp();

	Vector3D obb1_normal_separation_axis0 = *obb1->getpForward();
	Vector3D obb1_normal_separation_axis1 = *obb1->getpRight();
	Vector3D obb1_normal_separation_axis2 = *obb1->getpUp();

	// ���҂̒��S�Ԃ̋���
	Vector3D interval_vector = *obb0->getpPosition() - *obb1->getpPosition();

	// �ʏ�̕������Ƃ̏Փ˔���
	if (!DeterminationOfCollisionWithOrdinarySeparationAxis(&obb0_separation_axis0,
															&obb0_normal_separation_axis0,
															&obb1_separation_axis0,
															&obb1_separation_axis1,
															&obb1_separation_axis2,
															&interval_vector)) return false;
	if (!DeterminationOfCollisionWithOrdinarySeparationAxis(&obb0_separation_axis1,
															&obb0_normal_separation_axis1,
															&obb1_separation_axis0,
															&obb1_separation_axis1,
															&obb1_separation_axis2,
															&interval_vector)) return false;
	if (!DeterminationOfCollisionWithOrdinarySeparationAxis(&obb0_separation_axis2,
															&obb0_normal_separation_axis2,
															&obb1_separation_axis0,
															&obb1_separation_axis1,
															&obb1_separation_axis2,
															&interval_vector)) return false;
	if (!DeterminationOfCollisionWithOrdinarySeparationAxis(&obb1_separation_axis0,
															&obb1_normal_separation_axis0,
															&obb0_separation_axis0,
															&obb0_separation_axis1,
															&obb0_separation_axis2,
															&interval_vector)) return false;
	if (!DeterminationOfCollisionWithOrdinarySeparationAxis(&obb1_separation_axis1,
															&obb1_normal_separation_axis1,
															&obb0_separation_axis0,
															&obb0_separation_axis1,
															&obb0_separation_axis2,
															&interval_vector)) return false;
	if (!DeterminationOfCollisionWithOrdinarySeparationAxis(&obb1_separation_axis2,
															&obb1_normal_separation_axis2,
															&obb0_separation_axis0,
															&obb0_separation_axis1,
															&obb0_separation_axis2,
															&interval_vector)) return false;

	// �O�ς̕������Ƃ̏Փ˔���
	if (!DeterminationOfCollisionWithOuterAxisSeparationAxis(&obb0_normal_separation_axis0,
															 &obb1_normal_separation_axis0,
															 &obb0_separation_axis1,
															 &obb0_separation_axis2,
															 &obb1_separation_axis1,
															 &obb1_separation_axis2,
															 &interval_vector)) return false;
	if (!DeterminationOfCollisionWithOuterAxisSeparationAxis(&obb0_normal_separation_axis0,
															 &obb1_normal_separation_axis1,
															 &obb0_separation_axis1,
															 &obb0_separation_axis2,
															 &obb1_separation_axis0,
															 &obb1_separation_axis2,
															 &interval_vector)) return false;
	if (!DeterminationOfCollisionWithOuterAxisSeparationAxis(&obb0_normal_separation_axis0,
															 &obb1_normal_separation_axis2,
															 &obb0_separation_axis1,
															 &obb0_separation_axis2,
															 &obb1_separation_axis0,
															 &obb1_separation_axis1,
															 &interval_vector)) return false;
	if (!DeterminationOfCollisionWithOuterAxisSeparationAxis(&obb0_normal_separation_axis1,
															 &obb1_normal_separation_axis0,
															 &obb0_separation_axis0,
															 &obb0_separation_axis2,
															 &obb1_separation_axis1,
															 &obb1_separation_axis2,
															 &interval_vector)) return false;
	if (!DeterminationOfCollisionWithOuterAxisSeparationAxis(&obb0_normal_separation_axis1,
															 &obb1_normal_separation_axis1,
															 &obb0_separation_axis0,
															 &obb0_separation_axis2,
															 &obb1_separation_axis0,
															 &obb1_separation_axis2,
															 &interval_vector)) return false;
	if (!DeterminationOfCollisionWithOuterAxisSeparationAxis(&obb0_normal_separation_axis1,
															 &obb1_normal_separation_axis2,
															 &obb0_separation_axis0,
															 &obb0_separation_axis2,
															 &obb1_separation_axis0,
															 &obb1_separation_axis1,
															 &interval_vector)) return false;
	if (!DeterminationOfCollisionWithOuterAxisSeparationAxis(&obb0_normal_separation_axis2,
															 &obb1_normal_separation_axis0,
															 &obb0_separation_axis0,
															 &obb0_separation_axis1,
															 &obb1_separation_axis1,
															 &obb1_separation_axis2,
															 &interval_vector)) return false;
	if (!DeterminationOfCollisionWithOuterAxisSeparationAxis(&obb0_normal_separation_axis2,
															 &obb1_normal_separation_axis1,
															 &obb0_separation_axis0,
															 &obb0_separation_axis1,
															 &obb1_separation_axis0,
															 &obb1_separation_axis2,
															 &interval_vector)) return false;
	if (!DeterminationOfCollisionWithOuterAxisSeparationAxis(&obb0_normal_separation_axis2,
															 &obb1_normal_separation_axis2,
															 &obb0_separation_axis0,
															 &obb0_separation_axis1,
															 &obb1_separation_axis0,
															 &obb1_separation_axis1,
															 &interval_vector)) return false;

	return true;
}



void CollisionCalculation::EliminationOfNesting(CollisionInformation* information, Transform* transform)
{
	*transform->getpPosition() += *information->getpNestingVector();
	transform->CreateWorldMatrix();
}



float CollisionCalculation::FroatTruncation(float num)
{
	float shift_num = 10000.0f;
	num *= shift_num;			// ���ɃV�t�g
	num = floorf(num);			// �����_�؂�̂�
	num /= shift_num;			// �E�ɃV�t�g
	return num;
}



bool CollisionCalculation::DetermineWhetherTheRatioIsBetweenZeroAndOne(float ratio)
{
	if (ratio < 0.0f) return false;
	if (ratio > 1.0f) return false;

	return true;
}



bool CollisionCalculation::DetermineWhetherBothRatiosAreBetweenZeroAndOne(float ratio0,
																		  float ratio1)
{
	if (!DetermineWhetherTheRatioIsBetweenZeroAndOne(ratio0)) return false;
	if (!DetermineWhetherTheRatioIsBetweenZeroAndOne(ratio1)) return false;

	return true;
}



bool CollisionCalculation::DetermineWhetherXOfEitherLineSegmentIsZero(LineSegment* line_segment0,
																	  LineSegment* line_segment1)
{
	if (line_segment0->getpPosition()->x == 0) return true;
	if (line_segment1->getpPosition()->x == 0) return true;
	return false;
}



bool CollisionCalculation::DetermineWhetherXOfBothLineSegmentsIsZero(LineSegment* line_segment0,
																	 LineSegment* line_segment1)
{
	if (!line_segment0->getpPosition()->x == 0) return false;
	if (!line_segment1->getpPosition()->x == 0) return false;
	return true;
}



bool CollisionCalculation::DetermineWhetherItIsParallelFromSlope(float slope0,
																 float slope1)
{
	if (slope0 == slope1) return true;
	if (slope0 == -slope1) return true;
	return false;
}



bool CollisionCalculation::DetermineIfItIsLongerThanVector(Vector3D* vector,
														   float length)
{
	return vector->getLengthSquare() <= (length * length);
}



bool CollisionCalculation::DetermineWhetherASphereCollidesAgainstEachSide(Sphere* sphere,
																		  Triangle* triangle)
{
	// 1�߂̕�
	Vector3D temp_vector = *triangle->getpPoint(1) - *triangle->getpPoint(0);
	LineSegment temp_line_segment;
	temp_line_segment.Init(*triangle->getpPoint(0), temp_vector);

	CollisionInformation temp_information0;
	CollisionInformation temp_information1;
	if (CollisionJudgmentOfLineSegmentAndSphere(&temp_information0,
												&temp_information1,
												&temp_line_segment,
												sphere)) return true;

	// 2�߂̕�
	temp_vector = *triangle->getpPoint(2) - *triangle->getpPoint(1);
	temp_line_segment.Init(*triangle->getpPoint(1), temp_vector);
	if (CollisionJudgmentOfLineSegmentAndSphere(&temp_information0,
												&temp_information1,
												&temp_line_segment,
												sphere)) return true;

	// 3�߂̕�
	temp_vector = *triangle->getpPoint(0) - *triangle->getpPoint(2);
	temp_line_segment.Init(*triangle->getpPoint(2), temp_vector);
	if (CollisionJudgmentOfLineSegmentAndSphere(&temp_information0,
												&temp_information1,
												&temp_line_segment,
												sphere)) return true;

	return false;
}



bool CollisionCalculation::DetermineWhetherTheSphereIsSinkingInside(Sphere* sphere,
																	Triangle* triangle)
{
	Vector3D temp_vector = *triangle->getpPlane()->getpNormal() * -1;
	LineSegment temp_line_segment;
	temp_line_segment.Init(*sphere->getpPosition(), temp_vector);

	CollisionInformation temp_information0;
	CollisionInformation temp_information1;
	if (CollisionJudgmentOfLineSegmentAndTriangle(&temp_information0,
												  &temp_information1,
												  &temp_line_segment,
												  triangle)) return true;
	return false;
}



bool CollisionCalculation::DetermineWhetherThePlaneIsParallel(Plane* plane0,
															  Plane* plane1)
{
	float temp_dot = Vector3D::CreateDot(plane0->getpNormal(), plane1->getpNormal());
	if ((temp_dot >= 1.0f) || (temp_dot <= -1.0f)) return false;
	return true;
}



bool CollisionCalculation::DetermineIfATrianglePenetrates(bool* is_hit_segment_one,
														  Triangle* triangle0,
														  Triangle* triangle1)
{
	LineSegment temp_line_segment0;
	temp_line_segment0.Init(*triangle0->getpPoint(0), *triangle0->getpPoint(1) - *triangle1->getpPoint(0));
	LineSegment temp_line_segment1;
	temp_line_segment1.Init(*triangle0->getpPoint(1), *triangle0->getpPoint(2) - *triangle1->getpPoint(1));
	LineSegment temp_line_segment2;
	temp_line_segment2.Init(*triangle0->getpPoint(2), *triangle0->getpPoint(0) - *triangle1->getpPoint(2));

	CollisionInformation temp_information0;
	CollisionInformation temp_information1;
	bool is_hit0 = CollisionJudgmentOfLineSegmentAndTriangle(&temp_information0,
															 &temp_information1,
															 &temp_line_segment0, triangle1);
	bool is_hit1 = CollisionJudgmentOfLineSegmentAndTriangle(&temp_information0,
															 &temp_information1,
															 &temp_line_segment1, triangle1);
	bool is_hit2 = CollisionJudgmentOfLineSegmentAndTriangle(&temp_information0,
															 &temp_information1,
															 &temp_line_segment2, triangle1);

	if (is_hit0 || is_hit1 || is_hit2)
	{
		*is_hit_segment_one = true;
	}
	else
	{
		*is_hit_segment_one = false;
	}

	if ((is_hit0 && is_hit1)) return true;
	if ((is_hit1 && is_hit2)) return true;
	if ((is_hit2 && is_hit0)) return true;

	return false;
}



bool CollisionCalculation::DetermineWhetherTheIntersectionPointIsWithinALineSegment(Vector3D* hit_point,
																					LineSegment* line_segment0,
																					LineSegment* line_segment1,
																					Vector3D intersection_point)
{
	// �䗦�����߂�
	float ratio0 = (intersection_point.y - line_segment0->getpPosition()->y) / line_segment0->getpPosition()->y;
	float ratio1 = (intersection_point.x - line_segment1->getpPosition()->x) / line_segment1->getpPosition()->x;

	// ��_�����������ǂ���
	if (!DetermineWhetherBothRatiosAreBetweenZeroAndOne(ratio0, ratio1)) return false;

	// ��_�̍��W�������ɑ��
	*hit_point = intersection_point;

	return true;
}



bool CollisionCalculation::IntersectionCalculationOf2DLineSegmentAnd2DLineSegmentWhenXIsZero(Vector3D* hit_point,
																							 LineSegment* line_segment0,
																							 LineSegment* line_segment1)
{
	// �Փ˓_�̎Z�o
	Vector3D intersection_point;
	intersection_point.x = line_segment0->getpPosition()->x;
	float slope1 = line_segment1->getSlopeOf2DLineSegment();
	float temp_x1 = intersection_point.x - line_segment1->getpPosition()->x;
	intersection_point.y = (slope1 * temp_x1) + line_segment1->getpPosition()->x;

	return DetermineWhetherTheIntersectionPointIsWithinALineSegment(hit_point,
																	line_segment0,
																	line_segment1,
																	intersection_point);

}



bool CollisionCalculation::IntersectionCalculationOf2DLineSegmentAnd2DLineSegment(Vector3D* hit_point,
																				  LineSegment* line_segment0,
																				  LineSegment* line_segment1)
{
	// �X�������߂�
	float slope0 = line_segment0->getSlopeOf2DLineSegment();
	float slope1 = line_segment1->getSlopeOf2DLineSegment();


	// ���s���̔���
	if (DetermineWhetherItIsParallelFromSlope(slope0, slope1)) return false;

	// �Փ˓_�̎Z�o
	Vector3D intersection_point;
	intersection_point.x = (slope0 * line_segment0->getpPosition()->x - slope1
							* line_segment1->getpPosition()->x
							+ line_segment1->getpPosition()->y
							- line_segment1->getpPosition()->y) / (slope0 - slope1);

	intersection_point.y = slope0 * (intersection_point.x - line_segment0->getpPosition()->x) + line_segment0->getpPosition()->y;

	return DetermineWhetherTheIntersectionPointIsWithinALineSegment(hit_point,
																	line_segment0,
																	line_segment1,
																	intersection_point);
}



bool CollisionCalculation::QuadraticEquationCalculationForLineSegmentsAndSpheres(QuadraticEquation* equation,
																				 LineSegment* line_segment,
																				 Sphere* sphere)
{
	// ���̌������g�p����ׂ�a,b,c�����߂�
	// at^2 + bt + c = 0
	float temp_x = line_segment->getpPosition()->x - sphere->getpPosition()->x;
	float temp_y = line_segment->getpPosition()->y - sphere->getpPosition()->y;
	float temp_z = line_segment->getpPosition()->z - sphere->getpPosition()->z;



	*equation->getpA() = line_segment->getpVector()->getSquareX()
		+ line_segment->getpVector()->getSquareY()
		+ line_segment->getpVector()->getSquareZ();
	*equation->getpB() = 2.0f * (line_segment->getpVector()->x
								 * temp_x + line_segment->getpVector()->y
								 * temp_y + line_segment->getpVector()->z * temp_z);
	*equation->getpC() = (temp_x * temp_x) + (temp_y * temp_y) + (temp_z * temp_z)
		- (sphere->getRadius() * sphere->getRadius());

	// ���̌���������
	if (equation->CalculateTheSolutionFormula()) return true;

	return false;
}



bool CollisionCalculation::QuadraticEquationCalculationForLineSegmentsAndCylinders(QuadraticEquation* equation,
																				   LineSegment* line_segment,
																				   Cylinder* cylinder)
{
	// ���̌������g�p����ׂ�a,b,c�����߂�
	// at^2 + bt + c = 0
	Vector3D tempS = *cylinder->getpVector();

	// �e����ϒl�̎Z�o
	float dot_vector_vector = Vector3D::CreateDot(line_segment->getpVector(), line_segment->getpVector());
	float dot_tempS_vector = Vector3D::CreateDot(&tempS, line_segment->getpVector());
	float dot_position0_vector = Vector3D::CreateDot(cylinder->getpPosition(), line_segment->getpVector());
	float dot_tempS_tempS = Vector3D::CreateDot(&tempS, &tempS);
	float dot_position0_tempS = Vector3D::CreateDot(cylinder->getpPosition(), &tempS);
	float dot_position0_position0 = Vector3D::CreateDot(cylinder->getpPosition(), cylinder->getpPosition());

	// �~�����������Ȃ�
	if (dot_tempS_tempS == 0.0f) return false;


	*equation->getpA() = dot_vector_vector - (dot_tempS_vector * dot_tempS_vector) / dot_tempS_tempS;
	*equation->getpB() = dot_position0_vector - (dot_position0_tempS * dot_tempS_vector) / dot_tempS_tempS;
	*equation->getpC() = dot_position0_position0 - (dot_position0_tempS * dot_position0_tempS) / dot_tempS_tempS;


	// ���̌���������
	if (equation->CalculateTheSolutionFormula()) return true;

	return false;
}



float CollisionCalculation::CalculateTheRatioOfTheFrontInTheLineSegment(float ratio0,
																		float ratio1)
{
	// ��������1�Ԏ�O�̔䗦�����߂�
	float ratio = 2.0f;

	if (DetermineWhetherTheRatioIsBetweenZeroAndOne(ratio0))
	{
		if (ratio0 < ratio)
		{
			ratio = ratio0;
		}
	}
	if (DetermineWhetherTheRatioIsBetweenZeroAndOne(ratio1))
	{
		if (ratio1 < ratio)
		{
			ratio = ratio1;
		}
	}

	return ratio;
}



float CollisionCalculation::CalculateTheDistanceTheLineSegmentReachesThePlane(Vector3D segment_vector,
																			  Plane* plane,
																			  float length)
{
	// �����x�N�g��(���K���ς�)�ƕ��ʖ@���̔��΂���cos�������߂�
	segment_vector.ChangeNormalize();
	Vector3D inverse_normal = *plane->getpNormal() * -1;
	float cos_theta = Vector3D::CreateDot(&segment_vector, &inverse_normal);

	// ���������ʂɓ͂��������Z�o
	return length / cos_theta;
}



void CollisionCalculation::CalculationOfCollisionLineSegment(LineSegment* hit_line_segment,
															 Plane* plane0,
															 Plane* plane1)
{
	// �O�ςɂ���������x�N�g�����쐬

	*hit_line_segment->getpVector() = Vector3D::CreateCross(plane0->getpNormal(), plane1->getpNormal());

	// ���������̎n�_���Z�o
	if (hit_line_segment->getpVector()->z != 0.0f)
	{
		hit_line_segment->getpPosition()->x = (plane0->getpNormal()->y
											   * plane1->getAdjustmetD()
											   - plane1->getpNormal()->y
											   * plane0->getAdjustmetD())
			/ hit_line_segment->getpVector()->z;
		hit_line_segment->getpPosition()->y = (plane1->getpNormal()->x
											   * plane0->getAdjustmetD()
											   - plane0->getpNormal()->x
											   * plane1->getAdjustmetD())
			/ hit_line_segment->getpVector()->z;
		hit_line_segment->getpPosition()->z = 0.0f;
	}
	else if (hit_line_segment->getpVector()->y != 0.0f)
	{
		hit_line_segment->getpPosition()->x = (plane1->getpNormal()->z
											   * plane0->getAdjustmetD()
											   - plane0->getpNormal()->z
											   * plane1->getAdjustmetD())
			/ hit_line_segment->getpVector()->y;
		hit_line_segment->getpPosition()->y = 0.0f;
		hit_line_segment->getpPosition()->z = (plane0->getpNormal()->x
											   * plane1->getAdjustmetD()
											   - plane1->getpNormal()->x
											   * plane0->getAdjustmetD())
			/ hit_line_segment->getpVector()->y;
	}
	else
	{
		hit_line_segment->getpPosition()->x = (plane0->getpNormal()->z
											   * plane1->getAdjustmetD()
											   - plane1->getpNormal()->z
											   * plane0->getAdjustmetD())
			/ hit_line_segment->getpVector()->x;
		hit_line_segment->getpPosition()->y = 0.0f;
		hit_line_segment->getpPosition()->z = (plane1->getpNormal()->y
											   * plane0->getAdjustmetD()
											   - plane0->getpNormal()->y
											   * plane1->getAdjustmetD())
			/ hit_line_segment->getpVector()->x;
	}
}



float CollisionCalculation::CalculateTheLengthOfTheProjectionLineSegment(Vector3D* my_separation_axis,
																		 Vector3D* other_separation_axis0,
																		 Vector3D* other_separation_axis1,
																		 Vector3D* other_separation_axis2)
{

	float r1 = fabsf(Vector3D::CreateDot(my_separation_axis, other_separation_axis0));
	float r2 = fabsf(Vector3D::CreateDot(my_separation_axis, other_separation_axis1));
	float r3 = (other_separation_axis2 != nullptr)
		? fabsf(Vector3D::CreateDot(my_separation_axis, other_separation_axis2)) : 0;

	return r1 + r2 + r3;
}



bool CollisionCalculation::DeterminationOfCollisionWithOrdinarySeparationAxis(Vector3D* my_separation_axis,
																			  Vector3D* my_separation_axis_normal,
																			  Vector3D* other_separation_axis0,
																			  Vector3D* other_separation_axis1,
																			  Vector3D* other_separation_axis2,
																			  Vector3D* interval_vector)
{
	float r_a = my_separation_axis->getLength();
	float r_b = CalculateTheLengthOfTheProjectionLineSegment(my_separation_axis_normal,
															 other_separation_axis0,
															 other_separation_axis1,
															 other_separation_axis2);
	float length = fabsf(Vector3D::CreateDot(interval_vector, my_separation_axis_normal));
	if (length > (r_a + r_b)) return false;
	return true;
}



bool CollisionCalculation::DeterminationOfCollisionWithOuterAxisSeparationAxis(Vector3D* my_separation_axis_normal,
																			   Vector3D* other_separation_axis_normal,
																			   Vector3D* my_separation_axis0,
																			   Vector3D* my_separation_axis1,
																			   Vector3D* other_separation_axis0,
																			   Vector3D* other_separation_axis1,
																			   Vector3D* interval_vector)
{

	Vector3D temp_cross = Vector3D::CreateCross(my_separation_axis_normal,
												other_separation_axis_normal);
	float r_a = CalculateTheLengthOfTheProjectionLineSegment(&temp_cross,
															 my_separation_axis0,
															 my_separation_axis1);
	float r_b = CalculateTheLengthOfTheProjectionLineSegment(&temp_cross,
															 other_separation_axis0,
															 other_separation_axis1);
	float length = fabsf(Vector3D::CreateDot(interval_vector, &temp_cross));
	if (length > (r_a + r_b)) return false;
	return true;
}



float CollisionCalculation::CalculatePowerOfTheShortestDistanceBetween1DLineSegmentAndPoint(float line_segment_min,
																							float line_segment_max,
																							float any_component_of_a_point)
{
	float length = 0.0f;

	// ������菬�����Ƃ�
	if (any_component_of_a_point < line_segment_min)
	{
		length += (line_segment_min - any_component_of_a_point)
			* (line_segment_min - any_component_of_a_point);
	}

	// �������傫���Ƃ�
	if (any_component_of_a_point > line_segment_max)
	{
		length += (line_segment_max - any_component_of_a_point)
			* (line_segment_max - any_component_of_a_point);
	}

	return length;
}



float CollisionCalculation::CalculateTheShortestDistanceBetweenAABBAndAPoint(AABB* aabb, Vector3D* point)
{
	// �����ׂ̂���Ōv�Z���Ă���
	float length = 0.0f;

	// �e���ɑ΂��Ăׂ�����v�Z����
	length += CalculatePowerOfTheShortestDistanceBetween1DLineSegmentAndPoint(aabb->getpMin()->x,
																			  aabb->getpMax()->x,
																			  point->x);
	length += CalculatePowerOfTheShortestDistanceBetween1DLineSegmentAndPoint(aabb->getpMin()->y,
																			  aabb->getpMax()->y,
																			  point->y);
	length += CalculatePowerOfTheShortestDistanceBetween1DLineSegmentAndPoint(aabb->getpMin()->z,
																			  aabb->getpMax()->z,
																			  point->z);

	return (float)sqrt(length);
}



bool CollisionCalculation::IsParallelLine(LineSegment* line0, LineSegment* line1)
{
	// 2���������s���ǂ���( �O�ς̒�����0���ǂ��� )
	Vector3D temp_vector = Vector3D::CreateCross(line0->getpVector(),
												 line1->getpVector());

	// �덷�͈͂��ǂ���
	bool is_error_range = ((-ERROR_RANGE < temp_vector.getLengthSquare())
						   && (temp_vector.getLengthSquare() < ERROR_RANGE));
	if (is_error_range) return true;
	return false;
}



void CollisionCalculation::Clamp0_1(float* ratio)
{
	if (*ratio <= 0.0f)
	{
		*ratio = 0.0f;
	}
	else if (*ratio >= 1.0f)
	{
		*ratio = 1.0f;
	}
}



float CollisionCalculation::CalculateTheShortestDistanceBetweenPointsAndLine(Vector3D* intersection_point,
																			 float* ratio,
																			 Vector3D* point,
																			 LineSegment* line)
{
	// �_�Ɛ����̎n�_�̃x�N�g��
	Vector3D temp_vector = *point - *line->getpPosition();

	// ������0�ȏォ�ǂ���
	if (line->getpVector()->getLengthSquare() > 0.0f)
	{
		// ��_��t�̎Z�o

		*ratio = Vector3D::CreateDot(line->getpVector(), &temp_vector)
			/ Vector3D::CreateDot(line->getpVector(), line->getpVector());
	}
	else
	{
		*ratio = 0.0f;
	}

	// ��_��h�̎Z�o
	*intersection_point = *line->getpPosition() + *line->getpVector() * (*ratio);

	// ������Ԃ�
	temp_vector = *intersection_point - *point;
	return temp_vector.getLength();
}



float CollisionCalculation::CalculateTheShortestDistanceBetweenPointsAndLineSegments(Vector3D* intersection_point,
																					 float* ratio,
																					 Vector3D* point,
																					 LineSegment* line_segment)
{
	// �����̖��[��ۑ�
	Vector3D segment_position1 = line_segment->getAddVectorToPosition();

	// �����Ɠ_�̍ŒZ�������Z�o
	float length = CalculateTheShortestDistanceBetweenPointsAndLine(intersection_point, ratio, point, line_segment);

	// �����̎n�_���_���O���̎�
	if (IsObtuseAnglePoint3(point, line_segment->getpPosition(),
							&segment_position1))
	{
		*intersection_point = *line_segment->getpPosition();

		Vector3D temp_vector = *line_segment->getpPosition() - *point;

		return temp_vector.getLength();
	}

	// �����̏I�_���_���O���̎�
	if (IsObtuseAnglePoint3(point, &segment_position1,
							line_segment->getpPosition()))
	{
		*intersection_point = segment_position1;

		Vector3D temp_vector = *line_segment->getpPosition() - *point;

		return temp_vector.getLength();
	}

	return length;
}



float CollisionCalculation::CalculateTheShortestDistanceBetweenLineAndLine(Vector3D* intersection_point0,
																		   Vector3D* intersection_point1,
																		   float* ratio0,
																		   float* ratio1,
																		   LineSegment* line0,
																		   LineSegment* line1)
{
	// 2���������s
	if (IsParallelLine(line0, line1))
	{
		// ����1�ƒ���0�̍��W�Ƃ̍ŒZ�������Z�o
		float length = CalculateTheShortestDistanceBetweenPointsAndLine(intersection_point1, ratio1,
																		line0->getpPosition(),
																		line1);
		*intersection_point0 = *line0->getpPosition();
		*ratio0 = 0.0f;

		return length;
	}

	// ���s�łȂ�
	Vector3D between_position_vector = *line0->getpPosition()
		- *line1->getpPosition();
	float dot_vector0_vector1 = Vector3D::CreateDot(line0->getpVector(),
													line1->getpVector());
	float dot_vector0_vector0 = line0->getpVector()->getLengthSquare();
	float dot_vector1_vector1 = line1->getpVector()->getLengthSquare();
	float dot_vector0_position = Vector3D::CreateDot(line0->getpVector(),
													 &between_position_vector);
	float dot_vector1_position = Vector3D::CreateDot(line1->getpVector(),
													 &between_position_vector);

	*ratio0 = (dot_vector0_vector1 * dot_vector1_position - dot_vector1_vector1 * dot_vector0_position) / (dot_vector0_vector0 * dot_vector1_vector1 - dot_vector0_vector1 * dot_vector0_vector1);
	*intersection_point0 = *line0->getpPosition() + *line0->getpVector() * (*ratio0);

	Vector3D temp_vector = *intersection_point0 - *line1->getpPosition();

	*ratio1 = Vector3D::CreateDot(line1->getpVector(), &temp_vector)
		/ dot_vector1_vector1;

	*intersection_point1 = *line1->getpPosition() + *line1->getpVector() * (*ratio1);

	temp_vector = *intersection_point1 - *intersection_point0;

	return temp_vector.getLength();
}



float CollisionCalculation::CalculateTheShortestDistanceBetweenLineSegmentAndLineSegment(Vector3D* intersection_point0,
																						 Vector3D* intersection_point1,
																						 float* ratio0,
																						 float* ratio1,
																						 LineSegment* line_segment0,
																						 LineSegment* line_segment1)
{
	// segment0���k�ނ��Ă���
	if (line_segment0->getpPosition()->getLengthSquare() <= 0.0f)
	{
		if (line_segment1->getpVector()->getLengthSquare() <= 0.0f)
		{
			// �_�Ɠ_�̋���
			Vector3D temp_vector = *line_segment1->getpPosition()
				- *line_segment0->getpPosition();
			*intersection_point0 = *line_segment0->getpPosition();
			*intersection_point1 = *line_segment1->getpPosition();
			*ratio0 = 0.0f;
			*ratio1 = 0.0f;

			return temp_vector.getLength();
		}
		else
		{
			// segment0�̍��W��segment1�̍ŒZ����
			float length = CalculateTheShortestDistanceBetweenPointsAndLineSegments(intersection_point1, ratio1, line_segment0->getpPosition(), line_segment1);
			*intersection_point0 = *line_segment0->getpPosition();
			*ratio0 = 0.0f;
			Clamp0_1(ratio1);
			return length;
		}
	}


	// segment1���k�ނ��Ă�
	if (line_segment1->getpVector()->getLengthSquare() <= 0.0f)
	{
		// segment0�̍��W��segment1�̍ŒZ����
		float length = CalculateTheShortestDistanceBetweenPointsAndLineSegments(intersection_point0, ratio0, line_segment1->getpPosition(), line_segment0);
		*intersection_point1 = *line_segment1->getpPosition();
		*ratio1 = 0.0f;
		Clamp0_1(ratio0);
		return length;
	}

	// �������m
	// ���s�̎�
	if (IsParallelLine(line_segment0, line_segment1))
	{
		// �����̒[�_��1��������
		float length = CalculateTheShortestDistanceBetweenPointsAndLineSegments(intersection_point1, ratio1, line_segment0->getpPosition(), line_segment1);
		*intersection_point0 = *line_segment0->getpPosition();
		*ratio0 = 0.0f;

		// t1�����܂��Ă�����ΏI��
		bool within_range = *ratio1 >= 0.0f && *ratio1 <= 1.0f;
		if (within_range) return length;

	}
	else
	{
		// 2�����̍ŒZ���������߂āAt0,t1��������
		float length = CalculateTheShortestDistanceBetweenLineAndLine(intersection_point0, intersection_point1, ratio0, ratio1, line_segment0, line_segment1);

		// �������Ɏ��܂��Ă���ΏI��
		bool within_range = *ratio0 >= 0.0f && *ratio0 <= 1.0f && *ratio1 >= 0.0f && *ratio1 <= 1.0f;
		if (within_range) return length;
	}

	// segment0����t0���N�����v���A�������~�낷
	Clamp0_1(ratio0);
	*intersection_point0 = *line_segment0->getpPosition() + *line_segment0->getpVector() * (*ratio0);
	Vector3D temp_point = *intersection_point0;
	float length = CalculateTheShortestDistanceBetweenPointsAndLineSegments(intersection_point1, ratio1, &temp_point, line_segment1);

	// �~�낵���������������ɂ��邩
	bool within_range = *ratio1 >= 0.0f && *ratio1 <= 1.0f;
	if (within_range) return length;

	// segment1���N�����v���A�������~�낷
	Clamp0_1(ratio1);
	*intersection_point1 = *line_segment1->getpPosition() + *line_segment1->getpVector() * (*ratio1);
	temp_point = *intersection_point1;
	length = CalculateTheShortestDistanceBetweenPointsAndLineSegments(intersection_point0, ratio0, &temp_point, line_segment0);

	// �~�낵���������������ɂ��邩
	within_range = *ratio0 >= 0.0f && *ratio0 <= 1.0f;
	if (within_range) return length;

	// 2�����̒[�_�̋������ŒZ�Ɣ���
	Clamp0_1(ratio0);
	*intersection_point0 = *line_segment0->getpPosition() + *line_segment0->getpVector() * (*ratio0);
	Vector3D temp_vector = *intersection_point1 - *intersection_point0;

	return temp_vector.getLength();
}



void CollisionCalculation::CalculationOfProtrudingVector(Vector3D* overhang_vector,
														 Vector3D* obb_position,
														 Vector3D obb_vector_half,
														 Vector3D obb_axis,
														 Vector3D* point)
{
	// �ӂ̔����̒�����0�ȏォ
	float length_half = obb_vector_half.getLength();
	if (length_half <= 0.0f) return;

	// �_���璼���ɐ������~�낵���Ƃ��̌�_�̈ʒu��\�������x�N�g������Ƃ����䗦���Z�o
	Vector3D temp_vector = *point - *obb_position;
	float ratio = Vector3D::CreateDot(&temp_vector, &obb_axis) / length_half;

	// �͂ݏo���������̃x�N�g�����Z�o
	if (ratio < -1.0f)
	{
		*overhang_vector += (ratio + 1.0f) * (obb_vector_half);
	}
	else if (ratio > 1.0f)
	{
		*overhang_vector += (ratio - 1.0f) * (obb_vector_half);
	}
}



Vector3D CollisionCalculation::CalculateTheShortestDistanceVectorBetweenOBBAndPoint(OBB* obb, Vector3D* point)
{
	// �_��OBB�̍ŒZ�����x�N�g��
	Vector3D shortest_distance;

	// �e���ɑ΂��Ă͂ݏo���������Z�o
	CalculationOfProtrudingVector(&shortest_distance,
								  obb->getpPosition(),
								  obb->getForwardLengthVectorHalf(),
								  *obb->getpForward(),
								  point);

	CalculationOfProtrudingVector(&shortest_distance,
								  obb->getpPosition(),
								  obb->getUpLengthVectorHalf(),
								  *obb->getpUp(),
								  point);

	CalculationOfProtrudingVector(&shortest_distance,
								  obb->getpPosition(),
								  obb->getRightLengthVectorHalf(),
								  *obb->getpRight(),
								  point);
	return shortest_distance;
}



Vector3D CollisionCalculation::CalculateOfNormalFromCollisionPointOfOBB(OBB* obb,
																		Vector3D* collision_point)
{
	// ���������
	if (IsThePointOnTheFrontSideOfThePlane(obb->getpPlaneUp(),
										   collision_point)) return *obb->getpUp();
	// �t���������
	if (IsThePointOnTheFrontSideOfThePlane(obb->getpPlaneInverseUp(),
										   collision_point)) return -(*obb->getpUp());
	// �E��������
	if (IsThePointOnTheFrontSideOfThePlane(obb->getpPlaneRight(),
										   collision_point)) return *obb->getpRight();
	// �t�E��������
	if (IsThePointOnTheFrontSideOfThePlane(obb->getpPlaneInverseRight(),
										   collision_point)) return -(*obb->getpRight());
	// �O��������
	if (IsThePointOnTheFrontSideOfThePlane(obb->getpPlaneForward(),
										   collision_point)) return *obb->getpForward();
	// �t�O��������
	if (IsThePointOnTheFrontSideOfThePlane(obb->getpPlaneInverseForward(),
										   collision_point)) return -(*obb->getpForward());

	return Vector3D(0.0f, 0.0f, 0.0f);
}



float CollisionCalculation::CalculateTheShortestDistanceBetweenPlaneAndPoint(Plane* plane, Vector3D* point)
{
	float shortest_distance = (plane->getpNormal()->x * point->x) 
		+ (plane->getpNormal()->y * point->y)
		+ (plane->getpNormal()->z * point->z) + plane->getAdjustmetD();

	if (fabsf(shortest_distance) <= 0.0001f) shortest_distance = 0.0f;
	return shortest_distance;
}



bool CollisionCalculation::IsThePointOnTheFrontSideOfThePlane(Plane* plane, Vector3D* point)
{
	if (CalculateTheShortestDistanceBetweenPlaneAndPoint(plane, point) < 0.0f) return false;
	return true;
}



bool CollisionCalculation::IsPointsAreIncludedInThePlane(Triangle* triangle, Vector3D* point)
{
	// �C�ӂ̓_����e���_�ւ̃x�N�g�����Z�o
	Vector3D vector0 = *triangle->getpPoint(0) - *point;
	Vector3D vector1 = *triangle->getpPoint(1) - *point;
	Vector3D vector2 = *triangle->getpPoint(2) - *point;


	// 3�p�`�̕ӂ��Ȃ���x�N�g�����Z�o
	Vector3D edge_vector0 = *triangle->getpPoint(0) - *triangle->getpPoint(1);
	Vector3D edge_vector1 = *triangle->getpPoint(1) - *triangle->getpPoint(2);
	Vector3D edge_vector2 = *triangle->getpPoint(2) - *triangle->getpPoint(0);


	// �O�ς̎Z�o
	Vector3D cross_vector0 = Vector3D::CreateCross(&vector0, &edge_vector0);
	Vector3D cross_vector1 = Vector3D::CreateCross(&vector1, &edge_vector1);
	Vector3D cross_vector2 = Vector3D::CreateCross(&vector2, &edge_vector2);

	int zero_vector = 0;

	if (cross_vector0.getLengthSquare() == 0.0f)
	{
		zero_vector++;
	}

	if (cross_vector1.getLengthSquare() == 0.0f)
	{
		zero_vector++;
	}

	if (cross_vector2.getLengthSquare() == 0.0f)
	{
		zero_vector++;
	}

	if (zero_vector >= 2)
	{
		return true;
	}
	else if (zero_vector == 1)
	{
		float dot0 = 0.0f;

		if (cross_vector0.getLengthSquare() == 0.0f)
		{
			// �O�ς̌�����������Ă��邩�̃`�F�b�N
			dot0 = Vector3D::CreateDot(&cross_vector1, &cross_vector2);
		}
		if (cross_vector1.getLengthSquare() == 0.0f)
		{
			// �O�ς̌�����������Ă��邩�̃`�F�b�N
			dot0 = Vector3D::CreateDot(&cross_vector0, &cross_vector2);
		}
		if (cross_vector2.getLengthSquare() == 0.0f)
		{
			// �O�ς̌�����������Ă��邩�̃`�F�b�N
			dot0 = Vector3D::CreateDot(&cross_vector0, &cross_vector1);
		}

		bool is_same_direction = dot0 > 0.0f;

		if (is_same_direction) return true;
	}
	else
	{
		// �O�ς̌�����������Ă��邩�̃`�F�b�N
		float dot0 = Vector3D::CreateDot(&cross_vector0, &cross_vector1);
		float dot1 = Vector3D::CreateDot(&cross_vector1, &cross_vector2);
		float dot2 = Vector3D::CreateDot(&cross_vector0, &cross_vector2);

		bool is_same_direction0 = (dot0 * dot1) > 0.0f;
		bool is_same_direction1 = (dot0 * dot2) > 0.0f;
		bool is_same_direction2 = (dot1 * dot2) > 0.0f;

		int  same_count = 0;
		if (is_same_direction0 == is_same_direction1) same_count++;
		if (is_same_direction0 == is_same_direction2) same_count++;
		if (is_same_direction1 == is_same_direction2) same_count++;

		if (same_count == 3) return true;
	}

	return false;
}



bool CollisionCalculation::IsObtuseAnglePoint3(Vector3D* point0, Vector3D* point1, 
											   Vector3D* point2)
{
	return Vector3D::CreateDotPoint3(point0, point1, point2) <= 0.0f;
}