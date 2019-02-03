//================================================================================
//!	@file	 LimitedPointerArray.h
//!	@brief	 �L���|�C���^�[�z��Class
//! @details template
//!	@author  Kai Araki									@date 2018/04/18
//================================================================================
#ifndef	_LIMITED_POINTER_ARRAY_H_
#define _LIMITED_POINTER_ARRAY_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <unordered_map>

#include "SafeRelease.h"



//************************************************************														   
//! @brief   �L���|�C���^�[�z��Class(template)
//!
//! @details �L�����̃|�C���^�[���m�ۂ����z��Class(template)
//************************************************************
template<class Type, unsigned ARRAY_NUM = 100000>
class LimitedPointerArray
{
//====================
// �ϐ�
//====================
private:
	Type array_[ARRAY_NUM];									//!< �z��
	unsigned end_index_ = 0;								//!< �����C���f�b�N�X
	std::unordered_map<Type, unsigned> registration_map_;	//!< �o�^�}�b�v


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �I�u�W�F�N�g�擾�֐�
	//! @details
	//! @param index �C���f�b�N�X
	//! @retval void �Ȃ�
	//----------------------------------------
	Type getObject(unsigned index)
	{
		return array_[index];
	}

	//----------------------------------------
	//! @brief �����C���f�b�N�X�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	unsigned getEndIndex()
	{
		return end_index_;
	}

	//----------------------------------------
	//! @brief �z�񐔎擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	unsigned getArrayNum()
	{
		return ARRAY_NUM;
	}

	//----------------------------------------
	//! @brief �C���f�b�N�X�擾�֐�
	//! @details
	//! @param object �I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	unsigned getIndex(Type object)
	{
		// �o�^�̊m�F
		auto iterator = registration_map_.find(object);

		// �C���f�b�N�X�ԍ���Ԃ�
		if (iterator != registration_map_.end())
		{
			return iterator->second;
		}
	}


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �R���X�g���N�^
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	LimitedPointerArray()
	{
		// �z��̏�����
		for (unsigned i = 0; i < ARRAY_NUM; i++)
		{
			array_[i] = nullptr;
		}

		// �}�b�v�̏�����
		registration_map_.clear();
	}

	//----------------------------------------
	//! @brief �z��ɒǉ��֐�
	//! @details
	//! @param object �ǉ��I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	void AddToArray(Type object)
	{
		// �o�^�̊m�F
		auto iterator = registration_map_.find(object);
		if (iterator != registration_map_.end()) return;

		// �ǉ�
		for (unsigned i = 0; i < ARRAY_NUM; i++)
		{
			if (array_[i] != nullptr) continue;

			// �z��ɒǉ�
			array_[i] = object;

			// �}�b�v�ɓo�^
			registration_map_.insert(std::make_pair(object, i));

			// �G���h�|�C���^�̍X�V
			if (end_index_ < (i + 1))
			{
				end_index_ = (i + 1);
			}
			return;
		}
	}

	//----------------------------------------
	//! @brief �z��̏㏑���֐�
	//! @details
	//! @param old_object �Â��I�u�W�F�N�g
	//! @param new_object �V�K�I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	void OverwriteArray(Type old_object, Type new_object)
	{
		// �o�^�̊m�F
		auto iterator = registration_map_.find(old_object);
		if (iterator != registration_map_.end())
		{
			// �z��̏㏑��
			array_[iterator->second] = new_object;

			// �V�K�I�u�W�F�N�g��o�^�y�ьÂ��I�u�W�F�N�g�̍폜
			registration_map_.insert(std::make_pair(new_object, iterator->second));
			registration_map_.erase(old_object);
		}
		else
		{
			// �Â��I�u�W�F�N�g���Ȃ����ߐV�K����
			AddToArray(new_object);
		}
	}

	//----------------------------------------
	//! @brief �z��̏㏑���Ɖ���֐�
	//! @details
	//! @param old_object �Â��I�u�W�F�N�g
	//! @param new_object �V�K�I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	void OverwriteArrayAndReleaseOldObject(Type old_object, Type new_object)
	{
		// �o�^�̊m�F
		auto iterator = registration_map_.find(old_object);
		if (iterator != registration_map_.end())
		{
			// �z��̏㏑��
			array_[iterator->second] = new_object;

			// �V�K�I�u�W�F�N�g��o�^�y�ьÂ��I�u�W�F�N�g�̍폜
			registration_map_.insert(std::make_pair(new_object, iterator->second));
			registration_map_.erase(old_object);

			// �Â��I�u�W�F�N�g�̉��
			SafeRelease::Normal(&old_object);
		}
		else
		{
			// �Â��I�u�W�F�N�g���Ȃ����ߐV�K����
			AddToArray(new_object);
		}
	}

	//----------------------------------------
	//! @brief ���Z�b�g�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Reset()
	{
		// �z�񂩂�̍폜
		for (unsigned i = 0; i < end_index_; i++)
		{
			array_[i] = nullptr;
		}

		// �}�b�v�̃��Z�b�g
		registration_map_.clear();

		// �G���h�|�C���^�����Z�b�g
		end_index_ = 0;
	}

	//----------------------------------------
	//! @brief �o�^�I�u�W�F�N�g�̉���Ɣz��̃��Z�b�g�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void ReleaseObjectAndReset()
	{
		// �o�^��̉���Ɣz�񂩂�̍폜
		for (unsigned i = 0; i < end_index_; i++)
		{
			SafeRelease::Normal(&array_[i]);
			array_[i] = nullptr;
		}

		// �}�b�v�̃��Z�b�g
		registration_map_.clear();

		// �G���h�|�C���^�����Z�b�g
		end_index_ = 0;
	}

	//----------------------------------------
	//! @brief �z�񂩂�폜�֐�
	//! @details
	//! @param object �폜�I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	void DeleteFromArray(Type object)
	{
		// �o�^�̊m�F
		auto iterator = registration_map_.find(object);
		if (iterator == registration_map_.end()) return;

		// �z�񂩂�폜�y�сA�o�^�̉���
		array_[iterator->second] = nullptr;
		registration_map_.erase(object);
	}

	//----------------------------------------
	//! @brief �\�[�g�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Sort()
	{
		int temp_num = 0;

		for (unsigned i = 0; i < end_index_; i++)
		{
			if (array_[i] != nullptr) continue;

			temp_num++;

			for (unsigned k = (end_index_ - 1); k > i; k--)
			{
				if (array_[k] == nullptr) continue;

				// �I�u�W�F�N�g�����ւ���
				array_[i] = array_[k];
				array_[k] = nullptr;

				// �}�b�v�̍X�V
				registration_map_.find(array_[i])->second = i;
				break;
			}
		}

		// �G���h�|�C���^�̍X�V
		end_index_ -= temp_num;
	}

	//----------------------------------------
	//! @brief �z�񂩂�̍폜�ƃ\�[�g�֐�
	//! @details
	//! @param object �폜�I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	void DeleteFromArrayAndSort(Type object)
	{
		// �o�^�̊m�F
		auto iterator = registration_map_.find(object);
		if (iterator == registration_map_.end()) return;

		// �폜�悪�z��̖��[���ǂ���
		if (iterator->second == (end_index_ - 1))
		{
			// �z�񂩂�폜
			array_[iterator->second] = nullptr;
		}
		else
		{
			// �\�[�g
			for (unsigned i = (end_index_ - 1); i > iterator->second; i--)
			{
				if (array_[i] == nullptr) continue;

				// �I�u�W�F�N�g�����ւ���
				array_[iterator->second] = array_[i];
				array_[i] = nullptr;

				// �}�b�v�̍X�V
				registration_map_.find(array_[iterator->second])->second = iterator->second;

				break;
			}
		}

		// �}�b�v����폜
		registration_map_.erase(object);

		// �G���h�|�C���^�̍X�V
		end_index_--;
	}

	//----------------------------------------
	//! @brief �z���2�̃I�u�W�F�N�g����ёւ��֐�
	//! @details
	//! @param index0 �C���f�b�N�X0
	//! @param index0 �C���f�b�N�X1
	//! @retval void �Ȃ�
	//----------------------------------------
	void SortTheTwoObject(unsigned index0, unsigned index1)
	{
		// �}�b�v�̍X�V
		unsigned temp_index = registration_map_.find(array_[index0])->second;
		registration_map_.find(array_[index0])->second = registration_map_.find(array_[index1])->second;
		registration_map_.find(array_[index1])->second = temp_index;

		// �z��̕��ёւ�
		Type temp = array_[index0];
		array_[index0] = array_[index1];
		array_[index1] = temp;
	}

	//----------------------------------------
	//! @brief �o�^�����ő傩����֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval bool �o�^�����ő�Ȃ�true
	//----------------------------------------
	bool IsMax()
	{
		return ARRAY_NUM == (end_index_ + 1);
	}
};



#endif
