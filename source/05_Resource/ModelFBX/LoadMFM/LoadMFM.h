//================================================================================
//
//    FBX���f���N���X�w�b�_
//    Author : Araki Kai, Munesada                         �쐬�� : 2018/01/19
//
//================================================================================

#ifndef _LOAD_MFM_H_
#define _LOAD_MFM_H_



//**********************************************************************
//
// �C���N���[�h��
//
//**********************************************************************

#include <Windows.h>
#include <vector>



//**********************************************************************
//
// �\���̒�`&�N���X��`
//
//**********************************************************************

const int MFM_BONE_MAX = 4;



//**********************************************************************
//
// �\���̒�`&�N���X��`
//
//**********************************************************************

namespace mfmlib
{
	// float3��
	struct Float3
	{
		float x;
		float y;
		float z;
	};
	
	// float2��
	struct Float2
	{
		float U;
		float V;
	};
	
	// �}�e���A���J���[
	struct COLOR
	{
		Float3 Ambient;
		Float3 Diffuse;
		Float3 Emissive;
		Float3 Specular;
		Float3 Bump;
		float  Transparency;
		float  Shininess;
		float  Reflectivity;
	};
	
	// 4�~4�s��
	struct MATRIX4D
	{
	public:
		void  Set(int r, int c, float in) {Element[r][c] = in;}
		float Get(int r, int c)			  {return Element[r][c];}
	private:
		float Element[4][4];
	};
	
	
	// �d��
	struct Weight
	{
	public:
		float weight[MFM_BONE_MAX];
		int   index [MFM_BONE_MAX];	//directx�ł����Ƃ���unsigned�����ǐ��̐������͂���񂩂炽�Ԃ���v
	};
	
	
	// �}�e���A��
	struct Material
	{
		COLOR Color;
		TCHAR pTexName[MAX_PATH];
	};
	
	// �s��
	class MATRIX
	{
	public:
		int Num;
		std::vector<MATRIX4D> Data;
	};
	
	// float�^�f�[�^�Ǘ�
	class FloatData
	{
	public:
		void  SetNum(float in) {Num = in;}
		float GetNum()         {return Num;}
	private:
		float Num;
	};

	// float3��vector
	class Float3pData
	{
	public:
		int Num;
		std::vector<Float3> Data;
	};

	// float2��vector
	class Float2pData
	{
	public:
		int Num;
		std::vector<Float2> Data;
	};

	// float1��vector
	class Float1pData
	{
	public:
		FloatData Num;
		std::vector<float> Data;
	};

	// int�^vector
	class IntpData
	{
	public:
		int Num;
		std::vector<int> Data;
	};

	// ���_�̃{�[���̏d��
	class VertexBoneWeight
	{
	public:
		int Num;
		std::vector<Weight> Data;
	};

	// �{�[���A�j���s��
	class BoneAnim
	{
	public:
		MATRIX4D init;
		MATRIX   perFrame;
	};
	
	// �{�[�����b�V��
	class BoneMesh
	{
	public:
		int BoneNum;
		std::vector<BoneAnim> Data;
		VertexBoneWeight VertexData;
	};

	// ���b�V��
	class Mesh
	{
	public:
		//�f�[�^���o�����ꂷ��N���X�Q
		Float3pData Vertex;
		Float3pData Normals;
		Float2pData TexUV;
		IntpData Index;
		int MaterialIndex;
		int PrimitiveIndex;
	};
	
	// MFModel
	class Model
	{
	public:
		int						materialNum;	//�}�e���A����
		int						MeshNum;		//���b�V����
		int						FrameNum;		//�A�j���[�V�����̃t���[����
		std::vector<Mesh>		MeshData;		//���b�V���̎��f�[�^
		std::vector<Material>	MaterialData;	//�}�e���A���̎��f�[�^
		std::vector<BoneMesh>	BoneData;

		//�f�[�^���t�@�C������o�����ꂷ��֐�
		void SetFileName     (TCHAR* File_name);
		bool FileSaveMeshData();
		bool FileLoadMeshData(TCHAR* File_name);
		bool FileSaveFullData();
		bool FileLoadFullData(TCHAR* File_name);
	private:
		std::string Filename;
	};
	
}



#endif
