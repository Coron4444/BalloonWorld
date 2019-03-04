//================================================================================
//!	@file	 ScaffoldCollision.h
//!	@brief	 ����Փ�Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================
#ifndef	_SCAFFOLD_COLLISION_H_
#define _SCAFFOLD_COLLISION_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <GameEngine/Collision/CollisionNull.h>




//************************************************************														   
//! @brief   ����Փ�Class
//!
//! @details ����̏Փ�Class
//************************************************************
class ScaffoldCollision : public CollisionNull
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
	static const Vector3D MAIN_OBB_LENGTH;		//!< ���C��OBB����


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