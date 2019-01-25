//================================================================================
//!	@file	 LinerOctree.h
//!	@brief	 ���`8����Class
//! @details template
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================
#ifndef	_LINER_OCTREE_H_
#define _LINER_OCTREE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <windows.h>
#include <vector>
#include <list>

#include "ObjectOfTree/ObjectOfTree.h"
#include "SpaceOfTree/SpaceOfTree.h"

#include <Vector3D.h>
#include <SafeRelease/SafeRelease.h>



//************************************************************														   
//! @brief   ���`8����Class
//!
//! @details ���`�z��ɂ��8���؂̊Ǘ�Class(template)
//************************************************************
template <class Type>
class LinerOctree
{
//====================
// �萔
//====================
public:
	static const unsigned MAX_LEVEL = 9;	//!< �ő僌�x��


//====================
// �ϐ�
//====================
private:
	unsigned power_of_eight_array_[MAX_LEVEL + 1] = {0};	//!< �W�ׂ̂��搔�l�z��
	SpaceOfTree<Type>** space_pointer_array_ = nullptr;		//!< �e��ԃ|�C���^�z��
	Vec3 octree_width_ = {1.0f, 1.0f, 1.0f};				//!< 8���؂̕�
	Vec3 octree_width_min_ = {0.0f, 0.0f, 0.0f};			//!< 8���؂̕��̍ŏ��l
	Vec3 octree_width_max_ = {1.0f, 1.0f, 1.0f};			//!< 8���؂̕��̍ő�l
	Vec3 octree_unit_length_ = {1.0f, 1.0f, 1.0f};			//!< 8���؂̒P�ʒ���
	DWORD all_space_num_ = 0;								//!< ��Ԑ�
	unsigned  lowest_level_ = 0;							//!< �ŉ��ʃ��x��(��Ԗ��[��Level��)


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param lowest_level     �ŉ��ʃ��x��(��Ԗ��[��Level��)
	//! @param octree_width_min 8���؂̕��̍ŏ��l
	//! @param octree_width_max 8���؂̕��̍ő�l
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init(unsigned lowest_level, Vec3 octree_width_min, Vec3 octree_width_max)
	{
		// �ŉ��ʃ��x���̊m�F
		if (lowest_level > MAX_LEVEL)
		{
			MessageBox(nullptr, "�����ȍŉ��ʃ��x���ł��B(LinerOctree.cpp)", "Error", MB_OK);
			return;
		}

		// �ŉ��ʃ��x���̑��
		lowest_level_ = lowest_level;

		// 8�ׂ̂��搔�l�̊i�[
		power_of_eight_array_[0] = 1;
		for (unsigned i = 1; i < MAX_LEVEL + 1; i++)
		{
			power_of_eight_array_[i] = power_of_eight_array_[i - 1] * 8;
		}

		// ��Ԑ��̎Z�o(���䋉���̘a�̌���)
		all_space_num_ = (power_of_eight_array_[lowest_level_ + 1] - 1) / 7;

		// �e��ԃ|�C���^�z��̍쐬�Ə�����
		space_pointer_array_ = new SpaceOfTree<Type>*[all_space_num_];
		ZeroMemory(space_pointer_array_,
				   sizeof(SpaceOfTree<Type>*) * all_space_num_);

		// 8���؂̕��Z�o
		octree_width_min_ = octree_width_min;
		octree_width_max_ = octree_width_max;
		octree_width_ = octree_width_max_ - octree_width_min_;
		octree_unit_length_ = octree_width_ / ((float)(1 << lowest_level_));	// �����1�ӂ̋�Ԑ�
	}

	//----------------------------------------
	//! @brief �I���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Uninit()
	{
		for (unsigned i = 0; i < all_space_num_; i++)
		{
			SafeRelease::PlusUninit(&space_pointer_array_[i]);
		}

		if (space_pointer_array_ == nullptr) return;

		delete[] space_pointer_array_;
	}

	//----------------------------------------
	//! @brief �Փ˃��X�g�X�V�֐�
	//! @details
	//! @param *collision_list �Փ˃��X�g
	//! @retval void �Ȃ�
	//----------------------------------------
	void UpdateCollisionList(std::vector<Type>* collision_list)
	{
		// ������
		collision_list->clear();

		// ���[�g��Ԃ����邩�ǂ���
		if (space_pointer_array_[0] == nullptr) return;

		// ���[�g��Ԃ��珈�����J�n
		std::list<Type> temp_stack;
		GetCollisionList(0, collision_list, &temp_stack);
	}

	//----------------------------------------
	//! @brief �ǉ��֐�
	//! @details
	//! @param object     �ǉ��������I�u�W�F�N�g
	//! @param object_min �ǉ��������I�u�W�F�N�g�̍ŏ��l
	//! @param object_max �ǉ��������I�u�W�F�N�g�̍ő�l
	//! @retval void �Ȃ�
	//----------------------------------------
	void Add(ObjectOfTree<Type>* object, const Vec3* object_min, const Vec3* object_max)
	{
		// �I�u�W�F�N�g�̏�����Ԃ̔z��C���f�b�N�X�̎擾
		DWORD array_index = GetArrayIndexOfBelonginSpace(object_min, object_max);
		if (array_index >= all_space_num_)
		{
			MessageBox(nullptr, "�z�񐔂𒴂��܂���(LinerOctree.h)", "Error", MB_OK);
		}

		// ��Ԃ����݂��Ȃ��ꍇ�͍쐬
		if (space_pointer_array_[array_index] == nullptr)
		{
			CreateSpace(array_index);
		}

		// �I�u�W�F�N�g��o�^
		space_pointer_array_[array_index]->AddObject(object);
	}


private:
	//----------------------------------------
	//! @brief 3bit�Ԋu�֕����֐�
	//! @details
	//! @param *num �������������l
	//! @retval void �Ȃ�
	//----------------------------------------
	void SeparateInto3BitIntervals(DWORD* num)
	{
		*num = (*num | *num << 8) & 0x0000f00f;	// 1Byte��4bit���Ƃɕ�����
		*num = (*num | *num << 4) & 0x000c30c3;	// �e4bit���Qbit���Ƃɕ�����
		*num = (*num | *num << 2) & 0x00249249;	// �e2bit��1bit���Ƃɕ�����(3bit�Ԋu)
	}

	//----------------------------------------
	//! @brief 3D���[�g����Ԕԍ��擾�֐�
	//! @details
	//! @param *position ���[�g���ԍ����擾���������W
	//! @retval DWORD �Z�o����3D���[�g����Ԕԍ�
	//----------------------------------------
	DWORD GetMortonNumber(const Vec3* position)
	{
		// �ŉ��ʃ��x����Ԃł̍��W�֕ϊ�
		DWORD temp_x = (DWORD)((position->x - octree_width_min_.x) / octree_unit_length_.x);
		DWORD temp_y = (DWORD)((position->y - octree_width_min_.y) / octree_unit_length_.y);
		DWORD temp_z = (DWORD)((position->z - octree_width_min_.z) / octree_unit_length_.z);

		// 3bit�Ԋu�֕���
		SeparateInto3BitIntervals(&temp_x);
		SeparateInto3BitIntervals(&temp_y);
		SeparateInto3BitIntervals(&temp_z);

		// 1bit�����炷
		return temp_x | (temp_y << 1) | (temp_z << 2);
	}

	//----------------------------------------
	//! @brief ������Ԃ̔z��C���f�b�N�X�擾�֐�
	//! @details
	//! @param *object_min ������Ԃ̔z��C���f�b�N�X���擾�������I�u�W�F�N�g�̍ŏ��l
	//! @param *object_max ������Ԃ̔z��C���f�b�N�X���擾�������I�u�W�F�N�g�̍ő�l
	//! @retval DWORD ������Ԃ̔z��ԍ�
	//----------------------------------------
	DWORD GetArrayIndexOfBelonginSpace(const Vec3* object_min, const Vec3* object_max)
	{
		// �ŏ��l�ƍő�l�̃��[�g���ԍ���XOR���Z�o
		DWORD converted_min = GetMortonNumber(object_min);
		DWORD converted_max = GetMortonNumber(object_max);
		DWORD temp = converted_min ^ converted_max;

		// �ŏ�ʂ̋�؂肩��ŏ��l�ƍő�l�̋��L��ԃ��x�����Z�o����
		unsigned shared_space_level = 0;
		for (unsigned i = 0; i < lowest_level_; i++)
		{
			// 3bit�����炵��(3D�Ȉ�)�������琔�l�����邩���`�F�b�N
			DWORD check = temp >> (i * 3) & 0x7;
			if (check != 0) shared_space_level = i + 1;
		}

		// ���L��ԃ��x�����珊����Ԕԍ����Z�o(���L��ԃ��x����3bit�V�t�g)
		DWORD shared_space_num = converted_max >> (shared_space_level * 3);

		// ������Ԕԍ�����z��C���f�b�N�X�ɕϊ�(���䋉���̘a�̌����̕������Z)
		shared_space_num += (power_of_eight_array_[lowest_level_ - shared_space_level] - 1) / 7;

		return shared_space_num;
	}

	//----------------------------------------
	//! @brief ��Ԃ̐����֐�
	//! @details
	//! @param array_index �z��C���f�b�N�X
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateSpace(DWORD array_index)
	{
		while (space_pointer_array_[array_index] == nullptr)
		{
			// ��ԍ쐬
			space_pointer_array_[array_index] = new SpaceOfTree<Type>();

			// �e��Ԃֈړ�
			array_index = (array_index - 1) >> 3;
			if (array_index >= all_space_num_) break;
		}
	}

	//----------------------------------------
	//! @brief �Փ˃��X�g�̍쐬�֐�
	//! @details
	//! @param space_index      ��Ԕz��C���f�b�N�X
	//! @param *collision_list  �Փ˃I�u�W�F�N�g���X�g
	//! @param *collision_stack �Փ˃I�u�W�F�N�g�X�^�b�N
	//! @retval void �Ȃ�
	//----------------------------------------
	void GetCollisionList(DWORD space_index, std::vector<Type>* collision_list,
						  std::list<Type>* collision_stack)
	{
		ObjectOfTree<Type>* temp01 = space_pointer_array_[space_index]->getFirstObject();
		while (temp01 != nullptr)
		{
			// ����ԓ��I�u�W�F�N�g���m�̏Փ˃��X�g�쐬
			ObjectOfTree<Type>* temp02 = temp01->getpNext();
			while (temp02 != nullptr)
			{
				// �Փ˃��X�g�쐬
				collision_list->push_back(temp01->getObject());
				collision_list->push_back(temp02->getObject());

				// ���̃I�u�W�F�N�g��
				temp02 = temp02->getpNext();
			}

			// �X�^�b�N����Ă���I�u�W�F�N�g�Ƃ̏Փ˃��X�g�쐬
			for (auto it = collision_stack->begin(); it != collision_stack->end(); it++)
			{
				collision_list->push_back(temp01->getObject());
				collision_list->push_back(*it);
			}

			// ���̃I�u�W�F�N�g��
			temp01 = temp01->getpNext();
		}

		// �q��Ԃֈړ�
		bool child_flag = false;		// �q��ԃt���O
		DWORD object_num = 0;
		DWORD next_space_index = 0;
		for (unsigned i = 0; i < 8; i++)
		{
			// ���̋�Ԃ����邩�ǂ���
			next_space_index = space_index * 8 + 1 + i;
			if (next_space_index >= all_space_num_) continue;
			if (space_pointer_array_[next_space_index] == nullptr) continue;

			// �e���v�b�V��
			if (!child_flag)
			{
				temp01 = space_pointer_array_[space_index]->getFirstObject();
				while (temp01 != nullptr)
				{
					collision_stack->push_back(temp01->getObject());
					object_num++;
					temp01 = temp01->getpNext();
				}
			}

			// �q��ԃt���OON
			child_flag = true;

			// �q��Ԃ̍ċA����
			GetCollisionList(next_space_index, collision_list, collision_stack);
		}

		// �X�^�b�N����I�u�W�F�N�g���O��
		if (!child_flag) return;

		for (unsigned i = 0; i < object_num; i++)
		{
			collision_stack->pop_back();
		}
	}
};



#endif
