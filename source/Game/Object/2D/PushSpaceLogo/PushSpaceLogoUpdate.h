//================================================================================
//!	@file	 PushSpaceLogoUpdate.h
//!	@brief	 �v�b�V���X�y�[�X���S�X�VClass
//! @details 
//!	@author  Kai Araki									@date 2018/09/02
//================================================================================
#ifndef	_PUSH_SPACE_LOGO_UPDATE_H_
#define _PUSH_SPACE_LOGO_UPDATE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <GameEngine/Update/UpdateNull.h>



//****************************************
// �N���X�錾
//****************************************
class PushSpaceLogo;



//************************************************************														   
//! @brief   �v�b�V���X�y�[�X���S�X�VClass
//!
//! @details �v�b�V���X�y�[�X���S�̍X�VClass
//************************************************************
class PushSpaceLogoUpdate : public UpdateNull
{
//====================
// �萔
//====================
private:
	static const int COLOR_CHANGE_SPEED;		//!< �F�ύX���x


//====================
// �ϐ�
//====================
private:
	PushSpaceLogo* push_space_logo_;	//!< �v�b�V���X�y�[�X���S
	int color_change_counter_;			//!< �F�ύX�J�E���^
	

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

	//----------------------------------------
	//! @brief ���Z�b�g�֐�
	//! @details 
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Reset() override;
};



#endif