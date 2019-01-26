//================================================================================
//!	@file	 BackBuffer.cpp
//!	@brief	 �o�b�N�o�b�t�@�[Class
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "BackBuffer.h"

#include "../../Camera/Camera.h"

#include "../../ShaderManager/ShaderManager.h"
#include <Component/Draw/DrawBase/DrawBase.h>
#include <GameObjectBase/GameObjectBase.h>

#include <main.h>
#include <Renderer/Renderer.h>
#include <SafeRelease/SafeRelease.h>

#include <Effekseer/EffekseerManager/EffekseerManager.h>



//****************************************
// �v���p�e�B��`
//****************************************
Camera* BackBuffer::getpCamera()
{
	return camera_;
}



void BackBuffer::setShaderManager(ShaderManager* value)
{
	shader_manager_ = value;
}



//****************************************
// �֐���`
//****************************************
void BackBuffer::Init()
{
	ResetAllArray();

	// �J�����̏�����
	camera_ = new Camera();
	camera_->Init(nullptr);

	// �t�F�[�h�̏�����
	fade_ = new Fade();
	is_fade_ = false;

	// 
	LPDIRECT3DDEVICE9 device;
	Renderer::getpInstance()->getDevice(&device);
	D3DXCreateTexture(device, SCREEN_WIDTH, SCREEN_HEIGHT, 1,
					  D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8,
					  D3DPOOL_DEFAULT, &main_screen_texture_);
	main_screen_texture_->GetSurfaceLevel(0, &main_screen_surface_);

	D3DXCreateTexture(device, SCREEN_WIDTH, SCREEN_HEIGHT, 1,
					  D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8,
					  D3DPOOL_DEFAULT, &post_effect_texture_);
	post_effect_texture_->GetSurfaceLevel(0, &post_effect_surface_);

	device->GetRenderTarget(0, &back_buffer_surface_);

	render_texture_.Init();
}



void BackBuffer::Uninit()
{
	ResetAllArray();

	// �t�F�[�h���
	SafeRelease::PlusUninit(&camera_);
	SafeRelease::Normal(&fade_);

	render_texture_.Uninit();
	SafeRelease::PlusRelease(&main_screen_texture_);
	SafeRelease::PlusRelease(&post_effect_texture_);
	SafeRelease::PlusRelease(&main_screen_surface_);
	SafeRelease::PlusRelease(&post_effect_surface_);
}



void BackBuffer::UninitWhenChangeScene()
{
	ResetAllArray();

	camera_->Uninit();
}



void BackBuffer::Update()
{
	// �J�����̍X�V
	camera_->Update();

	// �����`����N���X�̍~���\�[�g
	SortTransparent();

	// 2D�`����N���X�̃\�[�g
	Sort2D();

	// �r���{�[�h�X�V
	AllBillboardUpdate();

	// �t�F�[�h�X�V
	if (is_fade_) fade_->Update();

	// �G�t�F�N�V�A�̍X�V
	EffekseerManager::getpInstance()->CreateViewMatrix(*camera_->getpPositon(),
													   *camera_->getpLookAtPoint(),
													   *camera_->getpUp());
	EffekseerManager::getpInstance()->CreateProjectionMatrix(camera_->getAngleOfView());
	EffekseerManager::getpInstance()->Update();
}



void BackBuffer::Draw()
{
	// �����_�[�^�[�Q�b�g�̐؂�ւ�
	LPDIRECT3DDEVICE9 device;
	Renderer::getpInstance()->getDevice(&device);
	//device->SetRenderTarget(0, main_screen_surface_);
	bool is_begin = Renderer::getpInstance()->DrawBegin();

	// �s�����I�u�W�F�N�g
	camera_->setType(Camera::Type::PERSPECTIVE);
	for (unsigned i = 0; i < all_opacity_draw_.GetEndPointer(); i++)
	{
		// �V�F�[�_�[�Z�b�g
		shader_manager_->ShaderSetToDevice(all_opacity_draw_.GetArrayObject(i),
										   ShaderManager::VertexShaderType::NONE,
										   ShaderManager::PixelShaderType::NONE);

		// �e�I�u�W�F�N�g�`��
		for (unsigned j = 0; j < all_opacity_draw_.GetArrayObject(i)->getObjectNum(); j++)
		{
			// �`��O�ݒ�
			all_opacity_draw_.GetArrayObject(i)->SettingBeforeDrawing(camera_, j);

			// �I�u�W�F�N�g�ݒ�
			shader_manager_->ObjectSetting(all_opacity_draw_.GetArrayObject(i),
										   camera_, j);

			// �e���b�V���`��
			for (unsigned k = 0; k < all_opacity_draw_.GetArrayObject(i)->getMeshNum(j); k++)
			{
				// ���b�V���ݒ�
				shader_manager_->MeshSetting(all_opacity_draw_.GetArrayObject(i),
											 camera_, j, k);

				all_opacity_draw_.GetArrayObject(i)->Draw(j, k);
			}

			// �`���ݒ�
			all_opacity_draw_.GetArrayObject(i)->SettingAfterDrawing(camera_, j);
		}
	}

	// �����I�u�W�F�N�g
	for (unsigned i = 0; i < all_transparency_draw_.GetEndPointer(); i++)
	{
		// �V�F�[�_�[���Z�b�g
		shader_manager_->ShaderSetToDevice(all_transparency_draw_.GetArrayObject(i),
										   ShaderManager::VertexShaderType::NONE,
										   ShaderManager::PixelShaderType::NONE);

		// �e�I�u�W�F�N�g�`��
		for (unsigned j = 0; j < all_transparency_draw_.GetArrayObject(i)->getObjectNum(); j++)
		{
			// �`��O�ݒ�
			all_transparency_draw_.GetArrayObject(i)->SettingBeforeDrawing(camera_, j);

			// �I�u�W�F�N�g�ݒ�
			shader_manager_->ObjectSetting(all_transparency_draw_.GetArrayObject(i),
										   camera_, j);

			// �e���b�V���`��
			for (unsigned k = 0; k < all_transparency_draw_.GetArrayObject(i)->getMeshNum(j); k++)
			{
				// ���b�V���ݒ�
				shader_manager_->MeshSetting(all_transparency_draw_.GetArrayObject(i),
											 camera_, j, k);

				all_transparency_draw_.GetArrayObject(i)->Draw(j, k);
			}

			// �`���ݒ�
			all_transparency_draw_.GetArrayObject(i)->SettingAfterDrawing(camera_, j);
		}
	}

	// �G�t�F�N�V�A�`��
	EffekseerManager::getpInstance()->Draw();

	// 2D�I�u�W�F�N�g
	camera_->setType(Camera::Type::TWO_DIMENSIONAL);
	for (unsigned i = 0; i < all_2D_draw_.GetEndPointer(); i++)
	{
		// �V�F�[�_�[�Z�b�g
		shader_manager_->ShaderSetToDevice(all_2D_draw_.GetArrayObject(i),
										   ShaderManager::VertexShaderType::NONE,
										   ShaderManager::PixelShaderType::NONE);

		// �e�I�u�W�F�N�g�`��
		for (unsigned j = 0; j < all_2D_draw_.GetArrayObject(i)->getObjectNum(); j++)
		{
			// �`��O�ݒ�
			all_2D_draw_.GetArrayObject(i)->SettingBeforeDrawing(camera_, j);

			// �I�u�W�F�N�g�ݒ�
			shader_manager_->ObjectSetting(all_2D_draw_.GetArrayObject(i),
										   camera_, j);

			// �e���b�V���`��
			for (unsigned k = 0; k < all_2D_draw_.GetArrayObject(i)->getMeshNum(j); k++)
			{
				// ���b�V���ݒ�
				shader_manager_->MeshSetting(all_2D_draw_.GetArrayObject(i),
											 camera_, j, k);

				all_2D_draw_.GetArrayObject(i)->Draw(j, k);
			}

			// �`���ݒ�
			all_2D_draw_.GetArrayObject(i)->SettingAfterDrawing(camera_, j);
		}
	}

	//camera_->SetType(Camera::Type::TWO_DIMENSIONAL);
	//device->SetVertexShader(nullptr);
	//device->SetPixelShader(nullptr);
	//device->SetMaterial(render_texture_.getpMaterial(0, 0));
	//device->SetTransform(D3DTS_VIEW, camera_->GetViewMatrix());
	//device->SetTransform(D3DTS_PROJECTION, camera_->GetProjectionMatrix());
	//render_texture_.Update(SCREEN_WIDTH * 1.03f,
	//					   SCREEN_HEIGHT * 1.03f,
	//					   XColor4(1.0f, 1.0f, 1.0f, 0.96f));
	//device->SetTransform(D3DTS_WORLD, render_texture_.getpMatrix(0));
	//device->SetTexture(0, post_effect_texture_);
	//render_texture_.Draw(0, 0);

	// �t�F�[�h�`��
	FadeDraw();

	Renderer::getpInstance()->DrawEnd(is_begin);

	/*device->SetRenderTarget(0, back_buffer_surface_);
	is_begin = Renderer::getpInstance()->DrawBegin();

	camera_->SetType(Camera::Type::TWO_DIMENSIONAL);
	device->SetVertexShader(nullptr);
	device->SetPixelShader(nullptr);
	device->SetMaterial(render_texture_.getpMaterial(0, 0));
	device->SetTransform(D3DTS_VIEW, camera_->GetViewMatrix());
	device->SetTransform(D3DTS_PROJECTION, camera_->GetProjectionMatrix());
	render_texture_.Update(SCREEN_WIDTH,
						   SCREEN_HEIGHT,
						   XColor4(1.0f, 1.0f, 1.0f, 1.0f));
	device->SetTransform(D3DTS_WORLD, render_texture_.getpMatrix(0));
	device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

	device->SetTexture(0, main_screen_texture_);
	render_texture_.Draw(0, 0);

	((RendererDirectX9*)Renderer::getpInstance()->getpRenderer())->SetDefaultSamplerState();

	Renderer::getpInstance()->DrawEnd(is_begin);

	LPDIRECT3DTEXTURE9 temp;
	temp = main_screen_texture_;
	main_screen_texture_ = post_effect_texture_;
	post_effect_texture_ = temp;

	LPDIRECT3DSURFACE9 temp2;
	temp2 = main_screen_surface_;
	main_screen_surface_ = post_effect_surface_;
	post_effect_surface_ = temp2;*/
}



void BackBuffer::AddDrawBaseToArray(DrawBase* draw)
{
	switch (draw->getpDrawOrderList()->getDrawType())
	{
		case DrawOrderList::DrawType::OPACITY:
		{
			all_opacity_draw_.AddToArray(draw);
			break;
		}
		case DrawOrderList::DrawType::TRANSPARENCY:
		{
			all_transparency_draw_.AddToArray(draw);
			break;
		}
		case DrawOrderList::DrawType::TWO_DIMENSIONAL:
		{
			all_2D_draw_.AddToArray(draw);
			break;
		}
	}
}



void BackBuffer::ResetAllArray()
{
	all_opacity_draw_.ResetArray();
	all_transparency_draw_.ResetArray();
	all_2D_draw_.ResetArray();
}



void BackBuffer::InitFade(Fade::Type type, Fade::State state, Vec2 size,
						  XColor4 fade_color, float fade_speed)
{
	// �t�F�[�h�̏�����
	fade_->Init(type, state, size, fade_color, fade_speed);

	// �t�F�[�h�t���OON
	is_fade_ = true;
}



void BackBuffer::UninitFade()
{
	// �t�F�[�h�̏I������
	fade_->Uninit();

	// �t�F�[�h�t���OOFF
	is_fade_ = false;
}



bool BackBuffer::IsFadeEnd()
{
	return fade_->getpEndFlag();
}



bool BackBuffer::IsFadeStateName(Fade::State state)
{
	return *fade_->getpState() == state;
}



void BackBuffer::SortTransparent()
{
	// �����I�u�W�F�N�g�����邩�ǂ���
	if (all_transparency_draw_.GetEndPointer() <= 0) return;

	for (unsigned i = 0; i < all_transparency_draw_.GetEndPointer() - 1; i++)
	{
		// �[�x�l���Z�o
		Vector3D temp_vector0 = *all_transparency_draw_.GetArrayObject(i)->getpGameObject()
			->GetTransform()->GetPosition() - *camera_->getpPositon();

		float depth_value0 = temp_vector0.GetLengthSquare();

		for (unsigned j = i + 1; j < all_transparency_draw_.GetEndPointer(); j++)
		{
			// �[�x�l���Z�o
			Vector3D temp_vector1 = *all_transparency_draw_.GetArrayObject(j)
				->getpGameObject()->GetTransform()->GetPosition() - *camera_->getpPositon();

			float depth_value1 = temp_vector1.GetLengthSquare();

			// �[�x�l���r
			if (depth_value0 < depth_value1)
			{
				// ���ёւ�
				all_transparency_draw_.SortTheTwoObject(i, j);
			}
		}
	}
}



void BackBuffer::Sort2D()
{
	// 2D�I�u�W�F�N�g�����邩�ǂ���
	if (all_2D_draw_.GetEndPointer() <= 0) return;

	for (unsigned i = 0; i < all_2D_draw_.GetEndPointer() - 1; i++)
	{
		for (unsigned j = i + 1; j < all_2D_draw_.GetEndPointer(); j++)
		{
			if (all_2D_draw_.GetArrayObject(i)->getpDrawOrderList()->getLayerNum()
		> all_2D_draw_.GetArrayObject(j)->getpDrawOrderList()->getLayerNum())
			{
				// ���ёւ�
				all_2D_draw_.SortTheTwoObject(i, j);
			}
		}
	}
}



void BackBuffer::SetBillboardMatrix(DrawBase* draw)
{
	// �r���[�s��̓]�u�s����Z�b�g
	draw->getpGameObject()->GetTransform()->UpdateTransposeMatrix(camera_->getpViewMatrix());

	// ���s�������J�b�g
	draw->getpGameObject()->GetTransform()->TransposeMatrixTranslationOff();

	// ���[���h�s��̍X�V
	draw->getpGameObject()->GetTransform()->UpdateAxisVector_WorldMatrixISRT();
}



void BackBuffer::AllBillboardUpdate()
{
	camera_->setType(Camera::Type::PERSPECTIVE);

	// �s�����I�u�W�F�N�g
	for (unsigned i = 0; i < all_opacity_draw_.GetEndPointer(); i++)
	{
		if (!all_opacity_draw_.GetArrayObject(i)->getpDrawOrderList()
			->getIsBillboard()) continue;
		SetBillboardMatrix(all_opacity_draw_.GetArrayObject(i));
	}

	// �����I�u�W�F�N�g
	for (unsigned i = 0; i < all_transparency_draw_.GetEndPointer(); i++)
	{
		if (!all_transparency_draw_.GetArrayObject(i)->getpDrawOrderList()
			->getIsBillboard()) continue;
		SetBillboardMatrix(all_transparency_draw_.GetArrayObject(i));
	}
}



void BackBuffer::FadeDraw()
{
	// �`��
	switch (*fade_->getpType())
	{
		case Fade::Type::TYPE_NORMAL:
		{
			camera_->setType(Camera::Type::TWO_DIMENSIONAL);
			// �V�F�[�_�[���Z�b�g
			shader_manager_->ShaderSetToDevice(fade_,
											   ShaderManager::VertexShaderType::NONE,
											   ShaderManager::PixelShaderType::NONE);

			// �e�I�u�W�F�N�g�`��
			for (unsigned j = 0; j < fade_->getObjectNum(); j++)
			{
				// �I�u�W�F�N�g�ݒ�
				shader_manager_->ObjectSetting(fade_, camera_, j);

				// �e���b�V���`��
				for (unsigned k = 0; k < fade_->getMeshNum(j); k++)
				{
					// ���b�V���ݒ�
					shader_manager_->MeshSetting(fade_, camera_, j, k);

					fade_->Draw(j, k);
				}
			}
			break;
		}
		case Fade::Type::TYPE_TRANSITION_01:
		{
			break;
		}
	}
}