//================================================================================
//!	@file	 CubePolygon.h
//!	@brief	 �L���[�u�|���S��Class
//! @details 
//!	@author  Kai Araki									@date 2017/10/16
//================================================================================
#ifndef	_CUBE_POLYGON_H_
#define _CUBE_POLYGON_H_



//************************************************************														   
//! @brief   �L���[�u�|���S��Class
//!
//! @details �L���[�u�̃|���S��Class
//************************************************************
class CubePolygon
{
//====================
// �萔
//====================
private:
	static const int PRIMITIVE_NUM;		//!< �v���~�e�B�u��


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


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param color �F
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init(XColor4 color = {1.0f, 1.0f, 1.0f, 1.0f});

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
	//! @param color �F
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateVertex(Color4 color);

	//----------------------------------------
	//! @brief �C���f�b�N�X�쐬�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateIndex();

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
};



#endif
