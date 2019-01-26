//================================================================================
//
//    �L���|�C���^�[�z��N���X(�N���X�e���v���[�g)
//    Author : Araki Kai                                �쐬�� : 2018/04/18
//
//================================================================================

#ifndef	_LIMITED_POINTER_ARRAY_H_
#define _LIMITED_POINTER_ARRAY_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include <unordered_map>
#include <assert.h>

#include <SafeRelease/SafeRelease.h>



//======================================================================
//
// �N���X��`
//
//======================================================================

template<class Type, unsigned ARRAY_NUM = 100000>
class LimitedPointerArray
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:
	// �f�t�H���g�R���X�g���N�^
	LimitedPointerArray()
		: end_pointer_(0)
	{
		// �z��̏�����
		for (unsigned i = 0; i < ARRAY_NUM; i++)
		{
			array_[i] = nullptr;
		}

		// �}�b�v�̏�����
		registration_map_.clear();
	}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:

	// �z��ɒǉ�
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
			if (end_pointer_ < (i + 1))
			{
				end_pointer_ = (i + 1);
			}
			return;
		}
	}



	// �z��̏㏑��
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



	// �z��̏㏑���Ɖ��
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



	// �z�񃊃Z�b�g
	void ResetArray()
	{
		// �z�񂩂�̍폜
		for (unsigned i = 0; i < end_pointer_; i++)
		{
			array_[i] = nullptr;
		}

		// �}�b�v�̃��Z�b�g
		registration_map_.clear();

		// �G���h�|�C���^�����Z�b�g
		end_pointer_ = 0;
	}

	// �o�^��̉���Ɣz��̃��Z�b�g
	void ReleaseObjectAndResetArray()
	{
		// �o�^��̉���Ɣz�񂩂�̍폜
		for (unsigned i = 0; i < end_pointer_; i++)
		{
			SafeRelease::Normal(&array_[i]);
			array_[i] = nullptr;
		}

		// �}�b�v�̃��Z�b�g
		registration_map_.clear();

		// �G���h�|�C���^�����Z�b�g
		end_pointer_ = 0;
	}

	// �z�񂩂�폜
	void DeleteFromArray(Type object)
	{
		// �o�^�̊m�F
		auto iterator = registration_map_.find(object);
		if (iterator == registration_map_.end()) return;

		// �z�񂩂�폜�y�сA�o�^�̉���
		array_[iterator->second] = nullptr;
		registration_map_.erase(object);
	}

	// �z��̃\�[�g
	void SortArray()
	{
		int temp_num = 0;

		for (unsigned i = 0; i < end_pointer_; i++)
		{
			if (array_[i] != nullptr) continue;

			temp_num++;

			for (unsigned k = (end_pointer_ - 1); k > i; k--)
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
		end_pointer_ -= temp_num;
	}

	// �z�񂩂�̍폜�ƃ\�[�g
	void DeleteFromArrayAndSortArray(Type object)
	{
		// �o�^�̊m�F
		auto iterator = registration_map_.find(object);
		if (iterator == registration_map_.end()) return;

		// �폜�悪�z��̖��[���ǂ���
		if (iterator->second == (end_pointer_ - 1))
		{
			// �z�񂩂�폜
			array_[iterator->second] = nullptr;
		}
		else
		{
			// �\�[�g
			for (unsigned i = (end_pointer_ - 1); i > iterator->second; i--)
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
		end_pointer_--;
	}

	// �z���2�̃I�u�W�F�N�g����ёւ�
	void SortTheTwoObject(unsigned index0, unsigned index1)
	{
		// �C���f�b�N�X�����������Ƃ��Ɏ~�߂�
		assert(!((index0 < 0) || (index0 > end_pointer_ - 1)) && "�s���ȃC���f�b�N�X�ł�(LimitedPointerArray.h)");
		assert(!((index1 < 0) || (index1 > end_pointer_ - 1)) && "�s���ȃC���f�b�N�X�ł�(LimitedPointerArray.h)");

		// �I�u�W�F�N�g��nullptr�̎�
		assert(array_[index0] != nullptr && "�z��nullptr�ł�(LimitedPointerArray.h)");
		assert(array_[index1] != nullptr && "�z��nullptr�ł�(LimitedPointerArray.h)");

		// �}�b�v�̍X�V
		unsigned temp_index = registration_map_.find(array_[index0])->second;
		registration_map_.find(array_[index0])->second = registration_map_.find(array_[index1])->second;
		registration_map_.find(array_[index1])->second = temp_index;

		// �z��̕��ёւ�
		Type temp = array_[index0];
		array_[index0] = array_[index1];
		array_[index1] = temp;
	}

	// �z��̃Q�b�^
	Type GetArrayObject(unsigned index)
	{
		// �C���f�b�N�X�����������Ƃ��Ɏ~�߂�
		assert(!((index < 0) || (index > ARRAY_NUM - 1)) && "�s���ȃC���f�b�N�X�ł�(LimitedPointerArray.h)");
		return array_[index];
	}

	// �G���h�|�C���^�̃Q�b�^
	unsigned GetEndPointer()
	{
		return end_pointer_;
	}

	// �z�񐔂̃Q�b�^
	unsigned GetArrayNum()
	{
		return ARRAY_NUM;
	}

	// �o�^�C���f�b�N�X�ԍ��̃Q�b�^
	unsigned GetIndexNum(Type object)
	{
		// �o�^�̊m�F
		auto iterator = registration_map_.find(object);

		// �o�^����Ă��Ȃ��I�u�W�F�N�g��������~�߂�
		assert(iterator != registration_map_.end() && "�o�^����Ă��Ȃ��I�u�W�F�N�g(LimitedPointerArray.h)");

		// �C���f�b�N�X�ԍ���Ԃ�
		if (iterator != registration_map_.end())
		{
			return iterator->second;
		}
	}

	// �o�^�����ő傩�ǂ���
	bool IsMax()
	{
		return ARRAY_NUM == (end_pointer_ + 1);
	}



//------------------------------------------------------------
private:
	// �����o�ϐ�
	Type array_[ARRAY_NUM];
	unsigned end_pointer_;
	std::unordered_map<Type, unsigned> registration_map_;
};



#endif
