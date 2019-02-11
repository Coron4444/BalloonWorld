//================================================================================
//!	@file	 BalloonGroup.h
//!	@brief	 ���D�QClass
//! @details 
//!	@author  Kai Araki									@date 2019/02/10
//================================================================================
#ifndef	_BALLOON_GROUP_H_
#define _BALLOON_GROUP_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <vector>

#include <GameEngine/GameObject/GameObjectNull.h>
#include <Tool/ReferenceList.h>



//****************************************
// �N���X��`
//****************************************
class Balloon;



//************************************************************														   
//! @brief   ���D�QClass
//!
//! @details ���D�̏W��Class
//************************************************************
class BalloonGroup : public GameObjectNull
{
//====================
// �萔
//====================
public:
	static const int MAX_BALLOON_NUM = 10;		//!< �ő啗�D��
	static const int BALLOON_LINE_NUM;			//!< ���D�̐��̐�


//====================
// �ϐ�
//====================
private:
	ReferenceList<BalloonGroup> reference_list_;	//!< �Q�ƃ��X�g
	std::vector<Balloon*> balloons_;				//!< ���D�Q
	int end_index_;									//!< �I�[�C���f�b�N�X
	

//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �Q�ƃ��X�g�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval ReferenceList<BalloonGroup>* �Q�ƃ��X�g
	//----------------------------------------
	ReferenceList<BalloonGroup>* getpReferenceList();

	//----------------------------------------
	//! @brief ���D���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval unsigned ���D��
	//----------------------------------------
	unsigned getBalloonNum();

	//----------------------------------------
	//! @brief ���W�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vec3 ���W
	//----------------------------------------
	Vec3 getPosition();

	//----------------------------------------
	//! @brief ���W�ݒ�֐�
	//! @details
	//! @param value ���W
	//! @retval void �Ȃ�
	//----------------------------------------
	void setPosition(Vec3 value);


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param balloon_num ���D��
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init(unsigned balloon_num);

	//----------------------------------------
	//! @brief �I���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Uninit() override;

	//----------------------------------------
	//! @brief �S������֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void ReleaseConstraint();

	//----------------------------------------
	//! @brief ���x�ǉ��֐�
	//! @details
	//! @param velocity ���x
	//! @retval void �Ȃ�
	//----------------------------------------
	void AddVelocity(Vec3 velocity);

	//----------------------------------------
	//! @brief �����x�ǉ��֐�
	//! @details
	//! @param acceleration �����x
	//! @retval void �Ȃ�
	//----------------------------------------
	void AddAcceleration(Vec3 acceleration);

	//----------------------------------------
	//! @brief �j��֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Rupture();

private:
};



#endif