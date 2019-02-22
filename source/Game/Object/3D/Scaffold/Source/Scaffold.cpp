//================================================================================
//!	@file	 Scaffold.cpp
//!	@brief	 ����Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../Scaffold.h"


//****************************************
// �v���p�e�B��`
//****************************************



//****************************************
// �v���p�e�B��`
//****************************************
void Scaffold::setPosition(Vec3 value)
{
	*getpTransform()->getpPosition() = value;
	getpTransform()->CreateWorldMatrix();
}



void Scaffold::setScale(Vec3 value)
{
	*getpTransform()->getpScale() = value;
	getpTransform()->CreateWorldMatrix();
}



XColor4* Scaffold::getpColor()
{
	return &color_;
}



void Scaffold::setColor(XColor4 value)
{
	color_ = value;
}



int Scaffold::getScore()
{
	int temp = score_;
	score_ = 0;
	return temp;
}



void Scaffold::setScore(int value)
{
	score_ = value;
}



//****************************************
// �֐���`
//****************************************
void Scaffold::Init(DrawBase* draw, CollisionBase* collision)
{
	// ���N���X�̏�����
	GameObjectBase::Init(draw, collision);
}



void Scaffold::Update()
{
}