//================================================================================
//!	@file	 PlayerDraw.h
//!	@brief	 プレイヤー描画Class
//! @details 
//!	@author  Kai Araki									@date 2018/03/27
//================================================================================
#ifndef	_PLAYER_DRAW_H_
#define _PLAYER_DRAW_H_



//****************************************
// インクルード文
//****************************************
#include <string>

#include <GameEngine/Draw/DrawNull.h>



//****************************************
// クラス宣言
//****************************************
class ModelXObject;
class MdBinObject;
class TextureObject;
class Player;


//************************************************************														   
//! @brief   プレイヤー描画Class
//!
//! @details プレイヤーの描画Class
//************************************************************
class PlayerDraw : public DrawNull
{
//====================
// 定数
//====================
private:
	static const std::string MODEL_NAME;				//!< モデル名
	static const std::string TEXTURE_PATH;				//!< モデルフォルダのテクスチャパス
	static const std::string NORMAL_TEXTURE_MODEL;		//!< 法線テクスチャ(モデル)
	static const std::string NORMAL_TEXTURE_SWORD;		//!< 法線テクスチャ(剣)


//====================
// 変数
//====================
private:
	ModelXObject* player_model_ = nullptr;			//!< モデルオブジェクト
	TextureObject* normal_texture_[2];				//!< テクスチャオブジェクト
	MdBinObject* test_object_ = nullptr;			//!< テスト用オブジェクト
	int pattern_num_ = 0;
	Player* player_ = nullptr;

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
	//! @brief ボーン数取得関数
	//! @details
	//! @param object_index オブジェクトインデックス
	//! @param mesh_index   メッシュインデックス
	//! @retval unsigned ボーン数
	//----------------------------------------
	unsigned getBoneNum(unsigned object_index,
								unsigned mesh_index) override;

	//----------------------------------------
	//! @brief ワールド行列取得関数
	//! @details
	//! @param object_index オブジェクトインデックス
	//! @retval MATRIX* ワールド行列
	//----------------------------------------
	MATRIX* getpMatrix(unsigned object_index) override;

	//----------------------------------------
	//! @brief ボーン行列取得関数
	//! @details
	//! @param object_index オブジェクトインデックス
	//! @param mesh_index   メッシュインデックス
	//! @param bone_index   ボーンインデックス
	//! @retval MATRIX* ボーン行列
	//----------------------------------------
	MATRIX* getpBoneMatrix(unsigned object_index,
								   unsigned mesh_index,
								   unsigned bone_index) override;

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

	 //----------------------------------------
	 //! @brief 法線テクスチャ取得関数
	 //! @details
	 //! @param object_index オブジェクトインデックス
	 //! @param mesh_index   メッシュインデックス
	 //! @retval RendererInterface* 法線テクスチャ
	 //----------------------------------------
	LPDIRECT3DTEXTURE9 getpNormalTexture(unsigned object_index,
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
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Update() override;

	//----------------------------------------
	//! @brief 描画関数
	//! @param object_index オブジェクトインデックス
	//! @param mesh_index   メッシュインデックス
	//! @retval void なし
	//----------------------------------------
	void Draw(unsigned object_index, unsigned mesh_index) override;
};



#endif