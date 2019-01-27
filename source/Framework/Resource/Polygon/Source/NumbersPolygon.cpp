//================================================================================
//!	@file	 NumbersPolygon.cpp
//!	@brief	 数字群ポリゴンClass
//! @details 
//!	@author  Kai Araki									@date 2018/06/19
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../NumbersPolygon.h"
#include "../PlanePolygon.h"
#include "../../Texture/TextureObject.h"

#include <GameEngine/Renderer/Renderer.h>
#include <Tool/SafeRelease.h>



//****************************************
// プロパティ定義
//****************************************
void NumbersPolygon::NumberPolygon::setNumber(int value)
{
	if (value < 0 || value > 9) return;
	if (number_ == value) return;

	// 数字の変更とUV値の変更
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

	// 左詰め
	LeftJustified(value, &temp_digits_num);

	// カンスト判定
	IsCountStop(&value, temp_digits_num);

	// 各桁の更新
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
// 関数定義
//****************************************
void NumbersPolygon::NumberPolygon::Init()
{
	// プレーンポリゴンの作成
	plane_polygon_ = new PlanePolygon;
	plane_polygon_->Init();

	// 初期数字セット
	number_ = -1;		// 初期の数字変更用
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
		// 新たな桁数の取得
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
		// 桁数の変更
		if (*digits_num == (int)number_.size()) return;
	}

	// 数字ポリゴン作成
	CreateNumberPolygon(number, digits_num);
}



void NumbersPolygon::CreateNumberPolygon(int number, int* digits_num)
{
	// 現在の数値の解放
	ReleaseNumberPolygon();

	// 数字ポリゴン作成
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
	// ずらし量
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

		// ゼロ詰めしないならループ終了
		if (!is_zero_ && !number) return;
	}
}



void NumbersPolygon::ReleaseNumberPolygon()
{
	// 数字ポリゴンを解放
	for (auto& contents : number_)
	{
		SafeRelease::PlusUninit(&contents);
	}
	number_.clear();
}