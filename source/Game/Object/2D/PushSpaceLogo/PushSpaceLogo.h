//================================================================================
//!	@file	 PushSpaceLogo.h
//!	@brief	 �v�b�V���X�y�[�X���SClass
//! @details 
//!	@author  Kai Araki									@date 2018/09/02
//================================================================================
#ifndef	_PUSH_SPACE_LOGO_H_
#define _PUSH_SPACE_LOGO_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <GameEngine/GameObject/GameObjectNull.h>



//************************************************************														   
//! @brief   �v�b�V���X�y�[�X���SClass
//!
//! @details �v�b�V���X�y�[�X���S��Class
//************************************************************
class PushSpaceLogo : public GameObjectNull
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
	XColor4 color_ = {1.0f, 1.0f, 1.0f, 1.0f};	//!< �F
	bool is_color_change_ = false;				//!< �F�ύX�t���O
	int color_change_counter_;					//!< �F�ύX�J�E���^


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �F�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	XColor4* getpColor();

	//----------------------------------------
	//! @brief �F�ύX�t���O�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval bool �F�ύX�t���O
	//----------------------------------------
	bool* getpIsColorChange();


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param *draw �`����N���X
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init(DrawBase* draw);

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