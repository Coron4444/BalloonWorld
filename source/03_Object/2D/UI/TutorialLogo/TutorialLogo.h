//================================================================================
//
//    �`���[�g���A�����S�N���X
//    Author : Araki Kai                                �쐬�� : 2018/09/02
//
//================================================================================

#ifndef	_TUTORIAL_LOGO_H_
#define _TUTORIAL_LOGO_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <GameObjectBase/GameObjectBase.h>



/*********************************************************//**
* @brief
* �`���[�g���A�����S�N���X
*
* �`���[�g���A�����S�̃N���X
*************************************************************/
class TutorialLogo : public GameObjectBase
{
//==============================
// ��ÓI�����o�֐�
//==============================
private:
	unsigned logo_num_ = 0;					//!< �`���[�g���A��


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �����o�֐�
	void Init(DrawBase* draw);
	void Uninit() override;
	void Reset()  override;

	unsigned GetLogoNum() { return logo_num_; }
	void SetLogoNum(unsigned value) { logo_num_ = value; }
};



#endif