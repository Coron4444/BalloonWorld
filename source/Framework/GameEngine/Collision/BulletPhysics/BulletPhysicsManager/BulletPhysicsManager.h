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

#include <vector>



//****************************************
// �N���X�錾
//****************************************
class BulletPhysicsDebug;
class Camera;



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
	BulletPhysicsDebug* debug_ = nullptr;						//!< �f�o�b�O�\��

	// �e�X�g�p
	std::vector<btCollisionShape*> shape_;
	std::vector<btRigidBody*> rigid_body_;
	std::vector<btDefaultMotionState*> motion_state_;

	btCollisionShape* ground_;						// �`
	btDefaultMotionState* ground_motion_state_;		// �O�����獄�̂𑀍삷��p
	btRigidBody* ground_rigid_body_;				// ����

	// �g�ݍ��킹
	btCollisionShape* comp_shape_[2];
	btRigidBody* comp_rigid_body_;
	btDefaultMotionState* comp_motion_state_;
	btCompoundShape* comp_;


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �f�o�b�O�ݒ�֐�
	//! @details
	//! @param value �f�o�b�O�t���O
	//! @retval void �Ȃ�
	//----------------------------------------
	void setDebug(bool value);

	//----------------------------------------
	//! @brief ���[�V�����X�e�[�g�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval btDefaultMotionState* ���[�V�����X�e�[�g�擾
	//----------------------------------------
	btDefaultMotionState* getpMotionState();

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

	//----------------------------------------
	//! @brief �f�o�b�O�\���֐�
	//! @details
	//! @param camera �J����
	//! @retval void �Ȃ�
	//----------------------------------------
	void DrawDebug(Camera* camera);


//====================
// �����ς݊֐�
//====================
private:
	BulletPhysicsManager(const BulletPhysicsManager& class_name) = delete;
	BulletPhysicsManager& operator = (const BulletPhysicsManager& class_name) = delete;
};



#endif