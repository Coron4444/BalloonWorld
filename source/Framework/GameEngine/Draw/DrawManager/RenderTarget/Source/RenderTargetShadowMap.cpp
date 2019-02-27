//================================================================================
//!	@file	 RenderTargetShadowMap.cpp
//!	@brief	 �����_�[�^�[�Q�b�g�V���h�E�}�b�vClass
//! @details 
//!	@author  Kai Araki									@date 2019/02/20
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../RenderTargetShadowMap.h"
#include "../../Shader/ShaderManager/ShaderManager.h"
#include "../../../DrawBase.h"
#include "../../../Camera/Camera.h"
#include "../../../../GameObject/GameObjectBase.h"



//****************************************
// �v���p�e�B��`
//****************************************
void RenderTargetShadowMap::setCamera(Camera* value)
{
	camera_ = value;
}



void RenderTargetShadowMap::setDrawCommonData(DrawCommonData* value)
{
	common_data_ = value;
}



void RenderTargetShadowMap::setShaderManager(ShaderManager* value)
{
	shader_manager_ = value;
}



//****************************************
// �֐���`
//****************************************
void RenderTargetShadowMap::Init()
{
	Reset();
}



void RenderTargetShadowMap::Uninit()
{
	Reset();
}



void RenderTargetShadowMap::UninitWhenChangeScene()
{
	Reset();
}



void RenderTargetShadowMap::Update()
{
	// �r���{�[�h�X�V
	AllBillboardUpdate();
}



void RenderTargetShadowMap::Draw()
{
	// �����_�[�^�[�Q�b�g�̐؂�ւ�
	common_data_->getpRenderTextureShadowMap()->setRenderTarget(0);
	common_data_->getpRenderTextureShadowMap()->setStencilSurfaceAndViewPort();
	bool is_begin = Renderer::getpInstance()->DrawBegin(XColor4(0.0f, 0.0f, 0.0f, 1.0f));

	// �J�����ݒ�
	ChangeCameraType(Camera::Type::PERSPECTIVE);

	for (unsigned i = 0; i < draw_.getEndIndex(); i++)
	{
		// �V�F�[�_�[�Z�b�g
		if (draw_.getObject(i)->getpDrawOrderList()->getIsAnimation())
		{
			shader_manager_->ShaderSetToDevice(draw_.getObject(i),
											   ShaderManager::VertexShaderType::SHADOW_MAP,
											   ShaderManager::PixelShaderType::SHADOW_MAP);
		}
		else
		{
			shader_manager_->ShaderSetToDevice(draw_.getObject(i),
											   ShaderManager::VertexShaderType::SHADOW_MAP,
											   ShaderManager::PixelShaderType::SHADOW_MAP);
			//shader_manager_->ShaderSetToDevice(draw_.getObject(i),
			//								   ShaderManager::VertexShaderType::NONE,
			//								   ShaderManager::PixelShaderType::NONE);
		}
		
		// �e�I�u�W�F�N�g�`��
		for (unsigned j = 0; j < draw_.getObject(i)->getObjectNum(); j++)
		{
			// �I�u�W�F�N�g�O�ݒ�
			draw_.getObject(i)->ObjectSettingBefore(j);
			shader_manager_->ObjectSetting(draw_.getObject(i), camera_, j);

			// �e���b�V���`��
			for (unsigned k = 0; k < draw_.getObject(i)->getMeshNum(j); k++)
			{
				// ���b�V���ݒ�
				shader_manager_->MeshSetting(draw_.getObject(i), camera_, j, k);

				draw_.getObject(i)->Draw(j, k);
			}

			// �I�u�W�F�N�g��ݒ�
			draw_.getObject(i)->ObjectSettingAfter(j);
		}
	}

	Renderer::getpInstance()->DrawEnd(is_begin);
}



void RenderTargetShadowMap::AddDrawBaseToArray(DrawBase* draw)
{
	switch (draw->getpDrawOrderList()->getDrawType())
	{
		case DrawOrderList::DrawType::OPACITY:
		case DrawOrderList::DrawType::TRANSPARENCY:
		{
			draw_.AddToArray(draw);
			break;
		}
	}
}



void RenderTargetShadowMap::Reset()
{
	draw_.Reset();
}



void RenderTargetShadowMap::ChangeBillboardMatrix(DrawBase* draw)
{
	// �r���[�s��̓]�u�s����Z�b�g
	draw->getpGameObject()->getpTransform()->setTransposeMatrix(camera_->getpViewMatrix(),
																true);
	// ���[���h�s��̍X�V
	draw->getpGameObject()->getpTransform()->CreateWorldMatrixPlusTranspose();
}



void RenderTargetShadowMap::AllBillboardUpdate()
{
	camera_->setType(Camera::Type::PERSPECTIVE);

	for (unsigned i = 0; i < draw_.getEndIndex(); i++)
	{
		if (!draw_.getObject(i)->getpDrawOrderList()->getIsBillboard()) continue;
		ChangeBillboardMatrix(draw_.getObject(i));
	}
}



void RenderTargetShadowMap::ChangeCameraType(Camera::Type camera_type)
{
	save_camera_type_ = camera_type;
	camera_->setType(camera_type);
}