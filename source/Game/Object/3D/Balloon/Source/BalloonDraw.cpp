//================================================================================
//!	@file	 BalloonDraw.cpp
//!	@brief	 風船描画Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/05
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../BalloonDraw.h"
#include "../Balloon.h"

#include <GameEngine/Collision/BulletPhysics/BulletPhysicsManager/BulletPhysicsManager.h>
#include <Resource/ModelX/ModelXManager/ModelXManager.h>
#include <Tool/SafeRelease.h>
#include <Tool/Random.h>



//****************************************
// 定数定義
//****************************************
const std::string BalloonDraw::BALLOON_MODEL_NAME = "Balloon/Balloon.x";
const std::string BalloonDraw::BALLOON_LINE_MODEL_NAME = "Balloon/Line.x";
const XColor4 BalloonDraw::BALLOON_COLOR[BalloonDraw::BALLOON_COLOR_NUM] =
{
	{0.3f, 1.0f, 1.0f, 1.0f},
	{1.0f, 1.0f, 0.5f, 1.0f},
	{1.0f, 0.3f, 0.5f, 1.0f}
};



//****************************************
// プロパティ定義
//****************************************
unsigned BalloonDraw::getObjectNum()
{
	return balloon_->getAllObjectNum();
}



unsigned BalloonDraw::getMeshNum(unsigned object_index)
{
	if (object_index == (unsigned)balloon_->getAllObjectNum() - 1)
	{
		return balloon_object_->getMeshNum();
	}
	else
	{
		return balloon_line_object_->getMeshNum();
	}
}



MATRIX* BalloonDraw::getpMatrix(unsigned object_index)
{
	return object_transform_[object_index].getpWorldMatrix();
}



D3DMATERIAL9* BalloonDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	if (object_index == (unsigned)balloon_->getAllObjectNum() - 1)
	{
		balloon_object_->setMaterialColor(mesh_index, color_);
		return balloon_object_->getpMaterial(mesh_index);
	}
	else
	{
		return balloon_line_object_->getpMaterial(mesh_index);
	}
}



//****************************************
// 関数定義
//****************************************
void BalloonDraw::Init()
{
	// ダウンキャスト
	balloon_ = (Balloon*)getpGameObject();

	// オーダーリスト設定
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::TRANSPARENCY);
	getpDrawOrderList()->getpRenderTargetFlag()->setFlag(DrawOrderList::RENDER_TARGET_MAIN);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::BLINN_PHONG);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::BLINN_PHONG);
	//getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::COOK_TORRANCE);
	//getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::COOK_TORRANCE);

	// オブジェクト取得
	balloon_object_ = ModelXManager::getpInstance()->getpObject(&BALLOON_MODEL_NAME);
	balloon_line_object_ = ModelXManager::getpInstance()->getpObject(&BALLOON_LINE_MODEL_NAME);

	// オブジェクト変形初期化
	object_transform_.resize(balloon_->getAllObjectNum());
	for (int i = 0; i < balloon_->getAllObjectNum() - 1; i++)
	{
		*object_transform_[i].getpScale() = Balloon::OBB_EDGE_LENGTH_HALF * 2.5f;
	}
	float adjustment_balloon_scale = 0.9f;
	object_transform_[balloon_->getAllObjectNum() - 1].getpScale()->x 
		= Balloon::SPHERE_RADIUS * adjustment_balloon_scale;
	object_transform_[balloon_->getAllObjectNum() - 1].getpScale()->y 
		= Balloon::SPHERE_RADIUS;
	object_transform_[balloon_->getAllObjectNum() - 1].getpScale()->z 
		= Balloon::SPHERE_RADIUS * adjustment_balloon_scale;

	// 色初期化
	int color_index = Random::getpInstance()->getInt(0, BALLOON_COLOR_NUM - 1);
	for (unsigned i = 0; i < balloon_object_->getMeshNum(); i++)
	{
		color_ = BALLOON_COLOR[color_index];
	}
}



void BalloonDraw::Uninit()
{
	SafeRelease::PlusRelease(&balloon_line_object_);
	SafeRelease::PlusRelease(&balloon_object_);
}



void BalloonDraw::Update()
{
	// オブジェクト変形
	for (int i = 0; i < balloon_->getAllObjectNum(); i++)
	{
		*object_transform_[i].getpPosition() = balloon_->getpObject(i)->getPosition();
		object_transform_[i].ResetAddQuaternion();
		object_transform_[i].setAddQuaternion(balloon_->getpObject(i)
											  ->getQuaternion());
		object_transform_[i].CreateAxisAndWorldMatrix();
	}
}



void BalloonDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	if (object_index <= 0) return;

	if (object_index == (unsigned)balloon_->getAllObjectNum() - 1)
	{
		balloon_object_->getpMesh()->DrawSubset(mesh_index);
	}
	else
	{
		balloon_line_object_->getpMesh()->DrawSubset(mesh_index);
	}
}