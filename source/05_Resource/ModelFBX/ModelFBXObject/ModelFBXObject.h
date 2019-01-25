//================================================================================
//
//    FBX���f���N���X�I�u�W�F�N�g�w�b�_
//    Author : Araki Kai                                �쐬�� : 2018/01/19
//
//================================================================================

#ifndef	_MODEL_FBX_OBJECT_H_
#define _MODEL_FBX_OBJECT_H_



//**********************************************************************
//
// �C���N���[�h��
//
//**********************************************************************

#include <string>
#include <vector>

#include <Vector3D.h>
#include <ModelFBX\LoadMFM\LoadMFM.h>



//**********************************************************************
//
// �萔��`
//
//**********************************************************************

const int MAX_MFM_BONE = 4;



//**********************************************************************
//
// �N���X�錾
//
//**********************************************************************

class TextureManager;
class Model;



//**********************************************************************
//
// �N���X��`
//
//**********************************************************************

class ModelFBXObject
{
// ============================================================
private :
	// �e��
	struct Impact
	{
		float         weight[MAX_MFM_BONE];
		unsigned char matrixIndex[MAX_MFM_BONE];
	};

	// ���_�\����
	struct VERTEX_3D
	{
		D3DXVECTOR3 Pos;
		D3DXVECTOR3 Normal;
		D3DCOLOR	color;
		D3DXVECTOR2 texcoord;
		Impact		ImpactMap;
	};

	struct Shaderbuff
	{
		std::vector<VERTEX_3D> Vertex;
	};


	struct Mesh_DirectX9
	{
		int         MaterialIndex;
		int         PrimitiveNum;
		std::string TexName;
	};

	struct Bone
	{
		std::vector<D3DXMATRIX> MatAry;
	};

	class MFMANIMEDATA
	{
	public:
		std::vector<Mesh_DirectX9>			 MeshData;
		std::vector<D3DMATERIAL9>			 Material;
		std::vector<LPDIRECT3DVERTEXBUFFER9> VertexBuffer;
		std::vector<LPDIRECT3DTEXTURE9>      Texture;
		std::vector<std::vector<Bone>>		 bone;
		int									 nAnimFrame;
	};

	


// ============================================================
public :
	// �f�t�H���g�R���X�g���N�^
	ModelFBXObject(TextureManager* texture_manager, const std::string* key_name, const std::string* file_path = nullptr);


// ============================================================
public :
	// �f�X�g���N�^
	virtual ~ModelFBXObject();


// ============================================================
public :
	// ���J�����o�֐�
	void SetModelFBXObject();

	int GetAnimationFrameNum(const int animation_count, int animation_speed);


	void SetColor(XColor4 color);

	int  GetAnimationFrameMax(){return mfm_model_data_.nAnimFrame;}


// ============================================================
private :
	// ����J�����o�֐�
	void CreateVertex  (mfmlib::Model* temp_model, std::vector<Shaderbuff>* temp_mesh, const std::string* file_path);
	void CreateMaterial(mfmlib::Model* temp_model);

	void AccessVRAM(LPDIRECT3DDEVICE9 pDevice, std::vector<Shaderbuff>* temp_mesh);

	void RegistrationVertex(std::vector<Shaderbuff>* temp_mesh);

// ============================================================
public :
	// ���J�����o�ϐ�
	Vec3		light_vector_;
	std::string shader_name_;


// ============================================================
private :
	// mfm���f���f�[�^
	MFMANIMEDATA mfm_model_data_;	
	
	// �e�N�X�`���}�l�[�W��
	TextureManager* texture_manager_;

	// ���_�錾
	IDirect3DVertexDeclaration9* vertex_declaration_;

	// ���b�V�����
	std::vector<Shaderbuff> mesh_;
};



#endif
