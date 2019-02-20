//================================================================================
//!	@file	 PixelShaderDefaultShadowShadow.cpp
//!	@brief	 デフォルト影ピクセルシェーダーClass
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../PixelShaderDefaultShadow.h"



//****************************************
// 定数定義
//****************************************
const char* PixelShaderDefaultShadow::PATH = "resource/HLSL/Effect/PixelShader/DefaultShadow.psh";



//****************************************
// 関数定義
//****************************************
void PixelShaderDefaultShadow::Init()
{
	// デバイス初期化
	InitDevice();

	// デフォルトテクスチャ初期化
	InitDefaultTexture();

	// シェーダーのコンパイル
	PixelShaderCompile(PATH, "MainPixelShader", "ps_3_0");
}



void PixelShaderDefaultShadow::Uninit()
{
	// シェーダーの解放
	ReleasePixelShader();
}



void PixelShaderDefaultShadow::ObjectSetting(DrawBase* draw, Camera* camera,
									   unsigned object_index)
{
	draw = draw;
	camera = camera;
	object_index = object_index;
}



void PixelShaderDefaultShadow::MeshSetting(DrawBase* draw, Camera* camera,
									 unsigned object_index,
									 unsigned mesh_index)
{
	camera = camera;

	// ディフーズテクスチャ
	int sampler_index = getpConstantTable()->GetSamplerIndex("DIFFUSE_SAMPLER");
	if (draw->getpDiffuseTexture(object_index, mesh_index) == nullptr)
	{
		getpDevice()->SetTexture(sampler_index, getpDefaultTexture());
	}
	else
	{
		getpDevice()->SetTexture(sampler_index,
								 draw->getpDiffuseTexture(object_index, mesh_index));
	}

	// シャドウマップテクスチャ
	sampler_index = getpConstantTable()->GetSamplerIndex("SHADOW_MAP_SAMPLER");
	getpDevice()->SetTexture(sampler_index, getpDrawCommonData()
							 ->getpRenderTextureShadowMap()->getpTexture());
}