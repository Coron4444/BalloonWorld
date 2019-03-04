//================================================================================
//!	@file	 CubePolygon.h
//!	@brief	 キューブポリゴンClass
//! @details 
//!	@author  Kai Araki									@date 2017/10/16
//================================================================================
#ifndef	_CUBE_POLYGON_H_
#define _CUBE_POLYGON_H_



//************************************************************														   
//! @brief   キューブポリゴンClass
//!
//! @details キューブのポリゴンClass
//************************************************************
class CubePolygon
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


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param color 色
	//! @retval void なし
	//----------------------------------------
	void Init(XColor4 color = {1.0f, 1.0f, 1.0f, 1.0f});

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
	//! @param color 色
	//! @retval void なし
	//----------------------------------------
	void CreateVertex(Color4 color);

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
