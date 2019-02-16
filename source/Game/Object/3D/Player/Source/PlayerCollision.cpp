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
const float PlayerCollision::MAIN_SPHERE_RADIUS = 2.0f;



//****************************************
// 関数定義
//****************************************
void PlayerCollision::Init()
{
	// タイプ
	CollisionBase::setType(CollisionBase::Type::PLAYER);

	//ダウンキャスト
	player_ = (Player*)getpGameObject();

	// 衝突オブジェクト作成
	collision_object_ = new CollisionObject();
	collision_object_->Init((int)ObjectTag::MAIN, this);
	CollisionBase::AddCollisionObject(collision_object_);

	// メイン球の作成
	main_sphere_ = new Sphere();
	Vector3D position = *getpGameObject()->getpTransform()->getpPosition();
	position.y += 2.0f;
	main_sphere_->Init(position, MAIN_SPHERE_RADIUS);
	collision_object_->AddShape((int)ShapeTag::MAIN, main_sphere_);
}



void PlayerCollision::Update()
{
	// メイン球の更新
	Vector3D position = *getpGameObject()->getpTransform()->getpPosition();
	position.y += 2.0f;
	*main_sphere_->getpPosition() = position;
}



void PlayerCollision::HitCollision(CollisionInformation* information)
{
	// 自分の衝突形状で振り分ける
	switch ((PlayerCollision::ShapeTag)information->getpMyShape()->getTag())
	{
		case PlayerCollision::ShapeTag::MAIN:
		{
			HitMainSphere(information);
			normal_ = *information->getpCollisionPointNormal();
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



void PlayerCollision::HitMainSphere(CollisionInformation* information)
{
	// 相手衝突基底クラスで振り分け
	switch (information->getpOpponentCollisionBase()->getType())
	{
		case CollisionBase::Type::COIN:
		{
			// 相手の衝突形状で振り分け
			switch ((CoinCollision::ShapeTag)information->getpOpponentShape()
					->getTag())
			{
				case CoinCollision::ShapeTag::MAIN:
				{
					Coin* coin = (Coin*)information->getpOpponentGameObject();
					if (*coin->getpColorChangeCounter() <= 0)
					{
						*coin->getpColorChangeCounter() = 120;
					}

					// めり込み解消
					CollisionCalculation
						::EliminationOfNesting(information, 
											   player_->getpTransform());

					// 相手のオブジェクトを消去
					//GameObjectManager::ReleaseGameObjectBaseFromArray(hit_collision->getpGameObject());
					break;
				}
			}
			break;
		}
		case CollisionBase::Type::ENEMY:
		{
			// 相手の衝突形状で振り分け
			switch ((EnemyCollision::ShapeTag)information->getpOpponentShape()
					->getTag())
			{
				case EnemyCollision::ShapeTag::MAIN:
				{
					// めり込み解消
					CollisionCalculation
						::EliminationOfNesting(information,
											   player_->getpTransform());

					//// 相手のオブジェクトを消去
					//GameObjectManager::getpInstance()
					//	->ReleaseGameObjectBaseFromArray(hit_collision->getpGameObject());
					break;
				}
			}
			break;
		}
		case CollisionBase::Type::GOAL:
		{
			// 相手の衝突形状で振り分け
			switch ((EnemyCollision::ShapeTag)information->getpOpponentShape()
					->getTag())
			{
				case EnemyCollision::ShapeTag::MAIN:
				{
					// めり込み解消
					CollisionCalculation
						::EliminationOfNesting(information,
											   player_->getpTransform());

					//// 相手のオブジェクトを消去
					//GameObjectManager::getpInstance()
					//	->ReleaseGameObjectBaseFromArray(hit_collision->getpGameObject());
					break;
				}
			}
			break;
		}
	}
}



void PlayerCollision::DebugDisplay()
{
#ifdef _DEBUG
	// ウィンドウの設定
	ImGui::SetNextWindowPos(ImVec2(30, 30), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(150, 500), ImGuiSetCond_Once);
	ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(1.0f, 0.0f, 0.0f, 0.8f));
	ImGui::PushStyleColor(ImGuiCol_TitleBgCollapsed, ImVec4(0.0f, 0.5f, 1.0f, 0.8f));
	ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.5f, 0.0f, 0.0f, 0.8f));
	ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.0f, 0.5f, 0.5f, 1.0f));

	// 開始
	ImGui::Begin("Player", nullptr, ImGuiWindowFlags_MenuBar);

	ImGui::Text("X : %f", normal_.x);
	ImGui::Text("Y : %f", normal_.y);
	ImGui::Text("Z : %f", normal_.z);

	// 終了
	ImGui::End();

	// 色の解放(設定でプッシュした分だけ)
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
#endif
}