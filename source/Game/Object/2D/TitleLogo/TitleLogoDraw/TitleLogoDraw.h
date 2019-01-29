//================================================================================
//
//    �^�C�g�����S�`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/07/03
//
//================================================================================

#ifndef	_TITLE_LOGO_DRAW_H_
#define _TITLE_LOGO_DRAW_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <string>

#include <Component/Draw/DrawNull/DrawNull.h>
#include "../TitleLogo.h"

#include <Texture/TextureManager/TextureManager.h>



/*********************************************************//**
* @brief
* �^�C�g�����S�`��N���X
*
* �^�C�g�����S�̕`��N���X
*************************************************************/
class TitleLogoDraw : public DrawNull
{
//==============================
// �萔
//==============================
private:
	static const std::string TEXTURE_NAME;		//!< �e�N�X�`����
	static const float       SCALE;				//!< �g�k


//==============================
// ��ÓI�����o�֐�
//==============================
private:
	TitleLogo* title_logo_;				//!< �^�C�g�����S
	TextureObject* diffuse_texture_;		//!< �f�B�q���[�Y�e�N�X�`��


//==============================
// ��ÓI�����o�֐�
//==============================
public:
	/**
	* @brief
	* �������֐�
	*/
	void Init() override;

	/**
	* @brief
	* �I���֐�
	*/
	void Uninit() override;

	/**
	* @brief
	* �`��֐�
	* @param
	* object_index : �I�u�W�F�N�g�C���f�b�N�X
	* mesh_index : ���b�V���C���f�b�N�X
	*/
	void Draw(unsigned object_index, unsigned mesh_index) override;

	// �v���p�e�B
	unsigned getMeshNum(unsigned object_index) override;
	MATRIX* getpMatrix(unsigned object_index) override;
	D3DMATERIAL9* getpMaterial(unsigned object_index, unsigned mesh_index) override;
	LPDIRECT3DTEXTURE9 getpDiffuseTexture(unsigned object_index, unsigned mesh_index) override;
};



#endif