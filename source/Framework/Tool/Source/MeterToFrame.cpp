//================================================================================
//!	@file	 MeterToFrame.cpp
//!	@brief	 移動単位とフレーム変換Class
//! @details static
//!	@author  Kai Araki									@date 2017/08/23
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../MeterToFrame.h"
#include "../TimeToFrame.h"



//****************************************
// static関数定義
//****************************************
float MeterToFrame::MeterToMeter(float meter)
{
	return meter;
}



float MeterToFrame::CentimeterToMeter(float centimeter)
{
	float meter = centimeter * 0.01f;
	return MeterToMeter(meter);
}



float MeterToFrame::MillimeterToMeter(float millimeter)
{
	float centimeter = millimeter * 0.1f;
	return CentimeterToMeter(centimeter);
}



float MeterToFrame::KilometerToMeter(float kilometer)
{
	float meter = kilometer * 1000.0f;
	return MeterToMeter(meter);
}



float MeterToFrame::MeterPerSecondToMeterPerFlame(float velocity)
{
	return MeterToMeter(velocity) / TimeToFrame::SecondToFrame(1.0f);
}



float MeterToFrame::KilometerPerHourToMeterPerFlame(float velocity)
{
	return KilometerToMeter(velocity) / TimeToFrame::HourToFrame(1.0f);
}



float MeterToFrame::MeterPerSecondSquaredToMeterPerFrameSquared(float acceleration)
{
	return MeterToMeter(acceleration) / (TimeToFrame::SecondToFrame(1.0f) 
										 * TimeToFrame::SecondToFrame(1.0f));
}