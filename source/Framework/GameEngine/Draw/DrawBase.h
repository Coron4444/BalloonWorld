//================================================================================
//!	@file	 DrawBase.h
//!	@brief	 描画BaseClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================
#ifndef	_DRAW_BASE_H_
#define _DRAW_BASE_H_



//****************************************
// インクルード文
//****************************************
#include "../ComponentBase.h"
#include "DrawManager/DrawOrderList.h"
#include "DrawManager/DrawCommonData.h"

#include <Tool/Vector3D.h>



//************************************************************														   
//! @brief   描画BaseClass
//!
//! @details 描画のBaseClass
//************************************************************
class DrawBase : public ComponentBase
{
//====================
// 変数
//====================
private:
	DrawOrderList order_list_;				//!< 描画注文リスト
	DrawCommonData* common_data_ = nullptr;	//!< 描画共通データ


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
	virtual unsigned getObjectNum() = 0;

	//----------------------------------------
	//! @brief メッシュ数取得関数
	//! @details
	//! @param object_index オブジェクトインデックス
	//! @retval unsigned メッシュ数
	//----------------------------------------
	virtual unsigned getMeshNum(unsigned object_index) = 0;

	//----------------------------------------
	//! @brief ボーン数取得関数
	//! @details
	//! @param object_index オブジェクトインデックス
	//! @param mesh_index   メッシュインデックス
	//! @retval unsigned ボーン数
	//----------------------------------------
	virtual unsigned getBoneNum(unsigned object_index,
								unsigned mesh_index) = 0;

	//----------------------------------------
	//! @brief ワールド行列取得関数
	//! @details
	//! @param object_index オブジェクトインデックス
	//! @retval MATRIX* ワールド行列
	//----------------------------------------
	virtual MATRIX* getpMatrix(unsigned object_index) = 0;

	//----------------------------------------
	//! @brief ボーン行列取得関数
	//! @details
	//! @param object_index オブジェクトインデックス
	//! @param mesh_index   メッシュインデックス
	//! @param bone_index   ボーンインデックス
	//! @retval MATRIX* ボーン行列
	//----------------------------------------
	virtual MATRIX* getpBoneMatrix(unsigned object_index,
								   unsigned mesh_index,
								   unsigned bone_index) = 0;

	//----------------------------------------
	//! @brief マテリアル取得関数
	//! @details
	//! @param object_index オブジェクトインデックス
	//! @param mesh_index   メッシュインデックス
	//! @retval D3DMATERIAL9* マテリアル
	//----------------------------------------
	virtual D3DMATERIAL9* getpMaterial(unsigned object_index,
									   unsigned mesh_index) = 0;

	//----------------------------------------
	//! @brief ディヒューズテクスチャ取得関数
	//! @details
	//! @param object_index オブジェクトインデックス
	//! @param mesh_index   メッシュインデックス
	//! @retval LPDIRECT3DTEXTURE9 ディヒューズテクスチャ
	//----------------------------------------
	virtual LPDIRECT3DTEXTURE9 getpDiffuseTexture(unsigned object_index,
												  unsigned mesh_index) = 0;

	 //----------------------------------------
	 //! @brief 法線テクスチャ取得関数
	 //! @details
	 //! @param object_index オブジェクトインデックス
	 //! @param mesh_index   メッシュインデックス
	 //! @retval RendererInterface* 法線テクスチャ
	 //----------------------------------------
	virtual LPDIRECT3DTEXTURE9 getpNormalTexture(unsigned object_index,
												 unsigned mesh_index) = 0;

	//----------------------------------------
	//! @brief 描画注文リスト取得関数
	//! @details
	//! @param void なし
	//! @retval DrawOrderList* 描画注文リスト
	//----------------------------------------
	DrawOrderList* getpDrawOrderList();

	//----------------------------------------
	//! @brief 描画共通データ取得関数
	//! @details
	//! @param void なし
	//! @retval DrawCommonData* 描画共通データ
	//----------------------------------------
	DrawCommonData* getpDrawCommonData();

	//----------------------------------------
	//! @brief 描画共通データ設定関数
	//! @details
	//! @param value 描画共通データ
	//! @retval void なし
	//----------------------------------------
	void setDrawCommonData(DrawCommonData* value);


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 仮想デストラクタ
	//! @details
	//! @param void なし
	//----------------------------------------
	virtual ~DrawBase() = 0;

	//----------------------------------------
	//! @brief 描画関数
	//! @details
	//! @param object_index オブジェクトインデックス
	//! @param mesh_index   メッシュインデックス
	//! @retval void なし
	//----------------------------------------
	virtual void Draw(unsigned object_index, unsigned mesh_index) = 0;

	//----------------------------------------
	//! @brief オブジェクト前設定関数
	//! @details
	//! @param object_index オブジェクトインデックス
	//! @retval void なし
	//----------------------------------------
	virtual void ObjectSettingBefore(unsigned object_index) = 0;

	//----------------------------------------
	//! @brief オブジェクト後設定関数
	//! @details
	//! @param object_index オブジェクトインデックス
	//! @retval void なし
	//----------------------------------------
	virtual void ObjectSettingAfter(unsigned object_index) = 0;
};



#endif