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



LPDIRECT3DSURFACE9 RenderTexture::getpStencilSurface()
{
	return stencil_surface_;
}



D3DVIEWPORT9* RenderTexture::getpViewPort()
{
	return &view_port_;
}



void RenderTexture::setViewPort(D3DVIEWPORT9 value)
{
	view_port_ = value;

}



void RenderTexture::setStencilSurface(LPDIRECT3DSURFACE9 value)
{
	stencil_surface_ = value;
}



void RenderTexture::setRenderTarget(int render_target_index)
{
	device_->SetRenderTarget(render_target_index, surface_);
}



void RenderTexture::setStencilSurfaceAndViewPort()
{
	device_->SetDepthStencilSurface(stencil_surface_);
	device_->SetViewport(&view_port_);
}



//****************************************
// 関数定義
//****************************************
void RenderTexture::Init(int texture_width, int texture_height, _D3DFORMAT format)
{
	Renderer::getpInstance()->getDevice(&device_);
	D3DXCreateTexture(device_, texture_width, texture_height, 1, D3DUSAGE_RENDERTARGET, format,
					  D3DPOOL_DEFAULT, &texture_);
	texture_->GetSurfaceLevel(0, &surface_);

	device_->CreateDepthStencilSurface(texture_width, texture_height, D3DFMT_D16,
									   D3DMULTISAMPLE_NONE, 0, TRUE,
									   &stencil_surface_, nullptr);

	view_port_ = {0, 0, (DWORD)texture_width, (DWORD)texture_height, 0.0f, 1.0f};
}



void RenderTexture::Uninit()
{
	SafeRelease::PlusRelease(&texture_);
	SafeRelease::PlusRelease(&surface_);
	SafeRelease::PlusRelease(&stencil_surface_);
}