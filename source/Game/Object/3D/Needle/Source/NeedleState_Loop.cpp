//================================================================================
//!	@file	 NeedleState_Loop.cpp
//!	@brief	 ���X�e�[�g���[�vClass
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../NeedleState_Loop.h"



//****************************************
// �萔��`
//****************************************
const Vec3 NeedleState_Loop::CENTER_POSITION(0.0f, 3.0f, 0.0f);
const float NeedleState_Loop::ROTATION_CENTER_SPEED = 0.0f;
const float NeedleState_Loop::ROTATION_SPEED = 2.0f;



//****************************************
// �֐���`
//****************************************
void NeedleState_Loop::Init()
{
	// ���W�ݒ�
	*getpNeedle()->getpTransform()->getpPosition() = CENTER_POSITION;
	getpNeedle()->getpTransform()->CreateAxisAndWorldMatrix();
	getpNeedle()->getpTransform()
		->AddParentMatrixToWorldMatrix(rotation_transform_.getpWorldMatrix());
}



void NeedleState_Loop::Uninit()
{
}



void NeedleState_Loop::Update()
{
	// ��]
	*rotation_transform_.getpAnglePitch() += ROTATION_CENTER_SPEED;
	*getpNeedle()->getpTransform()->getpAnglePitch() += ROTATION_SPEED;
	rotation_transform_.CreateAxisAndWorldMatrix();
	getpNeedle()->getpTransform()->CreateAxisAndWorldMatrix();
	getpNeedle()->getpTransform()
		->AddParentMatrixToWorldMatrix(rotation_transform_.getpWorldMatrix());
}