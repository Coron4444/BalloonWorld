//================================================================================
//!	@file	 MotionBlur.cpp
//!	@brief	 モーションブラーClass
//! @details 
//!	@author  Kai Araki									@date 2019/01/28
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../MotionBlur.h"
#include "../../DrawCommonData.h"
#include "../../RenderTexturePolygon.h"
#include "../../Shader/ShaderManager/ShaderManager.h"
#include "../../../Camera/Camera.h"



//****************************************
// プロパティ定義
//****************************************
void MotionBlur::setCamera(Camera* value)
{
	camera_ = value;
}



void MotionBlur::setDrawCommonData(DrawCommonData* value)
{
	common_data_ = value;
}



void MotionBlur::setShaderManager(ShaderManager* value)
{
	shader_manager_ = value;
}



//****************************************
// 関数定義
//****************************************
void MotionBlur::Init()
{
	polygon_ = new RenderTexturePolygon();
	polygon_->Init();
	polygon_->Update(0.0f, 0.0f,
		(float)GameEngine::SCREEN_WIDTH * 1.03f,
					 (float)GameEngine::SCREEN_HEIGHT * 1.03f,
					 XColor4(1.0f, 1.0f, 1.0f, 0.96f));
}



void MotionBlur::Uninit()
{
	SafeRelease::PlusUninit(&polygon_);
}



void MotionBlur::UninitWhenChangeScene()
{

}



void MotionBlur::Update()
{
}



void MotionBlur::LateUpdate()
{
	// テクスチャとサーフェスを交換
	LPDIRECT3DTEXTURE9 temp;
	temp = common_data_->getpRenderTextureMain()->getpTexture();
	common_data_->getpRenderTextureMain()->setTexture(common_data_
													  ->getpRenderTextureMotionBlur()
													  ->getpTexture());
	common_data_->getpRenderTextureMotionBlur()->setTexture(temp);

	LPDIRECT3DSURFACE9 temp2;
	temp2 = common_data_->getpRenderTextureMain()->getpSurface();
	common_data_->getpRenderTextureMain()->setSurface(common_data_
													  ->getpRenderTextureMotionBlur()
													  ->getpSurface());
	common_data_->getpRenderTextureMotionBlur()->setSurface(temp2);
}



void MotionBlur::Draw()
{
	// レンダーターゲットの切り替え
	LPDIRECT3DDEVICE9 device;
	Renderer::getpInstance()->getDevice(&device);
	common_data_->getpRenderTextureMain()->setRenderTarget(0);
	bool is_begin = Renderer::getpInstance()->NoClearDrawBegin();

	// カメラ切り替え
	camera_->setType(Camera::Type::TWO_DIMENSIONAL);

	// シェーダーセット
	shader_manager_->ShaderSetToDevice(polygon_,
									   ShaderManager::VertexShaderType::FIXED,
									   ShaderManager::PixelShaderType::FIXED);
	// オブジェクト設定
	shader_manager_->ObjectSetting(polygon_, camera_, 0);

	// 描画
	device->SetTexture(0, common_data_->getpRenderTextureMotionBlur()->getpTexture());
	polygon_->Draw(0, 0);
	Renderer::getpInstance()->DrawEnd(is_begin);
}