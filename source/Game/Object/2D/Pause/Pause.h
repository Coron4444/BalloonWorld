//================================================================================
//!	@file	 Pause.h
//!	@brief	 �|�[�YClass
//! @details 
//!	@author  Kai Araki									@date 2019/02/18
//================================================================================
#ifndef	_PAUSE_H_
#define _PAUSE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <GameEngine/GameObject/GameObjectNull.h>

#include <Tool/Interpolation.h>



//************************************************************														   
//! @brief   �|�[�YClass
//!
//! @details �|�[�Y��Class
//************************************************************
class Pause : public GameObjectNull
{
//====================
// �񋓌^
//====================
public:
	enum class SelectType
	{
		NONE = -1,
		CONTINUE,
		RESTART,
		QUIT,
		MAX
	};


//====================
// �萔
//====================
private:
	static const float FRAME_SCALE;					//!< �t���[���g�k
	static const float ICON_SCALE;					//!< �A�C�R���g�k
	static const float TOP_ICON_POSITION_Y;			//!< �A�C�R����Y����W
	static const float BOTTOM_ICON_POSITION_Y;		//!< �A�C�R����Y�����W
	static const float ADD_ICON_POSITION_Y;			//!< �A�C�R����Y���W�̕ω���
	static const Vector3D DEFAULT_ICON_POSITION;		//!< ����A�C�R�����W
	static const float BLINKING_SECOND;				//!< �_�ŕb��
	static const int BLINKING_NUM;					//!< �_�Ő�
	static const unsigned CHARACTER_COLOR_NUM = 3;	//!< �����F��

public:
	static const XColor4 CHARACTER_COLOR0;			//!< �����F0
	static const XColor4 CHARACTER_COLOR1;			//!< �����F1


//====================
// �ϐ�
//====================
private:
	bool is_enable_ = false;						//!< �L���t���O
	SelectType select_type_ = SelectType::NONE;		//!< �I�������^�C�v
	Transform icon_transform_;						//!< �A�C�R���p�ό`
	XColor4 character_color_[CHARACTER_COLOR_NUM];	//!< �����F
	Interpolation<float> inter_container_[4];		//!< ��ԃR���e�i
	Interpolation<float>::Iterator inter_iter_[4];	//!< ��ԃC�e���[�^


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
	//! @brief ����t���O�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval bool ����t���O
	//----------------------------------------
	bool getIsDecision();

	//----------------------------------------
	//! @brief �A�C�R���ό`�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	Transform* getpIconTransform();

	//----------------------------------------
	//! @brief �I�������^�C�v�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval SelectType �I�������^�C�v
	//----------------------------------------
	SelectType getSelectType();

	//----------------------------------------
	//! @brief �����F�擾�֐�
	//! @details
	//! @param index �C���f�b�N�X
	//! @retval XColor4 �����F
	//----------------------------------------
	XColor4 getCharacterColor(int index);
	

//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param *update �X�V���N���X
	//! @param *draw   �`����N���X
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init(DrawBase* draw);

	//----------------------------------------
	//! @brief �X�V�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Update() override;

private:
	//----------------------------------------
	//! @brief ���͊֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Input();
};



#endif