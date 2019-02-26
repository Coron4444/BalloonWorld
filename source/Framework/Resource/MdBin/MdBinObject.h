//================================================================================
//!	@file	 MdBinObject.h
//!	@brief	 �o�C�i���[���f���I�u�W�F�N�gClass
//! @details 
//!	@author  Kai Araki									@date 2019/1/11
//================================================================================
#ifndef	_MD_BIN_OBJECT_H_
#define _MD_BIN_OBJECT_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <windows.h>
#include <string>
#include <vector>

#include "MdBinData.h"
#include <Tool/Vector3D.h>
#include <Tool/Matrix.h>



//****************************************
// �N���X�錾
//****************************************
class TextureObject;



//************************************************************														   
//! @brief   �o�C�i���[���f���I�u�W�F�N�gClass
//!
//! @details �o�C�i���[���f���̃I�u�W�F�N�gClass
//************************************************************
class MdBinObject
{
//====================
// �N���X��`
//====================
public:
	//****************************************														   
	//! @brief ���_Struct
	//!
	//! @details ���_�p��Struct
	//****************************************
	struct Vertex
	{
	//====================
	// �ϐ�
	//====================
	public:
		Vec3 posisiont_;	//!< ���W
		Vec3 normal_;		//!< �@��
		Color4 color_;		//!< �J���[
		Vec2 uv_;			//!< UV
		float bone_weight_[MdBinData::Mesh::BoneWeight::MAX_BONE_NUM];			//!< �{�[���̏d��
		unsigned char bone_index_[MdBinData::Mesh::BoneWeight::MAX_BONE_NUM];	//!< �{�[���C���f�b�N�X
	};


	//****************************************														   
	//! @brief �{�[��Class
	//!
	//! @details �{�[����Class
	//****************************************
	class Bone
	{
	//====================
	// �ϐ�
	//====================
	private:
		std::string name_;						//!< �{�[����
		Matrix offset_matrix_;					//!< �I�t�Z�b�g�s��
		std::vector<Matrix> animation_matrix_;	//!< �A�j���[�V�����s��


	//====================
	// �v���p�e�B
	//====================
	public:
		//----------------------------------------
		//! @brief �{�[�����擾�֐�
		//! @details
		//! @param void �Ȃ�
		//! @retval std::string* �{�[����
		//----------------------------------------
		std::string* getpName();

		//----------------------------------------
		//! @brief �I�t�Z�b�g�s��擾�֐�
		//! @details
		//! @param void �Ȃ�
		//! @retval Matrix* �I�t�Z�b�g�z��
		//----------------------------------------
		Matrix* getpOffsetMatrix();

		//----------------------------------------
		//! @brief �A�j���[�V�����s��z��T�C�Y�擾�֐�
		//! @details
		//! @param void �Ȃ�
		//! @retval int �A�j���[�V�����s��z��T�C�Y
		//----------------------------------------
		int getAnimationMatrixArraySize();

		//----------------------------------------
		//! @brief �A�j���[�V�����s��z��T�C�Y�ݒ�֐�
		//! @details
		//! @param value �A�j���[�V�����s��z��T�C�Y
		//! @retval void �Ȃ�
		//----------------------------------------
		void setAnimationMatrixArraySize(int value);

		//----------------------------------------
		//! @brief �A�j���[�V�����s��擾�֐�
		//! @details
		//! @param index �C���f�b�N�X
		//! @retval Matrix* �A�j���[�V�����s��
		//----------------------------------------
		Matrix* getpAnimationMatrix(int index);
	};


	//****************************************														   
	//! @brief ���b�V��Class
	//!
	//! @details ���b�V����Class
	//****************************************
	class Mesh
	{
	//====================
	// �ϐ�
	//====================
	private:
		std::vector<Vertex> vertex_;						//!< ���_�z��
		std::vector<WORD> index_;							//!< �C���f�b�N�X�z��
		std::vector<Bone> bone_;							//!< �{�[���z��
		int material_index_;								//!< �}�e���A���C���f�b�N�X
		int primitive_num_;									//!< �v���~�e�B�u��
		TextureObject* diffuse_texture_object_ = nullptr;	//!< �f�B�q���[�Y�e�N�X�`���I�u�W�F�N�g
		LPDIRECT3DVERTEXBUFFER9 vertex_buffer_ = nullptr;	//!< ���_�o�b�t�@
		LPDIRECT3DINDEXBUFFER9  index_buffer_ = nullptr;	//!< �C���f�b�N�X�o�b�t�@


	//====================
	// �v���p�e�B
	//====================
	public:
		//----------------------------------------
		//! @brief ���_�z��T�C�Y�擾�֐�
		//! @details
		//! @param void �Ȃ� 
		//! @retval int �T�C�Y
		//----------------------------------------
		int getVertexArraySize();

		//----------------------------------------
		//! @brief ���_�z��T�C�Y�ݒ�֐�
		//! @details
		//! @param value �T�C�Y
		//! @retval void �Ȃ�
		//----------------------------------------
		void setVertexArraySize(int value);

		//----------------------------------------
		//! @brief ���_�擾�֐�
		//! @details
		//! @param index �C���f�b�N�X
		//! @retval Vertex* ���_
		//----------------------------------------
		Vertex* getpVertex(int index);

		//----------------------------------------
		//! @brief �C���f�b�N�X�z��T�C�Y�擾�֐�
		//! @details
		//! @param void �Ȃ� 
		//! @retval int �T�C�Y
		//----------------------------------------
		int getIndexArraySize();

		//----------------------------------------
		//! @brief �C���f�b�N�X�z��T�C�Y�ݒ�֐�
		//! @details
		//! @param value �T�C�Y
		//! @retval void �Ȃ�
		//----------------------------------------
		void setIndexArraySize(int value);

		//----------------------------------------
		//! @brief �C���f�b�N�X�擾�֐�
		//! @details
		//! @param index �C���f�b�N�X
		//! @retval WORD* �C���f�b�N�X
		//----------------------------------------
		WORD* getpIndex(int index);

		//----------------------------------------
		//! @brief �{�[���z��T�C�Y�擾�֐�
		//! @details
		//! @param void �Ȃ� 
		//! @retval int �T�C�Y
		//----------------------------------------
		int getBoneArraySize();

		//----------------------------------------
		//! @brief �{�[���z��T�C�Y�ݒ�֐�
		//! @details
		//! @param value �T�C�Y
		//! @retval void �Ȃ�
		//----------------------------------------
		void setBoneArraySize(int value);

		//----------------------------------------
		//! @brief �{�[���擾�֐�
		//! @details
		//! @param index �C���f�b�N�X
		//! @retval Bone* ���_
		//----------------------------------------
		Bone* getpBone(int index);

		//----------------------------------------
		//! @brief �}�e���A���C���f�b�N�X�擾�֐�
		//! @details
		//! @param void �Ȃ� 
		//! @retval int �}�e���A���C���f�b�N�X
		//----------------------------------------
		int getMaterialIndex();

		//----------------------------------------
		//! @brief �}�e���A���C���f�b�N�X�ݒ�֐�
		//! @details
		//! @param value �}�e���A���C���f�b�N�X
		//! @retval void �Ȃ�
		//----------------------------------------
		void setMaterialIndex(int value);

		//----------------------------------------
		//! @brief �v���~�e�B�u���擾�֐�
		//! @details
		//! @param void �Ȃ� 
		//! @retval int �v���~�e�B�u��
		//----------------------------------------
		int getPrimitiveNum();

		//----------------------------------------
		//! @brief �v���~�e�B�u���ݒ�֐�
		//! @details
		//! @param value �v���~�e�B�u��
		//! @retval void �Ȃ�
		//----------------------------------------
		void setPrimitiveNum(int value);

		//----------------------------------------
		//! @brief �f�B�q���[�Y�e�N�X�`���I�u�W�F�N�g�擾�֐�
		//! @details
		//! @param void �Ȃ� 
		//! @retval TextureObject* �f�B�q���[�Y�e�N�X�`���I�u�W�F�N�g
		//----------------------------------------
		TextureObject* getpDiffuseTextureObject();

		//----------------------------------------
		//! @brief �f�B�q���[�Y�e�N�X�`���I�u�W�F�N�g�ݒ�֐�
		//! @details
		//! @param *value �f�B�q���[�Y�e�N�X�`���I�u�W�F�N�g
		//! @retval void �Ȃ�
		//----------------------------------------
		void setDiffuseTextureObject(TextureObject* value);

		//----------------------------------------
		//! @brief ���_�o�b�t�@�擾�֐�
		//! @details
		//! @param void �Ȃ�
		//! @retval LPDIRECT3DVERTEXBUFFER9 ���_�o�b�t�@
		//----------------------------------------
		LPDIRECT3DVERTEXBUFFER9 getpVertexBuffer();

		//----------------------------------------
		//! @brief ���_�o�b�t�@�ϐ��|�C���^�擾�֐�
		//! @details
		//! @param void �Ȃ�
		//! @retval LPDIRECT3DVERTEXBUFFER9* ���_�o�b�t�@�ϐ��|�C���^
		//----------------------------------------
		LPDIRECT3DVERTEXBUFFER9* getp2VertexBuffer();

		//----------------------------------------
		//! @brief �C���f�b�N�X�o�b�t�@�擾�֐�
		//! @details
		//! @param void �Ȃ�
		//! @retval LPDIRECT3DINDEXBUFFER9 �C���f�b�N�X�o�b�t�@
		//----------------------------------------
		LPDIRECT3DINDEXBUFFER9 getpIndexBuffer();

		//----------------------------------------
		//! @brief �C���f�b�N�X�o�b�t�@�ϐ��|�C���^�擾�֐�
		//! @details
		//! @param void �Ȃ�
		//! @retval LPDIRECT3DINDEXBUFFER9* �C���f�b�N�X�o�b�t�@�ϐ��|�C���^
		//----------------------------------------
		LPDIRECT3DINDEXBUFFER9* getp2IndexBuffer();

	//====================
	// �֐�
	//====================
	public:
		//----------------------------------------
		//! @brief �I���֐�
		//! @details
		//! @param void �Ȃ�
		//! @retval void �Ȃ�
		//----------------------------------------
		void Uninit();
	};


//====================
// �ϐ�
//====================
private:
	std::vector<Mesh> mesh_;				//!< ���b�V���z��
	std::vector<D3DMATERIAL9> material_;	//!< �}�e���A���z��
	int animation_frame_num_;				//!< �A�j���[�V�����t���[����
	LPDIRECT3DDEVICE9 device_ = nullptr;	//!< �f�o�C�X
	std::string map_key_name_;				//!< �}�b�v�p�L�[��
	int reference_counter_ = 0;				//!< �Q�ƃJ�E���^


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief ���b�V�����擾�֐�
	//! @details
	//! @param void �Ȃ� 
	//! @retval unsigned ���b�V����
	//----------------------------------------
	unsigned getMeshNum();

	//----------------------------------------
	//! @brief ���b�V���擾�֐�
	//! @details
	//! @param index �C���f�b�N�X 
	//! @retval Mesh* ���b�V��
	//----------------------------------------
	Mesh* getpMesh(int index);

	//----------------------------------------
	//! @brief �}�e���A���擾�֐�
	//! @details
	//! @param mesh_index ���b�V���C���f�b�N�X 
	//! @retval D3DMATERIAL9* �}�e���A��
	//----------------------------------------
	D3DMATERIAL9* getpMaterial(unsigned mesh_index);

	//----------------------------------------
	//! @brief �f�B�q���[�Y�e�N�X�`���I�u�W�F�N�g�擾�֐�
	//! @details
	//! @param mesh_index ���b�V���C���f�b�N�X 
	//! @retval TextureObject* �f�B�q���[�Y�e�N�X�`���I�u�W�F�N�g
	//----------------------------------------
	TextureObject* getpDiffuseTextureObject(unsigned mesh_index);

	//----------------------------------------
	//! @brief �f�B�q���[�Y�e�N�X�`���n���h���擾�֐�
	//! @details
	//! @param mesh_index ���b�V���C���f�b�N�X  
	//! @retval LPDIRECT3DTEXTURE9 �f�B�q���[�Y�e�N�X�`���n���h��
	//----------------------------------------
	LPDIRECT3DTEXTURE9 getpDiffuseTextureHandler(unsigned mesh_index);

	int getAnimationFrameNum()
	{
		return animation_frame_num_;
	}

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
	//! @brief �`��֐�
	//! @details
	//! @param mesh_index ���b�V���C���f�b�N�X
	//! @retval void �Ȃ�
	//----------------------------------------
	void Draw(unsigned mesh_index);

private:
	//----------------------------------------
	//! @brief �}�e���A�������֐�
	//! @details
	//! @param *md_bin_data �o�C�i���[���f���f�[�^
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateMaterial(MdBinData* md_bin_data);

	//----------------------------------------
	//! @brief ���b�V�������֐�
	//! @details
	//! @param *file_path   �t�@�C���p�X
	//! @param *md_bin_data �o�C�i���[���f���f�[�^
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateMesh(std::string* file_path, MdBinData* md_bin_data);

	//----------------------------------------
	//! @brief �}�e���A���C���f�b�N�X�����֐�
	//! @details
	//! @param mesh_index   ���b�V���C���f�b�N�X
	//! @param *md_bin_data �o�C�i���[���f���f�[�^
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateMaterialIndex(int mesh_index, MdBinData* md_bin_data);

	//----------------------------------------
	//! @brief �C���f�b�N�X�����֐�
	//! @details
	//! @param mesh_index   ���b�V���C���f�b�N�X
	//! @param *md_bin_data �o�C�i���[���f���f�[�^
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateIndex(int mesh_index, MdBinData* md_bin_data);

	//----------------------------------------
	//! @brief ���_�����֐�
	//! @details
	//! @param mesh_index   ���b�V���C���f�b�N�X
	//! @param *md_bin_data �o�C�i���[���f���f�[�^
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateVertex(int mesh_index, MdBinData* md_bin_data);

	//----------------------------------------
	//! @brief ���_���W�����֐�
	//! @details
	//! @param mesh_index   ���b�V���C���f�b�N�X
	//! @param vertex_index ���_�C���f�b�N�X
	//! @param *md_bin_data �o�C�i���[���f���f�[�^
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateVertexPosition(int mesh_index, int vertex_index,
							  MdBinData* md_bin_data);

	//----------------------------------------
	//! @brief �@�������֐�
	//! @details
	//! @param mesh_index   ���b�V���C���f�b�N�X
	//! @param vertex_index ���_�C���f�b�N�X
	//! @param *md_bin_data �o�C�i���[���f���f�[�^
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateNormal(int mesh_index, int vertex_index,
					  MdBinData* md_bin_data);

	//----------------------------------------
	//! @brief �J���[�����֐�
	//! @details
	//! @param mesh_index   ���b�V���C���f�b�N�X
	//! @param vertex_index ���_�C���f�b�N�X
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateColor(int mesh_index, int vertex_index);

	//----------------------------------------
	//! @brief UV�����֐�
	//! @details
	//! @param mesh_index   ���b�V���C���f�b�N�X
	//! @param vertex_index ���_�C���f�b�N�X
	//! @param *md_bin_data �o�C�i���[���f���f�[�^
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateUV(int mesh_index, int vertex_index,
				  MdBinData* md_bin_data);

	//----------------------------------------
	//! @brief �{�[���̏d�ݐ����֐�
	//! @details
	//! @param mesh_index   ���b�V���C���f�b�N�X
	//! @param vertex_index ���_�C���f�b�N�X
	//! @param *md_bin_data �o�C�i���[���f���f�[�^
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateBoneWeight(int mesh_index, int vertex_index,
						  MdBinData* md_bin_data);

	//----------------------------------------
	//! @brief �f�B�q���[�Y�e�N�X�`�������֐�
	//! @details
	//! @param mesh_index   ���b�V���C���f�b�N�X
	//! @param *file_path   �t�@�C���p�X
	//! @param *md_bin_data �o�C�i���[���f���f�[�^
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateDiffuseTexture(int mesh_index,
							  std::string* file_path,
							  MdBinData* md_bin_data);

	//----------------------------------------
	//! @brief �{�[�������֐�
	//! @details
	//! @param mesh_index   ���b�V���C���f�b�N�X
	//! @param *md_bin_data �o�C�i���[���f���f�[�^
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateBone(int mesh_index,
					MdBinData* md_bin_data);

	//----------------------------------------
	//! @brief �s��ϊ��֐�
	//! @details
	//! @param *directx_matrix DirectX�s��
	//! @param *md_bin_matrix  �o�C�i���[���f���s��
	//! @retval void �Ȃ�
	//----------------------------------------
	void ChangeMatrix(MATRIX* directx_matrix,
					  MdBinData::Matrix* md_bin_matrix);

	//----------------------------------------
	//! @brief �t�@�C���p�X&�L�[�������֐�
	//! @details
	//! @param *file_path �t�@�C���p�X
	//! @param *key_name  �L�[��
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateFilePathAndKeyName(std::string* file_path,
								  std::string* key_name);

	//----------------------------------------
	//! @brief �o�b�t�@�����֐�
	//! @details
	//! @param mesh_index ���b�V���C���f�b�N�X
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateBuffer(int mesh_index);

	//----------------------------------------
	//! @brief ���_�o�b�t�@�����֐�
	//! @details
	//! @param mesh_index ���b�V���C���f�b�N�X
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateVertexBuffer(int mesh_index);

	//----------------------------------------
	//! @brief �C���f�b�N�X�o�b�t�@�����֐�
	//! @details
	//! @param mesh_index ���b�V���C���f�b�N�X
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateIndexBuffer(int mesh_index);
};



#endif
