//================================================================================
//!	@file	 Balloon.h
//!	@brief	 ���DClass
//! @details 
//!	@author  Kai Araki									@date 2019/02/05
//================================================================================
#ifndef	_BALLOON_H_
#define _BALLOON_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <vector>

#include <GameEngine/GameObject/GameObjectNull.h>



//****************************************
// �N���X��`
//****************************************
class BulletPhysicsObject;
class BulletPhysicsConstraint;



//************************************************************														   
//! @brief   ���DClass
//!
//! @details ���D��Class
//************************************************************
class Balloon : public GameObjectNull
{
//====================
// �萔
//====================
public:
	static const float RISING_SPEED;			//!< �㏸���x
	static const Vector3D OBB_EDGE_LENGTH_HALF;		//!< OBB�̕ӂ̒����̔���
	static const float SPHERE_RADIUS;			//!< ���̔��a


//====================
// �ϐ�
//====================
private:
	std::vector<BulletPhysicsObject*> all_object_;				//!< ���I�u�W�F�N�g
	std::vector<BulletPhysicsConstraint*> object_constraint_;	//!< �I�u�W�F�N�g�̍S��

	
//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief ���I�u�W�F�N�g���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval int ���I�u�W�F�N�g��
	//----------------------------------------
	int getAllObjectNum();

	//----------------------------------------
	//! @brief �I�u�W�F�N�g�̍S�����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval unsigned ���I�u�W�F�N�g��
	//----------------------------------------
	int getObjectConstraintNum();

	//----------------------------------------
	//! @brief �I�u�W�F�N�g�擾�֐�
	//! @details
	//! @param index �C���f�b�N�X
	//! @retval BulletPhysicsObject* �I�u�W�F�N�g
	//----------------------------------------
	BulletPhysicsObject* getpObject(unsigned index);

	//----------------------------------------
	//! @brief �I�u�W�F�N�g�̍S���擾�֐�
	//! @details
	//! @param index �C���f�b�N�X
	//! @retval BulletPhysicsConstraint* �I�u�W�F�N�g�̍S��
	//----------------------------------------
	BulletPhysicsConstraint* getpObjectConstraint(unsigned index);

	//----------------------------------------
	//! @brief ���W�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D ���W
	//----------------------------------------
	Vector3D getPosition();

	//----------------------------------------
	//! @brief ���W�ݒ�֐�
	//! @details
	//! @param value ���W
	//! @retval void �Ȃ�
	//----------------------------------------
	void setPosition(Vector3D value);


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param *draw            �`����N���X
	//! @param balloon_line_num ���D�̐��̐�
	//! @param position			���W
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init(DrawBase* draw, unsigned balloon_line_num, Vector3D position);

	//----------------------------------------
	//! @brief �X�V�֐�
	//! @details 
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Update() override;

	//----------------------------------------
	//! @brief �S������֐�
	//! @details
	//! @param index �C���f�b�N�X
	//! @retval void �Ȃ�
	//----------------------------------------
	void ReleaseConstraint(unsigned index);

	//----------------------------------------
	//! @brief ��_�S������֐�
	//! @details
	//! @param index �C���f�b�N�X
	//! @retval void �Ȃ�
	//----------------------------------------
	void ReleaseBaseConstraint();

	//----------------------------------------
	//! @brief ���x�ǉ��֐�
	//! @details
	//! @param velocity ���x
	//! @retval void �Ȃ�
	//----------------------------------------
	void AddVelocity(Vector3D velocity);

	//----------------------------------------
	//! @brief �����x�ǉ��֐�
	//! @details
	//! @param acceleration �����x
	//! @retval void �Ȃ�
	//----------------------------------------
	void AddAcceleration(Vector3D acceleration);

private:
	//----------------------------------------
	//! @brief �o���b�g�I�u�W�F�N�g�������֐�
	//! @details
	//! @param balloon_line_num ���D�̐��̐�
	//! @param position			���W
	//! @retval void �Ȃ�
	//----------------------------------------
	void InitBulletPhysicsObject(unsigned balloon_line_num, Vector3D position);
};



#endif