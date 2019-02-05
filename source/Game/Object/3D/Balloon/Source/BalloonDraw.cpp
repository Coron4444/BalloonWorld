//================================================================================
//!	@file	 BalloonDraw.cpp
//!	@brief	 ���D�`��Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/05
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../BalloonDraw.h"

#include <GameEngine/Draw/DrawManager/Shader/VertexShader/VertexShaderBumpMapping.h>
#include <Resource/MdBin/MdBinManager/MdBinManager.h>
#include <Resource/ModelX/ModelXManager/ModelXManager.h>
#include <Resource/Texture/TextureManager/TextureManager.h>
#include <Tool/SafeRelease.h>



//****************************************
// �萔��`
//****************************************
const std::string BalloonDraw::MODEL_NAME = "sen/sen.x";



//****************************************
// �v���p�e�B��`
//****************************************
unsigned BalloonDraw::getMeshNum(unsigned object_index)
{
	object_index = object_index;

	return object_->getMeshNum();
}



MATRIX* BalloonDraw::getpMatrix(unsigned object_index)
{
	object_index = object_index;

	return getpGameObject()->getpTransform()->getpWorldMatrix();
}



D3DMATERIAL9* BalloonDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;

	return object_->getpMaterial(mesh_index);
}



LPDIRECT3DTEXTURE9 BalloonDraw::getpDiffuseTexture(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return nullptr;// object_->getpDiffuseTextureObject(mesh_index)->getpHandler();
}



//****************************************
// �֐���`
//****************************************
void BalloonDraw::Init()
{
	// �I�[�_�[���X�g�ݒ�
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::OPACITY);
	getpDrawOrderList()->getpRenderTargetFlag()->setFlag(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::FIXED);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::FIXED);

	// �I�u�W�F�N�g�擾
	object_ = ModelXManager::getpInstance()->getpObject(&MODEL_NAME);
}



void BalloonDraw::Uninit()
{
	SafeRelease::PlusRelease(&object_);
}



void BalloonDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	object_->getpMesh()->DrawSubset(mesh_index);
}