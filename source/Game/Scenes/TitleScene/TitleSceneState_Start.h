//================================================================================
//!	@file	 TitleSceneState_Start.h
//!	@brief	 �^�C�g���V�[���X�e�[�g(�X�^�[�g)Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================
#ifndef	_TITLE_SCENE_STATE_START_H_
#define _TITLE_SCENE_STATE_START_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <GameEngine/Scene/SceneStateNull.h>



//****************************************
// �N���X�錾
//****************************************
class TitleScene;




//************************************************************														   
//! @brief   �^�C�g���V�[���X�e�[�g(�X�^�[�g)Class
//!
//! @details �^�C�g���V�[���̃X�e�[�g(�X�^�[�g)Class
//! @details �ŏ��̏�Ԃ�\��
//************************************************************
class TitleSceneState_Start : public SceneStateNull
{
//====================
// �ϐ�
//====================
private:
	TitleScene* title_scene_ = nullptr;		//!< �^�C�g���V�[��


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
	void Init() override;

	//----------------------------------------
	//! @brief �X�V�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Update() override;
};



#endif