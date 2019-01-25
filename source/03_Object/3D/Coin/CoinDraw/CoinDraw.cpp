//================================================================================
//!	@file	 CoinDraw.cpp
//!	@brief	 �R�C���`��Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "CoinDraw.h"

#include <SafeRelease/SafeRelease.h>
#include <Texture/TextureManager/TextureManager.h>



//****************************************
// �萔��`
//****************************************
const std::string CoinDraw::diffuse_TEXTURE = "Coin.png";



//****************************************
// �֐���`
//****************************************
//--------------------------------------------------
// +�������֐�
//--------------------------------------------------
void CoinDraw::Init()
{
	// �I�[�_�[���X�g�ݒ�
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::TRANSPARENCY);
	getpDrawOrderList()->getpRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::FIXED);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::FIXED);
	getpDrawOrderList()->setIsBillboard(true);

	// �_�E���L���X�g
	coin_ = (Coin*)getpGameObject();

	// �f�B�q���[�Y�e�N�X�`���̓ǂݍ���
	diffuse_texture_ = TextureManager::getpInstance()->getpObject(&diffuse_TEXTURE);
}



//--------------------------------------------------
// +�I���֐�
//--------------------------------------------------
void CoinDraw::Uninit()
{
	SafeRelease::PlusRelease(&diffuse_texture_);
}



//--------------------------------------------------
// +�X�V�֐�
//--------------------------------------------------
void CoinDraw::Update()
{
	if (coin_->getCount() > 0)
	{
		coin_->GetPolygon()->SetColor(XColor4(1.0f, 0.0f, 0.0f, 1.0f));

		coin_->setCount(coin_->getCount() - 1);
	}
	else
	{
		coin_->GetPolygon()->SetColor(XColor4(1.0f, 1.0f, 1.0f, 1.0f));
	}
}



//--------------------------------------------------
// +�`��֐�
//--------------------------------------------------
void CoinDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	// �|���S���`��
	coin_->GetPolygon()->Draw();
}



//--------------------------------------------------
// +�`��O�ݒ�֐�
//--------------------------------------------------
void CoinDraw::SettingBeforeDrawing(Camera* camera, unsigned object_index)
{
	camera = camera;
	object_index = object_index;
}



//--------------------------------------------------
// +���b�V�����擾�֐�
//--------------------------------------------------
unsigned CoinDraw::getMeshNum(unsigned object_index)
{
	object_index = object_index;

	return coin_->GetPolygon()->getMeshNum();
}



//--------------------------------------------------
// +�s��擾�֐�
//--------------------------------------------------
MATRIX* CoinDraw::getpMatrix(unsigned object_index)
{
	object_index = object_index;

	return coin_->GetTransform()->getpWorldMatrix();
}



//--------------------------------------------------
// +�}�e���A���擾�֐�
//--------------------------------------------------
D3DMATERIAL9* CoinDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return coin_->GetPolygon()->GetMaterial();
}



//--------------------------------------------------
// +�f�B�q���[�Y�e�N�X�`���擾�֐�
//--------------------------------------------------
LPDIRECT3DTEXTURE9 CoinDraw::getpDiffuseTexture(unsigned object_index,
											   unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return diffuse_texture_->getpHandler();
}