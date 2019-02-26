//================================================================================
//!	@file	 Needle.cpp
//!	@brief	 棘Class
//! @details 
//!	@author  Kai Araki									@date 2019/2/20
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../Needle.h"

#include <Tool/SafeRelease.h>



//****************************************
// 定数定義
//****************************************



//****************************************
// プロパティ定義
//****************************************
Needle* Needle::State::getpNeedle()
{
	return needle_;
}



void Needle::State::setNeedle(Needle* value)
{
	needle_ = value;
}



void Needle::setPosition(Vector3D value)
{
	*getpTransform()->getpPosition() = value;
	getpTransform()->CreateWorldMatrix();
}



void Needle::setScale(float value)
{
	*getpTransform()->getpScale() *= value;
	getpTransform()->CreateWorldMatrix();
}



void Needle::setState(State* value)
{
	SafeRelease::PlusUninit(&state_);
	state_ = value;
	if (state_ == nullptr) return;
	state_->setNeedle(this);
	state_->Init();
}



//****************************************
// 関数定義
//****************************************
Needle::State::~State()
{
}



void Needle::Init(DrawBase* draw, CollisionBase* collision)
{
	// 基底クラスの初期化
	GameObjectBase::Init(draw, collision);
}



void Needle::Uninit()
{
	UninitComponent();
	SafeRelease::PlusUninit(&state_);
}



void Needle::Update()
{
	if (state_ != nullptr) state_->Update();
}