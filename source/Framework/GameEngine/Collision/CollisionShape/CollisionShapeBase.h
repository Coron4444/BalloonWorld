//================================================================================
//!	@file	 CollisionShapeBase.h
//!	@brief	 �Փˌ`��BaseClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================
#ifndef	_COLLISION_SHAPE_BASE_H_
#define _COLLISION_SHAPE_BASE_H_



//************************************************************														   
//! @brief   �Փˌ`��BaseClass
//!
//! @details �Փˌ`���BaseClass
//************************************************************
class CollisionShapeBase
{
//====================
// �񋓌^��`
//====================
public:
	// �`��^�C�v
	enum Type
	{
		NONE = -1,
		AABB,
		CAPSULE,
		CYLINDER,
		OBB,
		PLANE,
		LINE_SEGMENT,
		SPHERE,
		TRIANGLE,
		MAX
	};


//====================
// �ϐ�
//====================
private:
	Type type_;				//!< �`��^�C�v


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �`��^�C�v�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Type �`��^�C�v
	//----------------------------------------
	Type getType();


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �R���X�g���N�^
	//! @details
	//! @param type �`��^�C�v
	//----------------------------------------
	CollisionShapeBase(Type type);

	//----------------------------------------
	//! @brief ���z�f�X�g���N�^
	//! @details
	//! @param void �Ȃ�
	//----------------------------------------
	virtual ~CollisionShapeBase() = 0;
};



#endif