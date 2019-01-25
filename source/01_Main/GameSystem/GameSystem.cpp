//================================================================================
//!	@file	 GameSystem.cpp
//!	@brief	 �Q�[���V�X�e��Class
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include <assert.h>

#include "GameSystem.h"

#include <Renderer/Renderer.h>
#include <Renderer/RendererFactory/RendererFactoryDirectX9/RendererFactoryDirectX9.h>
#include <SafeRelease/SafeRelease.h>
#include <Controller/Controller.h>
#include <Keyboard/Keyboard.h>
#include <Sound/Sound.h>
#include <SceneManager/SceneManager.h>
#include <Scenes/TitleScene/TitleScene.h>
#include <Scenes/TitleScene/TitleSceneState/TitleSceneState_Start/TitleSceneState_Start.h>
#include <Scenes/GameScene/GameScene.h>
#include <Scenes/GameScene/GameSceneState/GameSceneState_Start/GameSceneState_Start.h>


//#ifdef _DEBUG
#include <ImGUI/imgui.h>
#include <ImGUI/imgui_impl_dx9.h>
//#endif



//****************************************
// �֐���`
//****************************************
bool GameSystem::Init(HINSTANCE hInstance, HWND hWnd, BOOL is_full_screen,
					  int window_width, int window_height)
{
	// �����_���[�̏�����
	Renderer::getpInstance()->setRenderer(new RendererFactoryDirectX9(),
										  Renderer::MODE::DIRECTX9);
	bool is_init = Renderer::getpInstance()->Init(hInstance, hWnd, is_full_screen,
												  window_width, window_height);

#ifdef _DEBUG
	assert(is_init && "DirectX9�p�����_���[�̏������Ɏ��s!!");
#else
	is_init = is_init;
#endif

	// �T�E���h�̏�����
	InitSound(hWnd);

	// �L�[�{�[�h���͂̏�����
	InitKeyboard(hInstance, hWnd);

	// ImGUI�̏�����
//#ifdef _DEBUG
	LPDIRECT3DDEVICE9 device = nullptr;
	Renderer::getpInstance()->getDevice(&device);
	if (device == nullptr)
	{
		MessageBox(nullptr, "NotGetDevice!(GameSystem.cpp)", "Error", MB_OK);
		return false;
	}
	ImGui_ImplDX9_Init(hWnd, device);
//#endif

	// �V�[���}�l�[�W���[�̐���
	scene_manager_ = new SceneManager();
	scene_manager_->Init(new TitleScene(new TitleSceneState_Start()));

	return true;
}



void GameSystem::Uninit()
{
	// �V�[���}�l�[�W���[�̉��
	SafeRelease::PlusUninit(&scene_manager_);

	// ImGUI�̏I��
//#ifdef _DEBUG
	ImGui_ImplDX9_Shutdown();
//#endif

	// �L�[�{�[�h���͂̏I������
	UninitKeyboard();

	// �T�E���h�̏I������
	UninitSound();

	// �����_���[�̏I��
	Renderer::getpInstance()->Uninit();
	Renderer::ReleaseInstance();
}



void GameSystem::Update()
{
	// ImGUI�̍X�V
//#ifdef _DEBUG
	ImGui_ImplDX9_NewFrame();
//#endif

	// �L�[�{�[�h�̓��͏���
	UpdateKeyboard();

	// �Q�[���p�b�h�̓��͏���
	SetController();

	// �V�[���̍X�V
	scene_manager_->UpdateScene();
}



void GameSystem::Draw()
{
	// �`��J�n
	//bool is_begin = Renderer::GetInstance()->DrawBegin();

	// �V�[���̕`��
	scene_manager_->DrawScene();

	// �`��I��
	//Renderer::GetInstance()->DrawEnd(is_begin);

	// ImGUI�̕`��
//#ifdef _DEBUG
	ImGui::Render();
//#endif

	// �o�b�N�o�b�t�@���t�����g�o�b�t�@�ɔ��f
	Renderer::getpInstance()->Present();
}



void GameSystem::LateUpdate()
{
	scene_manager_->Update();
}