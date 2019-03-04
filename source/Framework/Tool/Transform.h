//================================================================================
//!	@file	 Transform.h
//!	@brief	 変形Class
//! @details 
//!	@author  Kai Araki									@date 2017/11/21
//================================================================================
#ifndef	_TRANSFORM_H_
#define _TRANSFORM_H_



//************************************************************														   
//! @brief   変形Class
//!
//! @details オブジェクトの変形を表すClass
//************************************************************
class Transform
{
//====================
// 変数
//====================
private:
	Vector3D position_;								//!< 座標
	Vector3D scale_;								//!< 拡縮
	Quaternion init_quaternion_;					//!< 初期値クォータニオン
	Quaternion now_quaternion_;						//!< 現在用クォータニオン
	Quaternion add_quaternion_;						//!< 追加用クォータニオン
	Quaternion yaw_pitch_roll_quaternion_;			//!< YawPitchRollクォータニオン
	Quaternion target_quaternion_;					//!< ターゲットクォータニオン
	Quaternion old_target_quaternion_;				//!< 古いターゲットクォータニオン
	Vector3D yaw_pitch_roll_angle_;					//!< YawPitchRoll角度
	float look_at_speed_;							//!< 向く速度
	float look_at_change_amount_;					//!< 向く変化量
	Matrix position_matrix_;						//!< 座標行列
	Matrix scale_matrix_;							//!< 拡縮行列
	Matrix rotation_matrix_;						//!< 回転行列
	Matrix no_init_rotation_matrix_;				//!< 初期回転無し回転行列
	Matrix inverse_matrix_;							//!< 逆行列
	Matrix transpose_matrix_;						//!< 転置行列
	Matrix world_matrix_;							//!< ワールド行列
	Matrix no_init_rotation_world_matrix_;			//!< 初期回転無しワールド行列


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief 座標取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D* 座標
	//----------------------------------------
	Vector3D* getpPosition();

	//----------------------------------------
	//! @brief 拡縮取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D* 座標
	//----------------------------------------
	Vector3D* getpScale();

	//----------------------------------------
	//! @brief 初期角度取得関数
	//! @details
	//! @param value 角度
	//! @retval void なし
	//----------------------------------------
	void setInitAngle(Vector3D value);

	//----------------------------------------
	//! @brief 追加用クォータニオン設定関数
	//! @details
	//! @param value 追加用クォータニオン
	//! @retval void なし
	//----------------------------------------
	void setAddQuaternion(Quaternion value);

	//----------------------------------------
	//! @brief Pitch角度取得関数
	//! @details
	//! @param void なし
	//! @retval float* Pitch角度
	//----------------------------------------
	float* getpAnglePitch();

	//----------------------------------------
	//! @brief Yaw角度取得関数
	//! @details
	//! @param void なし
	//! @retval float* Yaw角度
	//----------------------------------------
	float* getpAngleYaw();

	//----------------------------------------
	//! @brief Roll角度取得関数
	//! @details
	//! @param void なし
	//! @retval float* Roll角度
	//----------------------------------------
	float* getpAngleRoll();

	//----------------------------------------
	//! @brief YawPitchRoll角度取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D* YawPitchRoll角度
	//----------------------------------------
	Vector3D* getpAngleYawPitchRoll();

	//----------------------------------------
	//! @brief 向く速度取得関数
	//! @details
	//! @param void なし
	//! @retval float* 向く速度
	//----------------------------------------
	float* getpLookAtSpeed();

	//----------------------------------------
	//! @brief 向くベクトル設定関数
	//! @details
	//! @param look_at_vector 向くベクトル
	//! @retval void なし
	//----------------------------------------
	void setLookAtVector(Vector3D look_at_vector);

	//----------------------------------------
	//! @brief ターゲットクォータニオン設定関数
	//! @details
	//! @param axis  軸
	//! @param angle 角度
	//! @retval void なし
	//----------------------------------------
	void setTargetQuaternion(Vector3D axis, float angle);

	//----------------------------------------
	//! @brief 前ベクトル取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D* 前ベクトル
	//----------------------------------------
	Vector3D* getpForward();

	//----------------------------------------
	//! @brief 上ベクトル取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D* 上ベクトル
	//----------------------------------------
	Vector3D* getpUp();

	//----------------------------------------
	//! @brief 右ベクトル取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D* 右ベクトル
	//----------------------------------------
	Vector3D* getpRight();

	//----------------------------------------
	//! @brief 座標行列取得関数
	//! @details
	//! @param void
	//! @retval Matrix* 座標行列
	//----------------------------------------
	Matrix* getpPositionMatrix();

	//----------------------------------------
	//! @brief 拡縮行列取得関数
	//! @details
	//! @param void
	//! @retval Matrix* 拡縮行列
	//----------------------------------------
	Matrix* getpScaleMatrix();

	//----------------------------------------
	//! @brief 回転行列取得関数
	//! @details
	//! @param void
	//! @retval Matrix* 拡縮行列
	//----------------------------------------
	Matrix* getpRotationMatrix();

	//----------------------------------------
	//! @brief 初期回転無し回転行列取得関数
	//! @details
	//! @param void
	//! @retval Matrix* 拡縮行列
	//----------------------------------------
	Matrix* getpNoInitRotationMatrix();

	//----------------------------------------
	//! @brief 逆行列取得関数
	//! @details
	//! @param void
	//! @retval Matrix* 逆行列
	//----------------------------------------
	Matrix* getpInverseMatrix();

	//----------------------------------------
	//! @brief 逆行列設定関数
	//! @details
	//! @param value 逆行列にしたい行列
	//! @retval void なし
	//----------------------------------------
	void setInverseMatrix(Matrix* value);

	//----------------------------------------
	//! @brief 転置行列取得関数
	//! @details
	//! @param void
	//! @retval Matrix* 転置行列
	//----------------------------------------
	Matrix* getpTransposeMatrix();

	//----------------------------------------
	//! @brief 転置行列設定関数
	//! @details
	//! @param value           転置行列にしたい行列
	//! @param is_position_off 平行移動OFFフラグ
	//! @retval void なし
	//----------------------------------------
	void setTransposeMatrix(Matrix* value, bool is_position_off = false);

	//----------------------------------------
	//! @brief ワールド行列取得関数
	//! @details
	//! @param void
	//! @retval Matrix* ワールド行列
	//----------------------------------------
	Matrix* getpWorldMatrix();

	//----------------------------------------
	//! @brief 初期回転無しワールド行列取得関数
	//! @details
	//! @param void
	//! @retval Matrix* 初期回転無しワールド行列
	//----------------------------------------
	Matrix* getpNoInitRotationWorldMatrix();


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief コンストラクタ
	//! @details
	//! @param void なし
	//----------------------------------------
	Transform();

	//----------------------------------------
	//! @brief デストラクタ
	//! @details
	//----------------------------------------
	~Transform();

	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Init();

	//----------------------------------------
	//! @brief 追加用クォータニオンリセット関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void ResetAddQuaternion();

	//----------------------------------------
	//! @brief ワールド行列に親行列追加関数
	//! @details
	//! @param parent_matrix 親の行列
	//! @retval void なし
	//----------------------------------------
	void AddParentMatrixToWorldMatrix(Matrix* parent_matrix);

	//----------------------------------------
	//! @brief ワールド行列作成関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void CreateWorldMatrix();

	//----------------------------------------
	//! @brief 逆行列付きワールド行列作成関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void CreateWorldMatrixPlusInverse();

	//----------------------------------------
	//! @brief 転置行列付きワールド行列作成関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void CreateWorldMatrixPlusTranspose();


private :
	//----------------------------------------
	//! @brief クォータニオン作成関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void CreateQuaternion();

	//----------------------------------------
	//! @brief 行列反映関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void ReflectMatrix();

	//----------------------------------------
	//! @brief ワールド行列算出関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void CalculateWorldMatrix();

	//----------------------------------------
	//! @brief 逆行列付きワールド行列算出関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void CalculateWorldMatrixPlusInverse();

	//----------------------------------------
	//! @brief 転置列付きワールド行列算出関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void CalculateWorldMatrixPlusTranspose();
};



#endif