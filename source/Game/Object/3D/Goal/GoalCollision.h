//================================================================================
//!	@file	 GoalCollision.h
//!	@brief	 �S�[���Փ�Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/28
//================================================================================
#ifndef	_GOAL_COLLISION_H_
#define _GOAL_COLLISION_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <GameEngine/Collision/CollisionNull.h>




//************************************************************														   
//! @brief   �S�[���Փ�Class
//!
//! @details �S�[���̏Փ�Class
//************************************************************
class GoalCollision : public CollisionNull
{
//====================
// �񋓌^��`
//====================
public:
	enum class ObjectTag
	{
		NONE = -1,
		MAIN,
		MAX
	};

	enum class ShapeTag
	{
		NONE = -1,
		MAIN,
		MAX
	};


//====================
// �萔
//====================
private:
	static const float MAIN_SPHERE_RADIUS;		//!< ���C�������a


//====================
// �ϐ�
//====================
private:
	CollisionObject* collision_object_;		//!< �Փ˃I�u�W�F�N�g
	Sphere* main_sphere_;					//!< ���C����


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