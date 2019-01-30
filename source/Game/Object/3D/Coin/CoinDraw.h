//================================================================================
//!	@file	 CoinDraw.h
//!	@brief	 コイン描画Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================
#ifndef	_COIN_DRAW_H_
#define _COIN_DRAW_H_



//****************************************
// インクルード文
//****************************************
#include <string>

#include <GameEngine/Draw/DrawNull.h>
#include <Resource/Texture/TextureManager/TextureManager.h>



//****************************************
// クラス宣言
//****************************************
class Coin;
class PlanePolygon;



//************************************************************														   
//! @brief   コインロゴ描画Class
//!
//! @details コインロゴの描画Class
//************************************************************
class CoinDraw : public DrawNull
{
//====================
// 定数
//====================
private:
	static const std::string TEXTURE_NAME;	//!< テクスチャ名
	

//====================
// 変数
//====================
private:
	Coin* coin_;						//!< コイン
	PlanePolygon* plane_polygon_;		//!< 平面ポリゴン
	TextureObject* diffuse_texture_;	//!< ディヒューズテクスチャ


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
	//! @brief 更新関数
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Update() override;

	//----------------------------------------
	//! @brief 描画関数
	//! @param[in] object_index オブジェクトインデックス
	//! @param[in] mesh_index   メッシュインデックス
	//! @retval void なし
	//----------------------------------------
	void Draw(unsigned object_index, unsigned mesh_index) override;
};



#endif