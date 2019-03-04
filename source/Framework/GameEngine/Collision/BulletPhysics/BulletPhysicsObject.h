//================================================================================
//!	@file	 BulletPhysicsObject.h
//!	@brief	 �o���b�g�t�B�W�b�N�X�I�u�W�F�N�gClass
//! @details 
//!	@author  Kai Araki									@date 2019/02/08
//================================================================================
#ifndef	_BULLET_PHYSICS_OBJECT_H_
#define _BULLET_PHYSICS_OBJECT_H_



//****************************************
// �C���N���[�h��
//****************************************
#pragma warning(push)
#pragma warning(disable: 4100)
#pragma warning(disable: 4099)
#pragma warning(disable: 4127)
#include <btBulletDynamicsCommon.h>
#pragma warning(pop)

#include <Tool/Vector3D.h>



//************************************************************														   
//! @brief   �o���b�g�t�B�W�b�N�X�I�u�W�F�N�gClass
//!
//! @details �o���b�g�t�B�W�b�N�X�̃I�u�W�F�N�gClass
//************************************************************
class BulletPhysicsObject
{
//====================
// �񋓌^��`
//====================
private:
	enum class Type
	{
		NONE = -1,
		SPHERE,
		OBB,
		CAPSULE,
		MAX
	};


//====================
// �ϐ�
//====================
private:
	Type type_ = Type::NONE;						//!< �^�C�v
	btCollisionShape* collision_shape_ = nullptr;	//!< �Փˌ`��
	btDefaultMotionState* motion_state_ = nullptr;	//!< �O�����獄�̂𑀍삷��n���h��
	btRigidBody* rigid_body_ = nullptr;				//!< ����
	int reference_counter_ = 0;						//!< �Q�ƃJ�E���^


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �^�C�v�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Type �^�C�v
	//----------------------------------------
	Type getType();

	//----------------------------------------
	//! @brief �Փˌ`��擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval btCollisionShape* �Փˌ`��
	//----------------------------------------
	btCollisionShape* getpCollisionShape();

	//----------------------------------------
	//! @brief �O�����獄�̂𑀍삷��n���h�����֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval btDefaultMotionState* �O�����獄�̂𑀍삷��n���h��
	//----------------------------------------
	btDefaultMotionState* getpMotionState();

	//----------------------------------------
	//! @brief ���̎擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval btRigidBody* ����
	//----------------------------------------
	btRigidBody* getpRigidBody();

	//----------------------------------------
	//! @brief ���W�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D ���W
	//----------------------------------------
	Vector3D getPosition();

	//----------------------------------------
	//! @brief ���W�ݒ�֐�
	//! @details
	//! @param value ���W
	//! @retval void �Ȃ�
	//----------------------------------------
	void setPosition(Vector3D value);

	//----------------------------------------
	//! @brief �N�H�[�^�j�I���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Quaternion �N�H�[�^�j�I��
	//----------------------------------------
	Quaternion getQuaternion();

	//----------------------------------------
	//! @brief Kinematic���̐ݒ�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void setKinematic();


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief ���������֐�
	//! @details
	//! @param mass        ����
	//! @param *inertia    �������[�����g
	//! @param *position   ���W
	//! @param *quaternion �N�H�[�^�j�I��
	//! @param radius      ���a
	//! @retval void �Ȃ�
	//----------------------------------------
	void InitSphere(float mass, Vector3D* inertia, Vector3D* position,
					Quaternion* quaternion, float radius);

	//----------------------------------------
	//! @brief OBB�������֐�
	//! @details
	//! @param mass              ����
	//! @param *inertia          �������[�����g
	//! @param *position         ���W
	//! @param *quaternion       �N�H�[�^�j�I��
	//! @param *edge_half_length �ӂ̔����̒���
	//! @retval void �Ȃ�
	//----------------------------------------
	void InitOBB(float mass, Vector3D* inertia, Vector3D* position,
				 Quaternion* quaternion, Vector3D* edge_half_length);

	//----------------------------------------
	//! @brief ���������֐�
	//! @details
	//! @param mass        ����
	//! @param *inertia    �������[�����g
	//! @param *position   ���W
	//! @param *quaternion �N�H�[�^�j�I��
	//! @param radius      ���a
	//! @param height      ����
	//! @retval void �Ȃ�
	//----------------------------------------
	void InitCapsule(float mass, Vector3D* inertia, Vector3D* position,
					 Quaternion* quaternion, float radius, float height);

	//----------------------------------------
	//! @brief ����֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Release();

	//----------------------------------------
	//! @brief ��������֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void ForcedRelease();

	//----------------------------------------
	//! @brief �Q�ƃJ�E���^�ǉ��֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void AddReferenceCounter();

	//----------------------------------------
	//! @brief �����x�ǉ��֐�
	//! @details
	//! @param velocity    �����x
	//! @param power_point �͓_
	//! @retval void �Ȃ�
	//----------------------------------------
	void AddVelocity(Vector3D velocity, Vector3D power_point = {0.0f, 0.0f, 0.0f});

	//----------------------------------------
	//! @brief �����x�ǉ��֐�
	//! @details
	//! @param acceleration �����x
	//! @param power_point  �͓_
	//! @retval void �Ȃ�
	//----------------------------------------
	void AddAcceleration(Vector3D acceleration, Vector3D power_point = {0.0f, 0.0f, 0.0f});

private:
	//----------------------------------------
	//! @brief ���ʏ������֐�
	//! @details
	//! @param mass        ����
	//! @param *inertia    �������[�����g
	//! @param *position   ���W
	//! @param *quaternion �N�H�[�^�j�I��
	//! @retval void �Ȃ�
	//----------------------------------------
	void InitCommon(float mass, Vector3D* inertia,
					Vector3D* position, Quaternion* quaternion);
};



#endif