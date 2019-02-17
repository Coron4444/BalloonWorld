//================================================================================
//!	@file	 PixelShaderBase.h
//!	@brief	 ピクセルシェーダーBassClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================
#ifndef	_PIXEL_SHADER_BASE_H_
#define _PIXEL_SHADER_BASE_H_



//****************************************
// インクルード文
//****************************************
#include <string>

#include "../ShaderBase.h"



//****************************************
// クラス宣言
//****************************************
class TextureObject;



//************************************************************														   
//! @brief   ピクセルシェーダーBassClass
//!
//! @details ピクセルシェーダーのBassClass
//************************************************************
class PixelShaderBase : public ShaderBase
{
//====================
// 定数
//====================
private:
	static const std::string DEFAULT_TEXTURE_NAME;		//!< デフォルトテクスチャ名


//====================
// 変数
//====================
private:
	LPDIRECT3DPIXELSHADER9 pixel_shader_ = nullptr;		//!< ピクセルシェーダー
	TextureObject* default_texture_ = nullptr;			//!< デフォルトテクスチャオブジェクト


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief ピクセルシェーダー取得関数
	//! @details
	//! @param void なし
	//! @retval LPDIRECT3DPIXELSHADER9 ピクセルシェーダー
	//----------------------------------------
	LPDIRECT3DPIXELSHADER9 getpPixelShader();

	//----------------------------------------
	//! @brief デフォルトテクスチャハンドラ取得関数
	//! @details
	//! @param void なし
	//! @retval LPDIRECT3DTEXTURE9 デフォルトテクスチャハンドラ
	//----------------------------------------
	LPDIRECT3DTEXTURE9 getpDefaultTexture();


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief デフォルトテクスチャハンドラ初期化関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void InitDefaultTexture();

	//----------------------------------------
	//! @brief デバイスにシェーダー設定関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void ShaderSetToDevice() override;

	//----------------------------------------
	//! @brief ピクセルシェーダーコンパイル関数
	//! @details
	//! @param *file_name      ファイル名
	//! @param *entry_function エントリ関数名
	//! @param *version        シェーダーバージョン
	//! @retval bool コンパイル成功ならtrue
	//----------------------------------------
	bool PixelShaderCompile(const char* file_name,
							const char* entry_function,
							const char* version);

	//----------------------------------------
	//! @brief ピクセルシェーダー解放関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void ReleasePixelShader();
};



#endif
