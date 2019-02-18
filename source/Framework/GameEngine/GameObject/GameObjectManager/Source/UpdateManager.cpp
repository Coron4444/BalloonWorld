//================================================================================
//!	@file	 UpdateManager.cpp
//!	@brief	 更新マネージャーClass
//! @details 
//!	@author  Kai Araki									@date 2019/01/19
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../UpdateManager.h"
#include "../../GameObjectBase.h"



//****************************************
// 関数定義
//****************************************
void UpdateManager::Init()
{
}



void UpdateManager::Uninit()
{
	// 追加待ち配列のリセット
	await_add_.Reset();

	// 解放待ち配列のリセット
	await_release_.Reset();

	// 全更新配列のリセット
	all_object_.Reset();
}



void UpdateManager::UninitWhenChangeScene()
{
	// 追加待ち配列のリセット
	await_add_.Reset();

	// 解放待ち配列のリセット
	await_release_.Reset();

	// 全更新配列のリセット
	all_object_.Reset();
}



void UpdateManager::Update()
{
	// 追加待ち配列の中身を追加
	AddContentsOfAwaitAddArray();

	// 解放待ち配列の中身を解放
	ReleaseContentsOfAwaitReleaseArray();

	// 物理更新
	for (unsigned i = 0; i < all_object_.getEndIndex(); i++)
	{
		if (all_object_.getObject(i)->getpPhysics() == nullptr) continue;
		all_object_.getObject(i)->getpPhysics()->Update();
	}

	// 更新
	for (unsigned i = 0; i < all_object_.getEndIndex(); i++)
	{
		if (all_object_.getObject(i) == nullptr) continue;
		all_object_.getObject(i)->Update();
	}

	// 後更新
	for (unsigned i = 0; i < all_object_.getEndIndex(); i++)
	{
		if (all_object_.getObject(i) == nullptr) continue;
		all_object_.getObject(i)->LateUpdate();
	}

	// デバッグ
#ifdef _DEBUG
	for (unsigned i = 0; i < all_object_.getEndIndex(); i++)
	{
		if (all_object_.getObject(i) == nullptr) continue;
		all_object_.getObject(i)->DebugDisplay();
	}
#endif
}



void UpdateManager::AddGameObjectBase(GameObjectBase* update)
{
	// 追加待ち配列に追加
	await_add_.AddToArray(update);
}



void UpdateManager::ReleaseGameObjectBase(GameObjectBase* update)
{
	// 解放待ち配列に追加
	await_release_.AddToArray(update);
}



void UpdateManager::AddContentsOfAwaitAddArray()
{
	// 追加待ちがあるかどうか
	if(await_add_.getEndIndex() <= 0) return;

	// 追加
	for (unsigned i = 0; i < await_add_.getEndIndex(); i++)
	{
		all_object_.AddToArray(await_add_.getObject(i));
	}

	// 追加待ち配列をリセット
	await_add_.Reset();
}



void UpdateManager::ReleaseContentsOfAwaitReleaseArray()
{
	// 解放待ちがあるかどうか
	if(await_release_.getEndIndex() <= 0) return;

	// 解放とソート
	for (unsigned i = 0; i < await_release_.getEndIndex(); i++)
	{
		all_object_.DeleteFromArrayAndSort(await_release_.getObject(i));
	}

	// 解放待ち配列をリセット
	await_release_.Reset();
}