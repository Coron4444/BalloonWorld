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
#include <Tool/Debug/ImGUI/imgui.h>
#include <Tool/Debug/ImGUI/imgui_impl_dx9.h>
#endif

#include "GameObject/GameObjectBase.h"



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
	bool is_enable_ = true;			//!< �L���t���O


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

	//----------------------------------------
	//! @brief �L���t���O�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval bool �L���t���O
	//----------------------------------------
	bool getIsEnable();

	//----------------------------------------
	//! @brief �L���t���O�擾�֐�
	//! @details
	//! @param value �L���t���O
	//! @retval void �Ȃ�
	//----------------------------------------
	void setIsEnable(bool value);


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
	//! @brief ���Z�b�g�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void Reset() = 0;

	//----------------------------------------
	//! @brief �f�o�b�O�\���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void DebugDisplay() = 0;
};



#endif