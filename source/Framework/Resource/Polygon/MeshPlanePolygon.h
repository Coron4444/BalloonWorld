//================================================================================
//
//    ���b�V�����ʃ|���S���N���X�w�b�_
//    Author : Araki Kai                                �쐬�� : 2017/11/22
//
//================================================================================

#ifndef	_MESH_PLANE_POLYGON_H_
#define _MESH_PLANE_POLYGON_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include <string>
#include <vector>

#include <Vector3D.h>

#include <Renderer\Renderer.h>



//======================================================================
//
// �N���X�錾
//
//======================================================================

class TextureObject;



//======================================================================
//
// �N���X��`
//
//======================================================================

class MeshPlanePolygon
{
//------------------------------------------------------------
private :
	// �萔
	static const float TEXTURE_WIDTH; 
	static const float TEXTURE_HEIGHT;
	static const float MESH_MIN;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �f�t�H���g�R���X�g���N�^
	MeshPlanePolygon(Vec2 mesh_num   = {1.0f, 1.0f}, 
		             Vec2 mesh_scale = {1.0f, 1.0f},
					 XColor4 color   = {1.0f, 1.0f, 1.0f, 1.0f});


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �f�X�g���N�^
	virtual ~MeshPlanePolygon();


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �����o�֐�
	void Draw();

	void SetColor(XColor4 color);

	float GetHeight(Vec3 position);

	unsigned getMeshNum(){return 1;}
	D3DMATERIAL9* GetMaterial(){return &material_;}


//------------------------------------------------------------
private :
	// ����J�����o�֐�
	void CreateVertex(Vec2 mesh_num, Vec2 mesh_scale, Color4 color);
	void CreateIndex(Vec2 mesh_num);
	void CreatePrimitiveNum(Vec2 mesh_num);
	void CreateMaterial();

	void AccessVRAM();

	void RegistrationVertex();
	void RegistrationIndex();

	bool CalculationHeight(Vec3* position, int index0, int index1, int index2);


//------------------------------------------------------------
private :
	int primitive_num_;
	Vec2 mesh_num_;

	std::vector<RendererDirectX9::VERTEX_3D> vertex_;
	std::vector<WORD>      index_;

	LPDIRECT3DVERTEXBUFFER9 vertex_buffer_;
	LPDIRECT3DINDEXBUFFER9  index_buffer_;
	D3DMATERIAL9			material_;
	LPDIRECT3DDEVICE9		device_;
};



#endif
