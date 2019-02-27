//================================================================================
//!	@file	 StencilShadowTestDraw.cpp
//!	@brief	 �X�e���V���V���h�E�e�X�g�`��Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../StencilShadowTestDraw.h"



//****************************************
// �萔��`
//****************************************
const std::string StencilShadowTestDraw::MODEL_NAME = "knight_low/knight_low.X";


//****************************************
// �v���p�e�B��`
//****************************************
unsigned StencilShadowTestDraw::getObjectNum()
{
	return 3;
}



unsigned StencilShadowTestDraw::getMeshNum(unsigned object_index)
{
	if (object_index == 2) return 1;

	return player_model_->getMeshNum();
}



MATRIX* StencilShadowTestDraw::getpMatrix(unsigned object_index)
{
	if (object_index == 2)
	{
		return plane_polygon_transform_.getpWorldMatrix();
	}

	return getpGameObject()->getpTransform()->getpWorldMatrix();
}



D3DMATERIAL9* StencilShadowTestDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	if (object_index == 2) return nullptr;

	object_index = object_index;

	return player_model_->getpMaterial(mesh_index);
}



LPDIRECT3DTEXTURE9 StencilShadowTestDraw::getpDiffuseTexture(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;

	if (object_index == 2) return nullptr;

	return player_model_->getpDiffuseTextureObject(mesh_index)->getpHandler();
}



//****************************************
// �֐���`
//****************************************
void StencilShadowTestDraw::Init()
{
	// �I�[�_�[���X�g�ݒ�
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::TRANSPARENCY);
	getpDrawOrderList()->getpRenderTargetFlag()->setFlag(DrawOrderList::RENDER_TARGET_MAIN);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::FIXED);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::FIXED);

	// X���f���o�^
	player_model_ = ModelXManager::getpInstance()->getpObject(&MODEL_NAME);
	getpGameObject()->getpTransform()->getpPosition()->y += -1.0f;
	getpGameObject()->getpTransform()->CreateWorldMatrix();

	// �v���[���|���S���쐬
	plane_polygon_ = new PlanePolygon();
	plane_polygon_->Init();
	plane_polygon_->setColor(XColor4(0.0f, 0.0f, 0.0f, 1.0f));
	plane_polygon_transform_.getpScale()->x = (float)GameEngine::SCREEN_WIDTH;
	plane_polygon_transform_.getpScale()->y = (float)GameEngine::SCREEN_HEIGHT;
	plane_polygon_transform_.CreateWorldMatrix();
}



void StencilShadowTestDraw::Uninit()
{
	SafeRelease::PlusUninit(&plane_polygon_);
	SafeRelease::PlusRelease(&player_model_);
}



void StencilShadowTestDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	if (object_index != 2)
	{
		player_model_->getpMesh()->DrawSubset(mesh_index);
	}
	else
	{	
		// �|���S���`��
		plane_polygon_->Draw();
	}
}



void StencilShadowTestDraw::ObjectSettingBefore(unsigned object_index)
{
	LPDIRECT3DDEVICE9 device;
	Renderer::getpInstance()->getDevice(&device);
	switch (object_index)
	{
		case 0: 
		{
			device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
			device->SetRenderState(D3DRS_STENCILENABLE, TRUE);
			device->SetRenderState(D3DRS_COLORWRITEENABLE, 0);
			device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
			device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);
			device->SetRenderState(D3DRS_STENCILREF, 1);
			device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
			break;
		}
		case 1:
		{
			device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_DECR);
			device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
			break;
		}
		case 2:
		{
			getpDrawOrderList()->setTempChangeDrawType(DrawOrderList::DrawType::TWO_DIMENSIONAL);
			device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
			device->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);
			device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
			break;
		}
	}
}



void StencilShadowTestDraw::ObjectSettingAfter(unsigned object_index)
{
	if (object_index == 2)
	{
		LPDIRECT3DDEVICE9 device;
		Renderer::getpInstance()->getDevice(&device);
		device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		device->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	}
}