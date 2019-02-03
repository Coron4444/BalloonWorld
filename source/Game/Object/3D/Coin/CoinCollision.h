//================================================================================
//!	@file	 CoinCollision.h
//!	@brief	 �R�C���Փ�Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================
#ifndef	_COIN_COLLISION_H_
#define _COIN_COLLISION_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <GameEngine/Collision/CollisionNull.h>



//************************************************************														   
//! @brief   �R�C���Փ�Class
//!
//! @details �R�C���̏Փ�Class
//************************************************************
class CoinCollision : public CollisionNull
{
//====================
// �񋓌^��`
//====================
public:
	enum class ObjectTag
	{
		NONE = -1,
		BOUNDING_OBB,
		SUBSTANCE_OBB,
		MAX
	};

//====================
// �萔
//====================
private:
	static const Vec3 BOUNDING_OBB_LENGTH;		//!< �o�E���f�B���OOBB����
	static const Vec3 SUBSTANCE_OBB_LENGTH;		//!< ����OBB����


//====================
// �ϐ�
//====================
private:
	CollisionObjects* collision_objects_;		//!< �Փ˃I�u�W�F�N�g�Q
	CollisionObject* bounding_obb_;				//!< �o�E���f�B���OOBB
	CollisionObject* substance_obb_;			//!< ����OBB


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