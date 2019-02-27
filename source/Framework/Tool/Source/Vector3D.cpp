//================================================================================
//!	@file	 Vector3D.cpp
//!	@brief	 3DベクトルClass
//! @details 
//!	@author  Kai Araki									@date 2017/11/21
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../Vector3D.h"



//****************************************
// static関数定義
//****************************************
float Vector3D::CreateDot(Vector3D* vector0, Vector3D* vector1)
{
	return D3DXVec3Dot(vector0, vector1);
}



float Vector3D::CreateDotPoint3(Vector3D* point0, Vector3D* point1, Vector3D* point2)
{
	Vector3D vector0(*point0 - *point1);
	Vector3D vector1(*point2 - *point1);
	return CreateDot(&vector0, &vector1);
}



Vector3D Vector3D::CreateCross(Vector3D* vector0, Vector3D* vector1)
{
	Vector3D temp_vector;
	D3DXVec3Cross(&temp_vector, vector0, vector1);
	return temp_vector;
}



Vector3D Vector3D::CreateCrossPoint3(Vector3D* point0, Vector3D* point1, Vector3D* point2)
{
	Vector3D vector0(*point1 - *point0);
	Vector3D vector1(*point2 - *point1);
	return CreateCross(&vector0, &vector1);
}



float Vector3D::CreateAngleRadian(Vector3D* vector0, Vector3D* vector1)
{
	return acosf(D3DXVec3Dot(vector0, vector1));
}



float Vector3D::CreateAngleDegree(Vector3D* vector0, Vector3D* vector1)
{
	return D3DXToDegree(CreateAngleRadian(vector0, vector1));
}



//****************************************
// プロパティ定義
//****************************************
float Vector3D::getX() const
{
	return x;
}



void Vector3D::setX(float value)
{
	x = value;
}



float Vector3D::getY() const
{
	return y;
}



void Vector3D::setY(float value)
{
	z = value;
}



float Vector3D::getZ() const
{
	return z;
}



void Vector3D::setZ(float value)
{
	z = value;
}



float Vector3D::getSquareX() const
{
	return x * x;
}



float Vector3D::getSquareY() const
{
	return y * y;
}



float Vector3D::getSquareZ() const
{
	return z * z;
}



float Vector3D::getLength() const
{
	return D3DXVec3Length(this);
}



float Vector3D::getLengthSquare() const
{
	return getSquareX() + getSquareY() + getSquareZ();
}



float Vector3D::getLengthX() const
{
	return fabsf(x);
}



float Vector3D::getLengthY() const
{
	return fabsf(y);
}



float Vector3D::getLengthZ() const
{
	return fabsf(z);
}



float Vector3D::getLengthXY() const
{
	Vector3D temp_vector(x, y, 0.0f);

	return D3DXVec3Length(&temp_vector);
}



float Vector3D::getLengthXZ() const
{
	Vector3D temp_vector(x, 0.0f, z);

	return D3DXVec3Length(&temp_vector);
}



float Vector3D::getLengthYZ() const
{
	Vector3D temp_vector(0.0f, y, z);

	return D3DXVec3Length(&temp_vector);
}



//****************************************
// 演算子定義
//****************************************
bool Vector3D::operator < (const Vector3D& vector) const
{
	if (x >= vector.x) return false;
	if (y >= vector.y) return false;
	if (z >= vector.z) return false;
	return true;
}



bool Vector3D::operator > (const Vector3D& vector) const
{
	if (x <= vector.x) return false;
	if (y <= vector.y) return false;
	if (z <= vector.z) return false;
	return true;
}



bool Vector3D::operator <= (const Vector3D& vector) const
{
	if (x > vector.x) return false;
	if (y > vector.y) return false;
	if (z > vector.z) return false;
	return true;
}



bool Vector3D::operator >= (const Vector3D& vector) const
{
	if (x < vector.x) return false;
	if (y < vector.y) return false;
	if (z < vector.z) return false;
	return true;
}



//****************************************
// 関数定義
//****************************************
Vector3D::Vector3D()
	: Vec3(0.0f, 0.0f, 0.0f)
{
}



Vector3D::Vector3D(const float* value)
	: Vec3(value)
{
}



Vector3D::Vector3D(const Float16* value)
	: Vec3(value)
{
}



Vector3D::Vector3D(float value_x, float value_y, float value_z)
	: Vec3(value_x, value_y, value_z)
{
}



Vector3D::Vector3D(const Vec& vector)
	: Vec3(vector)
{
}



Vector3D::~Vector3D()
{
}



void Vector3D::Init()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}



Vector3D* Vector3D::ChangeNormalize()
{
	D3DXVec3Normalize(this, this);
	return this;
}



Vector3D* Vector3D::ChangeAnyLength(float length)
{
	ChangeNormalize();
	*this *= length;
	return this;
}



Vector3D* Vector3D::ChangeAnyLengthX(float length)
{
	Vector3D temp_vector(x, 0.0f, 0.0f);
	D3DXVec3Normalize(&temp_vector, &temp_vector);
	temp_vector *= length;
	x = temp_vector.x;
	return this;
}



Vector3D* Vector3D::ChangeAnyLengthY(float length)
{
	Vector3D temp_vector(0.0f, y, 0.0f);
	D3DXVec3Normalize(&temp_vector, &temp_vector);
	temp_vector *= length;
	y = temp_vector.y;
	return this;
}



Vector3D* Vector3D::ChangeAnyLengthZ(float length)
{
	Vector3D temp_vector(0.0f, 0.0f, z);
	D3DXVec3Normalize(&temp_vector, &temp_vector);
	temp_vector *= length;
	z = temp_vector.z;
	return this;
}



Vector3D* Vector3D::ChangeAnyLengthXY(float length)
{
	Vector3D temp_vector(x, y, 0.0f);
	D3DXVec3Normalize(&temp_vector, &temp_vector);
	temp_vector *= length;
	x = temp_vector.x;
	y = temp_vector.y;
	return this;
}



Vector3D* Vector3D::ChangeAnyLengthXZ(float length)
{
	Vector3D temp_vector(x, 0.0f, z);
	D3DXVec3Normalize(&temp_vector, &temp_vector);
	temp_vector *= length;
	x = temp_vector.x;
	z = temp_vector.z;
	return this;
}



Vector3D* Vector3D::ChangeAnyLengthYZ(float length)
{
	Vector3D temp_vector(0.0f, y, z);
	D3DXVec3Normalize(&temp_vector, &temp_vector);
	temp_vector *= length;
	y = temp_vector.y;
	z = temp_vector.z;
	return this;
}



Vector3D* Vector3D::RotationAxisX(float radian)
{
	Matrix matrix;
	matrix.CreateRotationAxisX(radian);
	D3DXVec3TransformNormal(this, this, &matrix);
	return this;
}



Vector3D* Vector3D::RotationAxisY(float radian)
{
	Matrix matrix;
	matrix.CreateRotationAxisY(radian);
	D3DXVec3TransformNormal(this, this, &matrix);
	return this;
}



Vector3D* Vector3D::RotationAxisZ(float radian)
{
	Matrix matrix;
	matrix.CreateRotationAxisZ(radian);
	D3DXVec3TransformNormal(this, this, &matrix);
	return this;
}



Vector3D* Vector3D::RotationAxisAny(Vector3D axis, float radian)
{
	Matrix matrix;
	matrix.CreateRotationAxisAny(axis, radian);
	D3DXVec3TransformNormal(this, this, &matrix);
	return this;
}



Vector3D* Vector3D::RotationMatrix(Matrix* matrix)
{
	D3DXVec3TransformNormal(this, this, matrix);
	return this;
}



Vector3D* Vector3D::RotationQuaternion(Quaternion* quaternion)
{
	Matrix matrix;
	matrix.CreateRotationQuaternion(quaternion);
	D3DXVec3TransformNormal(this, this, &matrix);
	return this;
}