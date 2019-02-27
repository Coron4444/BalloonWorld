//================================================================================
//!	@file	 CollisionObject.h
//!	@brief	 �Փ˃I�u�W�F�N�gClass
//! @details 
//!	@author  Kai Araki									@date 2019/02/14
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
#include "CollisionManager/ObjectOfTree.h"



//****************************************
// �N���X�錾
//****************************************
class CollisionBase;



//************************************************************														   
//! @brief   �Փ˃I�u�W�F�N�gClass
//!
//! @details �Փ˃I�u�W�F�N�g��Class
//************************************************************
class CollisionObject
{
//====================
// �N���X��`
//====================
public:
	//****************************************											   
	//! @brief   �Փˌ`��Class
	//!
	//! @details �Փ˂̌`��Class
	//****************************************
	class Shape
	{
	//====================
	// �萔
	//====================
	private:
		static const int TAG_NONE;		//!< �^�O�Ȃ����̒l


	//====================
	// �ϐ�
	//====================
	private:
		int	tag_ = TAG_NONE;		//!< �^�O
		CollisionShapeBase* shape_;	//!< �`��


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
		CollisionShapeBase* getpShape();

		//----------------------------------------
		//! @brief �Փˌ`��擾�֐�
		//! @details
		//! @param value �Փˌ`��
		//! @retval void �Ȃ�
		//----------------------------------------
		void setShape(CollisionShapeBase* value);


	//====================
	// �֐�
	//====================
	public:
		//----------------------------------------
		//! @brief �������֐�
		//! @details
		//! @param tag    �^�O
		//! @param *shape �Փˌ`��
		//! @retval void �Ȃ�
		//----------------------------------------
		void Init(int tag, CollisionShapeBase* shape);

		//----------------------------------------
		//! @brief �I���֐�
		//! @details
		//! @param void �Ȃ�
		//! @retval void �Ȃ�
		//----------------------------------------
		void Uninit();
	};


//====================
// �萔
//====================
private:
	static const unsigned ARRAY_NUM = 10000;	//!< �z��
	static const int TAG_NONE;					//!< �^�O�Ȃ����̒l


//====================
// �ϐ�
//====================
private:
	int	tag_ = TAG_NONE;								//!< �^�O
	LimitedPointerArray<Shape*, ARRAY_NUM> all_shape_;	//!< �S�Փˌ`��z��
	CollisionBase* collision_base_ = nullptr;			//!< �Փˊ��N���X
	ObjectOfTree<CollisionObject*>* object_of_tree_;	//!< ���؃I�u�W�F�N�g
	AABB octree_aabb_;									//!< 8���ؗpAABB
	

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
	//! @brief �z��̏I�[�C���f�b�N�X�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval unsigned �z��̏I�[�C���f�b�N�X
	//----------------------------------------
	unsigned getEndIndexOfArray();

	//----------------------------------------
	//! @brief �Փˌ`��擾�֐�
	//! @details
	//! @param index �C���f�b�N�X
	//! @retval Shape* �Փˌ`��
	//----------------------------------------
	Shape* getpShape(unsigned index);

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
	//! @retval ObjectOfTree<CollisionObject*>* ���؃I�u�W�F�N�g
	//----------------------------------------
	ObjectOfTree<CollisionObject*>* getpObjectOfTree();

	//----------------------------------------
	//! @brief ���؃I�u�W�F�N�g�ݒ�֐�
	//! @details
	//! @param value ���؃I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	void setObjectOfTree(ObjectOfTree<CollisionObject*>* value);

	//----------------------------------------
	//! @brief 8���ؗpAABB�|�C���^�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval AABB* 8���ؗpAABB�|�C���^
	//----------------------------------------
	AABB* getOctreeAABB();


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief ������
	//! @details
	//! @param tag        �^�O
	//! @param *collision �Փˊ��N���X
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init(int tag, CollisionBase* collision);

	//----------------------------------------
	//! @brief �X�V�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Update();

	//----------------------------------------
	//! @brief �Փˌ`��ǉ��֐�
	//! @details
	//! @param tag   �^�O
	//! @param shape �`��
	//! @retval void �Ȃ�
	//----------------------------------------
	void AddShape(int tag, CollisionShapeBase* shape);

	//----------------------------------------
	//! @brief �Փˌ`�����֐�
	//! @details
	//! @param tag   �^�O
	//! @retval void �Ȃ�
	//----------------------------------------
	void ReleaseShape(int tag);

	//----------------------------------------
	//! @brief �Փ˃I�u�W�F�N�g�S����֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void ReleaseAllShape();

private:
	//----------------------------------------
	//! @brief AABB�X�V�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void UpdateAABB();
};



#endif
