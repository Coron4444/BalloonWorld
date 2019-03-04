//================================================================================
//!	@file	 CoinDraw.cpp
//!	@brief	 �R�C���`��Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../CoinDraw.h"
#include "../Coin.h"



//****************************************
// �萔��`
//****************************************
const std::string CoinDraw::TEXTURE_NAME = "Coin.png";



//****************************************
// �v���p�e�B��`
//****************************************
unsigned CoinDraw::getMeshNum(unsigned object_index)
{
	object_index = object_index;

	return plane_polygon_->getMeshNum();
}



MATRIX* CoinDraw::getpMatrix(unsigned object_index)
{
	object_index = object_index;

	return getpGameObject()->getpTransform()->getpWorldMatrix();
}



D3DMATERIAL9* CoinDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return plane_polygon_->getpMaterial();
}



LPDIRECT3DTEXTURE9 CoinDraw::getpDiffuseTexture(unsigned object_index,
														 unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return diffuse_texture_->getpHandler();
}



//****************************************
// �֐���`
//****************************************
void CoinDraw::Init()
{
	// �I�[�_�[���X�g�ݒ�
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::TRANSPARENCY);
	getpDrawOrderList()->getpRenderTargetFlag()->setFlag(DrawOrderList::RENDER_TARGET_MAIN);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::FIXED);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::FIXED);
	getpDrawOrderList()->setIsBillboard(true);

	// �_�E���L���X�g
	coin_ = (Coin*)getpGameObject();

	// �e�N�X�`���̓o�^
	diffuse_texture_ = TextureManager::getpInstance()->getpObject(&TEXTURE_NAME);

	// ���ʃ|���S���쐬
	plane_polygon_ = new PlanePolygon();
	plane_polygon_->Init();
}



void CoinDraw::Uninit()
{
	SafeRelease::PlusRelease(&diffuse_texture_);
	SafeRelease::PlusUninit(&plane_polygon_);
}



void CoinDraw::Update()
{
	if (!*coin_->getpIsColorChange()) return;
	*coin_->getpIsColorChange() = true;
	plane_polygon_->setColor(*coin_->getpColor());
}



void CoinDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	plane_polygon_->Draw();
}