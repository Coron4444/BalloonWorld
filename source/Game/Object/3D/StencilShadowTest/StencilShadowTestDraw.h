//================================================================================
//!	@file	 StencilShadowTestDraw.h
//!	@brief	 ステンシルシャドウテスト描画Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================
#ifndef	_STENCIL_SHADOW_TEST_DRAW_H_
#define _STENCIL_SHADOW_TEST_DRAW_H_



//****************************************
// インクルード文
//****************************************
#include <string>

#include <GameEngine/Draw/DrawNull.h>



//****************************************
// クラス宣言
//****************************************
class PlanePolygon;
class ModelXObject;



//************************************************************														   
//! @brief   ステンシルシャドウテスト描画Class
//!
//! @details ステンシルシャドウテストの描画Class
//************************************************************
class StencilShadowTestDraw : public DrawNull
{
//====================
// 定数
//====================
private:
	static const std::string MODEL_NAME;		//!< モデル名


//====================
// 変数
//====================
private:
	ModelXObject* player_model_;			//!< モデルオブジェクト
	PlanePolygon* plane_polygon_;			//!< 板ポリゴン	
	Transform plane_polygon_transform_;		//!< 板ポリゴン用変形


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief オブジェクト数取得関数
	//! @details
	//! @param void なし
	//! @retval unsigned オブジェクト数
	//----------------------------------------
	unsigned getObjectNum() override;

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

	//----------------------------------------
	//! @brief オブジェクト前設定関数
	//! @details
	//! @param object_index オブジェクトインデックス
	//! @retval void なし
	//----------------------------------------
	void ObjectSettingBefore(unsigned object_index) override;

	//----------------------------------------
	//! @brief オブジェクト後設定関数
	//! @details
	//! @param object_index オブジェクトインデックス
	//! @retval void なし
	//----------------------------------------
	void ObjectSettingAfter(unsigned object_index) override;
};



#endif