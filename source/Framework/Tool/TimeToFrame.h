//================================================================================
//!	@file	 TimeToFrame.h
//!	@brief	 時間とフレーム変換Class
//! @details static
//!	@author  Kai Araki									@date 2017/08/23
//================================================================================
#ifndef	_TIME_TO_FRAME_H_
#define _TIME_TO_FRAME_H_



//************************************************************														   
//! @brief   時間とフレーム変換Class(static)
//!
//! @details 時間とフレームの変換Class(static)
//************************************************************
class TimeToFrame
{
//====================
// 定数
//====================
private:
	static const unsigned FPS;		//!< FPS


//====================
// static関数
//====================
public:
	//----------------------------------------
	//! @brief 秒からフレーム数へ変換関数
	//! @details
	//! @param second 秒
	//! @retval int フレーム数
	//----------------------------------------
	static int SecondToFrame(float second);

	//----------------------------------------
	//! @brief 分からフレーム数へ変換関数
	//! @details
	//! @param minute 分
	//! @retval int フレーム数
	//----------------------------------------
	static int MinuteToFrame(float minute);

	//----------------------------------------
	//! @brief 時からフレーム数へ変換関数
	//! @details
	//! @param hour 時
	//! @retval int フレーム数
	//----------------------------------------
	static int HourToFrame(float hour);

	//----------------------------------------
	//! @brief フレーム数から秒へ変換関数
	//! @details
	//! @param frame フレーム数
	//! @retval float 秒
	//----------------------------------------
	static float FrameToSecond(int frame);

	//----------------------------------------
	//! @brief フレーム数から分へ変換関数
	//! @details
	//! @param frame フレーム数
	//! @retval float 分
	//----------------------------------------
	static float FrameToMinute(int frame);

	//----------------------------------------
	//! @brief フレーム数から時へ変換関数
	//! @details
	//! @param frame フレーム数
	//! @retval float 時
	//----------------------------------------
	static float FrameToHour(int frame);

	//----------------------------------------
	//! @brief フレーム数から時間へ変換関数
	//! @details
	//! @param frame   フレーム数
	//! @param *hour   時
	//! @param *minute 分
	//! @param *second 秒
	//! @retval void なし
	//----------------------------------------
	static void FrameToTime(int frame, float* hour, float* minute, float* second);
};



#endif