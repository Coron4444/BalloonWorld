//================================================================================
//!	@file	 DrawCommonData.h
//!	@brief	 描画共通データClass
//! @details 
//!	@author  Kai Araki									@date 2019/01/28
//================================================================================
#ifndef	_DRAW_COMMON_DATA_H_
#define _DRAW_COMMON_DATA_H_



//****************************************
// インクルード文
//****************************************
#include "RenderTexture.h"

#include <Tool/Vector3D.h>



//************************************************************														   
//! @brief   描画共通データClass
//!
//! @details 描画の共通データClass
//************************************************************
class DrawCommonData
{	
//====================
// 変数
//====================
private:
	Vector3D directional_light_vector_ = {0.5f, -1.0f, 0.8f};	//!< 拡散反射照明ベクトル
	RenderTexture main_;			//!< メイン用レンダーテクスチャ
	RenderTexture motion_blur_;		//!< モーションブラー用レンダーテクスチャ


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief 拡散反射照明ベクトル取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D* 拡散反射照明ベクトル
	//----------------------------------------
	Vector3D* getpDirectionalLightVector();

	//----------------------------------------
	//! @brief メイン用レンダーテクスチャ取得関数
	//! @details
	//! @param void なし
	//! @retval RenderTexture* メイン用レンダーテクスチャ
	//----------------------------------------
	RenderTexture* getpRenderTextureMain();

	//----------------------------------------
	//! @brief モーションブラー用レンダーテクスチャ取得関数
	//! @details
	//! @param void なし
	//! @retval RenderTexture* モーションブラー用レンダーテクスチャ
	//----------------------------------------
	RenderTexture* getpRenderTextureMotionBlur();

//====================
// 関数定義
//====================
public:
	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Init();

	//----------------------------------------
	//! @brief 終了関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Uninit();
};



#endif