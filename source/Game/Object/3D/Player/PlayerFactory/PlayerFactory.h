//================================================================================
//
//    �v���C���[�t�@�N�g���[�N���X
//    Author : Araki Kai                                �쐬�� : 2018/07/23
//
//================================================================================

#ifndef	_PLAYER_FACTORY_H_
#define _PLAYER_FACTORY_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include "../Player.h"
#include "../PlayerUpdate/PlayerUpdate.h"
#include "../PlayerDraw/PlayerDraw.h"
#include "../PlayerCollision/PlayerCollision.h"


//======================================================================
//
// �N���X��`
//
//======================================================================

class PlayerFactory
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �����o�֐�
	Player* Create(GameScene* game_scene)
	{
		Player* temp = new Player();

		// ������
		temp->Init(new PlayerUpdate(),
				   new PlayerDraw(),
				   new PlayerCollision(),
			       game_scene);

		return temp;
	}
};



#endif