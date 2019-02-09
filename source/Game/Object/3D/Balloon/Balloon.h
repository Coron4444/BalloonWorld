//================================================================================
//!	@file	 Balloon.h
//!	@brief	 ���DClass
//! @details 
//!	@author  Kai Araki									@date 2019/02/05
//================================================================================
#ifndef	_BALLOON_H_
#define _BALLOON_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <GameEngine/GameObject/GameObjectNull.h>



//****************************************
// �N���X��`
//****************************************
class BulletPhysicsObject;
class BulletPhysicsConstraint;



//************************************************************														   
//! @brief   ���DClass
//!
//! @details ���D��Class
//************************************************************
class Balloon : public GameObjectNull
{
//====================
// �萔
//====================
public:
	static const unsigned MAX_BULLET_OBJECT = 25;
	static const unsigned MAX_BULLET_CONSTRAINT = MAX_BULLET_OBJECT - 1;
	static const Vec3 OBB_EDGE_LENGTH_HALF;
	static const float SPHERE_RADIUS;


//====================
// �ϐ�
//====================
public:
	BulletPhysicsObject* bullet_object_[MAX_BULLET_OBJECT];				//!< �o���b�g�I�u�W�F�N�g
	BulletPhysicsConstraint* bullet_constraint_[MAX_BULLET_CONSTRAINT];	//!< �o���b�g�S��
	Transform bullet_transform_[MAX_BULLET_OBJECT];
	

//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param *update �X�V���N���X
	//! @param *draw   �`����N���X
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init(UpdateBase* update, DrawBase* draw);

private:
	//----------------------------------------
	//! @brief �o���b�g�I�u�W�F�N�g�������֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void InitBulletPhysicsObject();
};



#endif