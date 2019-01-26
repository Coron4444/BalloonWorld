//================================================================================
//!	@file	 CoinDraw.h
//!	@brief	 �R�C���`��Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================
#ifndef	_COIN_DRAW_H_
#define _COIN_DRAW_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <string>

#include "../Coin.h"
#include <Component/Draw/DrawNull/DrawNull.h>



//****************************************
// �N���X�錾
//****************************************
class TextureObject;



//************************************************************														   
//! @brief   �R�C�����S�`��Class
//!
//! @details �R�C�����S�̕`��Class
//************************************************************
class CoinDraw : public DrawNull
{
//====================
// �萔
//====================
private:
	static const std::string diffuse_TEXTURE;	//!< �f�B�q���[�Y�e�N�X�`����
	

//====================
// �ϐ�
//====================
private:
	Coin* coin_;						//!< �R�C��
	TextureObject* diffuse_texture_;		//!< �f�B�q���[�Y�e�N�X�`��


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
	//! @brief �X�V�֐�
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Update() override;

	//----------------------------------------
	//! @brief �`��֐�
	//! @param[in] object_index �I�u�W�F�N�g�C���f�b�N�X
	//! @param[in] mesh_index   ���b�V���C���f�b�N�X
	//! @retval void �Ȃ�
	//----------------------------------------
	void Draw(unsigned object_index, unsigned mesh_index) override;

	//----------------------------------------
	//! @brief �`��O�ݒ�֐�
	//! @param[in] camera       �J����
	//! @param[in] object_index �I�u�W�F�N�g�C���f�b�N�X
	//! @retval void �Ȃ�
	//----------------------------------------
	void SettingBeforeDrawing(Camera* camera, unsigned object_index) override;


	// �v���p�e�B
	unsigned getMeshNum(unsigned object_index) override;
	MATRIX* getpMatrix(unsigned object_index) override;
	D3DMATERIAL9* getpMaterial(unsigned object_index, unsigned mesh_index) override;
	LPDIRECT3DTEXTURE9 getpDiffuseTexture(unsigned object_index, unsigned mesh_index) override;
};



#endif