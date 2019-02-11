//================================================================================
//!	@file	 GameObjectManager.cpp
//!	@brief	 ゲームオブジェクトマネージャClass
//! @details Singleton
//!	@author  Kai Araki									@date 2018/07/13
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../GameObjectManager.h"
#include "../../GameObjectBase.h"

#include <Tool/SafeRelease.h>



//****************************************
// static変数定義
//****************************************
GameObjectManager* GameObjectManager::instance_ = nullptr;



//****************************************
// staticプロパティ定義
//****************************************
GameObjectManager* GameObjectManager::getpInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new GameObjectManager();
	}
	return instance_;
}



//****************************************
// static関数定義
//****************************************
void GameObjectManager::ReleaseInstance()
{
	SafeRelease::Normal(&instance_);
}



//****************************************
// プロパティ定義
//****************************************
UpdateManager* GameObjectManager::getpUpdateManager()
{
	return &update_manager_;
}



DrawManager* GameObjectManager::getpDrawManager()
{
	return &draw_manager_;
}



CollisionManager* GameObjectManager::getpCollisionManager()
{
	return &collision_manager_;
}



//****************************************
// 関数定義
//****************************************
GameObjectManager::GameObjectManager()
{
}



void GameObjectManager::Init()
{
	// 各種マネージャの初期化
	update_manager_.Init();
	draw_manager_.Init();
	collision_manager_.Init();
}



void GameObjectManager::Uninit()
{
	// ゲームオブジェクトの解放
	Release();

	// 各種マネージャの終了処理
	collision_manager_.Uninit();
	draw_manager_.Uninit();
	update_manager_.Uninit();
}



void GameObjectManager::UninitWhenChangeScene()
{
	// ゲームオブジェクトの解放
	Release();

	// 各種マネージャのシーン変更時の終了処理
	collision_manager_.UninitWhenChangeScene();
	draw_manager_.UninitWhenChangeScene();
	update_manager_.UninitWhenChangeScene();
}



void GameObjectManager::Update()
{
	// 追加待ち配列の中身を追加
	AddContentsOfAwaitAddArray();

	// 解放待ち配列の中身を解放
	ReleaseContentsOfAwaitReleaseArray();

	// 更新
	update_manager_.Update();
	collision_manager_.Update();
	draw_manager_.Update();
}



void GameObjectManager::Draw()
{
	draw_manager_.Draw();
}



void GameObjectManager::Reset()
{
	// 登録されているオブジェクトを全てリセット
	for (unsigned i = 0; i < all_game_object_.getEndIndex(); i++)
	{
		all_game_object_.getObject(i)->Reset();
	}
}



void GameObjectManager::AddGameObjectBaseToArray(GameObjectBase* game_object)
{
	await_add_.AddToArray(game_object);
}



void GameObjectManager::ReleaseGameObjectBaseFromArray(GameObjectBase* game_object)
{
	// ゲームオブジェクト終了処理
	game_object->Uninit();

	// コンポーネントをマネージャから解放
	ReleaseComponentFromManager(game_object);

	// 解放待ち配列に追加
	await_release_.AddToArray(game_object);
}



void GameObjectManager::AddContentsOfAwaitAddArray()
{
	// 追加待ちがあるかどうか
	if (await_add_.getEndIndex() <= 0) return;

	// 追加
	for (unsigned i = 0; i < await_add_.getEndIndex(); i++)
	{
		// 全体配列へ追加
		all_game_object_.AddToArray(await_add_.getObject(i));

		// コンポーネントをマネージャにセット
		AddComponentToManager(await_add_.getObject(i));
	}

	// 追加待ち配列をリセット
	await_add_.Reset();
}



void GameObjectManager::ReleaseContentsOfAwaitReleaseArray()
{
	// 解放待ちがあるかどうか
	if (await_release_.getEndIndex() <= 0) return;

	// 解放とソート
	for (unsigned i = 0; i < await_release_.getEndIndex(); i++)
	{
		// 全体配列からの消去
		all_game_object_.DeleteFromArrayAndSort(await_release_.getObject(i));

		// オブジェクトの消去
		GameObjectBase* temp = await_release_.getObject(i);
		SafeRelease::Normal(&temp);
	}

	// 解放待ち配列をリセット
	await_release_.Reset();
}



void GameObjectManager::AddComponentToManager(GameObjectBase* game_object)
{
	if (game_object->getpUpdate() != nullptr)
	{
		update_manager_.AddUpdateBaseToArray(game_object->getpUpdate());
	}

	if (game_object->getpDraw() != nullptr)
	{
		draw_manager_.AddDrawBaseToArray(game_object->getpDraw());
	}

	if (game_object->getpCollision() != nullptr)
	{
		collision_manager_.AddCollisionBaseToArray(game_object->getpCollision());
	}
}



void GameObjectManager::ReleaseComponentFromManager(GameObjectBase* game_object)
{
	if (game_object->getpUpdate() != nullptr)
	{
		update_manager_.ReleaseUpdateBaseFromArray(game_object->getpUpdate());
	}

	if (game_object->getpDraw() != nullptr)
	{
		draw_manager_.ReleaseDrawBaseFromArray(game_object->getpDraw());
	}

	if (game_object->getpCollision() != nullptr)
	{
		collision_manager_.ReleaseCollisionBaseFromArray(game_object->getpCollision());
	}
}



void GameObjectManager::Release()
{
	// 解放待ち配列の中身を解放
	ReleaseContentsOfAwaitReleaseArray();

	// 残りのオブジェクトを全て解放待ちに登録
	for (unsigned i = 0; i < await_add_.getEndIndex(); i++)
	{
		ReleaseGameObjectBaseFromArray(await_add_.getObject(i));
	}

	for (unsigned i = 0; i < all_game_object_.getEndIndex(); i++)
	{
		ReleaseGameObjectBaseFromArray(all_game_object_.getObject(i));
	}

	// 解放待ち配列の中身を解放
	ReleaseContentsOfAwaitReleaseArray();
	
	// オブジェクト配列をリセット
	all_game_object_.Reset();
}