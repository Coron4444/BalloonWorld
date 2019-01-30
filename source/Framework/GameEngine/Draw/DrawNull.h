//================================================================================
//!	@file	 DrawNull.h
//!	@brief	 �󔒕`��Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================
#ifndef	_DRAW_NULL_H_
#define _DRAW_NULL_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "DrawBase.h"



//************************************************************														   
//! @brief   �󔒕`��Class
//!
//! @details �`��̋�Class
//************************************************************
class DrawNull : public DrawBase
{
//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �I�u�W�F�N�g���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval unsigned �I�u�W�F�N�g��
	//----------------------------------------
	virtual unsigned getObjectNum() override;

	//----------------------------------------
	//! @brief ���b�V�����擾�֐�
	//! @details
	//! @param object_index �I�u�W�F�N�g�C���f�b�N�X
	//! @retval unsigned ���b�V����
	//----------------------------------------
	virtual unsigned getMeshNum(unsigned object_index) override;

	//----------------------------------------
	//! @brief �{�[�����擾�֐�
	//! @details
	//! @param object_index �I�u�W�F�N�g�C���f�b�N�X
	//! @param mesh_index   ���b�V���C���f�b�N�X
	//! @retval unsigned �{�[����
	//----------------------------------------
	virtual unsigned getBoneNum(unsigned object_index,
								unsigned mesh_index) override;

	//----------------------------------------
	//! @brief ���[���h�s��擾�֐�
	//! @details
	//! @param object_index �I�u�W�F�N�g�C���f�b�N�X
	//! @retval MATRIX* ���[���h�s��
	//----------------------------------------
	virtual MATRIX* getpMatrix(unsigned object_index) override;

	//----------------------------------------
	//! @brief �{�[���s��擾�֐�
	//! @details
	//! @param object_index �I�u�W�F�N�g�C���f�b�N�X
	//! @param mesh_index   ���b�V���C���f�b�N�X
	//! @param bone_index   �{�[���C���f�b�N�X
	//! @retval MATRIX* �{�[���s��
	//----------------------------------------
	virtual MATRIX* getpBoneMatrix(unsigned object_index,
								   unsigned mesh_index,
								   unsigned bone_index) override;

	//----------------------------------------
	//! @brief �}�e���A���擾�֐�
	//! @details
	//! @param object_index �I�u�W�F�N�g�C���f�b�N�X
	//! @param mesh_index   ���b�V���C���f�b�N�X
	//! @retval D3DMATERIAL9* �}�e���A��
	//----------------------------------------
	virtual D3DMATERIAL9* getpMaterial(unsigned object_index,
									   unsigned mesh_index) override;

	//----------------------------------------
	//! @brief �f�B�q���[�Y�e�N�X�`���擾�֐�
	//! @details
	//! @param object_index �I�u�W�F�N�g�C���f�b�N�X
	//! @param mesh_index   ���b�V���C���f�b�N�X
	//! @retval LPDIRECT3DTEXTURE9 �f�B�q���[�Y�e�N�X�`��
	//----------------------------------------
	virtual LPDIRECT3DTEXTURE9 getpDiffuseTexture(unsigned object_index,
												  unsigned mesh_index) override;

	 //----------------------------------------
	 //! @brief �@���e�N�X�`���擾�֐�
	 //! @details
	 //! @param object_index �I�u�W�F�N�g�C���f�b�N�X
	 //! @param mesh_index   ���b�V���C���f�b�N�X
	 //! @retval RendererInterface* �@���e�N�X�`��
	 //----------------------------------------
	virtual LPDIRECT3DTEXTURE9 getpNormalTexture(unsigned object_index,
												 unsigned mesh_index) override;


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief ���z�f�X�g���N�^
	//! @details
	//! @param void �Ȃ�
	//----------------------------------------
	virtual ~DrawNull();

	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void Init() override;

	//----------------------------------------
	//! @brief �I���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void Uninit() override;

	//----------------------------------------
	//! @brief �X�V�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void Update() override;

	//----------------------------------------
	//! @brief ���Z�b�g�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void Reset() override;

	//----------------------------------------
	//! @brief �f�o�b�O�\���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void DebugDisplay() override;

	//----------------------------------------
	//! @brief �`��֐�
	//! @details
	//! @param object_index �I�u�W�F�N�g�C���f�b�N�X
	//! @param mesh_index   ���b�V���C���f�b�N�X
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void Draw(unsigned object_index, unsigned mesh_index) override;

	//----------------------------------------
	//! @brief �I�u�W�F�N�g�O�ݒ�֐�
	//! @details
	//! @param object_index �I�u�W�F�N�g�C���f�b�N�X
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void ObjectSettingBefore(unsigned object_index) override;

	//----------------------------------------
	//! @brief �I�u�W�F�N�g��ݒ�֐�
	//! @details
	//! @param object_index �I�u�W�F�N�g�C���f�b�N�X
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void ObjectSettingAfter(unsigned object_index) override;
};



#endif