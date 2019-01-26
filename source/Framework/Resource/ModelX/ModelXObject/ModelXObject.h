//================================================================================
//!	@file	 ModelXObject.h
//!	@brief	 X���f���I�u�W�F�N�gClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/01
//================================================================================
#ifndef	_MODEL_X_OBJECT_H_
#define _MODEL_X_OBJECT_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <string>
#include <vector>

#include <Renderer\Renderer.h>
#include <Vector3D.h>



//****************************************
// �N���X�錾
//****************************************
class TextureObject;



//************************************************************														   
//! @brief   X���f���I�u�W�F�N�gClass
//!
//! @details X���f���̃I�u�W�F�N�gClass
//************************************************************
class ModelXObject
{
//====================
// �ϐ�
//====================
private:
	LPD3DXMESH mesh_;										//!< ���b�V��
	DWORD mesh_num_;										//!< ���b�V����
	std::vector<D3DMATERIAL9> material_;					//!< �}�e���A��
	std::vector<TextureObject*> diffuse_texture_object_;	//!< �f�B�q���[�Y�e�N�X�`���I�u�W�F�N�g
	std::string map_key_name_;								//!< �}�b�v�p�L�[��
	int reference_counter_ = 0;								//!< �Q�ƃJ�E���^


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief ���b�V���擾�֐�
	//! @details
	//! @param void �Ȃ� 
	//! @retval LPD3DXMESH ���b�V��
	//----------------------------------------
	LPD3DXMESH getpMesh();

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
	//! @param index �C���f�b�N�X 
	//! @retval D3DMATERIAL9* �}�e���A��
	//----------------------------------------
	D3DMATERIAL9* getpMaterial(unsigned index);
	
	//----------------------------------------
	//! @brief �}�e���A���F�ݒ�֐�
	//! @details
	//! @param index �C���f�b�N�X
	//! @param color �F
	//! @retval void �Ȃ�
	//----------------------------------------
	void setMaterialColor(unsigned index, XColor4 color);

	//----------------------------------------
	//! @brief �f�B�q���[�Y�e�N�X�`���I�u�W�F�N�g�擾�֐�
	//! @details
	//! @param index �C���f�b�N�X
	//! @retval TextureObject* �f�B�q���[�Y�e�N�X�`���I�u�W�F�N�g
	//----------------------------------------
	TextureObject* getpDiffuseTextureObject(unsigned index);


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param *file_path    �t�@�C���p�X
	//! @param *map_key_name �}�b�v�p�L�[��
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init(std::string* file_path, const std::string* map_key_name);

	//----------------------------------------
	//! @brief ����֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Release();

	//----------------------------------------
	//! @brief ��������֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void ForcedRelease();

	//----------------------------------------
	//! @brief �Q�ƃJ�E���^�ǉ��֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void AddReferenceCounter();

	//----------------------------------------
	//! @brief ���_���ύX�֐�
	//! @details
	//! @param declaration ���_�錾
	//! @retval void �Ȃ�
	//----------------------------------------
	void UpdateMeshDeclaration(const D3DVERTEXELEMENT9* declaration);

private:
	//----------------------------------------
	//! @brief ���b�V�������֐�
	//! @details
	//! @param *file_path       �t�@�C���p�X
	//! @param *material_buffer �}�e���A���o�b�t�@
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateMesh(std::string* file_path, LPD3DXBUFFER* material_buffer);

	//----------------------------------------
	//! @brief �}�e���A�������֐�
	//! @details
	//! @param *file_path       �t�@�C���p�X
	//! @param *material_buffer �}�e���A���o�b�t�@
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateMaterial(std::string* file_path, LPD3DXBUFFER* material_buffer);

	//----------------------------------------
	//! @brief �t�@�C���p�X&�L�[�������֐�
	//! @details
	//! @param *file_path �t�@�C���p�X
	//! @param *key_name  �L�[��
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateFilePathAndKeyName(std::string* file_path,
								  std::string* key_name);
};



#endif