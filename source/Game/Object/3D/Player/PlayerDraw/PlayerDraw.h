//================================================================================
//
//    �v���C���[�`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/03/27
//
//================================================================================

#ifndef	_PLAYER_DRAW_H_
#define _PLAYER_DRAW_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <string>

#include <Component/Draw/DrawNull/DrawNull.h>
#include "../Player.h"



//****************************************
// �N���X�錾
//****************************************
class ModelXObject;
class TextureObject;
class MdBinObject;



/*********************************************************//**
* @brief
* �v���C���[�`��N���X
*
* �v���C���[�̕`��N���X
*************************************************************/
class PlayerDraw : public DrawNull
{
//==============================
// �萔
//==============================
private:
	// �萔
	static const std::string MODEL_NAME;				//!< ���f����
	static const std::string TEXTURE_PATH;				//!< ���f���t�H���_�̃e�N�X�`���p�X
	static const std::string NORMAL_TEXTURE_MODEL;		//!< �@���e�N�X�`��(���f��)
	static const std::string NORMAL_TEXTURE_SWORD;		//!< �@���e�N�X�`��(��)


//==============================
// ��ÓI�����o�֐�
//==============================
private:
	ModelXObject* player_model_;			//!< ���f���I�u�W�F�N�g
	TextureObject* normal_texture_[2];		//!< �e�N�X�`���I�u�W�F�N�g
	MdBinObject* test_object_;				//!< �e�X�g�p�I�u�W�F�N�g

	int count_ = 0;
	int frame_ = 0;

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

	void Update() override;

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
	unsigned getBoneNum(unsigned object_index, unsigned mesh_index) override;
	MATRIX* getpMatrix(unsigned object_index) override;
	MATRIX* getpBoneMatrix(unsigned object_index, unsigned mesh_index,
						   unsigned bone_index) override;
	D3DMATERIAL9* getpMaterial(unsigned object_index, unsigned mesh_index) override;
	LPDIRECT3DTEXTURE9 getpDiffuseTexture(unsigned object_index, unsigned mesh_index) override;
	LPDIRECT3DTEXTURE9 getpNormalTexture(unsigned object_index, unsigned mesh_index) override;
};



#endif