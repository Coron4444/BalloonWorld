//================================================================================
//
//    �Q�[���I�u�W�F�N�g���N���X
//    Author : Araki Kai                                �쐬�� : 2018/03/22
//
//================================================================================

#ifndef	_GAME_OBJECT_BASE_H_
#define _GAME_OBJECT_BASE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <SafeRelease/SafeRelease.h>
#include <Transform\Transform.h>
#include <Physics\Physics.h>

#include "../Component/Update/UpdateBase/UpdateBase.h"
#include "../Component/Draw/DrawBase/DrawBase.h"
#include "../Component/Collision/CollisionBase/CollisionBase.h"



/*********************************************************//**
* @brief
* �Q�[���I�u�W�F�N�g���N���X
*
* �Q�[���I�u�W�F�N�g�̊��N���X
*************************************************************/
class GameObjectBase
{
//==============================
// ��ÓI�����o�ϐ�
//==============================
private:
	Transform transform_;		//!< �g�����X�t�H�[��
	Physics*  physics_;			//!< ����

	bool is_registration_;		//!< �o�^�t���O

	UpdateBase*    update_;		//!< �X�V�R���|�[�l���g
	DrawBase*      draw_;		//!< �`��R���|�[�l���g
	CollisionBase* collision_;	//!< �Փ˃R���|�[�l���g



//==============================
// ��ÓI�����o�֐�
//==============================
public:
	/**
	* @brief
	* �R���X�g���N�^
	* @param
	* is_registration : �o�^�t���O
	*/
	GameObjectBase(bool is_registration = true);

	/**
	* @brief
	* ���z�f�X�g���N�^
	*/
	virtual ~GameObjectBase();

	/**
	* @brief
	* �I���֐�
	*/
	virtual void Uninit();

	/**
	* @brief
	* ���Z�b�g�֐�
	*/
	virtual void Reset() = 0;

	/**
	* @brief
	* ���̐����֐�
	*/
	void CreatePhysics();

	// �v���p�e�B
	Transform* GetTransform() { return &transform_; }
	Physics* GetPhysics() { return physics_; }
	void SetAllComponent(UpdateBase* value0, DrawBase* value1, CollisionBase* value2)
	{
		SetUpdate(value0);
		SetDraw(value1);
		SetCollision(value2);
	}
	UpdateBase* GetUpdate() { return update_; }
	void SetUpdate(UpdateBase* value) { update_ = value; }
	DrawBase* GetDraw() { return draw_; }
	void SetDraw(DrawBase* value) { draw_ = value; }
	CollisionBase* GetCollision() { return collision_; }
	void SetCollision(CollisionBase* value) { collision_ = value; }
	

protected:
	/**
	* @brief
	* �������֐�
	* @param
	* update : �X�V���N���X
	* draw : �`����N���X
	* collision : �Փˊ��N���X
	*/
	void Init(UpdateBase* update, DrawBase* draw, CollisionBase* collision);
	
	

private:
	/**
	* @brief
	* �R���|�[�l���g�������֐�
	*/
	void InitComponent();

	/**
	* @brief
	* �R���|�[�l���g�I���֐�
	*/
	void UninitComponent();
};



#endif
