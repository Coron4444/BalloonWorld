//================================================================================
//!	@file	 Vector3D.h
//!	@brief	 3D�x�N�g��Class
//! @details 
//!	@author  Kai Araki									@date 2017/11/21
//================================================================================
#ifndef	_VECTOR_3D_H_
#define _VECTOR_3D_H_



//****************************************
// �^��`
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
// �N���X�錾
//****************************************
class Matrix;



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
	static float CreateDot(Vector3D* vector0, Vector3D* vector1);

	//----------------------------------------
	//! @brief 3�_������ϐ����֐�
	//! @details
	//! @param *point0 �_0
	//! @param *point1 �_1
	//! @param *point2 �_2
	//! @retval float ���ϒl
	//----------------------------------------
	static float CreateDotPoint3(Vector3D* point0, Vector3D* point1, Vector3D* point2);

	//----------------------------------------
	//! @brief �O�ϐ����֐�
	//! @details
	//! @param *vector0 �x�N�g��0
	//! @param *vector1 �x�N�g��1
	//! @retval Vector3D �O�ϒl
	//----------------------------------------
	static Vector3D CreateCross(Vector3D* vector0, Vector3D* vector1);

	//----------------------------------------
	//! @brief 3�_����O�ϐ����֐�
	//! @details
	//! @param *point0 �_0
	//! @param *point1 �_1
	//! @param *point2 �_2
	//! @retval Vector3D �O�ϒl
	//----------------------------------------
	static Vector3D CreateCrossPoint3(Vector3D* point0, Vector3D* point1, Vector3D* point2);

	//----------------------------------------
	//! @brief ���W�A���p�x�����֐�
	//! @details
	//! @param *vector0 �x�N�g��0
	//! @param *vector1 �x�N�g��1
	//! @retval float ���W�A���p�x
	//----------------------------------------
	static float CreateAngleRadian(Vector3D* vector0, Vector3D* vector1);

	//----------------------------------------
	//! @brief �f�O���[�p�x�����֐�
	//! @details
	//! @param *vector0 �x�N�g��0
	//! @param *vector1 �x�N�g��1
	//! @retval float �f�O���[�p�x
	//----------------------------------------
	static float CreateAngleDegree(Vector3D* vector0, Vector3D* vector1);


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief X�����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float X����
	//----------------------------------------
	float getX() const;

	//----------------------------------------
	//! @brief X�����ݒ�֐�
	//! @details
	//! @param value X����
	//! @retval void �Ȃ�
	//----------------------------------------
	void setX(float value);

	//----------------------------------------
	//! @brief Y�����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float Y����
	//----------------------------------------
	float getY() const;

	//----------------------------------------
	//! @brief Y�����ݒ�֐�
	//! @details
	//! @param value X����
	//! @retval void �Ȃ�
	//----------------------------------------
	void setY(float value);

	//----------------------------------------
	//! @brief Z�����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float Z����
	//----------------------------------------
	float getZ() const;

	//----------------------------------------
	//! @brief Z�����ݒ�֐�
	//! @details
	//! @param value Z����
	//! @retval void �Ȃ�
	//----------------------------------------
	void setZ(float value);

	//----------------------------------------
	//! @brief X������2��擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float X������2��
	//----------------------------------------
	float getSquareX() const;

	//----------------------------------------
	//! @brief Y������2��擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float Y������2��
	//----------------------------------------
	float getSquareY() const;

	//----------------------------------------
	//! @brief Z������2��擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float Z������2��
	//----------------------------------------
	float getSquareZ() const;

	//----------------------------------------
	//! @brief �����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float ����
	//----------------------------------------
	float getLength() const;

	//----------------------------------------
	//! @brief ������2��擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float ������2��
	//----------------------------------------
	float getLengthSquare() const;

	//----------------------------------------
	//! @brief X�̒����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float X�̒���
	//----------------------------------------
	float getLengthX() const;

	//----------------------------------------
	//! @brief Y�̒����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float Y�̒���
	//----------------------------------------
	float getLengthY() const;

	//----------------------------------------
	//! @brief Z�̒����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float Z�̒���
	//----------------------------------------
	float getLengthZ() const;

	//----------------------------------------
	//! @brief XY�̒����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float XY�̒���
	//----------------------------------------
	float getLengthXY() const;

	//----------------------------------------
	//! @brief XZ�̒����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float XZ�̒���
	//----------------------------------------
	float getLengthXZ() const;

	//----------------------------------------
	//! @brief YZ�̒����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float YZ�̒���
	//----------------------------------------
	float getLengthYZ() const;


//====================
// ���Z�q
//====================
public:
	//----------------------------------------
	//! @brief <���Z�q
	//! @details
	//! @param vector �x�N�^�[
	//! @retval bool ����̗L��
	//----------------------------------------
	bool operator < (const Vector3D& vector) const;

	//----------------------------------------
	//! @brief >���Z�q
	//! @details
	//! @param vector �x�N�^�[
	//! @retval bool ����̗L��
	//----------------------------------------
	bool operator > (const Vector3D& vector) const;

	//----------------------------------------
	//! @brief <=���Z�q
	//! @details
	//! @param vector �x�N�^�[
	//! @retval bool ����̗L��
	//----------------------------------------
	bool operator <= (const Vector3D& vector) const;

	//----------------------------------------
	//! @brief >=���Z�q
	//! @details
	//! @param vector �x�N�^�[
	//! @retval bool ����̗L��
	//----------------------------------------
	bool operator >= (const Vector3D& vector) const;

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
	//! @param value ����
	//----------------------------------------
	Vector3D(const float* value);

	//----------------------------------------
	//! @brief �P��float16�R���X�g���N�^�֐�
	//! @details
	//! @param value ����
	//----------------------------------------
	Vector3D(const Float16* value);

	//----------------------------------------
	//! @brief ����float�R���X�g���N�^�֐�
	//! @details
	//! @param value_x X����
	//! @param value_y Y����
	//! @param value_z Z����
	//----------------------------------------
	Vector3D(float value_x, float value_y, float value_z);

	//----------------------------------------
	//! @brief �x�N�^�[�R���X�g���N�^�֐�
	//! @details
	//! @param vector �x�N�^�[
	//----------------------------------------
	Vector3D(const Vec& vector);

	//----------------------------------------
	//! @brief �f�X�g���N�^�֐�
	//! @details
	//----------------------------------------
	virtual ~Vector3D();

	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init();

	//----------------------------------------
	//! @brief ���K���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D* �ύX��x�N�g��
	//----------------------------------------
	Vector3D* ChangeNormalize();

	//----------------------------------------
	//! @brief �C�ӂ̒����ɕύX�֐�
	//! @details
	//! @param length ����
	//! @retval Vector3D* �ύX��x�N�g��
	//----------------------------------------
	Vector3D* ChangeAnyLength(float length);

	//----------------------------------------
	//! @brief X��C�ӂ̒����ɕύX�֐�
	//! @details
	//! @param length ����
	//! @retval Vector3D* �ύX��x�N�g��
	//----------------------------------------
	Vector3D* ChangeAnyLengthX(float length);

	//----------------------------------------
	//! @brief Y��C�ӂ̒����ɕύX�֐�
	//! @details
	//! @param length ����
	//! @retval Vector3D* �ύX��x�N�g��
	//----------------------------------------
	Vector3D* ChangeAnyLengthY(float length);

	//----------------------------------------
	//! @brief Z��C�ӂ̒����ɕύX�֐�
	//! @details
	//! @param length ����
	//! @retval Vector3D* �ύX��x�N�g��
	//----------------------------------------
	Vector3D* ChangeAnyLengthZ(float length);

	//----------------------------------------
	//! @brief XY��C�ӂ̒����ɕύX�֐�
	//! @details
	//! @param length ����
	//! @retval Vector3D* �ύX��x�N�g��
	//----------------------------------------
	Vector3D* ChangeAnyLengthXY(float length);

	//----------------------------------------
	//! @brief XZ��C�ӂ̒����ɕύX�֐�
	//! @details
	//! @param length ����
	//! @retval Vector3D* �ύX��x�N�g��
	//----------------------------------------
	Vector3D* ChangeAnyLengthXZ(float length);

	//----------------------------------------
	//! @brief YZ��C�ӂ̒����ɕύX�֐�
	//! @details
	//! @param length ����
	//! @retval Vector3D* �ύX��x�N�g��
	//----------------------------------------
	Vector3D* ChangeAnyLengthYZ(float length);

	//----------------------------------------
	//! @brief X����]�֐�
	//! @details
	//! @param radian �p�x
	//! @retval Vector3D* �ύX��x�N�g��
	//----------------------------------------
	Vector3D* RotationAxisX(float radian);

	//----------------------------------------
	//! @brief Y����]�֐�
	//! @details
	//! @param radian �p�x
	//! @retval Vector3D* �ύX��x�N�g��
	//----------------------------------------
	Vector3D* RotationAxisY(float radian);

	//----------------------------------------
	//! @brief Z����]�֐�
	//! @details
	//! @param radian �p�x
	//! @retval Vector3D* �ύX��x�N�g��
	//----------------------------------------
	Vector3D* RotationAxisZ(float radian);

	//----------------------------------------
	//! @brief �C�ӎ���]�֐�
	//! @details
	//! @param axis   ��
	//! @param radian �p�x
	//! @retval Vector3D* �ύX��x�N�g��
	//----------------------------------------
	Vector3D* RotationAxisAny(Vector3D axis, float radian);

	//----------------------------------------
	//! @brief �s���]�֐�
	//! @details
	//! @param matrix �s��
	//! @retval Vector3D* �ύX��x�N�g��
	//----------------------------------------
	Vector3D* RotationMatrix(Matrix* matrix);

	//----------------------------------------
	//! @brief �N�H�[�^�j�I����]��]�֐�
	//! @details
	//! @param quaternion �N�H�[�^�j�I��
	//! @retval Vector3D* �ύX��x�N�g��
	//----------------------------------------
	Vector3D* RotationQuaternion(Quaternion* quaternion);
};



#endif