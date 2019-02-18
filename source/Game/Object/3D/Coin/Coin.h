//================================================================================
//!	@file	 Coin.h
//!	@brief	 �R�C��Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================
#ifndef	_COIN_H_
#define _COIN_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <GameEngine/GameObject/GameObjectNull.h>



//************************************************************														   
//! @brief   �R�C��Class
//!
//! @details �R�C����Class
//************************************************************
class Coin : public GameObjectNull
{
//====================
// �ϐ�
//====================
private:
	int color_change_counter_ = 0;					//!< �F�ύX�J�E���^
	XColor4 color_ = {1.0f, 1.0f, 1.0f, 1.0f};		//!< �F
	bool is_color_change_ = false;					//!< �F�ύX�t���O

//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �F�ύX�J�E���^�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval int* �F�ύX�J�E���^
	//----------------------------------------
	int* getpColorChangeCounter();

	//----------------------------------------
	//! @brief �F�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval XColor4* �F
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
	//! @param *draw      �`����N���X
	//! @param *collision �Փˊ��N���X
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init(DrawBase* draw, CollisionBase* collision);

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