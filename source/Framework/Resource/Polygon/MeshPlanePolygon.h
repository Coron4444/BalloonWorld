//================================================================================
//!	@file	 MeshPlanePolygon.h
//!	@brief	 ���b�V�����ʃ|���S��Class
//! @details 
//!	@author  Kai Araki									@date 2017/11/22
//================================================================================
#ifndef	_MESH_PLANE_POLYGON_H_
#define _MESH_PLANE_POLYGON_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <string>
#include <vector>

#include <GameEngine/Renderer/Renderer.h>
#include <Tool/Vector3D.h>



//************************************************************														   
//! @brief   ���b�V�����ʃ|���S��Class
//!
//! @details ���b�V�����ʂ̃|���S��Class
//************************************************************
class MeshPlanePolygon
{
//====================
// �萔
//====================
private:
	static const float TEXTURE_WIDTH;		//!< �e�N�X�`����
	static const float TEXTURE_HEIGHT;		//!< �e�N�X�`������
	static const float MESH_MIN;			//!< �ŏ����b�V��


//====================
// �ϐ�
//====================
private:
	std::vector<RendererDirectX9::VERTEX_3D> vertex_;	//!< ���_
	std::vector<WORD> index_;							//!< �C���f�b�N�X
	D3DMATERIAL9 material_;								//!< �}�e���A��
	LPDIRECT3DVERTEXBUFFER9 vertex_buffer_ = nullptr;	//!< ���_�o�b�t�@
	LPDIRECT3DINDEXBUFFER9 index_buffer_ = nullptr;		//!< �C���f�b�N�X�o�b�t�@
	LPDIRECT3DDEVICE9 device_ = nullptr;				//!< �f�o�C�X
	int primitive_num_;									//!< �v���~�e�B�u��
	Vec2 mesh_num_;										//!< ���b�V����


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �F�ݒ�֐�
	//! @details
	//! @param value �F
	//! @retval void �Ȃ�
	//----------------------------------------
	void setColor(XColor4 value);

	//----------------------------------------
	//! @brief ���b�V�����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval unsigned ���b�V����
	//----------------------------------------
	unsigned getMeshNum();

	//----------------------------------------
	//! @brief �}�e���A���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval D3DMATERIAL9* �}�e���A��
	//----------------------------------------
	D3DMATERIAL9* getpMaterial();

	//----------------------------------------
	//! @brief �����擾�֐�
	//! @details
	//! @param position ���W
	//! @retval float ����
	//----------------------------------------
	float getHeight(Vector3D position);


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param mesh_num   ���b�V����
	//! @param mesh_scale ���b�V���g�k
	//! @param color      �F
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init(Vec2 mesh_num = {1.0f, 1.0f},
			  Vec2 mesh_scale = {1.0f, 1.0f},
			  XColor4 color = {1.0f, 1.0f, 1.0f, 1.0f});

	//----------------------------------------
	//! @brief �I���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Uninit();

	//----------------------------------------
	//! @brief �`��֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Draw();

	//----------------------------------------
	//! @brief ���C���[�t���[���ŕ`��֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void DrawWireFrame();

private:
	//----------------------------------------
	//! @brief ���_�쐬�֐�
	//! @details
	//! @param mesh_num   ���b�V����
	//! @param mesh_scale ���b�V���g�k
	//! @param color      �F
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateVertex(Vec2 mesh_num, Vec2 mesh_scale, Color4 color);

	//----------------------------------------
	//! @brief �C���f�b�N�X�쐬�֐�
	//! @details
	//! @param mesh_num ���b�V����
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateIndex(Vec2 mesh_num);

	//----------------------------------------
	//! @brief �v���~�e�B�u���쐬�֐�
	//! @details
	//! @param mesh_num ���b�V����
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreatePrimitiveNum(Vec2 mesh_num);

	//----------------------------------------
	//! @brief �}�e���A���쐬�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateMaterial();

	//----------------------------------------
	//! @brief VRAM�փA�N�Z�X�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void AccessVRAM();

	//----------------------------------------
	//! @brief ���_�o�b�t�@�ɓo�^�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void RegistrationVertex();

	//----------------------------------------
	//! @brief �C���f�b�N�X�o�b�t�@�ɓo�^�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void RegistrationIndex();

	//----------------------------------------
	//! @brief �����Z�o�֐�
	//! @details
	//! @param *position ���W
	//! @param index0	 �C���f�b�N�X0
	//! @param index1	 �C���f�b�N�X1
	//! @param index2	 �C���f�b�N�X2
	//! @retval bool ���W���|���S�����Ȃ�true
	//----------------------------------------
	bool CalculationHeight(Vector3D* position, int index0, int index1, int index2);
};



#endif
