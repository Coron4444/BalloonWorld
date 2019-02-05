//================================================================================
//!	@file	 BalloonDraw.h
//!	@brief	 ���D�`��Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/05
//================================================================================
#ifndef	_BALLOON_DRAW_H_
#define _BALLOON_DRAW_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <string>

#include <GameEngine/Draw/DrawNull.h>



//****************************************
// �N���X�錾
//****************************************
class MdBinObject;
class ModelXObject;



//************************************************************														   
//! @brief   ���D�`��Class
//!
//! @details ���D�̕`��Class
//************************************************************
class BalloonDraw : public DrawNull
{
//====================
// �萔
//====================
private:
	static const std::string MODEL_NAME;				//!< ���f����


//====================
// �ϐ�
//====================
private:
	ModelXObject* object_;		//!< �I�u�W�F�N�g


//====================
// �v���p�e�B
//====================
public:
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
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init() override;

	//----------------------------------------
	//! @brief �I���֐�
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Uninit() override;

	//----------------------------------------
	//! @brief �`��֐�
	//! @param object_index �I�u�W�F�N�g�C���f�b�N�X
	//! @param mesh_index   ���b�V���C���f�b�N�X
	//! @retval void �Ȃ�
	//----------------------------------------
	void Draw(unsigned object_index, unsigned mesh_index) override;
};



#endif