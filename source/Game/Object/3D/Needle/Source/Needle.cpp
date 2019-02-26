//================================================================================
//!	@file	 Needle.cpp
//!	@brief	 ��Class
//! @details 
//!	@author  Kai Araki									@date 2019/2/20
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../Needle.h"

#include <Tool/SafeRelease.h>



//****************************************
// �萔��`
//****************************************



//****************************************
// �v���p�e�B��`
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
// �֐���`
//****************************************
Needle::State::~State()
{
}



void Needle::Init(DrawBase* draw, CollisionBase* collision)
{
	// ���N���X�̏�����
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