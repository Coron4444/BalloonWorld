//================================================================================
//!	@file	 ClearLogoDraw.cpp
//!	@brief	 クリアロゴ描画Class
//! @details 
//!	@author  Kai Araki									@date 2018/06/19
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../ClearLogoDraw.h"
#include "../ClearLogo.h"
#include <Resource/Polygon/NumbersPolygon.h>
#include <Resource/Polygon/PlanePolygon.h>
#include <Tool/SafeRelease.h>



//****************************************
// 定数定義
//****************************************
const std::string ClearLogoDraw::TEXTURE_NAME = "UI/Num.png";
const std::string ClearLogoDraw::TEXTURE_NAME2 = "UI/Result.png";
const int ClearLogoDraw::SCORE_DIGITS_NUM = 0;
const Vec2 ClearLogoDraw::SCORE_POSITION(-60.0f, -150.0f);
const Vec2 ClearLogoDraw::SCORE_SCALE(290.0f, 240.0f);
const XColor4 ClearLogoDraw::SCORE_COLOR(0.0f, 0.0f, 0.0f, 1.0f);
const float ClearLogoDraw::SCALE = 1.41f;



//****************************************
// プロパティ定義
//****************************************
unsigned ClearLogoDraw::getObjectNum()
{
	return numbers_polygon_->getObjectNum() + 1;
}



MATRIX* ClearLogoDraw::getpMatrix(unsigned object_index)
{
	if (object_index == 0)
	{
		return clear_logo_->getpTransform()->getpWorldMatrix();
	}
	return numbers_polygon_->getpMatrix(object_index - 1);
}



D3DMATERIAL9* ClearLogoDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	mesh_index = mesh_index;
	if (object_index == 0)
	{
		return plane_polygon_->getpMaterial();
	}
	return numbers_polygon_->getpMaterial(object_index - 1);
}



LPDIRECT3DTEXTURE9 ClearLogoDraw::getpDiffuseTexture(unsigned object_index,
													 unsigned mesh_index)
{
	mesh_index = mesh_index;
	if (object_index == 0)
	{
		return texture_2->getpHandler();
	}
	return texture_->getpHandler();
}



//****************************************
// 関数定義
//****************************************
void ClearLogoDraw::Init()
{
	// オーダーリスト設定
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::TWO_DIMENSIONAL);
	getpDrawOrderList()->getpRenderTargetFlag()->setFlag(DrawOrderList::RENDER_TARGET_MAIN);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::FIXED);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::FIXED);

	// ダウンキャスト
	clear_logo_ = (ClearLogo*)getpGameObject();

	// テクスチャの登録
	texture_ = TextureManager::getpInstance()->getpObject(&TEXTURE_NAME);
	texture_2 = TextureManager::getpInstance()->getpObject(&TEXTURE_NAME2);

	// 数字群ポリゴン作成
	numbers_polygon_ = new NumbersPolygon();
	numbers_polygon_->Init(clear_logo_->getScore(), SCORE_DIGITS_NUM, true, SCORE_POSITION,
						   SCORE_SCALE, SCORE_COLOR, texture_);

	plane_polygon_ = new PlanePolygon();
	plane_polygon_->Init();
	clear_logo_->getpTransform()->getpPosition()->x = 0.0f;
	clear_logo_->getpTransform()->getpPosition()->y = 0.0f;
	clear_logo_->getpTransform()->getpScale()->x = texture_2->getWidth() * SCALE;
	clear_logo_->getpTransform()->getpScale()->y = texture_2->getHeight() * SCALE;
	clear_logo_->getpTransform()->CreateWorldMatrix();
}



void ClearLogoDraw::Uninit()
{
	SafeRelease::PlusRelease(&texture_);
	SafeRelease::PlusRelease(&texture_2);
	SafeRelease::PlusUninit(&numbers_polygon_);
	SafeRelease::PlusUninit(&plane_polygon_);
}



void ClearLogoDraw::Update()
{
	numbers_polygon_->setNumber(clear_logo_->getScore());
}



void ClearLogoDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	mesh_index = mesh_index;
	if (object_index == 0)
	{
		return plane_polygon_->Draw();
	}
	return numbers_polygon_->Draw(object_index - 1);
}