//================================================================================
//!	@file	 DrawManager.cpp
//!	@brief	 描画マネージャーClass
//! @details 
//!	@author  Kai Araki									@date 2019/01/19
//================================================================================



//****************************************
// インクルード文
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
// プロパティ定義
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
// 関数定義
//****************************************
void DrawManager::Init()
{
	// カメラ作成
	for (auto& contents : camera_)
	{
		contents = new Camera();
		contents->Init(nullptr);
	}

	// 共通データ初期化
	common_data_ = new DrawCommonData();
	common_data_->Init();

	// フェード作成
	fade_ = new Fade();
	fade_->Init();

	// シェーダーマネージャー初期化
	shader_manager_ = new ShaderManager();
	shader_manager_->Init(common_data_);

	// バックバッファサーフェスの保存
	Renderer::getpInstance()->getDevice(&device_);
	device_->GetRenderTarget(0, &back_buffer_surface_);

	// BackBuffer用ポリゴン作成
	back_buffer_polygon_ = new RenderTexturePolygon();
	back_buffer_polygon_->Init();
	back_buffer_polygon_->Update(-0.5f, -0.5f,
		(float)GameEngine::SCREEN_WIDTH,
								 (float)GameEngine::SCREEN_HEIGHT,
								 XColor4(1.0f, 1.0f, 1.0f, 1.0f));

	// レンダーターゲットメイン初期化
	render_target_main_ = new RenderTargetMain();
	render_target_main_->setCamera(camera_[(int)RenderTargetType::MAIN]);
	render_target_main_->setDrawCommonData(common_data_);
	render_target_main_->setShaderManager(shader_manager_);
	render_target_main_->Init();

	// モーションブラー初期化
	motion_blur_ = new MotionBlur();
	motion_blur_->setCamera(camera_[(int)RenderTargetType::MAIN]);
	motion_blur_->setDrawCommonData(common_data_);
	motion_blur_->setShaderManager(shader_manager_);
	motion_blur_->Init();

	// フォグ
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

	// カメラ更新
	for (auto contents : camera_)
	{
		contents->Update();
	}

	// 全描画基底クラス更新関数
	UpdateAllDrawBase();

	// レンダーターゲットのリセット
	ResetAllRenderTarget();

	// レンダーターゲットの振り分け
	DistributeDrawBase();

	// レンダーターゲット更新
	UpdateAllRenderTarget();

	// ポストエフェクト更新
	motion_blur_->Update();

	// フェード更新
	if (!fade_->getpEndFlag()) fade_->Update();

	// デバッグ表示
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
	// レンダーターゲット描画
	render_target_main_->Draw();

	// ポストエフェクト描画
	//motion_blur_->Draw();

	// フェード
	DrawFade();

	// BackBuffer描画
	DrawBackBuffer();
	
	// ポストエフェクト後更新
	//motion_blur_->LateUpdate();
}



void DrawManager::AddDrawBaseToArray(DrawBase* draw)
{
	// 追加待ち配列に追加
	await_add_.AddToArray(draw);
}



void DrawManager::OverwriteArrayDrawBase(GameObjectBase* game_object,
										 DrawBase* new_draw)
{
	// 新規がnullptrの場合
	if (new_draw == nullptr)
	{
		// 古い描画基底クラスの解放
		ReleaseDrawBaseFromArray(game_object->getpDraw());

		// 古い描画基底クラスの消去
		DrawBase* temp = game_object->getpDraw();
		SafeRelease::Normal(&temp);

		// nullptrの代入
		game_object->setDraw(new_draw);
	}
	else
	{
		// 配列の上書き
		all_draw_.OverwriteArray(game_object->getpDraw(), new_draw);

		// 古い描画基底クラスの消去
		DrawBase* temp = game_object->getpDraw();
		SafeRelease::Normal(&temp);

		// 新規コンポーネントの初期化
		game_object->setDraw(new_draw);
		*new_draw->getpGameObject() = *game_object;
		new_draw->Init();
	}
}



void DrawManager::ReleaseDrawBaseFromArray(DrawBase* draw)
{
	// 解放待ち配列に追加
	await_release_.AddToArray(draw);
}



void DrawManager::StartFadeIn(Fade::Type type, Vec2 size, XColor4 color, float speed)
{
	// フェードの初期化
	fade_->Start(type, Fade::State::FADE_IN, size, color, speed);
}



void DrawManager::StartFadeOut(Fade::Type type, Vec2 size, XColor4 color, float speed)
{
	// フェードの初期化
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
	// 追加待ちがあるかどうか
	if (await_add_.getEndIndex() <= 0) return;

	// 追加
	for (unsigned i = 0; i < await_add_.getEndIndex(); i++)
	{
		all_draw_.AddToArray(await_add_.getObject(i));
	}

	// 追加待ち配列をリセット
	await_add_.Reset();
}



void DrawManager::ReleaseContentsOfAwaitReleaseArray()
{
	// 解放待ちがあるかどうか
	if (await_release_.getEndIndex() <= 0) return;

	// 解放とソート
	for (unsigned i = 0; i < await_release_.getEndIndex(); i++)
	{
		all_draw_.DeleteFromArrayAndSort(await_release_.getObject(i));
	}

	// 解放待ち配列をリセット
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
		// レンダーターゲットメイン
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
	// レンダーターゲットの切り替え
	device_->SetRenderTarget(0, back_buffer_surface_);
	bool is_begin = Renderer::getpInstance()->DrawBegin();

	// カメラ切り替え
	camera_[(int)RenderTargetType::MAIN]->setType(Camera::Type::TWO_DIMENSIONAL);

	// シェーダーセット
	shader_manager_->ShaderSetToDevice(back_buffer_polygon_,
									   ShaderManager::VertexShaderType::FIXED,
									   ShaderManager::PixelShaderType::FIXED);

	// オブジェクト設定
	shader_manager_->ObjectSetting(back_buffer_polygon_,
								   camera_[(int)RenderTargetType::MAIN], 0);

	// サンプラー変更
	device_->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	device_->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	device_->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

	// アルファブレンドOFF
	((RendererDirectX9*)Renderer::getpInstance()->getpRenderer())
		->UseAlphaBlending(false);

	// 描画
	device_->SetTexture(0, common_data_->getpRenderTextureMain()->getpTexture());
	back_buffer_polygon_->Draw(0, 0);

	// アルファブレンドON
	((RendererDirectX9*)Renderer::getpInstance()->getpRenderer())
		->UseAlphaBlending(true);

	// サンプラー変更
	((RendererDirectX9*)Renderer::getpInstance()->getpRenderer())
		->SetDefaultSamplerState();

	Renderer::getpInstance()->DrawEnd(is_begin);
}



void DrawManager::DrawFade()
{
	// レンダーターゲットの切り替え
	common_data_->getpRenderTextureMain()->setRenderTarget(0);
	bool is_begin = Renderer::getpInstance()->NoClearDrawBegin();

	// カメラ切り替え
	camera_[(int)RenderTargetType::MAIN]->setType(Camera::Type::TWO_DIMENSIONAL);

	switch (*fade_->getpType())
	{
		case Fade::Type::NORMAL:
		{
			// シェーダーをセット
			shader_manager_->ShaderSetToDevice(fade_,
											   ShaderManager::VertexShaderType::NONE,
											   ShaderManager::PixelShaderType::NONE);

			// オブジェクト設定
			shader_manager_->ObjectSetting(fade_,
										   camera_[(int)RenderTargetType::MAIN], 0);

			// メッシュ設定
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