//================================================================================
//!	@file	 CameraState_CrawlUp.cpp
//!	@brief	 �������΂�J�����X�e�[�gClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../CameraState_CrawlUp.h"
#include "../../../Input/InputManager/InputManager.h"



//****************************************
// �萔��`
//****************************************
const float CameraState_CrawlUp::TRANSLATION_SPEED = 0.1f;
const float CameraState_CrawlUp::ROTATION_SPEED = 0.8f;
const float CameraState_CrawlUp::POSITION_Y = 8.0f;
const float CameraState_CrawlUp::LOOK_AT_POSITION_Y = POSITION_Y - 5.0f;



//****************************************
// �֐���`
//****************************************
void CameraState_CrawlUp::Init()
{
	getpCamera()->getpPositon()->y     = POSITION_Y;
	getpCamera()->getpLookAtPoint()->y = LOOK_AT_POSITION_Y;
}



void CameraState_CrawlUp::Uninit()
{
}



void CameraState_CrawlUp::Update()
{
	// �O
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_I))
	{
		// �O�x�N�g����ۑ�
		Vector3D temp_vector = *getpCamera()->getpAxis()->getpForawrd();

		// �n���͂�����
		temp_vector.y = 0.0f;

		temp_vector.ChangeAnyLength(TRANSLATION_SPEED);

		*getpCamera()->getpPositon() += temp_vector;
		*getpCamera()->getpLookAtPoint() += temp_vector;
	}

	// ���
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_K))
	{
		// �O�x�N�g����ۑ�
		Vector3D temp_vector = *getpCamera()->getpAxis()->getpForawrd();

		// �n���͂�����
		temp_vector.y = 0.0f;

		temp_vector.ChangeAnyLength(TRANSLATION_SPEED);

		*getpCamera()->getpPositon() += -temp_vector;
		*getpCamera()->getpLookAtPoint() += -temp_vector;
	}


	// �E
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_L))
	{
		// �E�x�N�g����ۑ�
		Vector3D temp_vector = *getpCamera()->getpAxis()->getpRight();

		// �n���͂�����
		temp_vector.y = 0.0f;

		temp_vector.ChangeAnyLength(TRANSLATION_SPEED);

		*getpCamera()->getpPositon() += temp_vector;
		*getpCamera()->getpLookAtPoint() += temp_vector;
	}


	// ��
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_J))
	{
		// �E�x�N�g����ۑ�
		Vector3D temp_vector = *getpCamera()->getpAxis()->getpRight();

		// �n���͂�����
		temp_vector.y = 0.0f;

		temp_vector.ChangeAnyLength(TRANSLATION_SPEED);

		*getpCamera()->getpPositon() += -temp_vector;
		*getpCamera()->getpLookAtPoint() += -temp_vector;
	}


	// �E����
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_E))
	{
		// �O�x�N�g���̍쐬
		Vector3D temp_vector = *getpCamera()->getpLookAtPoint() 
			- *getpCamera()->getpPositon();
		
		getpCamera()->getpAxis()->setForward(temp_vector);

		// ���x�N�g���̉�]
		getpCamera()->getpAxis()->RotationAxisY(D3DXToRadian(ROTATION_SPEED));

		// �����_�̍쐬
		float length = temp_vector.getLength();
		temp_vector = *getpCamera()->getpAxis()->getpForawrd();
		temp_vector.ChangeAnyLength(length);

		*getpCamera()->getpLookAtPoint() = *getpCamera()->getpPositon() + temp_vector;

		// �O�x�N�g�����쐬( �O�x�N�g�� = ���_���W - �J�������W )
		getpCamera()->getpAxis()->setForward(*getpCamera()->getpLookAtPoint() 
											 - *getpCamera()->getpPositon());
	}


	// ������
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_Q))
	{
		// �O�x�N�g���̍쐬
		Vector3D temp_vector = *getpCamera()->getpLookAtPoint() 
			- *getpCamera()->getpPositon();
		
		getpCamera()->getpAxis()->setForward(temp_vector);

		// ���x�N�g���̉�]
		getpCamera()->getpAxis()->RotationAxisY(D3DXToRadian(-ROTATION_SPEED));

		// �����_�̍쐬
		float length = temp_vector.getLength();
		temp_vector = *getpCamera()->getpAxis()->getpForawrd();
		temp_vector.ChangeAnyLength(length);

		*getpCamera()->getpLookAtPoint() = *getpCamera()->getpPositon() + temp_vector;

		// �O�x�N�g�����쐬( �O�x�N�g�� = ���_���W - �J�������W )
		getpCamera()->getpAxis()->setForward(*getpCamera()->getpLookAtPoint() 
											 - *getpCamera()->getpPositon());
	}

	// �����
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_T))
	{
		// �O�x�N�g���̍쐬
		Vector3D temp_vector = *getpCamera()->getpLookAtPoint() 
			- *getpCamera()->getpPositon();
		
		getpCamera()->getpAxis()->setForward(temp_vector);

		// ���x�N�g���̉�]
		getpCamera()->getpAxis()->RotationAxisRight(D3DXToRadian(-ROTATION_SPEED));

		// �����_�̍쐬
		float length = temp_vector.getLength();
		temp_vector = *getpCamera()->getpAxis()->getpForawrd();
		temp_vector.ChangeAnyLength(length);

		*getpCamera()->getpLookAtPoint() = *getpCamera()->getpPositon() + temp_vector;

		// �O�x�N�g�����쐬( �O�x�N�g�� = ���_���W - �J�������W )
		getpCamera()->getpAxis()->setForward(*getpCamera()->getpLookAtPoint() 
											 - *getpCamera()->getpPositon());
	}

	// ������
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_G))
	{
		// �O�x�N�g���̍쐬
		Vector3D temp_vector = *getpCamera()->getpLookAtPoint() 
			- *getpCamera()->getpPositon();
	
		getpCamera()->getpAxis()->setForward(temp_vector);

		// ���x�N�g���̉�]
		getpCamera()->getpAxis()->RotationAxisRight(D3DXToRadian(ROTATION_SPEED));

		// �����_�̍쐬
		float length = temp_vector.getLength();
		temp_vector = *getpCamera()->getpAxis()->getpForawrd();
		temp_vector.ChangeAnyLength(length);

		*getpCamera()->getpLookAtPoint() = *getpCamera()->getpPositon() + temp_vector;

		// �O�x�N�g�����쐬( �O�x�N�g�� = ���_���W - �J�������W )
		getpCamera()->getpAxis()->setForward(*getpCamera()->getpLookAtPoint() 
											 - *getpCamera()->getpPositon());
	}


	// �E����( ���_���S )
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_Y))
	{
		// �t�O�x�N�g���̍쐬
		Vector3D temp_vector = *getpCamera()->getpPositon() 
			- *getpCamera()->getpLookAtPoint();
		
		getpCamera()->getpAxis()->setForward(temp_vector);

		// ���x�N�g���̉�]
		getpCamera()->getpAxis()->RotationAxisY(D3DXToRadian(ROTATION_SPEED));

		// �J�������W�̍쐬
		float length = temp_vector.getLength();
		temp_vector = *getpCamera()->getpAxis()->getpForawrd();
		temp_vector.ChangeAnyLength(length);

		*getpCamera()->getpPositon() = *getpCamera()->getpLookAtPoint() + temp_vector;

		// �O�x�N�g�����쐬( �O�x�N�g�� = ���_���W - �J�������W )
		getpCamera()->getpAxis()->setForward(*getpCamera()->getpLookAtPoint() 
											 - *getpCamera()->getpPositon());
	}
	
	// ������( ���_���S )
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_H))
	{
		// �t�O�x�N�g���̍쐬
		Vector3D temp_vector = *getpCamera()->getpPositon() 
			- *getpCamera()->getpLookAtPoint();
		
		getpCamera()->getpAxis()->setForward(temp_vector);

		// ���x�N�g���̉�]
		getpCamera()->getpAxis()->RotationAxisY(D3DXToRadian(-ROTATION_SPEED));

		// �J�������W�̍쐬
		float length = temp_vector.getLength();
		temp_vector = *getpCamera()->getpAxis()->getpForawrd();
		temp_vector.ChangeAnyLength(length);

		*getpCamera()->getpPositon() = *getpCamera()->getpLookAtPoint()  + temp_vector;

		// �O�x�N�g�����쐬( �O�x�N�g�� = ���_���W - �J�������W )
		getpCamera()->getpAxis()->setForward(*getpCamera()->getpLookAtPoint() 
											 - *getpCamera()->getpPositon());
	}
}