//================================================================================
//!	@file	 GameObjectManager.h
//!	@brief	 �Q�[���I�u�W�F�N�g�}�l�[�W��Class
//! @details Singleton
//!	@author  Kai Araki									@date 2018/07/13
//================================================================================
#ifndef	_GAME_OBJECT_MANAGER_H_
#define _GAME_OBJECT_MANAGER_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "GameObjectReferenceManager.h"
#include "../../Update/UpdateManager/UpdateManager.h"
#include "../../Draw/DrawManager/DrawManager.h"
#include "../../Collision/CollisionManager/CollisionManager.h"

#include <Tool/LimitedPointerArray.h>



//****************************************
// �N���X�錾
//****************************************
class GameObjectBase;



//************************************************************														   
//! @brief   �Q�[���I�u�W�F�N�g�}�l�[�W��Class(Singleton)
//!
//! @details �Q�[���I�u�W�F�N�g�̃}�l�[�W��Class(Singleton)
//************************************************************
class GameObjectManager
{
//====================
// �萔
//====================
private:
	static const unsigned ARRAY_NUM = 1000;		//!< �z��


//====================
// static�ϐ�
//====================
private:
	static GameObjectManager* instance_;	//!< �C���X�^���X


//====================
// static�v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �C���X�^���X�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval GameObjectManager* �C���X�^���X
	//----------------------------------------
	static GameObjectManager* getpInstance();


//====================
// static�֐�
//====================
public:
	//----------------------------------------
	//! @brief �C���X�^���X����֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	static void ReleaseInstance();


//====================
// �ϐ�
//====================
private:
	LimitedPointerArray<GameObjectBase*, ARRAY_NUM> all_game_object_;	//!< �S�Q�[���I�u�W�F�N�g�z��
	LimitedPointerArray<GameObjectBase*, ARRAY_NUM> await_add_;			//!< �ǉ��҂��z��
	LimitedPointerArray<GameObjectBase*, ARRAY_NUM> await_release_;		//!< ����҂��z��

	GameObjectReferenceManager reference_manager_;	//!< �Q�ƃ}�l�[�W��
	UpdateManager update_manager_;					//!< �X�V�}�l�[�W��
	DrawManager draw_manager_;						//!< �`��}�l�[�W��
	CollisionManager collision_manager_;			//!< �Փ˃}�l�[�W��


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �X�V�}�l�[�W���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval UpdateManager* �X�V�}�l�[�W��
	//----------------------------------------
	UpdateManager* getpUpdateManager();

	//----------------------------------------
	//! @brief �`��}�l�[�W���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval DrawManager* �`��}�l�[�W��
	//----------------------------------------
	DrawManager* getpDrawManager();

	//----------------------------------------
	//! @brief �Փ˃}�l�[�W���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval CollisionManager* �Փ˃}�l�[�W��
	//----------------------------------------
	CollisionManager* getpCollisionManager();

	//----------------------------------------
	//! @brief �Q�[���I�u�W�F�N�g�Q�Ǝ擾�֐�
	//! @details
	//! @param reference_object      �Q�ƌ��I�u�W�F�N�g
	//! @param reference_destination �Q�Ɛ�I�u�W�F�N�g
	//! @param reference_pointer     �Q�ƃ|�C���^
	//! @retval void �Ȃ�
	//----------------------------------------
	template<class Type>
	void getpRegistrationReference(GameObjectBase* reference_object,
								   Type* reference_destination,
								   Type* reference_pointer)
	{
		// �Q�Ɛ�̑��
		*reference_pointer = reference_destination;

		// �Q�Ƃ̓o�^
		reference_manager_.AddReference(reference_object,
			(void*)reference_pointer,
										(GameObjectBase*)reference_destination);
	}


//====================
// �֐�
//====================
private:
	//----------------------------------------
	//! @brief �R���X�g���N�^
	//! @param void �Ȃ�
	//----------------------------------------
	GameObjectManager();

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
	//! @brief �`��֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Draw();

	//----------------------------------------
	//! @brief ���Z�b�g�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Reset();

	//----------------------------------------
	//! @brief �Q�[���I�u�W�F�N�g���N���X�ǉ��֐�
	//! @details
	//! @param *game_object �Q�[���I�u�W�F�N�g���N���X
	//! @retval void �Ȃ�
	//----------------------------------------
	void AddGameObjectBaseToArray(GameObjectBase* game_object);

	//----------------------------------------
	//! @brief �Q�[���I�u�W�F�N�g���N���X����֐�
	//! @details
	//! @param *game_object �Q�[���I�u�W�F�N�g���N���X
	//! @retval void �Ȃ�
	//----------------------------------------
	void ReleaseGameObjectBaseFromArray(GameObjectBase* game_object);

private:
	//----------------------------------------
	//! @brief �ǉ��҂��̒ǉ��֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void AddContentsOfAwaitAddArray();

	//----------------------------------------
	//! @brief ����҂��̉���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void ReleaseContentsOfAwaitReleaseArray();

	//----------------------------------------
	//! @brief �R���|�[�l���g���}�l�[�W���[�֒ǉ��֐�
	//! @details
	//! @param *game_object �Q�[���I�u�W�F�N�g���N���X
	//! @retval void �Ȃ�
	//----------------------------------------
	void AddComponentToManager(GameObjectBase* game_object);

	//----------------------------------------
	//! @brief �R���|�[�l���g���}�l�[�W���[�������֐�
	//! @details
	//! @param *game_object �Q�[���I�u�W�F�N�g���N���X
	//! @retval void �Ȃ�
	//----------------------------------------
	void ReleaseComponentFromManager(GameObjectBase* game_object);

	//----------------------------------------
	//! @brief ����֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Release();


//====================
// �����ς݊֐�
//====================
private:
	GameObjectManager(const GameObjectManager& class_name) = delete;
	GameObjectManager& operator = (const GameObjectManager& class_name) = delete;
};



#endif
