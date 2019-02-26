//================================================================================
//!	@file	 EnemyCollision.cpp
//!	@brief	 �G�Փ�Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../EnemyCollision.h"
#include "../Enemy.h"



//****************************************
// �萔��`
//****************************************
const Vector3D EnemyCollision::MAIN_OBB_LENGTH(1.0f, 1.0f, 1.0f);



//****************************************
// �֐���`
//****************************************
void EnemyCollision::Init()
{
	// �^�C�v
	CollisionBase::setType(CollisionBase::Type::ENEMY);

	// �Փ˃I�u�W�F�N�g�쐬
	collision_object_ = new CollisionObject();
	collision_object_->Init((int)ObjectTag::MAIN, this);
	CollisionBase::AddCollisionObject(collision_object_);

	// ���C��OBB�̍쐬
	main_obb_ = new OBB();
	main_obb_->Init(*getpGameObject()->getpTransform()->getpPosition(),
					Vector3D(MAIN_OBB_LENGTH));
	collision_object_->AddShape((int)ShapeTag::MAIN, main_obb_);
}



void EnemyCollision::Update()
{
	// ���C��OBB�̍X�V
	*main_obb_->getpPosition() = *getpGameObject()->getpTransform()->getpPosition();
	main_obb_->RotationMatrix(getpGameObject()->getpTransform()->getpNoInitRotationMatrix());
	main_obb_->getpLength()->x = getpGameObject()->getpTransform()->getpScale()->x * MAIN_OBB_LENGTH.x;
	main_obb_->getpLength()->y = getpGameObject()->getpTransform()->getpScale()->y * MAIN_OBB_LENGTH.y;
	main_obb_->getpLength()->z = getpGameObject()->getpTransform()->getpScale()->z * MAIN_OBB_LENGTH.z;
}