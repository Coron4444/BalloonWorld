//================================================================================
//!	@file	 SkyDome.cpp
//!	@brief	 �V��Class
//! @details 
//!	@author  Kai Araki									@date 2018/05/15
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../SkyDome.h"



//****************************************
// �֐���`
//****************************************
void SkyDome::Init(DrawBase* draw)
{
	// ���N���X�̏�����
	GameObjectBase::Init(draw, nullptr);
}



void SkyDome::Update()
{
	*getpTransform()->getpAngleYaw() += 0.0005f;
	getpTransform()->CreateWorldMatrix();
}