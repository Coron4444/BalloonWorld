//================================================================================
//
//    �S�[���`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/11/28
//
//================================================================================

#ifndef	_GOAL_DRAW_H_
#define _GOAL_DRAW_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <string>

#include <Component/Draw/DrawNull/DrawNull.h>
#include <string>

#include "../Goal.h"

#include <Polygon\CubePolygon\CubePolygon.h>



//****************************************
// �N���X�錾
//****************************************
class EffekseerObject;


/*********************************************************//**
* @brief
* �S�[���`��N���X
*
* �S�[���̕`��N���X
*************************************************************/
class GoalDraw : public DrawNull
{
//==============================
// �萔
//==============================
private:
	static const std::string EFFECT;			//!< �G�t�F�N�g��


//==============================
// ��ÓI�����o�ϐ�
//==============================
private:
	Goal* goal_;	//!< �S�[��
	CubePolygon* cube_polygon_;		//!< �L���[�u�|���S��
	EffekseerObject* effekseer_object_;	//!< �G�t�F�N�V�A�I�u�W�F�N�g

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
	* �X�V�֐�
	*/
	virtual void Update() override;

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