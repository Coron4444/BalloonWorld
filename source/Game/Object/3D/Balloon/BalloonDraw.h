//================================================================================
//!	@file	 BalloonDraw.h
//!	@brief	 風船描画Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/05
//================================================================================
#ifndef	_BALLOON_DRAW_H_
#define _BALLOON_DRAW_H_



//****************************************
// インクルード文
//****************************************
#include <string>

#include <GameEngine/Draw/DrawNull.h>



//****************************************
// クラス宣言
//****************************************
class Balloon;
class MdBinObject;
class ModelXObject;



//************************************************************														   
//! @brief   風船描画Class
//!
//! @details 風船の描画Class
//************************************************************
class BalloonDraw : public DrawNull
{
//====================
// 定数
//====================
private:
	static const std::string BALLOON_MODEL_NAME;		//!< 風船モデル名
	static const std::string BALLOON_LINE_MODEL_NAME;	//!< 風船の線モデル名


//====================
// 変数
//====================
private:
	Balloon* balloon_;	//!< 風船
	ModelXObject* balloon_object_;			//!< 風船オブジェクト
	ModelXObject* balloon_line_object_;		//!< 風船の線オブジェクト
	XColor4 color_;							//!< 色


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
};



#endif