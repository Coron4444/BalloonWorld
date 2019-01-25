//================================================================================
//
//    ���x�N�g���N���X
//    Author : Araki Kai                                �쐬�� : 2018/01/08
//
//================================================================================

#ifndef	_AXIS_VECTOR_H_
#define _AXIS_VECTOR_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include "../../Vector3D.h"



//======================================================================
//
// �N���X��`
//
//======================================================================

class AxisVector
{
//------------------------------------------------------------
private :
	static const Vector3D DEFAULT_FORWARD;
	static const Vector3D DEFAULT_UP;
	static const Vector3D DEFAULT_RIGHT;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �f�t�H���g�R���X�g���N�^
	AxisVector();


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// ���Z�b�g
	void ResetAxisVector();

	// ��]
	void RotationMatrix(MATRIX* rotation_matrix);
	void RotationAxis_PivotX(const float radian);
	void RotationAxis_PivotY(const float radian);
	void RotationAxis_PivotZ(const float radian);

	void RotationAxis_PivotForward(const float radian);
	void RotationAxis_PivotUp     (const float radian);
	void RotationAxis_PivotRight  (const float radian);

	void RotationAxis_PivotFree(const Vec3 axis_vector, const float radian);

	// �Z�b�g�֐�
	void SetForward(Vec3 forward);
	
	// �Q�b�g�֐�
	const Vector3D* GetForawrd() const {return &forward_;}
	const Vector3D* GetUp     () const {return &up_;     }
	const Vector3D* GetRight  () const {return &right_;  }
	const Vector3D* GetDefaultForawrd() const {return &DEFAULT_FORWARD;}
	const Vector3D* GetDefaultUp     () const {return &DEFAULT_UP;}
	const Vector3D* GetDefaultRight  () const {return &DEFAULT_RIGHT;}


//------------------------------------------------------------
private :
	

	// �O�x�N�g��1����c����쐬����
	void CalculationAxis_ConfirmAxisForward();

	// ���K��
	void NormalizeAxis_All();


//------------------------------------------------------------
private :
	// �����o�ϐ�
	Vector3D forward_;
	Vector3D up_;
	Vector3D right_;
};



#endif