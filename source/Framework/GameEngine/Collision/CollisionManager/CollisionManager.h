//================================================================================
//!	@file	 CollisionManager.h
//!	@brief	 �Փ˃}�l�[�W���[Class
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================
#ifndef	_COLLISION_MANAGER_H_
#define _COLLISION_MANAGER_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <vector>

#include "LinerOctree.h"

#include <Tool/LimitedPointerArray.h>



//****************************************
// �N���X�錾
//****************************************
class CollisionBase;
class CollisionObject;
class CollisionObjects;
class GameObjectBase;
class MeshPlanePolygon;



//************************************************************														   
//! @brief   �Փ˃}�l�[�W���[Class
//!
//! @details �o�^����Ă���Փˊ��N���X���Ǘ�����Class
//************************************************************
class CollisionManager
{
//====================
// �萔
//====================
public:
	static const unsigned ARRAY_NUM = 10000;		//!< �z��


//====================
// �ϐ�
//====================
private:
	LimitedPointerArray<CollisionBase*, ARRAY_NUM> all_collision_;	//!< �S�Փ˔z��
	LimitedPointerArray<CollisionBase*, ARRAY_NUM> await_add_;		//!< �ǉ��҂��z��
	LimitedPointerArray<CollisionBase*, ARRAY_NUM> await_release_;	//!< ����҂��z��
	LinerOctree<CollisionObjects*>* liner_octree_ = nullptr;		//!< 8����
	std::vector<CollisionObjects*> collision_objects_list_;			//!< �Փ˃��X�g
	MeshPlanePolygon* ground_polygon_;								//!< �n�ʃ|���S��

	// �f�o�b�O�p
	DWORD time_;
	bool is_octree_ = true;
	bool is_pair_check_ = true;


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �n�ʃ|���S���ݒ�֐�
	//! @details
	//! @param *ground_polygon �n�ʃ|���S��
	//! @retval void �Ȃ�
	//----------------------------------------
	void setGround(MeshPlanePolygon* ground_polygon);


//====================
// �֐�
//====================
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
	//! @brief �V�[���ύX���̏I���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void UninitWhenChangeScene();

	//----------------------------------------
	//! @brief �X�V�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Update();

	//----------------------------------------
	//! @brief �Փˊ��N���X�̒ǉ��֐�
	//! @details
	//! @param *collision �Փˊ��N���X
	//! @retval void �Ȃ�
	//----------------------------------------
	void AddCollisionBaseToArray(CollisionBase* collision);

	//----------------------------------------
	//! @brief �Փˊ��N���X�̏㏑���֐�
	//! @details
	//! @param *game_object   �Q�[���I�u�W�F�N�g
	//! @param *new_collision �V�K�Փˊ��N���X
	//! @retval void �Ȃ�
	//----------------------------------------
	void OverwriteArrayCollisionBase(GameObjectBase* game_object,
									 CollisionBase* new_collision);

	//----------------------------------------
	//! @brief �Փˊ��N���X�̉���֐�
	//! @details
	//! @param *collision �Փˊ��N���X
	//! @retval void �Ȃ�
	//----------------------------------------
	void ReleaseCollisionBaseFromArray(CollisionBase* collision);


private:
	//----------------------------------------
	//! @brief �ǉ��҂��z��̒��g��ǉ��֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void AddContentsOfAwaitAddArray();

	//----------------------------------------
	//! @brief ����҂��z��̒��g������֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void ReleaseContentsOfAwaitReleaseArray();

	//----------------------------------------
	//! @brief �Փ˔���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void CollisionDetermination();

	//----------------------------------------
	//! @brief �Â��Փ˔���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void OldCollisionDetermination();

	//----------------------------------------
	//! @brief �n�ʂƂ̏Փ˔���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void CollisionGround();

	//----------------------------------------
	//! @brief ���ۂ̌v�Z�֐�
	//! @details
	//! @param *collision_object0 �Փ˃I�u�W�F�N�g0
	//! @param *collision_object1 �Փ˃I�u�W�F�N�g1
	//! @retval void �Ȃ�
	//----------------------------------------
	void ActualCalculation(CollisionObjects* collision_objects0,
						   CollisionObjects* collision_objects1);

	//----------------------------------------
	//! @brief �Փˌv�Z�U�蕪���֐�
	//! @details
	//! @param *collision_object0 �Փ˃I�u�W�F�N�g0
	//! @param *collision_object1 �Փ˃I�u�W�F�N�g1
	//! @retval void �Ȃ�
	//----------------------------------------
	bool SortCollisionCalculation(CollisionObject* collision_object0,
								  CollisionObject* collision_object1);

	//----------------------------------------
	//! @brief Debug�\���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void DebugDisplay();
};



#endif