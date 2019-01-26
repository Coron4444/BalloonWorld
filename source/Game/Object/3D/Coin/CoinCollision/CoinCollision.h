//================================================================================
//
//    �R�C���Փ˃N���X
//    Author : Araki Kai                                �쐬�� : 2018/07/24
//
//================================================================================

#ifndef	_COIN_COLLISION_H_
#define _COIN_COLLISION_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include "../Coin.h"
#include <Component/Collision/CollisionNull/CollisionNull.h>

#include <string>




//======================================================================
//
// �N���X��`
//
//======================================================================

class CoinCollision : public CollisionNull
{
//------------------------------------------------------------
private :
	// �萔
	static const float BOUNDING_OBB_RIGHT;
	static const float BOUNDING_OBB_UP;
	static const float BOUNDING_OBB_FORWARD;

	static const float SUBSTANCE_RIGHT;
	static const float SUBSTANCE_UP;
	static const float SUBSTANCE_FORWARD;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	enum ObjectTag
	{
		NONE = -1,
		BOUNDING_OBB,
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
	CollisionObject* bounding_obb_;
	CollisionObject* substance_;
};



#endif