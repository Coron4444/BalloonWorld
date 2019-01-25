//================================================================================
//
//    �G�Փ˃N���X
//    Author : Araki Kai                                �쐬�� : 2018/07/24
//
//================================================================================

#ifndef	_ENEMY_COLLISION_H_
#define _ENEMY_COLLISION_H_



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

class EnemyCollision : public CollisionNull
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


//------------------------------------------------------------
private :
	// �����o�ϐ�
	CollisionObjects* collision_objects_;
	CollisionObject* bounding_sphere_;
	CollisionObject* substance_;
};



#endif