//================================================================================
//!	@file	 Pause.h
//!	@brief	 ポーズClass
//! @details 
//!	@author  Kai Araki									@date 2019/02/18
//================================================================================
#ifndef	_PAUSE_H_
#define _PAUSE_H_



//****************************************
// インクルード文
//****************************************
#include <GameEngine/GameObject/GameObjectNull.h>

#include <Tool/Interpolation.h>



//************************************************************														   
//! @brief   ポーズClass
//!
//! @details ポーズのClass
//************************************************************
class Pause : public GameObjectNull
{
//====================
// 列挙型
//====================
public:
	enum class SelectType
	{
		NONE = -1,
		CONTINUE,
		RESTART,
		QUIT,
		MAX
	};


//====================
// 定数
//====================
private:
	static const float FRAME_SCALE;					//!< フレーム拡縮
	static const float ICON_SCALE;					//!< アイコン拡縮
	static const float TOP_ICON_POSITION_Y;			//!< アイコンのY上座標
	static const float BOTTOM_ICON_POSITION_Y;		//!< アイコンのY下座標
	static const float ADD_ICON_POSITION_Y;			//!< アイコンのY座標の変化量
	static const Vector3D DEFAULT_ICON_POSITION;		//!< 既定アイコン座標
	static const float BLINKING_SECOND;				//!< 点滅秒数
	static const int BLINKING_NUM;					//!< 点滅数
	static const unsigned CHARACTER_COLOR_NUM = 3;	//!< 文字色数

public:
	static const XColor4 CHARACTER_COLOR0;			//!< 文字色0
	static const XColor4 CHARACTER_COLOR1;			//!< 文字色1


//====================
// 変数
//====================
private:
	bool is_enable_ = false;						//!< 有効フラグ
	SelectType select_type_ = SelectType::NONE;		//!< 選択したタイプ
	Transform icon_transform_;						//!< アイコン用変形
	XColor4 character_color_[CHARACTER_COLOR_NUM];	//!< 文字色
	Interpolation<float> inter_container_[4];		//!< 補間コンテナ
	Interpolation<float>::Iterator inter_iter_[4];	//!< 補間イテレータ


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief 有効フラグ取得関数
	//! @details
	//! @param void なし
	//! @retval value 有効フラグ
	//----------------------------------------
	bool getIsEnable();

	//----------------------------------------
	//! @brief 有効フラグ設定関数
	//! @details
	//! @param value 有効フラグ
	//! @retval void なし
	//----------------------------------------
	void setIsEnable(bool value);

	//----------------------------------------
	//! @brief 決定フラグ取得関数
	//! @details
	//! @param void なし
	//! @retval bool 決定フラグ
	//----------------------------------------
	bool getIsDecision();

	//----------------------------------------
	//! @brief アイコン変形取得関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	Transform* getpIconTransform();

	//----------------------------------------
	//! @brief 選択したタイプ取得関数
	//! @details
	//! @param void なし
	//! @retval SelectType 選択したタイプ
	//----------------------------------------
	SelectType getSelectType();

	//----------------------------------------
	//! @brief 文字色取得関数
	//! @details
	//! @param index インデックス
	//! @retval XColor4 文字色
	//----------------------------------------
	XColor4 getCharacterColor(int index);
	

//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param *update 更新基底クラス
	//! @param *draw   描画基底クラス
	//! @retval void なし
	//----------------------------------------
	void Init(DrawBase* draw);

	//----------------------------------------
	//! @brief 更新関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Update() override;

private:
	//----------------------------------------
	//! @brief 入力関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Input();
};



#endif