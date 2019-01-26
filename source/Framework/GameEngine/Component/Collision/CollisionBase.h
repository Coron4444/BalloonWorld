//================================================================================
//!	@file	 CollisionBase.h
//!	@brief	 �Փ�BaseClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================
#ifndef	_COLLISION_BASE_H_
#define _COLLISION_BASE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "../../ComponentBase/ComponentBase.h"
#include "CollisionObjects/CollisionObjects.h"

#include <LimitedPointerArray/LimitedPointerArray.h>
#include <Transform/Transform.h>
#include <Vector3D.h>



//************************************************************														   
//! @brief   �Փ�BaseClass
//!
//! @details �Փ˂�BaseClass
//************************************************************
class CollisionBase : public ComponentBase
{
//====================
// �񋓌^��`
//====================
public:
	// �^�C�v
	enum Type
	{
		NONE = -1,
		PLAYER,
		COIN,
		ENEMY,
		GOAL,
		MAX
	};


//====================
// �萔
//====================
private:
	static const unsigned ARRAY_NUM = 10000;		//!< �z��


//====================
// �ϐ�
//====================
private:
	LimitedPointerArray<CollisionObjects*, ARRAY_NUM> collision_objects_;	//!< �����Փ˃I�u�W�F�N�g�z��
	Type type_ = Type::NONE;			//!< �^�C�v
	bool is_judgment_ground_ = true;	//!< �n�ʂƂ̔���t���O


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �z��̍Ō�̖����̃C���f�b�N�X�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval unsigned �z��̍Ō�̖����̃C���f�b�N�X
	//----------------------------------------
	unsigned getEndIndexOfArray();
	
	//----------------------------------------
	//! @brief �����Փ˃I�u�W�F�N�g�擾�֐�
	//! @details
	//! @param index �����Փ˃I�u�W�F�N�g�̃C���f�b�N�X
	//! @retval CollisionObjects* �����Փ˃I�u�W�F�N�g
	//----------------------------------------
	CollisionObjects* getpCollisionObjects(unsigned index);
	
	//----------------------------------------
	//! @brief �^�C�v�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Type �^�C�v
	//----------------------------------------
	Type getType();
	
	//----------------------------------------
	//! @brief �^�C�v�ݒ�֐�
	//! @details
	//! @param value �^�C�v
	//! @retval void �Ȃ�
	//----------------------------------------
	void setType(Type value);
	
	//----------------------------------------
	//! @brief �n�ʂƂ̔���t���O�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval bool �n�ʂƂ̔���t���O
	//----------------------------------------
	bool getIsJudgmentGround();
	
	//----------------------------------------
	//! @brief �n�ʂƂ̔���t���O�ݒ�֐�
	//! @details
	//! @param value �n�ʂƂ̔���t���O
	//! @retval void �Ȃ�
	//----------------------------------------
	void setIsJudgmentGround(bool value);


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief ���z�f�X�g���N�^
	//! @details
	//! @param void �Ȃ�
	//----------------------------------------
	virtual ~CollisionBase() = 0;

	//----------------------------------------
	//! @brief �Փˎ��֐�
	//! @details
	//! @param *hit_collision ����̏Փˊ��N���X
	//! @param *hit_object    ����̏Փ˃I�u�W�F�N�g
	//! @param *hit_my_object �����̏Փ˃I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void HitCollision(CollisionBase* hit_collision,
							  CollisionObject* hit_object,
							  CollisionObject* hit_my_object) = 0;

	//----------------------------------------
	//! @brief ��Փˎ��֐�
	//! @details
	//! @param *hit_collision ����̏Փˊ��N���X
	//! @param *hit_object    ����̏Փ˃I�u�W�F�N�g
	//! @param *hit_my_object �����̏Փ˃I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void NotHitCollision(CollisionBase*	hit_collision,
								 CollisionObject* hit_object,
								 CollisionObject* hit_my_object) = 0;

	//----------------------------------------
	//! @brief �t�B�[���h�Ƃ̏Փˎ��֐�
	//! @details
	//! @param position_y �t�B�[���h�̍���
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void HitGround(float position_y) = 0;

	//----------------------------------------
	//! @brief �t�B�[���h�Ƃ̔�Փˎ��֐�
	//! @details
	//! @param position_y �t�B�[���h�̍���
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void NotHitGround(float position_y) = 0;

	//----------------------------------------
	//! @brief �����Փ˃I�u�W�F�N�g�ǉ��֐�
	//! @details
	//! @param *object �ǉ������������Փ˃I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	void AddCollisionObjectsToArray(CollisionObjects* object);

	//----------------------------------------
	//! @brief �����Փ˃I�u�W�F�N�g�㏑���֐�
	//! @details
	//! @param *object �Â������Փ˃I�u�W�F�N�g
	//! @param *object �V���������Փ˃I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	void OverwriteArrayCollisionsObject(CollisionObjects* old_object,
										CollisionObjects* new_object);

	//----------------------------------------
	//! @brief �����Փ˃I�u�W�F�N�g����֐�
	//! @details
	//! @param *object ���������������Փ˃I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	void ReleaseCollisionObjectsFromArray(CollisionObjects* object);

	//----------------------------------------
	//! @brief �����Փ˃I�u�W�F�N�g�S����֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void ReleaseAllCollisionObjectsFromArray();

	//----------------------------------------
	//! @brief �߂荞�݉����֐�
	//! @details
	//! @param *transform  �߂荞�݂��������������
	//! @param *hit_vector �߂荞�݃x�N�g��
	//! @retval void �Ȃ�
	//----------------------------------------
	void EliminationOfNesting(Transform* transform, const Vec3* hit_vector);
};



#endif