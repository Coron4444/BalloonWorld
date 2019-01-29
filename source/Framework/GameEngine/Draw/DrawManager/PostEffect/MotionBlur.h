//================================================================================
//!	@file	 MotionBlur.h
//!	@brief	 ���[�V�����u���[Class
//! @details 
//!	@author  Kai Araki									@date 2019/01/28
//================================================================================
#ifndef	_MOTION_BLUR_H_
#define _MOTION_BLUR_H_



//****************************************
// �N���X�錾
//****************************************
class Camera;
class DrawCommonData;
class ShaderManager;
class RenderTexturePolygon;



//************************************************************														   
//! @brief   ���[�V�����u���[Class
//!
//! @details ���[�V�����u���[��Class
//************************************************************
class MotionBlur
{
//====================
// �ϐ�
//====================
private:
	Camera* camera_ = nullptr;					//!< �J����
	DrawCommonData* common_data_ = nullptr;		//!< �`�拤�ʃf�[�^
	ShaderManager* shader_manager_ = nullptr;	//!< �V�F�[�_�[�}�l�[�W��
	RenderTexturePolygon* polygon_ = nullptr;	//!< �\���p�|���S��


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
	//! @brief ��X�V�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void LateUpdate();
};



#endif
