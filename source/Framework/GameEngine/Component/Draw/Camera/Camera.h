//================================================================================
//!	@file	 Camera.h
//!	@brief	 �J����Class
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================
#ifndef	_CAMERA_H_
#define _CAMERA_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <Transform\AxisVector\AxisVector.h>



//************************************************************														   
//! @brief   �J����Class
//!
//! @details �J������Class
//************************************************************
class Camera
{
//====================
// �N���X��`
//====================
public:
	//****************************************														   
	//! @brief �J�����X�e�[�gClass
	//!
	//! @details �J�����X�e�[�g��Class
	//****************************************
	class State
	{
	//====================
	// �ϐ�
	//====================
	private:
		Camera* camera_;	//!< �J����

	//====================
	// �v���p�e�B
	//====================
	public:
		//----------------------------------------
		//! @brief �J�����擾�֐�
		//! @details
		//! @param void �Ȃ�
		//! @retval Camera* �J����
		//----------------------------------------
		Camera* getpCamera();

		//----------------------------------------
		//! @brief �J�����ݒ�֐�
		//! @details
		//! @param *value �J����
		//! @retval void �Ȃ�
		//----------------------------------------
		void setCamera(Camera* value);


	//====================
	// �֐�
	//====================
	public:
		//----------------------------------------
		//! @brief �f�X�g���N�^
		//! @details
		//! @param void �Ȃ�
		//----------------------------------------
		virtual ~State() = 0;

		//----------------------------------------
		//! @brief �������֐�
		//! @details
		//! @param void �Ȃ�
		//! @retval void �Ȃ�
		//----------------------------------------
		virtual void Init() = 0;

		//----------------------------------------
		//! @brief �I���֐�
		//! @details
		//! @param void �Ȃ�
		//! @retval void �Ȃ�
		//----------------------------------------
		virtual void Uninit() = 0;

		//----------------------------------------
		//! @brief �X�V�֐�
		//! @details
		//! @param void �Ȃ�
		//! @retval void �Ȃ�
		//----------------------------------------
		virtual void Update() = 0;
	};


//====================
// �񋓌^��`
//====================
public:
	enum Type
	{
		NONE = -1,
		PERSPECTIVE,
		ORTHO,
		TWO_DIMENSIONAL,
		MAX
	};


//====================
// �ϐ�
//====================
public:
	static const float NEAR_CLIPPING_PLANE;		//!< �ߖʃN���b�v
	static const float FAR_CLIPPING_PLANE;		//!< ���ʃN���b�v
	static const int   DEFAULT_ANGLE_OF_VIEW;	//!< ��p


//====================
// �ϐ�
//====================
private:
	Vector3D position_;					//!< ���W
	Vector3D look_at_point_;			//!< �����_
	Vector3D up_;						//!< �����
	int angle_of_view_;					//!< ��p
	AxisVector axis_;					//!< ��
	MATRIX view_;						//!< �r���[�s��
	MATRIX view_2D_;					//!< �r���[�s��(2D)
	MATRIX projection_perspective_;		//!< �v���W�F�N�V�����s��(�������e)
	MATRIX projection_ortho_;			//!< �v���W�F�N�V�����s��(���ˉe)
	MATRIX projection_2D_;				//!< �v���W�F�N�V�����s��(2D)
	State* state_ = nullptr;			//!< �X�e�[�g
	Type type_ = Type::PERSPECTIVE;		//!< �^�C�v


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �r���[�s��擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval MATRIX* �r���[�s��
	//----------------------------------------
	const MATRIX* getpViewMatrix() const;

	//----------------------------------------
	//! @brief �v���W�F�N�V�����s��擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval MATRIX* �v���W�F�N�V�����s��
	//----------------------------------------
	const MATRIX* getpProjectionMatrix() const;

	//----------------------------------------
	//! @brief ���W�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D* ���W
	//----------------------------------------
	Vector3D* getpPositon();
	
	//----------------------------------------
	//! @brief �����_�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D* �����_
	//----------------------------------------
	Vector3D* getpLookAtPoint();
	
	//----------------------------------------
	//! @brief ������擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D* �����
	//----------------------------------------
	Vector3D* getpUp();
	
	//----------------------------------------
	//! @brief ��p�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval int ��p
	//----------------------------------------
	int getAngleOfView();
	
	//----------------------------------------
	//! @brief ��p�ݒ�֐�
	//! @details
	//! @param value ��p
	//! @retval void �Ȃ�
	//----------------------------------------
	void setAngleOfView(int value);
	
	//----------------------------------------
	//! @brief ���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval AxisVector* ��
	//----------------------------------------
	AxisVector* getpAxis();
	
	//----------------------------------------
	//! @brief �O�x�N�g���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D* �O�x�N�g��
	//----------------------------------------
	const Vector3D* getpForwardVector() const;
	
	//----------------------------------------
	//! @brief �X�e�[�g�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval State* �X�e�[�g
	//----------------------------------------
	const State* getpState() const;

	//----------------------------------------
	//! @brief �X�e�[�g�ݒ�֐�
	//! @details
	//! @param *value �X�e�[�g
	//! @retval void �Ȃ�
	//----------------------------------------
	void setState(State* value);
	
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


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param state         �X�e�[�g
	//! @param position      ���W
	//! @param look_at_point �����_
	//! @param up            ��x�N�g��
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init(State* state, Vec3 position = {0.0f, 0.0f, -10.0f},
			  Vec3 look_at_point = {0.0f, 0.0f, 0.0f}, Vec3 up = {0.0f, 1.0f, 0.0f});

	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Uninit();

	//----------------------------------------
	//! @brief �X�V�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Update();

	//----------------------------------------
	//! @brief �r���[�s��쐬�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateViewMatrix();

	//----------------------------------------
	//! @brief �v���W�F�N�V�����s��쐬�֐�(�������e�s��)
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateProjectionMatrix_PerspectiveFov();

	//----------------------------------------
	//! @brief �v���W�F�N�V�����s��쐬�֐�(���ˉe�s��)
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateProjectionMatrix_Ortho();

	//----------------------------------------
	//! @brief �v���W�F�N�V�����s��쐬�֐�(2D)
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateProjectionMatrix_2D();
};



#endif