//================================================================================
//
//    ���x�N�g���N���X
//    Author : Araki Kai                                �쐬�� : 2018/01/08
//
//================================================================================



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include "AxisVector.h"



//======================================================================
//
// �萔��`
//
//======================================================================

const Vector3D AxisVector::DEFAULT_FORWARD(0.0f, 0.0f, 1.0f);
const Vector3D AxisVector::DEFAULT_UP	  (0.0f, 1.0f, 0.0f);
const Vector3D AxisVector::DEFAULT_RIGHT  (1.0f, 0.0f, 0.0f);



//======================================================================
//
// ��ÓI�����o�֐���`
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �R���X�g���N�^ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

AxisVector::AxisVector()
	: forward_(DEFAULT_FORWARD), 
	  up_     (DEFAULT_UP), 
	  right_  (DEFAULT_RIGHT)
{
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ���x�N�g���̃��Z�b�g�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void AxisVector::ResetAxisVector()
{
	forward_ = DEFAULT_FORWARD; 
	up_      = DEFAULT_UP;
	right_   = DEFAULT_RIGHT;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ��]�֐�(�s��) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void AxisVector::RotationMatrix(MATRIX* rotation_matrix)
{
	// �O�A��x�N�g���̉�]
	forward_.RotationVector_Matrix(rotation_matrix);
	up_.RotationVector_Matrix(rotation_matrix);

	// �E�x�N�g���̍쐬�y�я�x�N�g���̍č쐬
	CalculationAxis_ConfirmAxisForward();

	// ���K��
	NormalizeAxis_All();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ X�x�N�g�����S��]�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void AxisVector::RotationAxis_PivotX(const float radian)
{
	// �O�x�N�g������]������
	forward_.RotationVector_AxisX(radian);

	// ��x�N�g������]������
	up_.RotationVector_AxisX(radian);

	// �E�x�N�g���̍쐬�y�я�x�N�g���̍č쐬
	CalculationAxis_ConfirmAxisForward();

	// ���K��
	NormalizeAxis_All();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ Y�x�N�g�����S��]�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void AxisVector::RotationAxis_PivotY(const float radian)
{
	// �O�x�N�g������]������
	forward_.RotationVector_AxisY(radian);

	// ��x�N�g������]������
	up_.RotationVector_AxisY(radian);

	// �E�x�N�g���̍쐬�y�я�x�N�g���̍č쐬
	CalculationAxis_ConfirmAxisForward();

	// ���K��
	NormalizeAxis_All();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ Z�x�N�g�����S��]�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void AxisVector::RotationAxis_PivotZ(const float radian)
{
	// �O�x�N�g������]������
	forward_.RotationVector_AxisZ(radian);

	// ��x�N�g������]������
	up_.RotationVector_AxisZ(radian);

	// �E�x�N�g���̍쐬�y�я�x�N�g���̍č쐬
	CalculationAxis_ConfirmAxisForward();

	// ���K��
	NormalizeAxis_All();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �O�x�N�g�����S��]�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void AxisVector::RotationAxis_PivotForward(const float radian)
{
	// ��x�N�g������]������
	up_.RotationVector_AxisFree(forward_, radian);

	// �E�x�N�g���̍쐬�y�я�x�N�g���̍č쐬
	CalculationAxis_ConfirmAxisForward();

	// ���K��
	NormalizeAxis_All();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ��x�N�g�����S��]�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void AxisVector::RotationAxis_PivotUp(const float radian)
{
	// �O�x�N�g������]������
	forward_.RotationVector_AxisFree(up_, radian);

	// �E�x�N�g���̍쐬�y�я�x�N�g���̍č쐬
	CalculationAxis_ConfirmAxisForward();

	// ���K��
	NormalizeAxis_All();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �E�x�N�g�����S��]�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void AxisVector::RotationAxis_PivotRight(const float radian)
{
	// �O�x�N�g������]������
	forward_.RotationVector_AxisFree(right_, radian);

	// ��x�N�g���̉�]
	up_.RotationVector_AxisFree(right_, radian);

	// �E�x�N�g���̍쐬�y�я�x�N�g���̍č쐬
	CalculationAxis_ConfirmAxisForward();

	// ���K��
	NormalizeAxis_All();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �C�Ӄx�N�g�����S��]�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void AxisVector::RotationAxis_PivotFree(const Vec3 axis_vector, const float radian)
{
	// �O�x�N�g������]������
	forward_.RotationVector_AxisFree(axis_vector, radian);

	// ��x�N�g���̉�]
	up_.RotationVector_AxisFree(axis_vector, radian);

	// �E�x�N�g���̍쐬�y�я�x�N�g���̍č쐬
	CalculationAxis_ConfirmAxisForward();

	// ���K��
	NormalizeAxis_All();

}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �O�x�N�g���ݒ�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void AxisVector::SetForward(Vec3 forward)
{
	forward_ = forward;

	// �E�x�N�g���̍쐬�y�я�x�N�g���̍č쐬
	CalculationAxis_ConfirmAxisForward();

	// ���K��
	NormalizeAxis_All();
}



//--------------------------------------------------------------------------------
//
// [ �O�x�N�g��1����c����쐬����֐� ]
//
//--------------------------------------------------------------------------------

void AxisVector::CalculationAxis_ConfirmAxisForward()
{
	// �E�x�N�g���̍쐬
	right_ = up_.CreateVectorCross(forward_);

	// ��x�N�g���̍쐬
	up_ = forward_.CreateVectorCross(right_);
}



//--------------------------------------------------------------------------------
//
// [ �S���x�N�g���̐��K���֐� ]
//
//--------------------------------------------------------------------------------

void AxisVector::NormalizeAxis_All()
{
	forward_.CreateNormalize();

	up_.CreateNormalize();

	right_.CreateNormalize();

}