//================================================================================
//!	@file	 SceneManager.cpp
//!	@brief	 �V�[���}�l�[�W��Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/01
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "SceneManager.h"
#include <SceneBase/SceneBase.h>

#include <main.h>
#include <SafeRelease/SafeRelease.h>
#include <GameObjectManager\GameObjectManager.h>
#include <Effekseer/EffekseerManager/EffekseerManager.h>
#include <Texture/TextureManager/TextureManager.h>
#include <ModelX/ModelXManager/ModelXManager.h>
#include <MdBin/MdBinManager/MdBinManager.h>



//****************************************
// �萔��`
//****************************************
const Fade::Type SceneManager::DEFAULT_FADE_TYPE = Fade::Type::TYPE_NORMAL;
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
		value->ReleaseState();
		SafeRelease::Normal(&value);
		return;
	}

	// �ύX�V�[���̓o�^
	next_scene_ = value;

	// �X�e�[�g�̕ύX
	state_ = SceneManager::State::CHANGE_SCENE;

	// Update�t���OOFF
	common_data_->setIsUpdate(false);

	// �t�F�[�h�A�E�g������
	GameObjectManager::GetDrawManager()->getpBackBuffer()
		->InitFade(fade_type_, Fade::State::STATE_FADE_OUT,
				   Vec2((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT),
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

	// ���\�[�X�̏�����
	EffekseerManager::getpInstance()->Init();
	TextureManager::getpInstance()->Init();
	ModelXManager::getpInstance()->Init();
	MdBinManager::getpInstance()->Init();

	// �Q�[���I�u�W�F�N�g�}�l�[�W���̏�����
	GameObjectManager::Init();

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
	GameObjectManager::Uninit();

	// ���\�[�X�̏I������
	MdBinManager::getpInstance()->Uninit();
	MdBinManager::ReleaseInstance();
	ModelXManager::getpInstance()->Uninit();
	ModelXManager::ReleaseInstance();
	TextureManager::getpInstance()->Uninit();
	TextureManager::ReleaseInstance();
	EffekseerManager::getpInstance()->Uninit();
	EffekseerManager::ReleaseInstance();

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
	GameObjectManager::Update();
}



void SceneManager::DrawScene()
{
	if (current_scene_ == nullptr) return;

	//�Q�[���I�u�W�F�N�g�}�l�[�W���̕`��
	GameObjectManager::Draw();
}



void SceneManager::ResetScene()
{
	// ���ɂق��̗v�����󂯕t���Ă���ꍇ
	if (state_ != SceneManager::State::NONE) return;

	// �X�e�[�g�̕ύX
	state_ = SceneManager::State::RESET_SCENE;

	// �t�F�[�h�A�E�g������
	GameObjectManager::GetDrawManager()->getpBackBuffer()
		->InitFade(fade_type_, Fade::State::STATE_FADE_OUT,
				   Vec2((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT),
				   fade_color_, fade_speed_);
}



void SceneManager::SceneChange()
{
	// �t�F�[�h�������I����Ă��邩�ǂ���
	if (!GameObjectManager::GetDrawManager()->getpBackBuffer()->IsFadeEnd()) return;

	// �t�F�[�h�̃X�e�[�g���Ƃ̏���
	if (GameObjectManager::GetDrawManager()->getpBackBuffer()
		->IsFadeStateName(Fade::State::STATE_FADE_OUT))
	{
		// ���݂̃��C���V�[���̏I������
		SafeRelease::PlusUninit(&current_scene_);

		// �Q�[���I�u�W�F�N�g�}�l�[�W���̃V�[���ύX���I������
		GameObjectManager::UninitWhenChangeScene();

		// �V�����V�[���ֈڍs
		current_scene_ = next_scene_;
		next_scene_ = nullptr;
		current_scene_->setSceneManager(this);
		current_scene_->Init();

		// �t�F�[�h�I��
		GameObjectManager::GetDrawManager()->getpBackBuffer()->UninitFade();

		// �t�F�[�h�C��������
		GameObjectManager::GetDrawManager()->getpBackBuffer()
			->InitFade(fade_type_, Fade::State::STATE_FADE_IN,
					   Vec2((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT),
					   fade_color_, fade_speed_);
	}
	else if (GameObjectManager::GetDrawManager()->getpBackBuffer()
			 ->IsFadeStateName(Fade::State::STATE_FADE_IN))
	{
		// �t�F�[�h�I������
		state_ = SceneManager::State::NONE;
		common_data_->setIsUpdate(true);
		GameObjectManager::GetDrawManager()->getpBackBuffer()->UninitFade();
	}
}



void SceneManager::SceneReset()
{
	// �t�F�[�h�������I����Ă��邩�ǂ���
	if (!GameObjectManager::GetDrawManager()->getpBackBuffer()->IsFadeEnd()) return;

	// �t�F�[�h�̃X�e�[�g���Ƃ̏���
	if (GameObjectManager::GetDrawManager()->getpBackBuffer()
		->IsFadeStateName(Fade::State::STATE_FADE_OUT))
	{
		// ���݂̃��C���V�[���̃��Z�b�g
		GameObjectManager::AllReset();
		current_scene_->Reset();

		// �t�F�[�h�I��
		GameObjectManager::GetDrawManager()->getpBackBuffer()->UninitFade();

		// �t�F�[�h�C��������
		GameObjectManager::GetDrawManager()->getpBackBuffer()
			->InitFade(fade_type_, Fade::State::STATE_FADE_IN,
					   Vec2((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT),
					   fade_color_, fade_speed_);
	}
	else if (GameObjectManager::GetDrawManager()->getpBackBuffer()
			 ->IsFadeStateName(Fade::State::STATE_FADE_IN))
	{
		// �t�F�[�h�I������
		state_ = SceneManager::State::NONE;
		common_data_->setIsUpdate(true);
		GameObjectManager::GetDrawManager()->getpBackBuffer()->UninitFade();
	}
}