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
	static const float ACCELERATION;			//!< �����x
	static const float MAX_VERTICAL_VELOCITY;	//!< �ő吂���������x
	static const float MAX_MASS;				//!< �ő县��

//====================
// �ϐ�
//====================
private:
	BalloonGroup* balloon_group_ = nullptr;			//!< ���D�Q
	Camera* camera_ = nullptr;						//!< �J����
	BulletPhysicsObject* bullet_object_ = nullptr;	//!< �o���b�g�I�u�W�F�N�g
	bool is_on_the_ground_ = false;					//!< �n�ʒ��n�t���O
	int score_ = 0;	
	int anim_counter_ = 0;


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
	void setPosition(Vector3D value);

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

	//----------------------------------------
	//! @brief �n�ʒ��n�t���O�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval bool �n�ʒ��n�t���O
	//----------------------------------------
	bool getIsOnTheGround();

	//----------------------------------------
	//! @brief �n�ʒ��n�t���O�ݒ�֐�
	//! @details
	//! @param value �n�ʒ��n�t���O
	//! @retval void �Ȃ�
	//----------------------------------------
	void setIsOnTheGround(bool value);

	//----------------------------------------
	//! @brief �X�R�A�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval int �X�R�A
	//----------------------------------------
	int getScore();
	
	//----------------------------------------
	//! @brief �A�j���[�V�����J�E���g�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval int �A�j���[�V�����J�E���g
	//----------------------------------------
	int getAnimCount();

	//----------------------------------------
	//! @brief �A�j���[�V�����J�E���g�擾�֐�
	//! @details
	//! @param value �A�j���[�V�����J�E���g
	//! @retval void �Ȃ�
	//----------------------------------------
	void setAnimCount(int value);


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
	//void DebugDisplay() override;

	//----------------------------------------
	//! @brief �X�R�A�ǉ��֐�
	//! @details 
	//! @param value �X�R�A
	//! @retval void �Ȃ�
	//----------------------------------------
	void AddScore(int value);

private:
	//----------------------------------------
	//! @brief ���͊֐�
	//! @details 
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Input();

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

	//----------------------------------------
	//! @brief ���D���͊֐�
	//! @details 
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void InputBalloon();
};



#endif