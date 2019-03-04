//================================================================================
//!	@file	 GameEngine.cpp
//!	@brief	 �Q�[���G���W��Class
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../GameEngine.h"
#include "../Renderer/RendererFactoryDirectX9.h"
#include "../Collision/BulletPhysics/BulletPhysicsManager/BulletPhysicsManager.h"

#include <Scenes/TitleScene/TitleScene.h>
#include <Scenes/TitleScene/TitleSceneState_Start.h>
#include <Scenes/GameScene/GameScene.h>
#include <Scenes/GameScene/GameSceneState_Start.h>



//****************************************
// �萔��`
//****************************************
const unsigned GameEngine::SCREEN_WIDTH = 1280;
const unsigned GameEngine::SCREEN_HEIGHT = 720;



//****************************************
// �֐���`
//****************************************
bool GameEngine::Init(HINSTANCE hInstance, HWND hWnd, BOOL is_full_screen,
					  int window_width, int window_height)
{
	// �����_���[�̏�����
	Renderer::getpInstance()->setRenderer(new RendererFactoryDirectX9(),
										  Renderer::MODE::DIRECTX9);
	bool is_init = Renderer::getpInstance()->Init(hInstance, hWnd, is_full_screen,
												  window_width, window_height);
	if (!is_init)
	{
		MessageBox(nullptr, "�����_���[���������s(GameEngine.cpp)", "Error", MB_OK);
		return false;
	}

	// ImGUI�̏�����
#ifdef _DEBUG
	LPDIRECT3DDEVICE9 device = nullptr;
	Renderer::getpInstance()->getDevice(&device);
	if (device == nullptr)
	{
		MessageBox(nullptr, "NotGetDevice!(GameEngine.cpp)", "Error", MB_OK);
		return false;
	}
	ImGui_ImplDX9_Init(hWnd, device);
#endif

	// ����������
	Random::getpInstance()->Init();

	// Bullet�̏�����
	BulletPhysicsManager::getpInstance()->Init();
	BulletPhysicsManager::getpInstance()->setDebug(false);
	
	// ���̓}�l�[�W���̏�����
	InputManager::getpInstance()->Init(hInstance, hWnd);

	// ���\�[�X�̏�����
	EffekseerManager::getpInstance()->Init();
	TextureManager::getpInstance()->Init();
	ModelXManager::getpInstance()->Init();
	MdBinManager::getpInstance()->Init();
	SoundManager::getpInstance()->Init(hWnd);

	// �V�[���}�l�[�W���[�̐���
	scene_manager_ = new SceneManager();
	scene_manager_->Init(new TitleScene(new TitleSceneState_Start()));
	//scene_manager_->Init(new GameScene(new GameSceneState_Start()));

	return true;
}



void GameEngine::Uninit()
{
	// �V�[���}�l�[�W���[�̉��
	SafeRelease::PlusUninit(&scene_manager_);

	// ���\�[�X�̏I������
	SoundManager::getpInstance()->Uninit();
	SoundManager::ReleaseInstance();
	MdBinManager::getpInstance()->Uninit();
	MdBinManager::ReleaseInstance();
	ModelXManager::getpInstance()->Uninit();
	ModelXManager::ReleaseInstance();
	TextureManager::getpInstance()->Uninit();
	TextureManager::ReleaseInstance();
	EffekseerManager::getpInstance()->Uninit();
	EffekseerManager::ReleaseInstance();

	// ���̓}�l�[�W���̏I������
	InputManager::getpInstance()->Uninit();
	InputManager::ReleaseInstance();

	// Bullet�̏I��
	BulletPhysicsManager::getpInstance()->Uninit();
	BulletPhysicsManager::ReleaseInstance();

	// �����̏I��
	Random::getpInstance()->Uninit();
	Random::ReleaseInstance();

	// ImGUI�̏I��
#ifdef _DEBUG
	ImGui_ImplDX9_Shutdown();
#endif

	// �����_���[�̏I��
	Renderer::getpInstance()->Uninit();
	Renderer::ReleaseInstance();
}



void GameEngine::Update()
{
	// ImGUI�̍X�V
#ifdef _DEBUG
	ImGui_ImplDX9_NewFrame();
#endif

	// Bullet�X�V
	BulletPhysicsManager::getpInstance()->Update();
	
	// ���̓}�l�[�W���X�V
	InputManager::getpInstance()->Update();

	// �V�[���̍X�V
	scene_manager_->UpdateScene();
}



void GameEngine::Draw()
{
	// �V�[���̕`��
	scene_manager_->DrawScene();

	// ImGUI�̕`��
#ifdef _DEBUG
	ImGui::Render();
#endif

	// �o�b�N�o�b�t�@���t�����g�o�b�t�@�ɔ��f
	Renderer::getpInstance()->Present();
}



void GameEngine::LateUpdate()
{
	scene_manager_->Update();
}