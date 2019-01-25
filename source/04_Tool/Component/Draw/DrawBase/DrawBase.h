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
#include "../../ComponentBase/ComponentBase.h"
#include "DrawOrderList/DrawOrderList.h"
#include <ComponentManager/DrawManager/Camera/Camera.h>

#include <Vector3D.h>



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
	DrawOrderList draw_order_list_;							//!< �`�撍�����X�g
	Camera::Type save_camera_type_ = Camera::Type::NONE;	//!< �J�����^�C�v�ۑ��p


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
	//! @brief �`��O�ݒ�֐�
	//! @details
	//! @param *camera      �J����
	//! @param object_index �I�u�W�F�N�g�C���f�b�N�X
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void SettingBeforeDrawing(Camera* camera, unsigned object_index) = 0;

	//----------------------------------------
	//! @brief �`���ݒ�֐�
	//! @details
	//! @param *camera      �J����
	//! @param object_index �I�u�W�F�N�g�C���f�b�N�X
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void SettingAfterDrawing(Camera* camera, unsigned object_index) = 0;

	//----------------------------------------
	//! @brief ����J�����^�C�v�ύX�֐�
	//! @details
	//! @param *camera �J����
	//! @param type �@ �J�����^�C�v
	//! @retval void �Ȃ�
	//----------------------------------------
	void LimitedChangeCameraType(Camera* camera, Camera::Type type);

	//----------------------------------------
	//! @brief �J�����^�C�v�����֐�
	//! @details
	//! @param *camera �J����
	//! @retval void �Ȃ�
	//----------------------------------------
	void RevivalCameraType(Camera* camera);
};



#endif