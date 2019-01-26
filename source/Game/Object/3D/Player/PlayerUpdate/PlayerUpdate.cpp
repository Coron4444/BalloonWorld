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

#include "PlayerUpdate.h"

#include <Keyboard\Keyboard.h>
#include <ConvertToFrame\MeterToFrame\MeterToFrame.h>

#include <3D/Player/PlayerUpdate_Special/PlayerUpdate_Special.h>
#include <GameObjectManager/GameObjectManager.h>
#include <Effekseer/EffekseerManager/EffekseerManager.h>


//======================================================================
//
// �萔��`
//
//======================================================================

const float PlayerUpdate::SPEED = MeterPerSecondSquared_To_MeterPerFrameSquared(50.0f);

static const std::string TEST_EFFEKSEER = "Beam/Beam.efk";



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

void PlayerUpdate::Init()
{
	// �_�E���L���X�g
	player_ = (Player*)getpGameObject();

	// ���̐ݒ�
	player_->CreatePhysics();
	player_->GetPhysics()->SetMaxVelocity(MeterPerSecond_To_MeterPerFlame(300.0f));
	player_->GetPhysics()->SetMass(8.0f);
	player_->GetPhysics()->SetMyFriction(1.0f);
	player_->GetPhysics()->SetMyBounciness(1.0f);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �I�������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PlayerUpdate::Uninit()
{
	
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �X�V�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PlayerUpdate::Update()
{
	// ���s�ړ�
	Vector3D temp_vector;

	if (GetKeyboardPress(DIK_D))
	{
		temp_vector += *player_->GetTransform()->GetRight();
	}
	if (GetKeyboardPress(DIK_A))
	{
		temp_vector += -*player_->GetTransform()->GetRight();
	}
	if (GetKeyboardPress(DIK_W))
	{
		temp_vector += *player_->GetTransform()->GetForawrd();
	}
	if (GetKeyboardPress(DIK_S))
	{
		temp_vector += -*player_->GetTransform()->GetForawrd();
	}

	*player_->GetPhysics()->GetAcceleration() += temp_vector.AnyLengthVector(SPEED);

	// �u���[�L
	if (GetKeyboardTrigger(DIK_N))
	{
		//GameObjectManager::GetUpdateManager()
			//->OverwriteArrayUpdateBase(player_, new PlayerUpdate_Special());
		//return;
		player_->GetPhysics()->AddFriction(0.5f);
	}

	player_->GetPhysics()->AddFriction(0.9f);

	// �W�����v
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		temp_vector = Vec3(0.0f, 1.0f, 0.0f);
		temp_vector.AnyLengthVector(MeterPerSecond_To_MeterPerFlame(30.0f));

		*player_->GetPhysics()->GetVelocity() += temp_vector;
	}

	// �g�k
	if (GetKeyboardPress(DIK_Z))
	{
		*player_->GetTransform()->GetScale() += Vec3(SPEED, SPEED, SPEED);
	}
	if (GetKeyboardPress(DIK_X))
	{
		*player_->GetTransform()->GetScale() += -Vec3(SPEED, SPEED, SPEED);
	}

	player_->GetTransform()->SetLookAtSpeed(0.05f);

	// ��]
	if (GetKeyboardPress(DIK_C))
	{
		player_->GetTransform()->SetLookAtVector(Vec3(1.0f, 1.0f, 0.0f));
	}
	if (GetKeyboardPress(DIK_V))
	{
		player_->GetTransform()->SetLookAtVector(Vec3(-1.0f, 0.0f, 0.0f));
	}
	if (GetKeyboardPress(DIK_B))
	{
		player_->GetTransform()->SetLookAtVector(Vec3(0.0f, 0.0f, -1.0f));
	}

	//float temp_scale = 1.0f;

	if (GetKeyboardTrigger(DIK_P))
	{
		EffekseerObject* temp_object = EffekseerManager::getpInstance()
			->getpDisposableObject(&TEST_EFFEKSEER);
		*temp_object->getpTransform()->GetPosition() = *player_->GetTransform()->GetPosition();
		temp_object->getpTransform()->UpdateWorldMatrixSRT();
		temp_object->Play();
	}

	player_->GetTransform()->UpdateAxisVector_WorldMatrixSRT();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ��X�V�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PlayerUpdate::LateUpdate()
{

}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �f�o�b�O�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PlayerUpdate::DebugDisplay()
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