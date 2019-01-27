//================================================================================
//!	@file	 Renderer.cpp
//!	@brief	 �����_���[Class
//! @details Singleton
//!	@author  Kai Araki									@date 2018/11/01
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../Renderer.h"
#include "../RendererFactoryInterface.h"

#include <Tool/SafeRelease.h>



//****************************************
// static�ϐ���`
//****************************************
Renderer* Renderer::instance_ = nullptr;
RendererInterface* Renderer::renderer_ = nullptr;



//****************************************
// static�v���p�e�B��`
//****************************************
Renderer* Renderer::getpInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new Renderer();
	}
	return instance_;
}



//****************************************
// static�֐���`
//****************************************
void Renderer::ReleaseInstance()
{
	SafeRelease::Normal(&instance_);
}



//****************************************
// �v���p�e�B��`
//****************************************
RendererInterface* Renderer::getpRenderer()
{
	return renderer_;
}

void Renderer::setRenderer(RendererFactoryInterface* factory, MODE mode)
{
	if (renderer_ == nullptr)
	{
		renderer_ = factory->Create();
		mode_ = mode;
	}

	SafeRelease::Normal(&factory);
}



//****************************************
// �֐���`
//****************************************
Renderer::Renderer()
{
}



bool Renderer::Init(HINSTANCE hInstance, HWND hWnd, BOOL is_full_screen,
					int window_width, int window_height)
{
	if (renderer_ == nullptr) return false;
	return renderer_->Init(hInstance, hWnd, is_full_screen, window_width, window_height);
}



void Renderer::Uninit()
{
	// �����_���[�̉��
	SafeRelease::PlusUninit(&renderer_);

	// ���[�h�̏�����
	mode_ = MODE::NONE;
}



bool Renderer::DrawBegin()
{
	if (renderer_ == nullptr) return false;
	return renderer_->DrawBegin();
}



void Renderer::DrawEnd(bool is_begin_scene)
{
	if (renderer_ == nullptr) return;
	renderer_->DrawEnd(is_begin_scene);
}



void Renderer::Present()
{
	if (renderer_ == nullptr) return;
	renderer_->Present();
}