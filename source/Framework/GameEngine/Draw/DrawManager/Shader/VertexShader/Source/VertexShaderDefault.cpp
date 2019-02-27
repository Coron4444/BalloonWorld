//================================================================================
//!	@file	 VertexShaderDefault.h
//!	@brief	 デフォルト頂点シェーダーClass
//! @details 
//!	@author  Kai Araki									@date 2019/02/19
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../VertexShaderDefault.h"



//****************************************
// 定数定義
//****************************************
const char* VertexShaderDefault::PATH = "resource/HLSL/Effect/VertexShader/Default.vsh";



//****************************************
// 関数定義
//****************************************
void VertexShaderDefault::Init()
{
	// デバイス初期化
	InitDevice();

	// シェーダーのコンパイル
	VertexShaderCompile(PATH, "MainVertexShader", "vs_3_0");
}



void VertexShaderDefault::Uninit()
{
	// シェーダーの解放
	ReleaseVertexShader();
}



void VertexShaderDefault::ObjectSetting(DrawBase* draw, Camera* camera,
											unsigned object_index)
{
	// 行列
	getpConstantTable()->SetMatrix(getpDevice(), "MATRIX_WORLD",
								   draw->getpMatrix(object_index));
	getpConstantTable()->SetMatrix(getpDevice(), "MATRIX_VIEW",
								   camera->getpViewMatrix());
	getpConstantTable()->SetMatrix(getpDevice(), "MATRIX_PROJECTION",
								   camera->getpProjectionMatrix());

	// ディレクショナルライトベクトル(オブジェクトのローカル座標系へ変換し第入)
	Vec4 light_vector = (Vec4)*getpDrawCommonData()
		->getpDirectionalLightVector();
	light_vector.w = 0.0f;
	D3DXMatrixIdentity(&math_matrix_);
	D3DXMatrixInverse(&math_matrix_, nullptr, draw->getpMatrix(object_index));
	D3DXVec4Transform(&light_vector, &light_vector, &math_matrix_);
	D3DXVec3Normalize((Vector3D*)&light_vector, (Vector3D*)&light_vector);
	light_vector.w = 0.9f;	// 環境光の比率
	getpConstantTable()->SetVector(getpDevice(), "DIRECTIONAL_LIGHT_VECTOR", 
								   &light_vector);
}



//--------------------------------------------------
// +固有設定関数
//--------------------------------------------------
void VertexShaderDefault::MeshSetting(DrawBase* draw, Camera* camera,
										  unsigned object_index, unsigned mesh_index)
{
	camera = camera;

	// ディヒューズ色の設定
	Vec4 material_diffuse_;
	material_diffuse_.x = draw->getpMaterial(object_index, mesh_index)->Diffuse.r;
	material_diffuse_.y = draw->getpMaterial(object_index, mesh_index)->Diffuse.g;
	material_diffuse_.z = draw->getpMaterial(object_index, mesh_index)->Diffuse.b;
	material_diffuse_.w = draw->getpMaterial(object_index, mesh_index)->Diffuse.a;
	getpConstantTable()->SetVector(getpDevice(), "MATERIAL_DIFFUSE",
								   &material_diffuse_);
}