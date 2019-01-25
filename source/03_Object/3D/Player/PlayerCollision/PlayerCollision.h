//================================================================================
//
//    �v���C���[�Փ˃N���X
//    Author : Araki Kai                                �쐬�� : 2018/03/27
//
//================================================================================

#ifndef	_PLAYER_COLLISION_H_
#define _PLAYER_COLLISION_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================


#include <Component/Collision/CollisionNull/CollisionNull.h>

#include <string>



//======================================================================
//
// �N���X��`
//
//======================================================================

class PlayerCollision : public CollisionNull
{
//------------------------------------------------------------
private :
	// �萔
	static const float BOUNDING_SPHERE_RADIUS;
	static const float SUBSTANCE_RADIUS;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	enum ObjectTag
	{
		NONE = -1,
		BOUNDING_SPHERE,
		SUBSTANCE,
		MAX
	};


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �����o�֐�
	void Init()   override;
	void Uninit() override;
	void Update() override;

	void HitCollision(CollisionBase* hit_collision,
					  CollisionObject*  hit_object,
					  CollisionObject*  hit_my_object) override;

	void NotHitCollision(CollisionBase* hit_collision,
						 CollisionObject*  hit_object,
						 CollisionObject*  hit_my_object) override;

	void HitGround(float position_y)    override;


//------------------------------------------------------------
private :
	// �o�E���f�B���O�X�t�B�A
	void HitBoundingSphere(CollisionBase* hit_collision,
						   CollisionObject*  hit_object,
						   CollisionObject*  hit_my_object);

	void NotHitBoundingSphere(CollisionBase* hit_collision,
							  CollisionObject*  hit_object,
							  CollisionObject*  hit_my_object);

	// �T�u�X�^���X
	void HitSubstance(CollisionBase* hit_collision,
					  CollisionObject*  hit_object,
					  CollisionObject*  hit_my_object);

	

//------------------------------------------------------------
private :
	// �����o�ϐ�
	CollisionObjects* collision_objects_;
	CollisionObject* bounding_sphere_;
	CollisionObject* substance_;
};



#endif