//================================================================================
//!	@file	 CameraState_Normal.h
//!	@brief	 �m�[�}���J�����X�e�[�gClass
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================
#ifndef	_CAMERA_STATE_NORMAL_H_
#define _CAMERA_STATE_NORMAL_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "Camera.h"



//****************************************
// �N���X�錾
//****************************************
class GameObjectBase;



//************************************************************														   
//! @brief   �m�[�}���J�����X�e�[�gClass
//!
//! @details �m�[�}���̃J�����X�e�[�gClass
//************************************************************
class CameraState_Normal : public Camera::State
{
//====================
// �萔
//====================
public:
	static const float TRANSLATION_SPEED;	//!< ���x
	static const float ROTATION_SPEED;		//!< ��]���x
	static const float POSITION_Y;			//!< Y���W
	static const float GAZING_POINT_Y;		//!< �����_��Y���W


//====================
// �ϐ�
//====================
private:
	Vector3D lenght_;							//!< ����
	float rotation_speed_;						//!< ��]���x


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
	//! @brief ���s�ړ����͊֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void InputTranslation();

	//----------------------------------------
	//! @brief ��]���͊֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void InputRotation();
};



#endif