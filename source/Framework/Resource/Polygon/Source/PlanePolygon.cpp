//================================================================================
//!	@file	 PlanePolygon.cpp
//!	@brief	 ���ʃ|���S��Class
//! @details 
//!	@author  Kai Araki									@date 2017/10/16
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../PlanePolygon.h"

#include <GameEngine/GameEngine.h>
#include <Resource/Texture/TextureObject.h>
#include <Tool/SafeRelease.h>



//****************************************
// �萔��`
//****************************************
const int PlanePolygon::PRIMITIVE_NUM = 2;



//****************************************
// �v���p�e�B��`
//****************************************
XColor4 PlanePolygon::getColor()
{
	return vertex_[0].color_;
}



void PlanePolygon::setColor(XColor4 value)
{
	for (auto& contents : vertex_)
	{
		contents.color_ = (Color4)value;
	}
	RegistrationVertex();
	material_.Diffuse = value;
	material_.Ambient = value;
}



unsigned PlanePolygon::getMeshNum()
{
	return 1;
}



D3DMATERIAL9* PlanePolygon::getpMaterial()
{
	return &material_;
}



void PlanePolygon::setUV(TextureObject* texture, int pattern_num = 0)
{
	vertex_[0].texcoord_ = Vec2(*texture->getpUV(pattern_num)->getpLeftUpU(),
								*texture->getpUV(pattern_num)->getpLeftUpV());
	vertex_[1].texcoord_ = Vec2(*texture->getpUV(pattern_num)->getpRightButtomU(),
								*texture->getpUV(pattern_num)->getpLeftUpV());
	vertex_[2].texcoord_ = Vec2(*texture->getpUV(pattern_num)->getpLeftUpU(),
								*texture->getpUV(pattern_num)->getpRightButtomV());
	vertex_[3].texcoord_ = Vec2(*texture->getpUV(pattern_num)->getpRightButtomU(),
								*texture->getpUV(pattern_num)->getpRightButtomV());
	RegistrationVertex();
}



//****************************************
// �֐���`
//****************************************
void PlanePolygon::Init(Vec2 mesh_scale, XColor4 color)
{
	CreateVertex(mesh_scale, (Color4)color);
	CreateIndex();
	CreateMaterial();

	Renderer::getpInstance()->getDevice(&device_);
	if (device_ == nullptr)
	{
		MessageBox(nullptr, "NotGetDevice!(PlanePolygon.cpp)", "Error", MB_OK);
		return;
	}
	AccessVRAM();
}



void PlanePolygon::Uninit()
{
	SafeRelease::PlusRelease(&vertex_buffer_);
	SafeRelease::PlusRelease(&index_buffer_);
}



void PlanePolygon::Draw()
{
	// FVF�̐ݒ�(�f�o�C�X�̕��ɒ��_�̑�����������)
	device_->SetFVF(RendererDirectX9::FVF_VERTEX_3D);

	// ���_�o�b�t�@���g��GPU�ƃo�[�e�b�N�X�o�b�t�@�̃p�C�v���C��
	// �g�������Ȃ�������NULL�������
	device_->SetStreamSource(0,										// �p�C�v���C���ԍ�
							 vertex_buffer_,						// �o�[�e�b�N�X�o�b�t�@�ϐ���
							 0,										// �ǂ����痬�����ނ�
							 sizeof(RendererDirectX9::VERTEX_3D));	// �X�g���C�h�l(�ׂ̒��_�܂ł̒�����1���_�̑傫��)

	 // ���C�e�B���OOFF
	device_->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �C���f�b�N�X�ŕ`��
	device_->SetIndices(index_buffer_);
	device_->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
								  0,						// �Z�b�g�X�g���[������ǂꂭ�炢����Ă��邩
								  0,						// �C���f�b�N�X�ň�ԏ������l
								  (UINT)vertex_.size(),		// ���_��
								  0,						// �X�^�[�g�C���f�b�N�X�ԍ�
								  PRIMITIVE_NUM);			// �v���~�e�B�u��

	 // ���C�e�B���OON
	device_->SetRenderState(D3DRS_LIGHTING, TRUE);
}



void PlanePolygon::CreateVertex(Vec2 mesh_scale, XColor4 color)
{
	// ���_���̓���
	float temp_x = mesh_scale.x / 2;
	float temp_y = mesh_scale.y / 2;

	float u0 = 0.0f;
	float v0 = 0.0f;
	float u1 = 1.0f;
	float v1 = 1.0f;

	vertex_.push_back({Vec3(-temp_x,  temp_y, 0.0f), Vec3(0.0f, 0.0f, -1.0f), color, Vec2(u0, v0)});
	vertex_.push_back({Vec3(temp_x,  temp_y, 0.0f), Vec3(0.0f, 0.0f, -1.0f), color, Vec2(u1, v0)});
	vertex_.push_back({Vec3(-temp_x, -temp_y, 0.0f), Vec3(0.0f, 0.0f, -1.0f), color, Vec2(u0, v1)});
	vertex_.push_back({Vec3(temp_x, -temp_y, 0.0f), Vec3(0.0f, 0.0f, -1.0f), color, Vec2(u1, v1)});
}



void PlanePolygon::CreateIndex()
{
	index_.push_back(2);
	index_.push_back(0);
	index_.push_back(3);
	index_.push_back(1);
}



void PlanePolygon::CreateMaterial()
{
	// �}�e���A���̐ݒ�
	ZeroMemory(&material_, sizeof(material_));	// �������̃A�h���X����sizeof()����0�Ŗ��߂�(�N���X�ɂ͎g��Ȃ�)

	// �}�e���A���J���[�𔒂ɂ���
	material_.Diffuse.r = 1.0f;
	material_.Diffuse.g = 1.0f;
	material_.Diffuse.b = 1.0f;
	material_.Diffuse.a = 1.0f;

	// �A���r�G���g�}�e���A���̐ݒ�
	material_.Ambient.r = 1.0f;
	material_.Ambient.g = 1.0f;
	material_.Ambient.b = 1.0f;
	material_.Ambient.a = 1.0f;
}



void PlanePolygon::AccessVRAM()
{
	// VRAM�̃��������m��(GPU�Ɉ˗�)(���_�o�b�t�@�̍쐬)
	HRESULT  hr = device_->CreateVertexBuffer(sizeof(RendererDirectX9::VERTEX_3D) * (int)vertex_.size(),	// �؂肽��baf�̗�(�o�C�g)�A�܂�1���_�̗e�ʁ~�K�v���_��
											  D3DUSAGE_WRITEONLY,											// �g�p�p�r(����͏������݂̂݁AGPU�������������������񂾃f�[�^��ǂ�ł̓_��(�l���s��))
											  RendererDirectX9::FVF_VERTEX_3D,								// ���_����
											  D3DPOOL_MANAGED,												// ���_�o�b�t�@�̊Ǘ����@( MANAGED�͊Ǘ���Direct3D�ɂ��C���Ƃ����Ӗ� )
											  &vertex_buffer_,												// �Ǘ��҂̋��ꏊ�̃�����(�|�C���^�̃|�C���^)(�S�Ă͂���̒l��m�邽�߂̍��)
											  NULL);

	if (FAILED(hr))
	{
		MessageBox(NULL, "Vertex buffer was not created.", "Error", MB_OK);
	}

	// VRAM�̃��������m��(GPU�Ɉ˗�)(�C���f�b�N�X�o�b�t�@�̍쐬)
	hr = device_->CreateIndexBuffer(sizeof(WORD) * (int)index_.size(),	// �؂肽��baf�̗�(�o�C�g)�A�܂�1���_�̗e�ʁ~�K�v���_��
									D3DUSAGE_WRITEONLY,					// �g�p�p�r(����͏������݂̂݁AGPU�������������������񂾃f�[�^��ǂ�ł̓_��(�l���s��))
									D3DFMT_INDEX16,						// ���_�t�H�[�}�b�g(WORD�^������16�ADWORD�^�Ȃ�32)
									D3DPOOL_MANAGED,					// ���_�o�b�t�@�̊Ǘ����@( MANAGED�͊Ǘ���Direct3D�ɂ��C���Ƃ����Ӗ� )
									&index_buffer_,						// �Ǘ��҂̋��ꏊ�̃�����(�|�C���^�̃|�C���^)(�S�Ă͂���̒l��m�邽�߂̍��)
									NULL);								// �Ȃ��H

	if (FAILED(hr))
	{
		MessageBox(NULL, "Index buffer was not created.", "Error", MB_OK);
	}

	RegistrationVertex();
	RegistrationIndex();
}



void PlanePolygon::RegistrationVertex()
{
	// ���_�̓o�^
	// ���z�A�h���X�����炤���_�|�C���^
	RendererDirectX9::VERTEX_3D* temp_vertex;

	// ���b�N����
	vertex_buffer_->Lock(0,						// �ǂ����烍�b�N��������
						 0,						// �ǂ̂��炢�؂肽����(0��VertexBuffer�S��)
						 (void**)&temp_vertex,	// ���b�N�����VRAM�̉��z�A�h���X�����炦��(���ۂɏ�������ł���킯�ł͂Ȃ�)
						 D3DLOCK_DISCARD);		// 0�ł��悢

	for (std::vector<RendererDirectX9::VERTEX_3D>::size_type i = 0; i < vertex_.size(); i++)
	{
		temp_vertex[i] = vertex_[i];
	}

	// �A�����b�N
	vertex_buffer_->Unlock();
}



void PlanePolygon::RegistrationIndex()
{
	// �C���f�b�N�X�̓o�^
	// ���z�A�h���X�����炤���_�|�C���^ 
	LPWORD temp_index;

	// ���b�N����
	index_buffer_->Lock(0,						// �ǂ����烍�b�N��������
						0,						// �ǂ̂��炢�؂肽����(0��VertexBuffer�S��)
						(void**)&temp_index,	// ���b�N�����VRAM�̉��z�A�h���X�����炦��(���ۂɏ�������ł���킯�ł͂Ȃ�)
						D3DLOCK_DISCARD);		// 0�ł��悢

	for (std::vector< WORD >::size_type i = 0; i < index_.size(); i++)
	{
		temp_index[i] = index_[i];

	}

	// �A�����b�N
	index_buffer_->Unlock();
}