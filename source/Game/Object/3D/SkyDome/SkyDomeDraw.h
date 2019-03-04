//================================================================================
//!	@file	 SkyDomeDraw.h
//!	@brief	 天球描画Class
//! @details 
//!	@author  Kai Araki									@date 2018/05/15
//================================================================================
#ifndef	_SKY_DOME_DRAW_H_
#define _SKY_DOME_DRAW_H_



//****************************************
// インクルード文
//****************************************
#include <GameEngine/Draw/DrawNull.h>



//****************************************
// クラス宣言
//****************************************
class ModelXObject;



//************************************************************														   
//! @brief   天球描画Class
//!
//! @details 天球の描画Class
//************************************************************
class SkyDomeDraw : public DrawNull
{
//====================
// 定数
//====================
private:
	static const std::string MODEL_NAME;	//!< モデル名
	static const float SCALE;				//!< 拡縮


//====================
// 変数
//====================
private:
	ModelXObject* sky_dome_model_;		//!< 天球モデル


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief メッシュ数取得関数
	//! @details
	//! @param object_index オブジェクトインデックス
	//! @retval unsigned メッシュ数
	//----------------------------------------
	unsigned getMeshNum(unsigned object_index) override;

	//----------------------------------------
	//! @brief ワールド行列取得関数
	//! @details
	//! @param object_index オブジェクトインデックス
	//! @retval MATRIX* ワールド行列
	//----------------------------------------
	MATRIX* getpMatrix(unsigned object_index) override;

	//----------------------------------------
	//! @brief マテリアル取得関数
	//! @details
	//! @param object_index オブジェクトインデックス
	//! @param mesh_index   メッシュインデックス
	//! @retval D3DMATERIAL9* マテリアル
	//----------------------------------------
	D3DMATERIAL9* getpMaterial(unsigned object_index,
							   unsigned mesh_index) override;

	//----------------------------------------
	//! @brief ディヒューズテクスチャ取得関数
	//! @details
	//! @param object_index オブジェクトインデックス
	//! @param mesh_index   メッシュインデックス
	//! @retval LPDIRECT3DTEXTURE9 ディヒューズテクスチャ
	//----------------------------------------
	LPDIRECT3DTEXTURE9 getpDiffuseTexture(unsigned object_index,
										  unsigned mesh_index) override;


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 初期化関数
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Init() override;

	//----------------------------------------
	//! @brief 終了関数
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Uninit() override;

	//----------------------------------------
	//! @brief 描画関数
	//! @param object_index オブジェクトインデックス
	//! @param mesh_index   メッシュインデックス
	//! @retval void なし
	//----------------------------------------
	void Draw(unsigned object_index, unsigned mesh_index) override;
};



#endif