//================================================================================
//!	@file	 CameraState_CrawlUp.h
//!	@brief	 �������΂�J�����X�e�[�gClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================
#ifndef	_CAMERA_STATE_CRAWL_UP_H_
#define _CAMERA_STATE_CRAWL_UP_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "Camera.h"



//************************************************************														   
//! @brief   �������΂�J�����X�e�[�gClass
//!
//! @details �������΂�J�����̃X�e�[�gClass
//************************************************************
class CameraState_CrawlUp : public Camera::State
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

	//----------------------------------------
	//! @brief �����_���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void InputRotationAroundGazingPoint();
};



#endif