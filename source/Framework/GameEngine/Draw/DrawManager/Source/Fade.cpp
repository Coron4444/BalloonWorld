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
const std::string Fade::TEXTURE_NAME_LOAD = "Fade/NowLoading.png";
const std::string Fade::TEXTURE_NAME_TRANSITION_01 = "Fade/Transition_01.png";



//****************************************
// プロパティ定義
//****************************************
MATRIX* Fade::getpMatrix(unsigned object_index)
{
	object_index = object_index;
	return transform_->getpWorldMatrix();
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



LPDIRECT3DTEXTURE9 Fade::getpDiffuseTexture(unsigned object_index,
											unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	switch (type_)
	{
		case Type::NORMAL:
		{
			return load_texture_->getpHandler();
		}
		case Type::TRANSITION_01:
		{
			return transition01_texture_->getpHandler();
		}
	}

	return nullptr;
}



//****************************************
// 関数定義
//****************************************
void Fade::Init()
{
	// テクスチャの登録
	load_texture_ = TextureManager::getpInstance()
		->getpObject(&TEXTURE_NAME_LOAD);
	transition01_texture_ = TextureManager::getpInstance()
		->getpObject(&TEXTURE_NAME_TRANSITION_01);

	// 変形作成
	transform_ = new Transform();

	// 平面ポリゴン作成
	plane_polygon_ = new PlanePolygon();
	plane_polygon_->Init();

	type_ = Fade::Type::NONE;
	state_ = Fade::State::NONE;
	end_flag_ = true;
}



void Fade::Uninit()
{
	SafeRelease::PlusUninit(&plane_polygon_);
	SafeRelease::PlusRelease(&load_texture_);
	SafeRelease::PlusRelease(&transition01_texture_);
	SafeRelease::Normal(&transform_);
}



void Fade::Update()
{
	color_.a = *inter_iter_;
	plane_polygon_->setColor(color_);
	if (inter_iter_.getIsFinished()) end_flag_ = true;
	inter_iter_++;
}



void Fade::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	// ポリゴン描画
	plane_polygon_->Draw();
}



void Fade::Start(Type type, State state, Vec2 size, XColor4 color, float speed)
{
	// 各種代入
	type_ = type;
	state_ = state;

	// オーダーリスト設定
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::TWO_DIMENSIONAL);
	getpDrawOrderList()->getpRenderTargetFlag()->setFlag(DrawOrderList::RENDER_TARGET_MAIN);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::FIXED);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::FIXED);

	// フェードを指定サイズに変更
	transform_->getpScale()->x = size.x;
	transform_->getpScale()->y = size.y;
	transform_->CreateWorldMatrix();

	// エンドフラグOFF
	end_flag_ = false;

	// ステートごとの処理
	color_ = color;
	double distance = 0.0f;
	if (state_ == State::FADE_IN)
	{
		float alpha = 1.0f;
		color_.a = alpha;
		plane_polygon_->setColor(color_);

		// 補間設定
		inter_container_.clear();
		inter_container_.push_back(alpha, distance);

		alpha = 0.0f;
		distance = (double)TimeToFrame::SecondToFrame(speed);
		inter_container_.push_back(alpha, distance);

		inter_iter_ = inter_container_.begin();
	}
	else if (state_ == State::FADE_OUT)
	{
		float alpha = 0.0f;
		color_.a = alpha;
		plane_polygon_->setColor(color_);

		// 補間設定
		inter_container_.clear();
		inter_container_.push_back(alpha, distance);

		alpha = 1.0f;
		distance = (double)TimeToFrame::SecondToFrame(speed);
		inter_container_.push_back(alpha, distance);

		inter_iter_ = inter_container_.begin();
	}
}