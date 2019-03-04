//================================================================================
//!	@file	 Camera.cpp
//!	@brief	 カメラClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../Camera.h"



//****************************************
// 定数定義
//****************************************
const float Camera::DEFAULT_ANGLE_OF_VIEW = 60.0f;
const float Camera::DEFAULT_NEAR_CLIP = 0.1f;
const float Camera::DEFAULT_FAR_CLIP = 1000.0f;



//****************************************
// プロパティ定義
//****************************************
bool Camera::State::getIsInput()
{
	return is_input_;
}



void Camera::State::setIsInput(bool value)
{
	is_input_ = value;
}



bool Camera::State::getIsUpdate()
{
	return is_update_;
}



void Camera::State::setIsUpdate(bool value)
{
	is_update_ = value;
}



Camera* Camera::State::getpCamera()
{
	return camera_;
}



void Camera::State::setCamera(Camera* value)
{
	camera_ = value;
}



Matrix* Camera::getpViewMatrix()
{
	if (type_ == Type::TWO_DIMENSIONAL) return &view_2D_;
	return &view_;
}



Matrix* Camera::getpProjectionMatrix()
{
	if (type_ == Type::PERSPECTIVE) return &projection_perspective_;
	if (type_ == Type::ORTHO) return &projection_ortho_;
	return &projection_2D_;
}



Vector3D* Camera::getpPosition()
{
	return &position_;
}



Vector3D* Camera::getpGazingPoint()
{
	return &gazing_point_;
}



float Camera::getAngleOfView() const
{
	return angle_of_view_;
}



void Camera::setAngleOfView(float value)
{
	angle_of_view_ = value;
	CreateProjectionMatrixPerspectiveFov();
	CreateProjectionMatrixOrtho();
}



float Camera::getNearClip() const
{
	return near_clip_;
}



void Camera::setNearClip(float value)
{
	near_clip_ = value;
	CreateProjectionMatrixPerspectiveFov();
	CreateProjectionMatrixOrtho();
}



float Camera::getFarClip() const
{
	return far_clip_;
}



void Camera::setFarClip(float value)
{
	far_clip_ = value;
	CreateProjectionMatrixPerspectiveFov();
	CreateProjectionMatrixOrtho();
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



Vector3D* Camera::getpRight()
{
	return view_.getpRight();
}



Vector3D* Camera::getpUp()
{
	return view_.getpUp();
}



Vector3D* Camera::getpForward()
{
	return view_.getpForward();
}



Vector3D* Camera::getpDefaultRight()
{
	return view_.getpDefaultRight();
}



Vector3D* Camera::getpDefaultUp()
{
	return view_.getpDefaultUp();
}



Vector3D* Camera::getpDefaultForward()
{
	return view_.getpDefaultForward();
}



//****************************************
// 関数定義
//****************************************
Camera::State::~State()
{
}



Camera::Camera() :
	angle_of_view_(DEFAULT_ANGLE_OF_VIEW),
	near_clip_(DEFAULT_NEAR_CLIP),
	far_clip_(DEFAULT_FAR_CLIP),
	state_(nullptr),
	type_(Type::NONE)
{

	position_.Init();
	gazing_point_.Init();
	up_.Init();
	view_.Init();
	view_2D_.Init();
	projection_perspective_.Init();
	projection_ortho_.Init();
	projection_2D_.Init();
}



Camera::~Camera()
{
	Uninit();
}



void Camera::Init(State* state, Vector3D position, 
				  Vector3D gazing_point, Vector3D up, float angle_of_view,
				  float near_clip, float far_clip)
{
	// 各種代入
	position_ = position;
	gazing_point_ = gazing_point;
	up_ = up;
	angle_of_view_ = angle_of_view;
	near_clip_ = near_clip;
	far_clip_ = far_clip;

	// ステートの初期化
	setState(state);

	// ビュー行列の作成
	view_2D_.Init();
	CreateViewMatrix();

	// プロジェクション行列の作成
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
	if (state_ != nullptr)
	{
		if (state_->getIsUpdate())
		{
			state_->Update();
		}
	}
	CreateViewMatrix();
}



void Camera::CreateViewMatrix()
{
	view_.CreateView(&position_, &gazing_point_, &up_);
}



void Camera::CreateProjectionMatrixPerspectiveFov()
{
	projection_perspective_.Init();
	projection_perspective_.CreateProjectionPerspectiveFovLH(angle_of_view_,
		(float)GameEngine::SCREEN_WIDTH,
															 (float)GameEngine::SCREEN_HEIGHT,
															 near_clip_,
															 far_clip_);
}



void Camera::CreateProjectionMatrixOrtho()
{
	projection_ortho_.Init();
	projection_ortho_.CreateProjectionOrtho(angle_of_view_,
		(float)GameEngine::SCREEN_WIDTH,
											(float)GameEngine::SCREEN_HEIGHT,
											near_clip_,
											far_clip_);
}



void Camera::CreateProjectionMatrix2D()
{
	projection_2D_.Init();
	projection_2D_.CreateProjection2D((float)GameEngine::SCREEN_WIDTH,
		(float)GameEngine::SCREEN_HEIGHT);
}