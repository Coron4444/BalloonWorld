//================================================================================
//
//    �Z�[�t�����[�X�N���X(static)
//    Author : Araki Kai                                �쐬�� : 2018/05/08
//
//================================================================================

#ifndef	_SAFE_RELEASE_H_
#define _SAFE_RELEASE_H_



//****************************************
// �C���N���[�h��
//****************************************

#include <Windows.h>



/*********************************************************//**
* @brief
* �Z�[�t�����[�X�N���X(static)
*
* ���I�I�u�W�F�N�g�̈��S�ȉ����S���֐��Q�N���X
*************************************************************/
class SafeRelease
{
//==============================
// �����o�֐�
//==============================
public:
	/**
	* @brief
	* ����֐�
	* @param
	* pointer : ����Ώۂ̃|�C���^
	*/
	template <class Type>
	static void Normal(Type** pointer)
	{
		if (*pointer != nullptr)
		{
			delete *pointer;
			*pointer = nullptr;
		}
	}

	/**
	* @brief
	* ����֐�(�I���L)
	* @param
	* pointer : ����Ώۂ̃|�C���^
	*/
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

	/**
	* @brief
	* ����֐�(Release�L)
	* @param
	* pointer : ����Ώۂ̃|�C���^
	*/
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