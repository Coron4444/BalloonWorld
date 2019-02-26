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



void Transform::setInitAngle(Vector3D value)
{
	D3DXQuaternionIdentity(&init_quaternion_);
	D3DXQuaternionRotationYawPitchRoll(&init_quaternion_,
									   value.y,
									   value.x,
									   value.z);
}



void Transform::setAddQuaternion(Quaternion value)
{
	D3DXQuaternionMultiply(&add_quaternion_, &add_quaternion_,
						   &value);
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
	Vector3D temp_vector = Vector3D::CreateCross(world_matrix_.getpDefaultForward(),
												 &look_at_vector);

	// ターゲットクォータニオンの回転角度の算出
	float temp_dot = Vector3D::CreateDot(world_matrix_.getpDefaultForward(), &look_at_vector);

	// 外積に使用したベクトルが平行だった場合
	if (temp_vector.getLengthSquare() <= 0.0f)
	{
		// ベクトルの向きが真逆だった場合
		if (temp_dot < 0)
		{
			// 初期値のクォータニオンと真逆のターゲットクォータニオンの作成
			setTargetQuaternion(*world_matrix_.getpDefaultUp(), D3DXToRadian(180.0f));
			D3DXQuaternionInverse(&target_quaternion_, &target_quaternion_);
			return;
		}
		else
		{
			// 初期値のクォータニオンでターゲットクォータニオンの作成
			setTargetQuaternion(*world_matrix_.getpDefaultUp(), D3DXToRadian(0.0f));
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



Vector3D* Transform::getpForward()
{
	return no_init_rotation_world_matrix_.getpForward();
}



Vector3D* Transform::getpUp()
{
	return no_init_rotation_world_matrix_.getpUp();
}



Vector3D* Transform::getpRight()
{
	return no_init_rotation_world_matrix_.getpRight();
}



Matrix* Transform::getpPositionMatrix()
{
	return &position_matrix_;
	
}



Matrix* Transform::getpScaleMatrix()
{
	return &scale_matrix_;
}



Matrix* Transform::getpRotationMatrix()
{
	return &rotation_matrix_;
}



Matrix* Transform::getpNoInitRotationMatrix()
{
	return &no_init_rotation_matrix_;
}



Matrix* Transform::getpInverseMatrix()
{
	return &inverse_matrix_;
}



void Transform::setInverseMatrix(Matrix* value)
{
	value->ChangeInverse();
	inverse_matrix_ = *value;
}



Matrix* Transform::getpTransposeMatrix()
{
	return &transpose_matrix_;
}



void Transform::setTransposeMatrix(Matrix* value, bool is_position_off)
{
	value->ChangeTranspose(is_position_off);
	transpose_matrix_ = *value;
}



Matrix* Transform::getpWorldMatrix()
{
	return &world_matrix_;
}



Matrix* Transform::getpNoInitRotationWorldMatrix()
{
	return &no_init_rotation_world_matrix_;
}



//****************************************
// 関数定義
//****************************************
Transform::Transform() : 
	position_(0.0f, 0.0f, 0.0f),
	scale_(1.0f, 1.0f, 1.0f),
	yaw_pitch_roll_angle_(0.0f, 0.0f, 0.0f),
	look_at_speed_(1.0f),
	look_at_change_amount_(0.0f)
{
	// 行列
	position_matrix_.Init();
	scale_matrix_.Init();			
	rotation_matrix_.Init();
	no_init_rotation_matrix_.Init();
	inverse_matrix_.Init();	
	transpose_matrix_.Init();
	world_matrix_.Init();	
	no_init_rotation_world_matrix_.Init();

	// クォータニオン
	D3DXQuaternionIdentity(&init_quaternion_);
	D3DXQuaternionIdentity(&now_quaternion_);
	D3DXQuaternionIdentity(&add_quaternion_);
	D3DXQuaternionIdentity(&yaw_pitch_roll_quaternion_);
	D3DXQuaternionIdentity(&old_target_quaternion_);
	D3DXQuaternionIdentity(&target_quaternion_);
}



Transform::~Transform()
{
}



void Transform::Init()
{
	position_ = {0.0f, 0.0f, 0.0f};
	scale_ = {1.0f, 1.0f, 1.0f};
	yaw_pitch_roll_angle_ = {0.0f, 0.0f, 0.0f};
	look_at_speed_ = 1.0f;
	look_at_change_amount_ = 0.0f;

	// 行列
	position_matrix_.Init();
	scale_matrix_.Init();
	rotation_matrix_.Init();
	no_init_rotation_matrix_.Init();
	inverse_matrix_.Init();
	transpose_matrix_.Init();
	world_matrix_.Init();
	no_init_rotation_world_matrix_.Init();

	// クォータニオン
	D3DXQuaternionIdentity(&init_quaternion_);
	D3DXQuaternionIdentity(&now_quaternion_);
	D3DXQuaternionIdentity(&add_quaternion_);
	D3DXQuaternionIdentity(&yaw_pitch_roll_quaternion_);
	D3DXQuaternionIdentity(&old_target_quaternion_);
	D3DXQuaternionIdentity(&target_quaternion_);
}



void Transform::ResetAddQuaternion()
{
	// 追加用初期化
	D3DXQuaternionIdentity(&add_quaternion_);
}



void Transform::AddParentMatrixToWorldMatrix(Matrix* parent_matrix)
{
	D3DXMatrixMultiply(&world_matrix_, &world_matrix_, parent_matrix);
}



void Transform::CreateWorldMatrix()
{
	CreateQuaternion();
	ReflectMatrix();
	CalculateWorldMatrix();
}



void Transform::CreateWorldMatrixPlusInverse()
{
	CreateQuaternion();
	ReflectMatrix();
	CalculateWorldMatrixPlusInverse();
}



void Transform::CreateWorldMatrixPlusTranspose()
{
	CreateQuaternion();
	ReflectMatrix();
	CalculateWorldMatrixPlusTranspose();
}



void Transform::CreateQuaternion()
{
	// 現在のクォータニオン初期化
	D3DXQuaternionIdentity(&now_quaternion_);

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
	
	// YawPitchRoll→球面線形補完→追加の順で結合
	D3DXQuaternionMultiply(&now_quaternion_, &yaw_pitch_roll_quaternion_,
						   &now_quaternion_);
	D3DXQuaternionMultiply(&now_quaternion_, &now_quaternion_,
						   &add_quaternion_);
}



void Transform::ReflectMatrix()
{
	// 平行移動&拡縮行列算出
	position_matrix_.CreatePosition(&position_);
	scale_matrix_.CreateScale(&scale_);

	// 初期回転無し回転行列算出
	no_init_rotation_matrix_.CreateRotationQuaternion(&now_quaternion_);

	// 初期回転有り回転行列作成(初期用→YawPitchRoll→球面線形補完→追加の順で結合)
	Quaternion rotation;
	D3DXQuaternionMultiply(&rotation, &init_quaternion_,
						   &now_quaternion_);
	rotation_matrix_.CreateRotationQuaternion(&rotation);
}



void Transform::CalculateWorldMatrix()
{
	// ワールド行列
	world_matrix_.CreateWorld(&scale_matrix_, &rotation_matrix_, &position_matrix_);

	// 初期回転無しワールド行列
	no_init_rotation_world_matrix_.CreateWorld(&scale_matrix_, &no_init_rotation_matrix_, &position_matrix_);
}



void Transform::CalculateWorldMatrixPlusInverse()
{
	CalculateWorldMatrix();

	// ワールド行列
	world_matrix_.AddChildMatrix(&inverse_matrix_);

	// 初期回転無しワールド行列
	no_init_rotation_world_matrix_.AddChildMatrix(&inverse_matrix_);
}



void Transform::CalculateWorldMatrixPlusTranspose()
{
	CalculateWorldMatrix();

	// ワールド行列
	world_matrix_.AddChildMatrix(&transpose_matrix_);

	// 初期回転無しワールド行列
	no_init_rotation_world_matrix_.AddChildMatrix(&transpose_matrix_);
}