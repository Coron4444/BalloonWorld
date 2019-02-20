//================================================================================
//!	@file	 StartBlock.h
//!	@brief	 �X�^�[�g�u���b�NClass
//! @details 
//!	@author  Kai Araki									@date 2019/02/13
//================================================================================
#ifndef	_START_BLOCK_H_
#define _START_BLOCK_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <GameEngine/GameObject/GameObjectNull.h>



//************************************************************														   
//! @brief   �X�^�[�g�u���b�NClass
//!
//! @details �X�^�[�g�u���b�N��Class
//************************************************************
class StartBlock : public GameObjectNull
{
//====================
// �萔
//====================
private:
	static const Vec3 SCALE;				//!< �g�k
	static const float ROTATION_SPEED;		//!< ��]


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief ���W�ݒ�֐�
	//! @details
	//! @param value ���W
	//! @retval void �Ȃ�
	//----------------------------------------
	void setPosition(Vec3 value);

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
};



#endif