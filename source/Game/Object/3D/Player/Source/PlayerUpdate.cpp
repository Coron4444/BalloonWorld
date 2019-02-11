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
#include <GameEngine/Collision/BulletPhysics/BulletPhysicsManager/BulletPhysicsManager.h>
#include <GameEngine/GameObject/GameObjectManager/GameObjectManager.h>
#include <Tool/MeterToFrame.h>
#include <Resource/Effekseer/EffekseerManager/EffekseerManager.h>
#include <Object/3D/Balloon/BalloonGroup.h>



//****************************************
// 定数定義
//****************************************
const float PlayerUpdate::SPEED = MeterToFrame::MeterPerSecondSquaredToMeterPerFrameSquared(50.0f);

static BulletPhysicsObject* test_;

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

	float mass = 0.0f;
	Vec3 inertia(0.0f, 0.0f, 0.0f);
	Quaternion quaternion(0.0f, 0.0f, 0.0f, 1.0f);
	Vec3 position(0.0f, 0.0f, 0.0f);
	test_ = BulletPhysicsManager::getpInstance()
		->getpObjectCapsule(mass, inertia, position, quaternion, 1.5f, 2.5f);
	test_->setKinematic();
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

	// 摩擦
	player_->getpPhysics()->AddFriction(0.9f);

	// ジャンプ
	if (InputManager::getpInstance()->getpKeyboard()->getTrigger(DIK_SPACE))
	{
		temp_vector = Vec3(0.0f, 1.0f, 0.0f);
		temp_vector.ChangeAnyLength(MeterToFrame::MeterPerSecondToMeterPerFlame(70.0f));

		*player_->getpPhysics()->getpVelocity() += temp_vector;
	}
	player_->getpTransform()->CreateAxisAndWorldMatrix();

	Vec test_pos = *player_->getpTransform()->getpPosition();
	test_pos.y += 2.0f;
	test_pos.z += 0.0f;
	test_->setPosition(test_pos);

	// 風船群の座標更新
	if (player_->getpBalloonGroup() == nullptr) return;
	Vec3 balloon_position = *player_->getpTransform()->getpPosition();
	balloon_position.y += 2.0f;
	balloon_position.z += -1.0f;
	player_->getpBalloonGroup()->setPosition(balloon_position);
	// 切り離し
	if (InputManager::getpInstance()->getpKeyboard()->getTrigger(DIK_M))
	{
		player_->getpBalloonGroup()->ReleaseConstraint();
	}

	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_N))
	{
		player_->getpBalloonGroup()->AddAcceleration(Vec3(-100.0f, 0.0f, 0.0f));
	}
}



void PlayerUpdate::DebugDisplay()
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