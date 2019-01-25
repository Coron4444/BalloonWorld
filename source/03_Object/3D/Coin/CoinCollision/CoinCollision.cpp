//================================================================================
//
//    �R�C���Փ˃N���X
//    Author : Araki Kai                                �쐬�� : 2018/07/24
//
//================================================================================



//**********************************************************************
//
// �C���N���[�h��
//
//**********************************************************************

#include "CoinCollision.h"

#include <Renderer\RendererDirectX9\RendererDirectX9.h>



//**********************************************************************
//
// �萔��`
//
//**********************************************************************

const float CoinCollision::BOUNDING_OBB_RIGHT = 1.0f;
const float CoinCollision::BOUNDING_OBB_UP = 1.0f;
const float CoinCollision::BOUNDING_OBB_FORWARD = 1.0f;

const float CoinCollision::SUBSTANCE_RIGHT = 1.0f;
const float CoinCollision::SUBSTANCE_UP = 1.0f;
const float CoinCollision::SUBSTANCE_FORWARD = 1.0f;



//**********************************************************************
//
// ��ÓI�����o�֐���`
//
//**********************************************************************
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void CoinCollision::Init()
{
	// �^�C�v
	CollisionBase::setType(CollisionBase::Type::COIN);

	// �����Փ˃I�u�W�F�N�g
	collision_objects_ = new CollisionObjects();
	collision_objects_->setCollisionBase(this);
	collision_objects_->getOctreeAABB()
		->Init(*getpGameObject()->GetTransform()->GetPosition(),
			   Vec3(1.0f, 1.0f, 1.0f));
	CollisionBase::AddCollisionObjectsToArray(collision_objects_);

	// �o�E���f�B���OOBB�̍쐬
	OBB* temp_obb_ = new OBB();
	temp_obb_->Init(*getpGameObject()->GetTransform()->GetPosition(),
					Vector3D(BOUNDING_OBB_RIGHT, BOUNDING_OBB_UP, BOUNDING_OBB_FORWARD));

	bounding_obb_ = new CollisionObject(temp_obb_, ObjectTag::BOUNDING_OBB);

	// �o�E���f�B���OOBB�̓o�^
	collision_objects_->AddCollisionObjectToArray(bounding_obb_);


	// �{��OBB�̍쐬
	temp_obb_ = new OBB();
	temp_obb_->Init(*getpGameObject()->GetTransform()->GetPosition(),
					Vector3D(SUBSTANCE_RIGHT, SUBSTANCE_UP, SUBSTANCE_FORWARD));

	substance_ = new CollisionObject(temp_obb_, ObjectTag::SUBSTANCE);

	// �{��OBB�̓o�^
	collision_objects_->AddCollisionObjectToArray(substance_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �I�������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void CoinCollision::Uninit()
{
	// �X�[�p�[�N���X�̏I������
	CollisionNull::Uninit();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �X�V�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void CoinCollision::Update()
{
	// �����Փ˃I�u�W�F�N�g�̍X�V
	*collision_objects_->getOctreeAABB()->getpPositon() = *getpGameObject()
		->GetTransform()->GetPosition();
	collision_objects_->getOctreeAABB()->Update();

	// �o�E���f�B���OOBB�̍X�V
	OBB* temp_obb = (OBB*)bounding_obb_->getpCollisionShape();

	*temp_obb->getpPosition() = *getpGameObject()->GetTransform()->GetPosition();
	*temp_obb->getpAxisVector() = *getpGameObject()->GetTransform()->GetAxisVector();
	*temp_obb->getpLength() = Vector3D(getpGameObject()->GetTransform()->GetScale()->x * BOUNDING_OBB_RIGHT,
									   getpGameObject()->GetTransform()->GetScale()->y * BOUNDING_OBB_UP,
									   getpGameObject()->GetTransform()->GetScale()->z * BOUNDING_OBB_FORWARD);


	// �{�̃X�t�B�AOBB�̍X�V
	temp_obb = (OBB*)substance_->getpCollisionShape();

	*temp_obb->getpPosition() = *getpGameObject()->GetTransform()->GetPosition();
	*temp_obb->getpAxisVector() = *getpGameObject()->GetTransform()->GetAxisVector();
	*temp_obb->getpLength() = Vector3D(getpGameObject()->GetTransform()->GetScale()->x * SUBSTANCE_RIGHT,
									   getpGameObject()->GetTransform()->GetScale()->y * SUBSTANCE_UP,
									   getpGameObject()->GetTransform()->GetScale()->z * SUBSTANCE_FORWARD);
}