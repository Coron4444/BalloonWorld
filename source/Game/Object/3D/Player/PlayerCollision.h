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
		BOUNDING_SPHERE,
		SUBSTANCE_SPHERE,
		MAX
	};


//====================
// �萔
//====================
private:
	static const float BOUNDING_SPHERE_RADIUS;		//!< �o�E���f�B���O���̔��a
	static const float SUBSTANCE_SPHERE_RADIUS;		//!< ���̋��̔��a


//====================
// �ϐ�
//====================
private:
	CollisionObjects* collision_objects_;	//!< �Փ˃I�u�W�F�N�g�Q
	CollisionObject* bounding_sphere_;		//!< �o�E���f�B���O��
	CollisionObject* substance_sphere_;		//!< ���̋�
	Player* player_;						//!< �v���C���[


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
	//! @param *hit_collision ����̏Փˊ��N���X
	//! @param *hit_object    ����̏Փ˃I�u�W�F�N�g
	//! @param *hit_my_object �����̏Փ˃I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	void HitCollision(CollisionBase* hit_collision,
					  CollisionObject* hit_object,
					  CollisionObject* hit_my_object) override;

	//----------------------------------------
	//! @brief ��Փˎ��֐�
	//! @details
	//! @param *hit_collision ����̏Փˊ��N���X
	//! @param *hit_object    ����̏Փ˃I�u�W�F�N�g
	//! @param *hit_my_object �����̏Փ˃I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	void NotHitCollision(CollisionBase*	hit_collision,
						 CollisionObject* hit_object,
						 CollisionObject* hit_my_object) override;

	//----------------------------------------
	//! @brief �t�B�[���h�Ƃ̏Փˎ��֐�
	//! @details
	//! @param position_y �t�B�[���h�̍���
	//! @retval void �Ȃ�
	//----------------------------------------
	void HitGround(float position_y) override;


private:
	//----------------------------------------
	//! @brief �o�E���f�B���O���Փˎ��֐�
	//! @details
	//! @param *hit_collision ����̏Փˊ��N���X
	//! @param *hit_object    ����̏Փ˃I�u�W�F�N�g
	//! @param *hit_my_object �����̏Փ˃I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	void HitBoundingSphere(CollisionBase* hit_collision,
						   CollisionObject* hit_object,
						   CollisionObject* hit_my_object);

	//----------------------------------------
	//! @brief �o�E���f�B���O����Փˎ��֐�
	//! @details
	//! @param *hit_collision ����̏Փˊ��N���X
	//! @param *hit_object    ����̏Փ˃I�u�W�F�N�g
	//! @param *hit_my_object �����̏Փ˃I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	void NotHitBoundingSphere(CollisionBase* hit_collision,
							  CollisionObject* hit_object,
							  CollisionObject* hit_my_object);

	//----------------------------------------
	//! @brief ���̋��Փˎ��֐�
	//! @details
	//! @param *hit_collision ����̏Փˊ��N���X
	//! @param *hit_object    ����̏Փ˃I�u�W�F�N�g
	//! @param *hit_my_object �����̏Փ˃I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	void HitSubstance(CollisionBase* hit_collision,
					  CollisionObject* hit_object,
					  CollisionObject* hit_my_object);
};



#endif