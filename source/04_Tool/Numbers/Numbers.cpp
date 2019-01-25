//================================================================================
//
//    �����̐����N���X
//    Author : Araki Kai                                �쐬�� : 2018/06/19
//
//================================================================================


//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include "Numbers.h"
#include "Number\NumberFactory\NumberFactory.h"

#include "Renderer\RendererDirectX9\RendererDirectX9.h"
#include <GameObjectManager\GameObjectManager.h>



//======================================================================
//
// ��ÓI�����o�֐���`
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Numbers::Init()
{
	// ���N���X�̏�����
	GameObjectBase::Init(nullptr, nullptr, nullptr);

	number_factory_ = new NumberFactory();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �I�������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Numbers::Uninit()
{
	// ���N���X�̏I������
	GameObjectBase::Uninit();

	SafeRelease::Normal(&number_factory_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ Reset�����֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Numbers::Reset()
{
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �����Q�ݒ�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Numbers::SetNumbers(int numbers, int digits, bool is_zero, 
						 Vec2 position, Vec2 scale, XColor4 color)
{
	int temp_digits = digits;
	// ���l�߂��邩�ǂ���
	if (temp_digits <= 0)
	{
		// ���l��
		LeftJustified(numbers, &temp_digits);
	}
	else
	{
		// �������ς�����Ƃ��X�V
		NotLeftJustified(&temp_digits);
	}

	// �J���X�g����
	IsCountStop(numbers, temp_digits);
	
	// �e���̍X�V
	UpdateEachDigit(numbers, temp_digits, is_zero, position, scale, color);
}



//--------------------------------------------------------------------------------
//
// [ ���l�ߏ����֐� ]
//
//--------------------------------------------------------------------------------

void Numbers::LeftJustified(int numbers, int* digits)
{
	// ���݂̐��l�̉��
	ReleaseNumber();

	// �V���Ȍ����̎擾
	int temp_numbers = numbers;

	*digits = 1;

	for ( ; ; )
	{
		temp_numbers /= 10;

		if (temp_numbers == 0) break;

		(*digits)++;
	}

	for (int i = 0; i < *digits; i++)
	{
		numbers_.push_back(number_factory_->Create());
	}
}



//--------------------------------------------------------------------------------
//
// [ ���l�ߏ����֐� ]
//
//--------------------------------------------------------------------------------

void Numbers::NotLeftJustified(int* digits)
{
	// �����̕ύX
	if (*digits == (int)numbers_.size()) return;
	
	// ���݂̐��l�̉��
	ReleaseNumber();

	for (int i = 0; i < *digits; i++)
	{
		numbers_.push_back(number_factory_->Create());
	}
}



//--------------------------------------------------------------------------------
//
// [ �J���X�g�����֐� ]
//
//--------------------------------------------------------------------------------

void Numbers::IsCountStop(int numbers, int digits)
{
	int numbers_max = 1;

	for (int i = 0; i < digits; i++)
	{
		numbers_max *= 10;
	}
	
	numbers_max--;

	numbers = min(numbers_max, numbers);
}



//--------------------------------------------------------------------------------
//
// [ �e���̍X�V�֐� ]
//
//--------------------------------------------------------------------------------

void Numbers::UpdateEachDigit(int numbers, int digits, bool is_zero, 
									 Vec2 position, Vec2 scale, XColor4 color)
{
	// ���炵��
	float AmountOfShift = (numbers_.size() - 1) * (scale.x / 2);

	for (int i = (digits - 1); i >= 0; i--)
	{
		int temp_number = numbers % 10;
		numbers /= 10;

		numbers_[i]->SetNumber(temp_number);
		numbers_[i]->SetColor (color);
		*numbers_[i]->GetTransform()->GetPosition() = Vec3(position.x + AmountOfShift, position.y, 0.0f);
		*numbers_[i]->GetTransform()->GetScale() = Vec3(scale.x, scale.y, 1.0f);
		numbers_[i]->GetTransform()->UpdateWorldMatrixSRT();

		AmountOfShift -= (scale.x / 2);

		// �[���l�߂��Ȃ��Ȃ烋�[�v�I��
		if ( !is_zero && !numbers ) return;
	}
}



//--------------------------------------------------------------------------------
//
// [ ��������֐� ]
//
//--------------------------------------------------------------------------------

void Numbers::ReleaseNumber()
{
	// ���������
	for (auto& contents : numbers_)
	{
		GameObjectManager::ReleaseGameObjectBaseFromArray(contents);
	}

	// �����z������Z�b�g
	numbers_.clear();
}