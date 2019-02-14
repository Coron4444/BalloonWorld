//================================================================================
//!	@file	 CollisionInformation.h
//!	@brief	 �Փˏ��Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/14
//================================================================================
#ifndef	_COLLISION_INFORMATION_H_
#define _COLLISION_INFORMATION_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "CollisionObject.h"
#include "CollisionShape/LineSegment.h"

#include <Tool/Vector3D.h>



//****************************************
// �N���X�錾
//****************************************
class CollisionBase;



//************************************************************														   
//! @brief   �Փˏ��Class
//!
//! @details �Փ˂̏��Class
//************************************************************
class CollisionInformation
{
//====================
// �ϐ�
//====================
private:
	Vector3D collision_point_;					//!< �Փ˓_
	Vector3D collision_normal_;					//!< �Փ˓_�@��
	LineSegment* collision_line_segment_;		//!< �Փː���(���ʗp)
	Vector3D nesting_vector_;					//!< �߂荞�݃x�N�g��
	CollisionBase* opponent_base_;				//!< ����̏Փˊ��N���X
	CollisionObject* my_object_;				//!< �����̏Փ˃I�u�W�F�N�g
	CollisionObject* opponent_object_;			//!< ����̏Փ˃I�u�W�F�N�g
	CollisionObject::Shape* my_shape_;			//!< �����̏Փˌ`��
	CollisionObject::Shape* opponent_shape_;	//!< ����̏Փˌ`��


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �Փ˓_�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D* �Փ˓_
	//----------------------------------------
	Vector3D* getpCollisionPoint();

	//----------------------------------------
	//! @brief �Փ˓_�ݒ�֐�
	//! @details
	//! @param value �߂荞�݃x�N�g��
	//! @retval void �Ȃ�
	//----------------------------------------
	void setCollisionPoint(Vector3D value);

	//----------------------------------------
	//! @brief �Փ˓_�@���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D* �Փ˓_�@��
	//----------------------------------------
	Vector3D* getpCollisionPointNormal();

	//----------------------------------------
	//! @brief �Փ˓_�@���ݒ�֐�
	//! @details
	//! @param value �Փ˓_�@��
	//! @retval void �Ȃ�
	//----------------------------------------
	void setCollisionPointNormal(Vector3D value);

	//----------------------------------------
	//! @brief  �Փː���(���ʗp)�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval LineSegment*  �Փː���(���ʗp)
	//----------------------------------------
	LineSegment* getpCollisionLineSegment();

	//----------------------------------------
	//! @brief  �Փː���(���ʗp)�ݒ�֐�
	//! @details
	//! @param *value  �Փː���(���ʗp)
	//! @retval void �Ȃ�
	//----------------------------------------
	void setCollisionLineSegment(LineSegment* value);

	//----------------------------------------
	//! @brief �߂荞�݃x�N�g���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D* �߂荞�݃x�N�g��
	//----------------------------------------
	Vector3D* getpNestingVector();

	//----------------------------------------
	//! @brief �߂荞�݃x�N�g���ݒ�֐�
	//! @details
	//! @param value �߂荞�݃x�N�g��
	//! @retval void �Ȃ�
	//----------------------------------------
	void setNestingVector(Vector3D value);

	//----------------------------------------
	//! @brief ����̏Փˊ��N���X�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval CollisionBase* ����̏Փˊ��N���X
	//----------------------------------------
	CollisionBase* getpOpponentCollisionBase();

	//----------------------------------------
	//! @brief ����̏Փˊ��N���X�ݒ�֐�
	//! @details
	//! @param *value ����̏Փˊ��N���X
	//! @retval void �Ȃ�
	//----------------------------------------
	void setOpponentCollisionBase(CollisionBase* value);

	//----------------------------------------
	//! @brief �����̏Փ˃I�u�W�F�N�g�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval CollisionObject* �����̏Փ˃I�u�W�F�N�g
	//----------------------------------------
	CollisionObject* getpMyObject();

	//----------------------------------------
	//! @brief �����̏Փ˃I�u�W�F�N�g�ݒ�֐�
	//! @details
	//! @param *value �����̏Փ˃I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	void setMyObject(CollisionObject* value);

	//----------------------------------------
	//! @brief ����̏Փ˃I�u�W�F�N�g�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval CollisionObject* ����̏Փ˃I�u�W�F�N�g
	//----------------------------------------
	CollisionObject* getpOpponentObject();

	//----------------------------------------
	//! @brief ����̏Փ˃I�u�W�F�N�g�ݒ�֐�
	//! @details
	//! @param *value ����̏Փ˃I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	void setOpponentObject(CollisionObject* value);

	//----------------------------------------
	//! @brief �����̏Փˌ`��擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval CollisionObject::Shape* �����̏Փˌ`��
	//----------------------------------------
	CollisionObject::Shape* getpMyShape();

	//----------------------------------------
	//! @brief �����̏Փˌ`��ݒ�֐�
	//! @details
	//! @param *value �����̏Փˌ`��
	//! @retval void �Ȃ�
	//----------------------------------------
	void setMyShape(CollisionObject::Shape* value);

	//----------------------------------------
	//! @brief ����̏Փˌ`��擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval CollisionObject::Shape* ����̏Փˌ`��
	//----------------------------------------
	CollisionObject::Shape* getpOpponentShape();

	//----------------------------------------
	//! @brief ����̏Փˌ`��ݒ�֐�
	//! @details
	//! @param *value ����̏Փˌ`��
	//! @retval void �Ȃ�
	//----------------------------------------
	void setOpponentShape(CollisionObject::Shape* value);
};



#endif