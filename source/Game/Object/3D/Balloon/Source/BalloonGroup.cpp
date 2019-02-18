//================================================================================
//!	@file	 BalloonGroup.cpp
//!	@brief	 風船群Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/10
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../BalloonGroup.h"
#include "../BalloonFactory.h"



//****************************************
// 定数定義
//****************************************
const int BalloonGroup::BALLOON_LINE_NUM = 20;



//****************************************
// プロパティ定義
//****************************************
ReferenceList<BalloonGroup>* BalloonGroup::getpReferenceList()
{
	return &reference_list_;
}



unsigned BalloonGroup::getBalloonNum()
{
	return balloons_.size();
}



Vec3 BalloonGroup::getPosition()
{
	return *getpTransform()->getpPosition();
}



void BalloonGroup::setPosition(Vec3 value)
{
	*getpTransform()->getpPosition() = value;
	for (int i = 0; i < end_index_ + 1; i++)
	{
		balloons_[i]->setPosition(*getpTransform()->getpPosition());
	}
}



//****************************************
// 関数定義
//****************************************
void BalloonGroup::Init(unsigned balloon_num)
{
	// 参照リストへ自分を登録
	reference_list_.setObject(this);

	// 風船生成
	BalloonFactory factory;
	end_index_ = balloon_num - 1;
	for (unsigned i = 0; i < balloon_num; i++)
	{
		Balloon* balloon = factory.Create(BALLOON_LINE_NUM);
		balloons_.push_back(balloon);
		balloons_[i]->setPosition(*getpTransform()->getpPosition());
	}

	// 基底クラスの初期化
	setIsUpdate(false);
	GameObjectBase::Init(nullptr, nullptr);
}



void BalloonGroup::Uninit()
{
	UninitComponent();
	reference_list_.Uninit();
}



void BalloonGroup::ReleaseConstraint()
{
	if (end_index_ < 0) return;
	balloons_[end_index_]->ReleaseBaseConstraint();
	end_index_--;
}



void BalloonGroup::AddVelocity(Vec3 velocity)
{
	for (int i = 0; i < end_index_ + 1; i++)
	{
		balloons_[i]->AddVelocity(velocity);
	}
}



void BalloonGroup::AddAcceleration(Vec3 acceleration)
{
	for (int i = 0; i < end_index_ + 1; i++)
	{
		balloons_[i]->AddAcceleration(acceleration);
	}
}



void BalloonGroup::Rupture()
{

}