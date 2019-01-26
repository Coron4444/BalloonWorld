//================================================================================
//!	@file	 DrawBase.cpp
//!	@brief	 �`��BaseClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================


//****************************************
// �C���N���[�h��
//****************************************
#include "DrawBase.h"



//****************************************
// �v���p�e�B��`
//****************************************
DrawOrderList* DrawBase::getpDrawOrderList() 
{
	return &draw_order_list_; 
}



//****************************************
// �֐���`
//****************************************
DrawBase::~DrawBase()
{
}



void DrawBase::LimitedChangeCameraType(Camera* camera, Camera::Type type)
{
	save_camera_type_ = camera->getType();
	camera->setType(type);
}



void DrawBase::RevivalCameraType(Camera* camera)
{
	if (save_camera_type_ == Camera::Type::NONE) return;
	camera->setType(save_camera_type_);
}