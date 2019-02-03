//================================================================================
//!	@file	 TutorialLogoDraw.h
//!	@brief	 �`���[�g���A�����S�`��Class
//! @details 
//!	@author  Kai Araki									@date 2018/09/02
//================================================================================
#ifndef	_TUTORIAL_LOGO_DRAW_H_
#define _TUTORIAL_LOGO_DRAW_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <string>

#include <GameEngine/Draw/DrawNull.h>
#include <Resource/Texture/TextureManager/TextureManager.h>



//****************************************
// �N���X�錾
//****************************************
class TutorialLogo;
class PlanePolygon;



//************************************************************														   
//! @brief   �N���A���S�`��Class
//!
//! @details �N���A���S�̕`��Class
//************************************************************
class TutorialLogoDraw : public DrawNull
{
//====================
// �萔
//====================
private:
	static const unsigned TEXTURE_NUM = 2;				//!< �e�N�X�`����
	static const std::string TEXTURE_NAME[TEXTURE_NUM];	//!< �e�N�X�`����
	static const float SCALE;							//!< �g�k


//====================
// �ϐ�
//====================
private:
	TutorialLogo* tutorial_logo_ = nullptr;						//!< �`���[�g���A��
	TextureObject* diffuse_texture_[TEXTURE_NUM] = {nullptr};	//!< �f�B�q���[�Y�e�N�X�`��
	PlanePolygon* plane_polygon_ = nullptr;						//!< ���ʃ|���S��


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