//================================================================================
//!	@file	 PlayerUpdate_Special.cpp
//!	@brief	 �v���C���[�X�y�V�����X�VClass
//! @details 
//!	@author  Kai Araki									@date 2019/03/27
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../PlayerUpdate_Special.h"
#include "../PlayerUpdate.h"
#include "../Player.h"

#include <GameEngine/Input/InputManager/InputManager.h>
#include <GameEngine/GameObject/GameObjectManager/GameObjectManager.h>
#include <Tool/MeterToFrame.h>



//****************************************
// �萔��`
//****************************************
const float PlayerUpdate_Special::SPEED = MeterToFrame::MeterPerSecondSquaredToMeterPerFrameSquared(1.0f);



//****************************************
// �֐���`
//****************************************
void PlayerUpdate_Special::Init()
{
	// �_�E���L���X�g
	player_ = (Player*)getpGameObject();

	// ���̐ݒ�
	player_->CreatePhysics();
	player_->getpPhysics()->setMaxHorizontalVelocity(MeterToFrame::MeterPerSecondToMeterPerFlame(10.0f));
	player_->getpPhysics()->setMaxVerticalVelocity(MeterToFrame::MeterPerSecondToMeterPerFlame(10.0f));
	player_->getpPhysics()->setMass(0.1f);
	player_->getpPhysics()->setMyFriction(1.0f);
	player_->getpPhysics()->setMyBounciness(1.0f);
}



void PlayerUpdate_Special::Update()
{
	// ���s�ړ�
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

	// �u���[�L
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
		ImGui::Text("X : %f", player_->getpTransform()->getpPosition()->x);
		ImGui::Text("Y : %f", player_->getpTransform()->getpPosition()->y);
		ImGui::Text("Z : %f", player_->getpTransform()->getpPosition()->z);
	}

	// ���x�N�g��
	if (ImGui::CollapsingHeader("Axis"))
	{
		// �m�[�h
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

	// ����
	if (ImGui::CollapsingHeader("Physics"))
	{
		// �m�[�h
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

	// �I��
	ImGui::End();

	// �F�̉��(�ݒ�Ńv�b�V������������)
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
#endif
}