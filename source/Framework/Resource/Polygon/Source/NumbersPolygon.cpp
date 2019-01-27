//================================================================================
//!	@file	 NumbersPolygon.cpp
//!	@brief	 �����Q�|���S��Class
//! @details 
//!	@author  Kai Araki									@date 2018/06/19
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../NumbersPolygon.h"
#include "../PlanePolygon.h"
#include "../../Texture/TextureObject.h"

#include <GameEngine/Renderer/Renderer.h>
#include <Tool/SafeRelease.h>



//****************************************
// �v���p�e�B��`
//****************************************
void NumbersPolygon::NumberPolygon::setNumber(int value)
{
	if (value < 0 || value > 9) return;
	if (number_ == value) return;

	// �����̕ύX��UV�l�̕ύX
	number_ = value;
	plane_polygon_->setUV(texture_, number_);
}



void NumbersPolygon::NumberPolygon::setColor(XColor4 value)
{
	plane_polygon_->setColor(value);
}



void NumbersPolygon::NumberPolygon::setTextureObject(TextureObject* value)
{
	texture_ = value;
}



Transform* NumbersPolygon::NumberPolygon::getpTransform()
{
	return &transform_;
}



void NumbersPolygon::setNumber(int value)
{
	int temp_digits_num = digits_num_;

	// ���l��
	LeftJustified(value, &temp_digits_num);

	// �J���X�g����
	IsCountStop(&value, temp_digits_num);

	// �e���̍X�V
	UpdateEachDigit(value, temp_digits_num);
}


void NumbersPolygon::setDigitsNum(int value)
{
	digits_num_ = value;
}



void NumbersPolygon::setIsZero(bool value)
{
	is_zero_ = value;
}



void NumbersPolygon::setPosition(Vec2 value)
{
	position_ = value;
}



void NumbersPolygon::setScale(Vec2 value)
{
	scale_ = value;
}



void NumbersPolygon::setColor(XColor4 value)
{
	color_ = value;
}



void NumbersPolygon::setTextureObject(TextureObject* value)
{
	texture_ = value;
	texture_->setDivisionNum(10, 10, 1);
}



unsigned NumbersPolygon::getObjectNum()
{
	return number_.size();
}



MATRIX* NumbersPolygon::getpMatrix(int mesh_index)
{
	return number_[mesh_index]->getpTransform()->getpWorldMatrix();
}



//****************************************
// �֐���`
//****************************************
void NumbersPolygon::NumberPolygon::Init()
{
	// �v���[���|���S���̍쐬
	plane_polygon_ = new PlanePolygon;
	plane_polygon_->Init();

	// ���������Z�b�g
	number_ = -1;		// �����̐����ύX�p
	setNumber(0);
}



void NumbersPolygon::NumberPolygon::Uninit()
{
	SafeRelease::PlusUninit(&plane_polygon_);
}



void NumbersPolygon::NumberPolygon::Draw()
{
	plane_polygon_->Draw();
}



void NumbersPolygon::Init()
{
}



void NumbersPolygon::Uninit()
{
}



void NumbersPolygon::Draw(int mesh_index)
{
	number_[mesh_index]->Draw();
}



void NumbersPolygon::LeftJustified(int number, int* digits_num)
{
	if (*digits_num <= 0)
	{
		// �V���Ȍ����̎擾
		*digits_num = 1;
		for (; ; )
		{
			number /= 10;
			if (number == 0) break;
			(*digits_num)++;
		}
	}
	else
	{
		// �����̕ύX
		if (*digits_num == (int)number_.size()) return;
	}

	// �����|���S���쐬
	CreateNumberPolygon(number, digits_num);
}



void NumbersPolygon::CreateNumberPolygon(int number, int* digits_num)
{
	// ���݂̐��l�̉��
	ReleaseNumberPolygon();

	// �����|���S���쐬
	for (int i = 0; i < *digits_num; i++)
	{
		NumbersPolygon::NumberPolygon* number_polygon = new NumbersPolygon::NumberPolygon();
		number_polygon->setTextureObject(texture_);
		number_polygon->Init();
		number_.push_back(number_polygon);
	}
}



void NumbersPolygon::IsCountStop(int* number, int digits_num)
{
	int numbers_max = 1;
	for (int i = 0; i < digits_num; i++)
	{
		numbers_max *= 10;
	}

	numbers_max--;
	*number = min(numbers_max, *number);
}



void NumbersPolygon::UpdateEachDigit(int number, int digits_num)
{
	// ���炵��
	float AmountOfShift = (number_.size() - 1) * (scale_.x / 2);

	for (int i = (digits_num - 1); i >= 0; i--)
	{
		int temp_number = number % 10;
		number /= 10;

		number_[i]->setNumber(temp_number);
		number_[i]->setColor(color_);
		*number_[i]->getpTransform()->getpPosition() = Vec3(position_.x + AmountOfShift, 
															position_.y, 0.0f);
		*number_[i]->getpTransform()->getpScale() = Vec3(scale_.x, scale_.y, 1.0f);
		number_[i]->getpTransform()->CreateWorldMatrix();

		AmountOfShift -= (scale_.x / 2);

		// �[���l�߂��Ȃ��Ȃ烋�[�v�I��
		if (!is_zero_ && !number) return;
	}
}



void NumbersPolygon::ReleaseNumberPolygon()
{
	// �����|���S�������
	for (auto& contents : number_)
	{
		SafeRelease::PlusUninit(&contents);
	}
	number_.clear();
}