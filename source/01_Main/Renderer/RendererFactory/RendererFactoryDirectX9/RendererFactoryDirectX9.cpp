//================================================================================
//!	@file	 RendererFactoryDirectX9.cpp
//!	@brief	 DirectX9�����_���[����Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/01
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "RendererFactoryDirectX9.h"

#include <Renderer/RendererDirectX9/RendererDirectX9.h>



//****************************************
// �֐���`
//****************************************
//----------------------------------------
RendererInterface* RendererFactoryDirectX9::Create()
{
	return new RendererDirectX9();
}