//================================================================================
//!	@file	 PlayerUpdate.h
//!	@brief	 �v���C���[�X�VClass
//! @details 
//!	@author  Kai Araki									@date 2019/03/27
//================================================================================
#ifndef	_PLAYER_UPDATE_H_
#define _PLAYER_UPDATE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <GameEngine/Update/UpdateNull.h>



//****************************************
// �N���X�錾
//****************************************
class Player;
class BulletPhysicsObject;



//************************************************************														   
//! @brief   �v���C���[�X�VClass
//!
//! @details �v���C���[�̍X�VClass
//************************************************************
class PlayerUpdate : public UpdateNull
{
//====================
// �ϐ�
//====================
private:
	static const float ACCELERATION;	//!< �����x


//====================
// �ϐ�
//====================
private:
	Player* player_;	//!< �v���C���[
	BulletPhysicsObject* bullet_object_;	//!< �o���b�g�I�u�W�F�N�g

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
	//! @brief �f�o�b�O�\���֐�
	//! @details 
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void DebugDisplay() override;

private:
	//----------------------------------------
	//! @brief ���s�ړ����͊֐�
	//! @details 
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void InputTranslation();

	//----------------------------------------
	//! @brief �J�����������s�ړ����͊֐�
	//! @details 
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void InputTranslationNotCamera();
};



#endif