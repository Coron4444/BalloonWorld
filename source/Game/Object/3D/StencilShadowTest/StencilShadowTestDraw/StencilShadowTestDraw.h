//================================================================================
//
//    �X�e���V���V���h�E�`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/03/27
//
//================================================================================

#ifndef	_STENCIL_SHADOW_TEST_DRAW_H_
#define _STENCIL_SHADOW_TEST_DRAW_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <string>

#include <Component/Draw/DrawNull/DrawNull.h>
#include "../StencilShadowTest.h"



//****************************************
// �N���X�錾
//****************************************
class PlanePolygon;
class ModelXObject;



/*********************************************************//**
* @brief
* �X�e���V���V���h�E�`��N���X
*
* �X�e���V���V���h�E�̕`��N���X
*************************************************************/
class StencilShadowTestDraw : public DrawNull
{
//==============================
// �萔
//==============================
private:
	// �萔
	static const std::string MODEL_NAME;		//!< ���f����

//==============================
// ��ÓI�����o�֐�
//==============================
private:
	ModelXObject* player_model_;			//!< ���f���I�u�W�F�N�g
	PlanePolygon* plane_polygon_;			//!< �|���S��	
	Transform plane_polygon_transform_;		//!< �|���S���p�ό`


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

	/**
	* @brief
	* �`��O�ݒ�֐�
	* @param
	* camera : �J����
	* object_index : �I�u�W�F�N�g�C���f�b�N�X
	*/
	virtual void SettingBeforeDrawing(Camera* camera, unsigned object_index) override;

	/**
	* @brief
	* �`���ݒ�֐�
	* @param
	* camera : �J����
	* object_index : �I�u�W�F�N�g�C���f�b�N�X
	*/
	virtual void SettingAfterDrawing(Camera* camera, unsigned object_index) override;

	// �v���p�e�B
	unsigned getObjectNum() override;
	unsigned getMeshNum(unsigned object_index) override;
	MATRIX* getpMatrix(unsigned object_index) override;
	D3DMATERIAL9* getpMaterial(unsigned object_index, unsigned mesh_index) override;
	LPDIRECT3DTEXTURE9 getpDiffuseTexture(unsigned object_index, unsigned mesh_index) override;
};



#endif