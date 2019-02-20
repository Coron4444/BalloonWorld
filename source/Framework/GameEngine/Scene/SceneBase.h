//================================================================================
//!	@file	 SceneBase.h
//!	@brief	 �V�[��BaseClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================
#ifndef	_SCENE_BASE_H_
#define _SCENE_BASE_H_



//****************************************
// �N���X�錾
//****************************************
class SceneManager;



//************************************************************														   
//! @brief   �V�[��BaseClass
//!
//! @details �V�[����BaseClass
//************************************************************
class SceneBase
{
//====================
// �N���X
//====================
public:
	//****************************************														   
	//! @brief   �V�[���X�e�[�gBaseClass
	//!
	//! @details �V�[���X�e�[�g��BaseClass
	//****************************************
	class StateBase
	{
	//====================
	// �ϐ�
	//====================
	private:
		SceneBase* scene_ = nullptr;	//!< �V�[��
		int id_ = -1;					//!< ID


	//====================
	// �v���p�e�B
	//====================
	public:
		//----------------------------------------
		//! @brief �V�[���擾�֐�
		//! @details
		//! @param void �Ȃ�
		//! @retval SceneBase* �V�[��
		//----------------------------------------
		SceneBase* getpScene();

		//----------------------------------------
		//! @brief �V�[���ݒ�֐�
		//! @details
		//! @param *value �V�[��
		//! @retval void �Ȃ�
		//----------------------------------------
		void setScene(SceneBase* value);

		//----------------------------------------
		//! @brief ID�擾�֐�
		//! @details
		//! @param void �Ȃ�
		//! @retval int ID
		//----------------------------------------
		int getID();

		//----------------------------------------
		//! @brief ID�ݒ�֐�
		//! @details
		//! @param *value ID
		//! @retval void �Ȃ�
		//----------------------------------------
		void setID(int value);


	//====================
	// �֐�
	//====================
	public:
		//----------------------------------------
		//! @brief �f�X�g���N�^
		//! @details
		//! @param void �Ȃ�
		//----------------------------------------
		virtual ~StateBase() = 0;

		//----------------------------------------
		//! @brief �������֐�
		//! @details
		//! @param void �Ȃ�
		//! @retval void �Ȃ�
		//----------------------------------------
		virtual void Init() = 0;

		//----------------------------------------
		//! @brief �I���֐�
		//! @details
		//! @param void �Ȃ�
		//! @retval void �Ȃ�
		//----------------------------------------
		virtual void Uninit() = 0;

		//----------------------------------------
		//! @brief �X�V�֐�
		//! @details
		//! @param void �Ȃ�
		//! @retval void �Ȃ�
		//----------------------------------------
		virtual void Update() = 0;

		//----------------------------------------
		//! @brief �|�[�Y�����֐�
		//! @details
		//! @param void �Ȃ�
		//! @retval void �Ȃ�
		//----------------------------------------
		virtual void PauseEntrance() = 0;

		//----------------------------------------
		//! @brief �|�[�Y�o���֐�
		//! @details
		//! @param void �Ȃ�
		//! @retval void �Ȃ�
		//----------------------------------------
		virtual void PauseExit() = 0;
	};


//====================
// �ϐ�
//====================
private:
	SceneManager* scene_manager_ = nullptr;		//!< �V�[���}�l�[�W��
	StateBase* state_ = nullptr;				//!< �X�e�[�g
	int current_state_id_ = -1;					//!< ���݂̃X�e�[�gID
	bool is_pause_ = false;						//!< �|�[�Y�t���O


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �V�[���}�l�[�W���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval SceneManager* �V�[���}�l�[�W��
	//----------------------------------------
	SceneManager* getpSceneManager();

	//----------------------------------------
	//! @brief �V�[���}�l�[�W���ݒ�֐�
	//! @details
	//! @param *value �V�[���}�l�[�W��
	//! @retval void �Ȃ�
	//----------------------------------------
	void setSceneManager(SceneManager* value);

	//----------------------------------------
	//! @brief �X�e�[�g�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval StateBase* �X�e�[�g
	//----------------------------------------
	StateBase* getpState();

	//----------------------------------------
	//! @brief �X�e�[�g�ݒ�֐�
	//! @details
	//! @param *value �X�e�[�g
	//! @retval void �Ȃ�
	//----------------------------------------
	void setState(StateBase* value);

	//----------------------------------------
	//! @brief ���Z�b�g�p�X�e�[�g�ݒ�֐�
	//! @details
	//! @param *value �X�e�[�g
	//! @retval void �Ȃ�
	//----------------------------------------
	void setResetState(StateBase* value);

	//----------------------------------------
	//! @brief �|�[�Y�t���O�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	bool getIsPause();

	//----------------------------------------
	//! @brief �|�[�Y�t���O�ݒ�֐�
	//! @details
	//! @param value �|�[�Y�t���O
	//! @retval void �Ȃ�
	//----------------------------------------
	void setIsPause(bool value);

	//----------------------------------------
	//! @brief ���݂̃X�e�[�gID�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval int ���݂̃X�e�[�gID
	//----------------------------------------
	int getCurrentStateID();


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �R���X�g���N�^
	//! @details
	//! @param *value �X�e�[�g
	//----------------------------------------
	SceneBase(StateBase* state);

	//----------------------------------------
	//! @brief �f�X�g���N�^
	//! @details
	//! @param void �Ȃ�
	//----------------------------------------
	virtual ~SceneBase() = 0;

	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void Init() = 0;

	//----------------------------------------
	//! @brief �I���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void Uninit() = 0;

	//----------------------------------------
	//! @brief �X�V�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void Update() = 0;

	//----------------------------------------
	//! @brief ���Z�b�g�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void Reset() = 0;

	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void InitState();

protected:
	//----------------------------------------
	//! @brief �I���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void UninitState();

	//----------------------------------------
	//! @brief �X�V�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void UpdateState();
};



#endif