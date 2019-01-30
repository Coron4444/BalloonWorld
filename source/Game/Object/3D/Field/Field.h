//================================================================================
//!	@file	 Field.h
//!	@brief	 地面Class
//! @details 
//!	@author  Kai Araki									@date 2018/05/15
//================================================================================
#ifndef	_FIELD_H_
#define _FIELD_H_



//****************************************
// インクルード文
//****************************************
#include <GameEngine/GameObject/GameObjectNull.h>
#include <Resource/Polygon/MeshPlanePolygon.h>



//************************************************************														   
//! @brief   コインClass
//!
//! @details コインのClass
//************************************************************
class Field : public GameObjectNull
{
//====================
// 変数
//====================
private:
	MeshPlanePolygon* mesh_plane_polygon_;		//!< メッシュ平面ポリゴン


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief メッシュ平面ポリゴン取得関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	MeshPlanePolygon* getpMeshPlanePolygon();


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param *draw 描画基底クラス
	//! @retval void なし
	//----------------------------------------
	void Init(DrawBase* draw);

	//----------------------------------------
	//! @brief 終了関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Uninit() override;
};



#endif