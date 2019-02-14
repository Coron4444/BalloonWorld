//================================================================================
//!	@file	 StartBlockCollision.h
//!	@brief	 �X�^�[�g�u���b�N�Փ�Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/13
//================================================================================
#ifndef	_GOAL_COLLISION_H_
#define _GOAL_COLLISION_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <GameEngine/Collision/CollisionNull.h>




//************************************************************														   
//! @brief   �X�^�[�g�u���b�N�Փ�Class
//!
//! @details �X�^�[�g�u���b�N�̏Փ�Class
//************************************************************
class StartBlockCollision : public CollisionNull
{
//====================
// �񋓌^��`
//====================
public:
	enum class ObjectTag
	{
		NONE = -1,
		BOUNDING_SPHERE,
		SUBSTANCE_SPHERE,
		MAX
	};

//====================
// �萔
//====================
private:
	static const float BOUNDING_SPHERE_RADIUS;		//!< �o�E���f�B���O�����a
	static const float SUBSTANCE_SPHERE_RADIUS;		//!< ���̋����a


//====================
// �ϐ�
//====================
private:
	CollisionObjects* collision_objects_;		//!< �Փ˃I�u�W�F�N�g�Q
	CollisionObject* bounding_sphere_;			//!< �o�E���f�B���O��
	CollisionObject* substance_sphere_;			//!< ���̋�


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init() override;

	//----------------------------------------
	//! @brief �X�V�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Update() override;
};



#endif