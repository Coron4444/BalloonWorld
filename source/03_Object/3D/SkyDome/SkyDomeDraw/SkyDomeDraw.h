//================================================================================
//
//    �X�J�C�h�[���`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/05/15
//
//================================================================================

#ifndef	_SKY_DOME_DRAW_H_
#define _SKY_DOME_DRAW_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <string>

#include <Component/Draw/DrawNull/DrawNull.h>
#include "../SkyDome.h"



//****************************************
// �N���X�錾
//****************************************
class ModelXObject;



/*********************************************************//**
* @brief
* �v���C���[�`��N���X
*
* �v���C���[�̕`��N���X
*************************************************************/
class SkyDomeDraw : public DrawNull
{
//==============================
// �萔
//==============================
private:
	// �萔
	static const std::string MODEL_NAME;	//!< ���f����


//==============================
// ��ÓI�����o�֐�
//==============================
private:
	ModelXObject* sky_dome_model_;		//!< ���f���I�u�W�F�N�g


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