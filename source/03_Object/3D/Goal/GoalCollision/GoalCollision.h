//================================================================================
//
//    �S�[���Փ˃N���X
//    Author : Araki Kai                                �쐬�� : 2018/11/28
//
//================================================================================

#ifndef	_GOAL_COLLISION_H_
#define _GOAL_COLLISION_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <string>

#include <Component/Collision/CollisionNull/CollisionNull.h>




/*********************************************************//**
* @brief
* �S�[���Փ˃N���X
*
* �S�[���̏Փ˃N���X
*************************************************************/
class GoalCollision : public CollisionNull
{
//==============================
// �萔
//==============================
private:
	static const float BOUNDING_SPHERE_RADIUS;
	static const float SUBSTANCE_RADIUS;


//==============================
// �񋓌^��`
//==============================
public:
	enum ObjectTag
	{
		NONE = -1,
		BOUNDING_SPHERE,
		SUBSTANCE,
		MAX
	};


//==============================
// ��ÓI�����o�ϐ�
//==============================
private:
	CollisionObjects* collision_objects_;
	CollisionObject* bounding_sphere_;
	CollisionObject* substance_;


//==============================
// ��ÓI�����o�֐�
//==============================
public:
	/**
	* @brief
	* �������֐�
	*/
	void Init() override;

	/**
	* @brief
	* �I���֐�
	*/
	void Uninit() override;

	/**
	* @brief
	* �X�V�֐�
	*/
	virtual void Update() override;
};



#endif