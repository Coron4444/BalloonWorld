//================================================================================
//!	@file	 SceneNull.cpp
//!	@brief	 シーン空白Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/13
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../SceneNull.h"



//****************************************
// 関数定義
//****************************************
SceneNull::StateNull::~StateNull()
{
}



void SceneNull::StateNull::Init()
{
}



void SceneNull::StateNull::Uninit()
{
}



void SceneNull::StateNull::Update()
{
}



void SceneNull::StateNull::PauseEntrance()
{
}



void SceneNull::StateNull::PauseExit()
{
}



SceneNull::SceneNull(StateBase* state)
	: SceneBase(state)
{
}



SceneNull::~SceneNull()
{
}



void SceneNull::Init()
{
	InitState();
}



void SceneNull::Uninit()
{
	UninitState();
}



void SceneNull::Update()
{
	UpdateState();
}



void SceneNull::Reset()
{
}