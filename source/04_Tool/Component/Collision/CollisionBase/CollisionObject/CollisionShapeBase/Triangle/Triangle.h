//================================================================================
//!	@file	 Triangle.h
//!	@brief	 �O�p�`����Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================
#ifndef	_TRIANGLE_H_
#define _TRIANGLE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "../CollisionShapeBase.h"
#include "../Plane/Plane.h"

#include <Vector3D.h>



//************************************************************														   
//! @brief   �O�p�`����Class
//!
//! @details �O�p�`���ʂ�Class
//************************************************************
class Triangle : public CollisionShapeBase
{
//====================
// �ϐ�
//====================
private:
	Vector3D point0_;		//!< �_0
	Vector3D point1_;		//!< �_1
	Vector3D point2_;		//!< �_2
	Plane plane_;			//!< ����


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �_0�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D* �_0
	//----------------------------------------
	Vector3D* getpPoint0();

	//----------------------------------------
	//! @brief �_1�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D* �_1
	//----------------------------------------
	Vector3D* getpPoint1();

	//----------------------------------------
	//! @brief �_2�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D* �_2
	//----------------------------------------
	Vector3D* getpPoint2();

	//----------------------------------------
	//! @brief ���ʎ擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D* ����
	//----------------------------------------
	Plane* getpPlane();


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �R���X�g���N�^
	//! @details
	//! @param void �Ȃ�
	//----------------------------------------
	Triangle();
	
	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param point0 �_0
	//! @param point1 �_1
	//! @param point2 �_2
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init(Vec3 point0, Vec3 point1, Vec3 point2);
};



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �_���O�p���ʂɊ܂܂�Ă��邩�ǂ��� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline bool CheckInnerPoint(Triangle* triangle, Vec3* point)
{
	// �C�ӂ̓_����e���_�ւ̃x�N�g�����Z�o
	Vector3D vector0 = *triangle->getpPoint0() - *point;
	Vector3D vector1 = *triangle->getpPoint1() - *point;
	Vector3D vector2 = *triangle->getpPoint2() - *point;


	// 3�p�`�̕ӂ��Ȃ���x�N�g�����Z�o
	Vector3D edge_vector0 = *triangle->getpPoint0() - *triangle->getpPoint1();
	Vector3D edge_vector1 = *triangle->getpPoint1() - *triangle->getpPoint2();
	Vector3D edge_vector2 = *triangle->getpPoint2() - *triangle->getpPoint0();


	// �O�ς̎Z�o
	Vector3D Cross_vector0 = vector0.CreateVectorCross(edge_vector0);
	Vector3D Cross_vector1 = vector1.CreateVectorCross(edge_vector1);
	Vector3D Cross_vector2 = vector2.CreateVectorCross(edge_vector2);

	int zero_vector = 0;

	if (Cross_vector0.GetLengthSquare() == 0.0f)
	{
		zero_vector++;
	}

	if (Cross_vector1.GetLengthSquare() == 0.0f)
	{
		zero_vector++;
	}

	if (Cross_vector2.GetLengthSquare() == 0.0f)
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

		if (Cross_vector0.GetLengthSquare() == 0.0f)
		{
			// �O�ς̌�����������Ă��邩�̃`�F�b�N
			dot0 = Cross_vector1.CreateVectorDot(Cross_vector2);
		}
		if (Cross_vector1.GetLengthSquare() == 0.0f)
		{
			// �O�ς̌�����������Ă��邩�̃`�F�b�N
			dot0 = Cross_vector0.CreateVectorDot(Cross_vector2);
		}
		if (Cross_vector2.GetLengthSquare() == 0.0f)
		{
			// �O�ς̌�����������Ă��邩�̃`�F�b�N
			dot0 = Cross_vector0.CreateVectorDot(Cross_vector1);
		}

		bool is_same_direction = dot0 > 0.0f;

		if (is_same_direction) return true;
	}
	else
	{
		// �O�ς̌�����������Ă��邩�̃`�F�b�N
		float dot0 = Cross_vector0.CreateVectorDot(Cross_vector1);
		float dot1 = Cross_vector1.CreateVectorDot(Cross_vector2);
		float dot2 = Cross_vector0.CreateVectorDot(Cross_vector2);

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



#endif