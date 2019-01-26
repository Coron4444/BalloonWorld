//================================================================================
//!	@file	 Transform.h
//!	@brief	 �ό`Class
//! @details 
//!	@author  Kai Araki									@date 2017/11/21
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../Transform.h"



//****************************************
// �v���p�e�B��`
//****************************************
Vector3D* Transform::getpPosition() 
{
	return &position_; 
}



Vector3D* Transform::getpScale() 
{
	return &scale_; 
}



float* Transform::getpAnglePitch()
{
	return &yaw_pitch_roll_angle_.x;
}



float* Transform::getpAngleYaw()
{
	return &yaw_pitch_roll_.y;
}



float* Transform::getpAngleRoll()
{
	return &yaw_pitch_roll_.z;
}



Vector3D* Transform::getpAngleYawPitchRoll()
{
	return &yaw_pitch_roll_;
}



float* Transform::getpLookAtSpeed()
{
	return look_at_speed_;
}



void Transform::setLookAtVector(Vector3D look_at_vector)
{
	// �����x�N�g�����K��
	look_at_vector.ChangeNormalize();

	// ������Ԃ̑O�x�N�g���ƌ��������Ƃ̊O�ς��Z�o
	Vector3D::Create
	Vector3D temp_vector = axis_vector_.GetDefaultForawrd()->CreateVectorCross(look_at_vector);

	// �^�[�Q�b�g�N�H�[�^�j�I���̉�]�p�x�̎Z�o
	float temp_dot = axis_vector_.GetDefaultForawrd()->CreateVectorDot(look_at_vector);

	// �O�ςɎg�p�����x�N�g�������s�������ꍇ
	if ((int)temp_vector.GetLengthSquare() == 0)
	{
		// �X�Ƀx�N�g���̌������^�t�������ꍇ
		if (temp_dot < 0)
		{
			// �����l�̃N�H�[�^�j�I���Ɛ^�t�̃^�[�Q�b�g�N�H�[�^�j�I���̍쐬
			SetTargetQuaternion(*axis_vector_.GetDefaultUp(), D3DXToRadian(180.0f));
			D3DXQuaternionInverse(&target_quaternion_, &target_quaternion_);
			return;
		}
	}


	// �^�[�Q�b�g�N�H�[�^�j�I���̍쐬
	temp_vector.CreateNormalize();
	SetTargetQuaternion(temp_vector, acosf(temp_dot));
}



//======================================================================
//
// ��ÓI�����o�֐���`
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �R���X�g���N�^ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Transform::Transform()
	: position_		        (0.0f, 0.0f, 0.0f),
	  scale_		        (1.0f, 1.0f, 1.0f),
	  yaw_pitch_roll_       (0.0f, 0.0f, 0.0f),
	  look_at_speed_        (1.0f),
	  look_at_change_amount_(0.0f)
{
	// �N�H�[�^�j�I���̏�����
	D3DXQuaternionIdentity(&now_quaternion_);
	D3DXQuaternionIdentity(&yaw_pitch_roll_quaternion_);
	D3DXQuaternionIdentity(&old_target_quaternion_);
	D3DXQuaternionIdentity(&target_quaternion_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �f�X�g���N�^ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Transform::~Transform()
{

}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ���X�V�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Transform::UpdateAxisVector()
{
	// �������Z�b�g
	axis_vector_.ResetAxisVector();

	// ��]�s��̍X�V
	CreateQuaternion();
	matrix_extend_.UpdateRotationMatrix(&now_quaternion_);

	// ���̍X�V
	axis_vector_.RotationMatrix(matrix_extend_.GetRotationMatrix());
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �^�[�Q�b�g�N�H�[�^�j�I���쐬�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Transform::SetTargetQuaternion(Vec3 axis, float angle)
{
	// �ω��ʂ����Z�b�g
	look_at_change_amount_ = 0.0f;

	// �^�[�Q�b�g�̕ۑ�
	old_target_quaternion_ = now_quaternion_;
	
	// �N�H�[�^�j�I���̍쐬
	D3DXQuaternionIdentity(&target_quaternion_);
	D3DXQuaternionRotationAxis(&target_quaternion_, &axis, angle);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ���[���h�s��X�V�֐�(SRT) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Transform::UpdateWorldMatrixSRT()
{
	// �g�k�s��̍X�V
	matrix_extend_.UpdateScaleMatrix(&scale_);

	// ��]�s��̍X�V
	CreateQuaternion();
	matrix_extend_.UpdateRotationMatrix(&now_quaternion_);

	// ���s�ړ��s��̍X�V
	matrix_extend_.UpdateTranslationMatrix(&position_);

	// ���[���h�s��̍X�V
	matrix_extend_.UpdateWorldMatrixSRT();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ���[���h�s��X�V�֐�(ISRT) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Transform::UpdateWorldMatrixISRT()
{
	// �g�k�s��̍X�V
	matrix_extend_.UpdateScaleMatrix(&scale_);

	// ��]�s��̍X�V
	CreateQuaternion();
	matrix_extend_.UpdateRotationMatrix(&now_quaternion_);

	// ���s�ړ��s��̍X�V
	matrix_extend_.UpdateTranslationMatrix(&position_);

	// ���[���h�s��̍X�V
	matrix_extend_.UpdateWorldMatrixISRT();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �������[���h�s��X�V�֐�(SRT) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Transform::UpdateAxisVector_WorldMatrixSRT()
{
	// ��
	UpdateAxisVector();

	// �g�k�s��̍X�V
	matrix_extend_.UpdateScaleMatrix(&scale_);

	// ���s�ړ��s��̍X�V
	matrix_extend_.UpdateTranslationMatrix(&position_);

	// ���[���h�s��̍X�V
	matrix_extend_.UpdateWorldMatrixSRT();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �������[���h�s��X�V�֐�(ISRT) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Transform::UpdateAxisVector_WorldMatrixISRT()
{
	// ��
	UpdateAxisVector();

	// �g�k�s��̍X�V
	matrix_extend_.UpdateScaleMatrix(&scale_);

	// ���s�ړ��s��̍X�V
	matrix_extend_.UpdateTranslationMatrix(&position_);

	// ���[���h�s��̍X�V
	matrix_extend_.UpdateWorldMatrixISRT();
}



//--------------------------------------------------------------------------------
//
// [ �N�H�[�^�j�I���쐬�֐� ]
//
//--------------------------------------------------------------------------------

void Transform::CreateQuaternion()
{
	// YawPitchRoll�N�H�[�^�j�I���̍쐬
	D3DXQuaternionIdentity(&yaw_pitch_roll_quaternion_);
	D3DXQuaternionRotationYawPitchRoll(&yaw_pitch_roll_quaternion_, yaw_pitch_roll_.y, yaw_pitch_roll_.x, yaw_pitch_roll_.z);

	// ���ʐ��`�⊮�ɂ��N�H�[�^�j�I���̍쐬
	look_at_change_amount_ += look_at_speed_;
	if (look_at_change_amount_ >= 1.0f) look_at_change_amount_ = 1.0f;
	D3DXQuaternionSlerp(&now_quaternion_, &old_target_quaternion_, &target_quaternion_, look_at_change_amount_);

	// �N�H�[�^�j�I���̌���
	D3DXQuaternionMultiply(&now_quaternion_, &now_quaternion_, &yaw_pitch_roll_quaternion_);
}