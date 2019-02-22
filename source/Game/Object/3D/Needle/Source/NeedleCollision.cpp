//================================================================================
//!	@file	 NeedleCollision.cpp
//!	@brief	 ���Փ�Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../NeedleCollision.h"



//****************************************
// �萔��`
//****************************************
const float NeedleCollision::MAIN_SPHERE_RADIUS = 1.0f;



//****************************************
// �֐���`
//****************************************
void NeedleCollision::Init()
{
	// �^�C�v
	CollisionBase::setType(CollisionBase::Type::NEEDLE);

	// �Փ˃I�u�W�F�N�g�쐬
	collision_object_ = new CollisionObject();
	collision_object_->Init((int)ObjectTag::MAIN, this);
	CollisionBase::AddCollisionObject(collision_object_);

	// ���C�����̍쐬
	main_sphere_ = new Sphere();
	Vector3D position = *getpGameObject()->getpTransform()->getpPosition();
	float radius = MAIN_SPHERE_RADIUS * getpGameObject()->getpTransform()->getpScale()->x;
	main_sphere_->Init(position, radius);
	collision_object_->AddShape((int)ShapeTag::MAIN, main_sphere_);
}



void NeedleCollision::Update()
{
	// ���C�����̍X�V
	Vector3D position = *getpGameObject()->getpTransform()->getpPosition();
	float radius = MAIN_SPHERE_RADIUS * getpGameObject()->getpTransform()->getpScale()->x;
	*main_sphere_->getpPosition() = position;
	main_sphere_->setRadius(radius);
}