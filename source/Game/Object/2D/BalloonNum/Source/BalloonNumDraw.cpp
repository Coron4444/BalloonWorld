//================================================================================
//!	@file	 BalloonNumDraw.cpp
//!	@brief	 ���D���`��Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../BalloonNumDraw.h"
#include "../BalloonNum.h"

#include <Resource/Polygon/NumbersPolygon.h>
#include <Resource/Polygon/PlanePolygon.h>
#include <Tool/SafeRelease.h>



//****************************************
// �萔��`
//****************************************
const std::string BalloonNumDraw::TEXTURE_NAME = "UI/Num.png";
const std::string BalloonNumDraw::TEXTURE_NAME2 = "UI/BalloonNum.png";
const int BalloonNumDraw::BALLOON_NUM_DIGITS_NUM = 1;
const Vec2 BalloonNumDraw::BALLOON_NUM_POSITION(-400.0f, -270.0f);
const Vec2 BalloonNumDraw::BALLOON_NUM_SCALE(100.0f, 70.0f);
const XColor4 BalloonNumDraw::BALLOON_NUM_COLOR(1.0f, 1.0f, 1.0f, 1.0f);



//****************************************
// �v���p�e�B��`
//****************************************
unsigned BalloonNumDraw::getObjectNum()
{
	return numbers_polygon_->getObjectNum() + 1;
}



MATRIX* BalloonNumDraw::getpMatrix(unsigned object_index)
{
	if (object_index == 0)
	{
		return balloon_num_->getpTransform()->getpWorldMatrix();
	}
	return numbers_polygon_->getpMatrix(object_index - 1);
}



D3DMATERIAL9* BalloonNumDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	mesh_index = mesh_index;
	if (object_index == 0)
	{
		return plane_polygon_->getpMaterial();
	}
	return numbers_polygon_->getpMaterial(object_index - 1);
}



LPDIRECT3DTEXTURE9 BalloonNumDraw::getpDiffuseTexture(unsigned object_index,
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
void BalloonNumDraw::Init()
{
	// �I�[�_�[���X�g�ݒ�
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::TWO_DIMENSIONAL);
	getpDrawOrderList()->getpRenderTargetFlag()->setFlag(DrawOrderList::RENDER_TARGET_MAIN);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::FIXED);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::FIXED);

	// �_�E���L���X�g
	balloon_num_ = (BalloonNum*)getpGameObject();

	// �e�N�X�`���̓o�^
	texture_ = TextureManager::getpInstance()->getpObject(&TEXTURE_NAME);
	texture_2 = TextureManager::getpInstance()->getpObject(&TEXTURE_NAME2);

	// �����Q�|���S���쐬
	numbers_polygon_ = new NumbersPolygon();
	numbers_polygon_->Init(balloon_num_->getBalloonNum(), BALLOON_NUM_DIGITS_NUM, 
						   true, BALLOON_NUM_POSITION, BALLOON_NUM_SCALE,
						   BALLOON_NUM_COLOR, texture_);

	plane_polygon_ = new PlanePolygon();
	plane_polygon_->Init();
	balloon_num_->getpTransform()->getpPosition()->x = -530.0f;
	balloon_num_->getpTransform()->getpPosition()->y = -250.0f;
	float scale = 0.7f;
	balloon_num_->getpTransform()->getpScale()->x = texture_2->getWidth() * scale;
	balloon_num_->getpTransform()->getpScale()->y = texture_2->getHeight() * scale;
	balloon_num_->getpTransform()->CreateWorldMatrix();
}



void BalloonNumDraw::Uninit()
{
	SafeRelease::PlusRelease(&texture_);
	SafeRelease::PlusRelease(&texture_2);
	SafeRelease::PlusUninit(&numbers_polygon_);
	SafeRelease::PlusUninit(&plane_polygon_);
}



void BalloonNumDraw::Update()
{
	numbers_polygon_->setNumber(balloon_num_->getBalloonNum());
}



void BalloonNumDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	mesh_index = mesh_index;
	if (object_index == 0)
	{
		return plane_polygon_->Draw();
	}
	return numbers_polygon_->Draw(object_index - 1);
}