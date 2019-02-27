//================================================================================
//!	@file	 CollisionCalculation.h
//!	@brief	 �Փˌv�ZClass
//! @details static
//!	@author  Kai Araki									@date 2018/11/06
//================================================================================
#ifndef	_COLLISION_CALCULATION_H_
#define _COLLISION_CALCULATION_H_



//****************************************
// �N���X�錾
//****************************************
class AABB;
class Capsule;
class Cylinder;
class LineSegment;
class OBB;
class Plane;
class Sphere;
class Triangle;
class QuadraticEquation;
class CollisionInformation;



//************************************************************														   
//! @brief   �Փˌv�ZClass
//!
//! @details �Փˌv�Z��Class(static)
//************************************************************
class CollisionCalculation
{
//====================
// static�֐�
//====================
private:
	static const float ERROR_RANGE;		//!< �덷�͈�


//====================
// static�֐�
//====================
public:
	//----------------------------------------
	//! @brief 2D������2D�����̏Փ˔���֐�
	//! @details
	//! @param *information0 �Փˏ��0
	//! @param *information1 �Փˏ��1
	//! @param *line_segment0 ����
	//! @param *line_segment1 ����
	//! @retval bool �Փ˂��Ă���ꍇtrue
	//----------------------------------------
	static bool CollisionJudgmentOf2DLineSegmentAnd2DLineSegment(CollisionInformation* information0,
																 CollisionInformation* information1,
																 LineSegment* line_segment0,
																 LineSegment* line_segment1);

	//----------------------------------------
	//! @brief �����Ƌ��̏Փ˔���֐�
	//! @details
	//! @param *information0 �Փˏ��0
	//! @param *information1 �Փˏ��1
	//! @param *line_segment ����
	//! @param *sphere       ��
	//! @retval bool �Փ˂��Ă���ꍇtrue
	//----------------------------------------
	static bool CollisionJudgmentOfLineSegmentAndSphere(CollisionInformation* information0,
														CollisionInformation* information1,
														LineSegment* line_segment,
														Sphere* sphere);

	//----------------------------------------
	//! @brief �����ƕ��ʂ̏Փ˔���֐�
	//! @details
	//! @param *information0 �Փˏ��0
	//! @param *information1 �Փˏ��1
	//! @param *line_segment ����
	//! @param *plane        ����
	//! @retval bool �Փ˂��Ă���ꍇtrue
	//----------------------------------------
	static bool CollisionJudgmentOfLineSegmentAndPlane(CollisionInformation* information0,
													   CollisionInformation* information1,
													   LineSegment* line_segment,
													   Plane* plane);

	//----------------------------------------
	//! @brief �����ƎO�p�`���ʂ̏Փ˔���֐�
	//! @details
	//! @param *information0 �Փˏ��0
	//! @param *information1 �Փˏ��1
	//! @param *line_segment ����
	//! @param *triangle     �O�p�`����
	//! @retval bool �Փ˂��Ă���ꍇtrue
	//----------------------------------------
	static bool CollisionJudgmentOfLineSegmentAndTriangle(CollisionInformation* information0,
														  CollisionInformation* information1,
														  LineSegment* line_segment,
														  Triangle* triangle);

	//----------------------------------------
	//! @brief �����Ɖ~���̏Փ˔���֐�
	//! @details
	//! @param *information0 �Փˏ��0
	//! @param *information1 �Փˏ��1
	//! @param *line_segment ����
	//! @param *cylinder     �~��
	//! @retval bool �Փ˂��Ă���ꍇtrue
	//----------------------------------------
	static bool CollisionJudgmentOfLineSegmentAndCylinder(CollisionInformation* information0,
														  CollisionInformation* information1,
														  LineSegment* line_segment,
														  Cylinder* cylinder);

	//----------------------------------------
	//! @brief �����ƃJ�v�Z���̏Փ˔���֐�
	//! @details
	//! @param *information0 �Փˏ��0
	//! @param *information1 �Փˏ��1
	//! @param *line_segment ����
	//! @param *capsule      �J�v�Z��
	//! @retval bool �Փ˂��Ă���ꍇtrue
	//----------------------------------------
	static bool CollisionJudgmentOfLineSegmentAndCapsule(CollisionInformation* information0,
														 CollisionInformation* information1,
														 LineSegment* line_segment,
														 Capsule* capsule);

	//----------------------------------------
	//! @brief ���Ƌ��̏Փ˔���֐�
	//! @details
	//! @param *information0 �Փˏ��0
	//! @param *information1 �Փˏ��1
	//! @param *sphere0      ��
	//! @param *sphere1      ��
	//! @retval bool �Փ˂��Ă���ꍇtrue
	//----------------------------------------
	static bool CollisionJudgmentOfSphereAndSphere(CollisionInformation* information0,
												   CollisionInformation* information1,
												   Sphere* sphere0,
												   Sphere* sphere1);

	//----------------------------------------
	//! @brief ���ƕ��ʂ̏Փ˔���֐�
	//! @details
	//! @param *information0 �Փˏ��0
	//! @param *information1 �Փˏ��1
	//! @param *sphere       ��
	//! @param *plane        ����
	//! @retval bool �Փ˂��Ă���ꍇtrue
	//----------------------------------------
	static bool CollisionJudgmentOfSphereAndPlane(CollisionInformation* information0,
												  CollisionInformation* information1,
												  Sphere* sphere,
												  Plane* plane);

	//----------------------------------------
	//! @brief ���ƎO�p�`���ʂ̏Փ˔���֐�
	//! @details
	//! @param *information0 �Փˏ��0
	//! @param *information1 �Փˏ��1
	//! @param *sphere       ��
	//! @param *triangle     �O�p�`����
	//! @retval bool �Փ˂��Ă���ꍇtrue
	//----------------------------------------
	static bool CollisionJudgmentOfSphereAndTriangle(CollisionInformation* information0,
													 CollisionInformation* information1,
													 Sphere* sphere,
													 Triangle* triangle);

	//----------------------------------------
	//! @brief ���ƃJ�v�Z���̏Փ˔���֐�
	//! @details
	//! @param *information0 �Փˏ��0
	//! @param *information1 �Փˏ��1
	//! @param *sphere       ��
	//! @param *capsule      �J�v�Z��
	//! @retval bool �Փ˂��Ă���ꍇtrue
	//----------------------------------------
	static bool CollisionJudgmentOfSphereAndCapsule(CollisionInformation* information0,
													CollisionInformation* information1,
													Sphere* sphere,
													Capsule* capsule);

	//----------------------------------------
	//! @brief ����OBB�̏Փ˔���֐�
	//! @details
	//! @param *information0 �Փˏ��0
	//! @param *information1 �Փˏ��1
	//! @param *sphere       ��
	//! @param *obb          OBB
	//! @retval bool �Փ˂��Ă���ꍇtrue
	//----------------------------------------
	static bool CollisionJudgmentOfSphereAndOBB(CollisionInformation* information0,
												CollisionInformation* information1,
												Sphere* sphere,
												OBB* obb);

	//----------------------------------------
	//! @brief ���ʂƕ��ʂ̏Փ˔���֐�
	//! @details
	//! @param *information0 �Փˏ��0
	//! @param *information1 �Փˏ��1
	//! @param *plane0       ����
	//! @param *plane1       ����
	//! @retval bool �Փ˂��Ă���ꍇtrue
	//----------------------------------------
	static bool CollisionJudgmentOfPlaneAndPlane(CollisionInformation* information0,
												 CollisionInformation* information1,
												 Plane* plane0,
												 Plane* plane1);

	//----------------------------------------
	//! @brief ���ʂƎO�p�`���ʂ̏Փ˔���֐�
	//! @details
	//! @param *information0 �Փˏ��0
	//! @param *information1 �Փˏ��1
	//! @param *plane        ����
	//! @param *triangle     �O�p�`����
	//! @retval bool �Փ˂��Ă���ꍇtrue
	//----------------------------------------
	static bool CollisionJudgmentOfPlaneAndTriangle(CollisionInformation* information0,
													CollisionInformation* information1,
													Plane* plane,
													Triangle* triangle);

	//----------------------------------------
	//! @brief �O�p�`���ʂƎO�p�`���ʂ̏Փ˔���֐�
	//! @details
	//! @param *information0 �Փˏ��0
	//! @param *information1 �Փˏ��1
	//! @param *triangle0    �O�p�`����
	//! @param *triangle0    �O�p�`����
	//! @retval bool �Փ˂��Ă���ꍇtrue
	//----------------------------------------
	static bool CollisionJudgmentOfTriangleAndTriangle(CollisionInformation* information0,
													   CollisionInformation* information1,
													   Triangle* triangle0,
													   Triangle* triangle1);

	//----------------------------------------
	//! @brief �J�v�Z���ƃJ�v�Z���̏Փ˔���֐�
	//! @details
	//! @param *information0 �Փˏ��0
	//! @param *information1 �Փˏ��1
	//! @param *capsule0     �J�v�Z��
	//! @param *capsule1     �J�v�Z��
	//! @param active_vector �␳�p�x�N�g��
	//! @retval bool �Փ˂��Ă���ꍇtrue
	//----------------------------------------
	static bool CollisionJudgmentOfCapsuleAndCapsule(CollisionInformation* information0,
													 CollisionInformation* information1,
													 Capsule* capsule0,
													 Capsule* capsule1,
													 Vector3D active_vector = {0.0f, 0.0f, 0.0f});

	//----------------------------------------
	//! @brief OBB��OBB�̏Փ˔���֐�
	//! @details
	//! @param *information0 �Փˏ��0
	//! @param *information1 �Փˏ��1
	//! @param *obb0         OBB
	//! @param *obb1         OBB
	//! @retval bool �Փ˂��Ă���ꍇtrue
	//----------------------------------------
	static bool CollisionJudgmentOfOBBAndOBB(CollisionInformation* information0,
											 CollisionInformation* information1,
											 OBB* obb0,
											 OBB* obb1);

	//----------------------------------------
	//! @brief �߂荞�݉����֐�
	//! @details
	//! @param *information �Փˏ��
	//! @param *transform   �߂荞�݂��������������
	//! @retval void �Ȃ�
	//----------------------------------------
	static void EliminationOfNesting(CollisionInformation* information, Transform* transform);

private:
	//----------------------------------------
	//! @brief float�̐؂�̂Ċ֐�
	//! @details
	//! @param num �؂�̂Ă������l
	//! @retval float �؂�̂Ă�float�l
	//----------------------------------------
	static float FroatTruncation(float num);

	//----------------------------------------
	//! @brief �䗦��0~1�̊Ԃɂ��邩����֐�
	//! @details
	//! @param ratio �䗦
	//! @retval bool �䗦��0~1�̊ԂȂ�true
	//----------------------------------------
	static bool DetermineWhetherTheRatioIsBetweenZeroAndOne(float ratio);

	//----------------------------------------
	//! @brief �����̔䗦��0~1�̊Ԃɂ��邩����֐�
	//! @details
	//! @param ratio0 �䗦
	//! @param ratio1 �䗦
	//! @retval bool �䗦��0~1�̊ԂȂ�true
	//----------------------------------------
	static bool DetermineWhetherBothRatiosAreBetweenZeroAndOne(float ratio0,
															   float ratio1);

	//----------------------------------------
	//! @brief �ǂ��炩�̐�����X��0������֐�
	//! @details
	//! @param *line_segment0 ����
	//! @param *line_segment1 ����
	//! @retval bool �ǂ��炩��X��0�Ȃ�true
	//----------------------------------------
	static bool DetermineWhetherXOfEitherLineSegmentIsZero(LineSegment* line_segment0,
														   LineSegment* line_segment1);

	//----------------------------------------
	//! @brief �����̐�����X��0������֐�
	//! @details
	//! @param *line_segment0 ����
	//! @param *line_segment1 ����
	//! @retval bool ������X��0�Ȃ�true
	//----------------------------------------
	static bool DetermineWhetherXOfBothLineSegmentsIsZero(LineSegment* line_segment0,
														  LineSegment* line_segment1);

	//----------------------------------------
	//! @brief �X�����畽�s������֐�
	//! @details
	//! @param slope0 �X��
	//! @param slope1 �X��
	//! @retval bool ���s�Ȃ�true
	//----------------------------------------
	static bool DetermineWhetherItIsParallelFromSlope(float slope0, float slope1);

	//----------------------------------------
	//! @brief �x�N�g����蒷��������֐�
	//! @details
	//! @param *vector �x�N�g��
	//! @param length  ����
	//! @retval bool �x�N�g����蒷���ꍇtrue
	//----------------------------------------
	static bool DetermineIfItIsLongerThanVector(Vector3D* vector, float length);

	//----------------------------------------
	//! @brief �����e�ӂɏՓ˂��Ă��邩����֐�
	//! @details
	//! @param *sphere   ��
	//! @param *triangle �O�p�`����
	//! @retval bool �Փ˂��Ă���ꍇtrue
	//----------------------------------------
	static bool DetermineWhetherASphereCollidesAgainstEachSide(Sphere* sphere,
															   Triangle* triangle);

	//----------------------------------------
	//! @brief ���������ɂ߂荞��ł��邩����֐�
	//! @details
	//! @param *sphere   ��
	//! @param *triangle �O�p�`����
	//! @retval bool �߂荞��ł���ꍇtrue
	//----------------------------------------
	static bool DetermineWhetherTheSphereIsSinkingInside(Sphere* sphere,
														 Triangle* triangle);

	//----------------------------------------
	//! @brief ���ʂ����s������֐�
	//! @details
	//! @param *plane0 ����
	//! @param *plane1 ����
	//! @retval bool ���s�Ȃ�true
	//----------------------------------------
	static bool DetermineWhetherThePlaneIsParallel(Plane* plane0, Plane* plane1);

	//----------------------------------------
	//! @brief �O�p�`���ʂ��т��Ă��邩����֐�
	//! @details
	//! @param *is_hit_segment_one 1�ӂ��ђʂ��Ă��邩�t���O
	//! @param *triangle0          �O�p�`����
	//! @param *triangle1          �O�p�`����
	//! @retval bool �т��Ă����true
	//----------------------------------------
	static bool DetermineIfATrianglePenetrates(bool* is_hit_segment_one,
											   Triangle* triangle0,
											   Triangle* triangle1);

	//----------------------------------------
	//! @brief ��_��������������֐�
	//! @details
	//! @param *hit_point         �Փ˓_
	//! @param *line_segment0     ����
	//! @param *line_segment1     ����
	//! @param intersection_point ��_
	//! @retval bool �������̏ꍇtrue
	//----------------------------------------
	static bool DetermineWhetherTheIntersectionPointIsWithinALineSegment(Vector3D* hit_point,
																		 LineSegment* line_segment0,
																		 LineSegment* line_segment1,
																		 Vector3D intersection_point);

	//----------------------------------------
	//! @brief X��0�̎���2D������2D�����̌�_�v�Z�֐�
	//! @details
	//! @param *hit_point     �Փ˓_
	//! @param *line_segment0 ����
	//! @param *line_segment1 ����
	//! @retval bool �Փ˂��Ă���ꍇtrue
	//----------------------------------------
	static bool IntersectionCalculationOf2DLineSegmentAnd2DLineSegmentWhenXIsZero(Vector3D* hit_point,
																				  LineSegment* line_segment0,
																				  LineSegment* line_segment1);

	//----------------------------------------
	//! @brief 2D������2D�����̌�_�v�Z�֐�
	//! @details
	//! @param *hit_point     �Փ˓_
	//! @param *line_segment0 ����
	//! @param *line_segment1 ����
	//! @retval bool �Փ˂��Ă���ꍇtrue
	//----------------------------------------
	static bool IntersectionCalculationOf2DLineSegmentAnd2DLineSegment(Vector3D* hit_point,
																	   LineSegment* line_segment0,
																	   LineSegment* line_segment1);

	//----------------------------------------
	//! @brief �����Ƌ���2���������v�Z
	//! @details
	//! @param *equation     2��������
	//! @param *line_segment ����
	//! @param *sphere       ��
	//! @retval bool 2���������̉�������ꍇtrue
	//----------------------------------------
	static bool QuadraticEquationCalculationForLineSegmentsAndSpheres(QuadraticEquation* equation,
																	  LineSegment* line_segment,
																	  Sphere* sphere);

	//----------------------------------------
	//! @brief �����Ɖ~����2���������v�Z
	//! @details
	//! @param *equation     2��������
	//! @param *line_segment ����
	//! @param *cylinder     �~��
	//! @retval bool 2���������̉�������ꍇtrue
	//----------------------------------------
	static bool QuadraticEquationCalculationForLineSegmentsAndCylinders(QuadraticEquation* equation,
																		LineSegment* line_segment,
																		Cylinder* cylinder);

	//----------------------------------------
	//! @brief ��������1�Ԏ�O�̔䗦�̎Z�o�֐�
	//! @details
	//! @param ratio0 �䗦
	//! @param ratio1 �䗦
	//! @retval float 1�Ԏ�O�̔䗦
	//----------------------------------------
	static float CalculateTheRatioOfTheFrontInTheLineSegment(float ratio0, float ratio1);

	//----------------------------------------
	//! @brief ���������ʂɓ͂������̎Z�o�֐�
	//! @details
	//! @param segment_vector �����x�N�g��
	//! @param *plane         ����
	//! @param length         ����
	//! @retval float ���������ʂɓ͂�����
	//----------------------------------------
	static float CalculateTheDistanceTheLineSegmentReachesThePlane(Vector3D segment_vector,
																   Plane* plane,
																   float length);

	//----------------------------------------
	//! @brief �Փː����̎Z�o�֐�
	//! @details
	//! @param *hit_line_segment �Փː���
	//! @param *plane0           ����
	//! @param *plane1           ����
	//! @retval void �Ȃ�
	//----------------------------------------
	static void CalculationOfCollisionLineSegment(LineSegment* hit_line_segment,
												  Plane* plane0,
												  Plane* plane1);

	//----------------------------------------
	//! @brief ���e�����̒����̎Z�o�֐�
	//! @details
	//! @param *my_separation_axis     �����̕�����
	//! @param *other_separation_axis0 ����̕�����
	//! @param *other_separation_axis1 ����̕�����
	//! @param *other_separation_axis2 ����̕�����
	//! @retval float ���e�����̒���
	//----------------------------------------
	static float CalculateTheLengthOfTheProjectionLineSegment(Vector3D* my_separation_axis,
															  Vector3D* other_separation_axis0,
															  Vector3D* other_separation_axis1,
															  Vector3D* other_separation_axis2 = nullptr);

	//----------------------------------------
	//! @brief �ʏ�̕������Ƃ̏Փ˔���֐�
	//! @details
	//! @param *my_separation_axis        �����̕�����
	//! @param *my_separation_axis_normal �����̕������̒P�ʃx�N�g��
	//! @param *other_separation_axis0    ����̕�����
	//! @param *other_separation_axis1    ����̕�����
	//! @param *other_separation_axis2    ����̕�����
	//! @param *interval_vector           ������OBB�Ԃ̃x�N�g��
	//! @retval bool �Փ˂��Ă���ꍇtrue
	//----------------------------------------
	static bool DeterminationOfCollisionWithOrdinarySeparationAxis(Vector3D* my_separation_axis,
																   Vector3D* my_separation_axis_normal,
																   Vector3D* other_separation_axis0,
																   Vector3D* other_separation_axis1,
																   Vector3D* other_separation_axis2,
																   Vector3D* interval_vector);

	//----------------------------------------
	//! @brief �O�ς̕������Ƃ̏Փ˔���֐�
	//! @details
	//! @param *my_separation_axis_normal �����̕������̒P�ʃx�N�g��
	//! @param *my_separation_axis_normal ����̕������̒P�ʃx�N�g��
	//! @param *my_separation_axis0       �����̕�����
	//! @param *my_separation_axis1       �����̕�����
	//! @param *other_separation_axis0    ����̕�����
	//! @param *other_separation_axis1    ����̕�����
	//! @param *interval_vector           ������OBB�Ԃ̃x�N�g��
	//! @retval bool �Փ˂��Ă���ꍇtrue
	//----------------------------------------
	static bool DeterminationOfCollisionWithOuterAxisSeparationAxis(Vector3D* my_separation_axis_normal,
																	Vector3D* other_separation_axis_normal,
																	Vector3D* my_separation_axis0,
																	Vector3D* my_separation_axis1,
																	Vector3D* other_separation_axis0,
																	Vector3D* other_separation_axis1,
																	Vector3D* interval_vector);

	//----------------------------------------
	//! @brief 1D�����Ɠ_�̍ŒZ�����ׂ̂���Z�o�֐�
	//! @details
	//! @param line_segment_min         �����̎n�_
	//! @param line_segment_max         �����̏I�_
	//! @param any_component_of_a_point �_�̔C�ӂ̐���
	//! @retval float 1D�����Ɠ_�̍ŒZ�����ׂ̂���
	//----------------------------------------
	static float CalculatePowerOfTheShortestDistanceBetween1DLineSegmentAndPoint(float line_segment_min,
																				 float line_segment_max,
																				 float any_component_of_a_point);

	//----------------------------------------
	//! @brief AABB�Ɠ_�̍ŒZ�����̎Z�o�֐�
	//! @details
	//! @param *aabb  AABB
	//! @param *point �_
	//! @retval float AABB�Ɠ_�̍ŒZ����
	//----------------------------------------
	float CalculateTheShortestDistanceBetweenAABBAndAPoint(AABB* aabb, Vector3D* point);

	//----------------------------------------
	//! @brief ���������s������֐�
	//! @details
	//! @param *line0 ����0
	//! @param *line1 ����1
	//! @retval bool ���s�Ȃ�true
	//----------------------------------------
	static bool IsParallelLine(LineSegment* line0, LineSegment* line1);

	//----------------------------------------
	//! @brief 0�`1�̊ԂɎ��߂�֐�
	//! @details
	//! @param *ratio �䗦
	//! @retval void �Ȃ�
	//----------------------------------------
	static void Clamp0_1(float* ratio);

	//----------------------------------------
	//! @brief �_�ƒ����̍ŒZ�����̎Z�o�֐�
	//! @details
	//! @param *intersection_point ��_
	//! @param *ratio			   �䗦
	//! @param *point			   �_
	//! @param *line			   ����
	//! @retval float �_�ƒ����̍ŒZ����
	//----------------------------------------
	static float CalculateTheShortestDistanceBetweenPointsAndLine(Vector3D* intersection_point,
																  float* ratio,
																  Vector3D* point,
																  LineSegment* line);

	//----------------------------------------
	//! @brief �_�Ɛ����̍ŒZ�����̎Z�o�֐�
	//! @details
	//! @param *intersection_point ��_
	//! @param *ratio			   �䗦
	//! @param *point			   �_
	//! @param *line_segment	   ����
	//! @retval float �_�Ɛ����̍ŒZ����
	//----------------------------------------
	static float CalculateTheShortestDistanceBetweenPointsAndLineSegments(Vector3D* intersection_point,
																		  float* ratio,
																		  Vector3D* point,
																		  LineSegment* line_segment);

	//----------------------------------------
	//! @brief �����ƒ����̍ŒZ�����̎Z�o�֐�
	//! @details
	//! @param *intersection_point0 ��_0
	//! @param *intersection_point1 ��_1
	//! @param *ratio0				�䗦0
	//! @param *ratio1				�䗦1
	//! @param *line0				����0
	//! @param *line1				����1
	//! @retval float �����ƒ����̍ŒZ����
	//----------------------------------------
	static float CalculateTheShortestDistanceBetweenLineAndLine(Vector3D* intersection_point0,
																Vector3D* intersection_point1,
																float* ratio0,
																float* ratio1,
																LineSegment* line0,
																LineSegment* line1);

	//----------------------------------------
	//! @brief �����Ɛ����̍ŒZ�����̎Z�o�֐�
	//! @details
	//! @param *intersection_point0 ��_0
	//! @param *intersection_point1 ��_1
	//! @param *ratio0				�䗦0
	//! @param *ratio1				�䗦1
	//! @param *line_segment0		����0
	//! @param *line_segment1		����1
	//! @retval float �����Ɛ����̍ŒZ����
	//----------------------------------------
	static float CalculateTheShortestDistanceBetweenLineSegmentAndLineSegment(Vector3D* intersection_point0,
																			  Vector3D* intersection_point1,
																			  float* ratio0,
																			  float* ratio1,
																			  LineSegment* line_segment0,
																			  LineSegment* line_segment1);

	//----------------------------------------
	//! @brief 1���������Ɠ_�̂͂ݏo�������̃x�N�g�����Z�o�֐�
	//! @details
	//! @param *overhang_vector �͂ݏo���x�N�g��
	//! @param *obb_position    OBB���W
	//! @param *obb_vector_half	OBB�����x�N�g��
	//! @param obb_axis		    BB��
	//! @param *point		    �_
	//! @retval void �Ȃ�
	//----------------------------------------
	static void CalculationOfProtrudingVector(Vector3D* overhang_vector,
											  Vector3D* obb_position,
											  Vector3D obb_vector_half,
											  Vector3D obb_axis,
											  Vector3D* point);

	//----------------------------------------
	//! @brief OBB�Ɠ_�̍ŒZ�����x�N�g���̎Z�o�֐�
	//! @details
	//! @param *obb   OBB
	//! @param *point �_
	//! @retval Vector3D �ŒZ�����x�N�g��
	//----------------------------------------
	static Vector3D CalculateTheShortestDistanceVectorBetweenOBBAndPoint(OBB* obb, Vector3D* point);

	//----------------------------------------
	//! @brief OBB�̏Փ˓_����@���x�N�g���̎Z�o�֐�
	//! @details
	//! @param *obb             OBB
	//! @param *collision_point �Փ˓_
	//! @retval Vector3D �@���x�N�g��
	//----------------------------------------
	static Vector3D CalculateOfNormalFromCollisionPointOfOBB(OBB* obb, Vector3D* collision_point);

	//----------------------------------------
	//! @brief ���ʂƓ_�̍ŒZ�����̎Z�o�֐�
	//! @details
	//! @param *plane ����
	//! @param *point �_
	//! @retval float ���ʂƓ_�̍ŒZ����
	//----------------------------------------
	static float CalculateTheShortestDistanceBetweenPlaneAndPoint(Plane* plane, Vector3D* point);

	//----------------------------------------
	//! @brief �_�����ʂ̕\���ɂ��邩����֐�
	//! @details
	//! @param *plane ����
	//! @param *point �_
	//! @retval bool �\�ʂɂ����true
	//----------------------------------------
	static bool IsThePointOnTheFrontSideOfThePlane(Plane* plane, Vector3D* point);

	//----------------------------------------
	//! @brief �_���O�p�`���ʂɊ܂܂�Ă��邩����֐�
	//! @details
	//! @param *triangle �O�p�`����
	//! @param *point    �_
	//! @retval bool �\�ʂɂ����true
	//----------------------------------------
	static bool IsPointsAreIncludedInThePlane(Triangle* triangle, Vector3D* point);

	//----------------------------------------
	//! @brief 3�_�̂Ȃ��p���݊p������֐�
	//! @details
	//! @param *point0 �_0
	//! @param *point1 �_1
	//! @param *point2 �_2
	//! @retval bool �݊p�̗L��
	//----------------------------------------
	static bool IsObtuseAnglePoint3(Vector3D* point0, Vector3D* point1, 
									Vector3D* point2);

//====================
// �����ς݊֐�
//====================
private:
	CollisionCalculation() = delete;
	CollisionCalculation(const CollisionCalculation& class_name) = delete;
	CollisionCalculation& operator = (const CollisionCalculation& class_name) = delete;
};



#endif