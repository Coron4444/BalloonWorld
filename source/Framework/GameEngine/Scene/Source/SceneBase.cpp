//================================================================================
//!	@file	 SceneBase.cpp
//!	@brief	 シーンBaseClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../SceneBase.h"

#include <Tool/SafeRelease.h>



//****************************************
// プロパティ定義
//****************************************
SceneBase* SceneBase::StateBase::getpScene()
{
	return scene_;
}



void SceneBase::StateBase::setScene(SceneBase* value)
{
	scene_ = value;
}



SceneManager* SceneBase::getpSceneManager()
{ 
	return scene_manager_; 
}



void SceneBase::setSceneManager(SceneManager* value)
{ 
	scene_manager_ = value; 
}



SceneBase::StateBase* SceneBase::getpState()
{ 
	return state_; 
}



void SceneBase::setState(StateBase* value)
{
	if (state_ != nullptr)
	{
		SafeRelease::PlusUninit(&state_);
	}

	state_ = value;

	if (state_ != nullptr)
	{
		state_->setScene(this);
		state_->Init();
	}
}



//****************************************
// 関数定義
//****************************************
SceneBase::StateBase::~StateBase()
{
}



SceneBase::SceneBase(StateBase* state)
	: state_(state)
{
	state_->setScene(this);
}



SceneBase::~SceneBase()
{
}



void SceneBase::InitState()
{
	if (state_ == nullptr) return;
	state_->Init();
}



void SceneBase::UninitState()
{
	SafeRelease::PlusUninit(&state_);
}



void SceneBase::UpdateState()
{
	if (state_ == nullptr) return;
	state_->Update();
}



void SceneBase::ResetState()
{
	if (state_ == nullptr) return;
	state_->Reset();
}