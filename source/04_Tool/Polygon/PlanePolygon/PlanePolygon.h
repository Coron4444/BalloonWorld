//================================================================================
//
//    ���ʃ|���S���N���X�w�b�_
//    Author : Araki Kai                                �쐬�� : 2017/12/06
//
//================================================================================

#ifndef	_PLANE_POLYGON_H_
#define _PLANE_POLYGON_H_



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

class PlanePolygon
{
//------------------------------------------------------------
private :
	// �萔
	static const int PRIMITIVE_NUM; 


// ============================================================
public:
	// �f�t�H���g�R���X�g���N�^
	PlanePolygon(XColor4 color = XColor4 (1.0f, 1.0f, 1.0f, 1.0f), Vec2 plane_size = Vec2 (1.0f, 1.0f));


// ============================================================
public:
	// �f�X�g���N�^
	virtual ~PlanePolygon();


// ============================================================
public:
	// �����o�֐�
	void Draw();

	void SetColor(XColor4 color);
	void SetUV(TextureObject* texture, int pattern_num = 0);

	XColor4 GetColor(){ return vertex_[0].color_; }

	unsigned getMeshNum(){return 1;}
	D3DMATERIAL9* GetMaterial(){return &material_;}


//------------------------------------------------------------
private:
	// ����J�����o�֐�
	void CreateVertex(Color4 color, Vec2 plane_size);
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
