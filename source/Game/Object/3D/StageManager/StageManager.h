//================================================================================
//!	@file	 StageManager.h
//!	@brief	 �X�e�[�W�}�l�[�W��Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/13
//================================================================================
#ifndef	_STAGE_MANAGER_H_
#define _STAGE_MANAGER_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <GameEngine/GameObject/GameObjectNull.h>



//****************************************
// �N���X�錾
//****************************************
class Camera;
class BalloonGroup;
class Player;



//************************************************************														   
//! @brief   �X�e�[�W�}�l�[�W��Class
//!
//! @details �X�e�[�W�}�l�[�W����Class
//************************************************************
class StageManager : public GameObjectNull
{
//====================
// �ϐ�
//====================
private:
	Camera* camera_ = nullptr;					//!< �J����
	BalloonGroup* balloon_group_ = nullptr;		//!< ���D�Q
	Player* player_ = nullptr;					//!< �v���C���[


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �v���C���[�J�����ݒ�֐�
	//! @details
	//! @param *value �J����
	//! @retval void �Ȃ�
	//----------------------------------------
	void setPlayerCamera(Camera* value);

	//----------------------------------------
	//! @brief �v���C���[�擾�֐�
	//! @details
	//! @param 
	//! @retval void �Ȃ�
	//----------------------------------------
	Player* getpPlayer();


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
	void Init();

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
	//! @brief �X�e�[�W�쐬�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateStage();
};



#endif