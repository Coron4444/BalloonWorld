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
#ifdef _DEBUG
#include <Tool/Debug/ImGUI/imgui.h>
#include <Tool/Debug/ImGUI/imgui_impl_dx9.h>
#endif

#include <Tool/Transform.h>
#include <Tool/Physics.h>



//****************************************
// �N���X�錾
//****************************************
class UpdateBase;
class DrawBase;
class CollisionBase;



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
	bool is_input_ = true;		//!< ���̓t���O
	bool is_update_ = true;		//!< �X�V�t���O

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
	//! @brief ���̓t���O�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval bool ���̓t���O
	//----------------------------------------
	bool getIsInput();

	//----------------------------------------
	//! @brief ���̓t���O�擾�֐�
	//! @details
	//! @param value ���̓t���O
	//! @retval void �Ȃ�
	//----------------------------------------
	void setIsInput(bool value);

	//----------------------------------------
	//! @brief �X�V�t���O�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval bool �X�V�t���O
	//----------------------------------------
	bool getIsUpdate();

	//----------------------------------------
	//! @brief �X�V�t���O�擾�֐�
	//! @details
	//! @param value �X�V�t���O
	//! @retval void �Ȃ�
	//----------------------------------------
	void setIsUpdate(bool value);

	//----------------------------------------
	//! @brief �S���N���X�ݒ�֐�
	//! @details
	//! @param draw      �`����N���X
	//! @param collision �Փˊ��N���X
	//! @retval void �Ȃ�
	//----------------------------------------
	void setAllComponent(DrawBase* draw, CollisionBase* collision);

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
	//! @param draw      �`����N���X
	//! @param collision �Փˊ��N���X
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init(DrawBase* draw, CollisionBase* collision);

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
	//! @brief ��X�V�֐�
	//! @details 
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void LateUpdate() = 0;

	//----------------------------------------
	//! @brief ���Z�b�g�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void Reset() = 0;

	//----------------------------------------
	//! @brief �f�o�b�O�\���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void DebugDisplay() = 0;

	//----------------------------------------
	//! @brief ���������֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreatePhysics();

	
protected:
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

private:
	//----------------------------------------
	//! @brief �R���|�[�l���g�������֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void InitComponent();

	//----------------------------------------
	//! @brief �`�拤�ʃf�[�^�ǉ��֐�
	//! @details
	//! @param draw �`����N���X
	//! @retval void �Ȃ�
	//----------------------------------------
	void AddDrawCommonData(DrawBase* draw);
};



#endif
