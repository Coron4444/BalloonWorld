//================================================================================
//!	@file	 EffekseerManager.cpp
//!	@brief	 �G�t�F�N�V�A�}�l�[�W��Class
//! @details Singleton
//!	@author  Kai Araki									@date 2019/1/11
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include <algorithm>

#include <GameEngine/Draw/Camera/Camera.h>



//****************************************
// ���q�֐��N���X��`
//****************************************
class IsPlayingDisposableObject
{
public:
	bool operator()(EffekseerObject* object)
	{
		if (!object->getpIsPlaying())
		{
			object->Release();
			return true;
		}
		return false;
	};
};



//****************************************
// �萔��`
//****************************************
const std::string EffekseerManager::DEFAULT_PATH = "Resource/Effekseer/";



//****************************************
// static�ϐ���`
//****************************************
EffekseerManager* EffekseerManager::instance_ = nullptr;



//****************************************
// static�v���p�e�B��`
//****************************************
EffekseerManager* EffekseerManager::getpInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new EffekseerManager();
	}
	return instance_;
}



//****************************************
// static�֐���`
//****************************************
void EffekseerManager::ReleaseInstance()
{
	SafeRelease::Normal(&instance_);
}



//****************************************
// �v���p�e�B��`
//****************************************
EffekseerObject* EffekseerManager::getpObject(const std::string* key_name,
											  const std::string* file_path)
{
	// �}�b�v�ɂ��邩�̊m�F
	auto iterator = object_map_.find(*key_name);
	if (iterator != object_map_.end())
	{
		// �Q�ƃJ�E���^��UP
		iterator->second->AddReferenceCounter();

		return iterator->second;
	}

	// �V�K�쐬
	std::string path = CreateFilePath(key_name, file_path);
	EffekseerObject* object = new EffekseerObject();
	object->Init(&path, key_name);
	object->AddReferenceCounter();
	object_map_.insert(std::make_pair(*key_name, object));
	return object;
}



EffekseerObject* EffekseerManager::getpDisposableObject(const std::string* key_name,
														const std::string* file_path)
{
	// �V�K�쐬
	std::string path = CreateFilePath(key_name, file_path);
	EffekseerObject* object = new EffekseerObject();
	object->Init(&path, key_name);
	object->AddReferenceCounter();
	object->setDisposable(true);
	disposable_object_.push_back(object);
	return object;
}



//****************************************
// �֐���`
//****************************************
EffekseerManager::EffekseerManager()
{
}



void EffekseerManager::Init()
{
	// �}�b�v�̏�����
	object_map_.clear();

	// ���X�g�̏�����
	disposable_object_.clear();
}



void EffekseerManager::Uninit()
{
	// �e�I�u�W�F�N�g�̋������
	auto iterator = object_map_.begin();
	while (iterator != object_map_.end())
	{
		iterator->second->ForcedRelease();
		iterator = object_map_.begin();
	}
	object_map_.clear();

	for (auto& contents : disposable_object_)
	{
		contents->ForcedRelease();
	}
	disposable_object_.clear();
}



void EffekseerManager::ReleaseFromTheMap(std::string* key_name)
{
	// �}�b�v������
	auto iterator = object_map_.find(*key_name);
	if (iterator != object_map_.end())
	{
		object_map_.erase(iterator);
	}
}



void EffekseerManager::Update()
{
	// �e��X�V
	for (auto contents : object_map_)
	{
		contents.second->ChangeViewMatrix(&view_matrix_);
		contents.second->ChangeProjectionMatrix(&projection_matrix_);
		contents.second->Update();
	}
	for (auto contents : disposable_object_)
	{
		contents->ChangeViewMatrix(&view_matrix_);
		contents->ChangeProjectionMatrix(&projection_matrix_);
		contents->Update();
	}

	// �g���̂ăI�u�W�F�N�g���
	disposable_object_.erase(remove_if(disposable_object_.begin(),
									   disposable_object_.end(),
									   IsPlayingDisposableObject()),
							 disposable_object_.end());
}



void EffekseerManager::Draw()
{
	// �e��`��
	bool is_draw = false;
	for (auto contents : object_map_)
	{
		contents.second->Draw();
		is_draw = true;
	}
	for (auto contents : disposable_object_)
	{
		contents->Draw();
		is_draw = true;
	}
	if (!is_draw) return;

	// �T���v���[�X�e�[�g�����ɖ߂�
	((RendererDirectX9*)Renderer::getpInstance()->getpRenderer())
		->SetDefaultSamplerState();
}



std::string EffekseerManager::CreateFilePath(const std::string* key_name,
											 const std::string* file_path)
{
	// �f�t�H���g�̃p�X���g�p
	if (file_path == nullptr) return DEFAULT_PATH + *key_name;

	// �C�ӂ̃p�X���g�p
	return *file_path + *key_name;
}



void EffekseerManager::CreateViewMatrix(Vector3D camera_position, 
										Vector3D look_at_point, Vector3D camera_up)
{
	view_matrix_ = Effekseer::Matrix44().LookAtLH(Effekseer::Vector3D(camera_position.x, camera_position.y, camera_position.z),
												  Effekseer::Vector3D(look_at_point.x, look_at_point.y, look_at_point.z),
												  Effekseer::Vector3D(camera_up.x, camera_up.y, camera_up.z));
}



void EffekseerManager::CreateProjectionMatrix(float angle_of_view_)
{
	projection_matrix_ = Effekseer::Matrix44().PerspectiveFovLH(D3DXToRadian(angle_of_view_),
		(float)GameEngine::SCREEN_WIDTH / GameEngine::SCREEN_HEIGHT,
																Camera::NEAR_CLIPPING_PLANE,
																Camera::FAR_CLIPPING_PLANE);
}