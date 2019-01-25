//================================================================================
//!	@file	 Capsule.h
//!	@brief	 �J�v�Z��Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================
#ifndef	_CAPSULE_H_
#define _CAPSULE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "../CollisionShapeBase.h"
#include "../Cylinder/Cylinder.h"
#include "../Sphere/Sphere.h"

#include <Vector3D.h>



//************************************************************														   
//! @brief   �J�v�Z��Class
//!
//! @details �J�v�Z����Class
//************************************************************
class Capsule : public CollisionShapeBase
{
//====================
// �ϐ�
//====================
private:
	Cylinder cylinder_;		//!< �~��
	Sphere sphere0_;		//!< ��0
	Sphere sphere1_;		//!< ��1


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief ��0�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Sphere* ��0
	//----------------------------------------
	Sphere* getpSphere0();

	//----------------------------------------
	//! @brief ��1�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Sphere* ��1
	//----------------------------------------
	Sphere* getpSphere1();

	//----------------------------------------
	//! @brief �~���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Cylinder* �~��
	//----------------------------------------
	Cylinder* getpCylinder();

	//----------------------------------------
	//! @brief �����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval LineSegment* ����
	//----------------------------------------
	LineSegment* getpLineSegment();

	//----------------------------------------
	//! @brief ���W�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D* ���W
	//----------------------------------------
	Vector3D* getpPosition();

	//----------------------------------------
	//! @brief �����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D* ����
	//----------------------------------------
	Vector3D* getpVector();

	//----------------------------------------
	//! @brief �����x�N�g�����Z�ςݍ��W�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D �����x�N�g�����Z�ςݍ��W
	//----------------------------------------
	Vector3D getAddVectorToPosition();

	//----------------------------------------
	//! @brief ���a�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float ���a
	//----------------------------------------
	float getRadius();

	//----------------------------------------
	//! @brief ���a�ݒ�֐�
	//! @details
	//! @param value ���a
	//! @retval void �Ȃ�
	//----------------------------------------
	void setRadius(float value);


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �R���X�g���N�^
	//! @param void �Ȃ�
	//----------------------------------------
	Capsule();

	//----------------------------------------
	//! @brief �������֐�
	//! @param position �n�_���W
	//! @param vector   ����
	//! @param radius   ���a
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init(Vector3D position, Vector3D vector, float radius);

	//----------------------------------------
	//! @brief �������֐�
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Update();
};



#endif