//================================================================================
//!	@file	 PlayerCollision.cpp
//!	@brief	 �v���C���[�Փ�Class
//! @details 
//!	@author  Kai Araki									@date 2018/03/27
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../PlayerCollision.h"
#include "../Player.h"

#include <GameEngine/Renderer/Renderer.h>
#include <GameEngine/GameObject/GameObjectManager/GameObjectManager.h>
#include <Object/3D/Coin/Coin.h>
#include <Object/3D/Coin/CoinCollision.h>
#include <Object/3D/Enemy/EnemyCollision.h>
#include <Resource/Polygon/MeshPlanePolygon.h>



//****************************************
// �萔��`
//****************************************
const float PlayerCollision::MAIN_SPHERE_RADIUS = 2.0f;



//****************************************
// �֐���`
//****************************************
void PlayerCollision::Init()
{
	// �^�C�v
	CollisionBase::setType(CollisionBase::Type::PLAYER);

	//�_�E���L���X�g
	player_ = (Player*)getpGameObject();

	// �Փ˃I�u�W�F�N�g�쐬
	collision_object_ = new CollisionObject();
	collision_object_->Init((int)ObjectTag::MAIN, this);
	CollisionBase::AddCollisionObject(collision_object_);

	// ���C�����̍쐬
	main_sphere_ = new Sphere();
	Vector3D position = *getpGameObject()->getpTransform()->getpPosition();
	position.y += 2.0f;
	main_sphere_->Init(position, MAIN_SPHERE_RADIUS);
	collision_object_->AddShape((int)ShapeTag::MAIN, main_sphere_);
}



void PlayerCollision::Update()
{
	// ���C�����̍X�V
	Vector3D position = *getpGameObject()->getpTransform()->getpPosition();
	position.y += 2.0f;
	*main_sphere_->getpPosition() = position;
}



void PlayerCollision::HitCollision(CollisionInformation* information)
{
	// �����̏Փˌ`��ŐU�蕪����
	switch ((PlayerCollision::ShapeTag)information->getpMyShape()->getTag())
	{
		case PlayerCollision::ShapeTag::MAIN:
		{
			HitMainSphere(information);
			normal_ = *information->getpCollisionPointNormal();
			break;
		}
	}
}



void PlayerCollision::HitGround(float position_y)
{
	// �_�E���L���X�g
	Player* player = (Player*)getpGameObject();

	// �n�ʂ̏�ɗ���
	player->getpTransform()->getpPosition()->y = position_y;
	player->getpTransform()->CreateWorldMatrix();

	if (player->getpPhysics() == nullptr) return;
	player->getpPhysics()->setOnTheGround();
}



void PlayerCollision::HitMainSphere(CollisionInformation* information)
{
	// ����Փˊ��N���X�ŐU�蕪��
	switch (information->getpOpponentCollisionBase()->getType())
	{
		case CollisionBase::Type::COIN:
		{
			// ����̏Փˌ`��ŐU�蕪��
			switch ((CoinCollision::ShapeTag)information->getpOpponentShape()
					->getTag())
			{
				case CoinCollision::ShapeTag::MAIN:
				{
					Coin* coin = (Coin*)information->getpOpponentGameObject();
					if (*coin->getpColorChangeCounter() <= 0)
					{
						*coin->getpColorChangeCounter() = 120;
					}

					// �߂荞�݉���
					CollisionCalculation
						::EliminationOfNesting(information, 
											   player_->getpTransform());

					// ����̃I�u�W�F�N�g������
					//GameObjectManager::ReleaseGameObjectBaseFromArray(hit_collision->getpGameObject());
					break;
				}
			}
			break;
		}
		case CollisionBase::Type::ENEMY:
		{
			// ����̏Փˌ`��ŐU�蕪��
			switch ((EnemyCollision::ShapeTag)information->getpOpponentShape()
					->getTag())
			{
				case EnemyCollision::ShapeTag::MAIN:
				{
					// �߂荞�݉���
					CollisionCalculation
						::EliminationOfNesting(information,
											   player_->getpTransform());

					//// ����̃I�u�W�F�N�g������
					//GameObjectManager::getpInstance()
					//	->ReleaseGameObjectBaseFromArray(hit_collision->getpGameObject());
					break;
				}
			}
			break;
		}
		case CollisionBase::Type::GOAL:
		{
			// ����̏Փˌ`��ŐU�蕪��
			switch ((EnemyCollision::ShapeTag)information->getpOpponentShape()
					->getTag())
			{
				case EnemyCollision::ShapeTag::MAIN:
				{
					// �߂荞�݉���
					CollisionCalculation
						::EliminationOfNesting(information,
											   player_->getpTransform());

					//// ����̃I�u�W�F�N�g������
					//GameObjectManager::getpInstance()
					//	->ReleaseGameObjectBaseFromArray(hit_collision->getpGameObject());
					break;
				}
			}
			break;
		}
	}
}



void PlayerCollision::DebugDisplay()
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

	ImGui::Text("X : %f", normal_.x);
	ImGui::Text("Y : %f", normal_.y);
	ImGui::Text("Z : %f", normal_.z);

	// �I��
	ImGui::End();

	// �F�̉��(�ݒ�Ńv�b�V������������)
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
#endif
}