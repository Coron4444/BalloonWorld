//================================================================================
//!	@file	 CollisionObjects.h
//!	@brief	 �����Փ˃I�u�W�F�N�gClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================
#ifndef	_COLLISION_OBJECTS_H_
#define _COLLISION_OBJECTS_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <LimitedPointerArray\LimitedPointerArray.h>

#include "../CollisionObject/CollisionObject.h"
#include "../ComponentManager/CollisionManager/LinerOctree/ObjectOfTree/ObjectOfTree.h"



//****************************************
// �N���X�錾
//****************************************
class CollisionBase;



//************************************************************														   
//! @brief   �����Փ˃I�u�W�F�N�gClass
//!
//! @details �����̏Փ˃I�u�W�F�N�g���Ǘ�����Class
//************************************************************
class CollisionObjects
{
//====================
// �萔
//====================
private:
	static const unsigned ARRAY_NUM = 10000;		//!< �z��


//====================
// �ϐ�
//====================
private:
	LimitedPointerArray<CollisionObject*, ARRAY_NUM> collision_object_;	//!< �S�Փ˃I�u�W�F�N�g�z��
	CollisionBase* collision_base_ = nullptr;			//!< �Փˊ��N���X
	ObjectOfTree<CollisionObjects*>* object_of_tree_;	//!< ���؃I�u�W�F�N�g
	AABB octree_aabb_;									//!< 8���ؗpAABB
	bool is_judgment_ = true;							//!< ����t���O


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
	//! @brief �Փ˃I�u�W�F�N�g�擾�֐�
	//! @details
	//! @param index �Փ˃I�u�W�F�N�g�̃C���f�b�N�X
	//! @retval CollisionObject* �Փ˃I�u�W�F�N�g
	//----------------------------------------
	CollisionObject* getpCollisionObject(unsigned index);

	//----------------------------------------
	//! @brief �Փˊ��N���X�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval CollisionBase* �Փˊ��N���X
	//----------------------------------------
	CollisionBase* getpCollisionBase();
	
	//----------------------------------------
	//! @brief �Փˊ��N���X�ݒ�֐�
	//! @details
	//! @param *value �Փˊ��N���X
	//! @retval void �Ȃ�
	//----------------------------------------
	void setCollisionBase(CollisionBase* value);
	
	//----------------------------------------
	//! @brief ���؃I�u�W�F�N�g�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval ObjectOfTree<CollisionObjects*>* ���؃I�u�W�F�N�g
	//----------------------------------------
	ObjectOfTree<CollisionObjects*>* getpObjectOfTree();
	
	//----------------------------------------
	//! @brief ���؃I�u�W�F�N�g�ݒ�֐�
	//! @details
	//! @param value ���؃I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	void setObjectOfTree(ObjectOfTree<CollisionObjects*>* value);

	//----------------------------------------
	//! @brief 8���ؗpAABB�|�C���^�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval AABB* 8���ؗpAABB�|�C���^
	//----------------------------------------
	AABB* getOctreeAABB();
	
	//----------------------------------------
	//! @brief ����t���O�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval bool ����t���O
	//----------------------------------------
	bool getIsJudgment();
	
	//----------------------------------------
	//! @brief ����t���O�ݒ�֐�
	//! @details
	//! @param value ����t���O
	//! @retval void �Ȃ�
	//----------------------------------------
	void setIsJudgment(bool value);


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �Փ˃I�u�W�F�N�g�ǉ��֐�
	//! @details
	//! @param *object �Փ˃I�u�W�F�N�g�|�C���^
	//! @retval void �Ȃ�
	//----------------------------------------
	void AddCollisionObjectToArray(CollisionObject* object);

	//----------------------------------------
	//! @brief �Փ˃I�u�W�F�N�g�㏑���֐�
	//! @details
	//! @param *old_object �Â��Փ˃I�u�W�F�N�g�|�C���^
	//! @param *new_object �V�����Փ˃I�u�W�F�N�g�|�C���^
	//! @retval void �Ȃ�
	//----------------------------------------
	void OverwriteArrayCollisionObject(CollisionObject* old_object,
									   CollisionObject* new_object);

	//----------------------------------------
	//! @brief �Փ˃I�u�W�F�N�g����֐�
	//! @details
	//! @param *object �Փ˃I�u�W�F�N�g�|�C���^
	//! @retval void �Ȃ�
	//----------------------------------------
	void ReleaseCollisionObjectFromArray(CollisionObject* object);

	//----------------------------------------
	//! @brief �Փ˃I�u�W�F�N�g�S����֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void ReleaseAllCollisionObjectFromArray();

	//----------------------------------------
	//! @brief �S�Փ˗p�f�[�^�̃��Z�b�g�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void ResetHitDataAllCollisionObject();
};



#endif
