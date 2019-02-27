//================================================================================
//!	@file	 BulletPhysicsDebug.h
//!	@brief	 �o���b�g�t�B�W�b�N�X�f�o�b�OClass
//! @details 
//!	@author  Kai Araki									@date 2019/02/07
//================================================================================
#ifndef	_BULLET_PHYSICS_DEBUG_H_
#define _BULLET_PHYSICS_DEBUG_H_



//****************************************
// �C���N���[�h��
//****************************************
#pragma warning(push)
#pragma warning(disable: 4100)
#pragma warning(disable: 4099)
#pragma warning(disable: 4127)
#include <btBulletDynamicsCommon.h>
#include <LinearMath/btIDebugDraw.h>
#pragma warning(pop)



//****************************************
// �N���X�錾
//****************************************
class Camera;
class Transform;



//************************************************************														   
//! @brief   �o���b�g�t�B�W�b�N�X�f�o�b�OClass
//!
//! @details �o���b�g�t�B�W�b�N�X�̃f�o�b�OClass
//************************************************************
class BulletPhysicsDebug : public btIDebugDraw
{
//====================
// �ϐ�
//====================
private:
	int debug_mode_ = 0;					//!< �f�o�b�O���[�h
	RendererDirectX9::VERTEX_3D vertex_[2];	//!< ���_
	LPDIRECT3DDEVICE9 device_ = nullptr;	//!< �f�o�C�X
	Transform transform_;		//!< �ό`


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �f�o�b�O���[�h�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval int �f�o�b�O���[�h
	//----------------------------------------
	int getDebugMode() const override;

	//----------------------------------------
	//! @brief �f�o�b�O���[�h�ݒ�֐�
	//! @details
	//! @param value �f�o�b�O���[�h
	//! @retval void �Ȃ�
	//----------------------------------------
	void setDebugMode(int value) override;


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
	//! @brief ���̕`��֐�
	//! @details
	//! @param from  �J�n�_
	//! @param to    �I�[�_
	//! @param color �F
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void drawLine(const btVector3& from, const btVector3& to,
						  const btVector3& color) override;

	//----------------------------------------
	//! @brief �`��O�ݒ�֐�
	//! @details
	//! @param camera �J����
	//! @retval void �Ȃ�
	//----------------------------------------
	void DrawSettingBefore(Camera* camera);

	//----------------------------------------
	//! @brief �`���ݒ�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void DrawSettingAfter();

	// ���Ή�
	void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB,
						  btScalar distance, int lifeTime, const btVector3& color) override;
	void reportErrorWarning(const char* warningString) override;
	void draw3dText(const btVector3& location, const char* textString) override;
};



#endif