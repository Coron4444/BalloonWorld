//================================================================================
//!	@file	 PlayerDraw.h
//!	@brief	 �v���C���[�`��Class
//! @details 
//!	@author  Kai Araki									@date 2018/03/27
//================================================================================
#ifndef	_PLAYER_DRAW_H_
#define _PLAYER_DRAW_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <string>

#include <GameEngine/Draw/DrawNull.h>



//****************************************
// �N���X�錾
//****************************************
class ModelXObject;
class MdBinObject;
class TextureObject;
class Player;


//************************************************************														   
//! @brief   �v���C���[�`��Class
//!
//! @details �v���C���[�̕`��Class
//************************************************************
class PlayerDraw : public DrawNull
{
//====================
// �萔
//====================
private:
	static const std::string MODEL_NAME;				//!< ���f����
	static const std::string TEXTURE_PATH;				//!< ���f���t�H���_�̃e�N�X�`���p�X
	static const std::string NORMAL_TEXTURE_MODEL;		//!< �@���e�N�X�`��(���f��)
	static const std::string NORMAL_TEXTURE_SWORD;		//!< �@���e�N�X�`��(��)


//====================
// �ϐ�
//====================
private:
	ModelXObject* player_model_ = nullptr;			//!< ���f���I�u�W�F�N�g
	TextureObject* normal_texture_[2];				//!< �e�N�X�`���I�u�W�F�N�g
	MdBinObject* test_object_ = nullptr;			//!< �e�X�g�p�I�u�W�F�N�g
	int pattern_num_ = 0;
	Player* player_ = nullptr;

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
	//! @brief �{�[�����擾�֐�
	//! @details
	//! @param object_index �I�u�W�F�N�g�C���f�b�N�X
	//! @param mesh_index   ���b�V���C���f�b�N�X
	//! @retval unsigned �{�[����
	//----------------------------------------
	unsigned getBoneNum(unsigned object_index,
								unsigned mesh_index) override;

	//----------------------------------------
	//! @brief ���[���h�s��擾�֐�
	//! @details
	//! @param object_index �I�u�W�F�N�g�C���f�b�N�X
	//! @retval MATRIX* ���[���h�s��
	//----------------------------------------
	MATRIX* getpMatrix(unsigned object_index) override;

	//----------------------------------------
	//! @brief �{�[���s��擾�֐�
	//! @details
	//! @param object_index �I�u�W�F�N�g�C���f�b�N�X
	//! @param mesh_index   ���b�V���C���f�b�N�X
	//! @param bone_index   �{�[���C���f�b�N�X
	//! @retval MATRIX* �{�[���s��
	//----------------------------------------
	MATRIX* getpBoneMatrix(unsigned object_index,
								   unsigned mesh_index,
								   unsigned bone_index) override;

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

	 //----------------------------------------
	 //! @brief �@���e�N�X�`���擾�֐�
	 //! @details
	 //! @param object_index �I�u�W�F�N�g�C���f�b�N�X
	 //! @param mesh_index   ���b�V���C���f�b�N�X
	 //! @retval RendererInterface* �@���e�N�X�`��
	 //----------------------------------------
	LPDIRECT3DTEXTURE9 getpNormalTexture(unsigned object_index,
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
	//! @brief �X�V�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Update() override;

	//----------------------------------------
	//! @brief �`��֐�
	//! @param object_index �I�u�W�F�N�g�C���f�b�N�X
	//! @param mesh_index   ���b�V���C���f�b�N�X
	//! @retval void �Ȃ�
	//----------------------------------------
	void Draw(unsigned object_index, unsigned mesh_index) override;
};



#endif