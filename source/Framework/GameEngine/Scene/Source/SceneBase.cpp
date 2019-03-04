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



int SceneBase::StateBase::getID()
{
	return id_;
}



void SceneBase::StateBase::setID(int value)
{
	id_ = value;
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

	InitState();
}



void SceneBase::setResetState(StateBase* value)
{
	if (state_ != nullptr)
	{
		SafeRelease::PlusUninit(&state_);
	}
	state_ = value;
}



bool SceneBase::getIsPause()
{
	return is_pause_;
}



void SceneBase::setIsPause(bool value)
{
	if (is_pause_ == value) return;
	is_pause_ = value;
	if (is_pause_)
	{
		state_->PauseEntrance();
	}
	else
	{
		state_->PauseExit();
	}
}



int SceneBase::getCurrentStateID()
{
	return current_state_id_;
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
}



SceneBase::~SceneBase()
{
}



void SceneBase::InitState()
{
	if (state_ == nullptr) return;
	state_->setScene(this);
	state_->Init();
	current_state_id_ = state_->getID();
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