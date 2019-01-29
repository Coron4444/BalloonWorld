//================================================================================
//!	@file	 Fade.cpp
//!	@brief	 フェードClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../Fade.h"
#include "../../../Renderer/Renderer.h"

#include <Resource/Texture/TextureManager/TextureManager.h>
#include <Resource/Polygon/PlanePolygon.h>
#include <Tool/SafeRelease.h>
#include <Tool/TimeToFrame.h>
#include <Tool/Transform.h>



//****************************************
// 定数定義
//****************************************
const std::string Fade::TEXTURE_NAME_TRANSITION_01 = "Fade/Transition_01.png";



//****************************************
// プロパティ定義
//****************************************
MATRIX* Fade::getpMatrix(unsigned object_index)
{
	object_index = object_index;
	return transform_->getpMatrixGroup()->getpWorldMatrix();
}



D3DMATERIAL9* Fade::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;
	return plane_polygon_->getpMaterial();
}



Fade::Type* Fade::getpType()
{
	return &type_; 
}



Fade::State* Fade::getpState()
{
	return &state_; 
}



bool Fade::getpEndFlag()
{
	return end_flag_; 
}



Transform* Fade::getpTransform() 
{
	return transform_;
}



TextureObject* Fade::getpTransition01Object()
{
	return transition01_texture_; 
}



//****************************************
// 関数定義
//****************************************
void Fade::Init(Type type, State state, Vec2 size, XColor4 color, float speed)
{
	// 各種代入
	type_ = type;
	state_ = state;

	// テクスチャの登録
	if (transition01_texture_ == nullptr)
	{
		transition01_texture_ = TextureManager::getpInstance()
			->getpObject(&TEXTURE_NAME_TRANSITION_01);
	}

	// オーダーリスト設定
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::TWO_DIMENSIONAL);
	getpDrawOrderList()->getpRenderTargetFlag()->setFlag(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::FIXED);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::FIXED);

	// フェードを指定サイズに変更
	transform_->getpScale()->x = size.x;
	transform_->getpScale()->y = size.y;
	transform_->CreateWorldMatrix();

	// エンドフラグOFF
	end_flag_ = false;

	// ステートごとの処理
	if (state_ == State::FADE_IN)
	{
		// カラー
		color.a = 1.0f;
		color_ = color;
		plane_polygon_->setColor(color_);

		// フェード速度(単位：秒)
		speed_ = -(1.0f / (float)TimeToFrame::SecondToFrame(speed));
	}
	else if (state_ == State::FADE_OUT)
	{
		// カラー
		color.a = 0.0f;
		color_ = color;
		plane_polygon_->setColor(color_);

		// フェード速度(単位：秒)
		speed_ = 1.0f / (float)TimeToFrame::SecondToFrame(speed);
	}
}



void Fade::Uninit()
{
	// ステートごとの処理
	if (state_ == State::FADE_IN)
	{

	}
	else if (state_ == State::FADE_OUT)
	{

	}
	end_flag_ = false;
	SafeRelease::PlusRelease(&transition01_texture_);
}



void Fade::Update()
{
	// α値を変更
	color_.a += speed_;
	plane_polygon_->setColor(color_);

	// フェードオブジェクトの更新
	if (state_ == State::FADE_IN)
	{
		// α値が0を下回ったら
		if (color_.a <= 0.0f)
		{
			end_flag_ = true;
		}
	}
	else if (state_ == State::FADE_OUT)
	{
		// α値が1を上回ったら
		if (color_.a >= 1.0f)
		{
			end_flag_ = true;
		}
	}
}



void Fade::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	// ポリゴン描画
	plane_polygon_->Draw();
}