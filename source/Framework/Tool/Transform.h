//================================================================================
//!	@file	 Transform.h
//!	@brief	 �ό`Class
//! @details 
//!	@author  Kai Araki									@date 2017/11/21
//================================================================================
#ifndef	_TRANSFORM_H_
#define _TRANSFORM_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "../Vector3D.h"
#include "../AxisVector/AxisVector.h"
#include "../MatrixExtend/MatrixExtend.h"
#include "../LimitedPointerArray/LimitedPointerArray.h"



//************************************************************														   
//! @brief   �ό`Class
//!
//! @details �I�u�W�F�N�g�̕ό`��\��Class
//************************************************************
class Transform
{
//====================
// �ϐ�
//====================
private:
	Vector3D position_;						//!< ���W
	Vector3D scale_;						//!< �g�k
	Quaternion now_quaternion_;				//!< ���݂̃N�H�[�^�j�I��
	Quaternion yaw_pitch_roll_quaternion_;	//!< YawPitchRoll�N�H�[�^�j�I��
	Quaternion target_quaternion_;			//!< �^�[�Q�b�g�N�H�[�^�j�I��
	Quaternion old_target_quaternion_;		//!< �Â��^�[�Q�b�g�N�H�[�^�j�I��
	Vector3D yaw_pitch_roll_angle_;			//!< YawPitchRoll�p�x
	float look_at_speed_;					//!< �������x
	float look_at_change_amount_;			//!< �����ω���
	MatrixExtend matrix_extend_;			//!< �s��
	AxisVector axis_vector_;				//!< ��


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
	Vector3D* getpPosition() { return &position_; }

	//----------------------------------------
	//! @brief �g�k�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D* ���W
	//----------------------------------------
	Vector3D* getpScale() { return &scale_; }

	//----------------------------------------
	//! @brief Pitch�p�x�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float* Pitch�p�x
	//----------------------------------------
	float* getpAnglePitch();

	//----------------------------------------
	//! @brief Yaw�p�x�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float* Yaw�p�x
	//----------------------------------------
	float* getpAngleYaw();

	//----------------------------------------
	//! @brief Roll�p�x�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float* Roll�p�x
	//----------------------------------------
	float* getpAngleRoll();

	//----------------------------------------
	//! @brief YawPitchRoll�p�x�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D* YawPitchRoll�p�x
	//----------------------------------------
	Vector3D* getpAngleYawPitchRoll();

	//----------------------------------------
	//! @brief �������x�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float* �������x
	//----------------------------------------
	float* getpLookAtSpeed();

	//----------------------------------------
	//! @brief �����x�N�g���ݒ�֐�
	//! @details
	//! @param look_at_vector �����x�N�g��
	//! @retval void �Ȃ�
	//----------------------------------------
	void setLookAtVector(Vector3D look_at_vector);

	//----------------------------------------
	//! @brief �^�[�Q�b�g�N�H�[�^�j�I���ݒ�֐�
	//! @details
	//! @param axis  ��
	//! @param angle �p�x
	//! @retval void �Ȃ�
	//----------------------------------------
	void setTargetQuaternion(Vector3D axis, float angle);

//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �R���X�g���N�^�֐�
	//! @details
	//! @param void �Ȃ�
	//----------------------------------------
	Transform();

	//----------------------------------------
	//! @brief �f�X�g���N�^�֐�
	//! @details
	//! @param void �Ȃ�
	//----------------------------------------
	~Transform();

	

	
	
	
	
	// ��
	void UpdateAxisVector();
	const Vector3D* GetForawrd(){return axis_vector_.GetForawrd();}
	const Vector3D* GetUp(){return axis_vector_.GetUp();}
	const Vector3D* GetRight(){return axis_vector_.GetRight();}
	AxisVector* GetAxisVector(){return &axis_vector_;}

	// �s��
	void UpdateWorldMatrixSRT();
	void UpdateWorldMatrixISRT();
	void UpdateInverseMatrix(const MATRIX* matrix){matrix_extend_.UpdateInverseMatrix(matrix);}
	void UpdateTransposeMatrix(const MATRIX* matrix){matrix_extend_.UpdateTransposeMatrix(matrix);}
	void TransposeMatrixTranslationOff(){matrix_extend_.TransposeMatrixTranslationOff();}
	MATRIX* getpWorldMatrix(){return matrix_extend_.GetWorldMatrix();}
	MatrixExtend* getpMatrixExtend(){return &matrix_extend_;}

	// �S��
	void UpdateAxisVector_WorldMatrixSRT();
	void UpdateAxisVector_WorldMatrixISRT();


//------------------------------------------------------------
private :
	// ��]
	void CreateQuaternion();

};



#endif