//================================================================================
//!	@file	 Physics.h
//!	@brief	 ����Class
//! @details 
//!	@author  Kai Araki									@date 2018/08/19
//================================================================================
#ifndef	_PHYSICS_H_
#define _PHYSICS_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "Vector3D.h"



//****************************************
// �N���X�錾
//****************************************
class GameObjectBase;



//************************************************************														   
//! @brief   ����Class
//!
//! @details �����̌v�ZClass
//************************************************************
class Physics
{
//====================
// �萔
//====================
private:
	static const float VELOCITY_MIN;		//!< �Œᑬ�x


//====================
// �ϐ�
//====================
private:
	bool is_enable_ = true;				//!< �L���t���O
	GameObjectBase* game_object_;		//!< �Q�[���I�u�W�F�N�g
	Vector3D acceleration_;				//!< �����x
	Vector3D velocity_;					//!< ���x
	float max_horizontal_velocity_;		//!< �ő吅�����x
	float max_vertical_velocity_;		//!< �ő吂�����x
	float mass_;						//!< ����
	float friction_;					//!< ���C
	float my_friction_;					//!< �����̖��C
	float bounciness_;					//!< ������
	float my_bounciness_;				//!< �����̔�����
	bool is_gravity_;					//!< �d�̓t���O
	float gravity_acceleration_;		//!< �d�͉����x
	Vector3D gravity_direction_;		//!< �d�̓x�N�g��
	bool is_on_tha_ground_;				//!< �n�ʂɏ���Ă���t���O
	bool is_landing_;					//!< ���n�����t���O


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �L���t���O�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval value �L���t���O
	//----------------------------------------
	bool getIsEnable();

	//----------------------------------------
	//! @brief �L���t���O�ݒ�֐�
	//! @details
	//! @param value �L���t���O
	//! @retval void �Ȃ�
	//----------------------------------------
	void setIsEnable(bool value);

	//----------------------------------------
	//! @brief �Q�[���I�u�W�F�N�g�ݒ�֐�
	//! @details
	//! @param *value �Q�[���I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	void setGameObject(GameObjectBase* value);

	//----------------------------------------
	//! @brief �����x�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D* �����x
	//----------------------------------------
	Vector3D* getpAcceleration();

	//----------------------------------------
	//! @brief ���x�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D* ���x
	//----------------------------------------
	Vector3D* getpVelocity();

	//----------------------------------------
	//! @brief �ő吅�����x�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float �ő吅�����x
	//----------------------------------------
	float getMaxHorizontalVelocity();

	//----------------------------------------
	//! @brief �ő吅�����x�ݒ�֐�
	//! @details
	//! @param value �ő吅�����x
	//! @retval void �Ȃ�
	//----------------------------------------
	void setMaxHorizontalVelocity(float value);

	//----------------------------------------
	//! @brief �ő吂�����x�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float �ő吂�����x
	//----------------------------------------
	float getMaxVerticalVelocity();

	//----------------------------------------
	//! @brief �ő吂�����x�ݒ�֐�
	//! @details
	//! @param value �ő吂�����x
	//! @retval void �Ȃ�
	//----------------------------------------
	void setMaxVerticalVelocity(float value);

	//----------------------------------------
	//! @brief ���ʎ擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float ����
	//----------------------------------------
	float getMass();

	//----------------------------------------
	//! @brief ���ʐݒ�֐�
	//! @details
	//! @param value ����
	//! @retval void �Ȃ�
	//----------------------------------------
	void setMass(float value);

	//----------------------------------------
	//! @brief ���C�͎擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float ���C��
	//----------------------------------------
	float getFriction();

	//----------------------------------------
	//! @brief �����̖��C�͎擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float �����̖��C��
	//----------------------------------------
	float getMyFriction();

	//----------------------------------------
	//! @brief �����̖��C�͐ݒ�֐�
	//! @details
	//! @param value �����̖��C��
	//! @retval void �Ȃ�
	//----------------------------------------
	void setMyFriction(float value);

	//----------------------------------------
	//! @brief �����͎擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float ������
	//----------------------------------------
	float getBounciness();

	//----------------------------------------
	//! @brief �����̔����͎擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float �����̔�����
	//----------------------------------------
	float getMyBounciness();

	//----------------------------------------
	//! @brief �����̔����͐ݒ�֐�
	//! @details
	//! @param value �����̔�����
	//! @retval void �Ȃ�
	//----------------------------------------
	void setMyBounciness(float value);

	//----------------------------------------
	//! @brief �d�̓t���O�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval bool �d�̓t���O
	//----------------------------------------
	bool getIsGravity();

	//----------------------------------------
	//! @brief �d�̓t���O�ݒ�֐�
	//! @details
	//! @param value �d�̓t���O
	//! @retval void �Ȃ�
	//----------------------------------------
	void setIsGravity(float value);

	//----------------------------------------
	//! @brief �n�ʂɏ���Ă���t���O�ݒ�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void setOnTheGround();


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �R���X�g���N�^
	//! @details
	//! @param void �Ȃ�
	//----------------------------------------
	Physics();

	//----------------------------------------
	//! @brief �X�V�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Update();

	//----------------------------------------
	//! @brief ���C�͒ǉ��֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void AddFriction(float friction);

	//----------------------------------------
	//! @brief �����͒ǉ��֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void AddBounciness(float bounciness);


private :
	//----------------------------------------
	//! @brief ���Z�b�g�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Reset();

	//----------------------------------------
	//! @brief �����x�X�V�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void UpdateAcceleration();

	//----------------------------------------
	//! @brief ���x�X�V�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void UpdateVelocity();

	//----------------------------------------
	//! @brief ���W�X�V�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void UpdatePosition();

	//----------------------------------------
	//! @brief �d�͒ǉ��֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void AddGravity();

	//----------------------------------------
	//! @brief �n�ʍX�V�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void UpdateGround();

	//----------------------------------------
	//! @brief ���x�̍ŏ��l�E�ő�l�`�F�b�N�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void CheckVelocityMinMax();

};



#endif