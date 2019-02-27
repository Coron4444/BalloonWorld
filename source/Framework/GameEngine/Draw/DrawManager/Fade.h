//================================================================================
//!	@file	 Fade.h
//!	@brief	 フェードClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================
#ifndef	_FADE_H_
#define _FADE_H_



//****************************************
// インクルード文
//****************************************
#include "../DrawNull.h"



//****************************************
// クラス宣言
//****************************************
class PlanePolygon;
class Transform;
class TextureObject;



//************************************************************														   
//! @brief   フェードClass
//!
//! @details フェードのClass
//************************************************************
class Fade : public DrawNull
{
//====================
// 列挙型定義
//====================
public:
	enum class Type
	{
		NONE = -1,
		NORMAL,
		TRANSITION_01,
		MAX
	};

	enum class State
	{
		NONE = -1,
		FADE_IN,
		FADE_OUT,
		MAX
	};


//====================
// 定数
//====================
public:
	static const std::string TEXTURE_NAME_LOAD;				//!< Loadテクスチャ名
	static const std::string TEXTURE_NAME_TRANSITION_01;	//!< テクスチャ名


//====================
// 変数
//====================
private:
	Type type_;										//!< タイプ
	State state_;									//!< ステート
	PlanePolygon* plane_polygon_ = nullptr;			//!< 板ポリゴン
	Transform* transform_ = nullptr;				//!< 状態
	TextureObject* load_texture_ = nullptr;			//!< Loadテクスチャオブジェクト
	TextureObject* transition01_texture_ = nullptr;	//!< テクスチャオブジェクト
	XColor4 color_;									//!< 色
	float speed_;									//!< フェード速度
	bool end_flag_ = true;							//!< 終了フラグ
	Interpolation<float> inter_container_;			//!< 補間コンテナ
	Interpolation<float>::Iterator inter_iter_;		//!< 補間イテレータ


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief 行列取得関数
	//! @details
	//! @param object_index オブジェクトインデックス
	//! @retval MATRIX* 行列
	//----------------------------------------
	MATRIX* getpMatrix(unsigned object_index) override;

	//----------------------------------------
	//! @brief マテリアル取得関数
	//! @details
	//! @param object_index オブジェクトインデックス
	//! @param mesh_index   メッシュインデックス
	//! @retval D3DMATERIAL9* マテリアル
	//----------------------------------------
	D3DMATERIAL9* getpMaterial(unsigned object_index, unsigned mesh_index) override;

	//----------------------------------------
	//! @brief タイプ取得関数
	//! @details
	//! @param void なし
	//! @retval Type* タイプ
	//----------------------------------------
	Type* getpType();

	//----------------------------------------
	//! @brief ステート取得関数
	//! @details
	//! @param void なし
	//! @retval State* ステート
	//----------------------------------------
	State* getpState();

	//----------------------------------------
	//! @brief 終了フラグ取得関数
	//! @details
	//! @param void なし
	//! @retval bool 終了フラグ
	//----------------------------------------
	bool getpEndFlag();

	//----------------------------------------
	//! @brief 状態取得関数
	//! @details
	//! @param void なし
	//! @retval Transform* 状態
	//----------------------------------------
	Transform* getpTransform();

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
	void Init();

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

	//----------------------------------------
	//! @brief スタート関数
	//! @details
	//! @param type  タイプ
	//! @param state ステート
	//! @param size  拡縮
	//! @param color 色
	//! @param speed フェード速度
	//! @retval void なし
	//----------------------------------------
	void Start(Type type, State state, Vec2 size, XColor4 color, float speed);
};



#endif