//================================================================================
//!	@file	 PlayerCollision.cpp
//!	@brief	 プレイヤー衝突Class
//! @details 
//!	@author  Kai Araki									@date 2018/03/27
//================================================================================



//****************************************
// インクルード文
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
// 定数定義
//****************************************
const float PlayerCollision::BOUNDING_SPHERE_RADIUS = 3.0f;
const float PlayerCollision::SUBSTANCE_SPHERE_RADIUS = 1.0f;



//****************************************
// 関数定義
//****************************************
void PlayerCollision::Init()
{
	// タイプ
	CollisionBase::setType(CollisionBase::Type::PLAYER);

	//ダウンキャスト
	player_ = (Player*)getpGameObject();

	// 複数衝突オブジェクト
	collision_objects_ = new CollisionObjects();
	collision_objects_->setCollisionBase(this);
	collision_objects_->getOctreeAABB()->Init(*getpGameObject()->getpTransform()
											  ->getpPosition(),
											  Vec3(3.0f, 3.0f, 3.0f));
	CollisionBase::AddCollisionObjectsToArray(collision_objects_);

	// バウンディング球の作成
	Sphere* temp_sphere = new Sphere();
	temp_sphere->Init(*getpGameObject()->getpTransform()->getpPosition(),
					  BOUNDING_SPHERE_RADIUS);
	bounding_sphere_ = new CollisionObject(temp_sphere, (int)ObjectTag::BOUNDING_SPHERE);
	collision_objects_->AddCollisionObjectToArray(bounding_sphere_);

	// 本体球の作成
	temp_sphere = new Sphere();
	temp_sphere->Init(*getpGameObject()->getpTransform()->getpPosition(),
					  SUBSTANCE_SPHERE_RADIUS);
	substance_sphere_ = new CollisionObject(temp_sphere, (int)ObjectTag::SUBSTANCE_SPHERE);
	collision_objects_->AddCollisionObjectToArray(substance_sphere_);
}



void PlayerCollision::Update()
{
	// 複数衝突オブジェクトの更新
	*collision_objects_->getOctreeAABB()->getpPositon() = *getpGameObject()
		->getpTransform()->getpPosition();
	collision_objects_->getOctreeAABB()->Update();

	// バウンディング球の更新
	Sphere* temp_sphere = (Sphere*)bounding_sphere_->getpCollisionShape();
	*temp_sphere->getpPosition() = *getpGameObject()->getpTransform()->getpPosition();

	//// 本体球の更新
	temp_sphere = (Sphere*)substance_sphere_->getpCollisionShape();
	*temp_sphere->getpPosition() = *getpGameObject()->getpTransform()->getpPosition();
}



void PlayerCollision::HitCollision(CollisionBase* hit_collision,
								   CollisionObject* hit_object,
								   CollisionObject* hit_my_object)
{
	// 自分の衝突オブジェクトで振り分ける
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
	// 自分の衝突オブジェクトで振り分ける
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
	// ダウンキャスト
	Player* player = (Player*)getpGameObject();

	// 地面の上に立つ
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

	// 衝突コンポーネントで振り分け
	switch (hit_collision->getType())
	{
		case CollisionBase::Type::COIN:
		{
			//TestCubeCollisionBase* temp_component = (TestCubeCollisionBase*)hit_collision;

			// 相手の衝突オブジェクトで振り分け
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

	// 衝突コンポーネントで振り分け
	switch (hit_collision->getType())
	{
		case CollisionBase::Type::COIN:
		{
			// 使わなかった引数
			hit_object = hit_object;

			// バウンディング球より内側の衝突オブジェクトをOFF
			substance_sphere_->setIsJudgment(false);
			break;
		}
	}
}



void PlayerCollision::HitSubstance(CollisionBase* hit_collision,
								   CollisionObject* hit_object,
								   CollisionObject* hit_my_object)
{
	// 衝突コンポーネントで振り分け
	switch (hit_collision->getType())
	{
		case CollisionBase::Type::COIN:
		{
			// 相手の衝突オブジェクトで振り分け
			switch ((CoinCollision::ObjectTag)hit_object->getTag())
			{
				case CoinCollision::ObjectTag::BOUNDING_OBB:
				{
					// ダウンキャスト
					Player* player = (Player*)getpGameObject();
					Coin* coin = (Coin*)hit_collision->getpGameObject();
					if (*coin->getpColorChangeCounter() <= 0)
					{
						*coin->getpColorChangeCounter() = 120;

						// スコアアップ
						player->getpGameScene()->setScore(player->getpGameScene()
														  ->getScore() + 10);
					}

					// めり込み解消
					//EliminationOfNesting(player->GetTransform(), hit_my_object->getpHitVector());

					// 相手のオブジェクトを消去
					//GameObjectManager::ReleaseGameObjectBaseFromArray(hit_collision->getpGameObject());

					break;
				}
			}
			break;
		}
		case CollisionBase::Type::ENEMY:
		{
			// 相手の衝突オブジェクトで振り分け
			switch ((EnemyCollision::ObjectTag)hit_object->getTag())
			{
				case EnemyCollision::ObjectTag::SUBSTANCE_SPHERE:
				{
					// ダウンキャスト
					Player* player = (Player*)getpGameObject();

					// めり込み解消
					EliminationOfNesting(player->getpTransform(), 
										 hit_my_object->getpHitVector());

					// スコアダウン
					player->getpGameScene()->setGameOver(1);

					// 相手のオブジェクトを消去
					GameObjectManager::getpInstance()
						->ReleaseGameObjectBaseFromArray(hit_collision->getpGameObject());
					break;
				}
			}
			break;
		}
		case CollisionBase::Type::GOAL:
		{
			// 相手の衝突オブジェクトで振り分け
			switch ((EnemyCollision::ObjectTag)hit_object->getTag())
			{
				case EnemyCollision::ObjectTag::SUBSTANCE_SPHERE:
				{
					// ダウンキャスト
					Player* player = (Player*)getpGameObject();

					// めり込み解消
					EliminationOfNesting(player->getpTransform(), 
										 hit_my_object->getpHitVector());

					// スコアダウン
					player->getpGameScene()->setGameOver(0);

					// 相手のオブジェクトを消去
					GameObjectManager::getpInstance()
						->ReleaseGameObjectBaseFromArray(hit_collision->getpGameObject());
					break;
				}
			}
			break;
		}
	}
}