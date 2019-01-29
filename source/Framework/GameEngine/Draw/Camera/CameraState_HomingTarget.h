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
	static const float HOMING_CAMERA_POSITION_Y;		//!< Y���W
	static const float HOMING_CAMERA_POSITION_Z;		//!< Z���W
	static const float HOMING_CAMERA_LOOK_AT_POINT_Y;	//!< �����_��Y���W


//====================
// �ϐ�
//====================
private:
	GameObjectBase* target_object_;		//!< �^�[�Q�b�g�I�u�W�F�N�g

//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �^�[�Q�b�g�I�u�W�F�N�g�ݒ�֐�
	//! @details
	//! @param value �^�[�Q�b�g�I�u�W�F�N�g
	//! @retval void �V�[���}�l�[�W��
	//----------------------------------------
	void setTargetObject(GameObjectBase* value);


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
};



#endif