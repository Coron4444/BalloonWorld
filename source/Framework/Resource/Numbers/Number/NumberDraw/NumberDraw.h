//================================================================================
//
//    �����`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/06/19
//
//================================================================================

#ifndef	_NUMBER_DRAW_H_
#define _NUMBER_DRAW_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <string>

#include <Component/Draw/DrawNull/DrawNull.h>
#include "../Number.h"



/*********************************************************//**
* @brief
* �����`��N���X
*
* �����̕`��N���X
*************************************************************/
class NumberDraw : public DrawNull
{
//==============================
// ��ÓI�����o�֐�
//==============================
private:
	Number* number_;	//!< ����


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