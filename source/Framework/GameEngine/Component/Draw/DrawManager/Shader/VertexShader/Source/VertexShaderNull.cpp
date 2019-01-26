//================================================================================
//!	@file	 VertexShaderNull.cpp
//!	@brief	 �󔒒��_�V�F�[�_�[Class
//! @details 
//!	@author  Kai Araki									@date 2019/01/19
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "VertexShaderNull.h"



//****************************************
// �֐���`
//****************************************
void VertexShaderNull::Init()
{
	InitDevice();
}



void VertexShaderNull::Uninit()
{
}



void VertexShaderNull::ObjectSetting(DrawBase* draw, Camera* camera,
									unsigned object_index)
{
	draw = draw;
	camera = camera;
	object_index = object_index;
}



void VertexShaderNull::MeshSetting(DrawBase* draw, Camera* camera,
								  unsigned object_index, unsigned mesh_index)
{
	draw = draw;
	camera = camera;
	object_index = object_index;
	mesh_index = mesh_index;
}