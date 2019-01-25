//================================================================================
//
//    �s��g���N���X
//    Author : Araki Kai                                �쐬�� : 2018/08/16
//
//================================================================================

#ifndef	_MATRIX_EXTEND_H_
#define _MATRIX_EXTEND_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include <d3dx9.h>
#include <Vector3D.h>



//======================================================================
//
// �N���X��`
//
//======================================================================
/**
* @brief
* DirectX9�̍s��̊g���ŃN���X
*
* �e��s�񂪑����Ă��܂��B
*/

class MatrixExtend
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	/** 
	* * @brief
	* �f�t�H���g�R���X�g���N�^
	*/
	MatrixExtend();


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	/** �f�X�g���N�^ */
	~MatrixExtend();


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	/**
	* @brief ���s�ړ��s��̍X�V
	* @param position : �s��ɂ��������W�l
	*/ 
	void UpdateTranslationMatrix(const Vec3* position);
	
	/**
	* @brief  ���s�ړ��s��̎擾
	* @return �s��̃|�C���^���擾
	*/ 
	MATRIX* GetTranslationMatrix(){return &matrix_translation_;}
	
	/**
	* @brief �g�k�s��̍X�V
	* @param scale : �s��ɂ������g�k�l
	*/
	void UpdateScaleMatrix(const Vec3* scale);

	/**
	* @brief  �g�k�s��̎擾
	* @return �s��̃|�C���^���擾
	*/
	MATRIX* GetScaleMatrix(){return &matrix_scale_;}

	// ��]
	void UpdateRotationMatrix(const Quaternion* quaternion);
	MATRIX* GetRotationMatrix(){return &matrix_rotation_;}

	// �t�s��
	void UpdateInverseMatrix(const MATRIX* matrix);
	MATRIX* GetInverseMatrix(){return &matrix_inverse_;}
	
	// �]�u�s��
	void UpdateTransposeMatrix(const MATRIX* matrix);
	void TransposeMatrixTranslationOff();
	

	// ���[���h�s��
	void UpdateWorldMatrixSRT();
	void UpdateWorldMatrixISRT();
	MATRIX* GetWorldMatrix(){return &matrix_world_;}


	// �e�̃��[���h�s�����Z
	void MultiplicationParentMatrix(const MATRIX* parent_matrix);


//------------------------------------------------------------
private :
	// ���Z�b�g
	void ResetAllMatrix();
	void ResetTranslationMatrix();
	void ResetScaleMatrix();
	void ResetRotationMatrix();
	void ResetInverseMatrix();
	void ResetWorldMatrix();



//------------------------------------------------------------
private :
	// �����o�ϐ�
	MATRIX matrix_translation_;
	MATRIX matrix_scale_;
	MATRIX matrix_rotation_;
	MATRIX matrix_inverse_;
	MATRIX matrix_world_;
};





//======================================================================
//
// ��ÓI�����o�֐���`( inline )
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �f�t�H���g�R���X�g���N�^ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline MatrixExtend::MatrixExtend() 
{
	ResetAllMatrix();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �f�X�g���N�^ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline MatrixExtend::~MatrixExtend() 
{

}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ���s�s��X�V�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline void MatrixExtend::UpdateTranslationMatrix(const Vec3* position)
{
	D3DXMatrixTranslation(&matrix_translation_, position->x, position->y, position->z);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �g�k�s��X�V�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline void MatrixExtend::UpdateScaleMatrix(const Vec3* scale)
{
	D3DXMatrixScaling(&matrix_scale_, scale->x, scale->y, scale->z);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ��]�s��X�V�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline void MatrixExtend::UpdateRotationMatrix(const Quaternion* quaternion)
{
	D3DXMatrixRotationQuaternion(&matrix_rotation_, quaternion);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �t�s��X�V�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline void MatrixExtend::UpdateInverseMatrix(const MATRIX* matrix)
{
	D3DXMatrixInverse(&matrix_inverse_, NULL, matrix);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �]�u�s��֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline void MatrixExtend::UpdateTransposeMatrix(const MATRIX* matrix)
{
	D3DXMatrixTranspose(&matrix_inverse_, matrix);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �]�u�s��̕��s�ړ���OFF�ɂ���֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline void MatrixExtend::TransposeMatrixTranslationOff()
{
	matrix_inverse_._14 = 0.0f;
	matrix_inverse_._24 = 0.0f;
	matrix_inverse_._34 = 0.0f;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ���[���h�s��쐬�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline void MatrixExtend::UpdateWorldMatrixSRT()
{
	D3DXMatrixMultiply(&matrix_world_, &matrix_scale_, &matrix_rotation_);
	D3DXMatrixMultiply(&matrix_world_, &matrix_world_, &matrix_translation_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ���[���h�s��쐬( �t�s����܂� )�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline void MatrixExtend::UpdateWorldMatrixISRT()
{
	D3DXMatrixMultiply(&matrix_world_, &matrix_scale_, &matrix_rotation_);
	D3DXMatrixMultiply(&matrix_world_, &matrix_world_, &matrix_translation_);

	D3DXMatrixMultiply(&matrix_world_, &matrix_inverse_, &matrix_world_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ���[���h�s��ɐe�̍s�����Z����֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline void MatrixExtend::MultiplicationParentMatrix(const MATRIX* parent_matrix)
{
	D3DXMatrixMultiply(&matrix_world_, &matrix_world_, parent_matrix);
}



//--------------------------------------------------------------------------------
//
// [ �S�Ă̍s��̃��Z�b�g�֐� ]
//
//--------------------------------------------------------------------------------

inline void MatrixExtend::ResetAllMatrix()
{
	ResetTranslationMatrix();
	ResetScaleMatrix();
	ResetRotationMatrix();
	ResetInverseMatrix();
	ResetWorldMatrix();
}



//--------------------------------------------------------------------------------
//
// [ ���s�s�񃊃Z�b�g�֐� ]
//
//--------------------------------------------------------------------------------

inline void MatrixExtend::ResetTranslationMatrix()
{
	D3DXMatrixIdentity(&matrix_translation_);
}



//--------------------------------------------------------------------------------
//
// [ �g�k�s�񃊃Z�b�g�֐� ]
//
//--------------------------------------------------------------------------------

inline void MatrixExtend::ResetScaleMatrix()
{
	D3DXMatrixIdentity(&matrix_scale_);
}



//--------------------------------------------------------------------------------
//
// [ ��]�s�񃊃Z�b�g�֐� ]
//
//--------------------------------------------------------------------------------

inline void MatrixExtend::ResetRotationMatrix()
{
	D3DXMatrixIdentity(&matrix_rotation_);
}




//--------------------------------------------------------------------------------
//
// [ �t�s�񃊃Z�b�g�֐� ]
//
//--------------------------------------------------------------------------------

inline void MatrixExtend::ResetInverseMatrix()
{
	D3DXMatrixIdentity(&matrix_inverse_);
}



//--------------------------------------------------------------------------------
//
// [ ���[���h�s�񃊃Z�b�g�֐� ]
//
//--------------------------------------------------------------------------------

inline void MatrixExtend::ResetWorldMatrix()
{
	D3DXMatrixIdentity(&matrix_world_);
}



#endif