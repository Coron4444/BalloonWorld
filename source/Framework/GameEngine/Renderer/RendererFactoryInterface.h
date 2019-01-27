//================================================================================
//!	@file	 RendererFactoryInterface.h
//!	@brief	 �����_���[����InterfaceClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/01
//================================================================================
#ifndef	_RENDERE_FACTORY_INTERFACE_H_
#define _RENDERE_FACTORY_INTERFACE_H_



//****************************************
// �N���X�錾
//****************************************
class RendererInterface;



//************************************************************														   
//! @brief   �����_���[����InterfaceClass
//!
//! @details �����_���[������InterfaceClass
//************************************************************
class RendererFactoryInterface
{
//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief ���z�f�X�g���N�^
	//! @details
	//! @param void �Ȃ�
	//----------------------------------------
	virtual ~RendererFactoryInterface() = 0;

	//----------------------------------------
	//! @brief �����֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval RendererInterface* �����_���[�|�C���^
	//----------------------------------------
	virtual RendererInterface* Create() = 0;
};



#endif