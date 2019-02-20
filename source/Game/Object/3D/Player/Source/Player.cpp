//================================================================================
//!	@file	 Player.cpp
//!	@brief	 プレイヤーClass
//! @details 
//!	@author  Kai Araki									@date 2018/04/01
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../Player.h"

#include <GameEngine/Draw/Camera/Camera.h>
#include <GameEngine/Input/InputManager/InputManager.h>
#include <GameEngine/Collision/BulletPhysics/BulletPhysicsManager/BulletPhysicsManager.h>
#include <Tool/MeterToFrame.h>
#include <Resource/Effekseer/EffekseerManager/EffekseerManager.h>
#include <Object/3D/Balloon/BalloonGroup.h>



//****************************************
// 定数定義
//****************************************
const float Player::ACCELERATION
= MeterToFrame::MeterPerSecondSquaredToMeterPerFrameSquared(200.0f);
const float Player::MAX_VERTICAL_VELOCITY
= MeterToFrame::MeterPerSecondToMeterPerFlame(500.0f);
const float Player::MAX_MASS = 80.0f;



//****************************************
// プロパティ定義
//****************************************
void Player::setPosition(Vec3 value)
{
	*getpTransform()->getpPosition() = value;
	getpTransform()->CreateWorldMatrix();
}

BalloonGroup* Player::getpBalloonGroup()
{
	return balloon_group_;
}



void Player::setBalloonGroup(BalloonGroup* value)
{
	value->getpReferenceList()->getpMyPointer(&balloon_group_);
	getpPhysics()->setMaxVerticalVelocity(MAX_VERTICAL_VELOCITY / balloon_group_->getBalloonNum());
	getpPhysics()->setMass(MAX_MASS / balloon_group_->getBalloonNum());
}



Camera* Player::getpCamera()
{
	return camera_;
}



void Player::setCamera(Camera* value)
{
	camera_ = value;
}



//****************************************
// 関数定義
//****************************************
void Player::Init(DrawBase* draw, CollisionBase* collision)
{
	// 初期姿勢
	getpTransform()->setInitAngle(Vector3D(0.0f, D3DXToRadian(-90.0f), 0.0f));
	*getpTransform()->getpLookAtSpeed() = 0.1f;

	// 剛体設定
	CreatePhysics();
	getpPhysics()->setMaxHorizontalVelocity(MeterToFrame::MeterPerSecondToMeterPerFlame(10000.0f));
	getpPhysics()->setMaxVerticalVelocity(MAX_VERTICAL_VELOCITY);
	getpPhysics()->setMass(MAX_MASS);
	getpPhysics()->setMyFriction(1.0f);
	getpPhysics()->setMyBounciness(1.0f);

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

	// 基底クラスの初期化
	GameObjectBase::Init(draw, collision);
}



void Player::Uninit()
{
	UninitComponent();

	if (balloon_group_ == nullptr) return;
	balloon_group_->getpReferenceList()->ReleaseReference(&balloon_group_);
}



void Player::Update()
{
	// 入力
	camera_ != nullptr ? InputTranslation() : InputTranslationNotCamera();
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_SPACE))
	{
		Vector3D temp_vector = Vec3(0.0f, 1.0f, 0.0f);
		temp_vector.ChangeAnyLength(MeterToFrame::MeterPerSecondToMeterPerFlame(150.0f));
		*getpPhysics()->getpVelocity() += temp_vector;
	}

	// 摩擦
	getpPhysics()->AddFriction(0.85f);

	getpTransform()->CreateAxisAndWorldMatrix();

	// バレットオブジェクト
	Vec bullet_position = *getpTransform()->getpPosition();
	bullet_position.y += 2.0f;
	bullet_object_->setPosition(bullet_position);

	// 風船群の座標更新
	if (getpBalloonGroup() == nullptr) return;
	Vector3D balloon_position(0.0f, 2.0f, -1.0f);
	MatrixGroup balloon_matrix;
	balloon_matrix.setPositionMatrix(&balloon_position);
	balloon_matrix.CreateWorldMatrix();
	balloon_matrix.AddParentMatrixToWorldMatrix(getpTransform()
												->getpNoInitRotationWorldMatrix());
	getpBalloonGroup()->setPosition(balloon_matrix.getPosition());

	// 切り離し
	if (InputManager::getpInstance()->getpKeyboard()->getTrigger(DIK_M))
	{
		getpBalloonGroup()->ReleaseConstraint();
		getpPhysics()->setMaxVerticalVelocity(MAX_VERTICAL_VELOCITY / balloon_group_->getBalloonNum());
		getpPhysics()->setMass(MAX_MASS / balloon_group_->getBalloonNum());
	}

	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_N))
	{
		getpBalloonGroup()->AddAcceleration(Vec3(-100.0f, 0.0f, 0.0f));
	}
}



void Player::InputTranslation()
{
	Axis* camera_axis = camera_->getpAxis();
	bool is_input = false;
	Vector3D look_at_vector;
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_W))
	{
		is_input = true;
		look_at_vector += *camera_axis->getpForward();
	}
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_S))
	{
		is_input = true;
		look_at_vector += -(*camera_axis->getpForward());
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
	getpTransform()->setLookAtVector(look_at_vector);
	Vector3D acceleration = *getpTransform()->getpForward();
	*getpPhysics()->getpAcceleration()
		+= *acceleration.ChangeAnyLength(ACCELERATION);
}



void Player::InputTranslationNotCamera()
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
	getpTransform()->setLookAtVector(look_at_vector);
	Vector3D acceleration = *getpTransform()->getpForward();
	*getpPhysics()->getpAcceleration()
		+= *acceleration.ChangeAnyLength(ACCELERATION);
}



void Player::DebugDisplay()
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
		ImGui::Text("X : %f", getpTransform()->getpPosition()->x);
		ImGui::Text("Y : %f", getpTransform()->getpPosition()->y);
		ImGui::Text("Z : %f", getpTransform()->getpPosition()->z);
	}

	// 軸ベクトル
	if (ImGui::CollapsingHeader("Axis"))
	{
		// ノード
		ImGui::SetNextTreeNodeOpen(true, ImGuiSetCond_Once);
		if (ImGui::TreeNode("Right"))
		{
			ImGui::Text("X : %f", getpTransform()->getpRight()->x);
			ImGui::Text("Y : %f", getpTransform()->getpRight()->y);
			ImGui::Text("Z : %f", getpTransform()->getpRight()->z);

			ImGui::TreePop();
		}

		ImGui::SetNextTreeNodeOpen(true, ImGuiSetCond_Once);
		if (ImGui::TreeNode("Up"))
		{
			ImGui::Text("X : %f", getpTransform()->getpUp()->x);
			ImGui::Text("Y : %f", getpTransform()->getpUp()->y);
			ImGui::Text("Z : %f", getpTransform()->getpUp()->z);

			ImGui::TreePop();
		}

		ImGui::SetNextTreeNodeOpen(true, ImGuiSetCond_Once);
		if (ImGui::TreeNode("Forward"))
		{
			ImGui::Text("X : %f", getpTransform()->getpForward()->x);
			ImGui::Text("Y : %f", getpTransform()->getpForward()->y);
			ImGui::Text("Z : %f", getpTransform()->getpForward()->z);

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
			ImGui::Text("X : %f", getpPhysics()->getpVelocity()->x);
			ImGui::Text("Y : %f", getpPhysics()->getpVelocity()->y);
			ImGui::Text("Z : %f", getpPhysics()->getpVelocity()->z);

			ImGui::TreePop();
		}

		ImGui::SetNextTreeNodeOpen(true, ImGuiSetCond_Once);
		if (ImGui::TreeNode("Mass"))
		{
			static float mass = 0.1f;
			ImGui::SliderFloat("slider 1", &mass, 0.1f, 2.0f);
			getpPhysics()->setMass(mass);
			ImGui::TreePop();
		}

		ImGui::SetNextTreeNodeOpen(true, ImGuiSetCond_Once);
		if (ImGui::TreeNode("Friction"))
		{
			static float friction = 0.0f;
			ImGui::SliderFloat("slider 1", &friction, 0.0f, 1.0f);
			getpPhysics()->AddFriction(friction);
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