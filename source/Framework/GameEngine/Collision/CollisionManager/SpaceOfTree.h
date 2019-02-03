//================================================================================
//!	@file	 SpaceOfTree.h
//!	@brief	 ���؋��Class
//! @details template
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================
#ifndef	_SPACE_OF_TREE_H_
#define _SPACE_OF_TREE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "ObjectOfTree.h"



//************************************************************														   
//! @brief   ���؋��Class(template)
//!
//! @details ���؂̋��Class(template)
//************************************************************
template <class Type>
class SpaceOfTree
{
//====================
// �ϐ�
//====================
private:
	ObjectOfTree<Type>* first_object_ = nullptr;	//!< �ŏ��̃I�u�W�F�N�g


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �ŏ��̃I�u�W�F�N�g�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval ObjectOfTree<Type>* �ŏ��̃I�u�W�F�N�g
	//----------------------------------------
	ObjectOfTree<Type>* getFirstObject() 
	{ 
		return first_object_; 
	}

	//----------------------------------------
	//! @brief �ŏ��̃I�u�W�F�N�g�ݒ�֐�
	//! @details
	//! @param *value �ŏ��̃I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	void setFirstObject(ObjectOfTree<Type>* value) 
	{ 
		first_object_ = value;
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
		if (first_object_ == nullptr) return;

		ResetLink(&first_object_);
	}

	//----------------------------------------
	//! @brief �����N�̃��Z�b�g�֐�
	//! @details
	//! @param **object �����N�����Z�b�g�������I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	void ResetLink(ObjectOfTree<Type>** object)
	{
		if ((*object)->getpNext() != nullptr)
		{
			ResetLink((*object)->getp2Next());
		}

		*object = nullptr;
	}

	//----------------------------------------
	//! @brief �I�u�W�F�N�g�̒ǉ��֐�
	//! @details
	//! @param *object �ǉ��������I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	void AddObject(ObjectOfTree<Type>* object)
	{
		// NULL&2�d�o�^�`�F�b�N
		if (object == nullptr) return;
		if (object->getpBelongingSpace() == this) return;

		// �ŏ��̃I�u�W�F�N�g�|�C���^���o�^����Ă��邩�ǂ���
		if (first_object_ == nullptr)
		{
			// �ŏ��̃I�u�W�F�N�g�|�C���^�ɓo�^
			first_object_ = object;
		}
		else
		{
			// �ŏ��̃I�u�W�F�N�g�|�C���^���X�V
			object->setNext(first_object_);
			first_object_->setPrevious(object);
			first_object_ = object;
		}

		// ��Ԃ�o�^
		object->setBelongingSpace(this);
	}

	//----------------------------------------
	//! @brief �����I�u�W�F�N�g�̃`�F�b�N�֐�
	//! @details
	//! @param *object �`�F�b�N�����������I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	void CheckDeleteObject(ObjectOfTree<Type>* object)
	{
		if (first_object_ != object) return;
		if (first_object_ == nullptr) return;

		// ���̃|�C���^�֑}���ւ���
		first_object_ = first_object_->getpNext();
	}
};



#endif
