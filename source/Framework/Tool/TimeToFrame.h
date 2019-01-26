//================================================================================
//!	@file	 TimeToFrame.h
//!	@brief	 ���Ԃƃt���[���ϊ�Class
//! @details static
//!	@author  Kai Araki									@date 2017/08/23
//================================================================================
#ifndef	_TIME_TO_FRAME_H_
#define _TIME_TO_FRAME_H_



//************************************************************														   
//! @brief   ���Ԃƃt���[���ϊ�Class(static)
//!
//! @details ���Ԃƃt���[���̕ϊ�Class(static)
//************************************************************
class TimeToFrame
{
//====================
// �萔
//====================
private:
	static const unsigned FPS;		//!< FPS


//====================
// static�֐�
//====================
public:
	//----------------------------------------
	//! @brief �b����t���[�����֕ϊ��֐�
	//! @details
	//! @param second �b
	//! @retval int �t���[����
	//----------------------------------------
	static int SecondToFrame(float second);

	//----------------------------------------
	//! @brief ������t���[�����֕ϊ��֐�
	//! @details
	//! @param minute ��
	//! @retval int �t���[����
	//----------------------------------------
	static int MinuteToFrame(float minute);

	//----------------------------------------
	//! @brief ������t���[�����֕ϊ��֐�
	//! @details
	//! @param hour ��
	//! @retval int �t���[����
	//----------------------------------------
	static int HourToFrame(float hour);

	//----------------------------------------
	//! @brief �t���[��������b�֕ϊ��֐�
	//! @details
	//! @param frame �t���[����
	//! @retval float �b
	//----------------------------------------
	static float FrameToSecond(int frame);

	//----------------------------------------
	//! @brief �t���[�������番�֕ϊ��֐�
	//! @details
	//! @param frame �t���[����
	//! @retval float ��
	//----------------------------------------
	static float FrameToMinute(int frame);

	//----------------------------------------
	//! @brief �t���[�������玞�֕ϊ��֐�
	//! @details
	//! @param frame �t���[����
	//! @retval float ��
	//----------------------------------------
	static float FrameToHour(int frame);

	//----------------------------------------
	//! @brief �t���[�������玞�Ԃ֕ϊ��֐�
	//! @details
	//! @param frame   �t���[����
	//! @param *hour   ��
	//! @param *minute ��
	//! @param *second �b
	//! @retval void �Ȃ�
	//----------------------------------------
	static void FrameToTime(int frame, float* hour, float* minute, float* second);
};



#endif