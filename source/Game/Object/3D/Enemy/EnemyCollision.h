//================================================================================
//!	@file	 EnemyCollision.h
//!	@brief	 �G�Փ�Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================
#ifndef	_ENEMY_COLLISION_H_
#define _ENEMY_COLLISION_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <GameEngine/Collision/CollisionNull.h>



//************************************************************														   
//! @brief   �G�Փ�Class
//!
//! @details �G�̏Փ�Class
//************************************************************
class EnemyCollision : public CollisionNull
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
	static const Vec3 MAIN_OBB_LENGTH;		//!< ���C��OBB����


//====================
// �ϐ�
//====================
private:
	CollisionObject* collision_object_;		//!< �Փ˃I�u�W�F�N�g
	OBB* main_obb_;							//!< ���C��OBB


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