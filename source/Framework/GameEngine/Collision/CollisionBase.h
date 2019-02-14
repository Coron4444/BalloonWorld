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
#include "../ComponentBase.h"
#include "CollisionObject.h"
#include "CollisionManager/CollisionCalculation.h"
#include "CollisionInformation.h"

#include <Tool/LimitedPointerArray.h>
#include <Tool/Transform.h>
#include <Tool/Vector3D.h>



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
	enum class Type
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
	Type type_ = Type::NONE;			//!< �^�C�v
	LimitedPointerArray<CollisionObject*, ARRAY_NUM> collision_object_;	//!< �Փ˃I�u�W�F�N�g�z��
	bool is_judgment_ground_ = true;	//!< �n�ʂƂ̔���t���O


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
	//! @brief �^�C�v�ݒ�֐�
	//! @details
	//! @param value �^�C�v
	//! @retval void �Ȃ�
	//----------------------------------------
	void setType(Type value);

	//----------------------------------------
	//! @brief �z��̍Ō�̖����̃C���f�b�N�X�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval unsigned �z��̍Ō�̖����̃C���f�b�N�X
	//----------------------------------------
	unsigned getEndIndexOfArray();

	//----------------------------------------
	//! @brief �Փ˃I�u�W�F�N�g�擾�֐�
	//! @details
	//! @param index �C���f�b�N�X
	//! @retval CollisionObject* �Փ˃I�u�W�F�N�g
	//----------------------------------------
	CollisionObject* getpCollisionObject(unsigned index);

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
	//! @param *information �Փˏ��
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void HitCollision(CollisionInformation* information) = 0;

	//----------------------------------------
	//! @brief �t�B�[���h�Ƃ̏Փˎ��֐�
	//! @details
	//! @param position_y �t�B�[���h�̍���
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void HitGround(float position_y) = 0;

	//----------------------------------------
	//! @brief �Փ˃I�u�W�F�N�g�ǉ��֐�
	//! @details
	//! @param *object �Փ˃I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	void AddCollisionObject(CollisionObject* object);

	//----------------------------------------
	//! @brief �Փ˃I�u�W�F�N�g�㏑���֐�
	//! @details
	//! @param *old_object �Â��Փ˃I�u�W�F�N�g
	//! @param *new_object �V�����Փ˃I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	void OverwriteCollisionsObject(CollisionObject* old_object,
								   CollisionObject* new_object);

	//----------------------------------------
	//! @brief �Փ˃I�u�W�F�N�g����֐�
	//! @details
	//! @param *object �Փ˃I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	void ReleaseCollisionObject(CollisionObject* object);

	//----------------------------------------
	//! @brief �Փ˃I�u�W�F�N�g�S����֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void ReleaseAllCollisionObject();

	//----------------------------------------
	//! @brief �Փ˃I�u�W�F�N�g�S�X�V�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void UpdateAllCollisionObject();
};



#endif