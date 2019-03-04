//================================================================================
//!	@file	 VertexShaderShadowMap.cpp
//!	@brief	 シャドウマップ頂点シェーダーClass
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../VertexShaderShadowMap.h"



//****************************************
// 定数定義
//****************************************
const char* VertexShaderShadowMap::PATH = "resource/HLSL/Effect/VertexShader/ShadowMap.vsh";



//****************************************
// 関数定義
//****************************************
void VertexShaderShadowMap::Init()
{
	// デバイス初期化
	InitDevice();

	// シェーダーのコンパイル
	VertexShaderCompile(PATH, "MainVertexShader", "vs_3_0");
}



void VertexShaderShadowMap::Uninit()
{
	// シェーダーの解放
	ReleaseVertexShader();
}



void VertexShaderShadowMap::ObjectSetting(DrawBase* draw, Camera* camera,
											unsigned object_index)
{
	// 行列
	getpConstantTable()->SetMatrix(getpDevice(), "MATRIX_WORLD",
								   draw->getpMatrix(object_index));
	getpConstantTable()->SetMatrix(getpDevice(), "MATRIX_VIEW",
								   camera->getpViewMatrix());
	getpConstantTable()->SetMatrix(getpDevice(), "MATRIX_PROJECTION",
								   camera->getpProjectionMatrix());
}