//================================================================================
//!	@file	 MeterToFrame.h
//!	@brief	 �ړ��P�ʂƃt���[���ϊ�Class
//! @details static
//!	@author  Kai Araki									@date 2017/08/23
//================================================================================
#ifndef	_METER_TO_FRAME_H_
#define _METER_TO_FRAME_H_



//************************************************************														   
//! @brief   �ړ��P�ʂƃt���[���ϊ�Class(static)
//!
//! @details �ړ��P�ʂƃt���[���̕ϊ�Class(static)
//************************************************************
class MeterToFrame
{
//====================
// static�֐�
//====================
public:
	//----------------------------------------
	//! @brief ���[�g�����烁�[�g���֕ϊ��֐�
	//! @details
	//! @param meter ���[�g��
	//! @retval float ���[�g��
	//----------------------------------------
	static float MeterToMeter(float meter);

	//----------------------------------------
	//! @brief �Z���`���[�g�����烁�[�g���֕ϊ��֐�
	//! @details
	//! @param centimeter �Z���`���[�g��
	//! @retval float ���[�g��
	//----------------------------------------
	static float CentimeterToMeter(float centimeter);

	//----------------------------------------
	//! @brief �~�����[�g�����烁�[�g���֕ϊ��֐�
	//! @details
	//! @param millimeter �~�����[�g��
	//! @retval float ���[�g��
	//----------------------------------------
	static float MillimeterToMeter(float millimeter);

	//----------------------------------------
	//! @brief �L�����[�g�����烁�[�g���֕ϊ��֐�
	//! @details
	//! @param kilometer �L�����[�g��
	//! @retval float ���[�g��
	//----------------------------------------
	static float KilometerToMeter(float kilometer);

	//----------------------------------------
	//! @brief m/s����m/f�֕ϊ��֐�
	//! @details
	//! @param velocity m/s�P�ʂ̑��x
	//! @retval float m/f
	//----------------------------------------
	static float MeterPerSecondToMeterPerFlame(float velocity);

	//----------------------------------------
	//! @brief km/h����m/f�֕ϊ��֐�
	//! @details
	//! @param velocity km/h�P�ʂ̑��x
	//! @retval float m/f
	//----------------------------------------
	static float KilometerPerHourToMeterPerFlame(float velocity);

	//----------------------------------------
	//! @brief m/s^2����m/f^2�֕ϊ��֐�
	//! @details
	//! @param acceleration km/h�P�ʂ̉����x
	//! @retval float m/f^2
	//----------------------------------------
	static float MeterPerSecondSquaredToMeterPerFrameSquared(float acceleration);
};



#endif