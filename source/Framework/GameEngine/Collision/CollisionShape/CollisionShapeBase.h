//================================================================================
//!	@file	 CollisionShapeBase.h
//!	@brief	 �Փˌ`��BaseClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================
#ifndef	_COLLISION_SHAPE_BASE_H_
#define _COLLISION_SHAPE_BASE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <Tool/Vector3D.h>



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
	enum class Type
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
	Type type_ = Type::NONE;	//!< �^�C�v
	Vector3D min_;				//!< �ŏ��l
	Vector3D max_;				//!< �ő�l

//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �^�C�v�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Type �^�C�v
	//----------------------------------------
	Type getType();

	//----------------------------------------
	//! @brief �^�C�v�ݒ�֐�
	//! @details
	//! @param value �^�C�v
	//! @retval void �Ȃ�
	//----------------------------------------
	void setType(Type value);
	
	//----------------------------------------
	//! @brief �ő���W�擾�֐�
	//! @details �`�����AABB�̍ő���W
	//! @param void �Ȃ�
	//! @retval Vector3D* �ő���W
	//----------------------------------------
	Vector3D* getpMax();

	//----------------------------------------
	//! @brief �ŏ����W�擾�֐�
	//! @details �`�����AABB�̍ŏ����W
	//! @param void �Ȃ�
	//! @retval Vector3D* �ŏ����W
	//----------------------------------------
	Vector3D* getpMin();


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief ���z�f�X�g���N�^
	//! @details
	//! @param void �Ȃ�
	//----------------------------------------
	virtual ~CollisionShapeBase() = 0;

	//----------------------------------------
	//! @brief �X�V�֐�
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void Update() = 0;

protected:
	//----------------------------------------
	//! @brief �ŏ��l�ƍő�l�Z�o�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void CalculationMinAndMax() = 0;
};



#endif