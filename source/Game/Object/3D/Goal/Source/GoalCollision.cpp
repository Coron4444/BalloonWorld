//================================================================================
//!	@file	 GoalCollision.cpp
//!	@brief	 �S�[���Փ�Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/28
//================================================================================


//****************************************
// �C���N���[�h��
//****************************************
#include "../GoalCollision.h"
#include "../Goal.h"



//****************************************
// �萔��`
//****************************************
const float GoalCollision::MAIN_SPHERE_RADIUS = 1.0f;



//****************************************
// �֐���`
//****************************************
void GoalCollision::Init()
{
	// �^�C�v
	CollisionBase::setType(CollisionBase::Type::GOAL);

	// �Փ˃I�u�W�F�N�g�쐬
	collision_object_ = new CollisionObject();
	collision_object_->Init((int)ObjectTag::MAIN, this);
	CollisionBase::AddCollisionObject(collision_object_);

	// ���C�����̍쐬
	main_sphere_ = new Sphere();
	main_sphere_->Init(*getpGameObject()->getpTransform()->getpPosition(),
					   MAIN_SPHERE_RADIUS);
	collision_object_->AddShape((int)ShapeTag::MAIN, main_sphere_);
}



void GoalCollision::Update()
{
	// ���C�����̍X�V
	*main_sphere_->getpPosition() = *getpGameObject()->getpTransform()->getpPosition();
}