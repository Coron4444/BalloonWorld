//================================================================================
//!	@file	 PixelShaderNull.cpp
//!	@brief	 �󔒃s�N�Z���V�F�[�_�[Class
//! @details 
//!	@author  Kai Araki									@date 2019/01/19
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../PixelShaderNull.h"



//****************************************
// �֐���`
//****************************************
void PixelShaderNull::Init()
{
	InitDevice();
}



void PixelShaderNull::Uninit()
{
}



void PixelShaderNull::ObjectSetting(DrawBase* draw, Camera* camera,
									unsigned object_index)
{
	draw = draw;
	camera = camera;
	object_index = object_index;
}



void PixelShaderNull::MeshSetting(DrawBase* draw, Camera* camera,
								  unsigned object_index, unsigned mesh_index)
{
	draw = draw;
	camera = camera;
	object_index = object_index;
	mesh_index = mesh_index;
}