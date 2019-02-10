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
class Balloon;
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
	static const std::string BALLOON_MODEL_NAME;		//!< ���D���f����
	static const std::string BALLOON_LINE_MODEL_NAME;	//!< ���D�̐����f����


//====================
// �ϐ�
//====================
private:
	Balloon* balloon_;	//!< ���D
	ModelXObject* balloon_object_;			//!< ���D�I�u�W�F�N�g
	ModelXObject* balloon_line_object_;		//!< ���D�̐��I�u�W�F�N�g
	XColor4 color_;							//!< �F


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