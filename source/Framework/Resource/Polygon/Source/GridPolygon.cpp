//================================================================================
//!	@file	 GridPolygon.cpp
//!	@brief	 �O���b�h�|���S��Class
//! @details 
//!	@author  Kai Araki									@date 2017/10/23
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../GridPolygon.h"



//****************************************
// �֐���`
//****************************************
void GridPolygon::Init()
{
	CreateVertex();
	CreateMaterial();

	Renderer::getpInstance()->getDevice(&device_);
	if (device_ == nullptr)
	{
		MessageBox(nullptr, "NotGetDevice!(GridPolygon.cpp)", "Error", MB_OK);
		return;
	}
}



void GridPolygon::Uninit()
{
}



void GridPolygon::Draw()
{
	// FVF�̐ݒ�(�f�o�C�X�̕��ɒ��_�̑�����������)
	device_->SetFVF(RendererDirectX9::FVF_VERTEX_3D);

	// �e�N�X�`����OFF
	device_->SetTexture(0, NULL);

	// �}�e���A�����f�o�C�X�ɃZ�b�g
	device_->SetMaterial(&material_);

	// ���C�e�B���O��OFF�ɂ���
	device_->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �O���b�h
	device_->DrawPrimitiveUP(D3DPT_LINELIST, 
							 vertex_.size() / 2, 
							 &vertex_[0], 
							 sizeof(RendererDirectX9::VERTEX_3D));

	// ���C�e�B���O��ON�ɂ���
	device_->SetRenderState(D3DRS_LIGHTING, TRUE);
}



void GridPolygon::CreateVertex()
{
	// ���_�f�[�^�쐬
	constexpr int   vertexMax = 44;
	constexpr float endPos = 5.0f;
	constexpr float interval_grid = 1.0f;

	vertex_.resize(vertexMax);

	int tempAdd = 0;

	// ����
	for (int i = 0; i < vertexMax / 2 - 1; i += 2)
	{
		float posX = -endPos + tempAdd * interval_grid;

		vertex_[i].posisiont_ = Vec3(posX, -endPos, 0.0f);
		vertex_[i + 1].posisiont_ = Vec3(posX, endPos, 0.0f);

		vertex_[i].color_ = 0xff00ff00;
		vertex_[i + 1].color_ = 0xff00ff00;

		tempAdd++;
	}

	tempAdd = 0;

	// �c��
	for (int i = vertexMax / 2; i < vertexMax - 1; i += 2)
	{
		float posY = -endPos + tempAdd * interval_grid;
		vertex_[i].posisiont_ = Vec3(-endPos, posY, 0.0f);
		vertex_[i + 1].posisiont_ = Vec3(endPos, posY, 0.0f);

		vertex_[i].color_ = 0xffff0000;
		vertex_[i + 1].color_ = 0xffff0000;

		tempAdd++;
	}
}



void GridPolygon::CreateMaterial()
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