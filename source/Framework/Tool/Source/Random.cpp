//================================================================================
//!	@file	 Random.cpp
//!	@brief	 �����_��Class
//! @details Singleton
//!	@author  Kai Araki									@date 2019/02/10
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../Random.h"

#include <Tool/SafeRelease.h>



//****************************************
// static�ϐ���`
//****************************************
Random* Random::instance_ = nullptr;



//****************************************
// static�v���p�e�B��`
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
// static�֐���`
//****************************************
void Random::ReleaseInstance()
{
	SafeRelease::Normal(&instance_);
}



//****************************************
// �v���p�e�B��`
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
// �֐���`
//****************************************
Random::Random()
{
}



void Random::Init()
{
	// ����������
	mersenne_twister_.seed(seed_());
}



void Random::Uninit()
{
}