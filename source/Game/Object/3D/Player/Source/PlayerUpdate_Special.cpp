//================================================================================
//!	@file	 PlayerUpdate_Special.cpp
//!	@brief	 プレイヤースペシャル更新Class
//! @details 
//!	@author  Kai Araki									@date 2019/03/27
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../PlayerUpdate_Special.h"
#include "../PlayerUpdate.h"
#include "../Player.h"

#include <GameEngine/Input/InputManager/InputManager.h>
#include <GameEngine/GameObject/GameObjectManager/GameObjectManager.h>
#include <Tool/MeterToFrame.h>



//****************************************
// 定数定義
//****************************************
const float PlayerUpdate_Special::SPEED = MeterToFrame::MeterPerSecondSquaredToMeterPerFrameSquared(1.0f);



//****************************************
// 関数定義
//****************************************
void PlayerUpdate_Special::Init()
{
	// ダウンキャスト
	player_ = (Player*)getpGameObject();

	// 剛体設定
	player_->CreatePhysics();
	player_->getpPhysics()->setMaxHorizontalVelocity(MeterToFrame::MeterPerSecondToMeterPerFlame(10.0f));
	player_->getpPhysics()->setMaxVerticalVelocity(MeterToFrame::MeterPerSecondToMeterPerFlame(10.0f));
	player_->getpPhysics()->setMass(0.1f);
	player_->getpPhysics()->setMyFriction(1.0f);
	player_->getpPhysics()->setMyBounciness(1.0f);
}



void PlayerUpdate_Special::Update()
{
	// 平行移動
	Vector3D temp_vector;

	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_RIGHT))
	{
		temp_vector += *player_->getpTransform()->getpRight();
	}
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_LEFT))
	{
		temp_vector += -*player_->getpTransform()->getpRight();
	}
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_UP))
	{
		temp_vector += *player_->getpTransform()->getpForawrd();
	}
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_DOWN))
	{
		temp_vector += -*player_->getpTransform()->getpForawrd();
	}

	*player_->getpPhysics()->getpAcceleration() += *temp_vector.ChangeAnyLength(SPEED);

	// ブレーキ
	if (InputManager::getpInstance()->getpKeyboard()->getTrigger(DIK_N))
	{
		GameObjectManager::getpInstance()->getpUpdateManager()
			->OverwriteArrayUpdateBase(player_, new PlayerUpdate());
		return;
	}


	player_->getpTransform()->CreateAxisAndWorldMatrix();
}



void PlayerUpdate_Special::DebugDisplay()
{
#ifdef _DEBUG
	// ウィンドウの設定
	ImGui::SetNextWindowPos(ImVec2(30, 30), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(150, 500), ImGuiSetCond_Once);
	ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(1.0f, 0.0f, 0.0f, 0.8f));
	ImGui::PushStyleColor(ImGuiCol_TitleBgCollapsed, ImVec4(0.0f, 0.5f, 1.0f, 0.8f));
	ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.5f, 0.0f, 0.0f, 0.8f));
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