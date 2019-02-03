//================================================================================
//!	@file	 CoinCollision.cpp
//!	@brief	 �R�C���Փ�Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../CoinCollision.h"



//****************************************
// �萔��`
//****************************************
const Vec3 CoinCollision::BOUNDING_OBB_LENGTH(1.0f, 1.0f, 1.0f);
const Vec3 CoinCollision::SUBSTANCE_OBB_LENGTH(1.0f, 1.0f, 1.0f);



//****************************************
// �֐���`
//****************************************
void CoinCollision::Init()
{
	// �^�C�v
	CollisionBase::setType(CollisionBase::Type::COIN);

	// �Փ˃I�u�W�F�N�g�Q�쐬
	collision_objects_ = new CollisionObjects();
	collision_objects_->setCollisionBase(this);
	collision_objects_->getOctreeAABB()->Init(*getpGameObject()->getpTransform()
											  ->getpPosition(),
											  Vec3(1.0f, 1.0f, 1.0f));
	CollisionBase::AddCollisionObjectsToArray(collision_objects_);

	// �o�E���f�B���OOBB�̍쐬
	OBB* temp_obb_ = new OBB();
	temp_obb_->Init(*getpGameObject()->getpTransform()->getpPosition(),
					Vector3D(BOUNDING_OBB_LENGTH));

	bounding_obb_ = new CollisionObject(temp_obb_, (int)ObjectTag::BOUNDING_OBB);
	collision_objects_->AddCollisionObjectToArray(bounding_obb_);

	// ����OBB�̍쐬
	temp_obb_ = new OBB();
	temp_obb_->Init(*getpGameObject()->getpTransform()->getpPosition(),
					Vector3D(SUBSTANCE_OBB_LENGTH));
	substance_obb_ = new CollisionObject(temp_obb_, (int)ObjectTag::SUBSTANCE_OBB);
	collision_objects_->AddCollisionObjectToArray(substance_obb_);
}



void CoinCollision::Update()
{
	// �Փ˃I�u�W�F�N�g�Q�X�V
	*collision_objects_->getOctreeAABB()->getpPositon() = *getpGameObject()
		->getpTransform()->getpPosition();
	collision_objects_->getOctreeAABB()->Update();

	// �o�E���f�B���OOBB�̍X�V
	OBB* temp_obb = (OBB*)bounding_obb_->getpCollisionShape();
	*temp_obb->getpPosition() = *getpGameObject()->getpTransform()->getpPosition();
	*temp_obb->getpAxis() = *getpGameObject()->getpTransform()->getpAxis();
	temp_obb->getpLength()->x = getpGameObject()->getpTransform()->getpScale()->x * BOUNDING_OBB_LENGTH.x;
	temp_obb->getpLength()->y = getpGameObject()->getpTransform()->getpScale()->y * BOUNDING_OBB_LENGTH.y;
	temp_obb->getpLength()->z = getpGameObject()->getpTransform()->getpScale()->z * BOUNDING_OBB_LENGTH.z;


	// �{�̃X�t�B�AOBB�̍X�V
	temp_obb = (OBB*)substance_obb_->getpCollisionShape();
	*temp_obb->getpPosition() = *getpGameObject()->getpTransform()->getpPosition();
	*temp_obb->getpAxis() = *getpGameObject()->getpTransform()->getpAxis();
	temp_obb->getpLength()->x = getpGameObject()->getpTransform()->getpScale()->x * SUBSTANCE_OBB_LENGTH.x;
	temp_obb->getpLength()->y = getpGameObject()->getpTransform()->getpScale()->y * SUBSTANCE_OBB_LENGTH.y;
	temp_obb->getpLength()->z = getpGameObject()->getpTransform()->getpScale()->z * SUBSTANCE_OBB_LENGTH.z;
}