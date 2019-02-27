//================================================================================
//!	@file	 BulletPhysicsConstraint.h
//!	@brief	 �o���b�g�t�B�W�b�N�X�S��Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/09
//================================================================================
#ifndef	_BULLET_PHYSICS_CONSTRAINT_H_
#define _BULLET_PHYSICS_CONSTRAINT_H_



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
//! @brief   �o���b�g�t�B�W�b�N�X�S��Class
//!
//! @details �o���b�g�t�B�W�b�N�X�̍S��Class
//************************************************************
class BulletPhysicsConstraint
{
//====================
// �񋓌^��`
//====================
private:
	enum class Type
	{
		NONE = -1,
		POINT_TO_POINT,
		MAX
	};


//====================
// �ϐ�
//====================
private:
	btTypedConstraint* constraint_ = nullptr;		//!< �S��
	Type type_ = Type::NONE;						//!< �^�C�v
	int reference_counter_ = 0;						//!< �Q�ƃJ�E���^


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �S���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval btTypedConstraint* �S��
	//----------------------------------------
	btTypedConstraint* getpConstraint();

	//----------------------------------------
	//! @brief �^�C�v�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Type �^�C�v
	//----------------------------------------
	Type getType();


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �|�C���g�ƃ|�C���g�S���������֐�
	//! @details
	//! @param *rigid_body0 ����0
	//! @param *rigid_body1 ����1
	//! @param *point0      �|�C���g0(���[�J�����W)
	//! @param *point1      �|�C���g1(���[�J�����W)
	//! @retval void �Ȃ�
	//----------------------------------------
	void InitPointToPoint(btRigidBody* rigid_body0, btRigidBody* rigid_body1,
						  Vector3D* point0, Vector3D* point1);

	//----------------------------------------
	//! @brief 1�̎�����]����S���������֐�
	//! @details
	//! @param *rigid_body0 ����0
	//! @param *rigid_body1 ����1
	//! @param *point0      �|�C���g0(���[�J�����W)
	//! @param *point1      �|�C���g1(���[�J�����W)
	//! @param angle_min    �ŏ��p�x1(1.0f~0.0f��1.0f�ɋ߂��قǎ��R������)
	//! @param angle_max    �ő�p�x0(1.0f~0.0f��1.0f�ɋ߂��قǎ��R������)
	//! @param *axis        ��]��
	//! @retval void �Ȃ�
	//----------------------------------------
	void InitHinge(btRigidBody* rigid_body0, btRigidBody* rigid_body1,
				   Vector3D* point0, Vector3D* point1, 
				   float angle_min, float angle_max, Vector3D* axis);

	//----------------------------------------
	//! @brief �ڑ��_�Ƃ���𒆐S�Ƃ���2���̍S���������֐�
	//! @details
	//! @param *rigid_body0 ����0
	//! @param *rigid_body1 ����1
	//! @param *anchor      �ڑ��_(���[���h���W)
	//! @param angle_min0   �ŏ��p�x0(1.0f~0.0f��1.0f�ɋ߂��قǎ��R������)
	//! @param angle_min1   �ŏ��p�x1(1.0f~0.0f��1.0f�ɋ߂��قǎ��R������)
	//! @param angle_max0   �ő�p�x0(1.0f~0.0f��1.0f�ɋ߂��قǎ��R������)
	//! @param angle_max1   �ő�p�x1(1.0f~0.0f��1.0f�ɋ߂��قǎ��R������)
	//! @param *axis0       ��]��0
	//! @param *axis1       ��]��1
	//! @retval void �Ȃ�
	//----------------------------------------
	void InitUniversal(btRigidBody* rigid_body0, btRigidBody* rigid_body1,
					   Vector3D* anchor, float angle_min0, float angle_min1,
					   float angle_max0, float angle_max1,
					   Vector3D* axis0, Vector3D* axis1);

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
};



#endif