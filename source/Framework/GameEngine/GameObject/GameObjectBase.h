//================================================================================
//!	@file	 GameObjectBase.h
//!	@brief	 �Q�[���I�u�W�F�N�gBaseClass
//! @details 
//!	@author  Kai Araki									@date 2018/03/22
//================================================================================
#ifndef	_GAME_OBJECT_BASE_H_
#define _GAME_OBJECT_BASE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "../Update/UpdateBase.h"
#include "../Draw/DrawBase.h"
#include "../Collision/CollisionBase.h"

#include <Tool/Transform.h>
#include <Tool/Physics.h>



//************************************************************														   
//! @brief   �Q�[���I�u�W�F�N�gBaseClass
//!
//! @details �Q�[���I�u�W�F�N�g��BaseClass
//************************************************************
class GameObjectBase
{
//====================
// �ϐ�
//====================
private:
	Transform transform_;		//!< �ό`
	Physics*  physics_;			//!< ����

	bool is_registration_;		//!< �o�^�t���O

	UpdateBase*    update_;		//!< �X�V���N���X
	DrawBase*      draw_;		//!< �`����N���X
	CollisionBase* collision_;	//!< �Փˊ��N���X


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �ό`�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Transform* �ό`
	//----------------------------------------
	Transform* getpTransform();

	//----------------------------------------
	//! @brief �����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Transform* �ό`
	//----------------------------------------
	Physics* getpPhysics();

	//----------------------------------------
	//! @brief �S���N���X�ݒ�֐�
	//! @details
	//! @param update    �X�V���N���X
	//! @param draw      �`����N���X
	//! @param collision �Փˊ��N���X
	//! @retval void �Ȃ�
	//----------------------------------------
	void setAllComponent(UpdateBase* update, DrawBase* draw, CollisionBase* collision);

	//----------------------------------------
	//! @brief �X�V���N���X�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval UpdateBase* �X�V���N���X
	//----------------------------------------
	UpdateBase* getpUpdate();

	//----------------------------------------
	//! @brief �X�V���N���X�ݒ�֐�
	//! @details
	//! @param value �X�V���N���X
	//! @retval void �Ȃ�
	//----------------------------------------
	void setUpdate(UpdateBase* value);

	//----------------------------------------
	//! @brief �`����N���X�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval DrawBase* �`����N���X
	//----------------------------------------
	DrawBase* getpDraw();

	//----------------------------------------
	//! @brief �`����N���X�ݒ�֐�
	//! @details
	//! @param value �`����N���X
	//! @retval void �Ȃ�
	//----------------------------------------
	void setDraw(DrawBase* value);

	//----------------------------------------
	//! @brief �Փˊ��N���X�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval CollisionBase* �Փˊ��N���X
	//----------------------------------------
	CollisionBase* getpCollision();

	//----------------------------------------
	//! @brief �Փˊ��N���X�ݒ�֐�
	//! @details
	//! @param value �Փˊ��N���X
	//! @retval void �Ȃ�
	//----------------------------------------
	void setCollision(CollisionBase* value);


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �R���X�g���N�^
	//! @details
	//! @param is_registration �o�^�t���O
	//----------------------------------------
	GameObjectBase(bool is_registration = true);

	//----------------------------------------
	//! @brief �f�X�g���N�^
	//! @details
	//! @param void �Ȃ�
	//----------------------------------------
	virtual ~GameObjectBase();

	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param update    �X�V���N���X
	//! @param draw      �`����N���X
	//! @param collision �Փˊ��N���X
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init(UpdateBase* update, DrawBase* draw, CollisionBase* collision);

	//----------------------------------------
	//! @brief �I���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void Uninit();

	//----------------------------------------
	//! @brief ���Z�b�g�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void Reset();

	//----------------------------------------
	//! @brief ���������֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreatePhysics();
:

private:
	//----------------------------------------
	//! @brief �R���|�[�l���g�������֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void InitComponent();

	//----------------------------------------
	//! @brief �R���|�[�l���g�I���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void UninitComponent();

	//----------------------------------------
	//! @brief �R���|�[�l���g���Z�b�g�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void ResetComponent();

	//----------------------------------------
	//! @brief �`�拤�ʃf�[�^�ǉ��֐�
	//! @details
	//! @param draw �`����N���X
	//! @retval void �Ȃ�
	//----------------------------------------
	void AddDrawCommonData(DrawBase* draw);
};



#endif
