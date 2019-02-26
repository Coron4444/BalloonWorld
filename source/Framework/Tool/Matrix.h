//================================================================================
//!	@file	 Matrix.h
//!	@brief	 �s��Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/23
//================================================================================
#ifndef	_MATRIX_H_
#define _MATRIX_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "Vector3D.h"



//****************************************
// �^��`
//****************************************
using MATRIX = D3DXMATRIX;



//************************************************************														   
//! @brief   �s��Class
//!
//! @details �s���Class
//************************************************************
class Matrix : public MATRIX
{
//====================
// �萔
//====================
private:
	static const Vector3D DEFAULT_RIGHT;	//!< ����E�x�N�g��
	static const Vector3D DEFAULT_UP;		//!< �����x�N�g��
	static const Vector3D DEFAULT_FORWARD;	//!< ����O�x�N�g��


//====================
// �ϐ�
//====================
private:
	Vector3D right_;			//!< �E�x�N�g��
	Vector3D up_;				//!< ��x�N�g��
	Vector3D forward_;			//!< �O�x�N�g��
	Vector3D default_right_;	//!< ����E�x�N�g��
	Vector3D default_up_;		//!< �����x�N�g��
	Vector3D default_forward_;	//!< ����O�x�N�g��


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief 11�����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float 11����
	//----------------------------------------
	float get11() const;

	//----------------------------------------
	//! @brief 11�����ݒ�֐�
	//! @details
	//! @param value 11����
	//! @retval void �Ȃ�
	//----------------------------------------
	void set11(float value);

	//----------------------------------------
	//! @brief 12�����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float 12����
	//----------------------------------------
	float get12() const;

	//----------------------------------------
	//! @brief 12�����ݒ�֐�
	//! @details
	//! @param value 12����
	//! @retval void �Ȃ�
	//----------------------------------------
	void set12(float value);

	//----------------------------------------
	//! @brief 13�����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float 13����
	//----------------------------------------
	float get13() const;

	//----------------------------------------
	//! @brief 13�����ݒ�֐�
	//! @details
	//! @param value 13����
	//! @retval void �Ȃ�
	//----------------------------------------
	void set13(float value);

	//----------------------------------------
	//! @brief 14�����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float 14����
	//----------------------------------------
	float get14() const;

	//----------------------------------------
	//! @brief 14�����ݒ�֐�
	//! @details
	//! @param value 14����
	//! @retval void �Ȃ�
	//----------------------------------------
	void set14(float value);

	//----------------------------------------
	//! @brief 21�����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float 21����
	//----------------------------------------
	float get21() const;

	//----------------------------------------
	//! @brief 21�����ݒ�֐�
	//! @details
	//! @param value 21����
	//! @retval void �Ȃ�
	//----------------------------------------
	void set21(float value);

	//----------------------------------------
	//! @brief 22�����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float 22����
	//----------------------------------------
	float get22() const;

	//----------------------------------------
	//! @brief 22�����ݒ�֐�
	//! @details
	//! @param value 22����
	//! @retval void �Ȃ�
	//----------------------------------------
	void set22(float value);

	//----------------------------------------
	//! @brief 23�����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float 23����
	//----------------------------------------
	float get23() const;

	//----------------------------------------
	//! @brief 23�����ݒ�֐�
	//! @details
	//! @param value 23����
	//! @retval void �Ȃ�
	//----------------------------------------
	void set23(float value);

	//----------------------------------------
	//! @brief 24�����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float 24����
	//----------------------------------------
	float get24() const;

	//----------------------------------------
	//! @brief 24�����ݒ�֐�
	//! @details
	//! @param value 24����
	//! @retval void �Ȃ�
	//----------------------------------------
	void set24(float value);

	//----------------------------------------
	//! @brief 31�����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float 31����
	//----------------------------------------
	float get31() const;

	//----------------------------------------
	//! @brief 31�����ݒ�֐�
	//! @details
	//! @param value 31����
	//! @retval void �Ȃ�
	//----------------------------------------
	void set31(float value);

	//----------------------------------------
	//! @brief 32�����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float 32����
	//----------------------------------------
	float get32() const;

	//----------------------------------------
	//! @brief 32�����ݒ�֐�
	//! @details
	//! @param value 32����
	//! @retval void �Ȃ�
	//----------------------------------------
	void set32(float value);

	//----------------------------------------
	//! @brief 33�����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float 33����
	//----------------------------------------
	float get33() const;

	//----------------------------------------
	//! @brief 33�����ݒ�֐�
	//! @details
	//! @param value 33����
	//! @retval void �Ȃ�
	//----------------------------------------
	void set33(float value);

	//----------------------------------------
	//! @brief 34�����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float 34����
	//----------------------------------------
	float get34() const;

	//----------------------------------------
	//! @brief 34�����ݒ�֐�
	//! @details
	//! @param value 34����
	//! @retval void �Ȃ�
	//----------------------------------------
	void set34(float value);

	//----------------------------------------
	//! @brief 41�����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float 41����
	//----------------------------------------
	float get41() const;

	//----------------------------------------
	//! @brief 41�����ݒ�֐�
	//! @details
	//! @param value 41����
	//! @retval void �Ȃ�
	//----------------------------------------
	void set41(float value);

	//----------------------------------------
	//! @brief 42�����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float 42����
	//----------------------------------------
	float get42() const;

	//----------------------------------------
	//! @brief 42�����ݒ�֐�
	//! @details
	//! @param value 42����
	//! @retval void �Ȃ�
	//----------------------------------------
	void set42(float value);

	//----------------------------------------
	//! @brief 43�����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float 43����
	//----------------------------------------
	float get43() const;

	//----------------------------------------
	//! @brief 43�����ݒ�֐�
	//! @details
	//! @param value 43����
	//! @retval void �Ȃ�
	//----------------------------------------
	void set43(float value);

	//----------------------------------------
	//! @brief 44�����擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval float 44����
	//----------------------------------------
	float get44() const;

	//----------------------------------------
	//! @brief 44�����ݒ�֐�
	//! @details
	//! @param value 44����
	//! @retval void �Ȃ�
	//----------------------------------------
	void set44(float value);

	//----------------------------------------
	//! @brief ���W�擾�擾�֐�
	//! @details
	//! @param void
	//! @retval Vector3D ���W
	//----------------------------------------
	Vector3D getPosition();

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
// ���Z�q
//====================
public:
	//----------------------------------------
	//! @brief *���Z�q
	//! @details
	//! @param &matrix �s��
	//! @retval Matrix ��Z��̍s��
	//----------------------------------------
	Matrix operator * (const Matrix& matrix) const;


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �R���X�g���N�^
	//! @details
	//! @param void �Ȃ�
	//----------------------------------------
	Matrix();

	//----------------------------------------
	//! @brief �P��float�R���X�g���N�^
	//! @details
	//! @param value ����
	//----------------------------------------
	Matrix(const float* value);

	//----------------------------------------
	//! @brief �P��float16�R���X�g���N�^
	//! @details
	//! @param value ����
	//----------------------------------------
	Matrix(const Float16* value);

	//----------------------------------------
	//! @brief �s��R���X�g���N�^
	//! @details
	//! @param matrix �s��
	//----------------------------------------
	Matrix(const Matrix& matrix);

	//----------------------------------------
	//! @brief ����float�R���X�g���N�^
	//! @details
	//! @param value11 11����
	//! @param value12 12����
	//! @param value13 13����
	//! @param value14 14����
	//! @param value21 21����
	//! @param value22 22����
	//! @param value23 23����
	//! @param value24 24����
	//! @param value31 31����
	//! @param value32 32����
	//! @param value33 33����
	//! @param value34 34����
	//! @param value41 41����
	//! @param value42 42����
	//! @param value43 43����
	//! @param value44 44����
	//----------------------------------------
	Matrix(float value11, float value12, float value13, float value14,
		   float value21, float value22, float value23, float value24,
		   float value31, float value32, float value33, float value34,
		   float value41, float value42, float value43, float value44);

	//----------------------------------------
	//! @brief �f�X�g���N�^
	//! @details
	//! @param matrix �s��
	//----------------------------------------
	~Matrix();

	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init();

	//----------------------------------------
	//! @brief ���W�s��쐬�֐�
	//! @details
	//! @param *position ���W
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreatePosition(Vector3D* position);

	//----------------------------------------
	//! @brief �g�k�s��쐬�֐�
	//! @details
	//! @param *scale �g�k
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateScale(Vector3D* scale);

	//----------------------------------------
	//! @brief X����]�s��쐬�֐�
	//! @details
	//! @param radian �p�x
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateRotationAxisX(float radian);

	//----------------------------------------
	//! @brief Z����]�s��쐬�֐�
	//! @details
	//! @param radian �p�x
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateRotationAxisY(float radian);

	//----------------------------------------
	//! @brief Z����]�s��쐬�֐�
	//! @details
	//! @param radian �p�x
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateRotationAxisZ(float radian);

	//----------------------------------------
	//! @brief �C�ӎ���]�s��쐬�֐�
	//! @details
	//! @param axis   ��
	//! @param radian �p�x
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateRotationAxisAny(Vector3D axis, float radian);

	//----------------------------------------
	//! @brief ��]�s��쐬�֐�
	//! @details
	//! @param *quaternion �N�H�[�^�j�I��
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateRotationQuaternion(Quaternion* quaternion);

	//----------------------------------------
	//! @brief ���[���h�s��쐬�֐�
	//! @details
	//! @param *scale    �g�k�s��
	//! @param *rotation ��]�s��
	//! @param *position ���W�s��
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateWorld(Matrix* scale, Matrix* rotation, Matrix* position);

	//----------------------------------------
	//! @brief �r���[�s��쐬�֐�
	//! @details
	//! @param *position     ���W
	//! @param *gazing_point �����_
	//! @param *up           �����
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateView(Vector3D* position, Vector3D* gazing_point, Vector3D* up);

	//----------------------------------------
	//! @brief ������W�n�������e�v���W�F�N�V�����s��쐬�֐�
	//! @details
	//! @param angle_of_view ��p
	//! @param screen_width  �X�N���[����
	//! @param screen_height �X�N���[������
	//! @param near_clip     �j�A�N���b�v
	//! @param far_clip      �t�@�[�N���b�v
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateProjectionPerspectiveFovLH(float angle_of_view, float screen_width,
										  float screen_height, float near_clip,
										  float far_clip);

	//----------------------------------------
	//! @brief ���ˉe�v���W�F�N�V�����s��쐬�֐�
	//! @details
	//! @param angle_of_view ��p
	//! @param screen_width  �X�N���[����
	//! @param screen_height �X�N���[������
	//! @param near_clip     �j�A�N���b�v
	//! @param far_clip      �t�@�[�N���b�v
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateProjectionOrtho(float angle_of_view, float screen_width,
							   float screen_height, float near_clip,
							   float far_clip);

	//----------------------------------------
	//! @brief 2D�v���W�F�N�V�����s��쐬�֐�
	//! @details
	//! @param screen_width  �X�N���[����
	//! @param screen_height �X�N���[������
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateProjection2D(float screen_width, float screen_height);

	//----------------------------------------
	//! @brief �t�s�񉻊֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void ChangeInverse();

	//----------------------------------------
	//! @brief �]�u�s�񉻊֐�
	//! @details
	//! @param is_position_off ���s�ړ�OFF�t���O
	//! @retval void �Ȃ�
	//----------------------------------------
	void ChangeTranspose(bool is_position_off = false);

	//----------------------------------------
	//! @brief �e�s��ǉ��֐�
	//! @details
	//! @param matrix �e�s��
	//! @retval void �Ȃ�
	//----------------------------------------
	void AddParentMatrix(Matrix* matrix);

	//----------------------------------------
	//! @brief �q�s��ǉ��֐�
	//! @details
	//! @param matrix �q�s��
	//! @retval void �Ȃ�
	//----------------------------------------
	void AddChildMatrix(Matrix* matrix);

private:
	//----------------------------------------
	//! @brief ���쐬�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateAxis();

	//----------------------------------------
	//! @brief �r���[���쐬�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateViewAxis();
};



#endif