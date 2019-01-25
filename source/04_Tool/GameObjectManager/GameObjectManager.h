//================================================================================
//
//    �Q�[���I�u�W�F�N�g�}�l�[�W���N���X(static)
//    Author : Araki Kai                                �쐬�� : 2018/07/13
//
//================================================================================

#ifndef	_GAME_OBJECT_MANAGER_H_
#define _GAME_OBJECT_MANAGER_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <LimitedPointerArray\LimitedPointerArray.h>
#include "GameObjectReferenceManager\GameObjectReferenceManager.h"
#include "ComponentManager/UpdateManager/UpdateManager.h"
#include "ComponentManager/DrawManager/DrawManager.h"
#include "ComponentManager/CollisionManager/CollisionManager.h"



//****************************************
// �N���X�錾
//****************************************
class GameObjectBase;



/*********************************************************//**
* @brief
* �Q�[���I�u�W�F�N�g�}�l�[�W���N���X
*
* �Q�[���I�u�W�F�N�g�S�̂̊Ǘ�������N���X
*************************************************************/
class GameObjectManager
{
//==============================
// �萔
//==============================
public:
	static const unsigned ARRAY_NUM = 1000;		//!< �z��


//==============================
// �ÓI�����o�ϐ�
//==============================
private:
	static LimitedPointerArray<GameObjectBase*, ARRAY_NUM> all_game_object_;	//!< �S�Q�[���I�u�W�F�N�g�z��
	static LimitedPointerArray<GameObjectBase*, ARRAY_NUM> await_add_;			//!< �ǉ��҂��z��
	static LimitedPointerArray<GameObjectBase*, ARRAY_NUM> await_release_;		//!< ����҂��z��

	static GameObjectReferenceManager reference_manager_;	//!< �Q�ƃ}�l�[�W��
	static UpdateManager update_manager_;					//!< �X�V�}�l�[�W��
	static DrawManager draw_manager_;						//!< �`��}�l�[�W��
	static CollisionManager collision_manager_;				//!< �Փ˃}�l�[�W��


//==============================
// �ÓI�����o�֐�
//==============================
public:
	/**
	* @brief
	* �������֐�
	*/
	static void Init();

	/**
	* @brief
	* �I���֐�
	*/
	static void Uninit();

	/**
	* @brief
	* �V�[���ύX���̏I���֐�
	*/
	static void UninitWhenChangeScene();

	/**
	* @brief
	* �X�V�֐�
	*/
	static void Update();

	/**
	* @brief
	* �`��֐�
	*/
	static void Draw();

	/**
	* @brief
	* �S�Q�[���I�u�W�F�N�g���Z�b�g�֐�
	*/
	static void AllReset();

	/**
	* @brief
	* �Q�[���I�u�W�F�N�g���N���X�̒ǉ��֐�
	*/
	static void AddGameObjectBaseToArray(GameObjectBase* game_object);

	/**
	* @brief
	* �Q�[���I�u�W�F�N�g���N���X�̉���֐�
	*/
	static void ReleaseGameObjectBaseFromArray(GameObjectBase* game_object);

	/**
	* @brief
	* �Q�[���I�u�W�F�N�g�Q�Ƃ̎擾
	*/
	template<class Type>
	static void GetPointer_RegistrationReference(GameObjectBase* reference_object,
												 Type* reference_destination,
												 Type* reference_pointer)
	{
		// �Q�Ɛ�̑��
		*reference_pointer = reference_destination;

		// �Q�Ƃ̓o�^
		reference_manager_.RegistrationReference(reference_object,
			(void*)reference_pointer,
												 (GameObjectBase*)reference_destination);
	}

	// �v���p�e�B
	static UpdateManager* GetUpdateManager() { return &update_manager_; }
	static DrawManager* GetDrawManager() { return &draw_manager_; }
	static CollisionManager* GetCollisionManager() { return &collision_manager_; }


private:
	/**
	* @brief
	* �ǉ��҂��z��̒��g��ǉ��֐�
	*/
	static void AddContentsOfAwaitAddArray();

	/**
	* @brief
	* ����҂��z��̒��g������֐�
	*/
	static void ReleaseContentsOfAwaitReleaseArray();

	/**
	* @brief
	* �R���|�[�l���g���}�l�[�W���[�֐ݒ�֐�
	*/
	static void SetComponentToManager(GameObjectBase* game_object);

	/**
	* @brief
	* �R���|�[�l���g���}�l�[�W���[�������֐�
	*/
	static void ReleaseComponentFromManager(GameObjectBase* game_object);

	/**
	* @brief
	* �S�Q�[���I�u�W�F�N�g�̉���֐�
	*/
	static void AllRelease();


//==============================
// ��ÓI�����o�֐�
//==============================
private:
	/**
	* @brief
	* �R���X�g���N�^(�폜)
	*/
	GameObjectManager() = delete;

	/**
	* @brief
	* �R�s�[�R���X�g���N�^(�폜)
	*/
	GameObjectManager(const GameObjectManager& value) = delete;

	/**
	* @brief
	* ������Z�q�̃I�[�o�[���[�h(�폜)
	*/
	GameObjectManager& operator = (const GameObjectManager& value) = delete;
};



#endif
