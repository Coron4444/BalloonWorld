//================================================================================
//!	@file	 StartBlock.cpp
//!	@brief	 �X�^�[�g�u���b�NClass
//! @details 
//!	@author  Kai Araki									@date 2019/02/13
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../StartBlock.h"


//****************************************
// �v���p�e�B��`
//****************************************
const Vec3 StartBlock::SCALE(15.0f, 5.0f, 15.0f);
const float StartBlock::ROTATION_SPEED = 0.01f;



//****************************************
// �v���p�e�B��`
//****************************************
void StartBlock::setPosition(Vec3 value)
{
	*getpTransform()->getpPosition() = value;
	getpTransform()->CreateWorldMatrix();
}



//****************************************
// �֐���`
//****************************************
void StartBlock::Init(DrawBase* draw, CollisionBase* collision)
{
	// �ό`
	*getpTransform()->getpScale() = SCALE;
	getpTransform()->CreateAxisAndWorldMatrix();

	// ���N���X�̏�����
	GameObjectBase::Init(draw, collision);
}



void StartBlock::Update()
{
	// �ό`
	*getpTransform()->getpAngleYaw() += ROTATION_SPEED;
	getpTransform()->CreateAxisAndWorldMatrix();
}