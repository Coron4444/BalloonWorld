//================================================================================
//!	@file	 RenderTexturePolygon.h
//!	@brief	 �����_�[�e�N�X�`���|���S��Class
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================
#ifndef	_RENDER_TEXTURE_POLYGON_H_
#define _RENDER_TEXTURE_POLYGON_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "../DrawNull.h"
#include <Tool/Vector3D.h>



//****************************************
// �N���X�錾
//****************************************
class PlanePolygon;
class Transform;



//************************************************************														   
//! @brief   �����_�[�e�N�X�`���|���S��Class
//!
//! @details �����_�[�e�N�X�`���̕`��p�|���S��Class
//************************************************************
class RenderTexturePolygon : public DrawNull
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
	//! @param position_x ���WX
	//! @param position_y ���WY
	//! @param scale_x �g�kX
	//! @param scale_y �g�kY
	//! @param color   �F
	//! @retval void �Ȃ�
	//----------------------------------------
	void Update(float position_x, float position_y,
				float scale_x, float scale_y, XColor4 color);
	

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