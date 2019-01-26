//================================================================================
//!	@file	 ComponentBase.h
//!	@brief	 �R���|�[�l���gBaseClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================
#ifndef	_COMPONENT_BASE_H_
#define _COMPONENT_BASE_H_



//****************************************
// �C���N���[�h��
//****************************************
#ifdef _DEBUG
#include <ImGUI/imgui.h>
#include <ImGUI/imgui_impl_dx9.h>
#endif



//****************************************
// �N���X�錾
//****************************************
class GameObjectBase;



//************************************************************														   
//! @brief   �R���|�[�l���gBaseClass
//!
//! @details �R���|�[�l���g��BaseClass
//************************************************************
class ComponentBase
{
//====================
// �ϐ�
//====================
private:
	GameObjectBase* game_object_;	//!< �Q�[���I�u�W�F�N�g


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �Q�[���I�u�W�F�N�g�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval GameObjectBase* �Q�[���I�u�W�F�N�g
	//----------------------------------------
	GameObjectBase* getpGameObject();
	
	//----------------------------------------
	//! @brief �Q�[���I�u�W�F�N�g�ݒ�֐�
	//! @details
	//! @param value �Q�[���I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	void setGameObject(GameObjectBase* value);


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief ���z�f�X�g���N�^
	//! @details
	//! @param void �Ȃ�
	//----------------------------------------
	virtual ~ComponentBase() = 0;

	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void Init() = 0;

	//----------------------------------------
	//! @brief �I���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void Uninit() = 0;

	//----------------------------------------
	//! @brief �X�V�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void Update() = 0;

	//----------------------------------------
	//! @brief �f�o�b�O�\���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void DebugDisplay() = 0;
};



#endif