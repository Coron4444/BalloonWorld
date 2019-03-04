//================================================================================
//!	@file	 Scaffold.h
//!	@brief	 ����Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================
#ifndef	_SCAFFOLD_H_
#define _SCAFFOLD_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <GameEngine/GameObject/GameObjectNull.h>



//************************************************************														   
//! @brief   ����Class
//!
//! @details �����Class
//************************************************************
class Scaffold : public GameObjectNull
{
//====================
// �萔
//====================
private:
	static const Vector3D SCALE;				//!< �g�k


//====================
// �ϐ�
//====================
private:
	XColor4 color_ = {1.0f, 1.0f, 1.0f, 1.0f};		//!< �F
	int score_ = 0;


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
	void setPosition(Vector3D value);

	//----------------------------------------
	//! @brief �g�k�ݒ�֐�
	//! @details
	//! @param value �g�k
	//! @retval void �Ȃ�
	//----------------------------------------
	void setScale(Vector3D value);

	//----------------------------------------
	//! @brief �F�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval XColor4* �F
	//----------------------------------------
	XColor4* getpColor();

	//----------------------------------------
	//! @brief �F�ݒ�֐�
	//! @details
	//! @param value �F
	//! @retval void �Ȃ�
	//----------------------------------------
	void setColor(XColor4 value);

	//----------------------------------------
	//! @brief �X�R�A�擾�֐�
	//! @details
	//! @param value �X�R�A
	//! @retval void �Ȃ�
	//----------------------------------------
	int getScore();

	//----------------------------------------
	//! @brief �X�R�A�ݒ�֐�
	//! @details
	//! @param value �X�R�A
	//! @retval void �Ȃ�
	//----------------------------------------
	void setScore(int value);



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