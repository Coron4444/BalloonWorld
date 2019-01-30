//================================================================================
//!	@file	 Field.h
//!	@brief	 �n��Class
//! @details 
//!	@author  Kai Araki									@date 2018/05/15
//================================================================================
#ifndef	_FIELD_H_
#define _FIELD_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <GameEngine/GameObject/GameObjectNull.h>
#include <Resource/Polygon/MeshPlanePolygon.h>



//************************************************************														   
//! @brief   �R�C��Class
//!
//! @details �R�C����Class
//************************************************************
class Field : public GameObjectNull
{
//====================
// �ϐ�
//====================
private:
	MeshPlanePolygon* mesh_plane_polygon_;		//!< ���b�V�����ʃ|���S��


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief ���b�V�����ʃ|���S���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	MeshPlanePolygon* getpMeshPlanePolygon();


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param *draw �`����N���X
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init(DrawBase* draw);

	//----------------------------------------
	//! @brief �I���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Uninit() override;
};



#endif