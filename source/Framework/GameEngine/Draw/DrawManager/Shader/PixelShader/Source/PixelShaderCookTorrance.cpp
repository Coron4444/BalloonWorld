//================================================================================
//!	@file	 PixelShaderCookTorrance.cpp
//!	@brief	 クック・トランスの金属反射ピクセルシェーダーClass
//! @details 
//!	@author  Kai Araki									@date 2019/02/18
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../PixelShaderCookTorrance.h"



//****************************************
// 定数定義
//****************************************
const char* PixelShaderCookTorrance::PATH = "resource/HLSL/Effect/PixelShader/CookTorrance.psh";



//****************************************
// 関数定義
//****************************************
void PixelShaderCookTorrance::Init()
{
	// デバイス初期化
	InitDevice();

	// デフォルトテクスチャ初期化
	InitDefaultTexture();

	// シェーダーのコンパイル
	PixelShaderCompile(PATH, "MainPixelShader", "ps_3_0");
}



void PixelShaderCookTorrance::Uninit()
{
	// シェーダーの解放
	ReleasePixelShader();
}



void PixelShaderCookTorrance::ObjectSetting(DrawBase* draw, Camera* camera,
										   unsigned object_index)
{
	camera = camera;

	// ディレクショナルライトベクトル(オブジェクトのローカル座標系へ変換し第入)
	Vec4 light_vector = (Vec4)*getpDrawCommonData()
		->getpDirectionalLightVector();
	light_vector.w = 0.0f;
	D3DXMatrixIdentity(&math_matrix_);
	D3DXMatrixInverse(&math_matrix_, nullptr, draw->getpMatrix(object_index));
	D3DXVec4Transform(&light_vector, &light_vector, &math_matrix_);
	D3DXVec3Normalize((Vector3D*)&light_vector, (Vector3D*)&light_vector);
	light_vector.w = 0.7f;	// 環境光の比率
	getpConstantTable()->SetVector(getpDevice(), "DIRECTIONAL_LIGHT_VECTOR",
								   &light_vector);

	// 視点の設定(オブジェクトのローカル座標でのカメラ座標を取得する)
	D3DXMatrixIdentity(&math_matrix_);
	D3DXMatrixMultiply(&math_matrix_, draw->getpMatrix(object_index),
					   camera->getpViewMatrix());
	D3DXMatrixInverse(&math_matrix_, nullptr, &math_matrix_);
	Vec4 object_local_camera_position(0.0f, 0.0f, 0.0f, 1.0f);
	D3DXVec4Transform(&object_local_camera_position, &object_local_camera_position, &math_matrix_);
	getpConstantTable()->SetVector(getpDevice(),
								   "CAMERA_POSITION",
								   &object_local_camera_position);
}



void PixelShaderCookTorrance::MeshSetting(DrawBase* draw, Camera* camera,
										 unsigned object_index, unsigned mesh_index)
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