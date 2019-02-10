//================================================================================
//!	@file	 Random.cpp
//!	@brief	 ランダムClass
//! @details Singleton
//!	@author  Kai Araki									@date 2019/02/10
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../Random.h"

#include <Tool/SafeRelease.h>



//****************************************
// static変数定義
//****************************************
Random* Random::instance_ = nullptr;



//****************************************
// staticプロパティ定義
//****************************************
Random* Random::getpInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new Random();
	}
	return instance_;
}



//****************************************
// static関数定義
//****************************************
void Random::ReleaseInstance()
{
	SafeRelease::Normal(&instance_);
}



//****************************************
// プロパティ定義
//****************************************
int Random::getInt(int min, int max)
{
	std::uniform_int_distribution<> random_int(min, max);
	return random_int(mersenne_twister_);
}



float Random::getFloat(float min, float max)
{
	std::uniform_real_distribution<> random_double((double)min, (double)max);
	return (float)random_double(mersenne_twister_);
}



double Random::getDouble(double min, double max)
{
	std::uniform_real_distribution<> random_double(min, max);
	return random_double(mersenne_twister_);
}



//****************************************
// 関数定義
//****************************************
Random::Random()
{
}



void Random::Init()
{
	// 乱数初期化
	mersenne_twister_.seed(seed_());
}



void Random::Uninit()
{
}