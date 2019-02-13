//================================================================================
//!	@file	 SceneManager.cpp
//!	@brief	 �V�[���}�l�[�W��Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/01
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../SceneManager.h"
#include "../../SceneBase.h"
#include "../../../GameEngine.h"
#include "../../../GameObject/GameObjectManager/GameObjectManager.h"

#include <Tool/SafeRelease.h>



//****************************************
// �萔��`
//****************************************
const Fade::Type SceneManager::DEFAULT_FADE_TYPE = Fade::Type::NORMAL;
const float      SceneManager::DEFAULT_FADE_SPEED = 1.0f;
const XColor4    SceneManager::DEFAULT_FADE_COLOR(0.0f, 0.0f, 0.0f, 1.0f);



//****************************************
// �v���p�e�B��`
//****************************************
bool SceneManager::CommonData::getIsUpdate()
{
	return is_update_;
}



void SceneManager::CommonData::setIsUpdate(bool value)
{
	is_update_ = value;
}



bool SceneManager::CommonData::getIsClear()
{
	return is_clear_;
}



void SceneManager::CommonData::setIsClear(bool value)
{
	is_clear_ = value;
}



void SceneManager::setNextScene(SceneBase* value)
{
	// ���ɂق��̗v�����󂯕t���Ă���ꍇ
	if (state_ != SceneManager::State::NONE)
	{
		SafeRelease::PlusUninit(&value);
		return;
	}

	// �ύX�V�[���̓o�^
	next_scene_ = value;

	// �X�e�[�g�̕ύX
	state_ = SceneManager::State::CHANGE_SCENE;

	// Update�t���OOFF
	common_data_->setIsUpdate(false);

	// �t�F�[�h�A�E�g������
	GameObjectManager::getpInstance()->getpDrawManager()
		->StartFadeOut(fade_type_,
					  Vec2((float)GameEngine::SCREEN_WIDTH, (float)GameEngine::SCREEN_HEIGHT),
					  fade_color_, fade_speed_);
}



SceneManager::CommonData* SceneManager::getpCommonData()
{
	return common_data_;
}



void SceneManager::setFadeType(Fade::Type value)
{
	fade_type_ = value;
}



void SceneManager::setFadeSpeed(float value)
{
	fade_speed_ = value;
}



void SceneManager::setFadeColor(XColor4 value)
{
	fade_color_ = value;
}



//****************************************
// �֐���`
//****************************************
void SceneManager::Init(SceneBase* scene)
{
	// ���L�f�[�^�[�̏�����
	common_data_ = new CommonData();
	common_data_->Reset();

	// �Q�[���I�u�W�F�N�g�}�l�[�W���̏�����
	GameObjectManager::getpInstance()->Init();

	// �V�[���̏�����
	current_scene_ = scene;
	current_scene_->setSceneManager(this);
	current_scene_->Init();
}



void SceneManager::Uninit()
{
	// �V�[���̏I������
	if (current_scene_ != nullptr) current_scene_->Uninit();
	if (next_scene_ != nullptr)  next_scene_->Uninit();

	//�Q�[���I�u�W�F�N�g�}�l�[�W���̏I������
	GameObjectManager::getpInstance()->getpInstance()->Uninit();
	GameObjectManager::ReleaseInstance();

	// �e��J��
	SafeRelease::Normal(&current_scene_);
	SafeRelease::Normal(&next_scene_);
	SafeRelease::Normal(&common_data_);
}



void SceneManager::Update()
{
	switch (state_)
	{
		case SceneManager::State::CHANGE_SCENE:
		{
			// �V�[���ύX
			SceneChange();
			break;
		}
		case SceneManager::State::RESET_SCENE:
		{
			// �V�[�����Z�b�g
			SceneReset();
			break;
		}
	}
}



void SceneManager::UpdateScene()
{
	if (current_scene_ == nullptr) return;

	// �e�V�[�����L�̍X�V
	current_scene_->Update();

	// �Q�[���I�u�W�F�N�g�}�l�[�W���̍X�V
	GameObjectManager::getpInstance()->Update();
}



void SceneManager::DrawScene()
{
	if (current_scene_ == nullptr) return;

	//�Q�[���I�u�W�F�N�g�}�l�[�W���̕`��
	GameObjectManager::getpInstance()->Draw();
}



void SceneManager::ResetScene()
{
	// ���ɂق��̗v�����󂯕t���Ă���ꍇ
	if (state_ != SceneManager::State::NONE) return;

	// �X�e�[�g�̕ύX
	state_ = SceneManager::State::RESET_SCENE;

	// �t�F�[�h�A�E�g������
	GameObjectManager::getpInstance()->getpDrawManager()
		->StartFadeOut(fade_type_,
					  Vec2((float)GameEngine::SCREEN_WIDTH, (float)GameEngine::SCREEN_HEIGHT),
					  fade_color_, fade_speed_);
}



void SceneManager::SceneChange()
{
	// �t�F�[�h�������I����Ă��邩�ǂ���
	if (!GameObjectManager::getpInstance()->getpDrawManager()->IsFadeEnd()) return;

	// �t�F�[�h�̃X�e�[�g���Ƃ̏���
	if (GameObjectManager::getpInstance()->getpDrawManager()
		->IsFadeState(Fade::State::FADE_OUT))
	{
		// ���݂̃��C���V�[���̏I������
		SafeRelease::PlusUninit(&current_scene_);

		// �Q�[���I�u�W�F�N�g�}�l�[�W���̃V�[���ύX���I������
		GameObjectManager::getpInstance()->UninitWhenChangeScene();

		// �V�����V�[���ֈڍs
		current_scene_ = next_scene_;
		next_scene_ = nullptr;
		current_scene_->setSceneManager(this);
		current_scene_->Init();

		// �t�F�[�h�C��������
		GameObjectManager::getpInstance()->getpDrawManager()
			->StartFadeIn(fade_type_,
						 Vec2((float)GameEngine::SCREEN_WIDTH, (float)GameEngine::SCREEN_HEIGHT),
						 fade_color_, fade_speed_);
	}
	else if (GameObjectManager::getpInstance()->getpDrawManager()
			 ->IsFadeState(Fade::State::FADE_IN))
	{
		// �t�F�[�h�I������
		state_ = SceneManager::State::NONE;
		common_data_->setIsUpdate(true);
	}
}



void SceneManager::SceneReset()
{
	// �t�F�[�h�������I����Ă��邩�ǂ���
	if (!GameObjectManager::getpInstance()->getpDrawManager()->IsFadeEnd()) return;

	// �t�F�[�h�̃X�e�[�g���Ƃ̏���
	if (GameObjectManager::getpInstance()->getpDrawManager()
		->IsFadeState(Fade::State::FADE_OUT))
	{
		// ���݂̃��C���V�[���̃��Z�b�g
		GameObjectManager::getpInstance()->Reset();
		current_scene_->Reset();

		// �t�F�[�h�C��������
		GameObjectManager::getpInstance()->getpDrawManager()
			->StartFadeIn(fade_type_,
						 Vec2((float)GameEngine::SCREEN_WIDTH, (float)GameEngine::SCREEN_HEIGHT),
						 fade_color_, fade_speed_);
	}
	else if (GameObjectManager::getpInstance()->getpDrawManager()
			 ->IsFadeState(Fade::State::FADE_IN))
	{
		// �t�F�[�h�I������
		state_ = SceneManager::State::NONE;
		common_data_->setIsUpdate(true);
	}
}