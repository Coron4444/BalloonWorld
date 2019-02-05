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
#include "../../CollisionObject.h"
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
		liner_octree_ = new LinerOctree<CollisionObjects*>();
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
			ObjectOfTree<CollisionObjects*>* temp = all_collision_.getObject(i)
				->getpCollisionObjects(j)->getpObjectOfTree();
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
			ObjectOfTree<CollisionObjects*>* temp = all_collision_.getObject(i)
				->getpCollisionObjects(j)->getpObjectOfTree();
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
	}

	// 8���؂̏���
	if (is_octree_)
	{
		for (unsigned i = 0; i < all_collision_.getEndIndex(); i++)
		{
			for (unsigned j = 0; j < all_collision_.getObject(i)->getEndIndexOfArray(); j++)
			{
				// �ړ��I�u�W�F�N�g�̓��X�g����ꎞ�I�ɗ��E����
				ObjectOfTree<CollisionObjects*>* temp = all_collision_.getObject(i)
					->getpCollisionObjects(j)->getpObjectOfTree();
				temp->DeleteFromList();

				// �ēo�^
				liner_octree_->Add(temp,
								   temp->getObject()->getOctreeAABB()->getpMin(),
								   temp->getObject()->getOctreeAABB()->getpMax());
			}
		}
		liner_octree_->UpdateCollisionList(&collision_objects_list_);

		time_ = timeGetTime();

		// �Փ˔���
		CollisionDetermination();
	}
	else
	{
		time_ = timeGetTime();

		// �Â��Փ˔���
		OldCollisionDetermination();
	}

	time_ = timeGetTime() - time_;

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
		ObjectOfTree<CollisionObjects*>* temp = collision->getpCollisionObjects(i)->getpObjectOfTree();
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
			ObjectOfTree<CollisionObjects*>* temp = new ObjectOfTree<CollisionObjects*>;
			CollisionObjects* temp_objects = await_add_.getObject(i)->getpCollisionObjects(j);
			temp->setObject(temp_objects);
			temp_objects->setObjectOfTree(temp);
			liner_octree_->Add(temp, temp_objects->getOctreeAABB()->getpMin(),
							   temp_objects->getOctreeAABB()->getpMax());
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
		// �����Փ˃I�u�W�F�N�g�����肷�邩�ǂ���
		if (!collision_objects_list_[i * 2]->getIsJudgment()) continue;
		if (!collision_objects_list_[i * 2 + 1]->getIsJudgment()) continue;

		// ���������g�ݍ��킹���H
		if (is_pair_check_)
		{
			if (!CollisionPairCheck::IsCheck(collision_objects_list_[i * 2]->getpCollisionBase(),
											 collision_objects_list_[i * 2 + 1]->getpCollisionBase())) continue;
		}

		// ���ۂ̔��菈��
		ActualCalculation(collision_objects_list_[i * 2],
						  collision_objects_list_[i * 2 + 1]);

		// �e�R���|�[�l���g�̏Փ˃I�u�W�F�N�g�̔�������Z�b�g
		if (collision_objects_list_[i * 2]->getIsJudgment())
		{
			collision_objects_list_[i * 2]->ResetHitDataAllCollisionObject();
		}
		if (collision_objects_list_[i * 2 + 1]->getIsJudgment())
		{
			collision_objects_list_[i * 2 + 1]->ResetHitDataAllCollisionObject();
		}
	}

}



void CollisionManager::OldCollisionDetermination()
{
	// �Փˊ��N���X��2�ȏォ�ǂ���
	if (all_collision_.getEndIndex() < 2) return;

	// �Փ˔���
	for (unsigned i = 0; i < all_collision_.getEndIndex() - 1; i++)
	{
		// �Փˊ��N���X�����邩�ǂ���
		if (all_collision_.getObject(i) == nullptr) continue;

		// ��������
		for (unsigned j = i + 1; j < all_collision_.getEndIndex(); j++)
		{
			// �Փˊ��N���X�����邩�ǂ���
			if (all_collision_.getObject(j) == nullptr) continue;

			// ���������g�ݍ��킹���H
			if (is_pair_check_)
			{
				if (!CollisionPairCheck::IsCheck(all_collision_.getObject(i),
												 all_collision_.getObject(j))) continue;
			}

			for (unsigned a = 0; a < all_collision_.getObject(i)->getEndIndexOfArray(); a++)
			{
				// �����Փ˃I�u�W�F�N�g�����肷�邩�ǂ���
				if (!all_collision_.getObject(i)->getpCollisionObjects(a)
					->getIsJudgment()) continue;

				for (unsigned b = 0; b < all_collision_.getObject(i)->getEndIndexOfArray(); b++)
				{
					// �����Փ˃I�u�W�F�N�g�����肷�邩�ǂ���
					if (!all_collision_.getObject(j)->getpCollisionObjects(b)
						->getIsJudgment()) continue;

					// ���ۂ̔��菈��
					ActualCalculation(all_collision_.getObject(i)->getpCollisionObjects(a),
									  all_collision_.getObject(j)->getpCollisionObjects(b));

					// �e�R���|�[�l���g�̏Փ˃I�u�W�F�N�g�̔�������Z�b�g
					if (all_collision_.getObject(i)->getpCollisionObjects(a)
						->getIsJudgment())
					{
						all_collision_.getObject(i)->getpCollisionObjects(a)
							->ResetHitDataAllCollisionObject();
					}
					else
					{
						a = all_collision_.getObject(i)->getEndIndexOfArray();
						break;
					}

					if (all_collision_.getObject(j)->getpCollisionObjects(b)
						->getIsJudgment())
					{
						all_collision_.getObject(j)->getpCollisionObjects(b)
							->ResetHitDataAllCollisionObject();
					}
					else
					{
						a = all_collision_.getObject(i)->getEndIndexOfArray();
						break;
					}

				}
			}
		}
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
		else
		{
			// �n�ʂƂ̔�Փˏ���
			all_collision_.getObject(i)->NotHitGround(position_y);
		}
	}
}



void CollisionManager::ActualCalculation(CollisionObjects* collision_objects0,
										 CollisionObjects* collision_objects1)
{
	for (unsigned i = 0; i < collision_objects0->getEndIndexOfArray(); i++)
	{
		// �Փ˃I�u�W�F�N�g�����肷�邩�ǂ���
		if (!collision_objects0->getpCollisionObject(i)->getIsJudgment()) continue;

		// ��������
		for (unsigned j = 0; j < collision_objects1->getEndIndexOfArray(); j++)
		{
			// �Փ˃I�u�W�F�N�g�����肷�邩�ǂ���
			if (!collision_objects1->getpCollisionObject(j)->getIsJudgment()) continue;

			// �Փˌv�Z
			if (SortCollisionCalculation(collision_objects0->getpCollisionObject(i),
										 collision_objects1->getpCollisionObject(j)))
			{
				// �R���|�[�l���g1�ڂ̏Փˉ���
				collision_objects0->getpCollisionBase()
					->HitCollision(collision_objects1->getpCollisionBase(),
								   collision_objects1->getpCollisionObject(j),
								   collision_objects0->getpCollisionObject(i));

				// �R���|�[�l���g2�ڂ̏Փˉ���
				collision_objects1->getpCollisionBase()
					->HitCollision(collision_objects0->getpCollisionBase(),
								   collision_objects0->getpCollisionObject(i),
								   collision_objects1->getpCollisionObject(j));
			}
			else
			{
				// �R���|�[�l���g1�ڂ̔�Փˉ���
				collision_objects0->getpCollisionBase()
					->NotHitCollision(collision_objects1->getpCollisionBase(),
									  collision_objects1->getpCollisionObject(j),
									  collision_objects0->getpCollisionObject(i));

				// �R���|�[�l���g2�ڂ̔�Փˉ���
				collision_objects1->getpCollisionBase()
					->NotHitCollision(collision_objects0->getpCollisionBase(),
									  collision_objects0->getpCollisionObject(i),
									  collision_objects1->getpCollisionObject(j));
			}

			// �R���|�[�l���g������\���ǂ���
			if (!collision_objects0->getIsJudgment()) return;
			if (!collision_objects1->getIsJudgment()) return;
		}
	}
}



bool CollisionManager::SortCollisionCalculation(CollisionObject* collision_object0,
												CollisionObject* collision_object1)
{
	bool is_hit = false;

	switch (collision_object0->getpCollisionShape()->getType())
	{
		case CollisionShapeBase::Type::AABB:
		{
			/*switch(collision_object1->getpCollisionShape()->getType())
			{
				default :
					break;
			}*/
			break;
		}
		case CollisionShapeBase::Type::CAPSULE:
		{
			switch (collision_object1->getpCollisionShape()->getType())
			{
				case CollisionShapeBase::Type::CAPSULE:
				{
					Vector3D temp_vector;

					is_hit = CollisionCalculation::CollisionJudgmentOfCapsuleAndCapsule(&temp_vector,
						(Capsule*)collision_object0->getpCollisionShape(),
																						(Capsule*)collision_object1->getpCollisionShape());

					collision_object0->setHitVector(temp_vector);
					collision_object1->setHitVector(-temp_vector);

					break;
				}
				case CollisionShapeBase::Type::LINE_SEGMENT:
				{
					Vector3D temp_position;

					is_hit = CollisionCalculation::CollisionJudgmentOfLineSegmentAndCapsule(&temp_position,
						(LineSegment*)collision_object1->getpCollisionShape(),
																							(Capsule*)collision_object0->getpCollisionShape());

					collision_object0->setHitVector(temp_position);
					collision_object1->setHitVector(temp_position);

					break;
				}
				case CollisionShapeBase::Type::SPHERE:
				{
					Vector3D temp_vector;

					is_hit = CollisionCalculation::CollisionJudgmentOfSphereAndCapsule(&temp_vector,
						(Sphere*)collision_object1->getpCollisionShape(),
																					   (Capsule*)collision_object0->getpCollisionShape());

					collision_object0->setHitVector(-temp_vector);
					collision_object1->setHitVector(temp_vector);

					break;
				}
			}
			break;
		}
		case CollisionShapeBase::Type::CYLINDER:
		{
			switch (collision_object1->getpCollisionShape()->getType())
			{
				case CollisionShapeBase::Type::LINE_SEGMENT:
				{
					Vector3D temp_position;

					is_hit = CollisionCalculation::CollisionJudgmentOfLineSegmentAndCylinder(&temp_position,
						(LineSegment*)collision_object1->getpCollisionShape(),
																							 (Cylinder*)collision_object0->getpCollisionShape());

					collision_object0->setHitVector(temp_position);
					collision_object1->setHitVector(temp_position);

					break;
				}
			}
			break;
		}
		case CollisionShapeBase::Type::OBB:
		{
			switch (collision_object1->getpCollisionShape()->getType())
			{
				case CollisionShapeBase::Type::OBB:
				{
					Vector3D temp_vector;

					is_hit = CollisionCalculation::CollisionJudgmentOfOBBAndOBB(&temp_vector,
						(OBB*)collision_object0->getpCollisionShape(),
																				(OBB*)collision_object1->getpCollisionShape());

					collision_object0->setHitVector(temp_vector);
					collision_object1->setHitVector(-temp_vector);

					break;
				}
				case CollisionShapeBase::Type::SPHERE:
				{
					Vector3D temp_vector;

					is_hit = CollisionCalculation::CollisionJudgmentOfSphereAndOBB(&temp_vector,
						(Sphere*)collision_object1->getpCollisionShape(),
																				   (OBB*)collision_object0->getpCollisionShape());

					collision_object0->setHitVector(-temp_vector);
					collision_object1->setHitVector(temp_vector);

					break;
				}
			}
			break;
		}
		case CollisionShapeBase::Type::PLANE:
		{
			switch (collision_object1->getpCollisionShape()->getType())
			{
				case CollisionShapeBase::Type::PLANE:
				{
					is_hit = CollisionCalculation::CollisionJudgmentOfPlaneAndPlane(nullptr,
						(Plane*)collision_object0->getpCollisionShape(),
																					(Plane*)collision_object1->getpCollisionShape());

					collision_object0->getpHitVector()->Reset();
					collision_object1->getpHitVector()->Reset();

					break;
				}
				case CollisionShapeBase::Type::LINE_SEGMENT:
				{
					Vector3D temp_position;

					is_hit = CollisionCalculation::CollisionJudgmentOfLineSegmentAndPlane(&temp_position,
						(LineSegment*)collision_object1->getpCollisionShape(),
																						  (Plane*)collision_object0->getpCollisionShape());

					collision_object0->setHitVector(temp_position);
					collision_object1->setHitVector(temp_position);

					break;
				}
				case CollisionShapeBase::Type::SPHERE:
				{
					Vector3D temp_vector;

					is_hit = CollisionCalculation::CollisionJudgmentOfSphereAndPlane(&temp_vector,
						(Sphere*)collision_object1->getpCollisionShape(),
																					 (Plane*)collision_object0->getpCollisionShape());

					collision_object0->setHitVector(-temp_vector);
					collision_object1->setHitVector(temp_vector);

					break;
				}
				case CollisionShapeBase::Type::TRIANGLE:
				{
					is_hit = CollisionCalculation::CollisionJudgmentOfPlaneAndTriangle((Plane*)collision_object0->getpCollisionShape(),
						(Triangle*)collision_object1->getpCollisionShape());

					collision_object0->getpHitVector()->Reset();
					collision_object1->getpHitVector()->Reset();

					break;
				}
			}
			break;
		}
		case CollisionShapeBase::Type::LINE_SEGMENT:
		{
			switch (collision_object1->getpCollisionShape()->getType())
			{
				case CollisionShapeBase::Type::CAPSULE:
				{
					Vector3D temp_position;

					is_hit = CollisionCalculation::CollisionJudgmentOfLineSegmentAndCapsule(&temp_position,
						(LineSegment*)collision_object0->getpCollisionShape(),
																							(Capsule*)collision_object1->getpCollisionShape());

					collision_object0->setHitVector(temp_position);
					collision_object1->setHitVector(temp_position);

				}
				case CollisionShapeBase::Type::CYLINDER:
				{
					Vector3D temp_position;

					is_hit = CollisionCalculation::CollisionJudgmentOfLineSegmentAndCylinder(&temp_position,
						(LineSegment*)collision_object0->getpCollisionShape(),
																							 (Cylinder*)collision_object1->getpCollisionShape());

					collision_object0->setHitVector(temp_position);
					collision_object1->setHitVector(temp_position);

					break;
				}
				case CollisionShapeBase::Type::PLANE:
				{
					Vector3D temp_position;

					is_hit = CollisionCalculation::CollisionJudgmentOfLineSegmentAndPlane(&temp_position,
						(LineSegment*)collision_object0->getpCollisionShape(),
																						  (Plane*)collision_object1->getpCollisionShape());

					collision_object0->setHitVector(temp_position);
					collision_object1->setHitVector(temp_position);

					break;
				}
				case CollisionShapeBase::Type::LINE_SEGMENT:
				{
					Vector3D temp_position;

					is_hit = CollisionCalculation::CollisionJudgmentOf2DLineSegmentAnd2DLineSegment(&temp_position,
						(LineSegment*)collision_object0->getpCollisionShape(),
																									(LineSegment*)collision_object1->getpCollisionShape());

					collision_object0->setHitVector(temp_position);
					collision_object1->setHitVector(temp_position);

					break;
				}
				case CollisionShapeBase::Type::SPHERE:
				{
					Vector3D temp_position;

					is_hit = CollisionCalculation::CollisionJudgmentOfLineSegmentAndSphere(&temp_position,
						(LineSegment*)collision_object0->getpCollisionShape(),
																						   (Sphere*)collision_object1->getpCollisionShape());

					collision_object0->setHitVector(temp_position);
					collision_object1->setHitVector(temp_position);

					break;
				}
				case CollisionShapeBase::Type::TRIANGLE:
				{
					Vector3D temp_position;

					is_hit = CollisionCalculation::CollisionJudgmentOfLineSegmentAndTriangle(&temp_position,
						(LineSegment*)collision_object0->getpCollisionShape(),
																							 (Triangle*)collision_object1->getpCollisionShape());

					collision_object0->setHitVector(temp_position);
					collision_object1->setHitVector(temp_position);

					break;
				}
			}
			break;
		}
		case CollisionShapeBase::Type::SPHERE:
		{
			switch (collision_object1->getpCollisionShape()->getType())
			{
				case CollisionShapeBase::Type::CAPSULE:
				{
					Vector3D temp_vector;

					is_hit = CollisionCalculation::CollisionJudgmentOfSphereAndCapsule(&temp_vector,
						(Sphere*)collision_object0->getpCollisionShape(),
																					   (Capsule*)collision_object1->getpCollisionShape());

					collision_object0->setHitVector(temp_vector);
					collision_object1->setHitVector(-temp_vector);

					break;
				}
				case CollisionShapeBase::Type::OBB:
				{
					Vector3D temp_vector;

					is_hit = CollisionCalculation::CollisionJudgmentOfSphereAndOBB(&temp_vector,
						(Sphere*)collision_object0->getpCollisionShape(),
																				   (OBB*)collision_object1->getpCollisionShape());

					collision_object0->setHitVector(temp_vector);
					collision_object1->setHitVector(-temp_vector);

					break;

				}
				case CollisionShapeBase::Type::PLANE:
				{
					Vector3D temp_vector;

					is_hit = CollisionCalculation::CollisionJudgmentOfSphereAndPlane(&temp_vector,
						(Sphere*)collision_object0->getpCollisionShape(),
																					 (Plane*)collision_object1->getpCollisionShape());

					collision_object0->setHitVector(temp_vector);
					collision_object1->setHitVector(-temp_vector);

					break;
				}
				case CollisionShapeBase::Type::LINE_SEGMENT:
				{
					Vector3D temp_position;

					is_hit = CollisionCalculation::CollisionJudgmentOfLineSegmentAndSphere(&temp_position,
						(LineSegment*)collision_object0->getpCollisionShape(),
																						   (Sphere*)collision_object1->getpCollisionShape());

					collision_object0->setHitVector(temp_position);
					collision_object1->setHitVector(temp_position);

					break;

				}
				case CollisionShapeBase::Type::SPHERE:
				{
					Vector3D temp_vector;

					is_hit = CollisionCalculation::CollisionJudgmentOfSphereAndSphere(&temp_vector,
						(Sphere*)collision_object0->getpCollisionShape(),
																					  (Sphere*)collision_object1->getpCollisionShape());

					collision_object0->setHitVector(temp_vector);
					collision_object1->setHitVector(-temp_vector);

					break;

				}
				case CollisionShapeBase::Type::TRIANGLE:
				{
					Vector3D temp_vector;

					is_hit = CollisionCalculation::CollisionJudgmentOfSphereAndTriangle(&temp_vector,
						(Sphere*)collision_object0->getpCollisionShape(),
																						(Triangle*)collision_object1->getpCollisionShape());

					collision_object0->setHitVector(temp_vector);
					collision_object1->setHitVector(-temp_vector);

					break;
				}
			}
			break;
		}
		case CollisionShapeBase::Type::TRIANGLE:
		{
			switch (collision_object1->getpCollisionShape()->getType())
			{
				case CollisionShapeBase::Type::PLANE:
				{
					is_hit = CollisionCalculation::CollisionJudgmentOfPlaneAndTriangle((Plane*)collision_object1->getpCollisionShape(),
						(Triangle*)collision_object0->getpCollisionShape());

					collision_object0->getpHitVector()->Reset();
					collision_object1->getpHitVector()->Reset();

					break;
				}
				case CollisionShapeBase::Type::LINE_SEGMENT:
				{
					Vector3D temp_position;

					is_hit = CollisionCalculation::CollisionJudgmentOfLineSegmentAndTriangle(&temp_position,
						(LineSegment*)collision_object1->getpCollisionShape(),
																							 (Triangle*)collision_object0->getpCollisionShape());

					collision_object0->setHitVector(temp_position);
					collision_object1->setHitVector(temp_position);

					break;
				}
				case CollisionShapeBase::Type::SPHERE:
				{
					Vector3D temp_vector;

					is_hit = CollisionCalculation::CollisionJudgmentOfSphereAndTriangle(&temp_vector,
						(Sphere*)collision_object1->getpCollisionShape(),
																						(Triangle*)collision_object0->getpCollisionShape());

					collision_object0->setHitVector(temp_vector);
					collision_object1->setHitVector(-temp_vector);

					break;
				}
				case CollisionShapeBase::Type::TRIANGLE:
				{
					is_hit = CollisionCalculation::CollisionJudgmentOfTriangleAndTriangle((Triangle*)collision_object0->getpCollisionShape(),
						(Triangle*)collision_object1->getpCollisionShape());

					collision_object0->getpHitVector()->Reset();
					collision_object1->getpHitVector()->Reset();

					break;
				}
			}
			break;
		}

	}
	return is_hit;
}



void CollisionManager::DebugDisplay()
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