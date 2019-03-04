//================================================================================
//!	@file	 PixelShaderShadowMap.cpp
//!	@brief	 シャドウマップピクセルシェーダーClass
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../PixelShaderShadowMap.h"



//****************************************
// 定数定義
//****************************************
const char* PixelShaderShadowMap::PATH = "resource/HLSL/Effect/PixelShader/ShadowMap.psh";



//****************************************
// 関数定義
//****************************************
void PixelShaderShadowMap::Init()
{
	// デバイス初期化
	InitDevice();

	// シェーダーのコンパイル
	PixelShaderCompile(PATH, "MainPixelShader", "ps_3_0");
}



void PixelShaderShadowMap::Uninit()
{
	// シェーダーの解放
	ReleasePixelShader();
}