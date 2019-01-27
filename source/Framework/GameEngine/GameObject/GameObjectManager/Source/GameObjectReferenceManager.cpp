//================================================================================
//!	@file	 GameObjectReferenceManager.cpp
//!	@brief	 ゲームオブジェクト参照マネージャClass
//! @details 
//!	@author  Kai Araki									@date 2018/07/15
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../GameObjectReferenceManager.h"
#include "../../GameObjectBase.h"
#include <Tool/SafeRelease.h>



//****************************************
// 関数定義
//****************************************
GameObjectReferenceManager::ReferenceData::ReferenceData(GameObjectBase* source,
														 void* pointer,
														 GameObjectBase* destination)
{
	reference_source_ = source;
	reference_destination_ = destination;
	reference_pointer_ = pointer;
}



GameObjectReferenceManager::~GameObjectReferenceManager()
{
	AllRelease();
}



void GameObjectReferenceManager::AddReference(GameObjectBase* source, void* pointer,
											  GameObjectBase* destination)
{
	// 参照元マップへの登録の確認
	AddSource(source, pointer, destination);

	// 参照先マップへの登録
	AddDestination(source, pointer, destination);
}



void GameObjectReferenceManager::Release(GameObjectBase* object)
{
	// 参照元マップから消去
	ReleaseSource(object);

	// 参照先マップから消去及びnullptrを代入
	ReleaseDestination(object);
}



void GameObjectReferenceManager::AllRelease()
{
	// 参照元マップの解放
	for (auto& contents : source_map_)
	{
		if (contents.second == nullptr) return;

		for (unsigned i = 0; i < contents.second->getEndIndex(); i++)
		{
			ReferenceData* temp = contents.second->getObject(i);
			SafeRelease::Normal(&temp);
		}

		SafeRelease::Normal(&contents.second);
	}

	// 参照先マップの解放
	for (auto& contents : destination_map_)
	{
		if (contents.second == nullptr) return;

		for (unsigned i = 0; i < contents.second->getEndIndex(); i++)
		{
			ReferenceData* temp = contents.second->getObject(i);
			SafeRelease::Normal(&temp);
		}

		SafeRelease::Normal(&contents.second);
	}
}



void GameObjectReferenceManager::AddSource(GameObjectBase* source, void* pointer,
										   GameObjectBase* destination)
{
	// 参照元の検索
	auto iterator = source_map_.find(source);

	// 登録されていない場合
	if (iterator == source_map_.end())
	{
		// 参照データ配列を作成
		LimitedPointerArray<ReferenceData*, ARRAY_NUM>* temp_array = new LimitedPointerArray<ReferenceData*, ARRAY_NUM>;
		temp_array->AddToArray(new ReferenceData(source, pointer, destination));

		// 参照元マップに参照データ配列を登録
		source_map_.insert(std::make_pair(source, temp_array));
	}
	else
	{
		// 登録されている場合
		unsigned index;
		for (index = 0; index < iterator->second->getEndIndex(); index++)
		{
			// 同じ参照先があるかどうか
			if (iterator->second->getObject(index)->reference_destination_ != destination) continue;

			break;
		}

		// 同じ参照先がないので登録
		if (index != iterator->second->getEndIndex())
		{
			// 追加
			iterator->second->AddToArray(new ReferenceData(source, pointer, destination));
		}
	}
}



void GameObjectReferenceManager::AddDestination(GameObjectBase* source, void* pointer,
																   GameObjectBase* destination)
{
	// 参照先の検索
	auto iterator = destination_map_.find(destination);

	// 登録されていない場合
	if (iterator == destination_map_.end())
	{
		// 参照データ配列を作成
		LimitedPointerArray<ReferenceData*, ARRAY_NUM>* temp_array = new LimitedPointerArray<ReferenceData*, ARRAY_NUM>;
		temp_array->AddToArray(new ReferenceData(source, pointer, destination));

		// 参照元マップに参照データ配列を登録
		destination_map_.insert(std::make_pair(destination, temp_array));
	}
	else
	{
		// 登録されている場合
		unsigned index;
		for (index = 0; index < iterator->second->getEndIndex(); index++)
		{
			// 同じ参照先があるかどうか
			if (iterator->second->getObject(index)->reference_source_ != source) continue;

			break;
		}

		// 同じ参照先がないので登録
		if (index != iterator->second->getEndIndex())
		{
			// 追加
			iterator->second->AddToArray(new ReferenceData(source, pointer, destination));
		}
	}
}



void GameObjectReferenceManager::ReleaseSource(GameObjectBase* object)
{
	auto iterator = source_map_.find(object);

	// 登録されている場合
	if (iterator != source_map_.end())
	{
		for (unsigned i = 0; i < iterator->second->getEndIndex(); i++)
		{
			// 解放
			ReferenceData* temp = iterator->second->getObject(i);
			SafeRelease::Normal(&temp);
		}

		// 配列の解放
		SafeRelease::Normal(&iterator->second);

		// 参照元マップから消去
		source_map_.erase(object);
	}
}



void GameObjectReferenceManager::ReleaseDestination(GameObjectBase* object)
{
	auto iterator = destination_map_.find(object);

	// 登録されている場合
	if (iterator != destination_map_.end())
	{
		for (unsigned i = 0; i < iterator->second->getEndIndex(); i++)
		{
			// nullptrの挿入
			iterator->second->getObject(i)->reference_pointer_ = nullptr;

			// 解放
			ReferenceData* temp = iterator->second->getObject(i);
			SafeRelease::Normal(&temp);
		}

		// 配列の解放
		SafeRelease::Normal(&iterator->second);

		// 参照元マップから消去
		destination_map_.erase(object);
	}
}