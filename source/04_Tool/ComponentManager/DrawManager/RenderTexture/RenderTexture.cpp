//================================================================================
//!	@file	 RenderTexture.cpp
//!	@brief	 �����_���[�e�N�X�`��Class
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "RenderTexture.h"

#include <Renderer\RendererDirectX9\RendererDirectX9.h>
#include <SafeRelease/SafeRelease.h>
#include <Vector\ConvertToFrame\TimeToFrame\TimeToFrame.h>
#include <Transform\Transform.h>
#include <Polygon\PlanePolygon\PlanePolygon.h>



//****************************************
// �v���p�e�B��`
//****************************************
MATRIX* RenderTexture::getpMatrix(unsigned object_index)
{
	object_index = object_index;
	return transform_->getpMatrixExtend()->GetWorldMatrix();
}



D3DMATERIAL9* RenderTexture::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;
	return plane_polygon_->GetMaterial();
}



//****************************************
// �֐���`
//****************************************
void RenderTexture::Init()
{
	plane_polygon_ = new PlanePolygon();
	transform_ = new Transform();
}



void RenderTexture::Uninit()
{
	SafeRelease::Normal(&plane_polygon_);
	SafeRelease::Normal(&transform_);
}



void RenderTexture::Update(float x, float y, XColor4 color)
{
	transform_->GetPosition()->x = -0.5f;
	transform_->GetPosition()->y = -0.5f;
	transform_->GetScale()->x = x;
	transform_->GetScale()->y = y;
	transform_->UpdateWorldMatrixSRT();

	plane_polygon_->SetColor(color);
}



void RenderTexture::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	// �|���S���`��
	plane_polygon_->Draw();
}