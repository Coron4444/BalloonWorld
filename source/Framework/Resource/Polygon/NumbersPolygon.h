//================================================================================
//!	@file	 NumbersPolygon.h
//!	@brief	 �����Q�|���S��Class
//! @details 
//!	@author  Kai Araki									@date 2018/06/19
//================================================================================
#ifndef	_NUMBERS_H_
#define _NUMBERS_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <vector>

#include <Tool/Transform.h>


//****************************************
// �N���X�錾
//****************************************
class PlanePolygon;
class TextureObject;



//************************************************************														   
//! @brief   �����Q�|���S��Class
//!
//! @details �����Q�̃|���S��Class
//************************************************************
class NumbersPolygon
{
//====================
// �N���X��`
//====================
public:
	//****************************************											   
	//! @brief   �����|���S��Class
	//!
	//! @details �����̃|���S��Class
	//****************************************
	class NumberPolygon
	{
	//====================
	// �ϐ�
	//====================
	private:
		PlanePolygon* plane_polygon_ = nullptr;		//!< ���ʃ|���S��
		TextureObject* texture_ = nullptr;			//!< �e�N�X�`���I�u�W�F�N�g
		Transform transform_;						//!< �ό`
		int number_;								//!< ���݂̐���
		int old_number_;							//!< �O��̐���

	//====================
	// �v���p�e�B
	//====================
	public:
		//----------------------------------------
		//! @brief �����ݒ�֐�
		//! @details
		//! @param value ����
		//! @retval void �Ȃ�
		//----------------------------------------
		void setNumber(int value);

		//----------------------------------------
		//! @brief �F�ݒ�֐�
		//! @details
		//! @param value �F
		//! @retval void �Ȃ�
		//----------------------------------------
		void setColor(XColor4 value);

		//----------------------------------------
		//! @brief �e�N�X�`���I�u�W�F�N�g�ݒ�֐�
		//! @details
		//! @param value �e�N�X�`���I�u�W�F�N�g
		//! @retval void �Ȃ�
		//----------------------------------------
		void setTextureObject(TextureObject* value);

		//----------------------------------------
		//! @brief �ό`�擾�֐�
		//! @details
		//! @param void �Ȃ�
		//! @retval Transform* �ό`
		//----------------------------------------
		Transform* getpTransform();


	//====================
	// �֐�
	//====================
	public:
		//----------------------------------------
		//! @brief �������֐�
		//! @details
		//! @param void �Ȃ�
		//! @retval void �Ȃ�
		//----------------------------------------
		void Init();

		//----------------------------------------
		//! @brief �I���֐�
		//! @details
		//! @param void �Ȃ�
		//! @retval void �Ȃ�
		//----------------------------------------
		void Uninit();

		//----------------------------------------
		//! @brief �`��֐�
		//! @details
		//! @param void �Ȃ�
		//! @retval void �Ȃ�
		//----------------------------------------
		void Draw();
	};


//====================
// �ϐ�
//====================
private:
	int digits_num_ = 0;						//!< ����
	bool is_zero_ = false;						//!< �[�����߃t���O
	Vec2 position_ = {0.0f, 0.0f};				//!< ���W
	Vec2 scale_ = {1.0f, 1.0f};					//!< �g�k
	XColor4 color_ = {1.0f, 1.0f, 1.0f, 1.0f};	//!< �F
	TextureObject* texture_ = nullptr;			//!< �e�N�X�`���I�u�W�F�N�g
	std::vector<NumberPolygon*> number_;		//!< �����|���S���z��


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �����ݒ�֐�
	//! @details
	//! @param value ����
	//! @retval void �Ȃ�
	//----------------------------------------
	void setNumber(int value);

	//----------------------------------------
	//! @brief �����ݒ�֐�
	//! @details
	//! @param value ����
	//! @retval void �Ȃ�
	//----------------------------------------
	void setDigitsNum(int value);

	//----------------------------------------
	//! @brief �[�����߃t���O�ݒ�֐�
	//! @details
	//! @param value �[�����߃t���O
	//! @retval void �Ȃ�
	//----------------------------------------
	void setIsZero(bool value);

	//----------------------------------------
	//! @brief ���W�ݒ�֐�
	//! @details
	//! @param value ���W
	//! @retval void �Ȃ�
	//----------------------------------------
	void setPosition(Vec2 value);

	//----------------------------------------
	//! @brief �g�k�ݒ�֐�
	//! @details
	//! @param value �g�k
	//! @retval void �Ȃ�
	//----------------------------------------
	void setScale(Vec2 value);

	//----------------------------------------
	//! @brief �F�ݒ�֐�
	//! @details
	//! @param value �F
	//! @retval void �Ȃ�
	//----------------------------------------
	void setColor(XColor4 value);

	//----------------------------------------
	//! @brief �e�N�X�`���I�u�W�F�N�g�ݒ�֐�
	//! @details
	//! @param value �e�N�X�`���I�u�W�F�N�g
	//! @retval void �Ȃ�
	//----------------------------------------
	void setTextureObject(TextureObject* value);

	//----------------------------------------
	//! @brief �I�u�W�F�N�g���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval unsigned �I�u�W�F�N�g��
	//----------------------------------------
	unsigned getObjectNum();

	//----------------------------------------
	//! @brief �s��擾�֐�
	//! @details
	//! @param mesh_index ���b�V���C���f�b�N�X
	//! @retval unsigned ���b�V����
	//----------------------------------------
	MATRIX* getpMatrix(int mesh_index);


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init();

	//----------------------------------------
	//! @brief �I���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Uninit();

	//----------------------------------------
	//! @brief �`��֐�
	//! @details
	//! @param mesh_index ���b�V���C���f�b�N�X
	//! @retval void �Ȃ�
	//----------------------------------------
	void Draw(int mesh_index);


private:
	//----------------------------------------
	//! @brief ���l�ߊ֐�
	//! @details
	//! @param number      ����
	//! @param *digits_num ����
	//! @retval void �Ȃ�
	//----------------------------------------
	void LeftJustified(int number, int* digits_num);

	//----------------------------------------
	//! @brief �����|���S���쐬�֐�
	//! @details
	//! @param number      ����
	//! @param *digits_num ����
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateNumberPolygon(int number, int* digits_num);

	//----------------------------------------
	//! @brief �J���X�g�����֐�
	//! @details
	//! @param *number    ����
	//! @param digits_num ����
	//! @retval void �Ȃ�
	//----------------------------------------
	void IsCountStop(int* number, int digits_num);

	//----------------------------------------
	//! @brief �e���X�V�֐�
	//! @details
	//! @param number     ����
	//! @param digits_num ����
	//! @retval void �Ȃ�
	//----------------------------------------
	void UpdateEachDigit(int number, int digits_num);

	//----------------------------------------
	//! @brief �����|���S���֐�
	//! @details
	//! @param number     ����
	//! @param digits_num ����
	//! @retval void �Ȃ�
	//----------------------------------------
	void ReleaseNumberPolygon();
};



#endif