//================================================================================
//!	@file	 LineSegment.h
//!	@brief	 ����Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================
#ifndef	_SEGMENT_H_
#define _SEGMENT_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "../CollisionShapeBase.h"

#include <Vector3D.h>



//************************************************************														   
//! @brief   ����Class
//!
//! @details ������Class
//************************************************************
class LineSegment : public CollisionShapeBase
{
//====================
// �ϐ�
//====================
private:
	Vector3D position_;		//!< ���W
	Vector3D vector_;		//!< ����


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief ���W�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D* ���W
	//----------------------------------------
	Vector3D* getpPosition();

	//----------------------------------------
	//! @brief �����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D* ����
	//----------------------------------------
	Vector3D* getpVector();

	//----------------------------------------
	//! @brief �����x�N�g�����Z�ςݍ��W�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D �����x�N�g�����Z�ςݍ��W
	//----------------------------------------
	Vector3D getAddVectorToPosition();

	//----------------------------------------
	//! @brief 2D�����̌X���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float 2D�����̌X��
	//----------------------------------------
	float getSlopeOf2DLineSegment();


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �R���X�g���N�^
	//! @details
	//! @param void �Ȃ�
	//----------------------------------------
	LineSegment();

	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param position ���W
	//! @param vector   ����
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init(Vector3D position, Vector3D vector);
};



//======================================================================
//
// �񃁃��o�֐��錾
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �_�ƒ����ŒZ���������߂�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline float ShortestDistancePointAndLine(Vec3* cross_point, float* t, Vector3D* point,
										  LineSegment* line_segment)
{
	// �_�Ɛ����̎n�_�̃x�N�g��
	Vector3D temp_vector = *point - *line_segment->getpPosition();

	// ������0�ȏォ�ǂ���
	if (line_segment->getpVector()->GetLengthSquare() > 0.0f)
	{
		// ��_��t�̎Z�o
		*t = line_segment->getpVector()->CreateVectorDot(temp_vector)
			/ line_segment->getpVector()->CreateVectorDot(*line_segment->getpVector());
	}
	else
	{
		*t = 0.0f;
	}

	// ��_��h�̎Z�o
	*cross_point = *line_segment->getpPosition() + *line_segment->getpVector() * (*t);

	// ������Ԃ�
	temp_vector = *cross_point - *point;
	return temp_vector.GetLength();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �_�Ɛ����̍ŒZ���������߂�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline float ShortestDistancePointAndLineSegment(Vec3* cross_point, float* t, Vector3D* point,
												 LineSegment* line_segment)
{
	// �����̖��[��ۑ�
	Vec3 segment_position1 = line_segment->getAddVectorToPosition();

	// �����Ɠ_�̍ŒZ�������Z�o
	float length = ShortestDistancePointAndLine(cross_point, t, point, line_segment);


	// �����̎n�_���_���O���̎�
	if (IsObtuseAngle(*point, *line_segment->getpPosition(), segment_position1))
	{
		*cross_point = *line_segment->getpPosition();

		Vector3D temp_vector = *line_segment->getpPosition() - *point;

		return temp_vector.GetLength();
	}

	// �����̏I�_���_���O���̎�
	if (IsObtuseAngle(*point, segment_position1, *line_segment->getpPosition()))
	{
		*cross_point = segment_position1;

		Vector3D temp_vector = *line_segment->getpPosition() - *point;

		return temp_vector.GetLength();
	}

	return length;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 2���������s���̔���֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline bool Is_ParallelSegment(LineSegment* line_segment0, LineSegment* line_segment1)
{
	// 2���������s���ǂ���( �O�ς̒�����0���ǂ��� )
	Vector3D temp_vector = line_segment0->getpVector()
		->CreateVectorCross(*line_segment1->getpVector());


	// �덷�͈͂��ǂ���
	const float num_error = 0.000001f;

	bool is_error_range = -num_error < temp_vector.GetLengthSquare() && temp_vector.GetLengthSquare() < num_error;

	if (is_error_range) return true;

	return false;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �����ƒ����̍ŒZ���������߂�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline float ShortestDistance_Line_Line(Vec3* cross_point0, Vec3* cross_point1,
										float* t0, float* t1,
										LineSegment* line_segment0,
										LineSegment* line_segment1)
{
	// 2���������s
	if (Is_ParallelSegment(line_segment0, line_segment1))
	{
		// ����1�ƒ���0�̍��W�Ƃ̍ŒZ�������Z�o
		float length = ShortestDistancePointAndLine(cross_point1, t1,
													line_segment0->getpPosition(),
													line_segment1);
		*cross_point0 = *line_segment0->getpPosition();
		*t0 = 0.0f;

		return length;
	}

	// ���s�łȂ�
	Vector3D between_position_vector = *line_segment0->getpPosition()
		- *line_segment1->getpPosition();

	float dot_vector0_vector1 = line_segment0->getpVector()
		->CreateVectorDot(*line_segment1->getpVector());
	float dot_vector0_vector0 = line_segment0->getpVector()->GetLengthSquare();
	float dot_vector1_vector1 = line_segment1->getpVector()->GetLengthSquare();
	float dot_vector0_position = line_segment0->getpVector()
		->CreateVectorDot(between_position_vector);
	float dot_vector1_position = line_segment1->getpVector()
		->CreateVectorDot(between_position_vector);

	*t0 = (dot_vector0_vector1 * dot_vector1_position - dot_vector1_vector1 * dot_vector0_position) / (dot_vector0_vector0 * dot_vector1_vector1 - dot_vector0_vector1 * dot_vector0_vector1);
	*cross_point0 = *line_segment0->getpPosition() + *line_segment0->getpVector() * (*t0);

	Vector3D temp_vector = *cross_point0 - *line_segment1->getpPosition();

	*t1 = line_segment1->getpVector()->CreateVectorDot(temp_vector) / dot_vector1_vector1;

	*cross_point1 = *line_segment1->getpPosition() + *line_segment1->getpVector() * (*t1);

	temp_vector = *cross_point1 - *cross_point0;

	return temp_vector.GetLength();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 0�`1�̊ԂɎ��߂�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline void Clamp0_1(float* t)
{
	if (*t <= 0.0f)
	{
		*t = 0.0f;
	}
	else if (*t >= 1.0f)
	{
		*t = 1.0f;
	}
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �����Ɛ����̍ŒZ���������߂�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline float ShortestDistance_Segment_Segment(Vec3* cross_point0,
											  Vec3* cross_point1, float* t0, float* t1,
											  LineSegment* line_segment0,
											  LineSegment* line_segment1)
{
	// segment0���k�ނ��Ă���
	if (line_segment0->getpPosition()->GetLengthSquare() <= 0.0f)
	{
		if (line_segment1->getpVector()->GetLengthSquare() <= 0.0f)
		{
			// �_�Ɠ_�̋���
			Vector3D temp_vector = *line_segment1->getpPosition()
				- *line_segment0->getpPosition();
			*cross_point0 = *line_segment0->getpPosition();
			*cross_point1 = *line_segment1->getpPosition();
			*t0 = 0.0f;
			*t1 = 0.0f;

			return temp_vector.GetLength();
		}
		else
		{
			// segment0�̍��W��segment1�̍ŒZ����
			float length = ShortestDistancePointAndLineSegment(cross_point1, t1, line_segment0->getpPosition(), line_segment1);
			*cross_point0 = *line_segment0->getpPosition();
			*t0 = 0.0f;
			Clamp0_1(t1);
			return length;
		}
	}


	// segment1���k�ނ��Ă�
	if (line_segment1->getpVector()->GetLengthSquare() <= 0.0f)
	{
		// segment0�̍��W��segment1�̍ŒZ����
		float length = ShortestDistancePointAndLineSegment(cross_point0, t0, line_segment1->getpPosition(), line_segment0);
		*cross_point1 = *line_segment1->getpPosition();
		*t1 = 0.0f;
		Clamp0_1(t0);
		return length;
	}

	// �������m
	// ���s�̎�
	if (Is_ParallelSegment(line_segment0, line_segment1))
	{
		// �����̒[�_��1��������
		float length = ShortestDistancePointAndLineSegment(cross_point1, t1, line_segment0->getpPosition(), line_segment1);
		*cross_point0 = *line_segment0->getpPosition();
		*t0 = 0.0f;

		// t1�����܂��Ă�����ΏI��
		bool within_range = *t1 >= 0.0f && *t1 <= 1.0f;
		if (within_range) return length;

	}
	else
	{
		// 2�����̍ŒZ���������߂āAt0,t1��������
		float length = ShortestDistance_Line_Line(cross_point0, cross_point1, t0, t1, line_segment0, line_segment1);

		// �������Ɏ��܂��Ă���ΏI��
		bool within_range = *t0 >= 0.0f && *t0 <= 1.0f && *t1 >= 0.0f && *t1 <= 1.0f;
		if (within_range) return length;
	}

	// segment0����t0���N�����v���A�������~�낷
	Clamp0_1(t0);
	*cross_point0 = *line_segment0->getpPosition() + *line_segment0->getpVector() * (*t0);
	Vector3D temp_point = *cross_point0;
	float length = ShortestDistancePointAndLineSegment(cross_point1, t1, &temp_point, line_segment1);

	// �~�낵���������������ɂ��邩
	bool within_range = *t1 >= 0.0f && *t1 <= 1.0f;
	if (within_range) return length;

	// segment1���N�����v���A�������~�낷
	Clamp0_1(t1);
	*cross_point1 = *line_segment1->getpPosition() + *line_segment1->getpVector() * (*t1);
	temp_point = *cross_point1;
	length = ShortestDistancePointAndLineSegment(cross_point0, t0, &temp_point, line_segment0);

	// �~�낵���������������ɂ��邩
	within_range = *t0 >= 0.0f && *t0 <= 1.0f;
	if (within_range) return length;

	// 2�����̒[�_�̋������ŒZ�Ɣ���
	Clamp0_1(t0);
	*cross_point0 = *line_segment0->getpPosition() + *line_segment0->getpVector() * (*t0);
	Vector3D temp_vector = *cross_point1 - *cross_point0;

	return temp_vector.GetLength();
}



#endif