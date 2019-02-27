//================================================================================
//!	@file	 TimeDraw.h
//!	@brief	 時間描画Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================
#ifndef	_TIME_DRAW_H_
#define _TIME_DRAW_H_



//****************************************
// インクルード文
//****************************************
#include <GameEngine/Draw/DrawNull.h>



//****************************************
// クラス宣言
//****************************************
class Time;
class NumbersPolygon;
class PlanePolygon;



//************************************************************														   
//! @brief   時間描画Class
//!
//! @details 時間の描画Class
//************************************************************
class TimeDraw : public DrawNull
{
//====================
// 定数
//====================
private:
	static const std::string TEXTURE_NAME;	//!< テクスチャ名
	static const std::string TEXTURE_NAME2;	//!< テクスチャ名
	static const int TIME_DIGITS_NUM;		//!< 時間桁数
	static const Vec2 TIME_POSITION;		//!< 時間座標
	static const Vec2 TIME_SCALE;			//!< 時間拡縮
	static const XColor4 TIME_COLOR;		//!< 時間色


//====================
// 変数
//====================
private:
	Time* time_;						//!< 時間
	NumbersPolygon* numbers_polygon_;	//!< 数字群ポリゴン
	PlanePolygon* plane_polygon_;		//!< 平面ポリゴン
	TextureObject* texture_;			//!< テクスチャオブジェクト
	TextureObject* texture_2;			//!< テクスチャオブジェクト


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
	virtual unsigned getObjectNum() override;

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
	//! @brief 更新関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Update() override;

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