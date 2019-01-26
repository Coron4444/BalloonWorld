//================================================================================
//
//    �X�R�A�`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/06/20
//
//================================================================================

#ifndef	_SCORE_DRAW_H_
#define _SCORE_DRAW_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <Component/Draw/DrawNull/DrawNull.h>
#include "../Score.h"



/*********************************************************//**
* @brief
* �X�R�A�`��N���X
*
* �X�R�A�̕`��N���X
*************************************************************/
class ScoreDraw : public DrawNull
{
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
	MATRIX* getpMatrix(unsigned object_index) override;
};



#endif