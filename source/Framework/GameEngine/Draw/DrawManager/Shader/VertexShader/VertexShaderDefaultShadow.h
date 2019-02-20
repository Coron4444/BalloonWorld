//================================================================================
//!	@file	 VertexShaderDefaultShadow.h
//!	@brief	 デフォルト影頂点シェーダーClass
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================
#ifndef	_VERTEX_SHADER_DEFAULT_SHADOW_H_
#define _VERTEX_SHADER_DEFAULT_SHADOW_H_



//****************************************
// インクルード文
//****************************************
#include "VertexShaderNull.h"

#include <Tool/Vector3D.h>



//************************************************************														   
//! @brief   デフォルト影頂点シェーダーClass
//!
//! @details デフォルト影の頂点シェーダーClass
//************************************************************
class VertexShaderDefaultShadow : public VertexShaderNull
{
//====================
// 定数
//====================
private:
	static const char* PATH;					//!< ファイルパス
	static const float OFF_SET_X;				//!< X座標オフセット値
	static const float OFF_SET_Y;				//!< Y座標オフセット値
	static const MATRIX TEXTURE_PROJECTION;		//!< テクスチャ座標


//====================
// 変数
//====================
private:
	MATRIX math_matrix_;	//!< 計算用行列


//====================
// 関数
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

	//----------------------------------------
	//! @brief オブジェクト設定関数
	//! @details
	//! @param *draw        描画基底クラス
	//! @param *camera      カメラ
	//! @param object_index 描画オブジェクトインデックス
	//! @retval void なし
	//----------------------------------------
	void ObjectSetting(DrawBase* draw, Camera* camera, unsigned object_index);

	//----------------------------------------
	//! @brief メッシュ設定関数
	//! @details
	//! @param *draw        描画基底クラス
	//! @param *camera      カメラ
	//! @param object_index 描画オブジェクトインデックス
	//! @param mesh_index   メッシュインデックス
	//! @retval void なし
	//----------------------------------------
	void MeshSetting(DrawBase* draw, Camera* camera,
					 unsigned object_index, unsigned mesh_index);
};



#endif
