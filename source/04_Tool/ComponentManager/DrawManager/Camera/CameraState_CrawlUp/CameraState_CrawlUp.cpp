//================================================================================
//!	@file	 CameraState_CrawlUp.cpp
//!	@brief	 �������΂�J�����X�e�[�gClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "CameraState_CrawlUp.h"

#include <Keyboard\Keyboard.h>



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
	if (GetKeyboardPress(DIK_I))
	{
		// �O�x�N�g����ۑ�
		Vector3D temp_vector = *getpCamera()->getpAxis()->GetForawrd();

		// �n���͂�����
		temp_vector.y = 0.0f;

		temp_vector.AnyLengthVector(TRANSLATION_SPEED);

		*getpCamera()->getpPositon() += temp_vector;
		*getpCamera()->getpLookAtPoint() += temp_vector;
	}

	// ���
	if (GetKeyboardPress(DIK_K))
	{
		// �O�x�N�g����ۑ�
		Vector3D temp_vector = *getpCamera()->getpAxis()->GetForawrd();

		// �n���͂�����
		temp_vector.y = 0.0f;

		temp_vector.AnyLengthVector(TRANSLATION_SPEED);

		*getpCamera()->getpPositon() += -temp_vector;
		*getpCamera()->getpLookAtPoint() += -temp_vector;
	}


	// �E
	if (GetKeyboardPress(DIK_L))
	{
		// �E�x�N�g����ۑ�
		Vector3D temp_vector = *getpCamera()->getpAxis()->GetRight();

		// �n���͂�����
		temp_vector.y = 0.0f;

		temp_vector.AnyLengthVector(TRANSLATION_SPEED);

		*getpCamera()->getpPositon() += temp_vector;
		*getpCamera()->getpLookAtPoint() += temp_vector;
	}


	// ��
	if (GetKeyboardPress(DIK_J))
	{
		// �E�x�N�g����ۑ�
		Vector3D temp_vector = *getpCamera()->getpAxis()->GetRight();

		// �n���͂�����
		temp_vector.y = 0.0f;

		temp_vector.AnyLengthVector(TRANSLATION_SPEED);

		*getpCamera()->getpPositon() += -temp_vector;
		*getpCamera()->getpLookAtPoint() += -temp_vector;
	}


	// �E����
	if (GetKeyboardPress(DIK_E))
	{
		// �O�x�N�g���̍쐬
		Vector3D temp_vector = *getpCamera()->getpLookAtPoint() 
			- *getpCamera()->getpPositon();
		
		getpCamera()->getpAxis()->SetForward(temp_vector);

		// ���x�N�g���̉�]
		getpCamera()->getpAxis()->RotationAxis_PivotY(D3DXToRadian(ROTATION_SPEED));

		// �����_�̍쐬
		float length = temp_vector.GetLength();
		temp_vector = *getpCamera()->getpAxis()->GetForawrd();
		temp_vector.AnyLengthVector(length);

		*getpCamera()->getpLookAtPoint() = *getpCamera()->getpPositon() + temp_vector;

		// �O�x�N�g�����쐬( �O�x�N�g�� = ���_���W - �J�������W )
		getpCamera()->getpAxis()->SetForward(*getpCamera()->getpLookAtPoint() 
											 - *getpCamera()->getpPositon());
	}


	// ������
	if (GetKeyboardPress(DIK_Q))
	{
		// �O�x�N�g���̍쐬
		Vector3D temp_vector = *getpCamera()->getpLookAtPoint() 
			- *getpCamera()->getpPositon();
		
		getpCamera()->getpAxis()->SetForward(temp_vector);

		// ���x�N�g���̉�]
		getpCamera()->getpAxis()->RotationAxis_PivotY(D3DXToRadian(-ROTATION_SPEED));

		// �����_�̍쐬
		float length = temp_vector.GetLength();
		temp_vector = *getpCamera()->getpAxis()->GetForawrd();
		temp_vector.AnyLengthVector(length);

		*getpCamera()->getpLookAtPoint() = *getpCamera()->getpPositon() + temp_vector;

		// �O�x�N�g�����쐬( �O�x�N�g�� = ���_���W - �J�������W )
		getpCamera()->getpAxis()->SetForward(*getpCamera()->getpLookAtPoint() 
											 - *getpCamera()->getpPositon());
	}

	// �����
	if (GetKeyboardPress(DIK_T))
	{
		// �O�x�N�g���̍쐬
		Vector3D temp_vector = *getpCamera()->getpLookAtPoint() 
			- *getpCamera()->getpPositon();
		
		getpCamera()->getpAxis()->SetForward(temp_vector);

		// ���x�N�g���̉�]
		getpCamera()->getpAxis()->RotationAxis_PivotRight(D3DXToRadian(-ROTATION_SPEED));

		// �����_�̍쐬
		float length = temp_vector.GetLength();
		temp_vector = *getpCamera()->getpAxis()->GetForawrd();
		temp_vector.AnyLengthVector(length);

		*getpCamera()->getpLookAtPoint() = *getpCamera()->getpPositon() + temp_vector;

		// �O�x�N�g�����쐬( �O�x�N�g�� = ���_���W - �J�������W )
		getpCamera()->getpAxis()->SetForward(*getpCamera()->getpLookAtPoint() 
											 - *getpCamera()->getpPositon());
	}

	// ������
	if (GetKeyboardPress(DIK_G))
	{
		// �O�x�N�g���̍쐬
		Vector3D temp_vector = *getpCamera()->getpLookAtPoint() 
			- *getpCamera()->getpPositon();
	
		getpCamera()->getpAxis()->SetForward(temp_vector);

		// ���x�N�g���̉�]
		getpCamera()->getpAxis()->RotationAxis_PivotRight(D3DXToRadian(ROTATION_SPEED));

		// �����_�̍쐬
		float length = temp_vector.GetLength();
		temp_vector = *getpCamera()->getpAxis()->GetForawrd();
		temp_vector.AnyLengthVector(length);

		*getpCamera()->getpLookAtPoint() = *getpCamera()->getpPositon() + temp_vector;

		// �O�x�N�g�����쐬( �O�x�N�g�� = ���_���W - �J�������W )
		getpCamera()->getpAxis()->SetForward(*getpCamera()->getpLookAtPoint() 
											 - *getpCamera()->getpPositon());
	}


	// �E����( ���_���S )
	if (GetKeyboardPress(DIK_Y))
	{
		// �t�O�x�N�g���̍쐬
		Vector3D temp_vector = *getpCamera()->getpPositon() 
			- *getpCamera()->getpLookAtPoint();
		
		getpCamera()->getpAxis()->SetForward(temp_vector);

		// ���x�N�g���̉�]
		getpCamera()->getpAxis()->RotationAxis_PivotY(D3DXToRadian(ROTATION_SPEED));

		// �J�������W�̍쐬
		float length = temp_vector.GetLength();
		temp_vector = *getpCamera()->getpAxis()->GetForawrd();
		temp_vector.AnyLengthVector(length);

		*getpCamera()->getpPositon() = *getpCamera()->getpLookAtPoint() + temp_vector;

		// �O�x�N�g�����쐬( �O�x�N�g�� = ���_���W - �J�������W )
		getpCamera()->getpAxis()->SetForward(*getpCamera()->getpLookAtPoint() 
											 - *getpCamera()->getpPositon());
	}
	
	// ������( ���_���S )
	if (GetKeyboardPress(DIK_H))
	{
		// �t�O�x�N�g���̍쐬
		Vector3D temp_vector = *getpCamera()->getpPositon() 
			- *getpCamera()->getpLookAtPoint();
		
		getpCamera()->getpAxis()->SetForward(temp_vector);

		// ���x�N�g���̉�]
		getpCamera()->getpAxis()->RotationAxis_PivotY(D3DXToRadian(-ROTATION_SPEED));

		// �J�������W�̍쐬
		float length = temp_vector.GetLength();
		temp_vector = *getpCamera()->getpAxis()->GetForawrd();
		temp_vector.AnyLengthVector(length);

		*getpCamera()->getpPositon() = *getpCamera()->getpLookAtPoint()  + temp_vector;

		// �O�x�N�g�����쐬( �O�x�N�g�� = ���_���W - �J�������W )
		getpCamera()->getpAxis()->SetForward(*getpCamera()->getpLookAtPoint() 
											 - *getpCamera()->getpPositon());
	}
}