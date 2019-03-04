//================================================================================
//!	@file	 PauseDraw.cpp
//!	@brief	 ポーズ描画Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/19
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../PauseDraw.h"
#include "../Pause.h"



//****************************************
// 定数定義
//****************************************
const std::string PauseDraw::TEXTURE_NAME[PauseDraw::OBJECT_NUM] =
{
	"Pause/Back.png",
	"Pause/Tuzukeru.png",
	"Pause/Hazimekara.png",
	"Pause/Yameru.png",
	"Pause/Icon.png"
};




//****************************************
// プロパティ定義
//****************************************
unsigned PauseDraw::getObjectNum()
{
	return OBJECT_NUM;
}



unsigned PauseDraw::getMeshNum(unsigned object_index)
{
	object_index = object_index;

	return plane_polygon_->getMeshNum();
}



MATRIX* PauseDraw::getpMatrix(unsigned object_index)
{
	if (object_index == OBJECT_NUM - 1)
	{
		return pause_->getpIconTransform()->getpWorldMatrix();
	}

	return getpGameObject()->getpTransform()->getpWorldMatrix();
}



D3DMATERIAL9* PauseDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	mesh_index = mesh_index;

	if (object_index == 0 || object_index == 4)
	{
		plane_polygon_->setColor(Pause::CHARACTER_COLOR0);
	}
	else
	{
		plane_polygon_->setColor(pause_->getCharacterColor(object_index - 1));
	}
	return plane_polygon_->getpMaterial();
}



LPDIRECT3DTEXTURE9 PauseDraw::getpDiffuseTexture(unsigned object_index,
												 unsigned mesh_index)
{
	mesh_index = mesh_index;

	return texture_[object_index]->getpHandler();
}



//****************************************
// 関数定義
//****************************************
void PauseDraw::Init()
{
	// オーダーリスト設定
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::TWO_DIMENSIONAL);
	getpDrawOrderList()->getpRenderTargetFlag()->setFlag(DrawOrderList::RENDER_TARGET_MAIN);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::FIXED);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::FIXED);

	// テクスチャの登録
	for (unsigned i = 0; i < OBJECT_NUM; i++)
	{
		texture_[i] = TextureManager::getpInstance()->getpObject(&TEXTURE_NAME[i]);
	}

	// 平面ポリゴン作成
	plane_polygon_ = new PlanePolygon();
	plane_polygon_->Init();

	// ダウンキャスト
	pause_ = (Pause*)getpGameObject();

	// 背景拡縮
	pause_->getpTransform()->getpScale()->x *= (float)texture_[0]->getWidth();
	pause_->getpTransform()->getpScale()->y *= (float)texture_[0]->getHeight();
	pause_->getpTransform()->CreateWorldMatrix();

	// アイコン拡縮
	pause_->getpIconTransform()->getpScale()->x *= (float)texture_[4]->getWidth();
	pause_->getpIconTransform()->getpScale()->y *= (float)texture_[4]->getHeight();
	pause_->getpIconTransform()->CreateWorldMatrix();
}



void PauseDraw::Uninit()
{
	SafeRelease::PlusUninit(&plane_polygon_);
	for (unsigned i = 0; i < OBJECT_NUM; i++)
	{
		SafeRelease::PlusRelease(&texture_[i]);
	}
}



void PauseDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	plane_polygon_->Draw();
}