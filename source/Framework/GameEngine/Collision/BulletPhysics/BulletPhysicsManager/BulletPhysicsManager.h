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
#include <list>

#include "../BulletPhysicsObject.h"
#include "../BulletPhysicsConstraint.h"

#include <Tool/Vector3D.h>



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
	btDynamicsWorld* dynamics_world_ = nullptr;					//!< Bullet���[���h
	BulletPhysicsDebug* debug_ = nullptr;						//!< �f�o�b�O�\��
	std::list<BulletPhysicsObject*> object_;					//!< �I�u�W�F�N�g���X�g
	std::list<BulletPhysicsConstraint*> constraint_;			//!< �S��


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
	//! @brief ���I�u�W�F�N�g�擾�֐�
	//! @details
	//! @param mass       ����
	//! @param inertia    �������[�����g
	//! @param position   ���W
	//! @param quaternion �N�H�[�^�j�I��
	//! @param radius     ���a
	//! @retval BulletPhysicsObject* ���I�u�W�F�N�g
	//----------------------------------------
	BulletPhysicsObject* getpObjectSphere(float mass, Vec3 inertia, Vec3 position,
										  Quaternion quaternion, float radius);

	//----------------------------------------
	//! @brief OBB�I�u�W�F�N�g�擾�֐�
	//! @details
	//! @param mass             ����
	//! @param inertia          �������[�����g
	//! @param position         ���W
	//! @param quaternion       �N�H�[�^�j�I��
	//! @param edge_half_length �ӂ̔����̒���
	//! @retval BulletPhysicsObject* OBB�I�u�W�F�N�g
	//----------------------------------------
	BulletPhysicsObject* getpObjectOBB(float mass, Vec3 inertia, Vec3 position,
									   Quaternion quaternion, Vec3 edge_half_length);

	//----------------------------------------
	//! @brief �J�v�Z���I�u�W�F�N�g�擾�֐�
	//! @details
	//! @param mass       ����
	//! @param inertia    �������[�����g
	//! @param position   ���W
	//! @param quaternion �N�H�[�^�j�I��
	//! @param radius     ���a
	//! @param height     ����
	//! @retval BulletPhysicsObject* ���I�u�W�F�N�g
	//----------------------------------------
	BulletPhysicsObject* getpObjectCapsule(float mass, Vec3 inertia, Vec3 position,
										   Quaternion quaternion, float radius, float height);

	//----------------------------------------
	//! @brief �|�C���g�ƃ|�C���g�̍S���ݒ�֐�
	//! @details
	//! @param bullet_object0 �I�u�W�F�N�g0
	//! @param bullet_object1 �I�u�W�F�N�g1
	//! @param point0         �|�C���g0
	//! @param point1         �|�C���g1
	//! @retval BulletPhysicsConstraint* �S��
	//----------------------------------------
	BulletPhysicsConstraint* setConstraintPointToPoint(BulletPhysicsObject* bullet_object0,
													   BulletPhysicsObject* bullet_object1,
													   Vec3 point0, Vec3 point1);

	//----------------------------------------
	//! @brief 1�̎�����]����S���������֐�
	//! @details
	//! @param bullet_object0 �I�u�W�F�N�g0
	//! @param bullet_object1 �I�u�W�F�N�g1
	//! @param point0      �|�C���g0(���[�J�����W)
	//! @param point1      �|�C���g1(���[�J�����W)
	//! @param angle_min    �ŏ��p�x1(1.0f~0.0f��1.0f�ɋ߂��قǎ��R������)
	//! @param angle_max    �ő�p�x0(1.0f~0.0f��1.0f�ɋ߂��قǎ��R������)
	//! @param axis        ��]��
	//! @retval void �Ȃ�
	//----------------------------------------
	BulletPhysicsConstraint* setConstraintHinge(BulletPhysicsObject* bullet_object0,
												BulletPhysicsObject* bullet_object1,
												Vec3 point0, Vec3 point1,
												float angle_min, float angle_max,
												Vec3 axis = {0.0f, 1.0f, 0.0f});

	//----------------------------------------
	//! @brief �ڑ��_�Ƃ���𒆐S�Ƃ���2���̍S���ݒ�֐�
	//! @details
	//! @param *bullet_object0 �I�u�W�F�N�g0
	//! @param *bullet_object1 �I�u�W�F�N�g1
	//! @param anchor          �ڑ��_(���[���h���W)
	//! @param angle_min0      �ŏ��p�x0(1.0f~0.0f��1.0f�ɋ߂��قǎ��R������)
	//! @param angle_min1      �ŏ��p�x1(1.0f~0.0f��1.0f�ɋ߂��قǎ��R������)
	//! @param angle_max0      �ő�p�x0(1.0f~0.0f��1.0f�ɋ߂��قǎ��R������)
	//! @param angle_max1      �ő�p�x1(1.0f~0.0f��1.0f�ɋ߂��قǎ��R������)
	//! @param axis0           ��]��0
	//! @param axis1           ��]��1
	//! @retval BulletPhysicsConstraint* �S��
	//----------------------------------------
	BulletPhysicsConstraint* setConstraintUniversal(BulletPhysicsObject* bullet_object0,
													BulletPhysicsObject* bullet_object1,
													Vec3 anchor,
													float angle_min0, float angle_min1,
													float angle_max0, float angle_max1,
													Vec3 axis0 = {1.0f, 0.0f, 0.0f},
													Vec3 axis1 = {0.0f, 0.0f, 1.0f});


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

	//----------------------------------------
	//! @brief �I�u�W�F�N�g���X�g�������֐�
	//! @details
	//! @param *object �I�u�W�F�N�g���g�̃|�C���^
	//! @retval void �Ȃ�
	//----------------------------------------
	void ReleaseFromTheObjectList(BulletPhysicsObject* object);

	//----------------------------------------
	//! @brief �S�����X�g�������֐�
	//! @details
	//! @param *constraint �S�����g�̃|�C���^
	//! @retval void �Ȃ�
	//----------------------------------------
	void ReleaseFromTheConstraintList(BulletPhysicsConstraint* constraint);


//====================
// �����ς݊֐�
//====================
private:
	BulletPhysicsManager(const BulletPhysicsManager& class_name) = delete;
	BulletPhysicsManager& operator = (const BulletPhysicsManager& class_name) = delete;
};



#endif