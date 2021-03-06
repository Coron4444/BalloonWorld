//================================================================================
//!	@file	 SceneManager.cpp
//!	@brief	 シーンマネージャClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/01
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../SceneManager.h"



//****************************************
// 定数定義
//****************************************
const Fade::Type SceneManager::DEFAULT_FADE_TYPE = Fade::Type::NORMAL;
const float      SceneManager::DEFAULT_FADE_SPEED = 0.3f;
const XColor4    SceneManager::DEFAULT_FADE_COLOR(1.0f, 1.0f, 1.0f, 1.0f);



//****************************************
// プロパティ定義
//****************************************
bool SceneManager::CommonData::getIsClear()
{
	return is_clear_;
}



void SceneManager::CommonData::setIsClear(bool value)
{
	is_clear_ = value;
}



void SceneManager::setNextScene(SceneBase* value)
{
	// 既にほかの要求を受け付けている場合
	if (state_ != SceneManager::State::NONE)
	{
		SafeRelease::PlusUninit(&value);
		return;
	}

	// 変更シーンの登録
	next_scene_ = value;

	// ステートの変更
	state_ = SceneManager::State::CHANGE_SCENE;

	
	// フェードアウト初期化
	GameObjectManager::getpInstance()->getpDrawManager()
		->StartFadeOut(fade_type_,
					  Vec2((float)GameEngine::SCREEN_WIDTH, (float)GameEngine::SCREEN_HEIGHT),
					  fade_color_, fade_speed_);
	
	// フェード中フラグOFF
	is_fade_ = true;
}



void SceneManager::setResetScene(SceneBase::StateBase* value)
{
	// 既にほかの要求を受け付けている場合
	if (state_ != SceneManager::State::NONE) return;

	// ステートの変更
	state_ = SceneManager::State::RESET_SCENE;

	// 現在のシーンにリセット用ステート設定
	current_scene_->setResetState(value);

	// フェードアウト初期化
	GameObjectManager::getpInstance()->getpDrawManager()
		->StartFadeOut(fade_type_,
					   Vec2((float)GameEngine::SCREEN_WIDTH, (float)GameEngine::SCREEN_HEIGHT),
					   fade_color_, fade_speed_);

	// フェード中フラグOFF
	is_fade_ = true;
}



SceneManager::CommonData* SceneManager::getpCommonData()
{
	return common_data_;
}



bool SceneManager::getIsFade()
{
	return is_fade_;
}



void SceneManager::setFadeType(Fade::Type value)
{
	fade_type_ = value;
}



void SceneManager::setFadeSpeed(float value)
{
	fade_speed_ = value;
}



void SceneManager::setFadeColor(XColor4 value)
{
	fade_color_ = value;
}

void SceneManager::CommonData::setScore(int value)
{
	score_ = value;
}



int SceneManager::CommonData::getScore()
{
	return score_;
}



//****************************************
// 関数定義
//****************************************
SceneManager::CommonData::CommonData()
{

}



SceneManager::CommonData::~CommonData()
{

}



void SceneManager::CommonData::Init()
{
	is_clear_ = false;
	score_ = 0;
}



SceneManager::SceneManager() :
	state_(State::NONE),
	common_data_(nullptr),
	current_scene_(nullptr),
	next_scene_(nullptr),
	is_fade_(false),
	fade_type_(DEFAULT_FADE_TYPE),
	fade_speed_(DEFAULT_FADE_SPEED),
	fade_color_(DEFAULT_FADE_COLOR)
{
}



SceneManager::~SceneManager()
{
}



void SceneManager::Init(SceneBase* scene)
{
	// 共有データーの初期化
	common_data_ = new CommonData();
	common_data_->Init();

	// ゲームオブジェクトマネージャの初期化
	GameObjectManager::getpInstance()->Init();

	// シーンの初期化
	current_scene_ = scene;
	current_scene_->setSceneManager(this);
	current_scene_->Init();
}



void SceneManager::Uninit()
{
	// シーンの終了処理
	if (current_scene_ != nullptr) current_scene_->Uninit();
	if (next_scene_ != nullptr)  next_scene_->Uninit();

	//ゲームオブジェクトマネージャの終了処理
	GameObjectManager::getpInstance()->Uninit();
	GameObjectManager::ReleaseInstance();

	// 各種開放
	SafeRelease::Normal(&current_scene_);
	SafeRelease::Normal(&next_scene_);
	SafeRelease::Normal(&common_data_);
}



void SceneManager::Update()
{
	switch (state_)
	{
		case SceneManager::State::CHANGE_SCENE:
		{
			// シーン変更
			SceneChange();
			break;
		}
		case SceneManager::State::RESET_SCENE:
		{
			// シーンリセット
			SceneReset();
			break;
		}
	}
}



void SceneManager::UpdateScene()
{
	if (current_scene_ == nullptr) return;

	// 各シーン特有の更新
	current_scene_->Update();

	// ゲームオブジェクトマネージャの更新
	GameObjectManager::getpInstance()->Update();
}



void SceneManager::DrawScene()
{
	if (current_scene_ == nullptr) return;

	//ゲームオブジェクトマネージャの描画
	GameObjectManager::getpInstance()->Draw();
}



void SceneManager::SceneChange()
{
	// フェード処理が終わっているかどうか
	if (!GameObjectManager::getpInstance()->getpDrawManager()->IsFadeEnd()) return;

	// フェードのステートごとの処理
	if (GameObjectManager::getpInstance()->getpDrawManager()
		->IsFadeState(Fade::State::FADE_OUT))
	{
		// 現在のメインシーンの終了処理
		SafeRelease::PlusUninit(&current_scene_);

		// ゲームオブジェクトマネージャのシーン変更時終了処理
		GameObjectManager::getpInstance()->UninitWhenChangeScene();

		// 新しいシーンへ移行
		current_scene_ = next_scene_;
		next_scene_ = nullptr;
		current_scene_->setSceneManager(this);
		current_scene_->Init();

		// フェードイン初期化
		GameObjectManager::getpInstance()->getpDrawManager()
			->StartFadeIn(fade_type_,
						 Vec2((float)GameEngine::SCREEN_WIDTH, (float)GameEngine::SCREEN_HEIGHT),
						 fade_color_, fade_speed_);
	}
	else if (GameObjectManager::getpInstance()->getpDrawManager()
			 ->IsFadeState(Fade::State::FADE_IN))
	{
		// フェード終了処理
		state_ = SceneManager::State::NONE;
	
		// フェード中フラグOFF
		is_fade_ = false;
	}
}



void SceneManager::SceneReset()
{
	// フェード処理が終わっているかどうか
	if (!GameObjectManager::getpInstance()->getpDrawManager()->IsFadeEnd()) return;

	// フェードのステートごとの処理
	if (GameObjectManager::getpInstance()->getpDrawManager()
		->IsFadeState(Fade::State::FADE_OUT))
	{
		// 現在のメインシーンのリセット
		GameObjectManager::getpInstance()->Reset();
		current_scene_->Reset();
		current_scene_->InitState();

		// フェードイン初期化
		GameObjectManager::getpInstance()->getpDrawManager()
			->StartFadeIn(fade_type_,
						 Vec2((float)GameEngine::SCREEN_WIDTH, (float)GameEngine::SCREEN_HEIGHT),
						 fade_color_, fade_speed_);
	}
	else if (GameObjectManager::getpInstance()->getpDrawManager()
			 ->IsFadeState(Fade::State::FADE_IN))
	{
		// フェード終了処理
		state_ = SceneManager::State::NONE;
		
		// フェード中フラグOFF
		is_fade_ = false;
	}
}