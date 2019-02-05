//================================================================================
//!	@file	 PlayerUpdate.cpp
//!	@brief	 プレイヤー更新Class
//! @details 
//!	@author  Kai Araki									@date 2019/03/27
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../PlayerUpdate.h"
#include "../PlayerUpdate_Special.h"
#include "../Player.h"

#include <GameEngine/Input/InputManager/InputManager.h>
#include <GameEngine/GameObject/GameObjectManager/GameObjectManager.h>
#include <Tool/MeterToFrame.h>
#include <Resource/Effekseer/EffekseerManager/EffekseerManager.h>



//****************************************
// 定数定義
//****************************************
const float PlayerUpdate::SPEED = MeterToFrame::MeterPerSecondSquaredToMeterPerFrameSquared(50.0f);

static const std::string TEST_EFFEKSEER = "Beam/Beam.efk";



//****************************************
// 関数定義
//****************************************
void PlayerUpdate::Init()
{
	// ダウンキャスト
	player_ = (Player*)getpGameObject();

	// 剛体設定
	player_->CreatePhysics();
	player_->getpPhysics()->setMaxVelocity(MeterToFrame::MeterPerSecondToMeterPerFlame(300.0f));
	player_->getpPhysics()->setMass(8.0f);
	player_->getpPhysics()->setMyFriction(1.0f);
	player_->getpPhysics()->setMyBounciness(1.0f);

	// 初期姿勢
	player_->getpTransform()->setInitAngle(Vector3D(0.0f, D3DXToRadian(-90.0f), 0.0f));
}



void PlayerUpdate::Update()
{
	// 平行移動
	Vector3D temp_vector;

	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_D))
	{
		temp_vector += *player_->getpTransform()->getpRight();
	}
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_A))
	{
		temp_vector += -*player_->getpTransform()->getpRight();
	}
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_W))
	{
		temp_vector += *player_->getpTransform()->getpForawrd();
	}
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_S))
	{
		temp_vector += -*player_->getpTransform()->getpForawrd();
	}

	*player_->getpPhysics()->getpAcceleration() += *temp_vector.ChangeAnyLength(SPEED);

	// ブレーキ
	if (InputManager::getpInstance()->getpKeyboard()->getTrigger(DIK_N))
	{
		//GameObjectManager::GetUpdateManager()
			//->OverwriteArrayUpdateBase(player_, new PlayerUpdate_Special());
		//return;
		player_->getpPhysics()->AddFriction(0.5f);
	}

	player_->getpPhysics()->AddFriction(0.9f);

	// ジャンプ
	if (InputManager::getpInstance()->getpKeyboard()->getTrigger(DIK_SPACE))
	{
		temp_vector = Vec3(0.0f, 1.0f, 0.0f);
		temp_vector.ChangeAnyLength(MeterToFrame::MeterPerSecondToMeterPerFlame(30.0f));

		*player_->getpPhysics()->getpVelocity() += temp_vector;
	}

	// 拡縮
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_Z))
	{
		*player_->getpTransform()->getpScale() += Vec3(SPEED, SPEED, SPEED);
	}
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_X))
	{
		*player_->getpTransform()->getpScale() += -Vec3(SPEED, SPEED, SPEED);
	}

	*player_->getpTransform()->getpLookAtSpeed() = 0.05f;

	// 回転
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_C))
	{
		player_->getpTransform()->setLookAtVector(Vec3(1.0f, 1.0f, 0.0f));
	}
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_V))
	{
		player_->getpTransform()->setLookAtVector(Vec3(-1.0f, 0.0f, 0.0f));
	}
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_B))
	{
		player_->getpTransform()->setLookAtVector(Vec3(0.0f, 0.0f, -1.0f));
	}

	//float temp_scale = 1.0f;

	if (InputManager::getpInstance()->getpKeyboard()->getTrigger(DIK_P))
	{
		EffekseerObject* temp_object = EffekseerManager::getpInstance()
			->getpDisposableObject(&TEST_EFFEKSEER);
		*temp_object->getpTransform()->getpPosition() = *player_->getpTransform()->getpPosition();
		temp_object->getpTransform()->CreateWorldMatrix();
		temp_object->Play();
	}

	player_->getpTransform()->CreateAxisAndWorldMatrix();
}



void PlayerUpdate::DebugDisplay()
{
#ifdef _DEBUG
	// ウィンドウの設定
    ImGui::SetNextWindowPos(ImVec2(30, 30), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(150, 500), ImGuiSetCond_Once);
	ImGui::PushStyleColor(ImGuiCol_TitleBgActive,    ImVec4(1.0f, 0.0f, 0.0f, 0.8f));
    ImGui::PushStyleColor(ImGuiCol_TitleBgCollapsed, ImVec4(0.0f, 0.5f, 1.0f, 0.8f));
	ImGui::PushStyleColor(ImGuiCol_TitleBg,          ImVec4(0.5f, 0.0f, 0.0f, 0.8f));
	ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.0f, 0.5f, 0.5f, 1.0f));

	// 開始
	ImGui::Begin("Player", nullptr, ImGuiWindowFlags_MenuBar);

	// メニュー
	if (ImGui::BeginMenuBar()) 
	{
		// メニュー名
		if (ImGui::BeginMenu("File"))
		{
		    // メニューごとの処理
		    if (ImGui::MenuItem("Save")) 
		    {

		    }
		    if (ImGui::MenuItem("Load"))
		    {
		    }

		    ImGui::EndMenu();
		}
			ImGui::EndMenuBar();	
	}

	// 座標
	if (ImGui::CollapsingHeader("Position"))
    {
        // テキスト表示
		ImGui::Text("X : %f", player_->getpTransform()->getpPosition()->x);
		ImGui::Text("Y : %f", player_->getpTransform()->getpPosition()->y);
		ImGui::Text("Z : %f", player_->getpTransform()->getpPosition()->z);
	}

	// 軸ベクトル
	if (ImGui::CollapsingHeader("Axis"))
    {
        // ノード
		ImGui::SetNextTreeNodeOpen(true, ImGuiSetCond_Once);
		if (ImGui::TreeNode("Right")) 
		{
			ImGui::Text("X : %f", player_->getpTransform()->getpRight()->x);
			ImGui::Text("Y : %f", player_->getpTransform()->getpRight()->y);
			ImGui::Text("Z : %f", player_->getpTransform()->getpRight()->z);

			ImGui::TreePop();
		}

		ImGui::SetNextTreeNodeOpen(true, ImGuiSetCond_Once);
		if (ImGui::TreeNode("Up")) 
		{
			ImGui::Text("X : %f", player_->getpTransform()->getpUp()->x);
			ImGui::Text("Y : %f", player_->getpTransform()->getpUp()->y);
			ImGui::Text("Z : %f", player_->getpTransform()->getpUp()->z);

			ImGui::TreePop();
		}

		ImGui::SetNextTreeNodeOpen(true, ImGuiSetCond_Once);
		if (ImGui::TreeNode("Forawrd")) 
		{
			ImGui::Text("X : %f", player_->getpTransform()->getpForawrd()->x);
			ImGui::Text("Y : %f", player_->getpTransform()->getpForawrd()->y);
			ImGui::Text("Z : %f", player_->getpTransform()->getpForawrd()->z);

			ImGui::TreePop();
		}
	}

	// 物理
	if (ImGui::CollapsingHeader("Physics"))
    {
        // ノード
		ImGui::SetNextTreeNodeOpen(true, ImGuiSetCond_Once);
		if (ImGui::TreeNode("Velocity")) 
		{
			ImGui::Text("X : %f", player_->getpPhysics()->getpVelocity()->x);
			ImGui::Text("Y : %f", player_->getpPhysics()->getpVelocity()->y);
			ImGui::Text("Z : %f", player_->getpPhysics()->getpVelocity()->z);

			ImGui::TreePop();
		}

		ImGui::SetNextTreeNodeOpen(true, ImGuiSetCond_Once);
		if (ImGui::TreeNode("Mass")) 
		{
			static float mass = 0.1f;
			ImGui::SliderFloat("slider 1", &mass, 0.1f, 2.0f);
			player_->getpPhysics()->setMass(mass);
			ImGui::TreePop();
		}

		ImGui::SetNextTreeNodeOpen(true, ImGuiSetCond_Once);
		if (ImGui::TreeNode("Friction")) 
		{
			static float friction = 0.0f;
			ImGui::SliderFloat("slider 1", &friction, 0.0f, 1.0f);
			player_->getpPhysics()->AddFriction(friction);
			ImGui::TreePop();
		}
	}

	// 終了
    ImGui::End();

    // 色の解放(設定でプッシュした分だけ)
    ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
#endif
}