//================================================================================
//
//    �����N���X
//    Author : Araki Kai                                �쐬�� : 2018/08/19
//
//================================================================================

#ifndef	_PHYSICS_H_
#define _PHYSICS_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include <Vector3D.h>



//======================================================================
//
// �N���X�錾
//
//======================================================================

class GameObjectBase;



//======================================================================
//
// �N���X��`
//
//======================================================================

class Physics
{
//------------------------------------------------------------
private :
	static const float VELOCITY_MIN;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �f�t�H���g�R���X�g���N�^
	Physics(GameObjectBase* game_object);



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �f�X�g���N�^
	~Physics();


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �X�V
	void Update();

	// �����x
	Vector3D* GetAcceleration(){return &acceleration_;}

	// ���x
	Vector3D* GetVelocity(){return &velocity_;}
	void      SetMaxVelocity(float max_velocity){max_velocity_ = max_velocity;}
	float     GetMaxVelocity(){return max_velocity_;}

	// ����
	void  SetMass(float mass){mass_ = mass;}
	float GetMass(){return mass_;}

	// ���C��
	void  AddFriction(float friction){friction_ += friction;}
	float GetFriction(){return friction_;}
	void  SetMyFriction(float my_friction){my_friction_ = my_friction;}
	float GetMyFriction(){return my_friction_;}

	// ������
	void  AddBounciness(float bounciness){bounciness_ += bounciness;}
	float GetBounciness(){return bounciness_;}
	void  SetMyBounciness(float bounciness){bounciness_ = bounciness;}
	float GetMyBounciness(){return bounciness_;}

	// �d��
	void SetGravity(bool is_gravity){is_gravity_ = is_gravity;}
	bool IsGravity() {return is_gravity_;}

	// �n��
	void SetOnTheGround(){is_on_tha_ground_ = true;}
	

//------------------------------------------------------------
private :
	void Reset();
	void UpdateAcceleration();
	void UpdateVelocity();
	void UpdatePosition();
	void SetGravity();
	void SetGround();
	void CheckVelocityMinMax();


//------------------------------------------------------------
private :
	// �Q�[���I�u�W�F�N�g
	GameObjectBase* game_object_;

	// �����x
	Vector3D acceleration_;

	// ���x
	Vector3D velocity_;
	float    max_velocity_;

	// ����
	float mass_;

	// ���C
	float friction_;
	float my_friction_;

	// ������(��ł����Ƃ������˕Ԃ������)
	float bounciness_;
	float my_bounciness_;
	
	// �d��
	bool is_gravity_;
	float gravity_acceleration_;
	Vector3D gravity_direction_;

	// �n��
	bool is_on_tha_ground_;
	bool is_landing_;



};



#endif