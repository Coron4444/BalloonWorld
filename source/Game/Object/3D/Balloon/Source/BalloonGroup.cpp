//================================================================================
//!	@file	 BalloonGroup.cpp
//!	@brief	 ���D�QClass
//! @details 
//!	@author  Kai Araki									@date 2019/02/10
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../BalloonGroup.h"
#include "../BalloonFactory.h"



//****************************************
// �萔��`
//****************************************
const int BalloonGroup::BALLOON_LINE_NUM = 20;



//****************************************
// �v���p�e�B��`
//****************************************
ReferenceList<BalloonGroup>* BalloonGroup::getpReferenceList()
{
	return &reference_list_;
}



int BalloonGroup::getBalloonNum()
{
	return (int)balloons_.size();
}



int BalloonGroup::getRemainingBalloonNum()
{
	return end_index_ + 1;
}



Vector3D BalloonGroup::getPosition()
{
	return *getpTransform()->getpPosition();
}



void BalloonGroup::setPosition(Vector3D value)
{
	*getpTransform()->getpPosition() = value;
	for (int i = 0; i < end_index_ + 1; i++)
	{
		balloons_[i]->setPosition(*getpTransform()->getpPosition());
	}
}



//****************************************
// �֐���`
//****************************************
void BalloonGroup::Init(unsigned balloon_num, Vector3D position)
{
	// �Q�ƃ��X�g�֎�����o�^
	reference_list_.setObject(this);

	// ���D����
	BalloonFactory factory;
	end_index_ = balloon_num - 1;
	for (unsigned i = 0; i < balloon_num; i++)
	{
		Balloon* balloon = factory.Create(BALLOON_LINE_NUM, position);
		balloons_.push_back(balloon);
		balloons_[i]->setPosition(position);
	}

	// ���N���X�̏�����
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



void BalloonGroup::AddVelocity(Vector3D velocity)
{
	for (int i = 0; i < end_index_ + 1; i++)
	{
		balloons_[i]->AddVelocity(velocity);
	}
}



void BalloonGroup::AddAcceleration(Vector3D acceleration)
{
	for (int i = 0; i < end_index_ + 1; i++)
	{
		balloons_[i]->AddAcceleration(acceleration);
	}
}



void BalloonGroup::Rupture()
{

}