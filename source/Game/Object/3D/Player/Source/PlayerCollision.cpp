//================================================================================
//!	@file	 PlayerCollision.cpp
//!	@brief	 �v���C���[�Փ�Class
//! @details 
//!	@author  Kai Araki									@date 2018/03/27
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../PlayerCollision.h"
#include "../Player.h"

#include <GameEngine/Renderer/Renderer.h>
#include <GameEngine/GameObject/GameObjectManager/GameObjectManager.h>
#include <Object/3D/Coin/Coin.h>
#include <Object/3D/Coin/CoinCollision.h>
#include <Object/3D/Enemy/EnemyCollision.h>
#include <Resource/Polygon/MeshPlanePolygon.h>



//****************************************
// �萔��`
//****************************************
const float PlayerCollision::BOUNDING_SPHERE_RADIUS = 3.0f;
const float PlayerCollision::SUBSTANCE_SPHERE_RADIUS = 1.0f;



//****************************************
// �֐���`
//****************************************
void PlayerCollision::Init()
{
	// �^�C�v
	CollisionBase::setType(CollisionBase::Type::PLAYER);

	//�_�E���L���X�g
	player_ = (Player*)getpGameObject();

	// �����Փ˃I�u�W�F�N�g
	collision_objects_ = new CollisionObjects();
	collision_objects_->setCollisionBase(this);
	collision_objects_->getOctreeAABB()->Init(*getpGameObject()->getpTransform()
											  ->getpPosition(),
											  Vec3(3.0f, 3.0f, 3.0f));
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



void PlayerCollision::Update()
{
	// �����Փ˃I�u�W�F�N�g�̍X�V
	*collision_objects_->getOctreeAABB()->getpPositon() = *getpGameObject()
		->getpTransform()->getpPosition();
	collision_objects_->getOctreeAABB()->Update();

	// �o�E���f�B���O���̍X�V
	Sphere* temp_sphere = (Sphere*)bounding_sphere_->getpCollisionShape();
	*temp_sphere->getpPosition() = *getpGameObject()->getpTransform()->getpPosition();

	//// �{�̋��̍X�V
	temp_sphere = (Sphere*)substance_sphere_->getpCollisionShape();
	*temp_sphere->getpPosition() = *getpGameObject()->getpTransform()->getpPosition();
}



void PlayerCollision::HitCollision(CollisionBase* hit_collision,
								   CollisionObject* hit_object,
								   CollisionObject* hit_my_object)
{
	// �����̏Փ˃I�u�W�F�N�g�ŐU�蕪����
	switch ((PlayerCollision::ObjectTag)hit_my_object->getTag())
	{
		case PlayerCollision::ObjectTag::BOUNDING_SPHERE:
		{
			HitBoundingSphere(hit_collision, hit_object, hit_my_object);
			break;
		}
		case PlayerCollision::ObjectTag::SUBSTANCE_SPHERE:
		{
			HitSubstance(hit_collision, hit_object, hit_my_object);
			break;
		}
	}
}



void PlayerCollision::NotHitCollision(CollisionBase* hit_collision,
									  CollisionObject* hit_object,
									  CollisionObject* hit_my_object)
{
	// �����̏Փ˃I�u�W�F�N�g�ŐU�蕪����
	switch ((PlayerCollision::ObjectTag)hit_my_object->getTag())
	{
		case PlayerCollision::ObjectTag::BOUNDING_SPHERE:
		{
			NotHitBoundingSphere(hit_collision, hit_object, hit_my_object);
			break;
		}
	}
}



void PlayerCollision::HitGround(float position_y)
{
	// �_�E���L���X�g
	Player* player = (Player*)getpGameObject();

	// �n�ʂ̏�ɗ���
	player->getpTransform()->getpPosition()->y = position_y;
	player->getpTransform()->CreateWorldMatrix();

	if (player->getpPhysics() == nullptr) return;
	player->getpPhysics()->setOnTheGround();
}



void PlayerCollision::HitBoundingSphere(CollisionBase* hit_collision,
										CollisionObject* hit_object,
										CollisionObject* hit_my_object)
{
	hit_my_object = hit_my_object;

	// �Փ˃R���|�[�l���g�ŐU�蕪��
	switch (hit_collision->getType())
	{
		case CollisionBase::Type::COIN:
		{
			//TestCubeCollisionBase* temp_component = (TestCubeCollisionBase*)hit_collision;

			// ����̏Փ˃I�u�W�F�N�g�ŐU�蕪��
			switch ((CoinCollision::ObjectTag)hit_object->getTag())
			{
				case CoinCollision::ObjectTag::BOUNDING_OBB:
				{
					//game_object_origin_->translation_->position_ += hit_my_object->hit_vector_;
					//game_object_origin_->matrix_->UpdateTranslationMatrix(game_object_origin_->translation_->position_);
					//game_object_origin_->matrix_->UpdateWorldMatrix();
					break;
				}

			}
		}
	}
}



void PlayerCollision::NotHitBoundingSphere(CollisionBase* hit_collision,
										   CollisionObject* hit_object,
										   CollisionObject* hit_my_object)
{
	hit_my_object = hit_my_object;

	// �Փ˃R���|�[�l���g�ŐU�蕪��
	switch (hit_collision->getType())
	{
		case CollisionBase::Type::COIN:
		{
			// �g��Ȃ���������
			hit_object = hit_object;

			// �o�E���f�B���O���������̏Փ˃I�u�W�F�N�g��OFF
			substance_sphere_->setIsJudgment(false);
			break;
		}
	}
}



void PlayerCollision::HitSubstance(CollisionBase* hit_collision,
								   CollisionObject* hit_object,
								   CollisionObject* hit_my_object)
{
	// �Փ˃R���|�[�l���g�ŐU�蕪��
	switch (hit_collision->getType())
	{
		case CollisionBase::Type::COIN:
		{
			// ����̏Փ˃I�u�W�F�N�g�ŐU�蕪��
			switch ((CoinCollision::ObjectTag)hit_object->getTag())
			{
				case CoinCollision::ObjectTag::BOUNDING_OBB:
				{
					// �_�E���L���X�g
					Player* player = (Player*)getpGameObject();
					Coin* coin = (Coin*)hit_collision->getpGameObject();
					if (*coin->getpColorChangeCounter() <= 0)
					{
						*coin->getpColorChangeCounter() = 120;

						// �X�R�A�A�b�v
						player->getpGameScene()->setScore(player->getpGameScene()
														  ->getScore() + 10);
					}

					// �߂荞�݉���
					//EliminationOfNesting(player->GetTransform(), hit_my_object->getpHitVector());

					// ����̃I�u�W�F�N�g������
					//GameObjectManager::ReleaseGameObjectBaseFromArray(hit_collision->getpGameObject());

					break;
				}
			}
			break;
		}
		case CollisionBase::Type::ENEMY:
		{
			// ����̏Փ˃I�u�W�F�N�g�ŐU�蕪��
			switch ((EnemyCollision::ObjectTag)hit_object->getTag())
			{
				case EnemyCollision::ObjectTag::SUBSTANCE_SPHERE:
				{
					// �_�E���L���X�g
					Player* player = (Player*)getpGameObject();

					// �߂荞�݉���
					EliminationOfNesting(player->getpTransform(), 
										 hit_my_object->getpHitVector());

					// �X�R�A�_�E��
					player->getpGameScene()->setGameOver(1);

					// ����̃I�u�W�F�N�g������
					GameObjectManager::getpInstance()
						->ReleaseGameObjectBaseFromArray(hit_collision->getpGameObject());
					break;
				}
			}
			break;
		}
		case CollisionBase::Type::GOAL:
		{
			// ����̏Փ˃I�u�W�F�N�g�ŐU�蕪��
			switch ((EnemyCollision::ObjectTag)hit_object->getTag())
			{
				case EnemyCollision::ObjectTag::SUBSTANCE_SPHERE:
				{
					// �_�E���L���X�g
					Player* player = (Player*)getpGameObject();

					// �߂荞�݉���
					EliminationOfNesting(player->getpTransform(), 
										 hit_my_object->getpHitVector());

					// �X�R�A�_�E��
					player->getpGameScene()->setGameOver(0);

					// ����̃I�u�W�F�N�g������
					GameObjectManager::getpInstance()
						->ReleaseGameObjectBaseFromArray(hit_collision->getpGameObject());
					break;
				}
			}
			break;
		}
	}
}