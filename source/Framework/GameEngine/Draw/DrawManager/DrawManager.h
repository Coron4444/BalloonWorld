//================================================================================
//!	@file	 DrawManager.h
//!	@brief	 �`��}�l�[�W���[Class
//! @details 
//!	@author  Kai Araki									@date 2019/01/19
//================================================================================
#ifndef	_DRAW_MANAGER_H_
#define _DRAW_MANAGER_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "RenderTarget/BackBuffer/BackBuffer.h"

#include <LimitedPointerArray\LimitedPointerArray.h>



//****************************************
// �N���X�錾
//****************************************
class DrawBase;
class GameObjectBase;
class ShaderManager;



//************************************************************														   
//! @brief   �`��}�l�[�W���[lass
//!
//! @details �o�^����Ă���`����N���X���Ǘ�����Class
//************************************************************
class DrawManager
{
//====================
// �萔
//====================
public:
	static const unsigned DRAW_ARRAY_NUM = 10000;	//!< �z��


//====================
// �ϐ�
//====================
private:
	LimitedPointerArray<DrawBase*, DRAW_ARRAY_NUM> all_draw_;		//!< �S�`��z��
	LimitedPointerArray<DrawBase*, DRAW_ARRAY_NUM> await_add_;		//!< �ǉ��҂��z��
	LimitedPointerArray<DrawBase*, DRAW_ARRAY_NUM> await_release_;	//!< ����҂��z��

	ShaderManager* shader_manager_ = nullptr;	//!< �V�F�[�_�[�}�l�[�W��
	BackBuffer* back_buffer_ = nullptr;			//!< �o�b�N�o�b�t�@

	Vec3 directional_light_vector_ = {0.5f, -1.0f, 0.8f};	//!< �f�B���N�V���i�����C�g����

//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �o�b�N�o�b�t�@�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval BackBuffer* �o�b�N�o�b�t�@
	//----------------------------------------
	BackBuffer* getpBackBuffer();

	const Vec3* GetDirectionalLightVector() { return &directional_light_vector_; }

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
	//! @brief �I���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Uninit();

	//----------------------------------------
	//! @brief �V�[���ύX���̏I���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void UninitWhenChangeScene();

	//----------------------------------------
	//! @brief �X�V�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Update();

	//----------------------------------------
	//! @brief �`��֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Draw();

	//----------------------------------------
	//! @brief �`����N���X�̒ǉ��֐�
	//! @details
	//! @param *draw �`����N���X
	//! @retval void �Ȃ�
	//----------------------------------------
	void AddDrawBaseToArray(DrawBase* draw);

	//----------------------------------------
	//! @brief �`����N���X�̏㏑���֐�
	//! @details
	//! @param *game_object �Q�[���I�u�W�F�N�g
	//! @param *new_draw    �V�K�`����N���X
	//! @retval void �Ȃ�
	//----------------------------------------
	void OverwriteArrayDrawBase(GameObjectBase* game_object,
								DrawBase* new_draw);

	//----------------------------------------
	//! @brief �`����N���X�̉���֐�
	//! @details
	//! @param *draw �`����N���X
	//! @retval void �Ȃ�
	//----------------------------------------
	void ReleaseDrawBaseFromArray(DrawBase* draw);
	
private:
	//----------------------------------------
	//! @brief �ǉ��҂��z��̒��g��ǉ��֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void AddContentsOfAwaitAddArray();

	//----------------------------------------
	//! @brief ����҂��z��̒��g������֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void ReleaseContentsOfAwaitReleaseArray();

	//----------------------------------------
	//! @brief �S�`����N���X�X�V�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void UpdateAllDrawBase();

	//----------------------------------------
	//! @brief �S�����_�[�^�[�Q�b�g�X�V�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void UpdateAllRenderTarget();

	//----------------------------------------
	//! @brief �S�����_�[�^�[�Q�b�g���Z�b�g�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void ResetAllRenderTarget();

	//----------------------------------------
	//! @brief �`����N���X�U�蕪���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void DistributeDrawBase();
};



#endif
