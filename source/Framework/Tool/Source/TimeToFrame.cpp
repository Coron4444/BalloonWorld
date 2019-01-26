//================================================================================
//!	@file	 TimeToFrame.cpp
//!	@brief	 ���Ԃƃt���[���ϊ�Class
//! @details static
//!	@author  Kai Araki									@date 2017/08/23
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../TimeToFrame.h"



//****************************************
// �萔��`
//****************************************
const unsigned TimeToFrame::FPS = 60;



//****************************************
// static�֐���`
//****************************************
int TimeToFrame::SecondToFrame(float second)
{
	return (int)(second * FPS);
}



int TimeToFrame::MinuteToFrame(float minute)
{
	float second = minute * 60;
	return (int)SecondToFrame(second);
}



int TimeToFrame::HourToFrame(float hour)
{
	float minute = hour * 60;
	return (int)MinuteToFrame(minute);
}



float TimeToFrame::FrameToSecond(int frame)
{
	return (float)frame / SecondToFrame(1.0f);
}



float TimeToFrame::FrameToMinute(int frame)
{
	return (float)frame / MinuteToFrame(1.0f);
}



float TimeToFrame::FrameToHour(int frame)
{
	return (float)frame / HourToFrame(1.0f);
}



void TimeToFrame::FrameToTime(int frame, float* hour, float* minute, float* second)
{
	*hour = FrameToHour  (frame);
	*min  = FrameToMinute(frame % HourToFrame(1.0f));
	*sec  = FrameToSecond(frame % MinuteToFrame(1.0f));
}