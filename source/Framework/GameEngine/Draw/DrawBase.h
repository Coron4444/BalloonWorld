//================================================================================
//!	@file	 DrawBase.h
//!	@brief	 �`��BaseClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================
#ifndef	_DRAW_BASE_H_
#define _DRAW_BASE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "../ComponentBase.h"
#include "DrawManager/DrawOrderList.h"
#include "DrawManager/DrawCommonData.h"

#include <Tool/Vector3D.h>



//************************************************************														   
//! @brief   �`��BaseClass
//!
//! @details �`���BaseClass
//************************************************************
class DrawBase : public ComponentBase
{
//====================
// �ϐ�
//====================
private:
	DrawOrderList order_list_;				//!< �`�撍�����X�g
	DrawCommonData* common_data_ = nullptr;	//!< �`�拤�ʃf�[�^


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
	virtual unsigned getObjectNum() = 0;

	//----------------------------------------
	//! @brief ���b�V�����擾�֐�
	//! @details
	//! @param object_index �I�u�W�F�N�g�C���f�b�N�X
	//! @retval unsigned ���b�V����
	//----------------------------------------
	virtual unsigned getMeshNum(unsigned object_index) = 0;

	//----------------------------------------
	//! @brief �{�[�����擾�֐�
	//! @details
	//! @param object_index �I�u�W�F�N�g�C���f�b�N�X
	//! @param mesh_index   ���b�V���C���f�b�N�X
	//! @retval unsigned �{�[����
	//----------------------------------------
	virtual unsigned getBoneNum(unsigned object_index,
								unsigned mesh_index) = 0;

	//----------------------------------------
	//! @brief ���[���h�s��擾�֐�
	//! @details
	//! @param object_index �I�u�W�F�N�g�C���f�b�N�X
	//! @retval MATRIX* ���[���h�s��
	//----------------------------------------
	virtual MATRIX* getpMatrix(unsigned object_index) = 0;

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
								   unsigned bone_index) = 0;

	//----------------------------------------
	//! @brief �}�e���A���擾�֐�
	//! @details
	//! @param object_index �I�u�W�F�N�g�C���f�b�N�X
	//! @param mesh_index   ���b�V���C���f�b�N�X
	//! @retval D3DMATERIAL9* �}�e���A��
	//----------------------------------------
	virtual D3DMATERIAL9* getpMaterial(unsigned object_index,
									   unsigned mesh_index) = 0;

	//----------------------------------------
	//! @brief �f�B�q���[�Y�e�N�X�`���擾�֐�
	//! @details
	//! @param object_index �I�u�W�F�N�g�C���f�b�N�X
	//! @param mesh_index   ���b�V���C���f�b�N�X
	//! @retval LPDIRECT3DTEXTURE9 �f�B�q���[�Y�e�N�X�`��
	//----------------------------------------
	virtual LPDIRECT3DTEXTURE9 getpDiffuseTexture(unsigned object_index,
												  unsigned mesh_index) = 0;

	 //----------------------------------------
	 //! @brief �@���e�N�X�`���擾�֐�
	 //! @details
	 //! @param object_index �I�u�W�F�N�g�C���f�b�N�X
	 //! @param mesh_index   ���b�V���C���f�b�N�X
	 //! @retval RendererInterface* �@���e�N�X�`��
	 //----------------------------------------
	virtual LPDIRECT3DTEXTURE9 getpNormalTexture(unsigned object_index,
												 unsigned mesh_index) = 0;

	//----------------------------------------
	//! @brief �`�撍�����X�g�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval DrawOrderList* �`�撍�����X�g
	//----------------------------------------
	DrawOrderList* getpDrawOrderList();

	//----------------------------------------
	//! @brief �`�拤�ʃf�[�^�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval DrawCommonData* �`�拤�ʃf�[�^
	//----------------------------------------
	DrawCommonData* getpDrawCommonData();

	//----------------------------------------
	//! @brief �`�拤�ʃf�[�^�ݒ�֐�
	//! @details
	//! @param value �`�拤�ʃf�[�^
	//! @retval void �Ȃ�
	//----------------------------------------
	void setDrawCommonData(DrawCommonData* value);


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief ���z�f�X�g���N�^
	//! @details
	//! @param void �Ȃ�
	//----------------------------------------
	virtual ~DrawBase() = 0;

	//----------------------------------------
	//! @brief �`��֐�
	//! @details
	//! @param object_index �I�u�W�F�N�g�C���f�b�N�X
	//! @param mesh_index   ���b�V���C���f�b�N�X
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void Draw(unsigned object_index, unsigned mesh_index) = 0;

	//----------------------------------------
	//! @brief �I�u�W�F�N�g�O�ݒ�֐�
	//! @details
	//! @param object_index �I�u�W�F�N�g�C���f�b�N�X
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void ObjectSettingBefore(unsigned object_index) = 0;

	//----------------------------------------
	//! @brief �I�u�W�F�N�g��ݒ�֐�
	//! @details
	//! @param object_index �I�u�W�F�N�g�C���f�b�N�X
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void ObjectSettingAfter(unsigned object_index) = 0;
};



#endif