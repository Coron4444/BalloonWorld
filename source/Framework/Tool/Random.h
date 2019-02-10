//================================================================================
//!	@file	 Random.h
//!	@brief	 �����_��Class
//! @details Singleton
//!	@author  Kai Araki									@date 2019/02/10
//================================================================================
#ifndef	_RANDOM_H_
#define _RANDOM_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <random>



//************************************************************														   
//! @brief   �����_��Class(Singleton)
//!
//! @details �����_����Class(Singleton)
//************************************************************
class Random
{
//====================
// static�ϐ�
//====================
private:
	static Random* instance_;	//!< �C���X�^���X


//====================
// static�v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �C���X�^���X�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Random* �C���X�^���X
	//----------------------------------------
	static Random* getpInstance();


//====================
// static�֐�
//====================
public:
	//----------------------------------------
	//! @brief �C���X�^���X����֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	static void ReleaseInstance();


//====================
// �ϐ�
//====================
private:
	std::random_device seed_;						//!< ���S�����_���V�[�h
	std::mt19937 mersenne_twister_;					//!< �����Z���k�c�C�X�^�[����������
	

//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief Int�^�����l�擾�֐�
	//! @details
	//! @param min �ŏ��l
	//! @param max �ő�l
	//! @retval int int�^�����l
	//----------------------------------------
	int getInt(int min, int max);

	//----------------------------------------
	//! @brief Float�^�����l�擾�֐�
	//! @details
	//! @param min �ŏ��l
	//! @param max �ő�l
	//! @retval int int�^�����l
	//----------------------------------------
	float getFloat(float min, float max);

	//----------------------------------------
	//! @brief Double�^�����l�擾�֐�
	//! @details
	//! @param min �ŏ��l
	//! @param max �ő�l
	//! @retval int int�^�����l
	//----------------------------------------
	double getDouble(double min, double max);


//====================
// �֐�
//====================
private:
	//----------------------------------------
	//! @brief �R���X�g���N�^
	//! @param void �Ȃ�
	//----------------------------------------
	Random();

public:
	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init();

	//----------------------------------------
	//! @brief �I���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Uninit();


private:
	

//====================
// �����ς݊֐�
//====================
private:
	Random(const Random& class_name) = delete;
	Random& operator = (const Random& class_name) = delete;
};



#endif