//================================================================================
//
//    �R�C���N���X
//    Author : Araki Kai                                �쐬�� : 2018/07/24
//
//================================================================================

#ifndef	_COIN_H_
#define _COIN_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include <GameObjectBase/GameObjectBase.h>

#include <Polygon\PlanePolygon\PlanePolygon.h>



//======================================================================
//
// �N���X��`
//
//======================================================================

class Coin : public GameObjectBase
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �����o�֐�
	void Init(DrawBase*      draw,
			  CollisionBase* collision);
	void Uninit() override;
	void Reset()  override;

	PlanePolygon* GetPolygon(){return polygon_;}

	int getCount() { return count_; }
	void setCount(int value) { count_ = value; }

//------------------------------------------------------------
private :
	// ���J�����o�ϐ�
	PlanePolygon* polygon_;
	int count_ = 0;
};



#endif