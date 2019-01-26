//================================================================================
//
//    �L���[�u�|���S���N���X�w�b�_
//    Author : Araki Kai                                �쐬�� : 2017/10/16
//
//================================================================================

#ifndef	_CUBE_POLYGON_H_
#define _CUBE_POLYGON_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include <vector>
#include <string>

#include <Vector3D.h>

#include <Renderer\Renderer.h>



//======================================================================
//
// �N���X��`
//
//======================================================================

class CubePolygon
{
//------------------------------------------------------------
private:
	// �萔
	static const int PRIMITIVE_NUM;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:
	// �f�t�H���g�R���X�g���N�^
	CubePolygon(XColor4 color = XColor4(1.0f, 1.0f, 1.0f, 1.0f));


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:
	// �f�X�g���N�^
	~CubePolygon();


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:
	// �����o�֐�
	void Draw();

	void SetColor(XColor4 color);

	unsigned getMeshNum() { return 1; }
	D3DMATERIAL9* GetMaterial() { return &material_; }



//------------------------------------------------------------
private:
	// ����J�����o�֐�
	void CreateVertex(Color4 color);
	void CreateIndex();
	void CreateMaterial();

	void AccessVRAM();

	void RegistrationVertex();
	void RegistrationIndex();


//------------------------------------------------------------
private:
	std::vector<RendererDirectX9::VERTEX_3D> vertex_;
	std::vector<WORD>      index_;

	LPDIRECT3DVERTEXBUFFER9 vertex_buffer_;
	LPDIRECT3DINDEXBUFFER9  index_buffer_;
	D3DMATERIAL9			material_;
	LPDIRECT3DDEVICE9		device_;
};



#endif
