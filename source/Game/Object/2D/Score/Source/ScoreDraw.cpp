//================================================================================
//!	@file	 ScoreDraw.h
//!	@brief	 �X�R�A�`��Class
//! @details 
//!	@author  Kai Araki									@date 2018/06/20
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../ScoreDraw.h"
#include "../Score.h"

#include <Resource/Polygon/NumbersPolygon.h>
#include <Resource/Polygon/PlanePolygon.h>
#include <Tool/SafeRelease.h>



//****************************************
// �萔��`
//****************************************
const std::string ScoreDraw::TEXTURE_NAME = "UI/Num.png";
const std::string ScoreDraw::TEXTURE_NAME2 = "UI/Score.png";
const int ScoreDraw::SCORE_DIGITS_NUM = 4;
const Vec2 ScoreDraw::SCORE_POSITION(70.0f, 300.0f);
const Vec2 ScoreDraw::SCORE_SCALE(50.0f, 40.0f);
const XColor4 ScoreDraw::SCORE_COLOR(0.0f, 0.0f, 0.0f, 1.0f);



//****************************************
// �v���p�e�B��`
//****************************************
unsigned ScoreDraw::getObjectNum()
{
	return numbers_polygon_->getObjectNum() + 1;
}



MATRIX* ScoreDraw::getpMatrix(unsigned object_index)
{
	if (object_index == 0)
	{
		return score_->getpTransform()->getpWorldMatrix();
	}
	return numbers_polygon_->getpMatrix(object_index - 1);
}



D3DMATERIAL9* ScoreDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	mesh_index = mesh_index;
	if (object_index == 0)
	{
		return plane_polygon_->getpMaterial();
	}
	return numbers_polygon_->getpMaterial(object_index - 1);
}



LPDIRECT3DTEXTURE9 ScoreDraw::getpDiffuseTexture(unsigned object_index,
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
void ScoreDraw::Init()
{
	// �I�[�_�[���X�g�ݒ�
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::TWO_DIMENSIONAL);
	getpDrawOrderList()->getpRenderTargetFlag()->setFlag(DrawOrderList::RENDER_TARGET_MAIN);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::FIXED);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::FIXED);

	// �_�E���L���X�g
	score_ = (Score*)getpGameObject();

	// �e�N�X�`���̓o�^
	texture_ = TextureManager::getpInstance()->getpObject(&TEXTURE_NAME);
	texture_2 = TextureManager::getpInstance()->getpObject(&TEXTURE_NAME2);

	// �����Q�|���S���쐬
	numbers_polygon_ = new NumbersPolygon();
	numbers_polygon_->Init(score_->getScore(), SCORE_DIGITS_NUM, true, SCORE_POSITION,
						   SCORE_SCALE, SCORE_COLOR, texture_);

	plane_polygon_ = new PlanePolygon();
	plane_polygon_->Init();
	score_->getpTransform()->getpPosition()->x = 0.0f;
	score_->getpTransform()->getpPosition()->y = 300.0f;
	float scale = 0.7f;
	score_->getpTransform()->getpScale()->x = texture_2->getWidth() * scale;
	score_->getpTransform()->getpScale()->y = texture_2->getHeight() * scale;
	score_->getpTransform()->CreateAxisAndWorldMatrix();
}



void ScoreDraw::Uninit()
{
	SafeRelease::PlusRelease(&texture_);
	SafeRelease::PlusRelease(&texture_2);
	SafeRelease::PlusUninit(&numbers_polygon_);
	SafeRelease::PlusUninit(&plane_polygon_);
}



void ScoreDraw::Update()
{
	numbers_polygon_->setNumber(score_->getScore());
}



void ScoreDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	mesh_index = mesh_index;
	if (object_index == 0)
	{
		return plane_polygon_->Draw();
	}
	return numbers_polygon_->Draw(object_index - 1);
}