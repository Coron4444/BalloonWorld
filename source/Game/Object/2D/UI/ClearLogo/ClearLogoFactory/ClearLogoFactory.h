//================================================================================
//
//    �N���A���S�t�@�N�g���[�N���X
//    Author : Araki Kai                                �쐬�� : 2018/06/19
//
//================================================================================

#ifndef	_CLEAR_LOGO_FACTORY_H_
#define _CLEAR_LOGO_FACTORY_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include "../ClearLogo.h"
#include "../ClearLogoDraw/ClearLogoDraw.h"



//======================================================================
//
// �N���X��`
//
//======================================================================

class ClearLogoFactory
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �����o�֐�
	ClearLogo* Create()
	{
		ClearLogo* temp = new ClearLogo();

		// ������
		temp->Init(new ClearLogoDraw());

		return temp;
	}
};



#endif