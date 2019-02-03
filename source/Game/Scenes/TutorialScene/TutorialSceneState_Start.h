//================================================================================
//!	@file	 TutorialSceneState_Start.h
//!	@brief	 �`���[�g���A���V�[���X�e�[�g(�X�^�[�g)Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================
#ifndef	_TUTORIAL_SCENE_STATE_START_H_
#define _TUTORIAL_SCENE_STATE_START_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <GameEngine/Scene/SceneStateNull.h>



//****************************************
// �N���X�錾
//****************************************
class TutorialScene;



//************************************************************														   
//! @brief   �`���[�g���A���V�[���X�e�[�g(�X�^�[�g)Class
//!
//! @details �`���[�g���A���V�[���̃X�e�[�g(�X�^�[�g)Class
//! @details �ŏ��̏�Ԃ�\��
//************************************************************
class TutorialSceneState_Start : public SceneStateNull
{
//====================
// �ϐ�
//====================
private:
	TutorialScene* tutorial_scene_ = nullptr;		//!< �`���[�g���A���V�[��
	

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