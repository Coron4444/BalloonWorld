//================================================================================
//!	@file	 PauseDraw.h
//!	@brief	 �|�[�Y�`��Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/19
//================================================================================
#ifndef	_PAUSE_DRAW_H_
#define _PAUSE_DRAW_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <string>

#include <GameEngine/Draw/DrawNull.h>
#include <Resource/Texture/TextureManager/TextureManager.h>



//****************************************
// �N���X�錾
//****************************************
class PlanePolygon;
class Pause;



//************************************************************														   
//! @brief   �|�[�Y�`��Class
//!
//! @details �|�[�Y�̕`��Class
//************************************************************
class PauseDraw : public DrawNull
{
//====================
// �萔
//====================
private:
	static const unsigned OBJECT_NUM = 5;				//!< �I�u�W�F�N�g��
	static const std::string TEXTURE_NAME[OBJECT_NUM];	//!< �e�N�X�`����
	

//====================
// �ϐ�
//====================
private:
	PlanePolygon* plane_polygon_ = nullptr;				//!< ���ʃ|���S��
	TextureObject* texture_[OBJECT_NUM] = {nullptr};	//!< �e�N�X�`��
	Pause* pause_;										//!< �|�[�Y


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
	unsigned getObjectNum() override;

	//----------------------------------------
	//! @brief ���b�V�����擾�֐�
	//! @details
	//! @param object_index �I�u�W�F�N�g�C���f�b�N�X
	//! @retval unsigned ���b�V����
	//----------------------------------------
	unsigned getMeshNum(unsigned object_index) override;

	//----------------------------------------
	//! @brief ���[���h�s��擾�֐�
	//! @details
	//! @param object_index �I�u�W�F�N�g�C���f�b�N�X
	//! @retval MATRIX* ���[���h�s��
	//----------------------------------------
	MATRIX* getpMatrix(unsigned object_index) override;

	//----------------------------------------
	//! @brief �}�e���A���擾�֐�
	//! @details
	//! @param object_index �I�u�W�F�N�g�C���f�b�N�X
	//! @param mesh_index   ���b�V���C���f�b�N�X
	//! @retval D3DMATERIAL9* �}�e���A��
	//----------------------------------------
	D3DMATERIAL9* getpMaterial(unsigned object_index,
							   unsigned mesh_index) override;

	//----------------------------------------
	//! @brief �f�B�q���[�Y�e�N�X�`���擾�֐�
	//! @details
	//! @param object_index �I�u�W�F�N�g�C���f�b�N�X
	//! @param mesh_index   ���b�V���C���f�b�N�X
	//! @retval LPDIRECT3DTEXTURE9 �f�B�q���[�Y�e�N�X�`��
	//----------------------------------------
	LPDIRECT3DTEXTURE9 getpDiffuseTexture(unsigned object_index,
										  unsigned mesh_index) override;


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
	void Init() override;

	//----------------------------------------
	//! @brief �I���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Uninit() override;

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