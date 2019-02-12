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
	GameScene* game_scene_ = nullptr;			//!< �Q�[���V�[��
	BalloonGroup* balloon_group_ = nullptr;		//!< ���D�Q
	Camera* camera_ = nullptr;					//!< �J����

//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �Q�[���V�[���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval GameScene* �Q�[���V�[��
	//----------------------------------------
	GameScene* getpGameScene();

	//----------------------------------------
	//! @brief �Q�[���V�[���ݒ�֐�
	//! @details
	//! @param *value �Q�[���V�[��
	//! @retval void �Ȃ�
	//----------------------------------------
	void setGameScene(GameScene* value);

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
	//! @param *update     �X�V���N���X
	//! @param *draw       �`����N���X
	//! @param *collision  �Փˊ��N���X
	//! @param *game_scene �Q�[���V�[��
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init(UpdateBase* update, DrawBase* draw, CollisionBase* collision, 
			  GameScene* game_scene);

	//----------------------------------------
	//! @brief �I���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Uninit() override;
};



#endif