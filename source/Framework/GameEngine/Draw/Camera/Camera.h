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
#include <Tool/Axis.h>
#include <Tool/Vector3D.h>
#include <Tool/Matrix.h>



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
		Camera* camera_;			//!< �J����
		bool is_input_ = true;		//!< ���̓t���O
		bool is_update_ = true;		//!< �X�V�t���O


	//====================
	// �v���p�e�B
	//====================
	public:
		//----------------------------------------
		//! @brief ���̓t���O�擾�֐�
		//! @details
		//! @param void �Ȃ�
		//! @retval bool ���̓t���O
		//----------------------------------------
		bool getIsInput();

		//----------------------------------------
		//! @brief ���̓t���O�擾�֐�
		//! @details
		//! @param value ���̓t���O
		//! @retval void �Ȃ�
		//----------------------------------------
		void setIsInput(bool value);

		//----------------------------------------
		//! @brief �X�V�t���O�擾�֐�
		//! @details
		//! @param void �Ȃ�
		//! @retval bool �X�V�t���O
		//----------------------------------------
		bool getIsUpdate();

		//----------------------------------------
		//! @brief �X�V�t���O�擾�֐�
		//! @details
		//! @param value �X�V�t���O
		//! @retval void �Ȃ�
		//----------------------------------------
		void setIsUpdate(bool value);

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
	enum class Type
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
	static const float DEFAULT_ANGLE_OF_VIEW;	//!< ��p


//====================
// �ϐ�
//====================
private:
	Vector3D position_;					//!< ���W
	Vector3D gazing_point_;				//!< �����_
	Vector3D up_;						//!< �����
	float angle_of_view_;				//!< ��p
	Matrix view_;						//!< �r���[�s��
	Matrix view_2D_;					//!< �r���[�s��(2D)
	Matrix projection_perspective_;		//!< �v���W�F�N�V�����s��(�������e)
	Matrix projection_ortho_;			//!< �v���W�F�N�V�����s��(���ˉe)
	Matrix projection_2D_;				//!< �v���W�F�N�V�����s��(2D)
	State* state_;						//!< �X�e�[�g
	Type type_;							//!< �^�C�v


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �r���[�s��擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Matrix* �r���[�s��
	//----------------------------------------
	Matrix* getpViewMatrix();

	//----------------------------------------
	//! @brief �v���W�F�N�V�����s��擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Matrix* �v���W�F�N�V�����s��
	//----------------------------------------
	Matrix* getpProjectionMatrix();

	//----------------------------------------
	//! @brief ���W�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D* ���W
	//----------------------------------------
	Vector3D* getpPosition();
	
	//----------------------------------------
	//! @brief �����_�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D* �����_
	//----------------------------------------
	Vector3D* getpGazingPoint();
	
	//----------------------------------------
	//! @brief ��p�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float ��p
	//----------------------------------------
	float getAngleOfView();
	
	//----------------------------------------
	//! @brief ��p�ݒ�֐�
	//! @details
	//! @param value ��p
	//! @retval void �Ȃ�
	//----------------------------------------
	void setAngleOfView(float value);
	
	//----------------------------------------
	//! @brief �X�e�[�g�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval State* �X�e�[�g
	//----------------------------------------
	State* getpState();

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

	//----------------------------------------
	//! @brief �E�x�N�g���擾�֐�
	//! @details
	//! @param void
	//! @retval Vector3D* �E�x�N�g��
	//----------------------------------------
	Vector3D* getpRight();

	//----------------------------------------
	//! @brief ��x�N�g���擾�֐�
	//! @details
	//! @param void
	//! @retval Vector3D* ��x�N�g��
	//----------------------------------------
	Vector3D* getpUp();

	//----------------------------------------
	//! @brief �O�x�N�g���擾�֐�
	//! @details
	//! @param void
	//! @retval Vector3D* �O�x�N�g��
	//----------------------------------------
	Vector3D* getpForward();

	//----------------------------------------
	//! @brief ����O�x�N�g���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D* ����O�x�N�g��
	//----------------------------------------
	Vector3D* getpDefaultForward();

	//----------------------------------------
	//! @brief �����x�N�g���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D* �����x�N�g��
	//----------------------------------------
	Vector3D* getpDefaultUp();

	//----------------------------------------
	//! @brief ����E�x�N�g���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Vector3D* ����E�x�N�g��
	//----------------------------------------
	Vector3D* getpDefaultRight();


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �R���X�g���N�^
	//! @details
	//! @param void �Ȃ�
	//----------------------------------------
	Camera();

	//----------------------------------------
	//! @brief �f�X�g���N�^
	//! @details
	//! @param void �Ȃ�
	//----------------------------------------
	~Camera();


	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param state        �X�e�[�g
	//! @param position     ���W
	//! @param gazing_point �����_
	//! @param up           ��x�N�g��
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init(State* state, Vector3D position = {0.0f, 0.0f, -10.0f},
			  Vector3D gazing_point = {0.0f, 0.0f, 0.0f}, 
			  Vector3D up = {0.0f, 1.0f, 0.0f});

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
	//! @brief �������e�v���W�F�N�V�����s��쐬�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateProjectionMatrixPerspectiveFov();

	//----------------------------------------
	//! @brief ���ˉe�v���W�F�N�V�����s��쐬�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateProjectionMatrixOrtho();

	//----------------------------------------
	//! @brief 2D�v���W�F�N�V�����s��쐬�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateProjectionMatrix2D();
};



#endif