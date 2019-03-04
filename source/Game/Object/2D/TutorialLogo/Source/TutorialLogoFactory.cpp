//================================================================================
//!	@file	 TutorialLogoFactory.cpp
//!	@brief	 チュートリアルロゴ生成Class
//! @details 
//!	@author  Kai Araki									@date 2018/09/02
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../TutorialLogoFactory.h"



//****************************************
// 関数定義
//****************************************
TutorialLogo* TutorialLogoFactory::Create()
{
	TutorialLogo* temp = new TutorialLogo();
	temp->Init(new TutorialLogoDraw());
	return temp;
}