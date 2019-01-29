//================================================================================
//!	@file	 Vector3D.h
//!	@brief	 3D�x�N�g��Class
//! @details 
//!	@author  Kai Araki									@date 2017/11/21
//================================================================================
#ifndef	_VECTOR_3D_H_
#define _VECTOR_3D_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <d3dx9.h>



//****************************************
// �^��`
//****************************************
using Vec = D3DVECTOR;
using Vec2 = D3DXVECTOR2;
using Vec3 = D3DXVECTOR3;
using Vec4 = D3DXVECTOR4;
using Float16 = D3DXFLOAT16;
using Quaternion = D3DXQUATERNION;
using MATRIX = D3DXMATRIX;
using Color4 = D3DCOLOR;
using XColor4 = D3DXCOLOR;



//************************************************************														   
//! @brief   3D�x�N�g��Class
//!
//! @details 3D�̃x�N�g��Class
//************************************************************
class Vector3D : public Vec3
{
//====================
// static�֐�
//====================
public:
	//----------------------------------------
	//! @brief ���ϐ����֐�
	//! @details
	//! @param *vector0 �x�N�g��0
	//! @param *vector1 �x�N�g��1
	//! @retval float ���ϒl
	//----------------------------------------
	static float CreateDot(Vec3* vector0, Vec3* vector1);

	//----------------------------------------
	//! @brief 3�_������ϐ����֐�
	//! @details
	//! @param *point0 �_0
	//! @param *point1 �_1
	//! @param *point2 �_2
	//! @retval float ���ϒl
	//----------------------------------------
	static float CreateDotPoint3(Vec3* point0, Vec3* point1, Vec3* point2);

	//----------------------------------------
	//! @brief �O�ϐ����֐�
	//! @details
	//! @param *vector0 �x�N�g��0
	//! @param *vector1 �x�N�g��1
	//! @retval Vec3 �O�ϒl
	//----------------------------------------
	static Vec3 CreateCross(Vec3* vector0, Vec3* vector1);

	//----------------------------------------
	//! @brief 3�_����O�ϐ����֐�
	//! @details
	//! @param *point0 �_0
	//! @param *point1 �_1
	//! @param *point2 �_2
	//! @retval Vec3 �O�ϒl
	//----------------------------------------
	static Vec3 CreateCrossPoint3(Vec3* point0, Vec3* point1, Vec3* point2);

//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief X��2��擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float X��2��
	//----------------------------------------
	float getSquareX();

	//----------------------------------------
	//! @brief Y��2��擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float Y��2��
	//----------------------------------------
	float getSquareY();

	//----------------------------------------
	//! @brief Z��2��擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float Z��2��
	//----------------------------------------
	float getSquareZ();

	//----------------------------------------
	//! @brief �����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float ����
	//----------------------------------------
	float getLength();

	//----------------------------------------
	//! @brief ������2��擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float ������2��
	//----------------------------------------
	float getLengthSquare();

	//----------------------------------------
	//! @brief XY�̒�����2��擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float XY�̒�����2��
	//----------------------------------------
	float getLengthXY();

	//----------------------------------------
	//! @brief XZ�̒�����2��擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float XZ�̒�����2��
	//----------------------------------------
	float getLengthXZ();

	//----------------------------------------
	//! @brief YZ�̒�����2��擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float YZ�̒�����2��
	//----------------------------------------
	float getLengthYZ();


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �R���X�g���N�^�֐�
	//! @details
	//! @param void �Ȃ�
	//----------------------------------------
	Vector3D();

	//----------------------------------------
	//! @brief �P��float�R���X�g���N�^�֐�
	//! @details
	//! @param num X,Y,Z�l
	//----------------------------------------
	Vector3D(const float* num);

	//----------------------------------------
	//! @brief �P��float16�R���X�g���N�^�֐�
	//! @details
	//! @param num X,Y,Z�l
	//----------------------------------------
	Vector3D(const Float16* num);

	//----------------------------------------
	//! @brief ����float�R���X�g���N�^�֐�
	//! @details
	//! @param num_x X�l
	//! @param num_y Y�l
	//! @param num_z Z�l
	//----------------------------------------
	Vector3D(float num_x, float num_y, float num_z);

	//----------------------------------------
	//! @brief �x�N�^�[�R���X�g���N�^�֐�
	//! @details
	//! @param vector X,Y,Z�l
	//----------------------------------------
	Vector3D(const Vec& vector);

	//----------------------------------------
	//! @brief �f�X�g���N�^�֐�
	//! @details
	//! @param void �Ȃ�
	//----------------------------------------
	virtual ~Vector3D();

	//----------------------------------------
	//! @brief ���Z�b�g�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Reset();

	//----------------------------------------
	//! @brief ���K���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vec3* �ύX��x�N�g��
	//----------------------------------------
	Vec3* ChangeNormalize();

	//----------------------------------------
	//! @brief �C�ӂ̒����ɕύX�֐�
	//! @details
	//! @param length ����
	//! @retval Vec3* �ύX��x�N�g��
	//----------------------------------------
	Vec3* ChangeAnyLength(float length);

	//----------------------------------------
	//! @brief X����]�֐�
	//! @details
	//! @param radian �p�x
	//! @retval Vec3* �ύX��x�N�g��
	//----------------------------------------
	Vec3* RotationAxisX(float radian);

	//----------------------------------------
	//! @brief Y����]�֐�
	//! @details
	//! @param radian �p�x
	//! @retval Vec3* �ύX��x�N�g��
	//----------------------------------------
	Vec3* RotationAxisY(float radian);

	//----------------------------------------
	//! @brief Z����]�֐�
	//! @details
	//! @param radian �p�x
	//! @retval Vec3* �ύX��x�N�g��
	//----------------------------------------
	Vec3* RotationAxisZ(float radian);

	//----------------------------------------
	//! @brief �C�ӎ���]�֐�
	//! @details
	//! @param radian �p�x
	//! @retval Vec3* �ύX��x�N�g��
	//----------------------------------------
	Vec3* RotationAxisAny(Vec3 axis, float radian);

	//----------------------------------------
	//! @brief �s���]�֐�
	//! @details
	//! @param rotation_matrix �s��
	//! @retval Vec3* �ύX��x�N�g��
	//----------------------------------------
	Vec3* RotationMatrix(MATRIX* rotation_matrix);
};



#endif