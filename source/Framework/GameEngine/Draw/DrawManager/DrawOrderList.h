//================================================================================
//!	@file	 DrawOrderList.h
//!	@brief	 描画注文リストClass
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================
#ifndef	_DRAW_ORDER_LIST_H_
#define _DRAW_ORDER_LIST_H_



//****************************************
// インクルード文
//****************************************
#include "Shader/ShaderManager/ShaderManager.h"



//************************************************************														   
//! @brief   描画注文リストClass
//!
//! @details 描画に関する注文リストClass
//************************************************************
class DrawOrderList
{
//====================
// 列挙型定義
//====================
public:
	// 描画タイプ
	enum DrawType
	{
		NONE = -1,
		OPACITY,
		TRANSPARENCY,
		TWO_DIMENSIONAL,
		MAX
	};

	
//====================
// 定数
//====================
public:
	static const unsigned RENDER_TARGET_MAIN = 1 << 0;
	static const unsigned RENDER_TARGET_SHADOW_MAP = 1 << 1;


//====================
// 変数
//====================
private:
	DrawType draw_type_ = DrawType::OPACITY;			//!< 描画の種類
	DrawType temp_change_draw_type_ = DrawType::NONE;	//!< 一時変更描画の種類
	ShaderManager::VertexShaderType vertex_shader_type_ = ShaderManager::VertexShaderType::FIXED;	//!< 頂点シェーダータイプ
	ShaderManager::PixelShaderType pixel_shader_type_ = ShaderManager::PixelShaderType::FIXED;		//!< ピクセルシェーダータイプ
	BitFlag render_target_flag_;		//!< レンダーターゲットフラグ
	bool is_billboard_ = false;			//!< ビルボードフラグ
	bool is_lighting_ = true;			//!< ラインティングフラグ
	bool is_animation_ = false;			//!< アニメーションフラグ
	int layer_num_ = 0;					//!< レイヤー数


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief 頂点シェーダーの種類取得関数
	//! @details
	//! @param void なし
	//! @retval ShaderManager::VertexShaderType 頂点シェーダーの種類
	//----------------------------------------
	ShaderManager::VertexShaderType getVertexShaderType();
	
	//----------------------------------------
	//! @brief 頂点シェーダータイプ設定関数
	//! @details
	//! @param value 頂点シェーダータイプ
	//! @retval void なし
	//----------------------------------------
	void setVertexShaderType(ShaderManager::VertexShaderType value);
	
	//----------------------------------------
	//! @brief ピクセルシェーダーの種類取得関数
	//! @details
	//! @param void なし
	//! @retval ShaderManager::PixelShaderType ピクセルシェーダーの種類
	//----------------------------------------
	ShaderManager::PixelShaderType getPixelShaderType();
	
	//----------------------------------------
	//! @brief ピクセルシェーダータイプ設定関数
	//! @details
	//! @param value ピクセルシェーダータイプ
	//! @retval void なし
	//----------------------------------------
	void setPixelShaderType(ShaderManager::PixelShaderType value);
	
	//----------------------------------------
	//! @brief 描画タイプ取得関数
	//! @details
	//! @param void なし
	//! @retval DrawType 描画タイプ
	//----------------------------------------
	DrawType getDrawType();
	
	//----------------------------------------
	//! @brief 描画タイプ設定関数
	//! @details
	//! @param value 描画タイプ
	//! @retval void なし
	//----------------------------------------
	void setDrawType(DrawType value);

	//----------------------------------------
	//! @brief 一時変更描画タイプ取得関数
	//! @details
	//! @param void なし
	//! @retval DrawType 一時変更描画タイプ
	//----------------------------------------
	DrawType getTempChangeDrawType();

	//----------------------------------------
	//! @brief 一時変更描画タイプ設定関数
	//! @details
	//! @param value 一時変更描画タイプ
	//! @retval void なし
	//----------------------------------------
	void setTempChangeDrawType(DrawType value);
	
	//----------------------------------------
	//! @brief レンダーターゲットフラグ取得関数
	//! @details
	//! @param void なし
	//! @retval BitFlag* レンダーターゲットフラグ
	//----------------------------------------
	BitFlag* getpRenderTargetFlag();
	
	//----------------------------------------
	//! @brief ビルボードフラグ取得関数
	//! @details
	//! @param void なし
	//! @retval bool ビルボードフラグ
	//----------------------------------------
	bool getIsBillboard();
	
	//----------------------------------------
	//! @brief ビルボードフラグ設定関数
	//! @details
	//! @param value ビルボードフラグ
	//! @retval void なし
	//----------------------------------------
	void setIsBillboard(bool value);
	
	//----------------------------------------
	//! @brief ライティングフラグ取得関数
	//! @details
	//! @param void なし
	//! @retval bool ライティングフラグ
	//----------------------------------------
	bool getIsLighting();
	
	//----------------------------------------
	//! @brief ライティングフラグ設定関数
	//! @details
	//! @param value ライティングフラグ
	//! @retval void なし
	//----------------------------------------
	void setIsLighting(bool value);
	
	//----------------------------------------
	//! @brief アニメーションフラグ取得関数
	//! @details
	//! @param void なし
	//! @retval bool アニメーションフラグ
	//----------------------------------------
	bool getIsAnimation();

	//----------------------------------------
	//! @brief アニメーションフラグ設定関数
	//! @details
	//! @param value アニメーションフラグ
	//! @retval void なし
	//----------------------------------------
	void setIsAnimation(bool value);

	//----------------------------------------
	//! @brief レイヤー数取得関数
	//! @details
	//! @param void なし
	//! @retval int レイヤー数
	//----------------------------------------
	int getLayerNum();
	
	//----------------------------------------
	//! @brief レイヤー数設定関数
	//! @details
	//! @param value レイヤー数
	//! @retval void なし
	//----------------------------------------
	void setLayerNum(int value);
};



#endif