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
	return &yaw_pitch_roll_angle_.y;
}



float* Transform::getpAngleRoll()
{
	return &yaw_pitch_roll_angle_.z;
}



Vector3D* Transform::getpAngleYawPitchRoll()
{
	return &yaw_pitch_roll_angle_;
}



float* Transform::getpLookAtSpeed()
{
	return &look_at_speed_;
}



void Transform::setLookAtVector(Vector3D look_at_vector)
{
	// �����x�N�g�����K��
	look_at_vector.ChangeNormalize();

	// ������Ԃ̑O�x�N�g���ƌ��������Ƃ̊O�ς��Z�o
	Vector3D temp_vector = Vector3D::CreateCross(axis_.getpDefaultForawrd(),
												 &look_at_vector);

	// �^�[�Q�b�g�N�H�[�^�j�I���̉�]�p�x�̎Z�o
	float temp_dot = Vector3D::CreateDot(axis_.getpDefaultForawrd(), &look_at_vector);

	// �O�ςɎg�p�����x�N�g�������s�������ꍇ
	if ((int)temp_vector.getLengthSquare() == 0)
	{
		// �X�Ƀx�N�g���̌������^�t�������ꍇ
		if (temp_dot < 0)
		{
			// �����l�̃N�H�[�^�j�I���Ɛ^�t�̃^�[�Q�b�g�N�H�[�^�j�I���̍쐬
			setTargetQuaternion(*axis_.getpDefaultUp(), D3DXToRadian(180.0f));
			D3DXQuaternionInverse(&target_quaternion_, &target_quaternion_);
			return;
		}
	}

	// �^�[�Q�b�g�N�H�[�^�j�I���̍쐬
	temp_vector.ChangeNormalize();
	setTargetQuaternion(temp_vector, acosf(temp_dot));
}



void Transform::setTargetQuaternion(Vector3D axis, float angle)
{
	// �ω��ʂ����Z�b�g
	look_at_change_amount_ = 0.0f;

	// �^�[�Q�b�g�̕ۑ�
	old_target_quaternion_ = now_quaternion_;

	// �N�H�[�^�j�I���̍쐬
	D3DXQuaternionIdentity(&target_quaternion_);
	D3DXQuaternionRotationAxis(&target_quaternion_, &axis, angle);
}



Vector3D* Transform::getpForawrd()
{
	return axis_.getpForawrd();
}



Vector3D* Transform::getpUp()
{
	return axis_.getpUp();
}



Vector3D* Transform::getpRight()
{
	return axis_.getpRight();
}



Axis* Transform::getpAxis()
{
	return &axis_;
}



MATRIX* Transform::getpPositionMatrix()
{
	return matrix_group_.getpPositionMatrix();
}



MATRIX* Transform::getpScaleMatrix()
{
	return matrix_group_.getpScaleMatrix();
}



MATRIX* Transform::getpRotationMatrix()
{
	return matrix_group_.getpRotationMatrix();
}



MATRIX* Transform::getpInverseMatrix()
{
	return matrix_group_.getpInverseMatrix();
}



void Transform::setInverseMatrix(MATRIX* value)
{
	matrix_group_.setInverseMatrix(value);
}



MATRIX* Transform::getpTransposeMatrix()
{
	return matrix_group_.getpTransposeMatrix();
}



void Transform::setTransposeMatrix(MATRIX* value, bool is_position_off)
{
	matrix_group_.setTransposeMatrix(value, is_position_off);
}



MATRIX* Transform::getpWorldMatrix()
{
	return matrix_group_.getpWorldMatrix();
}



MatrixGroup* Transform::getpMatrixGroup()
{
	return &matrix_group_;
}



//****************************************
// �֐���`
//****************************************
Transform::Transform()
	: position_(0.0f, 0.0f, 0.0f),
	scale_(1.0f, 1.0f, 1.0f),
	yaw_pitch_roll_angle_(0.0f, 0.0f, 0.0f),
	look_at_speed_(1.0f),
	look_at_change_amount_(0.0f)
{
	// �N�H�[�^�j�I���̏�����
	D3DXQuaternionIdentity(&now_quaternion_);
	D3DXQuaternionIdentity(&yaw_pitch_roll_quaternion_);
	D3DXQuaternionIdentity(&old_target_quaternion_);
	D3DXQuaternionIdentity(&target_quaternion_);
}



void Transform::CreateAxis()
{
	// �������Z�b�g
	axis_.Reset();

	// ��]�s��̍X�V
	CreateQuaternion();
	matrix_group_.setRotationMatrix(&now_quaternion_);

	// ���̍X�V
	axis_.RotationMatrix(matrix_group_.getpRotationMatrix());
}



void Transform::CreateWorldMatrix()
{
	ReflectMatrix();
	matrix_group_.CreateWorldMatrix();
}



void Transform::CreateWorldMatrixPlusInverse()
{
	ReflectMatrix();
	matrix_group_.CreateWorldMatrixPlusInverse();
}



void Transform::CreateWorldMatrixPlusTranspose()
{
	ReflectMatrix();
	matrix_group_.CreateWorldMatrixPlusTranspose();
}



void Transform::AddParentMatrixToWorldMatrix(MATRIX* parent_matrix)
{
	matrix_group_.AddParentMatrixToWorldMatrix(parent_matrix);
}



void Transform::CreateAxisAndWorldMatrix()
{
	CreateAxis();
	CreateWorldMatrix();
}



void Transform::CreateAxisAndWorldMatrixPlusInverse()
{
	CreateAxis();
	CreateWorldMatrixPlusInverse();
}



void Transform::CreateAxisAndWorldMatrixPlusTranspose()
{
	CreateAxis();
	CreateWorldMatrixPlusTranspose();
}



void Transform::CreateQuaternion()
{
	// YawPitchRoll�N�H�[�^�j�I���̍쐬
	D3DXQuaternionIdentity(&yaw_pitch_roll_quaternion_);
	D3DXQuaternionRotationYawPitchRoll(&yaw_pitch_roll_quaternion_, 
									   yaw_pitch_roll_angle_.y, 
									   yaw_pitch_roll_angle_.x,
									   yaw_pitch_roll_angle_.z);

	// ���ʐ��`�⊮�ɂ��N�H�[�^�j�I���̍쐬
	look_at_change_amount_ += look_at_speed_;
	if (look_at_change_amount_ >= 1.0f) look_at_change_amount_ = 1.0f;
	D3DXQuaternionSlerp(&now_quaternion_, &old_target_quaternion_, &target_quaternion_, 
						look_at_change_amount_);

	// �N�H�[�^�j�I���̌���
	D3DXQuaternionMultiply(&now_quaternion_, &now_quaternion_, 
						   &yaw_pitch_roll_quaternion_);
}



void Transform::ReflectMatrix()
{
	matrix_group_.setPositionMatrix(&position_);
	matrix_group_.setScaleMatrix(&scale_);
	matrix_group_.setRotationMatrix(&now_quaternion_);
}