//================================================================================
//!	@file	 SceneManager.h
//!	@brief	 �V�[���}�l�[�W��Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/01
//================================================================================
#ifndef	_SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <ComponentManager/DrawManager/Fade/Fade.h>
#include <Vector3D.h>



//****************************************
// �N���X�錾
//****************************************
class SceneBase;



//************************************************************														   
//! @brief   �V�[���}�l�[�W��Class
//!
//! @details �V�[���̃}�l�[�W��Class
//************************************************************
class SceneManager
{
//====================
// �N���X
//====================
public:
	//****************************************														   
	//! @brief   �V�[���ԋ��ʃf�[�^Class
	//!
	//! @details �V�[���Ԃ̋��ʃf�[�^Class
	//****************************************
	class CommonData
	{
	//====================
	// �ϐ�
	//====================
	private:
		bool is_update_;		//!< �S�̂��X�V���邩�t���O
		bool is_clear_;			//!< �Q�[�����N���A�������t���O


	//====================
	// �v���p�e�B
	//====================
	public:
		//----------------------------------------
		//! @brief �X�V�t���O�擾�֐�
		//! @details
		//! @param void �Ȃ�
		//! @retval bool �X�V�̗L��
		//----------------------------------------
		bool getIsUpdate();
		
		//----------------------------------------
		//! @brief �X�V�t���O�ݒ�֐�
		//! @details
		//! @param value �X�V�t���O
		//! @retval void �Ȃ�
		//----------------------------------------
		void setIsUpdate(bool value);
		
		//----------------------------------------
		//! @brief �N���A�t���O�擾�֐�
		//! @details
		//! @param void �Ȃ�
		//! @retval bool �N���A�̗L��
		//----------------------------------------
		bool getIsClear();

		//----------------------------------------
		//! @brief �N���A�t���O�ݒ�֐�
		//! @details
		//! @param value �N���A�t���O
		//! @retval void �Ȃ�
		//----------------------------------------
		void setIsClear(bool value);


	//====================
	// �֐�
	//====================
	public:
		//----------------------------------------
		//! @brief ���Z�b�g�֐�
		//! @details
		//! @param void �Ȃ�
		//! @retval void �Ȃ�
		//----------------------------------------
		void Reset()
		{
			is_update_ = false;
			is_clear_ = false;
		}
	};


//====================
// �񋓌^��`
//====================
public:
	// �X�e�[�g
	enum State
	{
		NONE = -1,
		CHANGE_SCENE,
		RESET_SCENE,
		MAX
	};


//====================
// �萔
//====================
private:
	static const Fade::Type DEFAULT_FADE_TYPE;		//!< �����t�F�[�h�^�C�v
	static const float      DEFAULT_FADE_SPEED;		//!< �����t�F�[�h���x
	static const XColor4    DEFAULT_FADE_COLOR;		//!< �����t�F�[�h�F


//====================
// �ϐ�
//====================
private:
	State state_ = State::NONE;						//!< �V�[���}�l�[�W���X�e�[�g
	CommonData* common_data_ = nullptr;				//!< �V�[���ԋ��ʃf�[�^
	SceneBase* current_scene_ = nullptr;			//!< ���݂̃V�[��
	SceneBase* next_scene_ = nullptr;				//!< ���̃V�[��
	Fade::Type fade_type_ = DEFAULT_FADE_TYPE;		//!< �t�F�[�h�̎��
	float fade_speed_ = DEFAULT_FADE_SPEED;			//!< �t�F�[�h���x
	XColor4 fade_color_ = DEFAULT_FADE_COLOR;		//!< �t�F�[�h�F


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief ���̃V�[���|�C���^�ݒ�֐�
	//! @details
	//! @param *value ���̃V�[���|�C���^
	//! @retval void �Ȃ�
	//----------------------------------------
	void setNextScene(SceneBase* value);

	//----------------------------------------
	//! @brief ���ʃf�[�^�|�C���^�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval CommonData* ���ʃf�[�^�|�C���^
	//----------------------------------------
	CommonData* getpCommonData();
	
	//----------------------------------------
	//! @brief �t�F�[�h�^�C�v�ݒ�֐�
	//! @details
	//! @param value �t�F�[�h�^�C�v
	//! @retval void �Ȃ�
	//----------------------------------------
	void setFadeType(Fade::Type value);
	
	//----------------------------------------
	//! @brief �t�F�[�h���x�ݒ�֐�
	//! @details
	//! @param value �t�F�[�h���x
	//! @retval void �Ȃ�
	//----------------------------------------
	void setFadeSpeed(float value);
	
	//----------------------------------------
	//! @brief �t�F�[�h�F�ݒ�֐�
	//! @details
	//! @param value �t�F�[�h�F
	//! @retval void �Ȃ�
	//----------------------------------------
	void setFadeColor(XColor4 value);


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param *scene �ŏ��̃V�[��
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init(SceneBase* scene);

	//----------------------------------------
	//! @brief �I���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Uninit();

	//----------------------------------------
	//! @brief �X�V�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Update();

	//----------------------------------------
	//! @brief �V�[���X�V�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void UpdateScene();

	//----------------------------------------
	//! @brief �V�[���`��֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void DrawScene();

	//----------------------------------------
	//! @brief �V�[�����Z�b�g�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void ResetScene();

private:
	//----------------------------------------
	//! @brief �V�[���ύX�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void SceneChange();

	//----------------------------------------
	//! @brief �V�[�����Z�b�g�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void SceneReset();
};



#endif