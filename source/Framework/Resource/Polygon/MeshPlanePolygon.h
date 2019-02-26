//================================================================================
//!	@file	 MeshPlanePolygon.h
//!	@brief	 メッシュ平面ポリゴンClass
//! @details 
//!	@author  Kai Araki									@date 2017/11/22
//================================================================================
#ifndef	_MESH_PLANE_POLYGON_H_
#define _MESH_PLANE_POLYGON_H_



//****************************************
// インクルード文
//****************************************
#include <string>
#include <vector>

#include <GameEngine/Renderer/Renderer.h>
#include <Tool/Vector3D.h>



//************************************************************														   
//! @brief   メッシュ平面ポリゴンClass
//!
//! @details メッシュ平面のポリゴンClass
//************************************************************
class MeshPlanePolygon
{
//====================
// 定数
//====================
private:
	static const float TEXTURE_WIDTH;		//!< テクスチャ幅
	static const float TEXTURE_HEIGHT;		//!< テクスチャ高さ
	static const float MESH_MIN;			//!< 最小メッシュ


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
	int primitive_num_;									//!< プリミティブ数
	Vec2 mesh_num_;										//!< メッシュ数


//====================
// プロパティ
//====================
public:
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
	//! @brief 高さ取得関数
	//! @details
	//! @param position 座標
	//! @retval float 高さ
	//----------------------------------------
	float getHeight(Vector3D position);


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param mesh_num   メッシュ数
	//! @param mesh_scale メッシュ拡縮
	//! @param color      色
	//! @retval void なし
	//----------------------------------------
	void Init(Vec2 mesh_num = {1.0f, 1.0f},
			  Vec2 mesh_scale = {1.0f, 1.0f},
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
	//! @param mesh_num   メッシュ数
	//! @param mesh_scale メッシュ拡縮
	//! @param color      色
	//! @retval void なし
	//----------------------------------------
	void CreateVertex(Vec2 mesh_num, Vec2 mesh_scale, Color4 color);

	//----------------------------------------
	//! @brief インデックス作成関数
	//! @details
	//! @param mesh_num メッシュ数
	//! @retval void なし
	//----------------------------------------
	void CreateIndex(Vec2 mesh_num);

	//----------------------------------------
	//! @brief プリミティブ数作成関数
	//! @details
	//! @param mesh_num メッシュ数
	//! @retval void なし
	//----------------------------------------
	void CreatePrimitiveNum(Vec2 mesh_num);

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

	//----------------------------------------
	//! @brief 高さ算出関数
	//! @details
	//! @param *position 座標
	//! @param index0	 インデックス0
	//! @param index1	 インデックス1
	//! @param index2	 インデックス2
	//! @retval bool 座標がポリゴン内ならtrue
	//----------------------------------------
	bool CalculationHeight(Vector3D* position, int index0, int index1, int index2);
};



#endif
