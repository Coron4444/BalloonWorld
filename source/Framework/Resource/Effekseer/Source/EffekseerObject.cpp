//================================================================================
//!	@file	 EffekseerObject.cpp
//!	@brief	 �G�t�F�N�V�A�I�u�W�F�N�gClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/01
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include <codecvt>

#include "../EffekseerObject.h"



//****************************************
// �萔��`
//****************************************
const int EffekseerObject::MAX_SPRITE_NUM = 2000;



//****************************************
// �v���p�e�B��`
//****************************************
void EffekseerObject::setDisposable(bool value)
{
	is_disposable_ = value;
}



bool EffekseerObject::getpIsPlaying()
{
	return is_playing_;
}



void EffekseerObject::setIsRepeat(bool value)
{
	is_repeat_ = value;
}



Transform* EffekseerObject::getpTransform()
{
	return &transform_;
}



//****************************************
// �֐���`
//****************************************
void EffekseerObject::Init(std::string* file_path, const std::string* map_key_name)
{
	// �����_���[&�}�l�[�W������
	CreateRendererAndManager();

	// �G�t�F�N�g����
	CreateEffect(file_path);

	// �L�[���ۑ�
	map_key_name_ = *map_key_name;
}



void EffekseerObject::Release()
{
	reference_counter_--;
	if (reference_counter_ > 0) return;

	//�G�t�F�N�g�̒�~
	Stop();

	//�e��J��
	ES_SAFE_RELEASE(effekseer_effect_);
	effekseer_manager_->Destroy();
	effekseer_renderer_->Destroy();

	// �}�b�v������
	if (!is_disposable_)
	{
		EffekseerManager::getpInstance()->ReleaseFromTheMap(&map_key_name_);
	}
	delete this;
}



void EffekseerObject::ForcedRelease()
{
	reference_counter_ = 0;
	Release();
}



void EffekseerObject::AddReferenceCounter()
{
	reference_counter_++;
}



void EffekseerObject::CreateRendererAndManager()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 device = nullptr;
	Renderer::getpInstance()->getDevice(&device);
	if (device == nullptr)
	{
		MessageBox(nullptr, "NotGetDevice!(EffekseerObject.cpp)", "Error", MB_OK);
		return;
	}

	// �G�t�F�N�V�A�̏�����
	effekseer_renderer_ = EffekseerRendererDX9::Renderer::Create(device, MAX_SPRITE_NUM);
	effekseer_manager_ = Effekseer::Manager::Create(MAX_SPRITE_NUM);

	// �`��@�\�̐ݒ�
	effekseer_manager_->SetSpriteRenderer(effekseer_renderer_->CreateSpriteRenderer());
	effekseer_manager_->SetRibbonRenderer(effekseer_renderer_->CreateRibbonRenderer());
	effekseer_manager_->SetRingRenderer(effekseer_renderer_->CreateRingRenderer());
	effekseer_manager_->SetTrackRenderer(effekseer_renderer_->CreateTrackRenderer());
	effekseer_manager_->SetModelRenderer(effekseer_renderer_->CreateModelRenderer());

	// �e�N�X�`��&���f���̓ǂݍ��ݐݒ�(����̓t�@�C������ǂݍ���)
	effekseer_manager_->SetTextureLoader(effekseer_renderer_->CreateTextureLoader());
	effekseer_manager_->SetModelLoader(effekseer_renderer_->CreateModelLoader());

	// ������W�n�ɐݒ�
	effekseer_manager_->SetCoordinateSystem(Effekseer::CoordinateSystem::LH);
}



void EffekseerObject::CreateEffect(std::string* file_path)
{
	// wchar_t�ɃR���o�[�g
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> convert;
	std::wstring converted_file_path = convert.from_bytes(*file_path);

	// �G�t�F�N�g�̓ǂݍ���
	effekseer_effect_ = Effekseer::Effect::Create(effekseer_manager_,
		(const EFK_CHAR*)converted_file_path.c_str());
}



void EffekseerObject::Update()
{
	// �Đ������ǂ���
	is_playing_ = effekseer_manager_->Exists(effekseer_handle_);
	if (!is_playing_)
	{
		// �g���̂Ă��ǂ���
		if (is_disposable_) return;

		// ���s�[�g���邩�ǂ���
		is_repeat_ ? Play() : Stop();
	}

	// ���[���h�s��ύX
	ChangeWorldMatrix(transform_.getpWorldMatrix());
	
	//���ׂẴG�t�F�N�g�̍X�V
	effekseer_manager_->Update();
}



void EffekseerObject::Draw()
{
	effekseer_renderer_->BeginRendering();
	effekseer_manager_->Draw();
	effekseer_renderer_->EndRendering();
}



void EffekseerObject::Play()
{
	//�G�t�F�N�g�̍Đ�
	is_playing_ = true;
	effekseer_handle_ = effekseer_manager_->Play(effekseer_effect_, 0.0f, 0.0f, 0.0f);
	effekseer_manager_->Flip();
}



void EffekseerObject::Stop()
{
	is_playing_ = false;
	effekseer_manager_->StopEffect(effekseer_handle_);
	effekseer_manager_->Flip();
}



void EffekseerObject::Pause(bool is_pause)
{
	is_pause_ = is_pause;
	effekseer_manager_->SetPaused(effekseer_handle_, is_pause_);
	effekseer_manager_->Flip();
}



void EffekseerObject::ChangeVelocity(float velocity)
{
	effekseer_manager_->SetSpeed(effekseer_handle_, velocity);
}



void EffekseerObject::ChangeColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	effekseer_manager_->SetAllColor(effekseer_handle_, Effekseer::Color(r, g, b, a));
}



void EffekseerObject::ChangeViewMatrix(Effekseer::Matrix44* view_matrix)
{
	effekseer_renderer_->SetCameraMatrix(*view_matrix);
}



void EffekseerObject::ChangeProjectionMatrix(Effekseer::Matrix44* projection_matrix)
{
	effekseer_renderer_->SetProjectionMatrix(*projection_matrix);
}



void EffekseerObject::ChangeWorldMatrix(MATRIX* world_matrix)
{
	// �G�t�F�N�V�A�p���[���h�s��
	world_matrix_.Value[0][0] = world_matrix->_11;
	world_matrix_.Value[0][1] = world_matrix->_12;
	world_matrix_.Value[0][2] = world_matrix->_13;
	world_matrix_.Value[1][0] = world_matrix->_21;
	world_matrix_.Value[1][1] = world_matrix->_22;
	world_matrix_.Value[1][2] = world_matrix->_23;
	world_matrix_.Value[2][0] = world_matrix->_31;
	world_matrix_.Value[2][1] = world_matrix->_32;
	world_matrix_.Value[2][2] = world_matrix->_33;
	world_matrix_.Value[3][0] = world_matrix->_41;
	world_matrix_.Value[3][1] = world_matrix->_42;
	world_matrix_.Value[3][2] = world_matrix->_43;

	// ���[���h�s����Z�b�g
	effekseer_manager_->SetMatrix(effekseer_handle_, world_matrix_);
}