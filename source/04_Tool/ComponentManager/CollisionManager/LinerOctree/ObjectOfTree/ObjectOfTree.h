//================================================================================
//!	@file	 ObjectOfTree.h
//!	@brief	 ���؃I�u�W�F�N�gClass
//! @details template
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================
#ifndef	_OBJECT_OF_TREE_H_
#define _OBJECT_OF_TREE_H_



//****************************************
// �N���X�錾
//****************************************
template<class Type>
class SpaceOfTree;



//************************************************************														   
//! @brief   ���؃I�u�W�F�N�gClass
//!
//! @details ���؂̃I�u�W�F�N�gClass(template)
//************************************************************
template <class Type>
class ObjectOfTree
{
//====================
// �ϐ�
//====================
private:
	SpaceOfTree<Type>* belonging_space_ = nullptr;	//!< �������
	Type object_ = nullptr;							//!< �I�u�W�F�N�g
	ObjectOfTree<Type>* previous_ = nullptr;		//!< �O���؃I�u�W�F�N�g
	ObjectOfTree<Type>* next_ = nullptr;			//!< �����؃I�u�W�F�N�g


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief ������Ԏ擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval SpaceOfTree<Type>* �������
	//----------------------------------------
	SpaceOfTree<Type>* getpBelongingSpace() 
	{
		return belonging_space_; 
	}
	
	//----------------------------------------
	//! @brief ������Ԑݒ�֐�
	//! @details
	//! @param *value �������
	//! @retval void �Ȃ�
	//----------------------------------------
	void setBelongingSpace(SpaceOfTree<Type>* value) 
	{
		belonging_space_ = value; 
	}
	
	//----------------------------------------
	//! @brief �I�u�W�F�N�g�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Type �I�u�W�F�N�g
	//----------------------------------------
	Type getObject() 
	{
		return object_; 
	}
	
	//----------------------------------------
	//! @brief �I�u�W�F�N�g�ݒ�֐�
	//! @details
	//! @param value �I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	void setObject(Type value)
	{ 
		object_ = value; 
	}
	
	//----------------------------------------
	//! @brief �O���؃I�u�W�F�N�g�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval SpaceOfTree<Type>* �O���؃I�u�W�F�N�g
	//----------------------------------------
	ObjectOfTree<Type>* getpPrevious() 
	{
		return previous_; 
	}
	
	//----------------------------------------
	//! @brief �O���؃I�u�W�F�N�g�ݒ�֐�
	//! @details
	//! @param *value �O���؃I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	void setPrevious(ObjectOfTree<Type>* value) 
	{ 
		previous_ = value; 
	}

	//----------------------------------------
	//! @brief �㕪�؃I�u�W�F�N�g�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval SpaceOfTree<Type>* �㕪�؃I�u�W�F�N�g
	//----------------------------------------
	ObjectOfTree<Type>* getpNext() 
	{ 
		return next_; 
	}
	
	//----------------------------------------
	//! @brief �㕪�؃I�u�W�F�N�g�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval SpaceOfTree<Type>** �㕪�؃I�u�W�F�N�g
	//----------------------------------------
	ObjectOfTree<Type>** getp2Next() 
	{
		return &next_; 
	}
	
	//----------------------------------------
	//! @brief �㕪�؃I�u�W�F�N�g�ݒ�֐�
	//! @details
	//! @param *value �㕪�؃I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	void setNext(ObjectOfTree<Type>* value)
	{
		next_ = value; 
	}


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief ���X�g�����������֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void DeleteFromList()
	{
		if (belonging_space_ == nullptr) return;

		// �������Ă����Ԃɏ�����ʒm
		belonging_space_->CheckDeleteObject(this);

		// �O��̃I�u�W�F�N�g�����т���
		if (previous_ != nullptr)
		{
			previous_->setNext(next_);
		}
		if (next_ != nullptr)
		{
			next_->setPrevious(previous_);
		}
		previous_ = nullptr;
		next_ = nullptr;
		belonging_space_ = nullptr;
	}
};



#endif
