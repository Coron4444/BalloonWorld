//================================================================================
//!	@file	 TutorialLogoDraw.h
//!	@brief	 チュートリアルロゴ描画Class
//! @details 
//!	@author  Kai Araki									@date 2018/09/02
//================================================================================
#ifndef	_TUTORIAL_LOGO_DRAW_H_
#define _TUTORIAL_LOGO_DRAW_H_



//****************************************
// インクルード文
//****************************************
#include <string>

#include <GameEngine/Draw/DrawNull.h>
#include <Resource/Texture/TextureManager/TextureManager.h>



//****************************************
// クラス宣言
//****************************************
class TutorialLogo;
class PlanePolygon;



//************************************************************														   
//! @brief   クリアロゴ描画Class
//!
//! @details クリアロゴの描画Class
//************************************************************
class TutorialLogoDraw : public DrawNull
{
//====================
// 定数
//====================
private:
	static const unsigned TEXTURE_NUM = 2;				//!< テクスチャ数
	static const std::string TEXTURE_NAME[TEXTURE_NUM];	//!< テクスチャ名
	static const float SCALE;							//!< 拡縮


//====================
// 変数
//====================
private:
	TutorialLogo* tutorial_logo_ = nullptr;						//!< チュートリアル
	TextureObject* diffuse_texture_[TEXTURE_NUM] = {nullptr};	//!< ディヒューズテクスチャ
	PlanePolygon* plane_polygon_ = nullptr;						//!< 平面ポリゴン


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