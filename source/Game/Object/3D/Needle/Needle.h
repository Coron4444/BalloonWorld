//================================================================================
//!	@file	 Needle.h
//!	@brief	 棘Class
//! @details 
//!	@author  Kai Araki									@date 2019/2/20
//================================================================================
#ifndef	_NEEDLE_H_
#define _NEEDLE_H_



//****************************************
// インクルード文
//****************************************
#include <GameEngine/GameObject/GameObjectNull.h>

#include <Scenes/GameScene/GameScene.h>



//************************************************************														   
//! @brief   棘Class
//!
//! @details 棘のClass
//************************************************************
class Needle : public GameObjectNull
{
//====================
// クラス
//====================
public :
	//**************************************************														   
	//! @brief   ステートClass
	//!
	//! @details ステートのClass
	//**************************************************
	class State
	{
	//====================
	// 変数
	//====================
	private:
		Needle* needle_ = nullptr;	//!<  棘

	//====================
	// プロパティ
	//====================
	public:
		//----------------------------------------
		//! @brief 棘取得関数
		//! @details
		//! @param void なし
		//! @retval Needle* 棘
		//----------------------------------------
		Needle* getpNeedle();

		//----------------------------------------
		//! @brief 棘設定関数
		//! @details
		//! @param *value 棘
		//! @retval void なし
		//----------------------------------------
		void setNeedle(Needle* value);

	//====================
	// 関数
	//====================
	public:
		//----------------------------------------
		//! @brief デストラクタ
		//! @details
		//! @param void なし
		//----------------------------------------
		virtual ~State();

		//----------------------------------------
		//! @brief 初期化関数
		//! @details
		//! @param void なし
		//! @retval void なし
		//----------------------------------------
		virtual void Init() = 0;

		//----------------------------------------
		//! @brief 終了関数
		//! @details
		//! @param void なし
		//! @retval void なし
		//----------------------------------------
		virtual void Uninit() = 0;

		//----------------------------------------
		//! @brief 更新関数
		//! @details
		//! @param void なし
		//! @retval void なし
		//----------------------------------------
		virtual void Update() = 0;
	};


//====================
// 変数
//====================
private:
	State* state_;	//!< ステート
	bool is_damage_ = true;

//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief 座標設定関数
	//! @details
	//! @param value 座標
	//! @retval void なし
	//----------------------------------------
	void setPosition(Vec3 value);

	//----------------------------------------
	//! @brief 拡縮設定関数
	//! @details
	//! @param value 拡縮
	//! @retval void なし
	//----------------------------------------
	void setScale(float value);

	//----------------------------------------
	//! @brief ステート設定関数
	//! @details
	//! @param *svalue ステート
	//! @retval void なし
	//----------------------------------------
	void setState(State* value);
	

	bool getIsDamage()
	{
		bool temp = is_damage_;
		is_damage_ = false;
		return temp;
	}

//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param *draw      描画基底クラス
	//! @param *collision 衝突基底クラス
	//! @retval void なし
	//----------------------------------------
	void Init(DrawBase* draw, CollisionBase* collision);

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

};



#endif