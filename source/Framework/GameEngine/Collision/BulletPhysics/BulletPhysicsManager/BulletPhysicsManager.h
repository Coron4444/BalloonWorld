//================================================================================
//!	@file	 BulletPhysicsManager.h
//!	@brief	 �o���b�g�t�B�W�b�N�X�}�l�[�W��Class
//! @details Singleton
//!	@author  Kai Araki									@date 2019/02/06
//================================================================================
#ifndef	_BULLET_PHYSICS_MANAGER_H_
#define _BULLET_PHYSICS_MANAGER_H_



//****************************************
// �C���N���[�h��
//****************************************
#pragma warning(push)
#pragma warning(disable: 4100)
#pragma warning(disable: 4099)
#pragma warning(disable: 4127)
#include <btBulletDynamicsCommon.h>
#pragma warning(pop)



//************************************************************														   
//! @brief   �o���b�g�t�B�W�b�N�X�}�l�[�W��Class(Singleton)
//!
//! @details �o���b�g�t�B�W�b�N�X�̃}�l�[�W��Class(Singleton)
//************************************************************
class BulletPhysicsManager
{
//====================
// �萔
//====================
private:
	static const btVector3 DEFULT_GRAVITY;	//!< �f�t�H���g�̏d�͒l
	static const btScalar TIME_STEP;		//!< �X�V����Ɛi�ޕb��
	static const int MAX_SUB_STEP;			//!< �X�V�ׂ̍���


//====================
// static�ϐ�
//====================
private:
	static BulletPhysicsManager* instance_;		//!< �C���X�^���X


//====================
// static�v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �C���X�^���X�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval BulletPhysicsManager* �C���X�^���X
	//----------------------------------------
	static BulletPhysicsManager* getpInstance();


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
	btDefaultCollisionConfiguration* configuration_ = nullptr;	//!< �Փˌv�Z�̐ݒ�
	btCollisionDispatcher* dispatcher_ = nullptr;				//!< �Փˌv�Z�̐ݒ�
	btDbvtBroadphase* broadphase_ = nullptr;					//!< �u���[�h�t�F�[�Y�@(�Փ˂���\���̂���I�u�W�F�N�g�̌��o)
	btSequentialImpulseConstraintSolver* solver_ = nullptr;		//!< �S���\���o(�I�u�W�F�N�g�̏d�Ȃ�����Ȃǂ̐ݒ�)
	btDiscreteDynamicsWorld* dynamics_world_ = nullptr;			//!< Bullet���[���h


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �I�u�W�F�N�g�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval TextureObject* �I�u�W�F�N�g
	//----------------------------------------


//====================
// �֐�
//====================
private:
	//----------------------------------------
	//! @brief �R���X�g���N�^
	//! @param void �Ȃ�
	//----------------------------------------
	BulletPhysicsManager();

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
	//! @brief �X�V�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Update();



//====================
// �����ς݊֐�
//====================
private:
	BulletPhysicsManager(const BulletPhysicsManager& class_name) = delete;
	BulletPhysicsManager& operator = (const BulletPhysicsManager& class_name) = delete;
};



#endif