//================================================================================
//!	@file	 GridPolygon.h
//!	@brief	 グリッドポリゴンClass
//! @details 
//!	@author  Kai Araki									@date 2017/10/23
//================================================================================
#ifndef	_GRID_POLYGON_H_
#define _GRID_POLYGON_H_



//****************************************
// インクルード文
//****************************************
#include <vector>
#include <string>

#include <GameEngine/Renderer\Renderer.h>



//************************************************************														   
//! @brief   グリッドポリゴンClass
//!
//! @details グリッドのポリゴンClass
//************************************************************
class GridPolygon
{
//====================
// 変数
//====================
private:
	std::vector<RendererDirectX9::VERTEX_3D> vertex_;	//!< 頂点
	D3DMATERIAL9 material_;								//!< マテリアル
	LPDIRECT3DDEVICE9 device_ = nullptr;				//!< デバイス

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
	void Uninit();

	//----------------------------------------
	//! @brief 描画関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Draw();

private:
//----------------------------------------
//! @brief 頂点作成関数
//! @details
//! @param void なし
//! @retval void なし
//----------------------------------------
	void CreateVertex();

	//----------------------------------------
	//! @brief マテリアル作成関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void CreateMaterial();
};



#endif
