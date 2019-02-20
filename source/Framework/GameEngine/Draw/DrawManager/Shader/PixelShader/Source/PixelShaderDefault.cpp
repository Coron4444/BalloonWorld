//================================================================================
//!	@file	 PixelShaderDefault.cpp
//!	@brief	 デフォルトピクセルシェーダーClass
//! @details 
//!	@author  Kai Araki									@date 2019/01/21
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../PixelShaderDefault.h"



//****************************************
// 定数定義
//****************************************
const char* PixelShaderDefault::PATH = "resource/HLSL/Effect/PixelShader/Default.psh";



//****************************************
// 関数定義
//****************************************
void PixelShaderDefault::Init()
{
	// デバイス初期化
	InitDevice();

	// デフォルトテクスチャ初期化
	InitDefaultTexture();

	// シェーダーのコンパイル
	PixelShaderCompile(PATH, "MainPixelShader", "ps_3_0");
}



void PixelShaderDefault::Uninit()
{
	// シェーダーの解放
	ReleasePixelShader();
}



void PixelShaderDefault::ObjectSetting(DrawBase* draw, Camera* camera,
									   unsigned object_index)
{
	draw = draw;
	camera = camera;
	object_index = object_index;
}



void PixelShaderDefault::MeshSetting(DrawBase* draw, Camera* camera,
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
}