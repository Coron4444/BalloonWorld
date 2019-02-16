//================================================================================
//!	@file	 ScoreDraw.h
//!	@brief	 スコア描画Class
//! @details 
//!	@author  Kai Araki									@date 2018/06/20
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../ScoreDraw.h"
#include "../Score.h"

#include <Resource/Polygon/NumbersPolygon.h>
#include <Tool/SafeRelease.h>



//****************************************
// 定数定義
//****************************************
const std::string ScoreDraw::TEXTURE_NAME = "UI/Num.png";
const int ScoreDraw::SCORE_DIGITS_NUM = 4;
const Vec2 ScoreDraw::SCORE_POSITION(-100.0f, 300.0f);
const Vec2 ScoreDraw::SCORE_SCALE(80.0f, 50.0f);
const XColor4 ScoreDraw::SCORE_COLOR(0.0f, 0.0f, 0.0f, 1.0f);



//****************************************
// プロパティ定義
//****************************************
unsigned ScoreDraw::getObjectNum()
{
	return numbers_polygon_->getObjectNum();
}



MATRIX* ScoreDraw::getpMatrix(unsigned object_index)
{
	return numbers_polygon_->getpMatrix(object_index);
}



D3DMATERIAL9* ScoreDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	mesh_index = mesh_index;
	return numbers_polygon_->getpMaterial(object_index);
}



LPDIRECT3DTEXTURE9 ScoreDraw::getpDiffuseTexture(unsigned object_index,
														 unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return diffuse_texture_->getpHandler();
}



//****************************************
// 関数定義
//****************************************
void ScoreDraw::Init()
{
	// オーダーリスト設定
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::TWO_DIMENSIONAL);
	getpDrawOrderList()->getpRenderTargetFlag()->setFlag(DrawOrderList::RENDER_TARGET_MAIN);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::FIXED);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::FIXED);

	// ダウンキャスト
	score_ = (Score*)getpGameObject();

	// テクスチャの登録
	diffuse_texture_ = TextureManager::getpInstance()->getpObject(&TEXTURE_NAME);

	// 数字群ポリゴン作成
	numbers_polygon_ = new NumbersPolygon();
	numbers_polygon_->Init(score_->getpGameScene()->getScore(),SCORE_DIGITS_NUM, true,
						   SCORE_POSITION, SCORE_SCALE, SCORE_COLOR, diffuse_texture_);
}



void ScoreDraw::Uninit()
{
	SafeRelease::PlusRelease(&diffuse_texture_);
	SafeRelease::PlusUninit(&numbers_polygon_);
}



void ScoreDraw::Update()
{
	numbers_polygon_->setNumber(score_->getpGameScene()->getScore());
}



void ScoreDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	mesh_index = mesh_index;
	numbers_polygon_->Draw(object_index);
}