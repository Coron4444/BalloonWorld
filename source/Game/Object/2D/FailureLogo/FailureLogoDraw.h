//================================================================================
//!	@file	 FailureLogoDraw.h
//!	@brief	 失敗ロゴ描画Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================
#ifndef	_FAILURE_LOGO_DRAW_H_
#define _FAILURE_LOGO_DRAW_H_



//****************************************
// インクルード文
//****************************************
#include <string>

#include <GameEngine/Draw/DrawNull.h>
#include <Resource/Texture/TextureManager/TextureManager.h>



//****************************************
// クラス宣言
//****************************************
class PlanePolygon;



//************************************************************														   
//! @brief   失敗ロゴ描画Class
//!
//! @details 失敗ロゴの描画Class
//************************************************************
class FailureLogoDraw : public DrawNull
{
//====================
// 定数
//====================
private:
	static const std::string TEXTURE_NAME;	//!< テクスチャ名
	static const float SCALE;				//!< 拡縮


//====================
// 変数
//====================
private:
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
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Init() override;

	//----------------------------------------
	//! @brief 終了関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Uninit() override;

	//----------------------------------------
	//! @brief 描画関数
	//! @details
	//! @param object_index オブジェクトインデックス
	//! @param mesh_index   メッシュインデックス
	//! @retval void なし
	//----------------------------------------
	void Draw(unsigned object_index, unsigned mesh_index) override;
};



#endif