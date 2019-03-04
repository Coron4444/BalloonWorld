//================================================================================
//!	@file	 Random.h
//!	@brief	 ランダムClass
//! @details Singleton
//!	@author  Kai Araki									@date 2019/02/10
//================================================================================
#ifndef	_RANDOM_H_
#define _RANDOM_H_



//****************************************
// インクルード文
//****************************************
#include <random>



//************************************************************														   
//! @brief   ランダムClass(Singleton)
//!
//! @details ランダムのClass(Singleton)
//************************************************************
class Random
{
//====================
// static変数
//====================
private:
	static Random* instance_;	//!< インスタンス


//====================
// staticプロパティ
//====================
public:
	//----------------------------------------
	//! @brief インスタンス取得関数
	//! @details
	//! @param void なし
	//! @retval Random* インスタンス
	//----------------------------------------
	static Random* getpInstance();


//====================
// static関数
//====================
public:
	//----------------------------------------
	//! @brief インスタンス解放関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	static void ReleaseInstance();


//====================
// 変数
//====================
private:
	std::random_device seed_;						//!< 完全ランダムシード
	std::mt19937 mersenne_twister_;					//!< メルセンヌツイスター乱数生成器
	

//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief Int型乱数値取得関数
	//! @details
	//! @param min 最小値
	//! @param max 最大値
	//! @retval int int型乱数値
	//----------------------------------------
	int getInt(int min, int max);

	//----------------------------------------
	//! @brief Float型乱数値取得関数
	//! @details
	//! @param min 最小値
	//! @param max 最大値
	//! @retval int int型乱数値
	//----------------------------------------
	float getFloat(float min, float max);

	//----------------------------------------
	//! @brief Double型乱数値取得関数
	//! @details
	//! @param min 最小値
	//! @param max 最大値
	//! @retval int int型乱数値
	//----------------------------------------
	double getDouble(double min, double max);


//====================
// 関数
//====================
private:
	//----------------------------------------
	//! @brief コンストラクタ
	//! @param void なし
	//----------------------------------------
	Random();

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


private:
	

//====================
// 消去済み関数
//====================
private:
	Random(const Random& class_name) = delete;
	Random& operator = (const Random& class_name) = delete;
};



#endif