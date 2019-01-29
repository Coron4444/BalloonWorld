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
#include "CollisionShapeBase.h"

#include <Tool/Vector3D.h>



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



#endif