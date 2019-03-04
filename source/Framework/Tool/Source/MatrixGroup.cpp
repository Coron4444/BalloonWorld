//================================================================================
//!	@file	 MatrixGroup.cpp
//!	@brief	 行列群Class
//! @details 
//!	@author  Kai Araki									@date 2018/08/16
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../MatrixGroup.h"



//****************************************
// プロパティ定義
//****************************************
MATRIX* MatrixGroup::getpPositionMatrix()
{
	return &position_;
}



void MatrixGroup::setPositionMatrix(Vec3* value)
{
	D3DXMatrixTranslation(&position_, value->x, value->y, value->z);
}



MATRIX* MatrixGroup::getpScaleMatrix()
{
	return &scale_;
}



void MatrixGroup::setScaleMatrix(Vec3* value)
{
	D3DXMatrixScaling(&scale_, value->x, value->y, value->z);
}



MATRIX* MatrixGroup::getpRotationMatrix()
{
	return &rotation_;
}



void MatrixGroup::setRotationMatrix(Quaternion* value)
{
	D3DXMatrixRotationQuaternion(&rotation_, value);
}



MATRIX* MatrixGroup::getpInverseMatrix()
{
	return &inverse_;
}



void MatrixGroup::setInverseMatrix(MATRIX* value)
{
	D3DXMatrixInverse(&inverse_, NULL, value);
}



MATRIX* MatrixGroup::getpTransposeMatrix()
{
	return &transpose_;
}



void MatrixGroup::setTransposeMatrix(MATRIX* value, bool is_position_off)
{
	D3DXMatrixTranspose(&transpose_, value);
	if (!is_position_off) return;
	transpose_._14 = 0.0f;
	transpose_._24 = 0.0f;
	transpose_._34 = 0.0f;
}



MATRIX* MatrixGroup::getpWorldMatrix()
{
	return &world_;
}



Vec3 MatrixGroup::getPosition()
{
	return Vec3(world_._41, world_._42, world_._43);
}



//****************************************
// 関数定義
//****************************************
MatrixGroup::MatrixGroup()
{
	ResetAllMatrix();
}



void MatrixGroup::CreateWorldMatrix()
{
	D3DXMatrixMultiply(&world_, &scale_, &rotation_);
	D3DXMatrixMultiply(&world_, &world_, &position_);
}



void MatrixGroup::CreateWorldMatrixPlusInverse()
{
	CreateWorldMatrix();
	D3DXMatrixMultiply(&world_, &inverse_, &world_);
}



void MatrixGroup::CreateWorldMatrixPlusTranspose()
{
	CreateWorldMatrix();
	D3DXMatrixMultiply(&world_, &transpose_, &world_);
}



void MatrixGroup::AddParentMatrixToWorldMatrix(MATRIX* parent_matrix)
{
	D3DXMatrixMultiply(&world_, &world_, parent_matrix);
}



void MatrixGroup::ResetAllMatrix()
{
	D3DXMatrixIdentity(&position_);
	D3DXMatrixIdentity(&scale_);
	D3DXMatrixIdentity(&rotation_);
	D3DXMatrixIdentity(&inverse_);
	D3DXMatrixIdentity(&transpose_);
	D3DXMatrixIdentity(&world_);
}