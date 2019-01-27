//================================================================================
//!	@file	 GridPolygon.h
//!	@brief	 �O���b�h�|���S��Class
//! @details 
//!	@author  Kai Araki									@date 2017/10/23
//================================================================================
#ifndef	_GRID_POLYGON_H_
#define _GRID_POLYGON_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <vector>
#include <string>

#include <GameEngine/Renderer\Renderer.h>



//************************************************************														   
//! @brief   �O���b�h�|���S��Class
//!
//! @details �O���b�h�̃|���S��Class
//************************************************************
class GridPolygon
{
//====================
// �ϐ�
//====================
private:
	std::vector<RendererDirectX9::VERTEX_3D> vertex_;	//!< ���_
	D3DMATERIAL9 material_;								//!< �}�e���A��
	LPDIRECT3DDEVICE9 device_ = nullptr;				//!< �f�o�C�X

//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init();

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

private:
//----------------------------------------
//! @brief ���_�쐬�֐�
//! @details
//! @param void �Ȃ�
//! @retval void �Ȃ�
//----------------------------------------
	void CreateVertex();

	//----------------------------------------
	//! @brief �}�e���A���쐬�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateMaterial();
};



#endif
