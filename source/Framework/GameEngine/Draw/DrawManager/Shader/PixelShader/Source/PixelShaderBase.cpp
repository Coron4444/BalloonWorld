//================================================================================
//!	@file	 PixelShaderBase.cpp
//!	@brief	 ピクセルシェーダーBassClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../PixelShaderBase.h"

#include <Resource/Texture/TextureManager/TextureManager.h>
#include <Tool/SafeRelease.h>



//****************************************
// 定数定義
//****************************************
const std::string PixelShaderBase::DEFAULT_TEXTURE_NAME = "Shader/DefaultTexture.png";



//****************************************
// プロパティ定義
//****************************************
LPDIRECT3DPIXELSHADER9 PixelShaderBase::getpPixelShader()
{
	return pixel_shader_;
}



LPDIRECT3DTEXTURE9 PixelShaderBase::getpDefaultTexture()
{
	
	return default_texture_->getpHandler();
}



//****************************************
// 関数定義
//****************************************
void PixelShaderBase::InitDefaultTexture()
{
	if (default_texture_ != nullptr) return;
	
	default_texture_ = TextureManager::getpInstance()
		->getpObject(&DEFAULT_TEXTURE_NAME);
}



void PixelShaderBase::ShaderSetToDevice()
{
	getpDevice()->SetPixelShader(pixel_shader_);
}



bool PixelShaderBase::PixelShaderCompile(const char* file_name,
										 const char* entry_function,
										 const char* version)
{
	LPD3DXBUFFER compiled_code;
	bool is_compile = ShaderBase::ShaderCompile(file_name, entry_function,
												version, &compiled_code);
	if (!is_compile) return false;

	HRESULT hr = getpDevice()
		->CreatePixelShader((DWORD*)compiled_code->GetBufferPointer(),
							&pixel_shader_);

	compiled_code->Release();

	// 成功したか
	if (SUCCEEDED(hr)) return true;

	// エラーメッセージ
	MessageBox(nullptr, "ピクセルシェーダー作成失敗", "Error", MB_OK);
	return false;
}



void PixelShaderBase::ReleasePixelShader()
{
	ReleaseConstantTable();
	SafeRelease::PlusRelease(&pixel_shader_);
	SafeRelease::PlusRelease(&default_texture_);
}