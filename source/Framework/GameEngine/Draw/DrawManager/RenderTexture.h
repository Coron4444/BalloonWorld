//================================================================================
//!	@file	 RenderTexture.h
//!	@brief	 レンダーテクスチャClass
//! @details 
//!	@author  Kai Araki									@date 2019/01/28
//================================================================================
#ifndef	_RENDER_TEXTURE_H_
#define _RENDER_TEXTURE_H_



//************************************************************														   
//! @brief   レンダーテクスチャClass
//!
//! @details レンダーテクスチャのClass
//************************************************************
class RenderTexture
{
//====================
// 変数
//====================
private:
	LPDIRECT3DTEXTURE9 texture_ = nullptr;			//!< テクスチャ
	LPDIRECT3DSURFACE9 surface_ = nullptr;			//!< サーフェス
	LPDIRECT3DSURFACE9 stencil_surface_ = nullptr;	//!< ステンシルサーフェス
	D3DVIEWPORT9 view_port_;						//!< ビューポート
	LPDIRECT3DDEVICE9 device_ = nullptr;			//!< デバイス

//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief テクスチャ取得関数
	//! @details
	//! @param void なし
	//! @retval LPDIRECT3DTEXTURE9 テクスチャ
	//----------------------------------------
	LPDIRECT3DTEXTURE9 getpTexture();

	//----------------------------------------
	//! @brief テクスチャ設定関数
	//! @details
	//! @param value テクスチャ
	//! @retval void なし
	//----------------------------------------
	void setTexture(LPDIRECT3DTEXTURE9 value);

	//----------------------------------------
	//! @brief サーフェス取得関数
	//! @details
	//! @param void なし
	//! @retval LPDIRECT3DSURFACE9 サーフェス
	//----------------------------------------
	LPDIRECT3DSURFACE9 getpSurface();

	//----------------------------------------
	//! @brief サーフェス設定関数
	//! @details
	//! @param value サーフェス
	//! @retval void なし
	//----------------------------------------
	void setSurface(LPDIRECT3DSURFACE9 value);

	//----------------------------------------
	//! @brief ステンシルサーフェス取得関数
	//! @details
	//! @param void なし
	//! @retval LPDIRECT3DSURFACE9 ステンシルサーフェス
	//----------------------------------------
	LPDIRECT3DSURFACE9 getpStencilSurface();

	//----------------------------------------
	//! @brief ステンシルサーフェス設定関数
	//! @details
	//! @param value ステンシルサーフェス
	//! @retval void なし
	//----------------------------------------
	void setStencilSurface(LPDIRECT3DSURFACE9 value);

	//----------------------------------------
	//! @brief ビューポート取得関数
	//! @details
	//! @param void なし
	//! @retval D3DVIEWPORT9 ビューポート
	//----------------------------------------
	D3DVIEWPORT9* getpViewPort();

	//----------------------------------------
	//! @brief ビューポート設定関数
	//! @details
	//! @param value ビューポート
	//! @retval void なし
	//----------------------------------------
	void setViewPort(D3DVIEWPORT9 value);

	//----------------------------------------
	//! @brief レンダーターゲット設定関数
	//! @details
	//! @param render_target_index レンダーターゲットインデックス
	//! @retval void なし
	//----------------------------------------
	void setRenderTarget(int render_target_index);

	//----------------------------------------
	//! @brief ステンシルサーフェス&ビューポート設定関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void setStencilSurfaceAndViewPort();


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param texture_width  なし
	//! @param texture_height なし
	//! @param format         フォーマット
	//! @retval void なし
	//----------------------------------------
	void Init(int texture_width, int texture_height, _D3DFORMAT format = D3DFMT_A8R8G8B8);

	//----------------------------------------
	//! @brief 終了関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Uninit();
};



#endif
