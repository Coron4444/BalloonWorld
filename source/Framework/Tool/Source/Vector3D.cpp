//================================================================================
//!	@file	 Vector3D.cpp
//!	@brief	 3DベクトルClass
//! @details 
//!	@author  Kai Araki									@date 2017/11/21
//================================================================================



//****************************************
// インクルード文
//****************************************
#include <math.h>

#include "../Vector3D.h"



//****************************************
// static関数定義
//****************************************
float Vector3D::CreateDot(Vec3* vector0, Vec3* vector1)
{
	return D3DXVec3Dot(vector0, vector1);
}



float Vector3D::CreateDotPoint3(Vec3* point0, Vec3* point1, Vec3* point2)
{
	Vec3 vector0(*point0 - *point1);
	Vec3 vector1(*point2 - *point1);
	return CreateDot(&vector0, &vector1);
}



Vec3 Vector3D::CreateCross(Vec3* vector0, Vec3* vector1)
{
	Vec3 temp_vector;
	D3DXVec3Cross(&temp_vector, vector0, vector1);
	return temp_vector;
}



Vec3 Vector3D::CreateCrossPoint3(Vec3* point0, Vec3* point1, Vec3* point2)
{
	Vec3 vector0(*point1 - *point0);
	Vec3 vector1(*point2 - *point1);
	return CreateCross(&vector0, &vector1);
}



//****************************************
// プロパティ定義
//****************************************
float Vector3D::getSquareX()
{
	return x * x;
}



float Vector3D::getSquareY()
{
	return y * y;
}



float Vector3D::getSquareZ()
{
	return z * z;
}



float Vector3D::getLength()
{
	return D3DXVec3Length(this);
}



float Vector3D::getLengthSquare()
{
	return getSquareX() + getSquareY() + getSquareZ();
}



float Vector3D::getLengthX()
{
	return fabsf(x);
}



float Vector3D::getLengthY()
{
	return fabsf(y);
}



float Vector3D::getLengthZ()
{
	return fabsf(z);
}



float Vector3D::getLengthXY()
{
	Vec3 temp_vector(x, y, 0.0f);

	return D3DXVec3Length(&temp_vector);
}



float Vector3D::getLengthXZ()
{
	Vec3 temp_vector(x, 0.0f, z);

	return D3DXVec3Length(&temp_vector);
}



float Vector3D::getLengthYZ()
{
	Vec3 temp_vector(0.0f, y, z);

	return D3DXVec3Length(&temp_vector);
}



//****************************************
// 演算子定義
//****************************************
bool Vector3D::operator < (Vector3D& vector)
{
	if (x >= vector.x) return false;
	if (y >= vector.y) return false;
	if (z >= vector.z) return false;
	return true;
}



bool Vector3D::operator > (Vector3D& vector)
{
	if (x <= vector.x) return false;
	if (y <= vector.y) return false;
	if (z <= vector.z) return false;
	return true;
}



bool Vector3D::operator <= (Vector3D& vector)
{
	if (x > vector.x) return false;
	if (y > vector.y) return false;
	if (z > vector.z) return false;
	return true;
}



bool Vector3D::operator >= (Vector3D& vector)
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



Vector3D::Vector3D(const float* num)
	: Vec3(num)
{
}



Vector3D::Vector3D(const Float16* num)
	: Vec3(num)
{
}



Vector3D::Vector3D(float num_x, float num_y, float num_z)
	: Vec3(num_x, num_y, num_z)
{
}



Vector3D::Vector3D(const Vec& vector)
	: Vec3(vector)
{
}



Vector3D::~Vector3D()
{
}



void Vector3D::Reset()
{
	*this = Vec3(0.0f, 0.0f, 0.0f);
}



Vec3* Vector3D::ChangeNormalize()
{
	D3DXVec3Normalize(this, this);
	return this;
}



Vec3* Vector3D::ChangeAnyLength(float length)
{
	ChangeNormalize();
	*this *= length;
	return this;
}



Vec3* Vector3D::ChangeAnyLengthX(float length)
{
	Vec3 temp_vector(x, 0.0f, 0.0f);
	D3DXVec3Normalize(&temp_vector, &temp_vector);
	temp_vector *= length;
	x = temp_vector.x;
	return this;
}



Vec3* Vector3D::ChangeAnyLengthY(float length)
{
	Vec3 temp_vector(0.0f, y, 0.0f);
	D3DXVec3Normalize(&temp_vector, &temp_vector);
	temp_vector *= length;
	y = temp_vector.y;
	return this;
}



Vec3* Vector3D::ChangeAnyLengthZ(float length)
{
	Vec3 temp_vector(0.0f, 0.0f, z);
	D3DXVec3Normalize(&temp_vector, &temp_vector);
	temp_vector *= length;
	z = temp_vector.z;
	return this;
}



Vec3* Vector3D::ChangeAnyLengthXY(float length)
{
	Vec3 temp_vector(x, y, 0.0f);
	D3DXVec3Normalize(&temp_vector, &temp_vector);
	temp_vector *= length;
	x = temp_vector.x;
	y = temp_vector.y;
	return this;
}



Vec3* Vector3D::ChangeAnyLengthXZ(float length)
{
	Vec3 temp_vector(x, 0.0f, z);
	D3DXVec3Normalize(&temp_vector, &temp_vector);
	temp_vector *= length;
	x = temp_vector.x;
	z = temp_vector.z;
	return this;
}



Vec3* Vector3D::ChangeAnyLengthYZ(float length)
{
	Vec3 temp_vector(0.0f, y, z);
	D3DXVec3Normalize(&temp_vector, &temp_vector);
	temp_vector *= length;
	y = temp_vector.y;
	z = temp_vector.z;
	return this;
}



Vec3* Vector3D::RotationAxisX(float radian)
{
	MATRIX rotation_matrix;
	D3DXMatrixRotationX(&rotation_matrix, radian);
	D3DXVec3TransformNormal(this, this, &rotation_matrix);
	return this;
}



Vec3* Vector3D::RotationAxisY(float radian)
{
	MATRIX rotation_matrix;
	D3DXMatrixRotationY(&rotation_matrix, radian);
	D3DXVec3TransformNormal(this, this, &rotation_matrix);
	return this;
}



Vec3* Vector3D::RotationAxisZ(float radian)
{
	MATRIX rotation_matrix;
	D3DXMatrixRotationZ(&rotation_matrix, radian);
	D3DXVec3TransformNormal(this, this, &rotation_matrix);
	return this;
}



Vec3* Vector3D::RotationAxisAny(Vec3 axis, float radian)
{
	MATRIX rotation_matrix;
	D3DXMatrixRotationAxis(&rotation_matrix, &axis, radian);
	D3DXVec3TransformNormal(this, this, &rotation_matrix);
	return this;
}



Vec3* Vector3D::RotationMatrix(MATRIX* rotation_matrix)
{
	D3DXVec3TransformNormal(this, this, rotation_matrix);
	return this;
}



Vec3* Vector3D::RotationQuaternion(Quaternion* quaternion)
{
	MATRIX rotation_matrix;
	D3DXMatrixRotationQuaternion(&rotation_matrix, quaternion);
	D3DXVec3TransformNormal(this, this, &rotation_matrix);
	return this;
}