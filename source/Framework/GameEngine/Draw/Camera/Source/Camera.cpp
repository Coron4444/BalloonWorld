//================================================================================
//!	@file	 Camera.cpp
//!	@brief	 �J����Class
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../Camera.h"
#include "../../../GameEngine.h"

#include <Tool/SafeRelease.h>



//****************************************
// �萔��`
//****************************************
const float Camera::NEAR_CLIPPING_PLANE = 0.1f;
const float Camera::FAR_CLIPPING_PLANE = 1000.0f;
const int   Camera::DEFAULT_ANGLE_OF_VIEW = 60;



//****************************************
// �v���p�e�B��`
//****************************************
Camera* Camera::State::getpCamera()
{
	return camera_;
}



void Camera::State::setCamera(Camera* value)
{
	camera_ = value;
}



MATRIX* Camera::getpViewMatrix()
{
	if (type_ == Type::TWO_DIMENSIONAL) return &view_2D_;
	return &view_;
}



MATRIX* Camera::getpProjectionMatrix()
{
	if (type_ == Type::PERSPECTIVE) return &projection_perspective_;
	if (type_ == Type::ORTHO) return &projection_ortho_;
	return &projection_2D_;
}



Vector3D* Camera::getpPositon()
{
	return &position_;
}



Vector3D* Camera::getpLookAtPoint()
{
	return &look_at_point_;
}



Vector3D* Camera::getpUp()
{
	return &up_;
}



int Camera::getAngleOfView()
{
	return angle_of_view_;
}



void Camera::setAngleOfView(int value)
{
	angle_of_view_ = value;
	CreateProjectionMatrixPerspectiveFov();
	CreateProjectionMatrixOrtho();
}



Axis* Camera::getpAxis()
{
	return &axis_;
}



Vector3D* Camera::getpForwardVector()
{
	return axis_.getpForawrd();
}



Camera::State* Camera::getpState()
{
	return state_;
}



void Camera::setState(Camera::State* value)
{
	if (state_ != nullptr)
	{
		SafeRelease::PlusUninit(&state_);
	}

	state_ = value;

	if (state_ != nullptr)
	{
		state_->setCamera(this);
		state_->Init();
	}
}



Camera::Type Camera::getType()
{
	return type_;
}



void Camera::setType(Camera::Type value)
{
	type_ = value;
}



//****************************************
// �֐���`
//****************************************
Camera::State::~State()
{
}



void Camera::Init(State* state, Vec3 position, Vec3 look_at_point, Vec3 up)
{
	// �e����
	position_ = position;
	look_at_point_ = look_at_point;
	up_ = up;
	angle_of_view_ = DEFAULT_ANGLE_OF_VIEW;

	// ���x�N�g�����쐬
	axis_.setForward(look_at_point_ - position_);

	// �X�e�[�g�̏�����
	setState(state);

	// �r���[�s��̍쐬
	D3DXMatrixIdentity(&view_2D_);
	CreateViewMatrix();

	// �v���W�F�N�V�����s��̍쐬
	CreateProjectionMatrixPerspectiveFov();
	CreateProjectionMatrixOrtho();
	CreateProjectionMatrix2D();
}



void Camera::Uninit()
{
	SafeRelease::PlusUninit(&state_);
}



void Camera::Update()
{
	if (state_ != nullptr) state_->Update();

	CreateViewMatrix();
}



void Camera::CreateViewMatrix()
{
	// �s�񏉊���
	D3DXMatrixIdentity(&view_);

	// �r���[�ϊ��s��( LH�͍�����W�n�̈Ӗ� )
	D3DXMatrixLookAtLH(&view_, &position_, &look_at_point_, &up_);
}



void Camera::CreateProjectionMatrixPerspectiveFov()
{
	// �s�񏉊���
	D3DXMatrixIdentity(&projection_perspective_);

	D3DXMatrixPerspectiveFovLH(&projection_perspective_,
							   D3DXToRadian(angle_of_view_),
							   (float)GameEngine::SCREEN_WIDTH / (float)GameEngine::SCREEN_HEIGHT,
							   NEAR_CLIPPING_PLANE,
							   FAR_CLIPPING_PLANE);
}



void Camera::CreateProjectionMatrixOrtho()
{
	// �s�񏉊���
	D3DXMatrixIdentity(&projection_ortho_);

	D3DXMatrixOrthoLH(&projection_ortho_,
		(float)GameEngine::SCREEN_WIDTH  * angle_of_view_,
					  (float)GameEngine::SCREEN_HEIGHT * angle_of_view_,
					  NEAR_CLIPPING_PLANE, FAR_CLIPPING_PLANE);
}



void Camera::CreateProjectionMatrix2D()
{
	projection_2D_ =
	{
		2.0f / (float)GameEngine::SCREEN_WIDTH,	0.0f, 0.0f, 0.0f,
		0.0f, 2.0f / (float)GameEngine::SCREEN_HEIGHT, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}