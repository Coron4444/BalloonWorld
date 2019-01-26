//================================================================================
//
//    �X�e���V���V���h�E�`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/03/27
//
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "StencilShadowTestDraw.h"

#include <main.h>

#include <Polygon\PlanePolygon\PlanePolygon.h>
#include <ModelX/ModelXManager/ModelXManager.h>



//****************************************
// �萔��`
//****************************************
const std::string StencilShadowTestDraw::MODEL_NAME = "knight_low/knight_low.X";



//****************************************
// ��ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +�������֐�
//--------------------------------------------------
void StencilShadowTestDraw::Init()
{
	// �I�[�_�[���X�g�ݒ�
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::TRANSPARENCY);
	getpDrawOrderList()->getpRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::FIXED);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::FIXED);

	// X���f���o�^
	player_model_ = ModelXManager::getpInstance()->getpObject(&MODEL_NAME);
	getpGameObject()->GetTransform()->GetPosition()->y += -1.0f;
	getpGameObject()->GetTransform()->UpdateWorldMatrixSRT();

	// �v���[���|���S���쐬
	plane_polygon_ = new PlanePolygon();
	plane_polygon_->SetColor(XColor4(0.0f, 0.0f, 0.0f, 1.0f));
	plane_polygon_transform_.GetScale()->x = SCREEN_WIDTH;
	plane_polygon_transform_.GetScale()->y = SCREEN_HEIGHT;
	plane_polygon_transform_.UpdateWorldMatrixSRT();
}



//--------------------------------------------------
// +�I���֐�
//--------------------------------------------------
void StencilShadowTestDraw::Uninit()
{
	// �e��J��
	SafeRelease::Normal(&plane_polygon_);
	SafeRelease::PlusRelease(&player_model_);
}



//--------------------------------------------------
// +�`��֐�
//--------------------------------------------------
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



//--------------------------------------------------
// +�`��O�ݒ�֐�
//--------------------------------------------------
void StencilShadowTestDraw::SettingBeforeDrawing(Camera* camera, unsigned object_index)
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
			DrawBase::LimitedChangeCameraType(camera, Camera::Type::TWO_DIMENSIONAL);
			device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
			device->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);
			device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
			break;
		}
	}
}



//--------------------------------------------------
// +�`���ݒ�֐�
//--------------------------------------------------
void StencilShadowTestDraw::SettingAfterDrawing(Camera* camera, unsigned object_index)
{
	if (object_index == 2)
	{
		LPDIRECT3DDEVICE9 device;
		Renderer::getpInstance()->getDevice(&device);
		DrawBase::RevivalCameraType(camera);
		device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		device->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	}
}



//--------------------------------------------------
// +�I�u�W�F�N�g���擾�֐�
//--------------------------------------------------
unsigned StencilShadowTestDraw::getObjectNum()
{
	return 3;
}



//--------------------------------------------------
// +���b�V�����擾�֐�
//--------------------------------------------------
unsigned StencilShadowTestDraw::getMeshNum(unsigned object_index)
{
	if (object_index == 2) return 1;

	return player_model_->getMeshNum();
}



//--------------------------------------------------
// +�s��擾�֐�
//--------------------------------------------------
MATRIX* StencilShadowTestDraw::getpMatrix(unsigned object_index)
{
	if (object_index == 2)
	{
		return plane_polygon_transform_.getpWorldMatrix();
	}
	
	return getpGameObject()->GetTransform()->getpWorldMatrix();
}



//--------------------------------------------------
// +�}�e���A���擾�֐�
//--------------------------------------------------
D3DMATERIAL9* StencilShadowTestDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	if (object_index == 2) return nullptr;

	object_index = object_index;

	return player_model_->getpMaterial(mesh_index);
}



//--------------------------------------------------
// +�f�B�q���[�Y�e�N�X�`���擾�֐�
//--------------------------------------------------
LPDIRECT3DTEXTURE9 StencilShadowTestDraw::getpDiffuseTexture(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;

	if (object_index == 2) return nullptr;

	return player_model_->getpDiffuseTextureObject(mesh_index)->getpHandler();
}