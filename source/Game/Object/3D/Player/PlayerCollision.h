//================================================================================
//!	@file	 PlayerCollision.h
//!	@brief	 �v���C���[�Փ�Class
//! @details 
//!	@author  Kai Araki									@date 2018/03/27
//================================================================================
#ifndef	_PLAYER_COLLISION_H_
#define _PLAYER_COLLISION_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <GameEngine/Collision/CollisionNull.h>



//****************************************
// �N���X��`
//****************************************
class Player;



//************************************************************														   
//! @brief   �v���C���[�Փ�Class
//!
//! @details �v���C���[�̏Փ�Class
//************************************************************
class PlayerCollision : public CollisionNull
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
		TEST,
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
	Player* player_;						//!< �v���C���[
	Vector3D normal_;

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

	//----------------------------------------
	//! @brief �Փˎ��֐�
	//! @details
	//! @param *information �Փˏ��
	//! @retval void �Ȃ�
	//----------------------------------------
	void HitCollision(CollisionInformation* information) override;

	//----------------------------------------
	//! @brief �t�B�[���h�Ƃ̏Փˎ��֐�
	//! @details
	//! @param position_y �t�B�[���h�̍���
	//! @retval void �Ȃ�
	//----------------------------------------
	void HitGround(float position_y) override;

	//----------------------------------------
	//! @brief �f�o�b�O�\���֐�
	//! @details 
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	//void DebugDisplay() override;

private:
	//----------------------------------------
	//! @brief ���C�����Փˎ��֐�
	//! @details
	//! @param *information �Փˏ��
	//! @retval void �Ȃ�
	//----------------------------------------
	void HitMainSphere(CollisionInformation* information);
};



#endif