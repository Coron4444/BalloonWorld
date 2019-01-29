//================================================================================
//!	@file	 RenderTexture.cpp
//!	@brief	 レンダーテクスチャClass
//! @details 
//!	@author  Kai Araki									@date 2019/01/28
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../RenderTexture.h"

#include <Tool/SafeRelease.h>



//****************************************
// プロパティ定義
//****************************************
LPDIRECT3DTEXTURE9 RenderTexture::getpTexture()
{
	return texture_;
}



void RenderTexture::setTexture(LPDIRECT3DTEXTURE9 value)
{
	texture_ = value;
}



LPDIRECT3DSURFACE9 RenderTexture::getpSurface()
{
	return surface_;
}



void RenderTexture::setSurface(LPDIRECT3DSURFACE9 value)
{
	surface_ = value;
}



void RenderTexture::setRenderTarget(int render_target_index)
{
	device_->SetRenderTarget(render_target_index, surface_);
}



//****************************************
// 関数定義
//****************************************
void RenderTexture::Init(float texture_width, float texture_height)
{
	Renderer::getpInstance()->getDevice(&device_);
	D3DXCreateTexture(device_, texture_width, texture_height, 1,
					  D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8,
					  D3DPOOL_DEFAULT, &texture_);
	texture_->GetSurfaceLevel(0, &surface_);
}



void RenderTexture::Uninit()
{
	SafeRelease::PlusRelease(&texture_);
	SafeRelease::PlusRelease(&surface_);
}