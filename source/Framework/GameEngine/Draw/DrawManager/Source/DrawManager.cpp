//================================================================================
//!	@file	 DrawManager.cpp
//!	@brief	 �`��}�l�[�W���[Class
//! @details 
//!	@author  Kai Araki									@date 2019/01/19
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "DrawManager.h"
#include "ShaderManager/ShaderManager.h"

#include <Component/Draw/DrawBase/DrawBase.h>
#include <GameObjectBase/GameObjectBase.h>
#include <SafeRelease/SafeRelease.h>



//****************************************
// �v���p�e�B��`
//****************************************
BackBuffer* DrawManager::getpBackBuffer()
{
	return back_buffer_; 
}



//****************************************
// �֐���`
//****************************************
void DrawManager::Init()
{
	// �V�F�[�_�[�}�l�[�W���[������
	shader_manager_ = new ShaderManager();
	shader_manager_->Init();

	// �o�b�N�o�b�t�@������
	back_buffer_ = new BackBuffer();
	back_buffer_->Init();
	back_buffer_->setShaderManager(shader_manager_);
}



void DrawManager::Uninit()
{
	// �ǉ��҂��z��̃��Z�b�g
	await_add_.ResetArray();

	// ����҂��z��̃��Z�b�g
	await_release_.ResetArray();

	// �S�`��z��̃��Z�b�g
	all_draw_.ResetArray();

	// �o�b�N�o�b�t�@�I������
	SafeRelease::PlusUninit(&back_buffer_);
	SafeRelease::PlusUninit(&shader_manager_);
}



void DrawManager::UninitWhenChangeScene()
{
	// �ǉ��҂��z��̃��Z�b�g
	await_add_.ResetArray();

	// ����҂��z��̃��Z�b�g
	await_release_.ResetArray();

	// �S�`��z��̃��Z�b�g
	all_draw_.ResetArray();

	// �o�b�N�o�b�t�@�I������
	back_buffer_->UninitWhenChangeScene();
}



void DrawManager::Update()
{
	// �ǉ��҂��z��̒��g��ǉ�
	AddContentsOfAwaitAddArray();

	// ����҂��z��̒��g�����
	ReleaseContentsOfAwaitReleaseArray();

	// �S�`����N���X�X�V�֐�
	UpdateAllDrawBase();
	
	// �S�����_�[�^�[�Q�b�g�̃��Z�b�g
	ResetAllRenderTarget();

	// �����_�[�^�[�Q�b�g���Ƃ̐U�蕪��
	DistributeDrawBase();

	// �S�����_�[�^�[�Q�b�g�X�V�֐�
	UpdateAllRenderTarget();

	// �f�o�b�O�\��
#ifdef _DEBUG
	for (unsigned i = 0; i < all_draw_.GetEndPointer(); i++)
	{
		if (all_draw_.GetArrayObject(i) == nullptr) continue;
		all_draw_.GetArrayObject(i)->DebugDisplay();
	}
#endif
}



void DrawManager::Draw()
{
	// �o�b�N�o�b�t�@
	back_buffer_->Draw();
}



void DrawManager::AddDrawBaseToArray(DrawBase* draw)
{
	// �ǉ��҂��z��ɒǉ�
	await_add_.AddToArray(draw);
}



void DrawManager::OverwriteArrayDrawBase(GameObjectBase* game_object,
										 DrawBase* new_draw)
{
	// �V�K��nullptr�̏ꍇ
	if (new_draw == nullptr)
	{
		// �Â��`����N���X�̉��
		ReleaseDrawBaseFromArray(game_object->GetDraw());

		// �Â��`����N���X�̏���
		DrawBase* temp = game_object->GetDraw();
		SafeRelease::Normal(&temp);

		// nullptr�̑��
		game_object->SetDraw(new_draw);
	}
	else
	{
		// �z��̏㏑��
		all_draw_.OverwriteArray(game_object->GetDraw(), new_draw);

		// �Â��`����N���X�̏���
		DrawBase* temp = game_object->GetDraw();
		SafeRelease::Normal(&temp);

		// �V�K�R���|�[�l���g�̏�����
		game_object->SetDraw(new_draw);
		*new_draw->getpGameObject() = *game_object;
		new_draw->Init();
	}
}



void DrawManager::ReleaseDrawBaseFromArray(DrawBase* draw)
{
	// ����҂��z��ɒǉ�
	await_release_.AddToArray(draw);
}



void DrawManager::AddContentsOfAwaitAddArray()
{
	// �ǉ��҂������邩�ǂ���
	if (await_add_.GetEndPointer() <= 0) return;

	// �ǉ�
	for (unsigned i = 0; i < await_add_.GetEndPointer(); i++)
	{
		all_draw_.AddToArray(await_add_.GetArrayObject(i));
	}

	// �ǉ��҂��z������Z�b�g
	await_add_.ResetArray();
}



void DrawManager::ReleaseContentsOfAwaitReleaseArray()
{
	// ����҂������邩�ǂ���
	if (await_release_.GetEndPointer() <= 0) return;

	// ����ƃ\�[�g
	for (unsigned i = 0; i < await_release_.GetEndPointer(); i++)
	{
		all_draw_.DeleteFromArrayAndSortArray(await_release_.GetArrayObject(i));
	}

	// ����҂��z������Z�b�g
	await_release_.ResetArray();
}



void DrawManager::UpdateAllDrawBase()
{
	for (unsigned i = 0; i < all_draw_.GetEndPointer(); i++)
	{
		all_draw_.GetArrayObject(i)->Update();
	}
}



void DrawManager::UpdateAllRenderTarget()
{
	// �o�b�N�o�b�t�@
	back_buffer_->Update();
}



void DrawManager::ResetAllRenderTarget()
{
	// �o�b�N�o�b�t�@
	back_buffer_->ResetAllArray();
}



void DrawManager::DistributeDrawBase()
{
	for (unsigned i = 0; i < all_draw_.GetEndPointer(); i++)
	{
		// �o�b�N�o�b�t�@
		if (all_draw_.GetArrayObject(i)->getpDrawOrderList()->getpRenderTargetFlag()
			->CheckAny(DrawOrderList::RENDER_TARGET_BACK_BUFFER))
		{
			back_buffer_->AddDrawBaseToArray(all_draw_.GetArrayObject(i));
		}
	}
}