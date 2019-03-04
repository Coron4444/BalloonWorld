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
class BalloonGroup;
class Camera;
class Player;
class StartBlock;
class Scaffold;
class Needle;


//************************************************************														   
//! @brief   �X�e�[�W�}�l�[�W��Class
//!
//! @details �X�e�[�W�}�l�[�W����Class
//************************************************************
class StageManager : public GameObjectNull
{
//====================
// �萔
//====================
private:
	static const int MAX_TIME;		//!< �ő厞��
	static const int BONUS_SCORE;		//!< �{�[�i�X�X�R�A
	static const int BONUS_SCORE_RAITO;	//!< �{�[�i�X�X�R�A�䗦


//====================
// �ϐ�
//====================
private:
	bool is_enable_ = false;					//!< �L���t���O
	bool is_ground_ = false;					//!< ���n�t���O
	int score_ = 0;								//!< �X�R�A
	int time_ = 0;								//!< ����
	BalloonGroup* balloon_group_ = nullptr;		//!< ���D�Q
	Player* player_ = nullptr;					//!< �v���C���[
	StartBlock* start_block_ = nullptr;			//!< �X�^�[�g�u���b�N
	Scaffold* scaffold_ = nullptr;				//!< ����
	Needle* needle_ = nullptr;					//!< ��


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �L���t���O�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval value �L���t���O
	//----------------------------------------
	bool getIsEnable();

	//----------------------------------------
	//! @brief �L���t���O�ݒ�֐�
	//! @details
	//! @param value �L���t���O
	//! @retval void �Ȃ�
	//----------------------------------------
	void setIsEnable(bool value);

	//----------------------------------------
	//! @brief �X�R�A�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval int �X�R�A
	//----------------------------------------
	int getScore();

	//----------------------------------------
	//! @brief ���Ԏ擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval int ����
	//----------------------------------------
	int getTime();

	//----------------------------------------
	//! @brief ���D���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval int ���D��
	//----------------------------------------
	int getBalloonNum();

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
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	Player* getpPlayer();

	//----------------------------------------
	//! @brief �n�ʒ��n�t���O�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	bool getIsOnTheGround();


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