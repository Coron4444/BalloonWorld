//================================================================================
//!	@file	 Needle.h
//!	@brief	 ��Class
//! @details 
//!	@author  Kai Araki									@date 2019/2/20
//================================================================================
#ifndef	_NEEDLE_H_
#define _NEEDLE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <GameEngine/GameObject/GameObjectNull.h>

#include <Scenes/GameScene/GameScene.h>



//************************************************************														   
//! @brief   ��Class
//!
//! @details ����Class
//************************************************************
class Needle : public GameObjectNull
{
//====================
// �N���X
//====================
public :
	//**************************************************														   
	//! @brief   �X�e�[�gClass
	//!
	//! @details �X�e�[�g��Class
	//**************************************************
	class State
	{
	//====================
	// �ϐ�
	//====================
	private:
		Needle* needle_ = nullptr;	//!<  ��

	//====================
	// �v���p�e�B
	//====================
	public:
		//----------------------------------------
		//! @brief ���擾�֐�
		//! @details
		//! @param void �Ȃ�
		//! @retval Needle* ��
		//----------------------------------------
		Needle* getpNeedle();

		//----------------------------------------
		//! @brief ���ݒ�֐�
		//! @details
		//! @param *value ��
		//! @retval void �Ȃ�
		//----------------------------------------
		void setNeedle(Needle* value);

	//====================
	// �֐�
	//====================
	public:
		//----------------------------------------
		//! @brief �f�X�g���N�^
		//! @details
		//! @param void �Ȃ�
		//----------------------------------------
		virtual ~State();

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
	};


//====================
// �ϐ�
//====================
private:
	State* state_;	//!< �X�e�[�g
	bool is_damage_ = true;

//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief ���W�ݒ�֐�
	//! @details
	//! @param value ���W
	//! @retval void �Ȃ�
	//----------------------------------------
	void setPosition(Vec3 value);

	//----------------------------------------
	//! @brief �g�k�ݒ�֐�
	//! @details
	//! @param value �g�k
	//! @retval void �Ȃ�
	//----------------------------------------
	void setScale(float value);

	//----------------------------------------
	//! @brief �X�e�[�g�ݒ�֐�
	//! @details
	//! @param *svalue �X�e�[�g
	//! @retval void �Ȃ�
	//----------------------------------------
	void setState(State* value);
	

	bool getIsDamage()
	{
		bool temp = is_damage_;
		is_damage_ = false;
		return temp;
	}

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

};



#endif