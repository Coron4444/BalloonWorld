//================================================================================
//
//    �v���C���[�t�@�N�g���[�N���X
//    Author : Araki Kai                                �쐬�� : 2018/07/23
//
//================================================================================

#ifndef	_STENCIL_SHADOW_TEST_FACTORY_H_
#define _STENCIL_SHADOW_TEST_FACTORY_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include "../StencilShadowTest.h"
#include "../StencilShadowTestDraw/StencilShadowTestDraw.h"



//======================================================================
//
// �N���X��`
//
//======================================================================

class StencilShadowTestFactory
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �����o�֐�
	StencilShadowTest* Create()
	{
		StencilShadowTest* temp = new StencilShadowTest();

		// ������
		temp->Init(new StencilShadowTestDraw());

		return temp;
	}
};



#endif