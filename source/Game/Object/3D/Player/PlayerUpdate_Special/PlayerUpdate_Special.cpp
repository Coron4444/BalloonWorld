//================================================================================
//
//    �v���C���[�X�V�N���X
//    Author : Araki Kai                                �쐬�� : 2018/03/27
//
//================================================================================



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include "PlayerUpdate_Special.h"

#include <Keyboard\Keyboard.h>
#include <ConvertToFrame\MeterToFrame\MeterToFrame.h>
#include <3D/Player/PlayerUpdate/PlayerUpdate.h>
#include <GameObjectManager/GameObjectManager.h>



//======================================================================
//
// �萔��`
//
//======================================================================

const float PlayerUpdate_Special::SPEED = MeterPerSecondSquared_To_MeterPerFrameSquared(1.0f);

static const std::string TEST_EFFEKSEER = "Beam/Beam.efk";

//static EffekseerObject* temp_object_;

//======================================================================
//
// ��ÓI�����o�֐���`
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PlayerUpdate_Special::Init()
{
	// �_�E���L���X�g
	player_ = (Player*)getpGameObject();

	// ���̐ݒ�
	player_->CreatePhysics();
	player_->GetPhysics()->SetMaxVelocity(MeterPerSecond_To_MeterPerFlame(10.0f));
	player_->GetPhysics()->SetMass(0.1f);
	player_->GetPhysics()->SetMyFriction(1.0f);
	player_->GetPhysics()->SetMyBounciness(1.0f);

	//EffekseerManager::AddUniqueData(&TEST_EFFEKSEER);

	//temp_object_ = EffekseerManager::GetReferenceEffekseerObject(&TEST_EFFEKSEER);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �I�������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PlayerUpdate_Special::Uninit()
{
	
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �X�V�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PlayerUpdate_Special::Update()
{
	// ���s�ړ�
	Vector3D temp_vector;

	if (GetKeyboardPress(DIK_RIGHT))
	{
		temp_vector += *player_->GetTransform()->GetRight();
	}
	if (GetKeyboardPress(DIK_LEFT))
	{
		temp_vector += -*player_->GetTransform()->GetRight();
	}
	if (GetKeyboardPress(DIK_UP))
	{
		temp_vector += *player_->GetTransform()->GetForawrd();
	}
	if (GetKeyboardPress(DIK_DOWN))
	{
		temp_vector += -*player_->GetTransform()->GetForawrd();
	}

	*player_->GetPhysics()->GetAcceleration() += temp_vector.AnyLengthVector(SPEED);

	// �u���[�L
	if (GetKeyboardTrigger(DIK_N))
	{
		GameObjectManager::GetUpdateManager()
			->OverwriteArrayUpdateBase(player_, new PlayerUpdate());
		return;
	}


	player_->GetTransform()->UpdateAxisVector_WorldMatrixSRT();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ��X�V�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PlayerUpdate_Special::LateUpdate()
{

}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �f�o�b�O�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PlayerUpdate_Special::DebugDisplay()
{
#ifdef _DEBUG
	 // �E�B���h�E�̐ݒ�
    ImGui::SetNextWindowPos(ImVec2(30, 30), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(150, 500), ImGuiSetCond_Once);
	ImGui::PushStyleColor(ImGuiCol_TitleBgActive,    ImVec4(1.0f, 0.0f, 0.0f, 0.8f));
    ImGui::PushStyleColor(ImGuiCol_TitleBgCollapsed, ImVec4(0.0f, 0.5f, 1.0f, 0.8f));
	ImGui::PushStyleColor(ImGuiCol_TitleBg,          ImVec4(0.5f, 0.0f, 0.0f, 0.8f));
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
		ImGui::Text("X : %f", player_->GetTransform()->GetPosition()->x);
		ImGui::Text("Y : %f", player_->GetTransform()->GetPosition()->y);
		ImGui::Text("Z : %f", player_->GetTransform()->GetPosition()->z);
	}

	// ���x�N�g��
	if (ImGui::CollapsingHeader("Axis"))
    {
        // �m�[�h
		ImGui::SetNextTreeNodeOpen(true, ImGuiSetCond_Once);
		if (ImGui::TreeNode("Right")) 
		{
			ImGui::Text("X : %f", player_->GetTransform()->GetRight()->x);
			ImGui::Text("Y : %f", player_->GetTransform()->GetRight()->y);
			ImGui::Text("Z : %f", player_->GetTransform()->GetRight()->z);

			ImGui::TreePop();
		}

		ImGui::SetNextTreeNodeOpen(true, ImGuiSetCond_Once);
		if (ImGui::TreeNode("Up")) 
		{
			ImGui::Text("X : %f", player_->GetTransform()->GetUp()->x);
			ImGui::Text("Y : %f", player_->GetTransform()->GetUp()->y);
			ImGui::Text("Z : %f", player_->GetTransform()->GetUp()->z);

			ImGui::TreePop();
		}

		ImGui::SetNextTreeNodeOpen(true, ImGuiSetCond_Once);
		if (ImGui::TreeNode("Forawrd")) 
		{
			ImGui::Text("X : %f", player_->GetTransform()->GetForawrd()->x);
			ImGui::Text("Y : %f", player_->GetTransform()->GetForawrd()->y);
			ImGui::Text("Z : %f", player_->GetTransform()->GetForawrd()->z);

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
			ImGui::Text("X : %f", player_->GetPhysics()->GetVelocity()->x);
			ImGui::Text("Y : %f", player_->GetPhysics()->GetVelocity()->y);
			ImGui::Text("Z : %f", player_->GetPhysics()->GetVelocity()->z);

			ImGui::TreePop();
		}

		ImGui::SetNextTreeNodeOpen(true, ImGuiSetCond_Once);
		if (ImGui::TreeNode("Mass")) 
		{
			static float mass = 0.1f;
			ImGui::SliderFloat("slider 1", &mass, 0.1f, 2.0f);
			player_->GetPhysics()->SetMass(mass);
			ImGui::TreePop();
		}

		ImGui::SetNextTreeNodeOpen(true, ImGuiSetCond_Once);
		if (ImGui::TreeNode("Friction")) 
		{
			static float friction = 0.0f;
			ImGui::SliderFloat("slider 1", &friction, 0.0f, 1.0f);
			player_->GetPhysics()->AddFriction(friction);
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