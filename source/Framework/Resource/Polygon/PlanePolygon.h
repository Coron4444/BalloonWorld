//================================================================================
//!	@file	 PlanePolygon.h
//!	@brief	 平面ポリゴンClass
//! @details 
//!	@author  Kai Araki									@date 2017/10/16
//================================================================================
#ifndef	_PLANE_POLYGON_H_
#define _PLANE_POLYGON_H_



//****************************************
// クラス宣言
//****************************************
class TextureObject;



//************************************************************														   
//! @brief   平面ポリゴンClass
//!
//! @details 平面のポリゴンClass
//************************************************************
class PlanePolygon
{
//====================
// 定数
//====================
private:
	static const int PRIMITIVE_NUM;		//!< プリミティブ数


//====================
// 変数
//====================
private:
	std::vector<RendererDirectX9::VERTEX_3D> vertex_;	//!< 頂点
	std::vector<WORD> index_;							//!< インデックス
	D3DMATERIAL9 material_;								//!< マテリアル
	LPDIRECT3DVERTEXBUFFER9 vertex_buffer_ = nullptr;	//!< 頂点バッファ
	LPDIRECT3DINDEXBUFFER9 index_buffer_ = nullptr;		//!< インデックスバッファ
	LPDIRECT3DDEVICE9 device_ = nullptr;				//!< デバイス


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief 色取得関数
	//! @details
	//! @param void なし
	//! @retval XColor4 色
	//----------------------------------------
	XColor4 getColor();

	//----------------------------------------
	//! @brief 色設定関数
	//! @details
	//! @param value 色
	//! @retval void なし
	//----------------------------------------
	void setColor(XColor4 value);

	//----------------------------------------
	//! @brief メッシュ数取得関数
	//! @details
	//! @param void なし
	//! @retval unsigned メッシュ数
	//----------------------------------------
	unsigned getMeshNum();

	//----------------------------------------
	//! @brief マテリアル取得関数
	//! @details
	//! @param void なし
	//! @retval D3DMATERIAL9* マテリアル
	//----------------------------------------
	D3DMATERIAL9* getpMaterial();

	//----------------------------------------
	//! @brief UV設定関数
	//! @details
	//! @param *texture    テクスチャオブジェクト
	//! @param pattern_num パターン数
	//! @retval D3DMATERIAL9* マテリアル
	//----------------------------------------
	void setUV(TextureObject* texture, int pattern_num = 0);


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param mesh_scale メッシュ拡縮
	//! @param color      色
	//! @retval void なし
	//----------------------------------------
	void Init(Vec2 mesh_scale = {1.0f, 1.0f},
			  XColor4 color = {1.0f, 1.0f, 1.0f, 1.0f});

	//----------------------------------------
	//! @brief 終了関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Uninit();

	//----------------------------------------
	//! @brief 描画関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Draw();

	//----------------------------------------
	//! @brief ワイヤーフレームで描画関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void DrawWireFrame();

private:
	//----------------------------------------
	//! @brief 頂点作成関数
	//! @details
	//! @param mesh_scale メッシュ拡縮
	//! @param color      色
	//! @retval void なし
	//----------------------------------------
	void CreateVertex(Vec2 mesh_scale, Color4 color);

	//----------------------------------------
	//! @brief インデックス作成関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void CreateIndex();

	//----------------------------------------
	//! @brief マテリアル作成関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void CreateMaterial();

	//----------------------------------------
	//! @brief VRAMへアクセス関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void AccessVRAM();

	//----------------------------------------
	//! @brief 頂点バッファに登録関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void RegistrationVertex();

	//----------------------------------------
	//! @brief インデックスバッファに登録関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void RegistrationIndex();
};



#endif
