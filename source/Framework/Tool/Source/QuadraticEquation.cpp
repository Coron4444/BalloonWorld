//================================================================================
//!	@file	 QuadraticEquation.cpp
//!	@brief	  二次方程式Class
//! @details 
//!	@author  Kai Araki									@date 2017/12/12
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../QuadraticEquation.h"



//****************************************
// プロパティ定義
//****************************************
float* QuadraticEquation::getpA()
{
	return &a_;
}



float* QuadraticEquation::getpB()
{
	return &b_;
}



float* QuadraticEquation::getpC()
{
	return &c_;
}



float* QuadraticEquation::getpD()
{
	return &d_;
}



float QuadraticEquation::getAnswer0()
{
	return answer0_;
}



float QuadraticEquation::getAnswer1()
{
	return answer1_;
}



//****************************************
// 関数定義
//****************************************
void QuadraticEquation::CreateD()
{
	d_ = b_ * b_ - (4.0f * a_ * c_);
}



bool QuadraticEquation::CalculateTheSolutionFormula()
{
	CreateD();

	// 解の公式が計算可能か
	if (d_ < 0.0f) return false;

	// 解の公式を解く
	d_ = sqrtf(d_);

	answer0_ = (-b_ + d_) / (2.0f * a_);
	answer1_ = (-b_ - d_) / (2.0f * a_);

	return true;
}