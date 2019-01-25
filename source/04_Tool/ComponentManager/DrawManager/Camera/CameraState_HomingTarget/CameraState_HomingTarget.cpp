//================================================================================
//!	@file	 CameraState_HomingTarget.cpp
//!	@brief	 �^�[�Q�b�g�ǐՃJ�����X�e�[�gClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "CameraState_HomingTarget.h"

#include <GameObjectBase/GameObjectBase.h>
#include <Vector3D.h>



//****************************************
// �萔��`
//****************************************
const float CameraState_HomingTarget::HOMING_CAMERA_POSITION_Y = 5.0f;
const float CameraState_HomingTarget::HOMING_CAMERA_POSITION_Z = -15.0f;
const float CameraState_HomingTarget::HOMING_CAMERA_LOOK_AT_POINT_Y = 1.0f;



//****************************************
// �v���p�e�B��`
//****************************************
void CameraState_HomingTarget::setTargetObject(GameObjectBase* value) 
{
	target_object_ = value; 
}



//****************************************
// �֐���`
//****************************************
void CameraState_HomingTarget::Init()
{
	Update();
}



void CameraState_HomingTarget::Uninit()
{
}



void CameraState_HomingTarget::Update()
{
	if (target_object_ == nullptr) return;

	// �J�����|�W�V�����̍쐬
	*getpCamera()->getpPositon() = *target_object_->GetTransform()->GetPosition();

	getpCamera()->getpPositon()->y += HOMING_CAMERA_POSITION_Y;
	getpCamera()->getpPositon()->z += HOMING_CAMERA_POSITION_Z;

	// �����_�̍쐬
	Vec3 temp_position = *target_object_->GetTransform()->GetPosition();
	temp_position.y += HOMING_CAMERA_LOOK_AT_POINT_Y;
	*getpCamera()->getpLookAtPoint() = temp_position;
}