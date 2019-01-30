//================================================================================
//!	@file	 GoalDraw.h
//!	@brief	 �S�[���`��Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/28
//================================================================================
#ifndef	_GOAL_DRAW_H_
#define _GOAL_DRAW_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <string>

#include <GameEngine/Draw/DrawNull.h>
#include <Resource/Texture/TextureManager/TextureManager.h>



//****************************************
// �N���X�錾
//****************************************
class CubePolygon;
class EffekseerObject;



//************************************************************														   
//! @brief   �S�[���`��Class
//!
//! @details �S�[���̕`��Class
//************************************************************
class GoalDraw : public DrawNull
{
//====================
// �萔
//====================
private:
	static const std::string EFFECT_NAME;		//!< �G�t�F�N�g��


//====================
// �ϐ�
//====================
private:
	CubePolygon* cube_polygon_;			//!< �l�p�`�|���S��
	EffekseerObject* effekseer_object_;	//!< �G�t�F�N�V�A�I�u�W�F�N�g


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
};



#endif