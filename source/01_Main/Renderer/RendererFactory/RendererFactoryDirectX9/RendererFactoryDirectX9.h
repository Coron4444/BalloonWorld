//================================================================================
//!	@file	 RendererFactoryDirectX9.h
//!	@brief	 DirectX9�����_���[����Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/01
//================================================================================
#ifndef	_RENDERE_FACTORY_DIRECTX9_H_
#define _RENDERE_FACTORY_DIRECTX9_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "../RendererFactoryInterface/RendererFactoryInterface.h"



//****************************************
// �N���X�錾
//****************************************
class RendererInterface;



//************************************************************														   
//! @brief   DirectX9�����_���[����Class
//!
//! @details DirectX9�����_���[�̐���Class
//************************************************************
class RendererFactoryDirectX9 : public RendererFactoryInterface
{
//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �����֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	RendererInterface* Create() override;
};



#endif