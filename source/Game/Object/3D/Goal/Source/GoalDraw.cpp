//================================================================================
//!	@file	 GoalDraw.cpp
//!	@brief	 �S�[���`��Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/28
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../GoalDraw.h"

#include <Resource/Effekseer/EffekseerManager/EffekseerManager.h>
#include <Resource/Polygon/CubePolygon.h>
#include <Tool/SafeRelease.h>



//****************************************
// �萔��`
//****************************************
const std::string GoalDraw::EFFECT_NAME = "CoinEffect/CoinEffect.efk";



//****************************************
// �v���p�e�B��`
//****************************************
unsigned GoalDraw::getMeshNum(unsigned object_index)
{
	object_index = object_index;

	return cube_polygon_->getMeshNum();
}



MATRIX* GoalDraw::getpMatrix(unsigned object_index)
{
	object_index = object_index;

	return getpGameObject()->getpTransform()->getpWorldMatrix();
}



D3DMATERIAL9* GoalDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return cube_polygon_->getpMaterial();
}



//****************************************
// �֐���`
//****************************************
void GoalDraw::Init()
{
	// �I�[�_�[���X�g�ݒ�
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::TRANSPARENCY);
	getpDrawOrderList()->getpRenderTargetFlag()->setFlag(DrawOrderList::RENDER_TARGET_MAIN);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::FIXED);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::FIXED);

	// �L���[�u�|���S���̐���
	cube_polygon_ = new CubePolygon();
	cube_polygon_->Init(XColor4(0.5f, 1.0f, 1.0f, 1.0f));

	// �G�t�F�N�g�̓ǂݍ���
	effekseer_object_ = EffekseerManager::getpInstance()->getpObject(&EFFECT_NAME);
	effekseer_object_->ChangeColor(255, 255, 255, 255);
	*effekseer_object_->getpTransform()->getpPosition() = *getpGameObject()->getpTransform()->getpPosition();
	effekseer_object_->getpTransform()->CreateWorldMatrix();
	effekseer_object_->setIsRepeat(true);
	effekseer_object_->Play();
}



void GoalDraw::Uninit()
{
	SafeRelease::PlusUninit(&cube_polygon_);
	SafeRelease::PlusRelease(&effekseer_object_);
}



void GoalDraw::Update()
{
	// �G�t�F�N�g�X�V
	*effekseer_object_->getpTransform()->getpPosition() = *getpGameObject()->getpTransform()->getpPosition();
	effekseer_object_->getpTransform()->CreateWorldMatrix();
}



void GoalDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	cube_polygon_->Draw();
}