//================================================================================
//!	@file	 ScoreDraw.h
//!	@brief	 �X�R�A�`��Class
//! @details 
//!	@author  Kai Araki									@date 2018/06/20
//================================================================================
#ifndef	_SCORE_DRAW_H_
#define _SCORE_DRAW_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <string>

#include <GameEngine/Draw/DrawNull.h>
#include <Resource/Texture/TextureManager/TextureManager.h>



//****************************************
// �N���X�錾
//****************************************
class Score;
class NumbersPolygon;
class PlanePolygon;



//************************************************************														   
//! @brief   �X�R�A�`��Class
//!
//! @details �X�R�A�̕`��Class
//************************************************************
class ScoreDraw : public DrawNull
{
//====================
// �萔
//====================
private:
	static const std::string TEXTURE_NAME;	//!< �e�N�X�`����
	static const std::string TEXTURE_NAME2;	//!< �e�N�X�`����
	static const int SCORE_DIGITS_NUM;		//!< �X�R�A����
	static const Vec2 SCORE_POSITION;		//!< �X�R�A���W
	static const Vec2 SCORE_SCALE;			//!< �X�R�A�g�k
	static const XColor4 SCORE_COLOR;		//!< �X�R�A�F


//====================
// �ϐ�
//====================
private:
	Score* score_;						//!< �X�R�A
	NumbersPolygon* numbers_polygon_;	//!< �����Q�|���S��
	PlanePolygon* plane_polygon_;		//!< ���ʃ|���S��
	TextureObject* texture_;			//!< �e�N�X�`���I�u�W�F�N�g
	TextureObject* texture_2;			//!< �e�N�X�`���I�u�W�F�N�g


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
	//! @brief �X�V�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Update() override;

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