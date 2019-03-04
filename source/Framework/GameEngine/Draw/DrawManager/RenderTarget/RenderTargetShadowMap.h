//================================================================================
//!	@file	 RenderTargetShadowMap.h
//!	@brief	 �����_�[�^�[�Q�b�g�V���h�E�}�b�vClass
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================
#ifndef	_RENDER_TARGET_SHADOW_MAP_H_
#define _RENDER_TARGET_SHADOW_MAP_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "../../Camera/Camera.h"



//****************************************
// �N���X�錾
//****************************************
class DrawBase;
class DrawCommonData;
class ShaderManager;



//************************************************************														   
//! @brief   �����_�[�^�[�Q�b�g�V���h�E�}�b�vClass
//!
//! @details �����_�[�^�[�Q�b�g�V���h�E�}�b�v��Class
//************************************************************
class RenderTargetShadowMap
{
//====================
// �萔
//====================
public:
	static const unsigned ARRAY_NUM = 10000;	//!< �z��


//====================
// �ϐ�
//====================
private:
	LimitedPointerArray<DrawBase*, ARRAY_NUM> draw_;		//!< �`����N���X�z��

	Camera* camera_ = nullptr;					//!< �J����
	Camera::Type save_camera_type_;				//!< �ۑ��p�J�����^�C�v
	DrawCommonData* common_data_ = nullptr;		//!< �`�拤�ʃf�[�^
	ShaderManager* shader_manager_ = nullptr;	//!< �V�F�[�_�[�}�l�[�W��


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �J�����ݒ�֐�
	//! @details
	//! @param *value �J����
	//! @retval void �Ȃ�
	//----------------------------------------
	void setCamera(Camera* value);

	//----------------------------------------
	//! @brief �`�拤�ʃf�[�^�ݒ�֐�
	//! @details
	//! @param *value �`�拤�ʃf�[�^
	//! @retval void �Ȃ�
	//----------------------------------------
	void setDrawCommonData(DrawCommonData* value);

	//----------------------------------------
	//! @brief �V�F�[�_�[�}�l�[�W���ݒ�֐�
	//! @details
	//! @param value �V�F�[�_�[�}�l�[�W��
	//! @retval void �Ȃ�
	//----------------------------------------
	void setShaderManager(ShaderManager* value);


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init();

	//----------------------------------------
	//! @brief �V�[���ύX���̏I���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void UninitWhenChangeScene();

	//----------------------------------------
	//! @brief �I���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Uninit();

	//----------------------------------------
	//! @brief �X�V�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Update();

	//----------------------------------------
	//! @brief �`��֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Draw();

	//----------------------------------------
	//! @brief �`����N���X�̒ǉ��֐�
	//! @details
	//! @param draw �`����N���X
	//! @retval void �Ȃ�
	//----------------------------------------
	void AddDrawBaseToArray(DrawBase* draw);

	//----------------------------------------
	//! @brief ���Z�b�g�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Reset();

private:
	//----------------------------------------
	//! @brief �r���{�[�h�p�s��ύX�֐�
	//! @details
	//! @param draw �`����N���X
	//! @retval void �Ȃ�
	//----------------------------------------
	void ChangeBillboardMatrix(DrawBase* draw);
	
	//----------------------------------------
	//! @brief �S�r���{�[�h�X�V�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void AllBillboardUpdate();

	//----------------------------------------
	//! @brief �J�����^�C�v�ύX�֐�
	//! @details
	//! @param camera_type �J�����^�C�v
	//! @retval void �Ȃ�
	//----------------------------------------
	void ChangeCameraType(Camera::Type camera_type);
};



#endif
