//================================================================================
//!	@file	 RenderTargetMain.cpp
//!	@brief	 �����_�[�^�[�Q�b�g���C��Class
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../RenderTargetMain.h"
#include "../../Shader/ShaderManager/ShaderManager.h"
#include "../../../DrawBase.h"
#include "../../../Camera/Camera.h"
#include "../../../../GameObject/GameObjectBase.h"

#include <Resource/Effekseer/EffekseerManager/EffekseerManager.h>
#include <Tool/SafeRelease.h>



//****************************************
// �v���p�e�B��`
//****************************************
void RenderTargetMain::setCamera(Camera* value)
{
	camera_ = value;
}



void RenderTargetMain::setDrawCommonData(DrawCommonData* value)
{
	common_data_ = value;
}



void RenderTargetMain::setShaderManager(ShaderManager* value)
{
	shader_manager_ = value;
}



//****************************************
// �֐���`
//****************************************
void RenderTargetMain::Init()
{
	Reset();
}



void RenderTargetMain::Uninit()
{
	Reset();
}



void RenderTargetMain::UninitWhenChangeScene()
{
	Reset();
}



void RenderTargetMain::Update()
{
	// �\�[�g
	SortTransparent();
	Sort2D();

	// �r���{�[�h�X�V
	AllBillboardUpdate();

	// �G�t�F�N�V�A�̍X�V
	EffekseerManager::getpInstance()->CreateViewMatrix(*camera_->getpPositon(),
													   *camera_->getpLookAtPoint(),
													   *camera_->getpUp());
	EffekseerManager::getpInstance()->CreateProjectionMatrix(camera_->getAngleOfView());
	EffekseerManager::getpInstance()->Update();
}



void RenderTargetMain::Draw()
{
	// �����_�[�^�[�Q�b�g�̐؂�ւ�
	LPDIRECT3DDEVICE9 device;
	Renderer::getpInstance()->getDevice(&device);
	common_data_->getpRenderTextureMain()->setRenderTarget(0);
	bool is_begin = Renderer::getpInstance()->DrawBegin();

	// �`��
	DrawOpacity();
	DrawTransparent();
	EffekseerManager::getpInstance()->Draw();
	Draw2D();

	Renderer::getpInstance()->DrawEnd(is_begin);
}



void RenderTargetMain::AddDrawBaseToArray(DrawBase* draw)
{
	switch (draw->getpDrawOrderList()->getDrawType())
	{
		case DrawOrderList::DrawType::OPACITY:
		{
			draw_opacity_.AddToArray(draw);
			break;
		}
		case DrawOrderList::DrawType::TRANSPARENCY:
		{
			draw_transparent_.AddToArray(draw);
			break;
		}
		case DrawOrderList::DrawType::TWO_DIMENSIONAL:
		{
			draw_2D_.AddToArray(draw);
			break;
		}
	}
}



void RenderTargetMain::Reset()
{
	draw_opacity_.Reset();
	draw_transparent_.Reset();
	draw_2D_.Reset();
}



void RenderTargetMain::SortTransparent()
{
	// �����I�u�W�F�N�g�����邩�ǂ���
	if (draw_transparent_.getEndIndex() <= 0) return;

	for (unsigned i = 0; i < draw_transparent_.getEndIndex() - 1; i++)
	{
		// �[�x�l���Z�o
		Vector3D temp_vector0 = *draw_transparent_.getObject(i)->getpGameObject()
			->getpTransform()->getpPosition() - *camera_->getpPositon();

		float depth_value0 = temp_vector0.getLengthSquare();

		for (unsigned j = i + 1; j < draw_transparent_.getEndIndex(); j++)
		{
			// �[�x�l���Z�o
			Vector3D temp_vector1 = *draw_transparent_.getObject(j)->getpGameObject()
				->getpTransform()->getpPosition() - *camera_->getpPositon();

			float depth_value1 = temp_vector1.getLengthSquare();

			// �[�x�l���r
			if (depth_value0 < depth_value1)
			{
				// ���ёւ�
				draw_transparent_.SortTheTwoObject(i, j);
			}
		}
	}
}



void RenderTargetMain::Sort2D()
{
	// 2D�I�u�W�F�N�g�����邩�ǂ���
	if (draw_2D_.getEndIndex() <= 0) return;

	for (unsigned i = 0; i < draw_2D_.getEndIndex() - 1; i++)
	{
		for (unsigned j = i + 1; j < draw_2D_.getEndIndex(); j++)
		{
			if (draw_2D_.getObject(i)->getpDrawOrderList()->getLayerNum()
				> draw_2D_.getObject(j)->getpDrawOrderList()->getLayerNum())
			{
				// ���ёւ�
				draw_2D_.SortTheTwoObject(i, j);
			}
		}
	}
}



void RenderTargetMain::ChangeBillboardMatrix(DrawBase* draw)
{
	// �r���[�s��̓]�u�s����Z�b�g
	draw->getpGameObject()->getpTransform()->setTransposeMatrix(camera_->getpViewMatrix(),
																true);
	// ���[���h�s��̍X�V
	draw->getpGameObject()->getpTransform()->CreateAxisAndWorldMatrixPlusTranspose();
}



void RenderTargetMain::AllBillboardUpdate()
{
	camera_->setType(Camera::Type::PERSPECTIVE);

	// �s�����I�u�W�F�N�g
	for (unsigned i = 0; i < draw_opacity_.getEndIndex(); i++)
	{
		if (!draw_opacity_.getObject(i)->getpDrawOrderList()->getIsBillboard()) continue;
		ChangeBillboardMatrix(draw_opacity_.getObject(i));
	}

	// �����I�u�W�F�N�g
	for (unsigned i = 0; i < draw_transparent_.getEndIndex(); i++)
	{
		if (!draw_transparent_.getObject(i)->getpDrawOrderList()->getIsBillboard()) continue;
		ChangeBillboardMatrix(draw_transparent_.getObject(i));
	}
}



void RenderTargetMain::ChangeCameraType(Camera::Type camera_type)
{
	save_camera_type_ = camera_type;
	camera_->setType(camera_type);
}



void RenderTargetMain::TempChangeCameraType(DrawBase* draw)
{
	switch (draw->getpDrawOrderList()->getTempChangeDrawType())
	{
		case DrawOrderList::DrawType::OPACITY:
		case DrawOrderList::DrawType::TRANSPARENCY:
		{
			camera_->setType(Camera::Type::PERSPECTIVE);
			break;
		}
		case DrawOrderList::DrawType::TWO_DIMENSIONAL:
		{
			camera_->setType(Camera::Type::TWO_DIMENSIONAL);
			break;
		}
	}
}


void RenderTargetMain::RevertTempChangeCameraType(DrawBase* draw)
{
	if (draw->getpDrawOrderList()
		->getTempChangeDrawType() == DrawOrderList::DrawType::NONE) return;

	camera_->setType(save_camera_type_);
	draw->getpDrawOrderList()
		->setTempChangeDrawType(DrawOrderList::DrawType::NONE);
}



void RenderTargetMain::DrawOpacity()
{
	// �J�����ݒ�
	ChangeCameraType(Camera::Type::PERSPECTIVE);
	
	for (unsigned i = 0; i < draw_opacity_.getEndIndex(); i++)
	{
		// �V�F�[�_�[�Z�b�g
		shader_manager_->ShaderSetToDevice(draw_opacity_.getObject(i),
										   ShaderManager::VertexShaderType::NONE,
										   ShaderManager::PixelShaderType::NONE);

		// �e�I�u�W�F�N�g�`��
		for (unsigned j = 0; j < draw_opacity_.getObject(i)->getObjectNum(); j++)
		{
			// �I�u�W�F�N�g�O�ݒ�
			draw_opacity_.getObject(i)->ObjectSettingBefore(j);
			TempChangeCameraType(draw_opacity_.getObject(i));
			shader_manager_->ObjectSetting(draw_opacity_.getObject(i), camera_, j);

			// �e���b�V���`��
			for (unsigned k = 0; k < draw_opacity_.getObject(i)->getMeshNum(j); k++)
			{
				// ���b�V���ݒ�
				shader_manager_->MeshSetting(draw_opacity_.getObject(i), camera_, j, k);

				draw_opacity_.getObject(i)->Draw(j, k);
			}

			// �I�u�W�F�N�g��ݒ�
			RevertTempChangeCameraType(draw_opacity_.getObject(i));
			draw_opacity_.getObject(i)->ObjectSettingAfter(j);
		}
	}
}



void RenderTargetMain::DrawTransparent()
{
	for (unsigned i = 0; i < draw_transparent_.getEndIndex(); i++)
	{
		// �V�F�[�_�[���Z�b�g
		shader_manager_->ShaderSetToDevice(draw_transparent_.getObject(i),
										   ShaderManager::VertexShaderType::NONE,
										   ShaderManager::PixelShaderType::NONE);

		// �e�I�u�W�F�N�g�`��
		for (unsigned j = 0; j < draw_transparent_.getObject(i)->getObjectNum(); j++)
		{
			// �I�u�W�F�N�g�O�ݒ�
			draw_transparent_.getObject(i)->ObjectSettingBefore(j);
			TempChangeCameraType(draw_transparent_.getObject(i));
			shader_manager_->ObjectSetting(draw_transparent_.getObject(i), camera_, j);

			// �e���b�V���`��
			for (unsigned k = 0; k < draw_transparent_.getObject(i)->getMeshNum(j); k++)
			{
				// ���b�V���ݒ�
				shader_manager_->MeshSetting(draw_transparent_.getObject(i),
											 camera_, j, k);

				draw_transparent_.getObject(i)->Draw(j, k);
			}

			// �I�u�W�F�N�g��ݒ�
			RevertTempChangeCameraType(draw_transparent_.getObject(i));
			draw_transparent_.getObject(i)->ObjectSettingAfter(j);
		}
	}
}



void RenderTargetMain::Draw2D()
{
	// �J�����ݒ�
	ChangeCameraType(Camera::Type::TWO_DIMENSIONAL);

	for (unsigned i = 0; i < draw_2D_.getEndIndex(); i++)
	{
		// �V�F�[�_�[�Z�b�g
		shader_manager_->ShaderSetToDevice(draw_2D_.getObject(i),
										   ShaderManager::VertexShaderType::NONE,
										   ShaderManager::PixelShaderType::NONE);

		// �e�I�u�W�F�N�g�`��
		for (unsigned j = 0; j < draw_2D_.getObject(i)->getObjectNum(); j++)
		{
			// �I�u�W�F�N�g�O�ݒ�
			draw_2D_.getObject(i)->ObjectSettingBefore(j);
			TempChangeCameraType(draw_2D_.getObject(i));
			shader_manager_->ObjectSetting(draw_2D_.getObject(i), camera_, j);

			// �e���b�V���`��
			for (unsigned k = 0; k < draw_2D_.getObject(i)->getMeshNum(j); k++)
			{
				// ���b�V���ݒ�
				shader_manager_->MeshSetting(draw_2D_.getObject(i),
											 camera_, j, k);

				draw_2D_.getObject(i)->Draw(j, k);
			}

			// �I�u�W�F�N�g��ݒ�
			RevertTempChangeCameraType(draw_2D_.getObject(i));
			draw_2D_.getObject(i)->ObjectSettingAfter(j);
		}
	}
}