//================================================================================
//!	@file	 Player.cpp
//!	@brief	 �v���C���[Class
//! @details 
//!	@author  Kai Araki									@date 2018/04/01
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../Player.h"

#include <GameEngine/Draw/Camera/Camera.h>
#include <GameEngine/Collision/BulletPhysics/BulletPhysicsManager/BulletPhysicsManager.h>

#include <Object/3D/Balloon/BalloonGroup.h>



//****************************************
// �萔��`
//****************************************
const float Player::ACCELERATION
= MeterToFrame::MeterPerSecondSquaredToMeterPerFrameSquared(200.0f);
const float Player::MAX_VERTICAL_VELOCITY
= MeterToFrame::MeterPerSecondToMeterPerFlame(500.0f);
const float Player::MAX_MASS = 80.0f;



//****************************************
// �v���p�e�B��`
//****************************************
void Player::setPosition(Vector3D value)
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
	getpPhysics()->setMaxVerticalVelocity(MAX_VERTICAL_VELOCITY / (balloon_group_->getRemainingBalloonNum() + 1));
	getpPhysics()->setMass(MAX_MASS / (balloon_group_->getRemainingBalloonNum() + 1));
}



Camera* Player::getpCamera()
{
	return camera_;
}



void Player::setCamera(Camera* value)
{
	camera_ = value;
}



bool Player::getIsOnTheGround()
{
	return is_on_the_ground_;
}



void Player::setIsOnTheGround(bool value)
{
	is_on_the_ground_ = value;
}


int Player::getScore()
{
	int temp = score_;
	score_ = 0;
	return temp;
}



int Player::getAnimCount()
{
	return anim_counter_;
}



void Player::setAnimCount(int value)
{
	anim_counter_ = value;
}



//****************************************
// �֐���`
//****************************************
void Player::Init(DrawBase* draw, CollisionBase* collision)
{
	// �����p��
	getpTransform()->setInitAngle(Vector3D(0.0f, D3DXToRadian(-90.0f), 0.0f));
	*getpTransform()->getpLookAtSpeed() = 0.1f;

	// ���̐ݒ�
	CreatePhysics();
	getpPhysics()->setMaxHorizontalVelocity(MeterToFrame::MeterPerSecondToMeterPerFlame(10000.0f));
	getpPhysics()->setMaxVerticalVelocity(MAX_VERTICAL_VELOCITY);
	getpPhysics()->setMass(MAX_MASS);
	getpPhysics()->setMyFriction(1.0f);
	getpPhysics()->setMyBounciness(1.0f);

	// �o���b�g�I�u�W�F�N�g
	float mass = 0.0f;
	Vector3D inertia(0.0f, 0.0f, 0.0f);
	Quaternion quaternion(0.0f, 0.0f, 0.0f, 1.0f);
	Vector3D position(0.0f, 0.0f, 0.0f);
	float radius = 1.5f;
	float height = 2.5f;
	bullet_object_ = BulletPhysicsManager::getpInstance()
		->getpObjectCapsule(mass, inertia, position, quaternion, radius, height);
	bullet_object_->setKinematic();

	// ���N���X�̏�����
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
	// ����
	Input();

	// ���C�ǉ�
	getpPhysics()->AddFriction(0.85f);
	getpTransform()->CreateWorldMatrix();

	// �o���b�g�I�u�W�F�N�g
	Vec bullet_position = *getpTransform()->getpPosition();
	bullet_position.y += 2.0f;
	bullet_object_->setPosition(bullet_position);

	// ���D�Q�̍��W�X�V
	if (getpBalloonGroup() == nullptr) return;
	Vector3D balloon_position(0.0f, 2.0f, -1.0f);
	Matrix balloon_position_matrix;
	balloon_position_matrix.Init();
	balloon_position_matrix.CreatePosition(&balloon_position);
	balloon_position_matrix.AddParentMatrix(getpTransform()
											->getpNoInitRotationWorldMatrix());
	getpBalloonGroup()->setPosition(balloon_position_matrix.getPosition());

	anim_counter_++;
}



void Player::AddScore(int value)
{
	score_ += value;
}



void Player::Input()
{
	if (getIsInput())
	{
		camera_ != nullptr ? InputTranslation() : InputTranslationNotCamera();
		InputBalloon();
	}
	else
	{
		anim_counter_ = 0;
	}
}



void Player::InputTranslation()
{
	bool is_input = false;
	Vector3D look_at_vector;
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_W) ||
		InputManager::getpInstance()->getpController()->getHoldLStick(0, Controller::Direction::UP))
	{
		is_input = true;
		look_at_vector += *camera_->getpForward();
	}
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_S) ||
		InputManager::getpInstance()->getpController()->getHoldLStick(0, Controller::Direction::DOWN))
	{
		is_input = true;
		look_at_vector += -(*camera_->getpForward());
	}
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_A) ||
		InputManager::getpInstance()->getpController()->getHoldLStick(0, Controller::Direction::LEFT))
	{
		is_input = true;
		look_at_vector += -(*camera_->getpRight());
	}
	if (InputManager::getpInstance()->getpKeyboard()->getHold(DIK_D) ||
		InputManager::getpInstance()->getpController()->getHoldLStick(0, Controller::Direction::RIGHT))
	{
		is_input = true;
		look_at_vector += *camera_->getpRight();
	}

	if (is_input)
	{
		look_at_vector.y = 0.0f;
		getpTransform()->setLookAtVector(look_at_vector);
		Vector3D acceleration = *getpTransform()->getpForward();
		*getpPhysics()->getpAcceleration()
			+= *acceleration.ChangeAnyLength(ACCELERATION);
	}
	else
	{
		anim_counter_ = 0;
	}
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

	if (is_input)
	{
		getpTransform()->setLookAtVector(look_at_vector);
		Vector3D acceleration = *getpTransform()->getpForward();
		*getpPhysics()->getpAcceleration()
			+= *acceleration.ChangeAnyLength(ACCELERATION);
	}
	else
	{
		anim_counter_ = 0;
	}
}



void Player::InputBalloon()
{
	// �؂藣��
	if (InputManager::getpInstance()->getpKeyboard()->getTrigger(DIK_SPACE) ||
		InputManager::getpInstance()->getpController()->getTrigger(0, XINPUT_GAMEPAD_X))
	{
		getpBalloonGroup()->ReleaseConstraint();
		getpPhysics()->setMaxVerticalVelocity(MAX_VERTICAL_VELOCITY / (balloon_group_->getRemainingBalloonNum() + 1));
		getpPhysics()->setMass(MAX_MASS / (balloon_group_->getRemainingBalloonNum() + 1));

		if (balloon_group_->getRemainingBalloonNum() >= 0)
		{
			SoundManager::getpInstance()->PlayOrStop(SoundManager::Type::SE_PURGE);
		}
	}
}



/*
void Player::DebugDisplay()
{
#ifdef _DEBUG
	// �E�B���h�E�̐ݒ�
	ImGui::SetNextWindowPos(ImVec2(30, 30), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(150, 500), ImGuiSetCond_Once);
	ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(1.0f, 0.0f, 0.0f, 0.8f));
	ImGui::PushStyleColor(ImGuiCol_TitleBgCollapsed, ImVec4(0.0f, 0.5f, 1.0f, 0.8f));
	ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.5f, 0.0f, 0.0f, 0.8f));
	ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.0f, 0.5f, 0.5f, 1.0f));

	// �J�n
	ImGui::Begin("Player", nullptr, ImGuiWindowFlags_MenuBar);

	// ���j���[
	if (ImGui::BeginMenuBar())
	{
		// ���j���[��
		if (ImGui::BeginMenu("File"))
		{
			// ���j���[���Ƃ̏���
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

	// ���W
	if (ImGui::CollapsingHeader("Position"))
	{
		// �e�L�X�g�\��
		ImGui::Text("X : %f", getpTransform()->getpPosition()->x);
		ImGui::Text("Y : %f", getpTransform()->getpPosition()->y);
		ImGui::Text("Z : %f", getpTransform()->getpPosition()->z);
	}

	// ���x�N�g��
	if (ImGui::CollapsingHeader("Axis"))
	{
		// �m�[�h
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

	// ����
	if (ImGui::CollapsingHeader("Physics"))
	{
		// �m�[�h
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

	// �I��
	ImGui::End();

	// �F�̉��(�ݒ�Ńv�b�V������������)
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
#endif
}
*/