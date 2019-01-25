//================================================================================
//
//    ���s���S�`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/07/24
//
//================================================================================

#ifndef	_FAILURE_LOGO_DRAW_H_
#define _FAILURE_LOGO_DRAW_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <string>

#include <Component/Draw/DrawNull/DrawNull.h>
#include "../FailureLogo.h"

#include <Texture/TextureManager/TextureManager.h>



/*********************************************************//**
* @brief
* ���s���S�`��N���X
*
* ���s���S�̕`��N���X
*************************************************************/
class FailureLogoDraw : public DrawNull
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
	FailureLogo* failure_logo_;			//!< ���s���S
	TextureObject* diffuse_texture_;	//!< �f�B�q���[�Y�e�N�X�`��


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