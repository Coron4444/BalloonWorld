//================================================================================
//
//    �v���C���[�Փ˃N���X
//    Author : Araki Kai                                �쐬�� : 2018/03/27
//
//================================================================================



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include "PlayerCollision.h"
#include "../Player.h"

#include <Renderer\RendererDirectX9\RendererDirectX9.h>
#include <GameObjectManager\GameObjectManager.h>
#include <3D\Coin\CoinCollision\CoinCollision.h>
#include <3D\Enemy\EnemyCollision\EnemyCollision.h>
#include <Polygon\MeshPlanePolygon\MeshPlanePolygon.h>



//======================================================================
//
// �萔��`
//
//======================================================================

const float PlayerCollision::BOUNDING_SPHERE_RADIUS = 3.0f;
const float PlayerCollision::SUBSTANCE_RADIUS = 1.0f;



//======================================================================
//
// ��ÓI�����o�֐���`
//
//======================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PlayerCollision::Init()
{
	// �^�C�v
	CollisionBase::setType(CollisionBase::Type::PLAYER);

	// �����Փ˃I�u�W�F�N�g
	collision_objects_ = new CollisionObjects();
	collision_objects_->setCollisionBase(this);
	collision_objects_->getOctreeAABB()
		->Init(*getpGameObject()->GetTransform()->GetPosition(),
			   Vec3(3.0f, 3.0f, 3.0f));
	CollisionBase::AddCollisionObjectsToArray(collision_objects_);

	// �o�E���f�B���O�X�t�B�A�̍쐬
	Sphere* temp_sphere = new Sphere();
	temp_sphere->Init(*getpGameObject()->GetTransform()->GetPosition(),
					  BOUNDING_SPHERE_RADIUS);

	bounding_sphere_ = new CollisionObject(temp_sphere, ObjectTag::BOUNDING_SPHERE);

	// �o�E���f�B���O�X�t�B�A��ǉ�
	collision_objects_->AddCollisionObjectToArray(bounding_sphere_);


	// �{�̃X�t�B�A�̍쐬
	temp_sphere = new Sphere();
	temp_sphere->Init(*getpGameObject()->GetTransform()->GetPosition(),
					  SUBSTANCE_RADIUS);

	substance_ = new CollisionObject(temp_sphere, ObjectTag::SUBSTANCE);

	// �{�̃X�t�B�A��ǉ�
	collision_objects_->AddCollisionObjectToArray(substance_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �I�������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PlayerCollision::Uninit()
{
	// �X�[�p�[�N���X�̏I������
	CollisionNull::Uninit();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �X�V�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PlayerCollision::Update()
{
	// �����Փ˃I�u�W�F�N�g�̍X�V
	*collision_objects_->getOctreeAABB()->getpPositon() = *getpGameObject()
		->GetTransform()->GetPosition();
	collision_objects_->getOctreeAABB()->Update();

	// �o�E���f�B���O�X�t�B�A�̍X�V
	Sphere* temp_sphere = (Sphere*)bounding_sphere_->getpCollisionShape();
	*temp_sphere->getpPosition() = *getpGameObject()->GetTransform()->GetPosition();

	//// �{�̃X�t�B�A�̍X�V
	temp_sphere = (Sphere*)substance_->getpCollisionShape();
	*temp_sphere->getpPosition() = *getpGameObject()->GetTransform()->GetPosition();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �Փˉ����֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PlayerCollision::HitCollision(CollisionBase* hit_collision,
								   CollisionObject*  hit_object,
								   CollisionObject*  hit_my_object)
{
	// �����̏Փ˃I�u�W�F�N�g�ŐU�蕪����
	switch (hit_my_object->getTag())
	{
		case PlayerCollision::ObjectTag::BOUNDING_SPHERE:
		{
			HitBoundingSphere(hit_collision, hit_object, hit_my_object);
			break;
		}
		case PlayerCollision::ObjectTag::SUBSTANCE:
		{
			HitSubstance(hit_collision, hit_object, hit_my_object);
			break;
		}
	}
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ��Փˉ����֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PlayerCollision::NotHitCollision(CollisionBase* hit_collision,
									  CollisionObject*  hit_object,
									  CollisionObject*  hit_my_object)
{
	// �����̏Փ˃I�u�W�F�N�g�ŐU�蕪����
	switch (hit_my_object->getTag())
	{
		case PlayerCollision::ObjectTag::BOUNDING_SPHERE:
		{
			NotHitBoundingSphere(hit_collision, hit_object, hit_my_object);
			break;
		}
	}
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �n�ʂƂ̏Փˉ����֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PlayerCollision::HitGround(float position_y)
{
	// �_�E���L���X�g
	Player* player = (Player*)getpGameObject();

	// �n�ʂ̏�ɗ���
	player->GetTransform()->GetPosition()->y = position_y;
	player->GetTransform()->UpdateWorldMatrixSRT();

	if (player->GetPhysics() == nullptr) return;
	player->GetPhysics()->SetOnTheGround();
}



//--------------------------------------------------------------------------------
//
// [ �o�E���f�B���O�X�t�B�A�Փˏ����֐� ]
//
//--------------------------------------------------------------------------------

void PlayerCollision::HitBoundingSphere(CollisionBase* hit_collision,
										CollisionObject*  hit_object,
										CollisionObject*  hit_my_object)
{
	hit_my_object = hit_my_object;

	// �Փ˃R���|�[�l���g�ŐU�蕪��
	switch(hit_collision->getType())
	{
		case CollisionBase::Type::COIN :
		{
			//TestCubeCollisionBase* temp_component = (TestCubeCollisionBase*)hit_collision;
	
			// ����̏Փ˃I�u�W�F�N�g�ŐU�蕪��
			switch(hit_object->getTag())
			{
				case CoinCollision::ObjectTag::BOUNDING_OBB :
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



//--------------------------------------------------------------------------------
//
// [ �o�E���f�B���O�X�t�B�A��Փˏ����֐� ]
//
//--------------------------------------------------------------------------------

void PlayerCollision::NotHitBoundingSphere(CollisionBase* hit_collision,
										   CollisionObject*  hit_object,
										   CollisionObject*  hit_my_object)
{
	hit_my_object = hit_my_object;

	// �Փ˃R���|�[�l���g�ŐU�蕪��
	switch(hit_collision->getType())
	{
		case CollisionBase::Type::COIN :
		{
			// �g��Ȃ���������
			hit_object = hit_object;

			// �o�E���f�B���O�X�t�B�A�������̏Փ˃I�u�W�F�N�g��OFF
			substance_->setIsJudgment(false);

			break;
		}
	}
}



//--------------------------------------------------------------------------------
//
// [ �T�u�X�^���X�Փˏ����֐� ]
//
//--------------------------------------------------------------------------------

void PlayerCollision::HitSubstance(CollisionBase* hit_collision,
								   CollisionObject*  hit_object,
								   CollisionObject*  hit_my_object)
{
	// �Փ˃R���|�[�l���g�ŐU�蕪��
	switch(hit_collision->getType())
	{
		case CollisionBase::Type::COIN:
		{
			// ����̏Փ˃I�u�W�F�N�g�ŐU�蕪��
			switch(hit_object->getTag())
			{
				case CoinCollision::ObjectTag::BOUNDING_OBB :
				{
					// �_�E���L���X�g
					Player* player = (Player*)getpGameObject();
					Coin* coin = (Coin*)hit_collision->getpGameObject();
					if (coin->getCount() <= 0)
					{
						coin->setCount(120);
						// �X�R�A�A�b�v
						player->game_scene_->setScore(player->game_scene_->getScore() + 10);
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
		case CollisionBase::Type::ENEMY :
		{
			// ����̏Փ˃I�u�W�F�N�g�ŐU�蕪��
			switch(hit_object->getTag())
			{
				case EnemyCollision::ObjectTag::SUBSTANCE :
				{
					// �_�E���L���X�g
					Player* player = (Player*)getpGameObject();
					
					// �߂荞�݉���
					EliminationOfNesting(player->GetTransform(), hit_my_object->getpHitVector());

					// �X�R�A�_�E��
					player->game_scene_->setGameOver(1);

					// ����̃I�u�W�F�N�g������
					GameObjectManager::ReleaseGameObjectBaseFromArray(hit_collision->getpGameObject());
					
					break;
				}
			}
			break;
		}
		case CollisionBase::Type::GOAL:
		{
			// ����̏Փ˃I�u�W�F�N�g�ŐU�蕪��
			switch (hit_object->getTag())
			{
				case EnemyCollision::ObjectTag::SUBSTANCE:
				{
					// �_�E���L���X�g
					Player* player = (Player*)getpGameObject();

					// �߂荞�݉���
					EliminationOfNesting(player->GetTransform(), hit_my_object->getpHitVector());

					// �X�R�A�_�E��
					player->game_scene_->setGameOver(0);

					// ����̃I�u�W�F�N�g������
					GameObjectManager::ReleaseGameObjectBaseFromArray(hit_collision->getpGameObject());

					break;
				}
			}
			break;
		}
	}
}