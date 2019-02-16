//================================================================================
//!	@file	 OBB.h
//!	@brief	 OBBClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================
#ifndef	_OBB_H_
#define _OBB_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "CollisionShapeBase.h"
#include "Plane.h"

#include <Tool/Axis.h>
#include <Tool/Vector3D.h>



//************************************************************														   
//! @brief   OBBClass
//!
//! @details OBB��Class
//************************************************************
class OBB : public CollisionShapeBase
{
//====================
// �萔
//====================
private:
	static const int MAX_POINT_NUM = 8;		//!< �ő�_��


//====================
// �ϐ�
//====================
private:
	Vector3D position_;				//!< ���W
	Vector3D length_;				//!< �e�ӂ̒���
	Axis axis_;						//!< ���x�N�g��
	Plane plane_right_;				//!< �E��������
	Plane plane_up_;				//!< ���������
	Plane plane_forward_;			//!< �O��������
	Plane plane_inverse_right_;		//!< �t�E��������
	Plane plane_inverse_up_;		//!< �t���������
	Plane plane_inverse_forward_;	//!< �t�O��������


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief ���W�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D* ���W
	//----------------------------------------
	Vector3D* getpPosition();

	//----------------------------------------
	//! @brief ���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Axis* ��
	//----------------------------------------
	Axis* getpAxis();

	//----------------------------------------
	//! @brief ���ݒ�֐�
	//! @details
	//! @param value ��
	//! @retval void �Ȃ�
	//----------------------------------------
	void setAxis(Axis* value);

	//----------------------------------------
	//! @brief �O�x�N�g���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D* �O�x�N�g��
	//----------------------------------------
	Vector3D* getpForward();

	//----------------------------------------
	//! @brief �O�x�N�g���ݒ�֐�
	//! @details
	//! @param value �O�x�N�g��
	//! @retval void �Ȃ�
	//----------------------------------------
	void setForward(Vector3D value);

	//----------------------------------------
	//! @brief ��x�N�g���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D* ��x�N�g��
	//----------------------------------------
	Vector3D* getpUp();

	//----------------------------------------
	//! @brief �E�x�N�g���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D* �E�x�N�g��
	//----------------------------------------
	Vector3D* getpRight();

	//----------------------------------------
	//! @brief �e�ӂ̎擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D* �e�ӂ̒���
	//----------------------------------------
	Vector3D* getpLength();

	//----------------------------------------
	//! @brief �E�����x�N�g���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D �E�����x�N�g��
	//----------------------------------------
	Vector3D getRightLengthVector();

	//----------------------------------------
	//! @brief �㒷���x�N�g���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D �㒷���x�N�g��
	//----------------------------------------
	Vector3D getUpLengthVector();

	//----------------------------------------
	//! @brief �O�����x�N�g���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D �O�����x�N�g��
	//----------------------------------------
	Vector3D getForwardLengthVector();

	//----------------------------------------
	//! @brief �E�����x�N�g���̔����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D �E�����x�N�g���̔���
	//----------------------------------------
	Vector3D getRightLengthVectorHalf();

	//----------------------------------------
	//! @brief �㒷���x�N�g���̔����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D �㒷���x�N�g���̔���
	//----------------------------------------
	Vector3D getUpLengthVectorHalf();

	//----------------------------------------
	//! @brief �O�����x�N�g���̔����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D �O�����x�N�g���̔���
	//----------------------------------------
	Vector3D getForwardLengthVectorHalf();

	//----------------------------------------
	//! @brief �E�������ʎ擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Plane* �E��������
	//----------------------------------------
	Plane* getpPlaneRight();

	//----------------------------------------
	//! @brief ��������ʎ擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Plane* ���������
	//----------------------------------------
	Plane* getpPlaneUp();

	//----------------------------------------
	//! @brief �O�������ʎ擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Plane* �O��������
	//----------------------------------------
	Plane* getpPlaneForward();

	//----------------------------------------
	//! @brief �t�E�������ʎ擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Plane* �t�E��������
	//----------------------------------------
	Plane* getpPlaneInverseRight();

	//----------------------------------------
	//! @brief �t��������ʎ擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Plane* �t���������
	//----------------------------------------
	Plane* getpPlaneInverseUp();

	//----------------------------------------
	//! @brief �t�O�������ʎ擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Plane* �t�O��������
	//----------------------------------------
	Plane* getpPlaneInverseForward();


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �f�X�g���N�^
	//! @details
	//! @param void �Ȃ�
	//----------------------------------------
	~OBB();

	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param position ���W
	//! @param length   �e�ӂ̒���
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init(Vector3D position, Vector3D length);

	//----------------------------------------
	//! @brief �X�V�֐�
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Update() override;

	//----------------------------------------
	//! @brief X����]�֐�
	//! @details
	//! @param radian �p�x
	//! @retval void �Ȃ�
	//----------------------------------------
	void RotationAxisX(float radian);

	//----------------------------------------
	//! @brief Y����]�֐�
	//! @details
	//! @param radian �p�x
	//! @retval void �Ȃ�
	//----------------------------------------
	void RotationAxisY(float radian);

	//----------------------------------------
	//! @brief Z����]�֐�
	//! @details
	//! @param radian �p�x
	//! @retval void �Ȃ�
	//----------------------------------------
	void RotationAxisZ(float radian);

	//----------------------------------------
	//! @brief �O�x�N�g������]�֐�
	//! @details
	//! @param radian �p�x
	//! @retval void �Ȃ�
	//----------------------------------------
	void RotationAxisForward(float radian);

	//----------------------------------------
	//! @brief ��x�N�g������]�֐�
	//! @details
	//! @param radian �p�x
	//! @retval void �Ȃ�
	//----------------------------------------
	void RotationAxisUp(float radian);

	//----------------------------------------
	//! @brief �E�x�N�g������]�֐�
	//! @details
	//! @param radian �p�x
	//! @retval void �Ȃ�
	//----------------------------------------
	void RotationAxisRight(float radian);

	//----------------------------------------
	//! @brief �C�ӎ���]�֐�
	//! @details
	//! @param radian �p�x
	//! @retval void �Ȃ�
	//----------------------------------------
	void RotationAxisAny(Vec3 axis, float radian);

	//----------------------------------------
	//! @brief �s���]�֐�
	//! @details
	//! @param rotation_matrix �s��
	//! @retval void �Ȃ�
	//----------------------------------------
	void RotationMatrix(MATRIX* rotation_matrix);

	//----------------------------------------
	//! @brief �N�H�[�^�j�I����]��]�֐�
	//! @details
	//! @param quaternion �N�H�[�^�j�I��
	//! @retval void �Ȃ�
	//----------------------------------------
	void RotationQuaternion(Quaternion* quaternion);

private:
	//----------------------------------------
	//! @brief �ŏ��l�ƍő�l�Z�o�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void CalculationMinAndMax() override;

	//----------------------------------------
	//! @brief ���ʎZ�o�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void CalculationPlane();
};



#endif