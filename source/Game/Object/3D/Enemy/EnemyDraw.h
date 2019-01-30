//================================================================================
//!	@file	 EnemyDraw.h
//!	@brief	 �G�`��Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================
#ifndef	_ENEMY_DRAW_H_
#define _ENEMY_DRAW_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <GameEngine/Draw/DrawNull.h>



//****************************************
// �N���X�錾
//****************************************
class Enemy;
class CubePolygon;



//************************************************************														   
//! @brief   �G�`��Class
//!
//! @details �G�̕`��Class
//************************************************************
class EnemyDraw : public DrawNull
{
//====================
// �ϐ�
//====================
private:
	Enemy* enemy_;					//!< �G
	CubePolygon* cube_polygon_;		//!< �l�p�`�|���S��


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
	//! @brief �`��֐�
	//! @param[in] object_index �I�u�W�F�N�g�C���f�b�N�X
	//! @param[in] mesh_index   ���b�V���C���f�b�N�X
	//! @retval void �Ȃ�
	//----------------------------------------
	void Draw(unsigned object_index, unsigned mesh_index) override;
};



#endif