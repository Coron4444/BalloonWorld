//================================================================================
//
//    �X�R�A�X�V�N���X
//    Author : Araki Kai                                �쐬�� : 2018/06/20
//
//================================================================================

#ifndef	_SCORE_UPDATE_H_
#define _SCORE_UPDATE_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include <Component/Update/UpdateNull/UpdateNull.h>



//======================================================================
//
// �N���X��`
//
//======================================================================

class ScoreUpdate : public UpdateNull
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �萔
	static const Vec2 SCORE_POSITION;
	static const Vec2 SCORE_SCALE;
	static const XColor4 SCORE_COLOR;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �����o�֐�
	void Init()		  override;
	void Uninit()	  override;
	void Update()	  override;
	void LateUpdate() override;
};



#endif