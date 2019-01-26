//================================================================================
//!	@file	 MatrixGroup.h
//!	@brief	 �s��QClass
//! @details 
//!	@author  Kai Araki									@date 2018/08/16
//================================================================================
#ifndef	_MATRIX_GROUP_H_
#define _MATRIX_GROUP_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "Vector3D.h"



//************************************************************														   
//! @brief   �s��QClass
//!
//! @details �s��̏W����Class
//************************************************************
class MatrixGroup
{
//====================
// �ϐ�
//====================
private:
	MATRIX position_;		//!< ���W�s��
	MATRIX scale_;			//!< �g�k�s��
	MATRIX rotation_;		//!< ��]�s��
	MATRIX inverse_;		//!< �t�s��
	MATRIX transpose_;		//!< �]�u�s��
	MATRIX world_;			//!< ���[���h�s��


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief ���W�s��擾�֐�
	//! @details
	//! @param void
	//! @retval MATRIX* ���W�s��
	//----------------------------------------
	MATRIX* getpPositionMatrix();

	//----------------------------------------
	//! @brief ���W�s��ݒ�֐�
	//! @details
	//! @param value �s��ɂ��������W�l
	//! @retval void �Ȃ�
	//----------------------------------------
	void setPositionMatrix(Vec3* value);

	//----------------------------------------
	//! @brief �g�k�s��擾�֐�
	//! @details
	//! @param void
	//! @retval MATRIX* �g�k�s��
	//----------------------------------------
	MATRIX* getpScaleMatrix();

	//----------------------------------------
	//! @brief �g�k�s��ݒ�֐�
	//! @details
	//! @param value �s��ɂ������g�k�l
	//! @retval void �Ȃ�
	//----------------------------------------
	void setScaleMatrix(Vec3* value);

	//----------------------------------------
	//! @brief ��]�s��擾�֐�
	//! @details
	//! @param void
	//! @retval MATRIX* �g�k�s��
	//----------------------------------------
	MATRIX* getpRotationMatrix();

	//----------------------------------------
	//! @brief ��]�s��ݒ�֐�
	//! @details
	//! @param value �s��ɂ�������]�l
	//! @retval void �Ȃ�
	//----------------------------------------
	void setRotationMatrix(Quaternion* value);

	//----------------------------------------
	//! @brief �t�s��擾�֐�
	//! @details
	//! @param void
	//! @retval MATRIX* �t�s��
	//----------------------------------------
	MATRIX* getpInverseMatrix();

	//----------------------------------------
	//! @brief �t�s��ݒ�֐�
	//! @details
	//! @param value �t�s��ɂ������s��
	//! @retval void �Ȃ�
	//----------------------------------------
	void setInverseMatrix(MATRIX* value);

	//----------------------------------------
	//! @brief �]�u�s��擾�֐�
	//! @details
	//! @param void
	//! @retval MATRIX* �]�u�s��
	//----------------------------------------
	MATRIX* getpTransposeMatrix();

	//----------------------------------------
	//! @brief �]�u�s��ݒ�֐�
	//! @details
	//! @param value           �]�u�s��ɂ������s��
	//! @param is_position_off ���s�ړ�OFF�t���O
	//! @retval void �Ȃ�
	//----------------------------------------
	void setTransposeMatrix(MATRIX* value, bool is_position_off = false);

	//----------------------------------------
	//! @brief ���[���h�s��擾�֐�
	//! @details
	//! @param void
	//! @retval MATRIX* �]�u�s��
	//----------------------------------------
	MATRIX* getpWorldMatrix();

//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �R���X�g���N�^
	//! @details
	//! @param void �Ȃ�
	//----------------------------------------
	MatrixGroup();

	//----------------------------------------
	//! @brief ���[���h�s��쐬�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateWorldMatrix();

	//----------------------------------------
	//! @brief �t�s��t�����[���h�s��쐬�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateWorldMatrixPlusInverse();

	//----------------------------------------
	//! @brief �]�u�s��t�����[���h�s��쐬�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateWorldMatrixPlusTranspose();

	//----------------------------------------
	//! @brief ���[���h�s��ɐe�s��ǉ��֐�
	//! @details
	//! @param parent_matrix �e�̍s��
	//! @retval void �Ȃ�
	//----------------------------------------
	void AddParentMatrixToWorldMatrix(MATRIX* parent_matrix);

private:
	//----------------------------------------
	//! @brief �S�s�񃊃Z�b�g�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void ResetAllMatrix();
};



#endif