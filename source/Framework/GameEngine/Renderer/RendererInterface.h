//================================================================================
//!	@file	 RendererInterface.h
//!	@brief	 レンダラーInterfaceClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================
#ifndef	_RENDERER_INTERFACE_H_
#define _RENDERER_INTERFACE_H_



//****************************************
// インクルード文
//****************************************



//************************************************************														   
//! @brief   レンダラーInterfaceClass
//!
//! @details レンダラーのInterfaceClass
//************************************************************
class RendererInterface
{
//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 仮想デストラクタ
	//! @details
	//! @param void なし
	//----------------------------------------
	virtual ~RendererInterface() = 0;
	
	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param hInstance	  インスタンスハンドル
	//! @param hWnd			  Windowsハンドル
	//! @param is_full_screen フルスクリーンフラグ
	//! @param window_width	  ウィンドウ幅
	//! @param window_height  ウィンドウ高さ
	//! @retval bool 初期化成功の有無
	//----------------------------------------
	virtual bool Init(HINSTANCE hInstance, HWND hWnd, BOOL is_full_screen,
					  int window_width, int window_height) = 0;

	//----------------------------------------
	//! @brief 終了関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void Uninit() = 0;

	//----------------------------------------
	//! @brief 描画開始関数
	//! @details
	//! @param clear_color クリア色
	//! @retval bool 描画開始成功の有無
	//----------------------------------------
	virtual bool DrawBegin(XColor4 clear_color = {0.123f, 0.25f, 0.75f, 1.0f}) = 0;

	//----------------------------------------
	//! @brief クリア無描画開始関数
	//! @details
	//! @param void なし
	//! @retval bool 描画開始成功の有無
	//----------------------------------------
	virtual bool NoClearDrawBegin() = 0;

	//----------------------------------------
	//! @brief 描画終了関数
	//! @details
	//! @param is_begin_scene 描画開始成功フラグ
	//! @retval void なし
	//----------------------------------------
	virtual void DrawEnd(bool is_begin_scene) = 0;

	//----------------------------------------
	//! @brief バックバッファをフロントバッファに反映関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	virtual void Present() = 0;
};



#endif



