//================================================================================
//!	@file	 SafeRelease.h
//!	@brief	 �Z�[�t�����[�XClass
//! @details static
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================
#ifndef	_SAFE_RELEASE_H_
#define _SAFE_RELEASE_H_



//************************************************************														   
//! @brief   �Z�[�t�����[�X�ϊ�Class(static)
//!
//! @details ���I�I�u�W�F�N�g�̈��S�ȉ����S���֐��QClass(static)
//************************************************************
class SafeRelease
{
//====================
// static�֐�
//====================
public:
	//----------------------------------------
	//! @brief ����֐�
	//! @details
	//! @param pointer ����Ώۂ̃|�C���^
	//! @retval void �Ȃ�
	//----------------------------------------
	template <class Type>
	static void Normal(Type** pointer)
	{
		if (*pointer != nullptr)
		{
			delete *pointer;
			*pointer = nullptr;
		}
	}

	//----------------------------------------
	//! @brief Uninit�t������֐�
	//! @details
	//! @param pointer ����Ώۂ̃|�C���^
	//! @retval void �Ȃ�
	//----------------------------------------
	template <class Type>
	static void PlusUninit(Type** pointer)
	{
		if (*pointer != nullptr)
		{
			(*pointer)->Uninit();
			delete *pointer;
			*pointer = nullptr;
		}
	}

	//----------------------------------------
	//! @brief Release�t������֐�
	//! @details
	//! @param pointer ����Ώۂ̃|�C���^
	//! @retval void �Ȃ�
	//----------------------------------------
	template <class Type>
	static void PlusRelease(Type** pointer)
	{
		if (*pointer != nullptr)
		{
			(*pointer)->Release();
			*pointer = nullptr;
		}
	}
};



#endif