//================================================================================
//!	@file	 GameEngine.cpp
//!	@brief	 ゲームエンジンClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../GameEngine.h"
#include "../Renderer/Renderer.h"
#include "../Renderer/RendererFactoryDirectX9.h"
#include "../Scene/SceneManager/SceneManager.h"

#include <Controller/Controller.h>
#include <Keyboard/Keyboard.h>

#include <Resource/Effekseer/EffekseerManager/EffekseerManager.h>
#include <Resource/Texture/TextureManager/TextureManager.h>
#include <Resource/ModelX/ModelXManager/ModelXManager.h>
#include <Resource/MdBin/MdBinManager/MdBinManager.h>
#include <Resource/Sound/SoundManager.h>
#include <Tool/SafeRelease.h>

#include <Scenes/TitleScene/TitleScene.h>
#include <Scenes/TitleScene/TitleSceneState/TitleSceneState_Start/TitleSceneState_Start.h>
#include <Scenes/GameScene/GameScene.h>
#include <Scenes/GameScene/GameSceneState/GameSceneState_Start/GameSceneState_Start.h>


//#ifdef _DEBUG
#include <Tool/Debug/ImGUI/imgui.h>
#include <Tool/Debug/ImGUI/imgui_impl_dx9.h>
//#endif



//****************************************
// 定数定義
//****************************************
const unsigned GameEngine::SCREEN_WIDTH = 1280;
const unsigned GameEngine::SCREEN_HEIGHT = 720;



//****************************************
// 関数定義
//****************************************
bool GameEngine::Init(HINSTANCE hInstance, HWND hWnd, BOOL is_full_screen,
					  int window_width, int window_height)
{
	// レンダラーの初期化
	Renderer::getpInstance()->setRenderer(new RendererFactoryDirectX9(),
										  Renderer::MODE::DIRECTX9);
	bool is_init = Renderer::getpInstance()->Init(hInstance, hWnd, is_full_screen,
												  window_width, window_height);

#ifdef _DEBUG
	assert(is_init && "DirectX9用レンダラーの初期化に失敗!!");
#else
	is_init = is_init;
#endif

	// キーボード入力の初期化
	InitKeyboard(hInstance, hWnd);

	// ImGUIの初期化
//#ifdef _DEBUG
	LPDIRECT3DDEVICE9 device = nullptr;
	Renderer::getpInstance()->getDevice(&device);
	if (device == nullptr)
	{
		MessageBox(nullptr, "NotGetDevice!(GameEngine.cpp)", "Error", MB_OK);
		return false;
	}
	ImGui_ImplDX9_Init(hWnd, device);
//#endif

	// リソースの初期化
	EffekseerManager::getpInstance()->Init();
	TextureManager::getpInstance()->Init();
	ModelXManager::getpInstance()->Init();
	MdBinManager::getpInstance()->Init();
	SoundManager::getpInstance()->Init();

	// シーンマネージャーの生成
	scene_manager_ = new SceneManager();
	scene_manager_->Init(new TitleScene(new TitleSceneState_Start()));

	return true;
}



void GameEngine::Uninit()
{
	// シーンマネージャーの解放
	SafeRelease::PlusUninit(&scene_manager_);

	// リソースの終了処理
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

	// ImGUIの終了
//#ifdef _DEBUG
	ImGui_ImplDX9_Shutdown();
//#endif

	// キーボード入力の終了処理
	UninitKeyboard();

	// レンダラーの終了
	Renderer::getpInstance()->Uninit();
	Renderer::ReleaseInstance();
}



void GameEngine::Update()
{
	// ImGUIの更新
//#ifdef _DEBUG
	ImGui_ImplDX9_NewFrame();
//#endif

	// キーボードの入力処理
	UpdateKeyboard();

	// ゲームパッドの入力処理
	SetController();

	// シーンの更新
	scene_manager_->UpdateScene();
}



void GameEngine::Draw()
{
	// 描画開始
	//bool is_begin = Renderer::GetInstance()->DrawBegin();

	// シーンの描画
	scene_manager_->DrawScene();

	// 描画終了
	//Renderer::GetInstance()->DrawEnd(is_begin);

	// ImGUIの描画
//#ifdef _DEBUG
	ImGui::Render();
//#endif

	// バックバッファをフロントバッファに反映
	Renderer::getpInstance()->Present();
}



void GameEngine::LateUpdate()
{
	scene_manager_->Update();
}