//================================================================================
//!	@file	 Interpolation.h
//!	@brief	 ���Class
//! @details Template
//!	@author  Kai Araki									@date 2018/02/04
//================================================================================
#ifndef	_INTERPOLATION_H_
#define _INTERPOLATION_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "SafeRelease.h"



//************************************************************														   
//! @brief   ��ԗv�fClass(Template)
//!
//! @details ��ԗp��Class(Template)
//************************************************************
template<class Value, class Distance = double, class AddInfo = double>
class InterpolationElement
{
//====================
// �ϐ�
//====================
private:
	Value value_;			//!< �L�[�l
	Distance distance_;		//!< ��ԋ���(�O�̗v�f����̑��΋���)
	AddInfo add_info_;		//!< �t�����


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �L�[�l�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Value* �L�[�l
	//----------------------------------------
	Value* getpValue()
	{
		return &value_;
	}

	//----------------------------------------
	//! @brief ��ԋ����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Distance* ��ԋ���
	//----------------------------------------
	Distance* getpDistance()
	{
		return &distance_;
	}

	//----------------------------------------
	//! @brief �t�����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval AddInfo* �t�����
	//----------------------------------------
	AddInfo* getpAddInfo()
	{
		return &add_info_;
	}


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �R���X�g���N�^
	//! @details
	//! @param &value    �L�[�l
	//! @param &distance ��ԋ���
	//! @param &add_info �t�����
	//----------------------------------------
	InterpolationElement(Value& value, Distance& distance, AddInfo& add_info)
		: value_(value),
		distance_(distance),
		add_info_(add_info)
	{
	}
};



//************************************************************														   
//! @brief   ��ԃX�g���e�WBaseClass(Template)
//!
//! @details ��ԃX�g���e�W��BaseClass(Template)
//************************************************************
template<class Value, class Distance = double, class AddInfo = double>
class InterpolationStrategyBase
{
//====================
// �^��`
//====================
public:
	typedef typename InterpolationElement<Value, Distance, AddInfo> Element;


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �K�v�ȗv�f�̐��擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval size_t �K�v�ȗv�f�̐�
	//----------------------------------------
	virtual size_t getNeedElementNum() = 0;

	//----------------------------------------
	//! @brief �v�f��o�^����z��擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Element** �v�f��o�^����z��
	//----------------------------------------
	virtual Element** getp2Array() = 0;


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief ��Ԓl�Z�o�֐�
	//! @details
	//! @param *value    �L�[�l
	//! @param &distance ��ԋ���
	//! @retval bool ��Ԑ����̗L��
	//----------------------------------------
	virtual bool CalculationOfInterpolation(Value* value,
											Distance& distance) = 0;
};



//************************************************************														   
//! @brief   ���`�⊮�X�g���e�WClass(Template)
//!
//! @details ���`�⊮�X�g���e�W��Class(Template)
//************************************************************
template<class Value, class Distance = double, class AddInfo = double>
class LinerInterpolationStrategy : public InterpolationStrategyBase<Value, Distance, AddInfo>
{
//====================
// �^��`
//====================
public:
	typedef typename InterpolationElement<Value, Distance, AddInfo> Element;

//====================
// �ϐ�
//====================
private:
	Element* element_[2] = {nullptr};		// �v�f��

//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �K�v�ȗv�f�̐��擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval size_t �K�v�ȗv�f�̐�
	//----------------------------------------
	size_t getNeedElementNum()
	{
		return 2;
	}

	//----------------------------------------
	//! @brief �v�f��o�^����z��擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Element** �v�f��o�^����z��
	//----------------------------------------
	Element** getp2Array()
	{
		return (Element**)&element_;
	}


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief ��Ԓl�Z�o�֐�
	//! @details
	//! @param *value    �L�[�l
	//! @param &distance ��ԋ���
	//! @retval bool ��Ԑ����̗L��
	//----------------------------------------
	bool CalculationOfInterpolation(Value* value,
									Distance& distance)
	{
		// ���`��Ԍv�Z
		*value = (Value)((1 - distance) * *element_[0]->getpValue()
			+ *element_[1]->getpValue() * distance);
		return true;
	}
};



//************************************************************														   
//! @brief   ���Class(Template)
//!
//! @details ��ԗv�f�̃R���e�iClass(Template)
//! @details ���̃R���e�i�ň�������Value�ɂ́A
//! @details �eInterpolationStrategy�Ŏg�p����A
//! @details ���Z�q�̃I�[�o�[���C�h���K�v�ł��B
//************************************************************
template<class Value, class Distance = double, class AddInfo = double, class Strategy = LinerInterpolationStrategy<Value, Distance, AddInfo>>
class Interpolation
{
//====================
// �^��`
//====================
public:
	typedef typename InterpolationElement<Value, Distance, AddInfo> Element;


//====================
// �萔
//====================
private:
#define END_POINTER ((Element*)(-1))


//====================
// �N���X
//====================
public:
	//****************************************											   
	//! @brief   ��ԃR���e�i�C�e���[�^Class
	//!
	//! @details ��ԃR���e�i�̃C�e���[�^Class
	//****************************************
	class Iterator_
	{
	//====================
	// �ϐ�
	//====================
	private:
		Element** first_pointer_;			//!< �C�e���[�^�̍ŏ��̃|�C���^
		Interpolation* interpolation_;		//!< ��ԃN���X
		Value current_value_;				//!< ���݂̕�Ԓl
		Distance distance_unit_;			//!< �P�ʋ���
		Distance current_distance_;			//!< ���݂̋���
		Distance cumulative_distance_;		//!< �ݐς̋���
		size_t offset_index_;				//!< �I�t�Z�b�g�C���f�b�N�X�l
		size_t max_index_;					//!< �ő�C���f�b�N�X�l
		size_t target_index_;				//!< �ڕW�v�f�̃C���f�b�N�X
		Element* target_element_;			//!< �ڕW�̗v�f
		bool is_finished_;					//!< �I�[�t���O
		Strategy strategy_;					//!< ��Ԍv�Z


	//====================
	// �v���p�e�B
	//====================
	public:
		//----------------------------------------
		//! @brief ���݂̕�Ԓl�擾�֐�
		//! @details
		//! @param void �Ȃ�
		//! @retval Value& ���݂̕�Ԓl
		//----------------------------------------
		Value& getValue()
		{
			return current_value_;
		}

		//----------------------------------------
		//! @brief �P�ʋ����ݒ�֐�
		//! @details
		//! @param value �P�ʋ���
		//! @retval void �Ȃ�
		//----------------------------------------
		void setDistanceUnit(Distance& value)
		{
			distance_unit_ = value;
		}

		//----------------------------------------
		//! @brief �ݐς̋����擾�֐�
		//! @details
		//! @param void �Ȃ�
		//! @retval Distance �ݐς̋���
		//----------------------------------------
		Distance getCumulativeDistance()
		{
			return cumulative_distance_;
		}

		//----------------------------------------
		//! @brief �I�[�t���O�擾�֐�
		//! @details
		//! @param void �Ȃ�
		//! @retval bool �I�[�t���O
		//----------------------------------------
		bool getIsFinished()
		{
			return is_finished_;
		}

	//====================
	// ���Z�q
	//====================
	public:
		//----------------------------------------
		//! @brief *�Ԑڎw�艉�Z�q�֐�
		//! @details
		//! @param void �Ȃ�
		//! @retval Value& ���݂̕�Ԓl
		//----------------------------------------
		Value& operator *()
		{
			return current_value_;
		}

		//----------------------------------------
		//! @brief ++�����P�����Z�q�֐�
		//! @details
		//! @param dummy �_�~�[
		//! @retval void �Ȃ�
		//----------------------------------------
		void operator ++(int dummy)
		{
			dummy = dummy;
			next(distance_unit_);	// �P�ʋ������X�V
		}

		//----------------------------------------
		//! @brief ==��r���Z�q�֐�
		//! @details
		//! @param iterator �C�e���[�^
		//! @retval void �Ȃ�
		//----------------------------------------
		bool operator ==(Iterator_ iterator)
		{
			if (iterator.target_element_ == target_element_) return true;
			return false;
		}

		//----------------------------------------
		//! @brief !=��r���Z�q�֐�
		//! @details
		//! @param iterator �C�e���[�^
		//! @retval void �Ȃ�
		//----------------------------------------
		bool operator !=(Iterator_ iterator)
		{
			if (iterator.target_element_ != target_element_) return true;
			return false;
		}


	//====================
	// �֐�
	//====================
	public:
		//----------------------------------------
		//! @brief �R���X�g���N�^
		//! @details
		//! @param **element_array �v�f�z��
		//! @param *interpolation  ��ԃN���X
		//----------------------------------------
		Iterator_(Element** element_array = nullptr, 
				  Interpolation* interpolation = nullptr)
			:first_pointer_(element_array),
			interpolation_(interpolation),
			distance_unit_(1),
			current_distance_(0),
			cumulative_distance_(0),
			offset_index_(0),
			max_index_(0),
			target_index_(0),
			target_element_(END_POINTER),
			is_finished_(true)
		{
			if (element_array == nullptr) return;

			// �擪����̃I�t�Z�b�g�C���f�b�N�X
			offset_index_ = ((size_t)element_array - (size_t)interpolation
							 ->getp2FirstPointer()) / sizeof(Element*);

			// �ő�C���f�b�N�X��
			max_index_ = interpolation->size() - offset_index_;

			// ���݂̕�Ԓl�̏����l
			current_value_ = *element_array[0]->getpValue();

			// �v�f���Q�ȏ�Ȃ��ԉ\
			if (max_index_ < 2) return;

			// �ڕW�v�f��ݒ�
			target_index_ = 1;
			target_element_ = first_pointer_[target_index_];

			// �I�[�t���OOFF
			is_finished_ = false;
		}

	private:
		//----------------------------------------
		//! @brief �C�e���[�^�X�V�֐�
		//! @details
		//! @param &distance ��ԋ���
		//! @retval Iterator_ �X�V��̃C�e���[�^
		//----------------------------------------
		Iterator_ next(Distance& distance)
		{
			// ���݂̋�Ԃ̉����ɐi�񂾂����Z�o
			Distance ratio = CalculationDistance(distance);

			// ��Ԍv�Z�ɕK�v�ȗv�f�����擾
			size_t need_element_num = strategy_.getNeedElementNum();

			// ��Ԍv�Z�p�z��̎擾
			Element** temp_element_array = strategy_.getp2Array();

			// ��Ԍv�Z�p�z��ɗv�f����
			if (!SubstitutionElement(need_element_num, temp_element_array))
			{
				// �I�[�t���O��ON�Ȃ�I�[�C�e���[�^��Ԃ�
				if (is_finished_ || (*first_pointer_ == END_POINTER))
				{
					// �ڕW�v�f���I�[�|�C���^�ɕύX
					target_element_ = END_POINTER;
					return *this;
				}
				else
				{
					// �Ō�̗v�f�ɍ��킹��
					is_finished_ = true;
					target_element_ = first_pointer_[interpolation_->size() - 1];
					current_value_ = *target_element_->getpValue();
					return *this;
				}
			}

			// ���̒l�ɍX�V(��Ԍv�Z)
			strategy_.CalculationOfInterpolation(&current_value_, ratio);
			return *this;
		}

		//----------------------------------------
		//! @brief ��ԋ����Z�o�֐�
		//! @details
		//! @param &distance ��ԋ���
		//! @retval Distance ��ԋ���
		//----------------------------------------
		Distance CalculationDistance(Distance& distance)
		{
			// �I�[�|�C���^�y�їv�f�����P�̎�
			if (*first_pointer_ == END_POINTER) return 1;
			if (interpolation_->size() <= 1) return 1;

			// ���������Z
			current_distance_ += distance;
			cumulative_distance_ += distance;	// �ݐςɂ��ǉ�

			// ���݂̖ڕW�v�f���m��
			for (; ;)
			{
				// �ڕW�v�f�����݂��邩�m�F
				if (target_index_ >= max_index_) return 1;

				// ���݂̋������ڕW�v�f��ԕ��𒴂��Ă��Ȃ����m�F
				if (current_distance_
					>= *first_pointer_[offset_index_ + target_index_]->getpDistance())
				{
					// ��яo���������Z�o���ڕW�v�f�C���f�b�N�X�����ɕύX����
					current_distance_ -= *first_pointer_[offset_index_ + target_index_]->getpDistance();
					target_index_++;
					continue;
				}
				break;
			}
			target_element_ = first_pointer_[offset_index_ + target_index_];

			// �ڕW�v�f�ɑ΂����ԋ����̎Z�o(0~1)
			return current_distance_ / *target_element_->getpDistance();
		}

		//----------------------------------------
		//! @brief ��Ԍv�Z�p�z��ɗv�f�����֐�
		//! @details
		//! @param need_element_num ��ԂɕK�v�ȗv�f��
		//! @param element_array    �v�f��������z��
		//! @retval bool �v�f�i�[�̐����̗L��
		//----------------------------------------
		bool SubstitutionElement(size_t need_element_num, Element** element_array)
		{
			// �ڕW�v�f���1�O�̗v�f���N�_�Ƃ��Ō�̗v�f�C���f�b�N�X���Z�o
			size_t last_element_num = (target_index_ - 1) + need_element_num;
			if (last_element_num > max_index_) return false;

			// �z��ɑ���R�s�[
			memcpy(element_array, first_pointer_ + target_index_ - 1, 
				   need_element_num * sizeof(Element*));
			return true;
		}
	};


//====================
// �^��`
//====================
public:
	typedef typename Interpolation<Value, Distance>::Iterator_ Iterator;


//====================
// �ϐ�
//====================
private:
	size_t size_;				//!< �z��
	Element** element_;			//!< �v�f�z��
	Element** end_pointer_;		//!< �I�[�|�C���^


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �ŏ��̃|�C���^�擾�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D* �O�x�N�g��
	//----------------------------------------
	Element** getp2FirstPointer()
	{
		return element_;
	}


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �R���X�g���N�^
	//! @details
	//! @param void �Ȃ�
	//----------------------------------------
	Interpolation()
	{
		size_ = 0;
		element_ = (Element**)malloc(sizeof(Element*));
		*element_ = END_POINTER;
		end_pointer_ = element_;
	}

	//----------------------------------------
	//! @brief �f�X�g���N�^
	//! @details
	//! @param void �Ȃ�
	//----------------------------------------
	~Interpolation()
	{
		clear();
		free(element_);
	}

	//----------------------------------------
	//! @brief �ǉ��֐�
	//! @details
	//! @param &value    �L�[�l
	//! @param &distance ��ԋ���
	//! @param add_info �t�����
	//! @retval void �Ȃ�
	//----------------------------------------
	void push_back(Value& value, Distance& distance, AddInfo add_info = 1.0)
	{
		// �v�f����
		Element* temp_element = new Element(value, distance, add_info);
		AddArrayMemory(1);
		Rewrite(temp_element);

	}

	//----------------------------------------
	//! @brief �N���A�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void clear()
	{
		// ���
		for (size_t i = 0; i < size_; i++)
		{
			delete element_[i];
		}
		size_ = 0;
		element_ = (Element**)realloc(element_, sizeof(Element*));
		*element_ = END_POINTER;
		end_pointer_ = element_;
	}

	//----------------------------------------
	//! @brief �n�܂�C�e���[�^�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Iterator �n�܂�C�e���[�^
	//----------------------------------------
	Iterator begin()
	{
		// �v�f����
		return Iterator(element_, this);
	}

	//----------------------------------------
	//! @brief �I�[�C�e���[�^�[�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Iterator �I�[�C�e���[�^
	//----------------------------------------
	Iterator end()
	{
		// �v�f����
		return Iterator(nullptr, this);
	}

	//----------------------------------------
	//! @brief �T�C�Y�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval size_t �T�C�Y
	//----------------------------------------
	size_t size()
	{
		return size_;
	}

private:
	//----------------------------------------
	//! @brief �z�񃁃����[�ǉ��֐�
	//! @details
	//! @param add_num �ǉ��� 
	//! @retval void �Ȃ�
	//----------------------------------------
	void AddArrayMemory(size_t add_num)
	{
		if (add_num <= 0) return;

		// �z�񃊃T�C�Y
		element_ = (Element**)realloc(element_, sizeof(Element*) * (size_ + add_num));

		// ���T�C�Y��������
		for (size_t i = 0; i < add_num; i++)
		{
			element_[size_ + i] = END_POINTER;
		}

		// �T�C�Y���y�яI�[�|�C���^�X�V
		size_ += add_num;
		end_pointer_ = element_ + size_ - 1;
	}

	//----------------------------------------
	//! @brief �z��㏑���֐�
	//! @details
	//! @param new_element �V�K�z��
	//! @retval void �Ȃ�
	//----------------------------------------
	void Rewrite(Element* new_element)
	{
		// �㏑�������̃|�C���^������
		if (*end_pointer_ != END_POINTER)
		{
			delete *end_pointer_;
		}

		*end_pointer_ = new_element;
	}
};



#endif