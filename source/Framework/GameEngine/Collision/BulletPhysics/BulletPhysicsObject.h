//================================================================================
//!	@file	 BulletPhysicsManager.h
//!	@brief	 �o���b�g�t�B�W�b�N�X�I�u�W�F�N�gClass
//! @details Singleton
//!	@author  Kai Araki									@date 2019/02/06
//================================================================================
#ifndef	_COLLISION_OBJECT_H_
#define _COLLISION_OBJECT_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "CollisionShape/AABB.h"
#include "CollisionShape/Capsule.h"
#include "CollisionShape/Cylinder.h"
#include "CollisionShape/OBB.h"
#include "CollisionShape/Plane.h"
#include "CollisionShape/LineSegment.h"
#include "CollisionShape/Sphere.h"
#include "CollisionShape/Triangle.h"

#include <Tool/Vector3D.h>



//************************************************************														   
//! @brief   �Փ˃I�u�W�F�N�gClass
//!
//! @details �Փ˃I�u�W�F�N�g��Class
//************************************************************
class CollisionObject
{
//====================
// �萔
//====================
private:
	static const int TAG_NONE = -1;			//!< �^�O�Ȃ����̒l


//====================
// �ϐ�
//====================
private:

	CollisionShapeBase* collision_shape_;		//!< �`��
	Vector3D hit_vector_;						//!< �߂荞�݃x�N�g��
	int	tag_;					//!< �^�O
	bool is_judgment_ = true;	//!< ���肷�邩�t���O
	bool is_trigger_ = true;	//!< �������Z�����邩�̃t���O


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �^�O�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval int �^�O
	//----------------------------------------
	int	getTag();

	//----------------------------------------
	//! @brief �Փˌ`��擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval CollisionShapeBase* �Փˌ`��
	//----------------------------------------
	CollisionShapeBase* getpCollisionShape();

	//----------------------------------------
	//! @brief �߂荞�݃x�N�g���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D* �߂荞�݃x�N�g��
	//----------------------------------------
	Vector3D* getpHitVector();

	//----------------------------------------
	//! @brief �߂荞�݃x�N�g���ݒ�֐�
	//! @details
	//! @param value �߂荞�݃x�N�g��
	//! @retval void �Ȃ�
	//----------------------------------------
	void setHitVector(Vector3D value);

	//----------------------------------------
	//! @brief ���肷�邩�t���O�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval bool ���肷�邩�t���O
	//----------------------------------------
	bool getIsJudgment();

	//----------------------------------------
	//! @brief ���肷�邩�t���O�ݒ�֐�
	//! @details
	//! @param value ���肷�邩�t���O
	//! @retval void �Ȃ�
	//----------------------------------------
	void setIsJudgment(bool value);


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �R���X�g���N�^
	//! @details
	//! @param *collision_shape �Փˌ`��
	//! @param collision_shape  �^�O
	//----------------------------------------
	CollisionObject(CollisionShapeBase* collision_shape, int tag);

	//----------------------------------------
	//! @brief �f�X�g���N�^
	//! @details
	//! @param void �Ȃ�
	//----------------------------------------
	~CollisionObject();

	//----------------------------------------
	//! @brief �Փ˗p�f�[�^���Z�b�g�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void ResetHitData();
};



#endif
