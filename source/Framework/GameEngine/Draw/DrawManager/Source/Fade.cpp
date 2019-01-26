//================================================================================
//!	@file	 Fade.cpp
//!	@brief	 �t�F�[�hClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "Fade.h"

#include <Renderer\RendererDirectX9\RendererDirectX9.h>
#include <SafeRelease/SafeRelease.h>
#include <Vector\ConvertToFrame\TimeToFrame\TimeToFrame.h>
#include <Texture\TextureManager\TextureManager.h>



//****************************************
// �萔��`
//****************************************
const std::string Fade::TEXTURE_NAME_TRANSITION_01 = "Fade/Transition_01.png";



//****************************************
// �v���p�e�B��`
//****************************************
MATRIX* Fade::getpMatrix(unsigned object_index)
{
	object_index = object_index;
	return transform_.getpMatrixExtend()->GetWorldMatrix();
}



D3DMATERIAL9* Fade::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;
	return plane_polygon_.GetMaterial();
}



const Fade::Type* Fade::getpType() const 
{
	return &type_; 
}



const Fade::State* Fade::getpState() const
{
	return &state_; 
}



bool Fade::getpEndFlag() const 
{
	return end_flag_; 
}



Transform* Fade::getpTransform() 
{
	return &transform_;
}



TextureObject* Fade::getpTransition01Object()
{
	return transition01_texture_; 
}



//****************************************
// �֐���`
//****************************************
void Fade::Init(Type type, State state, Vec2 size, XColor4 color, float speed)
{
	// �e����
	type_ = type;
	state_ = state;

	// �e�N�X�`���̓o�^
	if (transition01_texture_ == nullptr)
	{
		transition01_texture_ = TextureManager::getpInstance()
			->getpObject(&TEXTURE_NAME_TRANSITION_01);
	}

	// �I�[�_�[���X�g�ݒ�
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::TWO_DIMENSIONAL);
	getpDrawOrderList()->getpRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::FIXED);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::FIXED);

	// �t�F�[�h���w��T�C�Y�ɕύX
	transform_.GetScale()->x = size.x;
	transform_.GetScale()->y = size.y;
	transform_.UpdateWorldMatrixSRT();

	// �G���h�t���OOFF
	end_flag_ = false;

	// �X�e�[�g���Ƃ̏���
	if (state_ == State::STATE_FADE_IN)
	{
		// �J���[
		color.a = 1.0f;
		color_ = color;
		plane_polygon_.SetColor(color_);

		// �t�F�[�h���x(�P�ʁF�b)
		speed_ = -(1.0f / (float)Second_To_Frame(speed));
	}
	else if (state_ == State::STATE_FADE_OUT)
	{
		// �J���[
		color.a = 0.0f;
		color_ = color;
		plane_polygon_.SetColor(color_);

		// �t�F�[�h���x(�P�ʁF�b)
		speed_ = 1.0f / (float)Second_To_Frame(speed);
	}
}



void Fade::Uninit()
{
	// �X�e�[�g���Ƃ̏���
	if (state_ == State::STATE_FADE_IN)
	{

	}
	else if (state_ == State::STATE_FADE_OUT)
	{

	}

	end_flag_ = false;

	// �e��J��
	SafeRelease::PlusRelease(&transition01_texture_);
}



void Fade::Update()
{
	// ���l��ύX
	color_.a += speed_;
	plane_polygon_.SetColor(color_);

	// �t�F�[�h�I�u�W�F�N�g�̍X�V
	if (state_ == State::STATE_FADE_IN)
	{
		// ���l��1����������
		if (color_.a <= 0.0f)
		{
			end_flag_ = true;
		}
	}
	else if (state_ == State::STATE_FADE_OUT)
	{
		// ���l��1����������
		if (color_.a >= 1.0f)
		{
			end_flag_ = true;
		}
	}
}



void Fade::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	// �|���S���`��
	plane_polygon_.Draw();
}