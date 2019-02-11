//================================================================================
//!	@file	 ReferenceList.h
//!	@brief	 �Q�ƃ��X�gClass
//! @details template
//!	@author  Kai Araki									@date 2019/02/10
//================================================================================
#ifndef	_REFERENCE_LIST_H_
#define _REFERENCE_LIST_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <list>



//************************************************************														   
//! @brief   �Q�ƃ��X�gClass(template)
//!
//! @details �Q�Ƒ���̃��X�gClass(template)
//************************************************************
template<class Type>
class ReferenceList
{
//====================
// �ϐ�
//====================
private:
	Type* object_ = nullptr;					//!< �����̃I�u�W�F�N�g
	std::list<Type**> reference_opponent_;		//!< �Q�Ƒ���|�C���^���X�g


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �I�u�W�F�N�g�ݒ�֐�
	//! @details
	//! @param value �I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	void setObject(Type* value)
	{
		object_ = value;
	}

	//----------------------------------------
	//! @brief �����̃I�u�W�F�N�g�|�C���^�擾�֐�
	//! @details
	//! @param **value �Q�Ƒ���
	//! @retval Type* �����̃I�u�W�F�N�g�|�C���^
	//----------------------------------------
	void getpMyPointer(Type** value)
	{
		*value = object_;
		for (auto contents : reference_opponent_)
		{
			if (value == contents) return;
		}
		reference_opponent_.push_back(value);
	}


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �I���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Uninit()
	{
		// �Q�Ɛ��nullptr��ݒ�
		for (auto contents : reference_opponent_)
		{
			*contents = nullptr;
		}
	}

	//----------------------------------------
	//! @brief �Q�Ɖ���֐�
	//! @details
	//! @param **reference_opponent �Q�Ƒ���
	//! @retval void �Ȃ�
	//----------------------------------------
	void ReleaseReference(Type** reference_opponent)
	{
		for (auto iterator = reference_opponent_.begin(); iterator != reference_opponent_.end(); iterator++)
		{
			if (*iterator == reference_opponent)
			{
				reference_opponent_.erase(iterator);
				break;
			}
		}
	}
};



#endif
