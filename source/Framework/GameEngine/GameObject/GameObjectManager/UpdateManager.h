//================================================================================
//!	@file	 UpdateManager.h
//!	@brief	 �X�V�}�l�[�W���[Class
//! @details 
//!	@author  Kai Araki									@date 2019/01/19
//================================================================================
#ifndef	_UPDATE_MANAGER_H_
#define _UPDATE_MANAGER_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <Tool/LimitedPointerArray.h>



//****************************************
// �N���X�錾
//****************************************
class GameObjectBase;



//************************************************************														   
//! @brief   �X�V�}�l�[�W���[lass
//!
//! @details �o�^����Ă���X�V���N���X���Ǘ�����Class
//************************************************************
class UpdateManager
{
//====================
// �萔
//====================
public:
	static const unsigned ARRAY_NUM = 10000;		//!< �z��


//====================
// �ϐ�
//====================
private:
	LimitedPointerArray<GameObjectBase*, ARRAY_NUM> all_object_;	//!< �S�X�V�z��
	LimitedPointerArray<GameObjectBase*, ARRAY_NUM> await_add_;		//!< �ǉ��҂��z��
	LimitedPointerArray<GameObjectBase*, ARRAY_NUM> await_release_;	//!< ����҂��z��


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
	void Init();

	//----------------------------------------
	//! @brief �I���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Uninit();

	//----------------------------------------
	//! @brief �V�[���ύX���̏I���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void UninitWhenChangeScene();

	//----------------------------------------
	//! @brief �X�V�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Update();

	//----------------------------------------
	//! @brief �X�V���N���X�̒ǉ��֐�
	//! @details
	//! @param *update �X�V���N���X
	//! @retval void �Ȃ�
	//----------------------------------------
	void AddGameObjectBase(GameObjectBase* update);

	//----------------------------------------
	//! @brief �X�V���N���X�̉���֐�
	//! @details
	//! @param *update �X�V���N���X
	//! @retval void �Ȃ�
	//----------------------------------------
	void ReleaseGameObjectBase(GameObjectBase* update);

private:
	//----------------------------------------
	//! @brief �ǉ��҂��z��̒��g��ǉ��֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void AddContentsOfAwaitAddArray();

	//----------------------------------------
	//! @brief ����҂��z��̒��g������֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void ReleaseContentsOfAwaitReleaseArray();
};



#endif
