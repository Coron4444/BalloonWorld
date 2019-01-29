//================================================================================
//!	@file	 CollisionCalculation.cpp
//!	@brief	 衝突計算Class
//! @details static
//!	@author  Kai Araki									@date 2018/11/06
//================================================================================



//****************************************
// インクルード文
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

#include <Tool/QuadraticEquation.h>



//****************************************
// 定数定義
//****************************************
const float CollisionCalculation::ERROR_RANGE = 0.000001f;



//****************************************
// static関数定義
//****************************************
bool CollisionCalculation::CollisionJudgmentOf2DLineSegmentAnd2DLineSegment(Vector3D* hit_point,
																			LineSegment* line_segment0,
																			LineSegment* line_segment1)
{
	// X軸方向のベクトルが0かどうか
	if (DetermineWhetherXOfEitherLineSegmentIsZero(line_segment0, line_segment1))
	{
		// 両方のXベクトルが0、つまり平行である 
		if (DetermineWhetherXOfBothLineSegmentsIsZero(line_segment0,
													  line_segment1)) return false;

		// どちらかのXが0の場合
		if (line_segment0->getpVector()->x == 0)
		{
			return IntersectionCalculationOf2DLineSegmentAnd2DLineSegmentWhenXIsZero(hit_point,
																					 line_segment0,
																					 line_segment1);
		}
		else
		{
			return IntersectionCalculationOf2DLineSegmentAnd2DLineSegmentWhenXIsZero(hit_point,
																					 line_segment1,
																					 line_segment0);
		}

	}
	else
	{
		return IntersectionCalculationOf2DLineSegmentAnd2DLineSegment(hit_point,
																	  line_segment0,
																	  line_segment1);
	}

}



bool CollisionCalculation::CollisionJudgmentOfLineSegmentAndSphere(Vector3D* hit_point,
																   LineSegment* line_segment,
																   Sphere* sphere)
{
	// 二次方程式の計算
	QuadraticEquation equation;

	// 二次方程式に解があるか
	bool is_calculable = QuadraticEquationCalculationForLineSegmentsAndSpheres(&equation,
																			   line_segment,
																			   sphere);
	if (!is_calculable) return false;

	// 線分内の1番手前の比率を求める
	float ratio = CalculateTheRatioOfTheFrontInTheLineSegment(equation.getAnswer0(),
															  equation.getAnswer1());
	if (!DetermineWhetherTheRatioIsBetweenZeroAndOne(ratio)) return false;

	// 衝突点の算出
	if (hit_point)
	{
		*line_segment->getpVector() *= ratio;
		*hit_point = line_segment->getAddVectorToPosition();
	}
	return true;
}



bool CollisionCalculation::CollisionJudgmentOfLineSegmentAndPlane(Vector3D* hit_point,
																  LineSegment* line_segment,
																  Plane* plane)
{
	// 表裏チェック

	float temp_dot = Vector3D::CreateDot(line_segment->getpVector(), plane->getpNormal());
	if (temp_dot >= 0.0f) return false;

	// 線分始点と平面との距離を算出
	float length = CalculateTheShortestDistanceBetweenPlaneAndPoint(plane, line_segment->getpPosition());

	// 距離と線分の比較
	if (DetermineIfItIsLongerThanVector(line_segment->getpVector(),
										length)) return false;

	// 線分が平面に届く距離を算出
	float temp_length = CalculateTheDistanceTheLineSegmentReachesThePlane(*line_segment->getpVector(),
																		  plane,
																		  length);
	if (DetermineIfItIsLongerThanVector(line_segment->getpVector(),
										temp_length)) return false;

	// 衝突点の算出
	if (hit_point)
	{
		line_segment->getpVector()->ChangeAnyLength(length);
		*hit_point = line_segment->getAddVectorToPosition();
	}
	return true;
}



bool CollisionCalculation::CollisionJudgmentOfLineSegmentAndTriangle(Vector3D* hit_point,
																	 LineSegment* line_segment,
																	 Triangle* triangle)
{
	// 無限平面との当たり判定
	Vector3D temp_position;
	if (!CollisionJudgmentOfLineSegmentAndPlane(&temp_position, line_segment, triangle->getpPlane())) return false;

	// 交点が3角形内かの判定
	if (!IsPointsAreIncludedInThePlane(triangle, &temp_position)) return false;

	// 衝突点の算出
	if (hit_point)
	{
		*hit_point = temp_position;
	}
	return true;
}



bool CollisionCalculation::CollisionJudgmentOfLineSegmentAndCylinder(Vector3D* hit_point,
																	 LineSegment* line_segment,
																	 Cylinder* cylinder)
{
	// 二次方程式の計算
	QuadraticEquation equation;

	// 二次方程式に解があるか
	bool is_calculable = QuadraticEquationCalculationForLineSegmentsAndCylinders(&equation,
																				 line_segment,
																				 cylinder);
	if (!is_calculable) return false;

	// 線分内の1番手前の比率を求める
	float ratio = CalculateTheRatioOfTheFrontInTheLineSegment(equation.getAnswer0(),
															  equation.getAnswer1());
	if (!DetermineWhetherTheRatioIsBetweenZeroAndOne(ratio)) return false;

	// 衝突点の算出
	if (hit_point)
	{
		*line_segment->getpVector() *= ratio;
		*hit_point = line_segment->getAddVectorToPosition();
	}
	return true;
}



bool CollisionCalculation::CollisionJudgmentOfLineSegmentAndCapsule(Vector3D* hit_point,
																	LineSegment* line_segment,
																	Capsule* capsule)
{
	Vector3D temp_hit_position;

	// 前半球と衝突しているか？
	if (CollisionJudgmentOfLineSegmentAndSphere(&temp_hit_position, line_segment,
												capsule->getpSphere0()))
	{
		// 鈍角かどうか
		if (IsObtuseAnglePoint3(capsule->getpSphere1()->getpPosition(),
										  capsule->getpSphere0()->getpPosition(),
										  &temp_hit_position))
		{
			// 衝突点の算出
			if (hit_point)
			{
				*hit_point = temp_hit_position;
			}
			return true;
		}
	}

	// 後半球と衝突しているか？
	if (CollisionJudgmentOfLineSegmentAndSphere(&temp_hit_position, line_segment, capsule->getpSphere1()))
	{
		// 鈍角かどうか
		if (IsObtuseAnglePoint3(capsule->getpSphere0()->getpPosition(),
										  capsule->getpSphere1()->getpPosition(),
										  &temp_hit_position))
		{
			// 衝突点の算出
			if (hit_point)
			{
				*hit_point = temp_hit_position;
			}
			return true;
		}
	}

	// 円柱と衝突しているか？
	if (CollisionJudgmentOfLineSegmentAndCylinder(&temp_hit_position, line_segment,
												  capsule->getpCylinder()))
	{
		// 全て鋭角かどうか
		if (!IsObtuseAnglePoint3(capsule->getpSphere0()->getpPosition(),
										   capsule->getpSphere1()->getpPosition(),
										   &temp_hit_position)) return false;
		if (!IsObtuseAnglePoint3(capsule->getpSphere1()->getpPosition(),
										   capsule->getpSphere0()->getpPosition(),
										   &temp_hit_position)) return false;

						// 衝突点の算出
		if (hit_point)
		{
			*hit_point = temp_hit_position;
		}
		return true;
	}

	return false;
}



bool CollisionCalculation::CollisionJudgmentOfSphereAndSphere(Vector3D* hit_vector,
															  Sphere* sphere0,
															  Sphere* sphere1)
{
	// 中心間距離と半径の合計による衝突判定
	Vector3D center_to_center_vector = *sphere0->getpPosition() - *sphere1->getpPosition();
	float two_radius = sphere0->getRadius() + sphere1->getRadius();

	if (!DetermineIfItIsLongerThanVector(&center_to_center_vector,
										 two_radius)) return false;

	// 衝突ベクトルの算出
	if (hit_vector)
	{
		float length = two_radius - center_to_center_vector.getLength();
		*hit_vector = *center_to_center_vector.ChangeAnyLength(length);
	}
	return true;
}



bool CollisionCalculation::CollisionJudgmentOfSphereAndPlane(Vector3D* hit_vector,
															 Sphere* sphere,
															 Plane* plane)
{
	// 平面と球の中心距離と半径との判定
	float temp_length = CalculateTheShortestDistanceBetweenPlaneAndPoint(plane, sphere->getpPosition());
	if (!(sphere->getRadius() > temp_length)) return false;

	// 衝突ベクトルの算出
	if (hit_vector)
	{
		temp_length = sphere->getRadius() - CalculateTheShortestDistanceBetweenPlaneAndPoint(plane, sphere->getpPosition());
		Vector3D temp_vector = *plane->getpNormal();
		*hit_vector = *temp_vector.ChangeAnyLength(temp_length);
	}
	return true;
}



bool CollisionCalculation::CollisionJudgmentOfSphereAndTriangle(Vector3D* hit_vector,
																Sphere* sphere,
																Triangle* triangle)
{
	// 無限平面との衝突判定
	Vector3D temp_hit_vector;
	if (!CollisionJudgmentOfSphereAndPlane(&temp_hit_vector, sphere, triangle->getpPlane())) return false;

	// 三角形の各辺が衝突しているか
	if (DetermineWhetherASphereCollidesAgainstEachSide(sphere, triangle))
	{
		// 衝突ベクトルの算出
		if (hit_vector)
		{
			*hit_vector = temp_hit_vector;
		}
		return true;
	}

	// 球が三角形の内側にめり込んでいるか
	if (DetermineWhetherTheSphereIsSinkingInside(sphere, triangle))
	{
		// 衝突ベクトルの算出
		if (hit_vector)
		{
			*hit_vector = temp_hit_vector;
		}
		return true;
	}
	return false;
}



bool CollisionCalculation::CollisionJudgmentOfSphereAndCapsule(Vector3D* hit_vector,
															   Sphere* sphere,
															   Capsule* capsule)
{
	// 球の中心とカプセルとの距離を算出
	Vec3  intersection_point;
	float ratio;
	float length = CalculateTheShortestDistanceBetweenPointsAndLineSegments(&intersection_point,
																			&ratio,
																			sphere->getpPosition(),
																			capsule->getpLineSegment());

	// 距離と2つの半径との合計の比較
	float two_radius = sphere->getRadius() + capsule->getRadius();
	if (length > two_radius) return false;

	// 衝突ベクトルの算出
	if (hit_vector)
	{
		length = two_radius - length;
		*hit_vector = *sphere->getpPosition() - intersection_point;
		hit_vector->ChangeAnyLength(length);
	}

	return true;
}



bool CollisionCalculation::CollisionJudgmentOfSphereAndOBB(Vector3D* hit_vector,
														   Sphere* sphere,
														   OBB* obb)
{
	// 球とOBBの最短距離のベクトルを算出
	Vector3D temp_vector = CalculateTheShortestDistanceVectorBetweenOBBAndPoint(obb, sphere->getpPosition());

	// 距離と半径の比較
	if (FroatTruncation(temp_vector.getLength()) > sphere->getRadius()) return false;

	// 衝突ベクトルの算出
	if (hit_vector)
	{
		float length = sphere->getRadius() - temp_vector.getLength();
		*hit_vector = temp_vector;
		hit_vector->ChangeAnyLength(length);
	}
	return true;
}



bool CollisionCalculation::CollisionJudgmentOfPlaneAndPlane(LineSegment* hit_line_segment,
															Plane* plane0,
															Plane* plane1)
{
	// 平面の法線を用いて、両者が平行であるかの確認をする(衝突するかの確認)
	if (!DetermineWhetherThePlaneIsParallel(plane0, plane1)) return false;

	// 交差線分を求める
	if (hit_line_segment != nullptr)
	{
		CalculationOfCollisionLineSegment(hit_line_segment, plane0, plane1);
	}

	return true;
}



bool CollisionCalculation::CollisionJudgmentOfPlaneAndTriangle(Plane* plane,
															   Triangle* triangle)
{
	int side0 = (int)CalculateTheShortestDistanceBetweenPlaneAndPoint(plane, triangle->getpPoint0());
	int side1 = (int)CalculateTheShortestDistanceBetweenPlaneAndPoint(plane, triangle->getpPoint1());

	// この2点が両方同じ側か
	if ((side0 && !side1) || (!side0 && side1)) return true;

	int side2 = (int)CalculateTheShortestDistanceBetweenPlaneAndPoint(plane, triangle->getpPoint2());

	// この2点が両方同じ側か
	if ((side1 && !side2) || (!side1 && side2)) return true;

	return false;
}



bool CollisionCalculation::CollisionJudgmentOfTriangleAndTriangle(Triangle* triangle0,
																  Triangle* triangle1)
{
	bool is_hit_segment_one = false;

	// 片方の三角形がもう片方を貫いているか
	if (DetermineIfATrianglePenetrates(&is_hit_segment_one,
									   triangle0, triangle1)) return true;

	// もう片方をチェック
	if (DetermineIfATrianglePenetrates(&is_hit_segment_one,
									   triangle1, triangle0)) return true;

	// お互いに1辺が貫通しているか
	if (is_hit_segment_one) return true;

	return false;
}



bool CollisionCalculation::CollisionJudgmentOfCapsuleAndCapsule(Vector3D* hit_vector,
																Capsule* capsule0,
																Capsule* capsule1,
																Vector3D active_vector)
{
	Vector3D intersection_point0;
	Vector3D intersection_point1;
	float ratio0;
	float ratio1;

	// 線分間の最短距離と半径の合計を算出
	float length = CalculateTheShortestDistanceBetweenLineSegmentAndLineSegment(&intersection_point0, &intersection_point1, &ratio0,
																				&ratio1, capsule0->getpLineSegment(),
																				capsule1->getpLineSegment());
	float center_to_center_length = capsule0->getRadius() + capsule1->getRadius();

	// 長さの比較
	bool is_hit = length <= center_to_center_length;

	if (!is_hit) return false;

	// 衝突ベクトルの算出
	if (hit_vector)
	{
		Vector3D temp_vector = intersection_point0 - intersection_point1;

		length = center_to_center_length - length;

		if (temp_vector.getLengthSquare() > 0.0f)
		{
			*hit_vector = *temp_vector.ChangeAnyLength(length);
		}
		else
		{
			*hit_vector = *active_vector.ChangeAnyLength(length);
		}
	}
	return true;
}



bool CollisionCalculation::CollisionJudgmentOfOBBAndOBB(Vector3D* hit_vector,
														OBB* obb0,
														OBB* obb1)
{
	hit_vector = hit_vector;

	// 分離軸の確保(軸方向の半分の長さ)
	Vector3D obb0_separation_axis0 = obb0->getForwardHalf();
	Vector3D obb0_separation_axis1 = obb0->getRightHalf();
	Vector3D obb0_separation_axis2 = obb0->getUpHalf();

	Vector3D obb1_separation_axis0 = obb1->getForwardHalf();
	Vector3D obb1_separation_axis1 = obb1->getRightHalf();
	Vector3D obb1_separation_axis2 = obb1->getUpHalf();

	// 分離軸単位ベクトルの確保(軸ベクトル)
	Vector3D obb0_normal_separation_axis0 = *obb0->getpAxis()->getpForawrd();
	Vector3D obb0_normal_separation_axis1 = *obb0->getpAxis()->getpRight();
	Vector3D obb0_normal_separation_axis2 = *obb0->getpAxis()->getpUp();

	Vector3D obb1_normal_separation_axis0 = *obb1->getpAxis()->getpForawrd();
	Vector3D obb1_normal_separation_axis1 = *obb1->getpAxis()->getpRight();
	Vector3D obb1_normal_separation_axis2 = *obb1->getpAxis()->getpUp();

	// 両者の中心間の距離
	Vector3D interval_vector = *obb0->getpPosition() - *obb1->getpPosition();

	// 通常の分離軸との衝突判定
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

	// 外積の分離軸との衝突判定
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



float CollisionCalculation::FroatTruncation(float num)
{
	float SHIFT_NUM = 10000.0f;
	// 左にシフト
	num *= SHIFT_NUM;
	// 小数点切り捨て
	num = floorf(num);
	// 右にシフト
	num /= SHIFT_NUM;

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
	// 1つめの辺
	Vec3 temp_vector = *triangle->getpPoint1() - *triangle->getpPoint0();
	LineSegment temp_line_segment;
	temp_line_segment.Init(*triangle->getpPoint0(), temp_vector);
	if (CollisionJudgmentOfLineSegmentAndSphere(nullptr, &temp_line_segment,
												sphere)) return true;

	// 2つめの辺
	temp_vector = *triangle->getpPoint2() - *triangle->getpPoint1();
	temp_line_segment.Init(*triangle->getpPoint1(), temp_vector);
	if (CollisionJudgmentOfLineSegmentAndSphere(nullptr, &temp_line_segment,
												sphere)) return true;

	// 3つめの辺
	temp_vector = *triangle->getpPoint0() - *triangle->getpPoint2();
	temp_line_segment.Init(*triangle->getpPoint2(), temp_vector);
	if (CollisionJudgmentOfLineSegmentAndSphere(nullptr, &temp_line_segment,
												sphere)) return true;

	return false;
}



bool CollisionCalculation::DetermineWhetherTheSphereIsSinkingInside(Sphere* sphere,
																	Triangle* triangle)
{
	Vec3 temp_vector = *triangle->getpPlane()->getpNormal() * -1;
	LineSegment temp_line_segment;
	temp_line_segment.Init(*sphere->getpPosition(), temp_vector);
	if (CollisionJudgmentOfLineSegmentAndTriangle(nullptr, &temp_line_segment,
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
	temp_line_segment0.Init(*triangle0->getpPoint0(), *triangle0->getpPoint1() - *triangle1->getpPoint0());
	LineSegment temp_line_segment1;
	temp_line_segment1.Init(*triangle0->getpPoint1(), *triangle0->getpPoint2() - *triangle1->getpPoint1());
	LineSegment temp_line_segment2;
	temp_line_segment2.Init(*triangle0->getpPoint2(), *triangle0->getpPoint0() - *triangle1->getpPoint2());

	bool is_hit0 = CollisionJudgmentOfLineSegmentAndTriangle(nullptr, &temp_line_segment0, triangle1);
	bool is_hit1 = CollisionJudgmentOfLineSegmentAndTriangle(nullptr, &temp_line_segment1, triangle1);
	bool is_hit2 = CollisionJudgmentOfLineSegmentAndTriangle(nullptr, &temp_line_segment2, triangle1);

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
	// 比率を求める
	float ratio0 = (intersection_point.y - line_segment0->getpPosition()->y) / line_segment0->getpPosition()->y;
	float ratio1 = (intersection_point.x - line_segment1->getpPosition()->x) / line_segment1->getpPosition()->x;

	// 交点が線分内かどうか
	if (!DetermineWhetherBothRatiosAreBetweenZeroAndOne(ratio0, ratio1)) return false;

	// 交点の座標を引数に代入
	*hit_point = intersection_point;

	return true;
}



bool CollisionCalculation::IntersectionCalculationOf2DLineSegmentAnd2DLineSegmentWhenXIsZero(Vector3D* hit_point,
																							 LineSegment* line_segment0,
																							 LineSegment* line_segment1)
{
	// 衝突点の算出
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
	// 傾きを求める
	float slope0 = line_segment0->getSlopeOf2DLineSegment();
	float slope1 = line_segment1->getSlopeOf2DLineSegment();


	// 平行かの判定
	if (DetermineWhetherItIsParallelFromSlope(slope0, slope1)) return false;

	// 衝突点の算出
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
	// 解の公式を使用する為のa,b,cを求める
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

	// 解の公式を解く
	if (equation->CalculateTheSolutionFormula()) return true;

	return false;
}



bool CollisionCalculation::QuadraticEquationCalculationForLineSegmentsAndCylinders(QuadraticEquation* equation,
																				   LineSegment* line_segment,
																				   Cylinder* cylinder)
{
	// 解の公式を使用する為のa,b,cを求める
	// at^2 + bt + c = 0
	Vector3D tempS = *cylinder->getpVector();

	// 各種内積値の算出
	float dot_vector_vector = Vector3D::CreateDot(line_segment->getpVector(), line_segment->getpVector());
	float dot_tempS_vector = Vector3D::CreateDot(&tempS, line_segment->getpVector());
	float dot_position0_vector = Vector3D::CreateDot(cylinder->getpPosition(), line_segment->getpVector());
	float dot_tempS_tempS = Vector3D::CreateDot(&tempS, &tempS);
	float dot_position0_tempS = Vector3D::CreateDot(cylinder->getpPosition(), &tempS);
	float dot_position0_position0 = Vector3D::CreateDot(cylinder->getpPosition(), cylinder->getpPosition());

	// 円柱が成立しない
	if (dot_tempS_tempS == 0.0f) return false;


	*equation->getpA() = dot_vector_vector - (dot_tempS_vector * dot_tempS_vector) / dot_tempS_tempS;
	*equation->getpB() = dot_position0_vector - (dot_position0_tempS * dot_tempS_vector) / dot_tempS_tempS;
	*equation->getpC() = dot_position0_position0 - (dot_position0_tempS * dot_position0_tempS) / dot_tempS_tempS;


	// 解の公式を解く
	if (equation->CalculateTheSolutionFormula()) return true;

	return false;
}



float CollisionCalculation::CalculateTheRatioOfTheFrontInTheLineSegment(float ratio0,
																		float ratio1)
{
	// 線分内の1番手前の比率を求める
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
	// 線分ベクトル(正規化済み)と平面法線の反対からcosΘを求める
	segment_vector.ChangeNormalize();
	Vector3D inverse_normal = *plane->getpNormal() * -1;
	float cos_theta = Vector3D::CreateDot(&segment_vector, &inverse_normal);

	// 線分が平面に届く距離を算出
	return length / cos_theta;
}



void CollisionCalculation::CalculationOfCollisionLineSegment(LineSegment* hit_line_segment,
															 Plane* plane0,
															 Plane* plane1)
{
	// 外積により交差するベクトルを作成

	*hit_line_segment->getpVector() = Vector3D::CreateCross(plane0->getpNormal(), plane1->getpNormal());

	// 交差線分の始点を算出
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

	// 線分より小さいとき
	if (any_component_of_a_point < line_segment_min)
	{
		length += (line_segment_min - any_component_of_a_point)
			* (line_segment_min - any_component_of_a_point);
	}

	// 線分より大きいとき
	if (any_component_of_a_point > line_segment_max)
	{
		length += (line_segment_max - any_component_of_a_point)
			* (line_segment_max - any_component_of_a_point);
	}

	return length;
}



float CollisionCalculation::CalculateTheShortestDistanceBetweenAABBAndAPoint(AABB* aabb, Vector3D* point)
{
	// 長さのべき乗で計算していく
	float length = 0.0f;

	// 各軸に対してべき乗を計算する
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
	// 2直線が平行かどうか( 外積の長さが0かどうか )
	Vector3D temp_vector = Vector3D::CreateCross(line0->getpVector(),
												 line1->getpVector());

	// 誤差範囲かどうか
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



float CollisionCalculation::CalculateTheShortestDistanceBetweenPointsAndLine(Vec3* intersection_point,
																			 float* ratio,
																			 Vector3D* point,
																			 LineSegment* line)
{
	// 点と線分の始点のベクトル
	Vector3D temp_vector = *point - *line->getpPosition();

	// 線分が0以上かどうか
	if (line->getpVector()->getLengthSquare() > 0.0f)
	{
		// 交点のtの算出

		*ratio = Vector3D::CreateDot(line->getpVector(), &temp_vector)
			/ Vector3D::CreateDot(line->getpVector(), line->getpVector());
	}
	else
	{
		*ratio = 0.0f;
	}

	// 交点のhの算出
	*intersection_point = *line->getpPosition() + *line->getpVector() * (*ratio);

	// 距離を返す
	temp_vector = *intersection_point - *point;
	return temp_vector.getLength();
}



float CollisionCalculation::CalculateTheShortestDistanceBetweenPointsAndLineSegments(Vec3* intersection_point,
																					 float* ratio,
																					 Vector3D* point,
																					 LineSegment* line_segment)
{
	// 線分の末端を保存
	Vec3 segment_position1 = line_segment->getAddVectorToPosition();

	// 直線と点の最短距離を算出
	float length = CalculateTheShortestDistanceBetweenPointsAndLine(intersection_point, ratio, point, line_segment);

	// 線分の始点より点が外側の時
	if (IsObtuseAnglePoint3(point, line_segment->getpPosition(),
									  &segment_position1))
	{
		*intersection_point = *line_segment->getpPosition();

		Vector3D temp_vector = *line_segment->getpPosition() - *point;

		return temp_vector.getLength();
	}

	// 線分の終点より点が外側の時
	if (IsObtuseAnglePoint3(point, &segment_position1,
									  line_segment->getpPosition()))
	{
		*intersection_point = segment_position1;

		Vector3D temp_vector = *line_segment->getpPosition() - *point;

		return temp_vector.getLength();
	}

	return length;
}



float CollisionCalculation::CalculateTheShortestDistanceBetweenLineAndLine(Vec3* intersection_point0,
																		   Vec3* intersection_point1,
																		   float* ratio0,
																		   float* ratio1,
																		   LineSegment* line0,
																		   LineSegment* line1)
{
	// 2直線が平行
	if (IsParallelLine(line0, line1))
	{
		// 直線1と直線0の座標との最短距離を算出
		float length = CalculateTheShortestDistanceBetweenPointsAndLine(intersection_point1, ratio1,
																		line0->getpPosition(),
																		line1);
		*intersection_point0 = *line0->getpPosition();
		*ratio0 = 0.0f;

		return length;
	}

	// 平行でない
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



float CollisionCalculation::CalculateTheShortestDistanceBetweenLineSegmentAndLineSegment(Vec3* intersection_point0,
																						 Vec3* intersection_point1,
																						 float* ratio0,
																						 float* ratio1,
																						 LineSegment* line_segment0,
																						 LineSegment* line_segment1)
{
	// segment0が縮退している
	if (line_segment0->getpPosition()->getLengthSquare() <= 0.0f)
	{
		if (line_segment1->getpVector()->getLengthSquare() <= 0.0f)
		{
			// 点と点の距離
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
			// segment0の座標とsegment1の最短距離
			float length = CalculateTheShortestDistanceBetweenPointsAndLineSegments(intersection_point1, ratio1, line_segment0->getpPosition(), line_segment1);
			*intersection_point0 = *line_segment0->getpPosition();
			*ratio0 = 0.0f;
			Clamp0_1(ratio1);
			return length;
		}
	}


	// segment1が縮退してる
	if (line_segment1->getpVector()->getLengthSquare() <= 0.0f)
	{
		// segment0の座標とsegment1の最短距離
		float length = CalculateTheShortestDistanceBetweenPointsAndLineSegments(intersection_point0, ratio0, line_segment1->getpPosition(), line_segment0);
		*intersection_point1 = *line_segment1->getpPosition();
		*ratio1 = 0.0f;
		Clamp0_1(ratio0);
		return length;
	}

	// 線分同士
	// 平行の時
	if (IsParallelLine(line_segment0, line_segment1))
	{
		// 垂線の端点の1つを仮決定
		float length = CalculateTheShortestDistanceBetweenPointsAndLineSegments(intersection_point1, ratio1, line_segment0->getpPosition(), line_segment1);
		*intersection_point0 = *line_segment0->getpPosition();
		*ratio0 = 0.0f;

		// t1が収まってい居れば終了
		bool within_range = *ratio1 >= 0.0f && *ratio1 <= 1.0f;
		if (within_range) return length;

	}
	else
	{
		// 2直線の最短距離を求めて、t0,t1を仮決定
		float length = CalculateTheShortestDistanceBetweenLineAndLine(intersection_point0, intersection_point1, ratio0, ratio1, line_segment0, line_segment1);

		// 線分内に収まっていれば終了
		bool within_range = *ratio0 >= 0.0f && *ratio0 <= 1.0f && *ratio1 >= 0.0f && *ratio1 <= 1.0f;
		if (within_range) return length;
	}

	// segment0側のt0をクランプし、垂線を降ろす
	Clamp0_1(ratio0);
	*intersection_point0 = *line_segment0->getpPosition() + *line_segment0->getpVector() * (*ratio0);
	Vector3D temp_point = *intersection_point0;
	float length = CalculateTheShortestDistanceBetweenPointsAndLineSegments(intersection_point1, ratio1, &temp_point, line_segment1);

	// 降ろした垂線が線分内にあるか
	bool within_range = *ratio1 >= 0.0f && *ratio1 <= 1.0f;
	if (within_range) return length;

	// segment1をクランプし、垂線を降ろす
	Clamp0_1(ratio1);
	*intersection_point1 = *line_segment1->getpPosition() + *line_segment1->getpVector() * (*ratio1);
	temp_point = *intersection_point1;
	length = CalculateTheShortestDistanceBetweenPointsAndLineSegments(intersection_point0, ratio0, &temp_point, line_segment0);

	// 降ろした垂線が線分内にあるか
	within_range = *ratio0 >= 0.0f && *ratio0 <= 1.0f;
	if (within_range) return length;

	// 2直線の端点の距離が最短と判明
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
	// 長さが0以上か
	float temp_length = obb_vector_half.getLength();
	if (temp_length <= 0.0f) return;

	// 点から直線に垂線を降ろしたときの交点の位置を表す値(tとする)を算出
	Vector3D temp_vector = *point - *obb_position;
	float t = Vector3D::CreateDot(&temp_vector, &obb_axis) / temp_length;

	// はみ出した部分のベクトルを算出
	if (t < -1.0f)
	{
		*overhang_vector += (t + 1.0f) * (obb_vector_half);
	}
	else if (t > 1.0f)
	{
		*overhang_vector += (t - 1.0f) * (obb_vector_half);
	}
}



Vector3D CollisionCalculation::CalculateTheShortestDistanceVectorBetweenOBBAndPoint(OBB* obb, Vector3D* point)
{
	// OBBまでの最短距離を求めるベクトル
	Vector3D temp_vector;

	// 各軸に対してはみ出し部分を算出
	CalculationOfProtrudingVector(&temp_vector,
								  obb->getpPosition(),
								  obb->getForwardHalf(),
								  *obb->getpAxis()->getpForawrd(),
								  point);

	CalculationOfProtrudingVector(&temp_vector,
								  obb->getpPosition(),
								  obb->getUpHalf(),
								  *obb->getpAxis()->getpUp(),
								  point);

	CalculationOfProtrudingVector(&temp_vector,
								  obb->getpPosition(),
								  obb->getRightHalf(),
								  *obb->getpAxis()->getpRight(),
								  point);
	return temp_vector;
}



float CollisionCalculation::CalculateTheShortestDistanceBetweenPlaneAndPoint(Plane* plane, Vec3* point)
{
	return (plane->getpNormal()->x * point->x)
		+ (plane->getpNormal()->y * point->y)
		+ (plane->getpNormal()->z * point->z) + plane->getAdjustmetD();
}



bool CollisionCalculation::IsThePointOnTheFrontSideOfThePlane(Plane* plane, Vec3* point)
{
	if (CalculateTheShortestDistanceBetweenPlaneAndPoint(plane, point) < 0.0f) return false;
	return true;
}



bool CollisionCalculation::IsPointsAreIncludedInThePlane(Triangle* triangle, Vec3* point)
{
	// 任意の点から各頂点へのベクトルを算出
	Vector3D vector0 = *triangle->getpPoint0() - *point;
	Vector3D vector1 = *triangle->getpPoint1() - *point;
	Vector3D vector2 = *triangle->getpPoint2() - *point;


	// 3角形の辺をなぞるベクトルを算出
	Vector3D edge_vector0 = *triangle->getpPoint0() - *triangle->getpPoint1();
	Vector3D edge_vector1 = *triangle->getpPoint1() - *triangle->getpPoint2();
	Vector3D edge_vector2 = *triangle->getpPoint2() - *triangle->getpPoint0();


	// 外積の算出
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
			// 外積の向きがそろっているかのチェック
			dot0 = Vector3D::CreateDot(&cross_vector1, &cross_vector2);
		}
		if (cross_vector1.getLengthSquare() == 0.0f)
		{
			// 外積の向きがそろっているかのチェック
			dot0 = Vector3D::CreateDot(&cross_vector0, &cross_vector2);
		}
		if (cross_vector2.getLengthSquare() == 0.0f)
		{
			// 外積の向きがそろっているかのチェック
			dot0 = Vector3D::CreateDot(&cross_vector0, &cross_vector1);
		}

		bool is_same_direction = dot0 > 0.0f;

		if (is_same_direction) return true;
	}
	else
	{
		// 外積の向きがそろっているかのチェック
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



bool CollisionCalculation::IsObtuseAnglePoint3(Vec3* point0, Vec3* point1, Vec3* point2)
{
	return Vector3D::CreateDotPoint3(point0, point1, point2) <= 0.0f;
}