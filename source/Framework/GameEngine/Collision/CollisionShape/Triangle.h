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
#include "CollisionShapeBase.h"
#include "Plane.h"

#include <Tool/Vector3D.h>



//************************************************************														   
//! @brief   �O�p�`����Class
//!
//! @details �O�p�`���ʂ�Class
//************************************************************
class Triangle : public CollisionShapeBase
{
//====================
// �萔
//====================
private:	
	static const int MAX_POINT_NUM = 3;		//!< �ő�_��


//====================
// �ϐ�
//====================
private:
	Vector3D point_[MAX_POINT_NUM];		//!< �_0
	Plane plane_;						//!< ����


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �_�擾�֐�
	//! @details
	//! @param index �C���f�b�N�X
	//! @retval Vector3D* �_
	//----------------------------------------
	Vector3D* getpPoint(unsigned index);

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
	//! @brief �f�X�g���N�^
	//! @details
	//! @param void �Ȃ�
	//----------------------------------------
	~Triangle();
	
	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param point0 �_0
	//! @param point1 �_1
	//! @param point2 �_2
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init(Vector3D point0, Vector3D point1, Vector3D point2);

	//----------------------------------------
	//! @brief �X�V�֐�
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Update() override;

private:
	//----------------------------------------
	//! @brief �ŏ��l�ƍő�l�Z�o�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void CalculationMinAndMax() override;
};



#endif