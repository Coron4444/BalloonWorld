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
const float GoalCollision::BOUNDING_SPHERE_RADIUS = 3.0f;
const float GoalCollision::SUBSTANCE_SPHERE_RADIUS = 1.0f;



//****************************************
// �֐���`
//****************************************
void GoalCollision::Init()
{
	// �^�C�v
	CollisionBase::setType(CollisionBase::Type::ENEMY);

	// �Փ˃I�u�W�F�N�g�Q�쐬
	collision_objects_ = new CollisionObjects();
	collision_objects_->setCollisionBase(this);
	collision_objects_->getOctreeAABB()->Init(*getpGameObject()->getpTransform()
											  ->getpPosition(),
											  Vec3(1.0f, 1.0f, 1.0f));
	CollisionBase::AddCollisionObjectsToArray(collision_objects_);

	// �o�E���f�B���O���̍쐬
	Sphere* temp_sphere = new Sphere();
	temp_sphere->Init(*getpGameObject()->getpTransform()->getpPosition(),
					  BOUNDING_SPHERE_RADIUS);
	bounding_sphere_ = new CollisionObject(temp_sphere, (int)ObjectTag::BOUNDING_SPHERE);
	collision_objects_->AddCollisionObjectToArray(bounding_sphere_);

	// �{�̋��̍쐬
	temp_sphere = new Sphere();
	temp_sphere->Init(*getpGameObject()->getpTransform()->getpPosition(),
					  SUBSTANCE_SPHERE_RADIUS);
	substance_sphere_ = new CollisionObject(temp_sphere, (int)ObjectTag::SUBSTANCE_SPHERE);
	collision_objects_->AddCollisionObjectToArray(substance_sphere_);
}



void GoalCollision::Update()
{
	// �Փ˃I�u�W�F�N�g�Q�X�V
	*collision_objects_->getOctreeAABB()->getpPositon() = *getpGameObject()
		->getpTransform()->getpPosition();
	collision_objects_->getOctreeAABB()->Update();

	// �o�E���f�B���O���̍X�V
	Sphere* temp_sphere = (Sphere*)bounding_sphere_->getpCollisionShape();
	*temp_sphere->getpPosition() = *getpGameObject()->getpTransform()->getpPosition();

	// �{�̋��̍X�V
	temp_sphere = (Sphere*)substance_sphere_->getpCollisionShape();
	*temp_sphere->getpPosition() = *getpGameObject()->getpTransform()->getpPosition();
}