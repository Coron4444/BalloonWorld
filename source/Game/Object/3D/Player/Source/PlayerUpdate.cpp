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

#include <GameEngine/Draw/Camera/Camera.h>
#include <GameEngine/Input/InputManager/InputManager.h>
#include <GameEngine/Collision/BulletPhysics/BulletPhysicsManager/BulletPhysicsManager.h>
#include <GameEngine/GameObject/GameObjectManager/GameObjectManager.h>
#include <Tool/MeterToFrame.h>
#include <Resource/Effekseer/EffekseerManager/EffekseerManager.h>
#include <Object/3D/Balloon/BalloonGroup.h>



//****************************************
// 定数定義
//****************************************
const float PlayerUpdate::ACCELERATION
= MeterToFrame::MeterPerSecondSquaredToMeterPerFrameSquared(100.0f);



//****************************************
// 関数定義
//****************************************
void PlayerUpdate::Init()
{
	// ダウンキャスト
	player_ = (Player*)getpGameObject();

	// 初期姿勢
	player_->getpTransform()->setInitAngle(Vector3D(0.0f, D3DXToRadian(-90.0f), 0.0f));
	*player_->getpTransform()->getpLookAtSpeed() = 0.1f;

	// 剛体設定
	player_->CreatePhysics();
	player_->getpPhysics()->setMaxHorizontalVelocity(MeterToFrame::MeterPerSecondToMeterPerFlame(10000.0f));
	player_->getpPhysics()->setMaxVerticalVelocity(MeterToFrame::MeterPerSecondToMeterPerFlame(10.0f));
	player_->getpPhysics()->setMass(3.0f);
	player_->getpPhysics()->setMyFriction(1.0f);
	player_->getpPhysics()->setMyBounciness(1.0f);

	
	// バレットオブジェクト
	float mass = 0.0f;
	Vec3 inertia(0.0f, 0.0f, 0.0f);
	Quaternion quaternion(0.0f, 0.0f, 0.0f, 1.0f);
	Vec3 position(0.0f, 0.0f, 0.0f);
	float radius = 1.5f;
	float height = 2.5f;
	bullet_object_ = BulletPhysicsManager::getpInstance()
		->getpObjectCapsule(mass, inertia, position, quaternion, radius, height);
	bullet_object_->setKinematic();
}



void PlayerUpdate::Update()
{
	// 入力
	player_->getpCamera() != nullptr ? InputTranslation() : InputTranslationNotCamera();
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_SPACE))
	{
		Vector3D temp_vector = Vec3(0.0f, 1.0f, 0.0f);
		temp_vector.ChangeAnyLength(MeterToFrame::MeterPerSecondToMeterPerFlame(150.0f));
		*player_->getpPhysics()->getpVelocity() += temp_vector;
	}

	// 摩擦
	player_->getpPhysics()->AddFriction(0.85f);

	player_->getpTransform()->CreateAxisAndWorldMatrix();

	// バレットオブジェクト
	Vec bullet_position = *player_->getpTransform()->getpPosition();
	bullet_position.y += 2.0f;
	bullet_object_->setPosition(bullet_position);

	// 風船群の座標更新
	if (player_->getpBalloonGroup() == nullptr) return;
	Vector3D balloon_position(0.0f, 2.0f, -1.0f);
	MatrixGroup balloon_matrix;
	balloon_matrix.setPositionMatrix(&balloon_position);
	balloon_matrix.CreateWorldMatrix();
	balloon_matrix.AddParentMatrixToWorldMatrix(player_->getpTransform()
												->getpNoInitRotationWorldMatrix());
	player_->getpBalloonGroup()->setPosition(balloon_matrix.getPosition());
	
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



void PlayerUpdate::InputTranslation()
{
	Axis* camera_axis = player_->getpCamera()->getpAxis();
	bool is_input = false;
	Vector3D look_at_vector;
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_W))
	{
		is_input = true;
		look_at_vector += *camera_axis->getpForawrd();
	}
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_S))
	{
		is_input = true;
		look_at_vector += -(*camera_axis->getpForawrd());
	}
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_A))
	{
		is_input = true;
		look_at_vector += -(*camera_axis->getpRight());
	}
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_D))
	{
		is_input = true;
		look_at_vector += *camera_axis->getpRight();
	}
	
	if (!is_input) return;
	look_at_vector.y = 0.0f;
	player_->getpTransform()->setLookAtVector(look_at_vector);
	Vector3D acceleration = *player_->getpTransform()->getpForawrd();
	*player_->getpPhysics()->getpAcceleration()
		+= *acceleration.ChangeAnyLength(ACCELERATION);
}



void PlayerUpdate::InputTranslationNotCamera()
{
	bool is_input = false;
	Vector3D look_at_vector;
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_W))
	{
		is_input = true;
		look_at_vector += Vector3D(0.0f, 0.0f, 1.0f);
	}
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_S))
	{
		is_input = true;
		look_at_vector += Vector3D(0.0f, 0.0f, -1.0f);
	}
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_A))
	{
		is_input = true;
		look_at_vector += Vector3D(-1.0f, 0.0f, 0.0f);
	}
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_D))
	{
		is_input = true;
		look_at_vector += Vector3D(1.0f, 0.0f, 0.0f);
	}

	if (!is_input) return;	
	player_->getpTransform()->setLookAtVector(look_at_vector);
	Vector3D acceleration = *player_->getpTransform()->getpForawrd();
	*player_->getpPhysics()->getpAcceleration() 
		+= *acceleration.ChangeAnyLength(ACCELERATION);
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