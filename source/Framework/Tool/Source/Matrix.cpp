//================================================================================
//!	@file	 Matrix.cpp
//!	@brief	 行列Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/23
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../Matrix.h"



//****************************************
// 定数定義
//****************************************
const Vector3D Matrix::DEFAULT_RIGHT(1.0f, 0.0f, 0.0f);
const Vector3D Matrix::DEFAULT_UP(0.0f, 1.0f, 0.0f);
const Vector3D Matrix::DEFAULT_FORWARD(0.0f, 0.0f, 1.0f);



//****************************************
// プロパティ定義
//****************************************
float Matrix::get11() const
{
	return _11;
}


void Matrix::set11(float value)
{
	_11 = value;
}


float Matrix::get12() const
{
	return _12;
}


void Matrix::set12(float value)
{
	_12 = value;
}


float Matrix::get13() const
{
	return _13;
}


void Matrix::set13(float value)
{
	_13 = value;
}


float Matrix::get14() const
{
	return _14;
}


void Matrix::set14(float value)
{
	_14 = value;
}


float Matrix::get21() const
{
	return _21;
}


void Matrix::set21(float value)
{
	_21 = value;
}


float Matrix::get22() const
{
	return _22;
}


void Matrix::set22(float value)
{
	_22 = value;
}


float Matrix::get23() const
{
	return _23;
}


void Matrix::set23(float value)
{
	_23 = value;
}


float Matrix::get24() const
{
	return _24;
}


void Matrix::set24(float value)
{
	_24 = value;
}


float Matrix::get31() const
{
	return _31;
}


void Matrix::set31(float value)
{
	_31 = value;
}


float Matrix::get32() const
{
	return _32;
}


void Matrix::set32(float value)
{
	_32 = value;
}


float Matrix::get33() const
{
	return _33;
}


void Matrix::set33(float value)
{
	_33 = value;
}


float Matrix::get34() const
{
	return _34;
}


void Matrix::set34(float value)
{
	_34 = value;
}


float Matrix::get41() const
{
	return _41;
}


void Matrix::set41(float value)
{
	_41 = value;
}


float Matrix::get42() const
{
	return _42;
}


void Matrix::set42(float value)
{
	_42 = value;
}


float Matrix::get43() const
{
	return _43;
}


void Matrix::set43(float value)
{
	_43 = value;
}


float Matrix::get44() const
{
	return _44;
}


void Matrix::set44(float value)
{
	_44 = value;
}



Vector3D Matrix::getPosition()
{
	return Vector3D(_41, _42, _43);
}



Vector3D* Matrix::getpRight()
{
	return &right_;
}



Vector3D* Matrix::getpUp()
{
	return &up_;
}



Vector3D* Matrix::getpForward()
{
	return &forward_;
}



Vector3D* Matrix::getpDefaultRight()
{
	return &default_right_;
}



Vector3D* Matrix::getpDefaultUp()
{
	return &default_up_;
}



Vector3D* Matrix::getpDefaultForward()
{
	return &default_forward_;
}



//****************************************
// 演算子定義
//****************************************
Matrix Matrix::operator * (const Matrix& matrix) const
{
	Matrix temp_matrix;
	D3DXMatrixMultiply(&temp_matrix, this, &matrix);
	return temp_matrix;
}



//****************************************
// 関数定義
//****************************************
Matrix::Matrix() :
	right_(DEFAULT_RIGHT),
	up_(DEFAULT_UP),
	forward_(DEFAULT_FORWARD),
	default_right_(DEFAULT_RIGHT),
	default_up_(DEFAULT_UP),
	default_forward_(DEFAULT_FORWARD)
{
}



Matrix::Matrix(const float* value) :
	MATRIX(value),
	right_(DEFAULT_RIGHT),
	up_(DEFAULT_UP),
	forward_(DEFAULT_FORWARD),
	default_right_(DEFAULT_RIGHT),
	default_up_(DEFAULT_UP),
	default_forward_(DEFAULT_FORWARD)
{
}




Matrix::Matrix(const Float16* value) :
	MATRIX(value),
	right_(DEFAULT_RIGHT),
	up_(DEFAULT_UP),
	forward_(DEFAULT_FORWARD),
	default_right_(DEFAULT_RIGHT),
	default_up_(DEFAULT_UP),
	default_forward_(DEFAULT_FORWARD)
{
}



Matrix::Matrix(const Matrix& matrix) :
	MATRIX(matrix),
	right_(DEFAULT_RIGHT),
	up_(DEFAULT_UP),
	forward_(DEFAULT_FORWARD),
	default_right_(DEFAULT_RIGHT),
	default_up_(DEFAULT_UP),
	default_forward_(DEFAULT_FORWARD)
{
}



Matrix::Matrix(float value11, float value12, float value13, float value14,
			   float value21, float value22, float value23, float value24,
			   float value31, float value32, float value33, float value34,
			   float value41, float value42, float value43, float value44) :
	MATRIX(value11, value12, value13, value14, value21, value22, value23, value24,
		   value31, value32, value33, value34, value41, value42, value43, value44),
	right_(DEFAULT_RIGHT),
	up_(DEFAULT_UP),
	forward_(DEFAULT_FORWARD),
	default_right_(DEFAULT_RIGHT),
	default_up_(DEFAULT_UP),
	default_forward_(DEFAULT_FORWARD)
{
}



Matrix::~Matrix()
{
}



void Matrix::Init()
{
	D3DXMatrixIdentity(this);

	right_ = DEFAULT_RIGHT;
	up_ = DEFAULT_UP;
	forward_ = DEFAULT_FORWARD;
	default_right_ = DEFAULT_RIGHT;
	default_up_ = DEFAULT_UP;
	default_forward_ = DEFAULT_FORWARD;
}



void Matrix::CreatePosition(Vector3D* position)
{
	D3DXMatrixTranslation(this, position->x, position->y, position->z);
	CreateAxis();
}



void Matrix::CreateScale(Vector3D* scale)
{
	D3DXMatrixScaling(this, scale->x, scale->y, scale->z);
	CreateAxis();
}



void Matrix::CreateRotationAxisX(float radian)
{
	D3DXMatrixRotationX(this, radian);
	CreateAxis();
}



void Matrix::CreateRotationAxisY(float radian)
{
	D3DXMatrixRotationY(this, radian);
	CreateAxis();
}



void Matrix::CreateRotationAxisZ(float radian)
{
	D3DXMatrixRotationZ(this, radian);
	CreateAxis();
}



void Matrix::CreateRotationAxisAny(Vector3D axis, float radian)
{
	D3DXMatrixRotationAxis(this, &axis, radian);
	CreateAxis();
}



void Matrix::CreateRotationQuaternion(Quaternion* quaternion)
{
	D3DXMatrixRotationQuaternion(this, quaternion);
	CreateAxis();
}



void Matrix::CreateWorld(Matrix* scale, Matrix* rotation, Matrix* position)
{
	D3DXMatrixMultiply(this, scale, rotation);
	D3DXMatrixMultiply(this, this, position);
	CreateAxis();
}



void Matrix::CreateView(Vector3D* position, Vector3D* gazing_point, Vector3D* up)
{
	D3DXMatrixLookAtLH(this, position, gazing_point, up);
}



void Matrix::CreateProjectionPerspectiveFovLH(float angle_of_view, float screen_width,
											  float screen_height, float near_clip,
											  float far_clip)
{
	D3DXMatrixPerspectiveFovLH(this, D3DXToRadian(angle_of_view),
							   screen_width / screen_height,
							   near_clip, far_clip);
}



void Matrix::CreateProjectionOrtho(float angle_of_view, float screen_width,
								   float screen_height, float near_clip,
								   float far_clip)
{
	D3DXMatrixOrthoLH(this, screen_width * angle_of_view,
					  screen_height * angle_of_view, near_clip, far_clip);
}



void Matrix::CreateProjection2D(float screen_width, float screen_height)
{
	*this =
	{
		2.0f / screen_width, 0.0f, 0.0f, 0.0f,
		0.0f, 2.0f / screen_height, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}



void Matrix::ChangeInverse()
{
	D3DXMatrixInverse(this, NULL, this);
	CreateAxis();
}



void Matrix::ChangeTranspose(bool is_position_off)
{
	D3DXMatrixTranspose(this, this);
	if (!is_position_off) return;
	_14 = 0.0f;
	_24 = 0.0f;
	_34 = 0.0f;
	CreateAxis();
}



void Matrix::AddParentMatrix(Matrix* matrix)
{
	D3DXMatrixMultiply(this, this, matrix);
	CreateAxis();
}



void Matrix::AddChildMatrix(Matrix* matrix)
{
	D3DXMatrixMultiply(this, matrix, this);
	CreateAxis();
}



void Matrix::CreateAxis()
{
	right_ = {_11, _12, _13};
	up_ = {_21, _22, _23};
	forward_ = {_31, _32, _33};

	right_.ChangeNormalize();
	up_.ChangeNormalize();
	forward_.ChangeNormalize();
}