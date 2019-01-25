//================================================================================
//
//    3D�x�N�g���N���X�w�b�_
//    Author : Araki Kai                                �쐬�� : 2017/11/21
//
//================================================================================


#ifndef	_VECTOR_3D_H_
#define _VECTOR_3D_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include <math.h>
#include <d3dx9.h>



//======================================================================
//
// �^��`
//
//======================================================================

using Vec        = D3DVECTOR;
using Vec2       = D3DXVECTOR2;
using Vec3       = D3DXVECTOR3;
using Vec4       = D3DXVECTOR4;
using Float16    = D3DXFLOAT16;
using Quaternion = D3DXQUATERNION;
using MATRIX     = D3DXMATRIX;
using Color4     = D3DCOLOR;
using XColor4    = D3DXCOLOR;



//======================================================================
//
// �N���X��`
//
//======================================================================

class Vector3D : public Vec3
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �R���X�g���N�^�Q
	Vector3D();
    Vector3D(const float*   num   );
    Vector3D(const Vec&     vector);
    Vector3D(const Float16* num   );
    Vector3D(float num_x, float num_y, float num_z);



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �f�X�g���N�^
	virtual ~Vector3D();



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// ���Z�b�g
	void ResetVector();

	// �����֌W
	Vec3 CreateNormalize();
	Vec3 AnyLengthVector(const float length);

	Vec3 RotationVector_AxisX   (const float radian);
	Vec3 RotationVector_AxisY   (const float radian);
	Vec3 RotationVector_AxisZ   (const float radian);
	Vec3 RotationVector_AxisFree(const Vec3 axis_vector, const float radian );
	Vec3 RotationVector_Matrix  (MATRIX* rotation_matrix);

	// ���ρE�O��
	float CreateVectorDot  (const Vec3 vector) const;
	Vec3  CreateVectorCross(const Vec3 vector) const;


	// ---- �A�N�Z�b�T ----

	// �Q��Q�b�^
	float GetSquareX() const {return x * x;}
	float GetSquareY() const {return y * y;}
	float GetSquareZ() const {return z * z;}


	// �����֌W�Q�b�^
	float GetLength       () const;
	float GetLengthSquare () const;
	float GetLength_XY    () const;
	float GetLength_XZ    () const;
	float GetLength_YZ    () const;
};





//======================================================================
//
// ��ÓI�����o�֐���`(inline)
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �f�t�H���g�R���X�g���N�^ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline Vector3D::Vector3D() 
	: Vec3(0.0f, 0.0f, 0.0f)
{
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �P��float�R���X�g���N�^ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline Vector3D::Vector3D(const float* num)
	: Vec3(num)
{
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �x�N�^�[�R���X�g���N�^ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline Vector3D::Vector3D(const Vec& vector) 
	: Vec3(vector)
{
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �P��float16�R���X�g���N�^ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline Vector3D::Vector3D(const Float16* num) 
	: Vec3(num)
{
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ����float�R���X�g���N�^ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline Vector3D::Vector3D(const float num_x, const float num_y, const float num_z) 
	: Vec3(num_x, num_y, num_z)
{
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �f�X�g���N�^ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline Vector3D::~Vector3D() 
{
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ Vector�̃��Z�b�g�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline void Vector3D::ResetVector()
{ 
	*this = Vec3(0.0f, 0.0f, 0.0f);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ Vector��3D�̐��K���X�V�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline Vec3 Vector3D::CreateNormalize()
{ 
	D3DXVec3Normalize(this, this);

	return *this;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ Vector��C�ӂ̒����ɕύX�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline Vec3 Vector3D::AnyLengthVector(const float length)
{ 
	CreateNormalize();

	*this *= length;

	return *this;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ Vector��X����]�ϊ��֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline Vec3 Vector3D::RotationVector_AxisX(const float radian)
{
	MATRIX temp_rotation_matrix;

	D3DXMatrixRotationX(&temp_rotation_matrix, radian);

	D3DXVec3TransformNormal(this, this, &temp_rotation_matrix);

	return *this;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ Vector��Y����]�ϊ��֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline Vec3 Vector3D::RotationVector_AxisY(const float radian)
{
	MATRIX temp_rotation_matrix;

	D3DXMatrixRotationY(&temp_rotation_matrix, radian);

	D3DXVec3TransformNormal(this, this, &temp_rotation_matrix);

	return *this;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ Vector��Z����]�ϊ��֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline Vec3 Vector3D::RotationVector_AxisZ(const float radian)
{
	MATRIX temp_rotation_matrix;

	D3DXMatrixRotationZ(&temp_rotation_matrix, radian);

	D3DXVec3TransformNormal(this, this, &temp_rotation_matrix);

	return *this;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ Vector��C�ӎ���]�ϊ��֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline Vec3 Vector3D::RotationVector_AxisFree(const Vec3 axis_vector, const float radian)
{
	MATRIX temp_rotation_matrix;

	D3DXMatrixRotationAxis(&temp_rotation_matrix, &axis_vector, radian);

	D3DXVec3TransformNormal(this, this, &temp_rotation_matrix);

	return *this;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ Vector��ϊ��֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline Vec3 Vector3D::RotationVector_Matrix(MATRIX* rotation_matrix)
{
	D3DXVec3TransformNormal(this, this, rotation_matrix);

	return *this;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ Vector���m�̓��ύ쐬�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline float Vector3D::CreateVectorDot(const Vec3 vector) const
{

	return D3DXVec3Dot(this, &vector);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ Vector���m�̊O�ύ쐬�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline Vec3 Vector3D::CreateVectorCross(const Vec3 vector) const
{

	Vec3 temp_vector;
	
	D3DXVec3Cross( &temp_vector, this, &vector );

	return temp_vector;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ Vector�̒����擾�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline float Vector3D::GetLength() const
{ 
	return D3DXVec3Length(this);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ Vector�̒�����2��擾�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline float Vector3D::GetLengthSquare() const 
{ 
	return GetSquareX() + GetSquareY() + GetSquareZ();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ Vector�̒����擾�֐�(XY) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline float Vector3D::GetLength_XY() const
{ 
	Vec3 temp_vector(x, y, 0.0f);

	return D3DXVec3Length(&temp_vector);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ Vector�̒����擾�֐�(XZ) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline float Vector3D::GetLength_XZ() const
{ 
	Vec3 temp_vector(x, 0.0f, z);

	return D3DXVec3Length(&temp_vector);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ Vector�̒����擾�֐�(YZ) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline float Vector3D::GetLength_YZ() const
{ 
	Vec3 temp_vector(0.0f, y, z);

	return D3DXVec3Length(&temp_vector);
}






//======================================================================
//
// �񃁃��o�֐��錾
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 3�_����O�ς��쐬����֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline float Point3_Dot(Vector3D vector1, Vector3D vector2, Vector3D vector3)
{
	Vec3 temp_point1 = vector1;
	Vec3 temp_point2 = vector2;
	Vec3 temp_point3 = vector3;

	Vector3D temp_vector1(temp_point1 - temp_point2);
	Vector3D temp_vector2(temp_point3 - temp_point2);

	return temp_vector1.CreateVectorDot(temp_vector2);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 3�_����O�ς��쐬����֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline Vec3 Point3_Cross(Vector3D vector1, Vector3D vector2, Vector3D vector3)
{
	Vec3 temp_point1 = vector1;
	Vec3 temp_point2 = vector2;
	Vec3 temp_point3 = vector3;

	Vector3D temp_vector1(temp_point2 - temp_point1);
	Vector3D temp_vector2(temp_point3 - temp_point2);

	return temp_vector1.CreateVectorCross(temp_vector2);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 3�_�̊p���݊p���ǂ�������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline bool IsObtuseAngle(Vector3D point0, Vector3D point1, Vector3D point2)
{
	float temp_dot = Point3_Dot(point0, point1, point2);
	
	return temp_dot <= 0.0f;
}



#endif