//================================================================================
//!	@file	 Scaffold.cpp
//!	@brief	 足場Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../Scaffold.h"


//****************************************
// プロパティ定義
//****************************************



//****************************************
// プロパティ定義
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
// 関数定義
//****************************************
void Scaffold::Init(DrawBase* draw, CollisionBase* collision)
{
	// 基底クラスの初期化
	GameObjectBase::Init(draw, collision);
}



void Scaffold::Update()
{
}