//================================================================================
//!	@file	 CameraState_HomingTarget.h
//!	@brief	 �^�[�Q�b�g�ǐՃJ�����X�e�[�gClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================
#ifndef	_CAMERA_STATE_HOMING_TARGET_H_
#define _CAMERA_STATE_HOMING_TARGET_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "Camera.h"



//****************************************
// �N���X�錾
//****************************************
class GameObjectBase;



//************************************************************														   
//! @brief   �^�[�Q�b�g�ǐՃJ�����X�e�[�gClass
//!
//! @details �^�[�Q�b�g�ǐՂ̃J�����X�e�[�gClass
//************************************************************
class CameraState_HomingTarget : public Camera::State
{
//====================
// �萔
//====================
public:
	static const Vec3 DEFAULT_LENGHT;			//!< ���苗��
	static const float GAZING_POINT_Y;			//!< �����_��Y���W
	static const float DEFAULT_ROTATION_SPEED;	//!< �����]���x


//====================
// �ϐ�
//====================
private:
	GameObjectBase* target_object_ = nullptr;	//!< �^�[�Q�b�g�I�u�W�F�N�g
	Vector3D lenght_;							//!< ����
	float rotation_speed_;						//!< ��]���x


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �^�[�Q�b�g�I�u�W�F�N�g�ݒ�֐�
	//! @details
	//! @param value �^�[�Q�b�g�I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	void setTargetObject(GameObjectBase* value);

	//----------------------------------------
	//! @brief �����ݒ�֐�
	//! @details
	//! @param value ����
	//! @retval void �Ȃ�
	//----------------------------------------
	void setLength(Vec3 value);

	//----------------------------------------
	//! @brief ��]���x�ݒ�֐�
	//! @details
	//! @param value ��]���x
	//! @retval void �Ȃ�
	//----------------------------------------
	void setRotationSpeed(float value);


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param camera �J����
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init() override;

	//----------------------------------------
	//! @brief �I���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Uninit() override;

	//----------------------------------------
	//! @brief �X�V�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Update() override;

private:
	//----------------------------------------
	//! @brief ���W�Z�o�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void CalculationPosition();

	//----------------------------------------
	//! @brief �����_�Z�o�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void CalculationGazingPoint();

	//----------------------------------------
	//! @brief �O�x�N�g���Z�o�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void CalculationForward();

	//----------------------------------------
	//! @brief �����_���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void InputRotationAroundGazingPoint();
};



#endif