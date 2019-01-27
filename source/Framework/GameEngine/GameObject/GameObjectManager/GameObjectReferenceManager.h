//================================================================================
//!	@file	 GameObjectReferenceManager.h
//!	@brief	 �Q�[���I�u�W�F�N�g�Q�ƃ}�l�[�W��Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/15
//================================================================================
#ifndef	_GAME_OBJECT_REFERENCE_MANAGER_H_
#define _GAME_OBJECT_REFERENCE_MANAGER_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <unordered_map>

#include <Tool/LimitedPointerArray.h>



//****************************************
// �N���X�錾
//****************************************
class GameObjectBase;


//************************************************************														   
//! @brief   �Q�[���I�u�W�F�N�g�Q�ƃ}�l�[�W��Class
//!
//! @details �Q�[���I�u�W�F�N�g�̎Q�ƃ}�l�[�W��Class
//************************************************************
class GameObjectReferenceManager
{
//====================
// �\���̒�`
//====================
public:
	//****************************************											   
	//! @brief   �Q�ƃf�[�^Class
	//!
	//! @details �Q�Ƃ̃f�[�^Class
	//****************************************
	struct ReferenceData
	{
	//====================
	// �ϐ�
	//====================
	public:
		GameObjectBase* reference_source_;			//!< �Q�ƌ��I�u�W�F�N�g
		GameObjectBase* reference_destination_;		//!< �Q�Ɛ�I�u�W�F�N�g
		void* reference_pointer_;					//!< �Q�ƃ|�C���^
		int	registration_index_;					//!< �o�^�C���f�b�N�X

	//====================
	// �֐�
	//====================
	public:
		//----------------------------------------
		//! @brief �R���X�g���N�^
		//! @details
		//! @param source      �Q�ƌ��I�u�W�F�N�g
		//! @param pointer     �Q�ƃ|�C���^
		//! @param destination �Q�Ɛ�I�u�W�F�N�g
		//----------------------------------------
		ReferenceData(GameObjectBase* source, void* pointer,
					  GameObjectBase* destination);
	};


//====================
// �萔
//====================
private:
	static const unsigned ARRAY_NUM = 1000;		//!< �z��


//====================
// �ϐ�
//====================
private:
	std::unordered_map<GameObjectBase*, LimitedPointerArray<ReferenceData*, ARRAY_NUM>*> source_map_;		//!< �L�[�̃I�u�W�F�N�g���Q�ƌ��̃}�b�v
	std::unordered_map<GameObjectBase*, LimitedPointerArray<ReferenceData*, ARRAY_NUM>*> destination_map_;	//!< // �L�[�̃I�u�W�F�N�g���Q�Ɛ�̃}�b�v


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �f�X�g���N�^
	//! @param void �Ȃ�
	//----------------------------------------
	~GameObjectReferenceManager();

	//----------------------------------------
	//! @brief �Q�ƃf�[�^�ǉ��֐�
	//! @details
	//! @param source      �Q�ƌ��I�u�W�F�N�g
	//! @param pointer     �Q�ƃ|�C���^
	//! @param destination �Q�Ɛ�I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	void AddReference(GameObjectBase* source, void* pointer,
					  GameObjectBase* destination);

	//----------------------------------------
	//! @brief ����֐�
	//! @details
	//! @param object �Q�[���I�u�W�F�N�g���N���X
	//! @retval void �Ȃ�
	//----------------------------------------
	void Release(GameObjectBase* object);

	//----------------------------------------
	//! @brief �S�J���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void AllRelease();

private:
	//----------------------------------------
	//! @brief �Q�ƌ��ǉ��֐�
	//! @details
	//! @param source      �Q�ƌ��I�u�W�F�N�g
	//! @param pointer     �Q�ƃ|�C���^
	//! @param destination �Q�Ɛ�I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	void AddSource(GameObjectBase* source, void* pointer,
				   GameObjectBase* destination);

	//----------------------------------------
	//! @brief �Q�Ɛ�ǉ��֐�
	//! @details
	//! @param source      �Q�ƌ��I�u�W�F�N�g
	//! @param pointer     �Q�ƃ|�C���^
	//! @param destination �Q�Ɛ�I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	void AddDestination(GameObjectBase* source, void* pointer,
						GameObjectBase* destination);

	//----------------------------------------
	//! @brief �Q�ƌ�����֐�
	//! @details
	//! @param object �Q�[���I�u�W�F�N�g���N���X
	//! @retval void �Ȃ�
	//----------------------------------------
	void ReleaseSource(GameObjectBase* object);

	//----------------------------------------
	//! @brief �Q�Ɛ����֐�
	//! @details
	//! @param object �Q�[���I�u�W�F�N�g���N���X
	//! @retval void �Ȃ�
	//----------------------------------------
	void ReleaseDestination(GameObjectBase* object);
};



#endif
