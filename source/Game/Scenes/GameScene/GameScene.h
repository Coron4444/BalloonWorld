//================================================================================
//!	@file	 GameScene.h
//!	@brief	 �Q�[���V�[��Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================
#ifndef	_GAME_SCENE_H_
#define _GAME_SCENE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <GameEngine/Scene/SceneNull.h>



//****************************************
// �N���X�錾
//****************************************
class Pause;
class StageManager;
class Score;
class Time;
class BalloonNum;



//************************************************************														   
//! @brief   �Q�[���V�[��Class
//!
//! @details �Q�[���V�[�����Ǘ�����Class
//! @details �Q�[���V�[�����L�̋��L�f�[�^�������Ă���
//************************************************************
class GameScene : public SceneNull
{
//====================
// �ϐ�
//====================
public:
	enum class State
	{
		NONE = -1,
		START,
		GAME,
		PAUSE,
		END,
		MAX
	};


//====================
// �ϐ�
//====================
private:
	Pause* pause_ = nullptr;					//!< �|�[�Y
	StageManager* stage_manager_ = nullptr;		//!< �X�e�[�W�}�l�[�W��
	Score* score_ = nullptr;					//!< �X�R�A					
	Time* time_ = nullptr;						//!< ����
	BalloonNum* balloon_num_ = nullptr;			//!< ���D��


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �X�e�[�W�}�l�[�W���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval StageManager* �X�e�[�W�}�l�[�W��
	//----------------------------------------
	StageManager* getpStageManager();

	//----------------------------------------
	//! @brief �X�e�[�W�}�l�[�W���ݒ�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval StageManager* �X�e�[�W�}�l�[�W��
	//----------------------------------------
	void setStageManager(StageManager* value);

	//----------------------------------------
	//! @brief �X�R�A�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Score* �X�R�A
	//----------------------------------------
	Score* getpScore();

	//----------------------------------------
	//! @brief ���Ԏ擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Time* ����
	//----------------------------------------
	Time* getpTime();

	//----------------------------------------
	//! @brief ���D���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval BalloonNum* ���D��
	//----------------------------------------
	BalloonNum* getpBalloonNum();

	//----------------------------------------
	//! @brief �SUI�ݒ�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void setAllUI();

//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �R���X�g���N�^
	//! @details
	//! @param *value �X�e�[�g
	//----------------------------------------
	GameScene(StateBase* state);

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
	virtual void Uninit();

	//----------------------------------------
	//! @brief �X�V�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Update();
};



#endif