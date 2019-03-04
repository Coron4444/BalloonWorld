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



//****************************************
// クラス宣言
//****************************************
class Camera;


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
	RenderTexture shadow_map_;		//!< シャドウマップ用レンダーテクスチャ
	RenderTexture motion_blur_;		//!< モーションブラー用レンダーテクスチャ
	Camera* camera_shadow_map_;		//!< シャドウマップ用カメラ



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
	//! @brief シャドウマップ用レンダーテクスチャ取得関数
	//! @details
	//! @param void なし
	//! @retval RenderTexture* シャドウマップ用レンダーテクスチャ
	//----------------------------------------
	RenderTexture* getpRenderTextureShadowMap();

	//----------------------------------------
	//! @brief モーションブラー用レンダーテクスチャ取得関数
	//! @details
	//! @param void なし
	//! @retval RenderTexture* モーションブラー用レンダーテクスチャ
	//----------------------------------------
	RenderTexture* getpRenderTextureMotionBlur();

	//----------------------------------------
	//! @brief シャドウマップ用カメラ取得関数
	//! @details
	//! @param void なし
	//! @retval Camera* シャドウマップ用カメラ
	//----------------------------------------
	Camera* getpCameraShadowMap();

	//----------------------------------------
	//! @brief シャドウマップ用カメラ取得関数
	//! @details
	//! @param value シャドウマップ用カメラ
	//! @retval void なし 
	//----------------------------------------
	void setCameraShadowMap(Camera* value);


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