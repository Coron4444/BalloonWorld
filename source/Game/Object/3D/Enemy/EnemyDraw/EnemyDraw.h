//================================================================================
//
//    �G�`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/07/24
//
//================================================================================

#ifndef	_ENEMY_DRAW_H_
#define _ENEMY_DRAW_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <string>

#include <Component/Draw/DrawNull/DrawNull.h>
#include "../Enemy.h"



/*********************************************************//**
* @brief
* �G�`��N���X
*
* �G�̕`��N���X
*************************************************************/
class EnemyDraw : public DrawNull
{
//==============================
// ��ÓI�����o�֐�
//==============================
private:
	Enemy* enemy_;				//!< �G


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
};



#endif