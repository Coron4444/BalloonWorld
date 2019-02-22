//================================================================================
//!	@file	 TimeDraw.cpp
//!	@brief	 ���ԕ`��Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../TimeDraw.h"
#include "../Time.h"

#include <Resource/Polygon/NumbersPolygon.h>
#include <Resource/Polygon/PlanePolygon.h>
#include <Tool/SafeRelease.h>



//****************************************
// �萔��`
//****************************************
const std::string TimeDraw::TEXTURE_NAME = "UI/Num.png";
const std::string TimeDraw::TEXTURE_NAME2 = "UI/Time.png";
const int TimeDraw::TIME_DIGITS_NUM = 2;
const Vec2 TimeDraw::TIME_POSITION(-450.0f, 300.0f);
const Vec2 TimeDraw::TIME_SCALE(50.0f, 40.0f);
const XColor4 TimeDraw::TIME_COLOR(0.0f, 0.0f, 0.0f, 1.0f);



//****************************************
// �v���p�e�B��`
//****************************************
unsigned TimeDraw::getObjectNum()
{
	return numbers_polygon_->getObjectNum() + 1;
}



MATRIX* TimeDraw::getpMatrix(unsigned object_index)
{
	if (object_index == 0)
	{
		return time_->getpTransform()->getpWorldMatrix();
	}
	return numbers_polygon_->getpMatrix(object_index - 1);
}



D3DMATERIAL9* TimeDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	mesh_index = mesh_index;
	if (object_index == 0)
	{
		return plane_polygon_->getpMaterial();
	}
	return numbers_polygon_->getpMaterial(object_index - 1);
}



LPDIRECT3DTEXTURE9 TimeDraw::getpDiffuseTexture(unsigned object_index,
														 unsigned mesh_index)
{
	mesh_index = mesh_index;
	if (object_index == 0)
	{
		return texture_2->getpHandler();
	}
	return texture_->getpHandler();
}



//****************************************
// �֐���`
//****************************************
void TimeDraw::Init()
{
	// �I�[�_�[���X�g�ݒ�
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::TWO_DIMENSIONAL);
	getpDrawOrderList()->getpRenderTargetFlag()->setFlag(DrawOrderList::RENDER_TARGET_MAIN);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::FIXED);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::FIXED);

	// �_�E���L���X�g
	time_ = (Time*)getpGameObject();

	// �e�N�X�`���̓o�^
	texture_ = TextureManager::getpInstance()->getpObject(&TEXTURE_NAME);
	texture_2 = TextureManager::getpInstance()->getpObject(&TEXTURE_NAME2);

	// �����Q�|���S���쐬
	numbers_polygon_ = new NumbersPolygon();
	numbers_polygon_->Init(time_->getTime(), TIME_DIGITS_NUM, true, TIME_POSITION,
						   TIME_SCALE, TIME_COLOR, texture_);

	plane_polygon_ = new PlanePolygon();
	plane_polygon_->Init();
	time_->getpTransform()->getpPosition()->x = -500.0f;
	time_->getpTransform()->getpPosition()->y = 300.0f;
	float scale = 0.4f;
	time_->getpTransform()->getpScale()->x = texture_2->getWidth() * scale;
	time_->getpTransform()->getpScale()->y = texture_2->getHeight() * scale;
	time_->getpTransform()->CreateAxisAndWorldMatrix();
}



void TimeDraw::Uninit()
{
	SafeRelease::PlusRelease(&texture_);
	SafeRelease::PlusRelease(&texture_2);
	SafeRelease::PlusUninit(&numbers_polygon_);
	SafeRelease::PlusUninit(&plane_polygon_);
}



void TimeDraw::Update()
{
	numbers_polygon_->setNumber(time_->getTime());
}



void TimeDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	mesh_index = mesh_index;
	if (object_index == 0)
	{
		return plane_polygon_->Draw();
	}
	return numbers_polygon_->Draw(object_index - 1);
}