//================================================================================
//!	@file	 CollisionManager.cpp
//!	@brief	 �Փ˃}�l�[�W���[Class
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../CollisionManager.h"
#include "../CollisionPairCheck.h"
#include "../CollisionCalculation.h"
#include "../../CollisionBase.h"
#include "../../../GameObject/GameObjectBase.h"

#include <Resource/Polygon/MeshPlanePolygon.h>
#include <Tool/SafeRelease.h>
#include <Tool/Debug/ImGUI/imgui.h>
#include <Tool/Debug/ImGUI/imgui_impl_dx9.h>



//****************************************
// �v���p�e�B��`
//****************************************
void CollisionManager::setGround(MeshPlanePolygon* ground_polygon)
{
	ground_polygon_ = ground_polygon;
}



//****************************************
// �֐���`
//****************************************
void CollisionManager::Init()
{
	// �n�ʂ̏�����
	ground_polygon_ = nullptr;

	// 8���؂̏�����
	if (liner_octree_ == nullptr)
	{
		liner_octree_ = new LinerOctree<CollisionObject*>();
		liner_octree_->Init(7, Vec3(-50.0f, -10.0f, -50.0f), Vec3(50.0f, 90.0f, 50.0f));
	}
}



void CollisionManager::Uninit()
{
	// ����҂��z��̒��g�����
	ReleaseContentsOfAwaitReleaseArray();

	// 8����
	SafeRelease::PlusUninit(&liner_octree_);
	for (unsigned i = 0; i < all_collision_.getEndIndex(); i++)
	{
		for (unsigned j = 0; j < all_collision_.getObject(i)->getEndIndexOfArray(); j++)
		{
			// �ړ��I�u�W�F�N�g�̓��X�g����ꎞ�I�ɗ��E����
			ObjectOfTree<CollisionObject*>* temp = all_collision_.getObject(i)
				->getpCollisionObject(j)->getpObjectOfTree();
			temp->DeleteFromList();
			SafeRelease::Normal(&temp);
		}
	}
	collision_objects_list_.clear();

	// �ǉ��҂��z��̃��Z�b�g
	await_add_.Reset();

	// ����҂��z��̃��Z�b�g
	await_release_.Reset();

	// �S�Փ˔z��̃��Z�b�g
	all_collision_.Reset();
}



void CollisionManager::UninitWhenChangeScene()
{
	// ����҂��z��̒��g�����
	ReleaseContentsOfAwaitReleaseArray();

	// 8����
	for (unsigned i = 0; i < all_collision_.getEndIndex(); i++)
	{
		for (unsigned j = 0; j < all_collision_.getObject(i)->getEndIndexOfArray(); j++)
		{
			// �ړ��I�u�W�F�N�g�̓��X�g����ꎞ�I�ɗ��E����
			ObjectOfTree<CollisionObject*>* temp = all_collision_.getObject(i)
				->getpCollisionObject(j)->getpObjectOfTree();
			temp->DeleteFromList();
			SafeRelease::Normal(&temp);
		}
	}
	collision_objects_list_.clear();

	// �ǉ��҂��z��̃��Z�b�g
	await_add_.Reset();

	// ����҂��z��̃��Z�b�g
	await_release_.Reset();

	// �S�Փ˔z��̃��Z�b�g
	all_collision_.Reset();
}



void CollisionManager::Update()
{
	// �ǉ��҂��z��̒��g��ǉ�
	AddContentsOfAwaitAddArray();

	// ����҂��z��̒��g�����
	ReleaseContentsOfAwaitReleaseArray();

	// �Փ˃N���X�̍X�V
	for (unsigned i = 0; i < all_collision_.getEndIndex(); i++)
	{
		all_collision_.getObject(i)->Update();
		all_collision_.getObject(i)->UpdateAllCollisionObject();
	}

	// 8���؂̏���
	for (unsigned i = 0; i < all_collision_.getEndIndex(); i++)
	{
		for (unsigned j = 0; j < all_collision_.getObject(i)->getEndIndexOfArray(); j++)
		{
			// �ړ��I�u�W�F�N�g�̓��X�g����ꎞ�I�ɗ��E����
			ObjectOfTree<CollisionObject*>* temp = all_collision_.getObject(i)
				->getpCollisionObject(j)->getpObjectOfTree();
			temp->DeleteFromList();

			// �ēo�^
			liner_octree_->Add(temp,
							   temp->getObject()->getOctreeAABB()->getpMin(),
							   temp->getObject()->getOctreeAABB()->getpMax());
		}
	}
	liner_octree_->UpdateCollisionList(&collision_objects_list_);

	// �Փ˔���
	CollisionDetermination();

	// �n�ʂƂ̏Փ˔���
	CollisionGround();

	// �f�o�b�O�\��
	DebugDisplay();

	// �f�o�b�O
#ifdef _DEBUG
	for (unsigned i = 0; i < all_collision_.getEndIndex(); i++)
	{
		if (all_collision_.getObject(i) == nullptr) continue;
		all_collision_.getObject(i)->DebugDisplay();
	}
#endif
}



void CollisionManager::AddCollisionBaseToArray(CollisionBase* collision)
{
	// �ǉ��҂��z��ɒǉ�
	await_add_.AddToArray(collision);
}



void CollisionManager::OverwriteArrayCollisionBase(GameObjectBase* game_object,
												   CollisionBase* new_collision)
{
	// �V�K��nullptr�̏ꍇ
	if (new_collision == nullptr)
	{
		// �Â��Փˊ��N���X�̉��
		ReleaseCollisionBaseFromArray(game_object->getpCollision());

		// �Â��Փˊ��N���X�̏���
		CollisionBase* temp = game_object->getpCollision();
		SafeRelease::Normal(&temp);

		// nullptr�̑��
		game_object->setCollision(new_collision);
	}
	else
	{
		// �z��̏㏑��
		all_collision_.OverwriteArray(game_object->getpCollision(), new_collision);

		// �Â��Փˊ��N���X�̏���
		CollisionBase* temp = game_object->getpCollision();
		SafeRelease::Normal(&temp);

		// �V�K�R���|�[�l���g�̏�����
		game_object->setCollision(new_collision);
		*new_collision->getpGameObject() = *game_object;
		new_collision->Init();
	}
}



void CollisionManager::ReleaseCollisionBaseFromArray(CollisionBase* collision)
{
	// 8���؂������
	for (unsigned i = 0; i < collision->getEndIndexOfArray(); i++)
	{
		ObjectOfTree<CollisionObject*>* temp
			= collision->getpCollisionObject(i)->getpObjectOfTree();
		if (temp == nullptr) continue;
		temp->DeleteFromList();
		SafeRelease::Normal(&temp);
	}

	// ����҂��z��ɒǉ�
	await_release_.AddToArray(collision);
}



void CollisionManager::AddContentsOfAwaitAddArray()
{
	// �ǉ��҂������邩�ǂ���
	if (await_add_.getEndIndex() <= 0) return;

	// �ǉ�
	for (unsigned i = 0; i < await_add_.getEndIndex(); i++)
	{
		all_collision_.AddToArray(await_add_.getObject(i));

		// 8���؂ւ̒ǉ�
		for (unsigned j = 0; j < await_add_.getObject(i)->getEndIndexOfArray(); j++)
		{
			ObjectOfTree<CollisionObject*>* temp = new ObjectOfTree<CollisionObject*>;
			CollisionObject* temp_object = await_add_.getObject(i)->getpCollisionObject(j);
			temp->setObject(temp_object);
			temp_object->setObjectOfTree(temp);
			liner_octree_->Add(temp, temp_object->getOctreeAABB()->getpMin(),
							   temp_object->getOctreeAABB()->getpMax());
		}
	}

	// �ǉ��҂��z������Z�b�g
	await_add_.Reset();
}



void CollisionManager::ReleaseContentsOfAwaitReleaseArray()
{
	// ����҂������邩�ǂ���
	if (await_release_.getEndIndex() <= 0) return;

	// ����ƃ\�[�g
	for (unsigned i = 0; i < await_release_.getEndIndex(); i++)
	{
		// �S�̔z�񂩂���
		all_collision_.DeleteFromArrayAndSort(await_release_.getObject(i));
	}

	// ����҂��z������Z�b�g
	await_release_.Reset();
}



void CollisionManager::CollisionDetermination()
{
	// �y�A�ɂȂ��Ă��邽��
	unsigned max_index = collision_objects_list_.size() / 2;

	for (unsigned i = 0; i < max_index; i++)
	{
		// ���������g�ݍ��킹���H
		if (!CollisionPairCheck::IsCheck(collision_objects_list_[i * 2]->getpCollisionBase(),
										 collision_objects_list_[i * 2 + 1]->getpCollisionBase())) continue;

		// ���ۂ̔��菈��
		ActualCalculation(collision_objects_list_[i * 2],
						  collision_objects_list_[i * 2 + 1]);
	}

}



void CollisionManager::CollisionGround()
{
	if (ground_polygon_ == nullptr) return;

	for (unsigned i = 0; i < all_collision_.getEndIndex(); i++)
	{
		// �n�ʂƂ̔�������邩�ǂ���
		if (!all_collision_.getObject(i)->getIsJudgmentGround()) continue;

		// �n�ʍ����擾
		float position_y = ground_polygon_->getHeight(*all_collision_.getObject(i)
													  ->getpGameObject()->getpTransform()
													  ->getpPosition());

		// �Փ˂��Ă邩
		if (position_y >= all_collision_.getObject(i)
			->getpGameObject()->getpTransform()->getpPosition()->y)
		{
			// �n�ʂƂ̏Փˏ���
			all_collision_.getObject(i)->HitGround(position_y);
		}
	}
}



void CollisionManager::ActualCalculation(CollisionObject* collision_object0,
										 CollisionObject* collision_object1)
{
	for (unsigned i = 0; i < collision_object0->getEndIndexOfArray(); i++)
	{
		// ��������
		for (unsigned j = 0; j < collision_object1->getEndIndexOfArray(); j++)
		{
			// �Փˌv�Z
			CollisionInformation information0;
			CollisionInformation information1;
			if (SortCollisionCalculation(&information0, &information1,
										 collision_object0->getpShape(i),
										 collision_object1->getpShape(j)))
			{
				// ���̊i�[
				information0.setOpponentCollisionBase(collision_object1->getpCollisionBase());
				information1.setOpponentCollisionBase(collision_object0->getpCollisionBase());
				information0.setMyObject(collision_object0);
				information1.setMyObject(collision_object1);
				information0.setOpponentObject(collision_object1);
				information1.setOpponentObject(collision_object0);
				information0.setMyShape(collision_object0->getpShape(i));
				information1.setMyShape(collision_object1->getpShape(j));
				information0.setOpponentShape(collision_object1->getpShape(j));
				information1.setOpponentShape(collision_object0->getpShape(i));

				// �Փˉ���
				collision_object0->getpCollisionBase()->HitCollision(&information0);
				collision_object1->getpCollisionBase()->HitCollision(&information1);
			}
		}
	}
}



bool CollisionManager::SortCollisionCalculation(CollisionInformation* information0,
												CollisionInformation* information1,
												CollisionObject::Shape* collision_shape0,
												CollisionObject::Shape* collision_shape1)
{
	bool is_hit = false;

	switch (collision_shape0->getpShape()->getType())
	{
		case CollisionShapeBase::Type::AABB:
		{
			break;
		}
		case CollisionShapeBase::Type::CAPSULE:
		{
			switch (collision_shape1->getpShape()->getType())
			{
				case CollisionShapeBase::Type::CAPSULE:
				{
					is_hit = CollisionCalculation
						::CollisionJudgmentOfCapsuleAndCapsule(information0,
															   information1,
															   (Capsule*)collision_shape0->getpShape(),
															   (Capsule*)collision_shape1->getpShape());
					break;
				}
				case CollisionShapeBase::Type::LINE_SEGMENT:
				{
					is_hit = CollisionCalculation
						::CollisionJudgmentOfLineSegmentAndCapsule(information0,
																   information1,
																   (LineSegment*)collision_shape1->getpShape(),
																   (Capsule*)collision_shape0->getpShape());
					break;
				}
				case CollisionShapeBase::Type::SPHERE:
				{
					is_hit = CollisionCalculation
						::CollisionJudgmentOfSphereAndCapsule(information0,
															  information1,
															  (Sphere*)collision_shape1->getpShape(),
															  (Capsule*)collision_shape0->getpShape());
					break;
				}
			}
			break;
		}
		case CollisionShapeBase::Type::CYLINDER:
		{
			switch (collision_shape1->getpShape()->getType())
			{
				case CollisionShapeBase::Type::LINE_SEGMENT:
				{
					is_hit = CollisionCalculation
						::CollisionJudgmentOfLineSegmentAndCylinder(information0,
																	information1,
																	(LineSegment*)collision_shape1->getpShape(),
																	(Cylinder*)collision_shape0->getpShape());
					break;
				}
			}
			break;
		}
		case CollisionShapeBase::Type::OBB:
		{
			switch (collision_shape1->getpShape()->getType())
			{
				case CollisionShapeBase::Type::OBB:
				{
					is_hit = CollisionCalculation
						::CollisionJudgmentOfOBBAndOBB(information0,
													   information1,
													   (OBB*)collision_shape0->getpShape(),
													   (OBB*)collision_shape1->getpShape());
					break;
				}
				case CollisionShapeBase::Type::SPHERE:
				{
					is_hit = CollisionCalculation
						::CollisionJudgmentOfSphereAndOBB(information0,
														  information1,
														  (Sphere*)collision_shape1->getpShape(),
														  (OBB*)collision_shape0->getpShape());
					break;
				}
			}
			break;
		}
		case CollisionShapeBase::Type::PLANE:
		{
			switch (collision_shape1->getpShape()->getType())
			{
				case CollisionShapeBase::Type::PLANE:
				{
					is_hit = CollisionCalculation
						::CollisionJudgmentOfPlaneAndPlane(information0,
														   information1,
														   (Plane*)collision_shape0->getpShape(),
														   (Plane*)collision_shape1->getpShape());
					break;
				}
				case CollisionShapeBase::Type::LINE_SEGMENT:
				{
					is_hit = CollisionCalculation
						::CollisionJudgmentOfLineSegmentAndPlane(information0,
																 information1,
																 (LineSegment*)collision_shape1->getpShape(),
																 (Plane*)collision_shape0->getpShape());
					break;
				}
				case CollisionShapeBase::Type::SPHERE:
				{
					is_hit = CollisionCalculation
						::CollisionJudgmentOfSphereAndPlane(information0,
															information1,
															(Sphere*)collision_shape1->getpShape(),
															(Plane*)collision_shape0->getpShape());
					break;
				}
				case CollisionShapeBase::Type::TRIANGLE:
				{
					is_hit = CollisionCalculation
						::CollisionJudgmentOfPlaneAndTriangle(information0,
															  information1,
															  (Plane*)collision_shape0->getpShape(),
															  (Triangle*)collision_shape1->getpShape());
					break;
				}
			}
			break;
		}
		case CollisionShapeBase::Type::LINE_SEGMENT:
		{
			switch (collision_shape1->getpShape()->getType())
			{
				case CollisionShapeBase::Type::CAPSULE:
				{
					is_hit = CollisionCalculation
						::CollisionJudgmentOfLineSegmentAndCapsule(information0,
																   information1,
																   (LineSegment*)collision_shape0->getpShape(),
																   (Capsule*)collision_shape1->getpShape());
					break;

				}
				case CollisionShapeBase::Type::CYLINDER:
				{
					is_hit = CollisionCalculation
						::CollisionJudgmentOfLineSegmentAndCylinder(information0,
																	information1,
																	(LineSegment*)collision_shape0->getpShape(),
																	(Cylinder*)collision_shape1->getpShape());
					break;
				}
				case CollisionShapeBase::Type::PLANE:
				{
					is_hit = CollisionCalculation
						::CollisionJudgmentOfLineSegmentAndPlane(information0,
																 information1,
																 (LineSegment*)collision_shape0->getpShape(),
																 (Plane*)collision_shape1->getpShape());
					break;
				}
				case CollisionShapeBase::Type::LINE_SEGMENT:
				{
					is_hit = CollisionCalculation
						::CollisionJudgmentOf2DLineSegmentAnd2DLineSegment(information0,
																		   information1,
																		   (LineSegment*)collision_shape0->getpShape(),
																		   (LineSegment*)collision_shape1->getpShape());
					break;
				}
				case CollisionShapeBase::Type::SPHERE:
				{
					is_hit = CollisionCalculation
						::CollisionJudgmentOfLineSegmentAndSphere(information0,
																  information1,
																  (LineSegment*)collision_shape0->getpShape(),
																  (Sphere*)collision_shape1->getpShape());
					break;
				}
				case CollisionShapeBase::Type::TRIANGLE:
				{
					is_hit = CollisionCalculation
						::CollisionJudgmentOfLineSegmentAndTriangle(information0,
																	information1,
																	(LineSegment*)collision_shape0->getpShape(),
																	(Triangle*)collision_shape1->getpShape());
					break;
				}
			}
			break;
		}
		case CollisionShapeBase::Type::SPHERE:
		{
			switch (collision_shape1->getpShape()->getType())
			{
				case CollisionShapeBase::Type::CAPSULE:
				{
					is_hit = CollisionCalculation
						::CollisionJudgmentOfSphereAndCapsule(information0,
															  information1,
															  (Sphere*)collision_shape0->getpShape(),
															  (Capsule*)collision_shape1->getpShape());
					break;
				}
				case CollisionShapeBase::Type::OBB:
				{
					is_hit = CollisionCalculation
						::CollisionJudgmentOfSphereAndOBB(information0,
														  information1,
														  (Sphere*)collision_shape0->getpShape(),
														  (OBB*)collision_shape1->getpShape());
					break;

				}
				case CollisionShapeBase::Type::PLANE:
				{
					is_hit = CollisionCalculation
						::CollisionJudgmentOfSphereAndPlane(information0,
															information1,
															(Sphere*)collision_shape0->getpShape(),
															(Plane*)collision_shape1->getpShape());
					break;
				}
				case CollisionShapeBase::Type::LINE_SEGMENT:
				{
					is_hit = CollisionCalculation
						::CollisionJudgmentOfLineSegmentAndSphere(information0,
																  information1,
																  (LineSegment*)collision_shape0->getpShape(),
																  (Sphere*)collision_shape1->getpShape());
					break;

				}
				case CollisionShapeBase::Type::SPHERE:
				{
					is_hit = CollisionCalculation
						::CollisionJudgmentOfSphereAndSphere(information0,
															 information1,
															 (Sphere*)collision_shape0->getpShape(),
															 (Sphere*)collision_shape1->getpShape());
					break;

				}
				case CollisionShapeBase::Type::TRIANGLE:
				{
					is_hit = CollisionCalculation
						::CollisionJudgmentOfSphereAndTriangle(information0,
															   information1,
															   (Sphere*)collision_shape0->getpShape(),
															   (Triangle*)collision_shape1->getpShape());
					break;
				}
			}
			break;
		}
		case CollisionShapeBase::Type::TRIANGLE:
		{
			switch (collision_shape1->getpShape()->getType())
			{
				case CollisionShapeBase::Type::PLANE:
				{
					is_hit = CollisionCalculation
						::CollisionJudgmentOfPlaneAndTriangle(information0,
															  information1,
															  (Plane*)collision_shape1->getpShape(),
															  (Triangle*)collision_shape0->getpShape());
					break;
				}
				case CollisionShapeBase::Type::LINE_SEGMENT:
				{
					is_hit = CollisionCalculation
						::CollisionJudgmentOfLineSegmentAndTriangle(information0,
																	information1,
																	(LineSegment*)collision_shape1->getpShape(),
																	(Triangle*)collision_shape0->getpShape());
					break;
				}
				case CollisionShapeBase::Type::SPHERE:
				{
					is_hit = CollisionCalculation
						::CollisionJudgmentOfSphereAndTriangle(information0,
															   information1,
															   (Sphere*)collision_shape1->getpShape(),
															   (Triangle*)collision_shape0->getpShape());
					break;
				}
				case CollisionShapeBase::Type::TRIANGLE:
				{
					is_hit = CollisionCalculation
						::CollisionJudgmentOfTriangleAndTriangle(information0,
																 information1,
																 (Triangle*)collision_shape0->getpShape(),
																 (Triangle*)collision_shape1->getpShape());
					break;
				}
			}
			break;
		}

	}
	return is_hit;
}



/*void CollisionManager::DebugDisplay()
{
	// �E�B���h�E�̐ݒ�
	ImGui::SetNextWindowPos(ImVec2(1100, 30), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(150, 500), ImGuiSetCond_Once);
	ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(1.0f, 0.0f, 0.0f, 0.8f));
	ImGui::PushStyleColor(ImGuiCol_TitleBgCollapsed, ImVec4(0.0f, 0.5f, 1.0f, 0.8f));
	ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.5f, 0.0f, 0.0f, 0.8f));
	ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.0f, 0.5f, 0.5f, 1.0f));

	// �J�n
	ImGui::Begin("CollisionManager", nullptr);

	// ��������
	ImGui::Text("Time : %05lu ms", time_);

	// �R���r��
	if (is_octree_)
	{
		ImGui::Text("CombiNum : %06d", collision_objects_list_.size() / 2);
	}
	else
	{
		ImGui::Text("CombiNum : %06d", (all_collision_.getEndIndex()) * (all_collision_.getEndIndex() - 1) / 2);
	}

	// 8���؂̗L��
	ImGui::Text("PairCheck : %s", is_pair_check_ ? "true" : "false");
	if (ImGui::Button("PairCheckButton"))
	{
		is_pair_check_ ^= 1;
	}

	// 8���؂̗L��
	ImGui::Text("Octree : %s", is_octree_ ? "true" : "false");
	if (ImGui::Button("OctreeButton"))
	{
		is_octree_ ^= 1;
	}

	// �I��
	ImGui::End();

	// �F�̉��(�ݒ�Ńv�b�V������������)
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
}
*/