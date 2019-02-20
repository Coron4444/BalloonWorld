//================================================================================
//!	@file	 Pause.cpp
//!	@brief	 ポーズClass
//! @details 
//!	@author  Kai Araki									@date 2019/02/18
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../Pause.h"

#include <GameEngine/Input/InputManager/InputManager.h>
#include <GameEngine/Draw/DrawBase.h>
#include <Tool/TimeToFrame.h>



//****************************************
// 定数定義
//****************************************
const float Pause::FRAME_SCALE = 0.5f;
const float Pause::ICON_SCALE = 0.3f;
const float Pause::TOP_ICON_POSITION_Y = 40.0f;
const float Pause::BOTTOM_ICON_POSITION_Y = -200.0f;
const float Pause::ADD_ICON_POSITION_Y = 120.0f;
const Vec3 Pause::DEFAULT_ICON_POSITION(-150.0f, TOP_ICON_POSITION_Y, 0.0f);
const float Pause::BLINKING_SECOND = 0.3f;
const int Pause::BLINKING_NUM = 8;
const XColor4 Pause::CHARACTER_COLOR0(1.0f, 1.0f, 1.0f, 1.0f);
const XColor4 Pause::CHARACTER_COLOR1(1.0f, 0.0f, 0.0f, 1.0f);



//****************************************
// プロパティ定義
//****************************************
bool Pause::getIsEnable()
{
	return is_enable_;
}



void Pause::setIsEnable(bool value)
{
	if (value)
	{
		if (is_enable_) return;
		is_enable_ = true;
		setIsUpdate(true);
		getpDraw()->setIsEnable(true);
		select_type_ = SelectType::NONE;
		*icon_transform_.getpPosition() = DEFAULT_ICON_POSITION;
		icon_transform_.CreateAxisAndWorldMatrix();
		inter_container_[0].clear();
		inter_container_[1].clear();
		inter_container_[2].clear();
		inter_container_[3].clear();

		for (int i = 0; i < CHARACTER_COLOR_NUM; i++)
		{
			character_color_[i] = CHARACTER_COLOR0;
		}
	}
	else
	{
		is_enable_ = false;
		setIsUpdate(false);
		setIsInput(true);
		getpDraw()->setIsEnable(false);
		inter_container_[0].clear();
		inter_container_[1].clear();
		inter_container_[2].clear();
		inter_container_[3].clear();
	}
}



bool Pause::getIsDecision()
{
	if (inter_container_[0].size() == 0) return false;
	if (!inter_iter_[0].getIsFinished()) return false;
	return true;
}



Transform* Pause::getpIconTransform()
{
	return &icon_transform_;
}



Pause::SelectType Pause::getSelectType()
{
	return select_type_;
}



XColor4 Pause::getCharacterColor(int index)
{
	return character_color_[index];
}



//****************************************
// 関数定義
//****************************************
void Pause::Init(DrawBase* draw)
{
	// 変形
	*getpTransform()->getpScale() = Vec3(FRAME_SCALE, FRAME_SCALE, 1.0f);
	getpTransform()->CreateAxisAndWorldMatrix();

	// アイコン変形
	*icon_transform_.getpScale() = Vec3(ICON_SCALE, ICON_SCALE, 1.0f);
	*icon_transform_.getpPosition() = DEFAULT_ICON_POSITION;
	icon_transform_.CreateAxisAndWorldMatrix();

	// 基底クラスの初期化
	GameObjectBase::Init(draw, nullptr);
}



void Pause::Update()
{
	Input();
	icon_transform_.CreateAxisAndWorldMatrix();
	//icon_transform_.AddParentMatrixToWorldMatrix(getpTransform()->getpWorldMatrix());

	switch (select_type_)
	{
		case Pause::SelectType::CONTINUE:
		{
			character_color_[(int)Pause::SelectType::CONTINUE] = CHARACTER_COLOR1;
			character_color_[(int)Pause::SelectType::RESTART] = CHARACTER_COLOR0;
			character_color_[(int)Pause::SelectType::QUIT] = CHARACTER_COLOR0;
			break;
		}
		case Pause::SelectType::RESTART:
		{
			character_color_[(int)Pause::SelectType::CONTINUE] = CHARACTER_COLOR0;
			character_color_[(int)Pause::SelectType::RESTART] = CHARACTER_COLOR1;
			character_color_[(int)Pause::SelectType::QUIT] = CHARACTER_COLOR0;
			break;
		}
		case Pause::SelectType::QUIT:
		{
			character_color_[(int)Pause::SelectType::CONTINUE] = CHARACTER_COLOR0;
			character_color_[(int)Pause::SelectType::RESTART] = CHARACTER_COLOR0;
			character_color_[(int)Pause::SelectType::QUIT] = CHARACTER_COLOR1;
			break;
		}
	}

	// 色の補間を進行
	if (inter_container_[0].size() == 0) return;
	XColor4 color = XColor4(*inter_iter_[0], *inter_iter_[1], 
							*inter_iter_[2], *inter_iter_[3]);
	character_color_[(int)select_type_] = color;
	inter_iter_[0]++;
	inter_iter_[1]++;
	inter_iter_[2]++;
	inter_iter_[3]++;
}



void Pause::Input()
{
	if (!getIsInput()) return;

	// 上
	if (InputManager::getpInstance()->getpKeyboard()->getTrigger(DIK_W) ||
		InputManager::getpInstance()->getpController()
		->getTriggerLStick(0, Controller::Direction::UP))
	{
		icon_transform_.getpPosition()->y += ADD_ICON_POSITION_Y;

		// ループ処理
		if (icon_transform_.getpPosition()->y > TOP_ICON_POSITION_Y)
		{
			icon_transform_.getpPosition()->y = BOTTOM_ICON_POSITION_Y;
		}
	}

	// 下
	if (InputManager::getpInstance()->getpKeyboard()->getTrigger(DIK_S) ||
		InputManager::getpInstance()->getpController()
		->getTriggerLStick(0, Controller::Direction::DOWN))
	{
		icon_transform_.getpPosition()->y += -ADD_ICON_POSITION_Y;

		// ループ処理
		if (icon_transform_.getpPosition()->y < BOTTOM_ICON_POSITION_Y)
		{
			icon_transform_.getpPosition()->y = TOP_ICON_POSITION_Y;
		}
	}

	// 選択タイプ変更
	if (icon_transform_.getpPosition()->y == TOP_ICON_POSITION_Y)
	{
		select_type_ = SelectType::CONTINUE;
	}
	else if (icon_transform_.getpPosition()->y == BOTTOM_ICON_POSITION_Y)
	{
		select_type_ = SelectType::QUIT;
	}
	else
	{
		select_type_ = SelectType::RESTART;
	}

	// 決定
	if (InputManager::getpInstance()->getpKeyboard()->getTrigger(DIK_SPACE) ||
		InputManager::getpInstance()->getpController()
		->getTrigger(0, XINPUT_GAMEPAD_B))
	{
		// カラーアニメーションセット
		float pattern_second = BLINKING_SECOND / BLINKING_NUM;	// 1パターンの秒数
		for (int i = 0; i < BLINKING_NUM; i++)
		{
			XColor4 color = (i % 2) == 0 ? CHARACTER_COLOR0 : CHARACTER_COLOR1;
			double distance = (double)TimeToFrame::SecondToFrame(pattern_second);
			inter_container_[0].push_back(color.r, distance);
			inter_container_[1].push_back(color.g, distance);
			inter_container_[2].push_back(color.b, distance);
			inter_container_[3].push_back(color.a, distance);
		}
		inter_iter_[0] = inter_container_[0].begin();
		inter_iter_[1] = inter_container_[1].begin();
		inter_iter_[2] = inter_container_[2].begin();
		inter_iter_[3] = inter_container_[3].begin();

		// 入力OFF
		setIsInput(false);
	}
}