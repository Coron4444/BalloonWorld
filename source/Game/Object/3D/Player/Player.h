//================================================================================
//!	@file	 Player.h
//!	@brief	 �v���C���[Class
//! @details 
//!	@author  Kai Araki									@date 2018/04/01
//================================================================================
#ifndef	_PLAYER_H_
#define _PLAYER_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <GameEngine/GameObject/GameObjectNull.h>

#include <Scenes/GameScene/GameScene.h>



//****************************************
// �N���X�錾
//****************************************
class BalloonGroup;
class BulletPhysicsObject;
class Camera;



//************************************************************														   
//! @brief   �v���C���[Class
//!
//! @details �v���C���[��Class
//************************************************************
class Player : public GameObjectNull
{
//====================
// �ϐ�
//====================
private:
	static const float ACCELERATION;	//!< �����x


//====================
// �ϐ�
//====================
private:
	GameScene* game_scene_ = nullptr;				//!< �Q�[���V�[��
	BalloonGroup* balloon_group_ = nullptr;			//!< ���D�Q
	Camera* camera_ = nullptr;						//!< �J����
	BulletPhysicsObject* bullet_object_ = nullptr;	//!< �o���b�g�I�u�W�F�N�g


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief ���D�Q�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval BalloonGroup* ���D�Q
	//----------------------------------------
	BalloonGroup* getpBalloonGroup();

	//----------------------------------------
	//! @brief ���D�Q�ݒ�֐�
	//! @details
	//! @param *value ���D�Q
	//! @retval void �Ȃ�
	//----------------------------------------
	void setBalloonGroup(BalloonGroup* value);

	//----------------------------------------
	//! @brief �J�����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Camera* �J����
	//----------------------------------------
	Camera* getpCamera();

	//----------------------------------------
	//! @brief �J�����ݒ�֐�
	//! @details
	//! @param *value �J����
	//! @retval void �Ȃ�
	//----------------------------------------
	void setCamera(Camera* value);


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param *draw      �`����N���X
	//! @param *collision �Փˊ��N���X
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init(DrawBase* draw, CollisionBase* collision);

	//----------------------------------------
	//! @brief �I���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Uninit() override;

	//----------------------------------------
	//! @brief �X�V�֐�
	//! @details 
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Update() override;

	//----------------------------------------
	//! @brief �f�o�b�O�\���֐�
	//! @details 
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void DebugDisplay() override;

private:
	//----------------------------------------
	//! @brief ���s�ړ����͊֐�
	//! @details 
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void InputTranslation();

	//----------------------------------------
	//! @brief �J�����������s�ړ����͊֐�
	//! @details 
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void InputTranslationNotCamera();
};



#endif