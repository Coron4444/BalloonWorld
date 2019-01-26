//================================================================================
//!	@file	 RenderTexture.h
//!	@brief	 �����_���[�e�N�X�`��Class
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================
#ifndef	_RENDER_TEXTURE_H_
#define _RENDER_TEXTURE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <string>

#include <Component/Draw/DrawNull/DrawNull.h>
#include <Vector3D.h>



//****************************************
// �N���X�錾
//****************************************
class PlanePolygon;
class Transform;



//************************************************************														   
//! @brief   �����_���[�e�N�X�`��Class
//!
//! @details �����_���[�e�N�X�`����Class
//************************************************************
class RenderTexture : public DrawNull
{
//====================
// �ϐ�
//====================
private:
	PlanePolygon* plane_polygon_ = nullptr;			//!< �|���S��
	Transform* transform_ = nullptr;				//!< ���


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �s��擾�֐�
	//! @details
	//! @param object_index �I�u�W�F�N�g�C���f�b�N�X
	//! @retval MATRIX* �s��
	//----------------------------------------
	MATRIX* getpMatrix(unsigned object_index) override;

	//----------------------------------------
	//! @brief �}�e���A���擾�֐�
	//! @details
	//! @param object_index �I�u�W�F�N�g�C���f�b�N�X
	//! @param mesh_index   ���b�V���C���f�b�N�X
	//! @retval D3DMATERIAL9* �}�e���A��
	//----------------------------------------
	D3DMATERIAL9* getpMaterial(unsigned object_index, unsigned mesh_index) override;


//==============================
// ��ÓI�����o�֐�
//==============================
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
	void Uninit() override;

	//----------------------------------------
	//! @brief �X�V�֐�
	//! @details
	//! @param x     X���W
	//! @param y     Y���W
	//! @param color �F
	//! @retval void �Ȃ�
	//----------------------------------------
	void Update(float x, float y, XColor4 color);
	

	//----------------------------------------
	//! @brief �`��֐�
	//! @details
	//! @param object_index �I�u�W�F�N�g�C���f�b�N�X
	//! @param mesh_index   ���b�V���C���f�b�N�X
	//! @retval void �Ȃ�
	//----------------------------------------
	void Draw(unsigned object_index, unsigned mesh_index) override;
};



#endif