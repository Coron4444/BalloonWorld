//================================================================================
//!	@file	 Transform.h
//!	@brief	 �ό`Class
//! @details 
//!	@author  Kai Araki									@date 2017/11/21
//================================================================================
#ifndef	_TRANSFORM_H_
#define _TRANSFORM_H_



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
	Matrix position_matrix_;						//!< ���W�s��
	Matrix scale_matrix_;							//!< �g�k�s��
	Matrix rotation_matrix_;						//!< ��]�s��
	Matrix no_init_rotation_matrix_;				//!< ������]������]�s��
	Matrix inverse_matrix_;							//!< �t�s��
	Matrix transpose_matrix_;						//!< �]�u�s��
	Matrix world_matrix_;							//!< ���[���h�s��
	Matrix no_init_rotation_world_matrix_;			//!< ������]�������[���h�s��


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
	Vector3D* getpForward();

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
	//! @brief ���W�s��擾�֐�
	//! @details
	//! @param void
	//! @retval Matrix* ���W�s��
	//----------------------------------------
	Matrix* getpPositionMatrix();

	//----------------------------------------
	//! @brief �g�k�s��擾�֐�
	//! @details
	//! @param void
	//! @retval Matrix* �g�k�s��
	//----------------------------------------
	Matrix* getpScaleMatrix();

	//----------------------------------------
	//! @brief ��]�s��擾�֐�
	//! @details
	//! @param void
	//! @retval Matrix* �g�k�s��
	//----------------------------------------
	Matrix* getpRotationMatrix();

	//----------------------------------------
	//! @brief ������]������]�s��擾�֐�
	//! @details
	//! @param void
	//! @retval Matrix* �g�k�s��
	//----------------------------------------
	Matrix* getpNoInitRotationMatrix();

	//----------------------------------------
	//! @brief �t�s��擾�֐�
	//! @details
	//! @param void
	//! @retval Matrix* �t�s��
	//----------------------------------------
	Matrix* getpInverseMatrix();

	//----------------------------------------
	//! @brief �t�s��ݒ�֐�
	//! @details
	//! @param value �t�s��ɂ������s��
	//! @retval void �Ȃ�
	//----------------------------------------
	void setInverseMatrix(Matrix* value);

	//----------------------------------------
	//! @brief �]�u�s��擾�֐�
	//! @details
	//! @param void
	//! @retval Matrix* �]�u�s��
	//----------------------------------------
	Matrix* getpTransposeMatrix();

	//----------------------------------------
	//! @brief �]�u�s��ݒ�֐�
	//! @details
	//! @param value           �]�u�s��ɂ������s��
	//! @param is_position_off ���s�ړ�OFF�t���O
	//! @retval void �Ȃ�
	//----------------------------------------
	void setTransposeMatrix(Matrix* value, bool is_position_off = false);

	//----------------------------------------
	//! @brief ���[���h�s��擾�֐�
	//! @details
	//! @param void
	//! @retval Matrix* ���[���h�s��
	//----------------------------------------
	Matrix* getpWorldMatrix();

	//----------------------------------------
	//! @brief ������]�������[���h�s��擾�֐�
	//! @details
	//! @param void
	//! @retval Matrix* ������]�������[���h�s��
	//----------------------------------------
	Matrix* getpNoInitRotationWorldMatrix();


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �R���X�g���N�^
	//! @details
	//! @param void �Ȃ�
	//----------------------------------------
	Transform();

	//----------------------------------------
	//! @brief �f�X�g���N�^
	//! @details
	//----------------------------------------
	~Transform();

	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init();

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
	void AddParentMatrixToWorldMatrix(Matrix* parent_matrix);

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

	//----------------------------------------
	//! @brief ���[���h�s��Z�o�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void CalculateWorldMatrix();

	//----------------------------------------
	//! @brief �t�s��t�����[���h�s��Z�o�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void CalculateWorldMatrixPlusInverse();

	//----------------------------------------
	//! @brief �]�u��t�����[���h�s��Z�o�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void CalculateWorldMatrixPlusTranspose();
};



#endif