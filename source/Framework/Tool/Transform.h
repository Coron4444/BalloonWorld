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
#include "Vector3D.h"
#include "Axis.h"
#include "MatrixGroup.h"



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
	Vector3D position_;								//!< ���W
	Vector3D scale_;								//!< �g�k
	Quaternion init_quaternion_;					//!< �����l�N�H�[�^�j�I��
	Quaternion now_quaternion_;						//!< ���ݗp�N�H�[�^�j�I��
	Quaternion add_quaternion_;						//!< �ǉ��p�N�H�[�^�j�I��
	Quaternion yaw_pitch_roll_quaternion_;			//!< YawPitchRoll�N�H�[�^�j�I��
	Quaternion target_quaternion_;					//!< �^�[�Q�b�g�N�H�[�^�j�I��
	Quaternion old_target_quaternion_;				//!< �Â��^�[�Q�b�g�N�H�[�^�j�I��
	Vector3D yaw_pitch_roll_angle_;					//!< YawPitchRoll�p�x
	float look_at_speed_;							//!< �������x
	float look_at_change_amount_;					//!< �����ω���
	Axis axis_;										//!< ��
	MatrixGroup matrix_group_;						//!< �s��Q
	MatrixGroup no_init_rotation_matrix_group_;		//!< ������]�����s��Q


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
	//! @brief �g�k�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D* ���W
	//----------------------------------------
	Vector3D* getpScale();

	//----------------------------------------
	//! @brief �����p�x�擾�֐�
	//! @details
	//! @param value �p�x
	//! @retval void �Ȃ�
	//----------------------------------------
	void setInitAngle(Vector3D value);

	//----------------------------------------
	//! @brief �ǉ��p�N�H�[�^�j�I���ݒ�֐�
	//! @details
	//! @param value �ǉ��p�N�H�[�^�j�I��
	//! @retval void �Ȃ�
	//----------------------------------------
	void setAddQuaternion(Quaternion value);

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

	//----------------------------------------
	//! @brief �O�x�N�g���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D* �O�x�N�g��
	//----------------------------------------
	Vector3D* getpForawrd();

	//----------------------------------------
	//! @brief ��x�N�g���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D* ��x�N�g��
	//----------------------------------------
	Vector3D* getpUp();

	//----------------------------------------
	//! @brief �E�x�N�g���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D* �E�x�N�g��
	//----------------------------------------
	Vector3D* getpRight();

	//----------------------------------------
	//! @brief ���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Axis* ��
	//----------------------------------------
	Axis* getpAxis();

	//----------------------------------------
	//! @brief ���W�s��擾�֐�
	//! @details
	//! @param void
	//! @retval MATRIX* ���W�s��
	//----------------------------------------
	MATRIX* getpPositionMatrix();

	//----------------------------------------
	//! @brief �g�k�s��擾�֐�
	//! @details
	//! @param void
	//! @retval MATRIX* �g�k�s��
	//----------------------------------------
	MATRIX* getpScaleMatrix();

	//----------------------------------------
	//! @brief ��]�s��擾�֐�
	//! @details
	//! @param void
	//! @retval MATRIX* �g�k�s��
	//----------------------------------------
	MATRIX* getpRotationMatrix();

	//----------------------------------------
	//! @brief ������]������]�s��擾�֐�
	//! @details
	//! @param void
	//! @retval MATRIX* �g�k�s��
	//----------------------------------------
	MATRIX* getpNoInitRotationMatrix();

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
	//! @retval MATRIX* ���[���h�s��
	//----------------------------------------
	MATRIX* getpWorldMatrix();

	//----------------------------------------
	//! @brief ������]�������[���h�s��擾�֐�
	//! @details
	//! @param void
	//! @retval MATRIX* ������]�������[���h�s��
	//----------------------------------------
	MATRIX* getpNoInitRotationWorldMatrix();

	//----------------------------------------
	//! @brief �s��Q�擾�֐�
	//! @details
	//! @param void
	//! @retval MatrixGroup* �s��Q
	//----------------------------------------
	MatrixGroup* getpMatrixGroup();


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
	//! @brief �ǉ��p�N�H�[�^�j�I�����Z�b�g�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void ResetAddQuaternion();

	//----------------------------------------
	//! @brief ���[���h�s��ɐe�s��ǉ��֐�
	//! @details
	//! @param parent_matrix �e�̍s��
	//! @retval void �Ȃ�
	//----------------------------------------
	void AddParentMatrixToWorldMatrix(MATRIX* parent_matrix);

	//----------------------------------------
	//! @brief ���쐬�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateAxis();

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
	//! @brief ��&���[���h�s��쐬�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateAxisAndWorldMatrix();

	//----------------------------------------
	//! @brief ��&�t�s��t�����[���h�s��쐬�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateAxisAndWorldMatrixPlusInverse();

	//----------------------------------------
	//! @brief ��&�]�u�s��t�����[���h�s��쐬�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateAxisAndWorldMatrixPlusTranspose();

private :
	//----------------------------------------
	//! @brief �N�H�[�^�j�I���쐬�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateQuaternion();

	//----------------------------------------
	//! @brief �s�񔽉f�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void ReflectMatrix();
};



#endif