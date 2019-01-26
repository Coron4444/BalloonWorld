//================================================================================
//!	@file	 BackBuffer.h
//!	@brief	 �o�b�N�o�b�t�@�[Class
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================
#ifndef	_BACK_BUFFER_H_
#define _BACK_BUFFER_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "../../Fade/Fade.h"
#include <LimitedPointerArray\LimitedPointerArray.h>
#include <ComponentManager/DrawManager/RenderTexture/RenderTexture.h>



//****************************************
// �N���X�錾
//****************************************
class Camera;
class DrawBase;
class Fade;
class ShaderManager;



//************************************************************														   
//! @brief   �o�b�N�o�b�t�@�[Class
//!
//! @details �o�b�N�o�b�t�@�[�֕`�悷��`����N���X���Ǘ�����Class
//************************************************************
class BackBuffer
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
	LimitedPointerArray<DrawBase*, ARRAY_NUM> all_opacity_draw_;		//!< �s�����z��
	LimitedPointerArray<DrawBase*, ARRAY_NUM> all_transparency_draw_;	//!< �����z��
	LimitedPointerArray<DrawBase*, ARRAY_NUM> all_2D_draw_;				//!< 2D�z��

	Camera* camera_ = false;	//!< �J����

	Fade* fade_ = false;		//!< �t�F�[�h
	bool  is_fade_ = false;		//!< �t�F�[�h���t���O

	ShaderManager* shader_manager_ = nullptr;	//!< �V�F�[�_�[�}�l�[�W��

	LPDIRECT3DTEXTURE9 main_screen_texture_;
	LPDIRECT3DSURFACE9 main_screen_surface_;

	LPDIRECT3DTEXTURE9 post_effect_texture_;
	LPDIRECT3DSURFACE9 post_effect_surface_;

	LPDIRECT3DSURFACE9 back_buffer_surface_;

	RenderTexture render_texture_;


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �J�����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Camera* �J����
	//----------------------------------------
	Camera* getpCamera();
	
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
	//! @brief �S�z��̃��Z�b�g�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void ResetAllArray();

	//----------------------------------------
	//! @brief �t�F�[�h�������֐�
	//! @details
	//! @param type  �^�C�v
	//! @param state �X�e�[�g
	//! @param size  �g�k
	//! @param color �F
	//! @param speed �t�F�[�h���x
	//! @retval void �Ȃ�
	//----------------------------------------
	void InitFade(Fade::Type type, Fade::State state, Vec2 size,
				  XColor4 fade_color, float fade_speed);

	//----------------------------------------
	//! @brief �t�F�[�h�I���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void UninitFade();

	//----------------------------------------
	//! @brief �t�F�[�h�I�����̊m�F�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval bool �t�F�[�h�I�����̗L��
	//----------------------------------------
	bool IsFadeEnd();

	//----------------------------------------
	//! @brief �t�F�[�h�X�e�[�g�̖��O����֐�
	//! @details
	//! @param state �X�e�[�g
	//! @retval bool �X�e�[�g�ƍ����Ă����true
	//----------------------------------------
	bool IsFadeStateName(Fade::State state);

private:
	//----------------------------------------
	//! @brief �����`����N���X�̃\�[�g�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void SortTransparent();

	//----------------------------------------
	//! @brief 2D�`����N���X�̃\�[�g�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Sort2D();

	//----------------------------------------
	//! @brief �r���{�[�h�p�s��ύX�֐�
	//! @details
	//! @param draw �`����N���X
	//! @retval void �Ȃ�
	//----------------------------------------
	void SetBillboardMatrix(DrawBase* draw);
	
	//----------------------------------------
	//! @brief �S�r���{�[�h�X�V�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void AllBillboardUpdate();

	//----------------------------------------
	//! @brief �t�F�[�h�`��֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void FadeDraw();
};



#endif
