//================================================================================
//!	@file	 StartBlockDraw.cpp
//!	@brief	 スタートブロック描画Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/13
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../StartBlockDraw.h"

#include <Resource/Effekseer/EffekseerManager/EffekseerManager.h>
#include <Resource/Polygon/CubePolygon.h>
#include <Tool/SafeRelease.h>



//****************************************
// 定数定義
//****************************************
const std::string StartBlockDraw::EFFECT_NAME = "CoinEffect/CoinEffect.efk";



//****************************************
// プロパティ定義
//****************************************
unsigned StartBlockDraw::getMeshNum(unsigned object_index)
{
	object_index = object_index;

	return cube_polygon_->getMeshNum();
}



MATRIX* StartBlockDraw::getpMatrix(unsigned object_index)
{
	object_index = object_index;

	return getpGameObject()->getpTransform()->getpWorldMatrix();
}



D3DMATERIAL9* StartBlockDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return cube_polygon_->getpMaterial();
}



//****************************************
// 関数定義
//****************************************
void StartBlockDraw::Init()
{
	// オーダーリスト設定
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::OPACITY);
	getpDrawOrderList()->getpRenderTargetFlag()->setFlag(DrawOrderList::RENDER_TARGET_MAIN);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::FIXED);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::FIXED);

	// キューブポリゴンの生成
	cube_polygon_ = new CubePolygon();
	cube_polygon_->Init(XColor4(0.5f, 1.0f, 1.0f, 1.0f));

	// エフェクトの読み込み
	effekseer_object_ = EffekseerManager::getpInstance()->getpObject(&EFFECT_NAME);
	effekseer_object_->ChangeColor(255, 255, 255, 255);
	*effekseer_object_->getpTransform()->getpPosition() = *getpGameObject()->getpTransform()->getpPosition();
	*effekseer_object_->getpTransform()->getpPosition() = *getpGameObject()->getpTransform()->getpScale();
	effekseer_object_->getpTransform()->CreateWorldMatrix();
	effekseer_object_->setIsRepeat(true);
	effekseer_object_->Play();
}



void StartBlockDraw::Uninit()
{
	SafeRelease::PlusUninit(&cube_polygon_);
	SafeRelease::PlusRelease(&effekseer_object_);
}



void StartBlockDraw::Update()
{
	// エフェクト更新
	*effekseer_object_->getpTransform()->getpPosition() = *getpGameObject()->getpTransform()->getpPosition();
	*effekseer_object_->getpTransform()->getpPosition() = *getpGameObject()->getpTransform()->getpScale();
	effekseer_object_->getpTransform()->CreateWorldMatrix();
}



void StartBlockDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	cube_polygon_->Draw();
}