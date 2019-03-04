//================================================================================
//!	@file	 MeterToFrame.h
//!	@brief	 移動単位とフレーム変換Class
//! @details static
//!	@author  Kai Araki									@date 2017/08/23
//================================================================================
#ifndef	_METER_TO_FRAME_H_
#define _METER_TO_FRAME_H_



//************************************************************														   
//! @brief   移動単位とフレーム変換Class(static)
//!
//! @details 移動単位とフレームの変換Class(static)
//************************************************************
class MeterToFrame
{
//====================
// static関数
//====================
public:
	//----------------------------------------
	//! @brief メートルからメートルへ変換関数
	//! @details
	//! @param meter メートル
	//! @retval float メートル
	//----------------------------------------
	static float MeterToMeter(float meter);

	//----------------------------------------
	//! @brief センチメートルからメートルへ変換関数
	//! @details
	//! @param centimeter センチメートル
	//! @retval float メートル
	//----------------------------------------
	static float CentimeterToMeter(float centimeter);

	//----------------------------------------
	//! @brief ミリメートルからメートルへ変換関数
	//! @details
	//! @param millimeter ミリメートル
	//! @retval float メートル
	//----------------------------------------
	static float MillimeterToMeter(float millimeter);

	//----------------------------------------
	//! @brief キロメートルからメートルへ変換関数
	//! @details
	//! @param kilometer キロメートル
	//! @retval float メートル
	//----------------------------------------
	static float KilometerToMeter(float kilometer);

	//----------------------------------------
	//! @brief m/sからm/fへ変換関数
	//! @details
	//! @param velocity m/s単位の速度
	//! @retval float m/f
	//----------------------------------------
	static float MeterPerSecondToMeterPerFlame(float velocity);

	//----------------------------------------
	//! @brief km/hからm/fへ変換関数
	//! @details
	//! @param velocity km/h単位の速度
	//! @retval float m/f
	//----------------------------------------
	static float KilometerPerHourToMeterPerFlame(float velocity);

	//----------------------------------------
	//! @brief m/s^2からm/f^2へ変換関数
	//! @details
	//! @param acceleration km/h単位の加速度
	//! @retval float m/f^2
	//----------------------------------------
	static float MeterPerSecondSquaredToMeterPerFrameSquared(float acceleration);
};



#endif