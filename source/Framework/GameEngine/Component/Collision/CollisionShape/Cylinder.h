//================================================================================
//!	@file	 Cylinder.h
//!	@brief	 �~��Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================
#ifndef	_CYLINDER_H_
#define _CYLINDER_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "../CollisionShapeBase.h"
#include "../LineSegment/LineSegment.h"

#include <Vector3D.h>



//************************************************************														   
//! @brief   �~��Class
//!
//! @details �~����Class
//************************************************************
class Cylinder : public CollisionShapeBase
{
//====================
// �ϐ�
//====================
private:
	LineSegment line_segment_;	//!< ����
	float radius_;				//!< ���a


//====================
// �v���p�e�B
//====================
public:
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
	//! @details
	//! @param void �Ȃ�
	//----------------------------------------
	Cylinder();

	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param position �n�_���W
	//! @param vector   ����
	//! @param radius   ���a
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init(Vector3D position, Vector3D vector, float radius);
};



#endif