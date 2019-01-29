//================================================================================
//
//    �v�b�V���X�y�[�X���S�t�@�N�g���[�N���X
//    Author : Araki Kai                                �쐬�� : 2018/09/02
//
//================================================================================

#ifndef	_PUSH_SPACE_LOGO_FACTORY_H_
#define _PUSH_SPACE_LOGO_FACTORY_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include "../PushSpaceLogo.h"
#include "../PushSpaceLogoDraw/PushSpaceLogoDraw.h"
#include "../PushSpaceLogoUpdate/PushSpaceLogoUpdate.h"


//======================================================================
//
// �N���X��`
//
//======================================================================

class PushSpaceLogoFactory
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �����o�֐�
	PushSpaceLogo* Create()
	{
		PushSpaceLogo* temp = new PushSpaceLogo();

		// ������
		temp->Init(new PushSpaceLogoUpdate(),
			       new PushSpaceLogoDraw());

		return temp;
	}
};



#endif