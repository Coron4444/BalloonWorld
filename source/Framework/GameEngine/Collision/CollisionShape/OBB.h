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
#include "CollisionShapeBase.h"

#include <Tool/Axis.h>
#include <Tool/Vector3D.h>



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
	Axis axis_;				//!< ���x�N�g��
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
	//! @retval Axis* ���x�N�g��
	//----------------------------------------
	Axis* getpAxis();

	//----------------------------------------
	//! @brief �E�x�N�g���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D �E�x�N�g��
	//----------------------------------------
	Vector3D getRight();

	//----------------------------------------
	//! @brief ��x�N�g���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D ��x�N�g��
	//----------------------------------------
	Vector3D getUp();

	//----------------------------------------
	//! @brief �O�x�N�g���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D �O�x�N�g��
	//----------------------------------------
	Vector3D getForward();

	//----------------------------------------
	//! @brief �E�x�N�g���̔����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D �E�x�N�g���̔���
	//----------------------------------------
	Vector3D getRightHalf();

	//----------------------------------------
	//! @brief ��x�N�g���̔����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D ��x�N�g���̔���
	//----------------------------------------
	Vector3D getUpHalf();

	//----------------------------------------
	//! @brief �O�x�N�g���̔����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D �O�x�N�g���̔���
	//----------------------------------------
	Vector3D getForwardHalf();


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



#endif