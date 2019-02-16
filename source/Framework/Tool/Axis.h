//================================================================================
//!	@file	 Axis.h
//!	@brief	 ��Class
//! @details 
//!	@author  Kai Araki									@date 2018/01/08
//================================================================================
#ifndef	_AXIS_H_
#define _AXIS_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "Vector3D.h"



//************************************************************														   
//! @brief   ��Class
//!
//! @details ����\��Class
//************************************************************
class Axis
{
//====================
// �萔
//====================
private:
	static const Vector3D DEFAULT_FORWARD;	//!< ����O�x�N�g��
	static const Vector3D DEFAULT_UP;		//!< �����x�N�g��
	static const Vector3D DEFAULT_RIGHT;	//!< ����E�x�N�g��


//====================
// �ϐ�
//====================
private:
	Vector3D forward_ = DEFAULT_FORWARD;			//!< �O�x�N�g��
	Vector3D default_forward_ = DEFAULT_FORWARD;	//!< ����O�x�N�g��
	Vector3D up_ = DEFAULT_UP;						//!< ��x�N�g��
	Vector3D default_up_ = DEFAULT_UP;				//!< �����x�N�g��
	Vector3D right_ = DEFAULT_RIGHT;				//!< �E�x�N�g��
	Vector3D default_right_ = DEFAULT_RIGHT;		//!< ����E�x�N�g��


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �O�x�N�g���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D* �O�x�N�g��
	//----------------------------------------
	Vector3D* getpForward();

	//----------------------------------------
	//! @brief ����O�x�N�g���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D* ����O�x�N�g��
	//----------------------------------------
	Vector3D* getpDefaultForward();

	//----------------------------------------
	//! @brief �O�x�N�g���ݒ�֐�
	//! @details
	//! @param value �O�x�N�g��
	//! @retval void �Ȃ�
	//----------------------------------------
	void setForward(Vec3 value);

	//----------------------------------------
	//! @brief ��x�N�g���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D* ��x�N�g��
	//----------------------------------------
	Vector3D* getpUp();

	//----------------------------------------
	//! @brief �����x�N�g���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D* �����x�N�g��
	//----------------------------------------
	Vector3D* getpDefaultUp();

	//----------------------------------------
	//! @brief �E�x�N�g���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D* �E�x�N�g��
	//----------------------------------------
	Vector3D* getpRight();

	//----------------------------------------
	//! @brief ����E�x�N�g���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D* ����E�x�N�g��
	//----------------------------------------
	Vector3D* getpDefaultRight();


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief ���Z�b�g�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Reset();

	//----------------------------------------
	//! @brief X����]�֐�
	//! @details
	//! @param radian �p�x
	//! @retval void �Ȃ�
	//----------------------------------------
	void RotationAxisX(float radian);

	//----------------------------------------
	//! @brief Y����]�֐�
	//! @details
	//! @param radian �p�x
	//! @retval void �Ȃ�
	//----------------------------------------
	void RotationAxisY(float radian);

	//----------------------------------------
	//! @brief Z����]�֐�
	//! @details
	//! @param radian �p�x
	//! @retval void �Ȃ�
	//----------------------------------------
	void RotationAxisZ(float radian);

	//----------------------------------------
	//! @brief �O�x�N�g������]�֐�
	//! @details
	//! @param radian �p�x
	//! @retval void �Ȃ�
	//----------------------------------------
	void RotationAxisForward(float radian);

	//----------------------------------------
	//! @brief ��x�N�g������]�֐�
	//! @details
	//! @param radian �p�x
	//! @retval void �Ȃ�
	//----------------------------------------
	void RotationAxisUp(float radian);

	//----------------------------------------
	//! @brief �E�x�N�g������]�֐�
	//! @details
	//! @param radian �p�x
	//! @retval void �Ȃ�
	//----------------------------------------
	void RotationAxisRight(float radian);

	//----------------------------------------
	//! @brief �C�ӎ���]�֐�
	//! @details
	//! @param radian �p�x
	//! @retval void �Ȃ�
	//----------------------------------------
	void RotationAxisAny(Vec3 axis, float radian);

	//----------------------------------------
	//! @brief �s���]�֐�
	//! @details
	//! @param rotation_matrix �s��
	//! @retval void �Ȃ�
	//----------------------------------------
	void RotationMatrix(MATRIX* rotation_matrix);

	//----------------------------------------
	//! @brief �N�H�[�^�j�I����]��]�֐�
	//! @details
	//! @param quaternion �N�H�[�^�j�I��
	//! @retval void �Ȃ�
	//----------------------------------------
	void RotationQuaternion(Quaternion* quaternion);

private:
	//----------------------------------------
	//! @brief ��&�E�x�N�g���Z�o�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void CalculationUpAndRightVector();

	//----------------------------------------
	//! @brief �S�x�N�g�����K���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void NormalizeAllVector();
};



#endif