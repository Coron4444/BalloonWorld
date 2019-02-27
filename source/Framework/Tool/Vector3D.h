//================================================================================
//!	@file	 Vector3D.h
//!	@brief	 3DベクトルClass
//! @details 
//!	@author  Kai Araki									@date 2017/11/21
//================================================================================
#ifndef	_VECTOR_3D_H_
#define _VECTOR_3D_H_



//****************************************
// 型定義
//****************************************
using Vec = D3DVECTOR;
using Vec2 = D3DXVECTOR2;
using Vec3 = D3DXVECTOR3;
using Vec4 = D3DXVECTOR4;
using Float16 = D3DXFLOAT16;
using Quaternion = D3DXQUATERNION;
using Color4 = D3DCOLOR;
using XColor4 = D3DXCOLOR;



//****************************************
// クラス宣言
//****************************************
class Matrix;



//************************************************************														   
//! @brief   3DベクトルClass
//!
//! @details 3DのベクトルClass
//************************************************************
class Vector3D : public Vec3
{
//====================
// static関数
//====================
public:
	//----------------------------------------
	//! @brief 内積生成関数
	//! @details
	//! @param *vector0 ベクトル0
	//! @param *vector1 ベクトル1
	//! @retval float 内積値
	//----------------------------------------
	static float CreateDot(Vector3D* vector0, Vector3D* vector1);

	//----------------------------------------
	//! @brief 3点から内積生成関数
	//! @details
	//! @param *point0 点0
	//! @param *point1 点1
	//! @param *point2 点2
	//! @retval float 内積値
	//----------------------------------------
	static float CreateDotPoint3(Vector3D* point0, Vector3D* point1, Vector3D* point2);

	//----------------------------------------
	//! @brief 外積生成関数
	//! @details
	//! @param *vector0 ベクトル0
	//! @param *vector1 ベクトル1
	//! @retval Vector3D 外積値
	//----------------------------------------
	static Vector3D CreateCross(Vector3D* vector0, Vector3D* vector1);

	//----------------------------------------
	//! @brief 3点から外積生成関数
	//! @details
	//! @param *point0 点0
	//! @param *point1 点1
	//! @param *point2 点2
	//! @retval Vector3D 外積値
	//----------------------------------------
	static Vector3D CreateCrossPoint3(Vector3D* point0, Vector3D* point1, Vector3D* point2);

	//----------------------------------------
	//! @brief ラジアン角度生成関数
	//! @details
	//! @param *vector0 ベクトル0
	//! @param *vector1 ベクトル1
	//! @retval float ラジアン角度
	//----------------------------------------
	static float CreateAngleRadian(Vector3D* vector0, Vector3D* vector1);

	//----------------------------------------
	//! @brief デグリー角度生成関数
	//! @details
	//! @param *vector0 ベクトル0
	//! @param *vector1 ベクトル1
	//! @retval float デグリー角度
	//----------------------------------------
	static float CreateAngleDegree(Vector3D* vector0, Vector3D* vector1);


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief X成分取得関数
	//! @details
	//! @param void なし
	//! @retval float X成分
	//----------------------------------------
	float getX() const;

	//----------------------------------------
	//! @brief X成分設定関数
	//! @details
	//! @param value X成分
	//! @retval void なし
	//----------------------------------------
	void setX(float value);

	//----------------------------------------
	//! @brief Y成分取得関数
	//! @details
	//! @param void なし
	//! @retval float Y成分
	//----------------------------------------
	float getY() const;

	//----------------------------------------
	//! @brief Y成分設定関数
	//! @details
	//! @param value X成分
	//! @retval void なし
	//----------------------------------------
	void setY(float value);

	//----------------------------------------
	//! @brief Z成分取得関数
	//! @details
	//! @param void なし
	//! @retval float Z成分
	//----------------------------------------
	float getZ() const;

	//----------------------------------------
	//! @brief Z成分設定関数
	//! @details
	//! @param value Z成分
	//! @retval void なし
	//----------------------------------------
	void setZ(float value);

	//----------------------------------------
	//! @brief X成分の2乗取得関数
	//! @details
	//! @param void なし
	//! @retval float X成分の2乗
	//----------------------------------------
	float getSquareX() const;

	//----------------------------------------
	//! @brief Y成分の2乗取得関数
	//! @details
	//! @param void なし
	//! @retval float Y成分の2乗
	//----------------------------------------
	float getSquareY() const;

	//----------------------------------------
	//! @brief Z成分の2乗取得関数
	//! @details
	//! @param void なし
	//! @retval float Z成分の2乗
	//----------------------------------------
	float getSquareZ() const;

	//----------------------------------------
	//! @brief 長さ取得関数
	//! @details
	//! @param void なし
	//! @retval float 長さ
	//----------------------------------------
	float getLength() const;

	//----------------------------------------
	//! @brief 長さの2乗取得関数
	//! @details
	//! @param void なし
	//! @retval float 長さの2乗
	//----------------------------------------
	float getLengthSquare() const;

	//----------------------------------------
	//! @brief Xの長さ取得関数
	//! @details
	//! @param void なし
	//! @retval float Xの長さ
	//----------------------------------------
	float getLengthX() const;

	//----------------------------------------
	//! @brief Yの長さ取得関数
	//! @details
	//! @param void なし
	//! @retval float Yの長さ
	//----------------------------------------
	float getLengthY() const;

	//----------------------------------------
	//! @brief Zの長さ取得関数
	//! @details
	//! @param void なし
	//! @retval float Zの長さ
	//----------------------------------------
	float getLengthZ() const;

	//----------------------------------------
	//! @brief XYの長さ取得関数
	//! @details
	//! @param void なし
	//! @retval float XYの長さ
	//----------------------------------------
	float getLengthXY() const;

	//----------------------------------------
	//! @brief XZの長さ取得関数
	//! @details
	//! @param void なし
	//! @retval float XZの長さ
	//----------------------------------------
	float getLengthXZ() const;

	//----------------------------------------
	//! @brief YZの長さ取得関数
	//! @details
	//! @param void なし
	//! @retval float YZの長さ
	//----------------------------------------
	float getLengthYZ() const;


//====================
// 演算子
//====================
public:
	//----------------------------------------
	//! @brief <演算子
	//! @details
	//! @param vector ベクター
	//! @retval bool 判定の有無
	//----------------------------------------
	bool operator < (const Vector3D& vector) const;

	//----------------------------------------
	//! @brief >演算子
	//! @details
	//! @param vector ベクター
	//! @retval bool 判定の有無
	//----------------------------------------
	bool operator > (const Vector3D& vector) const;

	//----------------------------------------
	//! @brief <=演算子
	//! @details
	//! @param vector ベクター
	//! @retval bool 判定の有無
	//----------------------------------------
	bool operator <= (const Vector3D& vector) const;

	//----------------------------------------
	//! @brief >=演算子
	//! @details
	//! @param vector ベクター
	//! @retval bool 判定の有無
	//----------------------------------------
	bool operator >= (const Vector3D& vector) const;

//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief コンストラクタ関数
	//! @details
	//! @param void なし
	//----------------------------------------
	Vector3D();

	//----------------------------------------
	//! @brief 単一floatコンストラクタ関数
	//! @details
	//! @param value 成分
	//----------------------------------------
	Vector3D(const float* value);

	//----------------------------------------
	//! @brief 単一float16コンストラクタ関数
	//! @details
	//! @param value 成分
	//----------------------------------------
	Vector3D(const Float16* value);

	//----------------------------------------
	//! @brief 複数floatコンストラクタ関数
	//! @details
	//! @param value_x X成分
	//! @param value_y Y成分
	//! @param value_z Z成分
	//----------------------------------------
	Vector3D(float value_x, float value_y, float value_z);

	//----------------------------------------
	//! @brief ベクターコンストラクタ関数
	//! @details
	//! @param vector ベクター
	//----------------------------------------
	Vector3D(const Vec& vector);

	//----------------------------------------
	//! @brief デストラクタ関数
	//! @details
	//----------------------------------------
	virtual ~Vector3D();

	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Init();

	//----------------------------------------
	//! @brief 正規化関数
	//! @details
	//! @param void なし
	//! @retval Vector3D* 変更後ベクトル
	//----------------------------------------
	Vector3D* ChangeNormalize();

	//----------------------------------------
	//! @brief 任意の長さに変更関数
	//! @details
	//! @param length 長さ
	//! @retval Vector3D* 変更後ベクトル
	//----------------------------------------
	Vector3D* ChangeAnyLength(float length);

	//----------------------------------------
	//! @brief Xを任意の長さに変更関数
	//! @details
	//! @param length 長さ
	//! @retval Vector3D* 変更後ベクトル
	//----------------------------------------
	Vector3D* ChangeAnyLengthX(float length);

	//----------------------------------------
	//! @brief Yを任意の長さに変更関数
	//! @details
	//! @param length 長さ
	//! @retval Vector3D* 変更後ベクトル
	//----------------------------------------
	Vector3D* ChangeAnyLengthY(float length);

	//----------------------------------------
	//! @brief Zを任意の長さに変更関数
	//! @details
	//! @param length 長さ
	//! @retval Vector3D* 変更後ベクトル
	//----------------------------------------
	Vector3D* ChangeAnyLengthZ(float length);

	//----------------------------------------
	//! @brief XYを任意の長さに変更関数
	//! @details
	//! @param length 長さ
	//! @retval Vector3D* 変更後ベクトル
	//----------------------------------------
	Vector3D* ChangeAnyLengthXY(float length);

	//----------------------------------------
	//! @brief XZを任意の長さに変更関数
	//! @details
	//! @param length 長さ
	//! @retval Vector3D* 変更後ベクトル
	//----------------------------------------
	Vector3D* ChangeAnyLengthXZ(float length);

	//----------------------------------------
	//! @brief YZを任意の長さに変更関数
	//! @details
	//! @param length 長さ
	//! @retval Vector3D* 変更後ベクトル
	//----------------------------------------
	Vector3D* ChangeAnyLengthYZ(float length);

	//----------------------------------------
	//! @brief X軸回転関数
	//! @details
	//! @param radian 角度
	//! @retval Vector3D* 変更後ベクトル
	//----------------------------------------
	Vector3D* RotationAxisX(float radian);

	//----------------------------------------
	//! @brief Y軸回転関数
	//! @details
	//! @param radian 角度
	//! @retval Vector3D* 変更後ベクトル
	//----------------------------------------
	Vector3D* RotationAxisY(float radian);

	//----------------------------------------
	//! @brief Z軸回転関数
	//! @details
	//! @param radian 角度
	//! @retval Vector3D* 変更後ベクトル
	//----------------------------------------
	Vector3D* RotationAxisZ(float radian);

	//----------------------------------------
	//! @brief 任意軸回転関数
	//! @details
	//! @param axis   軸
	//! @param radian 角度
	//! @retval Vector3D* 変更後ベクトル
	//----------------------------------------
	Vector3D* RotationAxisAny(Vector3D axis, float radian);

	//----------------------------------------
	//! @brief 行列回転関数
	//! @details
	//! @param matrix 行列
	//! @retval Vector3D* 変更後ベクトル
	//----------------------------------------
	Vector3D* RotationMatrix(Matrix* matrix);

	//----------------------------------------
	//! @brief クォータニオン回転回転関数
	//! @details
	//! @param quaternion クォータニオン
	//! @retval Vector3D* 変更後ベクトル
	//----------------------------------------
	Vector3D* RotationQuaternion(Quaternion* quaternion);
};



#endif