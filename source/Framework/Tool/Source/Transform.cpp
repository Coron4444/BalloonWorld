//================================================================================
//!	@file	 Transform.h
//!	@brief	 変形Class
//! @details 
//!	@author  Kai Araki									@date 2017/11/21
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../Transform.h"



//****************************************
// プロパティ定義
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
	// 向くベクトル正規化
	look_at_vector.ChangeNormalize();

	// 初期状態の前ベクトルと向く方向との外積を算出
	Vector3D temp_vector = Vector3D::CreateCross(axis_.getpDefaultForawrd(),
												 &look_at_vector);

	// ターゲットクォータニオンの回転角度の算出
	float temp_dot = Vector3D::CreateDot(axis_.getpDefaultForawrd(), &look_at_vector);

	// 外積に使用したベクトルが平行だった場合
	if ((int)temp_vector.getLengthSquare() == 0)
	{
		// 更にベクトルの向きが真逆だった場合
		if (temp_dot < 0)
		{
			// 初期値のクォータニオンと真逆のターゲットクォータニオンの作成
			setTargetQuaternion(*axis_.getpDefaultUp(), D3DXToRadian(180.0f));
			D3DXQuaternionInverse(&target_quaternion_, &target_quaternion_);
			return;
		}
	}

	// ターゲットクォータニオンの作成
	temp_vector.ChangeNormalize();
	setTargetQuaternion(temp_vector, acosf(temp_dot));
}



void Transform::setTargetQuaternion(Vector3D axis, float angle)
{
	// 変化量をリセット
	look_at_change_amount_ = 0.0f;

	// ターゲットの保存
	old_target_quaternion_ = now_quaternion_;

	// クォータニオンの作成
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
// 関数定義
//****************************************
Transform::Transform()
	: position_(0.0f, 0.0f, 0.0f),
	scale_(1.0f, 1.0f, 1.0f),
	yaw_pitch_roll_angle_(0.0f, 0.0f, 0.0f),
	look_at_speed_(1.0f),
	look_at_change_amount_(0.0f)
{
	// クォータニオンの初期化
	D3DXQuaternionIdentity(&now_quaternion_);
	D3DXQuaternionIdentity(&yaw_pitch_roll_quaternion_);
	D3DXQuaternionIdentity(&old_target_quaternion_);
	D3DXQuaternionIdentity(&target_quaternion_);
}



void Transform::CreateAxis()
{
	// 軸をリセット
	axis_.Reset();

	// 回転行列の更新
	CreateQuaternion();
	matrix_group_.setRotationMatrix(&now_quaternion_);

	// 軸の更新
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
	// YawPitchRollクォータニオンの作成
	D3DXQuaternionIdentity(&yaw_pitch_roll_quaternion_);
	D3DXQuaternionRotationYawPitchRoll(&yaw_pitch_roll_quaternion_, 
									   yaw_pitch_roll_angle_.y, 
									   yaw_pitch_roll_angle_.x,
									   yaw_pitch_roll_angle_.z);

	// 球面線形補完によるクォータニオンの作成
	look_at_change_amount_ += look_at_speed_;
	if (look_at_change_amount_ >= 1.0f) look_at_change_amount_ = 1.0f;
	D3DXQuaternionSlerp(&now_quaternion_, &old_target_quaternion_, &target_quaternion_, 
						look_at_change_amount_);

	// クォータニオンの結合
	D3DXQuaternionMultiply(&now_quaternion_, &now_quaternion_, 
						   &yaw_pitch_roll_quaternion_);
}



void Transform::ReflectMatrix()
{
	matrix_group_.setPositionMatrix(&position_);
	matrix_group_.setScaleMatrix(&scale_);
	matrix_group_.setRotationMatrix(&now_quaternion_);
}