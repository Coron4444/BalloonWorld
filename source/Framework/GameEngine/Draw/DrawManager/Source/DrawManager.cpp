//================================================================================
//!	@file	 DrawManager.cpp
//!	@brief	 �`��}�l�[�W���[Class
//! @details 
//!	@author  Kai Araki									@date 2019/01/19
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../DrawCommonData.h"
#include "../DrawManager.h"
#include "../Fade.h"
#include "../RenderTarget/RenderTargetMain.h"
#include "../RenderTexturePolygon.h"
#include "../Shader/ShaderManager/ShaderManager.h"
#include "../../DrawBase.h"
#include "../../../GameObject/GameObjectBase.h"
#include "../../../GameEngine.h"
#include "../PostEffect/MotionBlur.h"

#include <Tool/SafeRelease.h>



//****************************************
// �v���p�e�B��`
//****************************************
DrawCommonData* DrawManager::getpDrawCommonData()
{
	return common_data_;
}



Camera* DrawManager::getpCamera(RenderTargetType type)
{
	return camera_[(int)type];
}



//****************************************
// �֐���`
//****************************************
void DrawManager::Init()
{
	// �J�����쐬
	for (auto& contents : camera_)
	{
		contents = new Camera();
		contents->Init(nullptr);
	}

	// ���ʃf�[�^������
	common_data_ = new DrawCommonData();
	common_data_->Init();

	// �t�F�[�h�쐬
	fade_ = new Fade();
	fade_->Init();

	// �V�F�[�_�[�}�l�[�W���[������
	shader_manager_ = new ShaderManager();
	shader_manager_->Init(common_data_);

	// �o�b�N�o�b�t�@�T�[�t�F�X�̕ۑ�
	Renderer::getpInstance()->getDevice(&device_);
	device_->GetRenderTarget(0, &back_buffer_surface_);

	// BackBuffer�p�|���S���쐬
	back_buffer_polygon_ = new RenderTexturePolygon();
	back_buffer_polygon_->Init();
	back_buffer_polygon_->Update(-0.5f, -0.5f,
		(float)GameEngine::SCREEN_WIDTH,
								 (float)GameEngine::SCREEN_HEIGHT,
								 XColor4(1.0f, 1.0f, 1.0f, 1.0f));

	// �����_�[�^�[�Q�b�g���C��������
	render_target_main_ = new RenderTargetMain();
	render_target_main_->setCamera(camera_[(int)RenderTargetType::MAIN]);
	render_target_main_->setDrawCommonData(common_data_);
	render_target_main_->setShaderManager(shader_manager_);
	render_target_main_->Init();

	// ���[�V�����u���[������
	motion_blur_ = new MotionBlur();
	motion_blur_->setCamera(camera_[(int)RenderTargetType::MAIN]);
	motion_blur_->setDrawCommonData(common_data_);
	motion_blur_->setShaderManager(shader_manager_);
	motion_blur_->Init();

	// �t�H�O
	device_->SetRenderState(D3DRS_FOGENABLE, TRUE);
	device_->SetRenderState(D3DRS_FOGCOLOR, D3DCOLOR_RGBA(255, 255, 255, 255));
	device_->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_NONE);
	device_->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_EXP);
	float density = 0.001f;
	device_->SetRenderState(D3DRS_FOGDENSITY, *((DWORD*)&density));
}



void DrawManager::Uninit()
{
	await_add_.Reset();
	await_release_.Reset();
	all_draw_.Reset();

	SafeRelease::PlusRelease(&back_buffer_surface_);
	SafeRelease::PlusUninit(&motion_blur_);
	SafeRelease::PlusUninit(&render_target_main_);
	SafeRelease::PlusUninit(&back_buffer_polygon_);
	SafeRelease::PlusUninit(&shader_manager_);
	SafeRelease::PlusUninit(&fade_);
	SafeRelease::PlusUninit(&common_data_);
	for (auto& contents : camera_)
	{
		SafeRelease::PlusUninit(&contents);
	}
}



void DrawManager::UninitWhenChangeScene()
{
	await_add_.Reset();
	await_release_.Reset();
	all_draw_.Reset();

	render_target_main_->UninitWhenChangeScene();
	motion_blur_->UninitWhenChangeScene();

	for (auto& contents : camera_)
	{
		contents->setState(nullptr);
	}
}



void DrawManager::Update()
{
	AddContentsOfAwaitAddArray();
	ReleaseContentsOfAwaitReleaseArray();

	// �J�����X�V
	for (auto contents : camera_)
	{
		contents->Update();
	}

	// �S�`����N���X�X�V�֐�
	UpdateAllDrawBase();

	// �����_�[�^�[�Q�b�g�̃��Z�b�g
	ResetAllRenderTarget();

	// �����_�[�^�[�Q�b�g�̐U�蕪��
	DistributeDrawBase();

	// �����_�[�^�[�Q�b�g�X�V
	UpdateAllRenderTarget();

	// �|�X�g�G�t�F�N�g�X�V
	motion_blur_->Update();

	// �t�F�[�h�X�V
	if (!fade_->getpEndFlag()) fade_->Update();

	// �f�o�b�O�\��
#ifdef _DEBUG
	for (unsigned i = 0; i < all_draw_.getEndIndex(); i++)
	{
		if (all_draw_.getObject(i) == nullptr) continue;
		all_draw_.getObject(i)->DebugDisplay();
	}
#endif
}



void DrawManager::Draw()
{
	// �����_�[�^�[�Q�b�g�`��
	render_target_main_->Draw();

	// �|�X�g�G�t�F�N�g�`��
	//motion_blur_->Draw();

	// �t�F�[�h
	DrawFade();

	// BackBuffer�`��
	DrawBackBuffer();
	
	// �|�X�g�G�t�F�N�g��X�V
	//motion_blur_->LateUpdate();
}



void DrawManager::AddDrawBaseToArray(DrawBase* draw)
{
	// �ǉ��҂��z��ɒǉ�
	await_add_.AddToArray(draw);
}



void DrawManager::OverwriteArrayDrawBase(GameObjectBase* game_object,
										 DrawBase* new_draw)
{
	// �V�K��nullptr�̏ꍇ
	if (new_draw == nullptr)
	{
		// �Â��`����N���X�̉��
		ReleaseDrawBaseFromArray(game_object->getpDraw());

		// �Â��`����N���X�̏���
		DrawBase* temp = game_object->getpDraw();
		SafeRelease::Normal(&temp);

		// nullptr�̑��
		game_object->setDraw(new_draw);
	}
	else
	{
		// �z��̏㏑��
		all_draw_.OverwriteArray(game_object->getpDraw(), new_draw);

		// �Â��`����N���X�̏���
		DrawBase* temp = game_object->getpDraw();
		SafeRelease::Normal(&temp);

		// �V�K�R���|�[�l���g�̏�����
		game_object->setDraw(new_draw);
		*new_draw->getpGameObject() = *game_object;
		new_draw->Init();
	}
}



void DrawManager::ReleaseDrawBaseFromArray(DrawBase* draw)
{
	// ����҂��z��ɒǉ�
	await_release_.AddToArray(draw);
}



void DrawManager::StartFadeIn(Fade::Type type, Vec2 size, XColor4 color, float speed)
{
	// �t�F�[�h�̏�����
	fade_->Start(type, Fade::State::FADE_IN, size, color, speed);
}



void DrawManager::StartFadeOut(Fade::Type type, Vec2 size, XColor4 color, float speed)
{
	// �t�F�[�h�̏�����
	fade_->Start(type, Fade::State::FADE_OUT, size, color, speed);
}



bool DrawManager::IsFadeEnd()
{
	return fade_->getpEndFlag();
}



bool DrawManager::IsFadeState(Fade::State state)
{
	return *fade_->getpState() == state;
}



void DrawManager::AddContentsOfAwaitAddArray()
{
	// �ǉ��҂������邩�ǂ���
	if (await_add_.getEndIndex() <= 0) return;

	// �ǉ�
	for (unsigned i = 0; i < await_add_.getEndIndex(); i++)
	{
		all_draw_.AddToArray(await_add_.getObject(i));
	}

	// �ǉ��҂��z������Z�b�g
	await_add_.Reset();
}



void DrawManager::ReleaseContentsOfAwaitReleaseArray()
{
	// ����҂������邩�ǂ���
	if (await_release_.getEndIndex() <= 0) return;

	// ����ƃ\�[�g
	for (unsigned i = 0; i < await_release_.getEndIndex(); i++)
	{
		all_draw_.DeleteFromArrayAndSort(await_release_.getObject(i));
	}

	// ����҂��z������Z�b�g
	await_release_.Reset();
}



void DrawManager::UpdateAllDrawBase()
{
	for (unsigned i = 0; i < all_draw_.getEndIndex(); i++)
	{
		all_draw_.getObject(i)->Update();
	}
}



void DrawManager::ResetAllRenderTarget()
{
	render_target_main_->Reset();
}



void DrawManager::DistributeDrawBase()
{
	for (unsigned i = 0; i < all_draw_.getEndIndex(); i++)
	{
		// �����_�[�^�[�Q�b�g���C��
		if (all_draw_.getObject(i)->getpDrawOrderList()->getpRenderTargetFlag()
			->CheckAny(DrawOrderList::RENDER_TARGET_MAIN))
		{
			render_target_main_->AddDrawBaseToArray(all_draw_.getObject(i));
		}
	}
}



void DrawManager::UpdateAllRenderTarget()
{
	render_target_main_->Update();
}



void DrawManager::DrawBackBuffer()
{
	// �����_�[�^�[�Q�b�g�̐؂�ւ�
	device_->SetRenderTarget(0, back_buffer_surface_);
	bool is_begin = Renderer::getpInstance()->DrawBegin();

	// �J�����؂�ւ�
	camera_[(int)RenderTargetType::MAIN]->setType(Camera::Type::TWO_DIMENSIONAL);

	// �V�F�[�_�[�Z�b�g
	shader_manager_->ShaderSetToDevice(back_buffer_polygon_,
									   ShaderManager::VertexShaderType::FIXED,
									   ShaderManager::PixelShaderType::FIXED);

	// �I�u�W�F�N�g�ݒ�
	shader_manager_->ObjectSetting(back_buffer_polygon_,
								   camera_[(int)RenderTargetType::MAIN], 0);

	// �T���v���[�ύX
	device_->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	device_->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	device_->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

	// �A���t�@�u�����hOFF
	((RendererDirectX9*)Renderer::getpInstance()->getpRenderer())
		->UseAlphaBlending(false);

	// �`��
	device_->SetTexture(0, common_data_->getpRenderTextureMain()->getpTexture());
	back_buffer_polygon_->Draw(0, 0);

	// �A���t�@�u�����hON
	((RendererDirectX9*)Renderer::getpInstance()->getpRenderer())
		->UseAlphaBlending(true);

	// �T���v���[�ύX
	((RendererDirectX9*)Renderer::getpInstance()->getpRenderer())
		->SetDefaultSamplerState();

	Renderer::getpInstance()->DrawEnd(is_begin);
}



void DrawManager::DrawFade()
{
	// �����_�[�^�[�Q�b�g�̐؂�ւ�
	common_data_->getpRenderTextureMain()->setRenderTarget(0);
	bool is_begin = Renderer::getpInstance()->NoClearDrawBegin();

	// �J�����؂�ւ�
	camera_[(int)RenderTargetType::MAIN]->setType(Camera::Type::TWO_DIMENSIONAL);

	switch (*fade_->getpType())
	{
		case Fade::Type::NORMAL:
		{
			// �V�F�[�_�[���Z�b�g
			shader_manager_->ShaderSetToDevice(fade_,
											   ShaderManager::VertexShaderType::NONE,
											   ShaderManager::PixelShaderType::NONE);

			// �I�u�W�F�N�g�ݒ�
			shader_manager_->ObjectSetting(fade_,
										   camera_[(int)RenderTargetType::MAIN], 0);

			// ���b�V���ݒ�
			shader_manager_->MeshSetting(fade_,
										 camera_[(int)RenderTargetType::MAIN], 0, 0);
			fade_->Draw(0, 0);
			break;
		}
		case Fade::Type::TRANSITION_01:
		{
			break;
		}
	}

	Renderer::getpInstance()->DrawEnd(is_begin);
}