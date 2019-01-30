//================================================================================
//!	@file	 NumbersPolygon.h
//!	@brief	 数字群ポリゴンClass
//! @details 
//!	@author  Kai Araki									@date 2018/06/19
//================================================================================
#ifndef	_NUMBERS_H_
#define _NUMBERS_H_



//****************************************
// インクルード文
//****************************************
#include <vector>

#include <Tool/Transform.h>



//****************************************
// クラス宣言
//****************************************
class D3DMATERIAL9;
class PlanePolygon;
class TextureObject;



//************************************************************														   
//! @brief   数字群ポリゴンClass
//!
//! @details 数字群のポリゴンClass
//************************************************************
class NumbersPolygon
{
//====================
// クラス定義
//====================
public:
	//****************************************											   
	//! @brief   数字ポリゴンClass
	//!
	//! @details 数字のポリゴンClass
	//****************************************
	class NumberPolygon
	{
	//====================
	// 変数
	//====================
	private:
		PlanePolygon* plane_polygon_ = nullptr;		//!< 平面ポリゴン
		TextureObject* texture_ = nullptr;			//!< テクスチャオブジェクト
		Transform transform_;						//!< 変形
		int number_;								//!< 現在の数字
		int old_number_;							//!< 前回の数字

	//====================
	// プロパティ
	//====================
	public:
		//----------------------------------------
		//! @brief 数字設定関数
		//! @details
		//! @param value 数字
		//! @retval void なし
		//----------------------------------------
		void setNumber(int value);

		//----------------------------------------
		//! @brief 色設定関数
		//! @details
		//! @param value 色
		//! @retval void なし
		//----------------------------------------
		void setColor(XColor4 value);

		//----------------------------------------
		//! @brief テクスチャオブジェクト設定関数
		//! @details
		//! @param value テクスチャオブジェクト
		//! @retval void なし
		//----------------------------------------
		void setTextureObject(TextureObject* value);

		//----------------------------------------
		//! @brief 変形取得関数
		//! @details
		//! @param void なし
		//! @retval Transform* 変形
		//----------------------------------------
		Transform* getpTransform();

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
	};


//====================
// 変数
//====================
private:
	int digits_num_ = 0;						//!< 桁数
	bool is_zero_ = false;						//!< ゼロ埋めフラグ
	Vec2 position_ = {0.0f, 0.0f};				//!< 座標
	Vec2 scale_ = {1.0f, 1.0f};					//!< 拡縮
	XColor4 color_ = {1.0f, 1.0f, 1.0f, 1.0f};	//!< 色
	TextureObject* texture_ = nullptr;			//!< テクスチャオブジェクト
	std::vector<NumberPolygon*> number_;		//!< 数字ポリゴン配列


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief 数字設定関数
	//! @details
	//! @param value 数字
	//! @retval void なし
	//----------------------------------------
	void setNumber(int value);

	//----------------------------------------
	//! @brief 桁数設定関数
	//! @details
	//! @param value 桁数
	//! @retval void なし
	//----------------------------------------
	void setDigitsNum(int value);

	//----------------------------------------
	//! @brief ゼロ埋めフラグ設定関数
	//! @details
	//! @param value ゼロ埋めフラグ
	//! @retval void なし
	//----------------------------------------
	void setIsZero(bool value);

	//----------------------------------------
	//! @brief 座標設定関数
	//! @details
	//! @param value 座標
	//! @retval void なし
	//----------------------------------------
	void setPosition(Vec2 value);

	//----------------------------------------
	//! @brief 拡縮設定関数
	//! @details
	//! @param value 拡縮
	//! @retval void なし
	//----------------------------------------
	void setScale(Vec2 value);

	//----------------------------------------
	//! @brief 色設定関数
	//! @details
	//! @param value 色
	//! @retval void なし
	//----------------------------------------
	void setColor(XColor4 value);

	//----------------------------------------
	//! @brief テクスチャオブジェクト設定関数
	//! @details
	//! @param value テクスチャオブジェクト
	//! @retval void なし
	//----------------------------------------
	void setTextureObject(TextureObject* value);

	//----------------------------------------
	//! @brief オブジェクト数取得関数
	//! @details
	//! @param void なし
	//! @retval unsigned オブジェクト数
	//----------------------------------------
	unsigned getObjectNum();

	//----------------------------------------
	//! @brief 行列取得関数
	//! @details
	//! @param object_index オブジェクトインデックス
	//! @retval MATRIX* 行列
	//----------------------------------------
	MATRIX* getpMatrix(int object_index);

	//----------------------------------------
	//! @brief マテリアル取得関数
	//! @details
	//! @param object_index オブジェクトインデックス
	//! @retval D3DMATERIAL9* マテリアル
	//----------------------------------------
	D3DMATERIAL9* getpMaterial(int object_index);


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param number     数字
	//! @param digits_num 桁数
	//! @param is_zero    ゼロ埋めフラグ
	//! @param position   座標
	//! @param scale      拡縮
	//! @param color      色
	//! @param *texture   テクスチャオブジェクト
	//! @retval void なし
	//----------------------------------------
	void Init(int number, int digits_num, bool is_zero, Vec2 position,
			  Vec2 scale, XColor4 color, TextureObject* texture);

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
	//! @param object_index オブジェクトインデックス
	//! @retval void なし
	//----------------------------------------
	void Draw(int object_index);


private:
	//----------------------------------------
	//! @brief 左詰め関数
	//! @details
	//! @param number      数字
	//! @param *digits_num 桁数
	//! @retval void なし
	//----------------------------------------
	void LeftJustified(int number, int* digits_num);

	//----------------------------------------
	//! @brief 数字ポリゴン作成関数
	//! @details
	//! @param number      数字
	//! @param *digits_num 桁数
	//! @retval void なし
	//----------------------------------------
	void CreateNumberPolygon(int number, int* digits_num);

	//----------------------------------------
	//! @brief カンスト処理関数
	//! @details
	//! @param *number    数字
	//! @param digits_num 桁数
	//! @retval void なし
	//----------------------------------------
	void IsCountStop(int* number, int digits_num);

	//----------------------------------------
	//! @brief 各桁更新関数
	//! @details
	//! @param number     数字
	//! @param digits_num 桁数
	//! @retval void なし
	//----------------------------------------
	void UpdateEachDigit(int number, int digits_num);

	//----------------------------------------
	//! @brief 数字ポリゴン関数
	//! @details
	//! @param number     数字
	//! @param digits_num 桁数
	//! @retval void なし
	//----------------------------------------
	void ReleaseNumberPolygon();
};



#endif