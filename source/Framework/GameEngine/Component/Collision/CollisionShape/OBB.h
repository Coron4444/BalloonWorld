//================================================================================
//!	@file	 OBB.h
//!	@brief	 OBBClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================
#ifndef	_OBB_H_
#define _OBB_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "../CollisionShapeBase.h"

#include <Vector3D.h>
#include <Transform\AxisVector\AxisVector.h>



//************************************************************														   
//! @brief   OBBClass
//!
//! @details OBB��Class
//************************************************************
class OBB : public CollisionShapeBase
{
//====================
// �ϐ�
//====================
private:
	Vector3D position_;		//!< ���W
	Vector3D length_;		//!< �e�ӂ̒���
	AxisVector axis_;		//!< ���x�N�g��
	Vector3D math_vector_;	//!< �v�Z�p�x�N�g��


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
	//! @brief �e�ӂ̎擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D* �e�ӂ̒���
	//----------------------------------------
	Vector3D* getpLength();

	//----------------------------------------
	//! @brief ���x�N�g���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D* ���x�N�g��
	//----------------------------------------
	AxisVector* getpAxisVector();

	//----------------------------------------
	//! @brief �E�x�N�g���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D �E�x�N�g��
	//----------------------------------------
	Vector3D getRightVector();

	//----------------------------------------
	//! @brief ��x�N�g���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D ��x�N�g��
	//----------------------------------------
	Vector3D getUpVector();

	//----------------------------------------
	//! @brief �O�x�N�g���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D �O�x�N�g��
	//----------------------------------------
	Vector3D getForwardVector();

	//----------------------------------------
	//! @brief �E�x�N�g���̔����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D �E�x�N�g���̔���
	//----------------------------------------
	Vector3D getRightVectorHalf();

	//----------------------------------------
	//! @brief ��x�N�g���̔����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D ��x�N�g���̔���
	//----------------------------------------
	Vector3D getUpVectorHalf();

	//----------------------------------------
	//! @brief �O�x�N�g���̔����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D �O�x�N�g���̔���
	//----------------------------------------
	Vector3D getForwardVectorHalf();


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �R���X�g���N�^
	//! @details
	//! @param void �Ȃ�
	//----------------------------------------
	OBB();

	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param position ���W
	//! @param length   �e�ӂ̒���
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init(Vector3D position, Vector3D length);
};

//======================================================================
//
// �񃁃��o�֐��錾
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 1���������Ɠ_�̂͂ݏo�������̃x�N�g�������߂�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline void OverhangingPartOBB_Segment1D_Point(Vector3D* shortest_distance_vector,
											   Vector3D* obb_position,
											   Vector3D obb_vector_half,
											   Vector3D obb_axis_vector,
											   Vector3D* point)
{
	// ������0�ȏォ
	float temp_length = obb_vector_half.GetLength();
	if (temp_length <= 0.0f) return;

	// �_���璼���ɐ������~�낵���Ƃ��̌�_�̈ʒu��\���l(t�Ƃ���)���Z�o
	Vector3D temp_vector = *point - *obb_position;
	float t = temp_vector.CreateVectorDot(obb_axis_vector) / temp_length;

	// �͂ݏo���������̃x�N�g�����Z�o
	if (t < -1.0f)
	{
		*shortest_distance_vector += (t + 1.0f) * (obb_vector_half);
	}
	else if (t > 1.0f)
	{
		*shortest_distance_vector += (t - 1.0f) * (obb_vector_half);
	}
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ OBB�Ɠ_�̍ŒZ�����̃x�N�g�������߂�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline Vector3D ShortestDistance_OBB_Point(OBB* obb, Vector3D* point)
{
	// OBB�܂ł̍ŒZ���������߂�x�N�g��
	Vector3D temp_vector;

	// �e���ɑ΂��Ă͂ݏo���������Z�o
	OverhangingPartOBB_Segment1D_Point(&temp_vector,
									   obb->getpPosition(),
									   obb->getForwardVectorHalf(),
									   *obb->getpAxisVector()->GetForawrd(),
									   point);

	OverhangingPartOBB_Segment1D_Point(&temp_vector,
									   obb->getpPosition(),
									   obb->getUpVectorHalf(),
									   *obb->getpAxisVector()->GetUp(),
									   point);

	OverhangingPartOBB_Segment1D_Point(&temp_vector,
									   obb->getpPosition(),
									   obb->getRightVectorHalf(),
									   *obb->getpAxisVector()->GetRight(),
									   point);
	return temp_vector;
}



#endif