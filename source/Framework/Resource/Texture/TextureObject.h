//================================================================================
//!	@file	 TextureObject.h
//!	@brief	 �e�N�X�`���I�u�W�F�N�gClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/01
//================================================================================
#ifndef	_TEXTURE_OBJECT_H_
#define _TEXTURE_OBJECT_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <string>
#include <vector>

#include <GameEngine/Renderer/Renderer.h>
#include <Tool/Vector3D.h>



//************************************************************														   
//! @brief   �e�N�X�`���I�u�W�F�N�gClass
//!
//! @details �e�N�X�`���̃I�u�W�F�N�gClass
//************************************************************
class TextureObject
{
//====================
// �N���X��`
//====================
public:
	//****************************************											   
	//! @brief   UVClass
	//!
	//! @details UV��Class
	//****************************************
	class UV
	{
	//====================
	// �ϐ�
	//====================
	private:
		Vec2 left_up_uv_;		//!< ����UV
		Vec2 right_bottom_uv_;	//!< �E��UV


	//====================
	// �v���p�e�B
	//====================
	public:
		//----------------------------------------
		//! @brief ����U�����擾�֐�
		//! @details
		//! @param void �Ȃ�
		//! @retval float* ����U����
		//----------------------------------------
		float* getpLeftUpU();

		//----------------------------------------
		//! @brief ����V�����擾�֐�
		//! @details
		//! @param void �Ȃ�
		//! @retval float* ����V����
		//----------------------------------------
		float* getpLeftUpV();

		//----------------------------------------
		//! @brief �E��U�����擾�֐�
		//! @details
		//! @param void �Ȃ�
		//! @retval float* �E��U����
		//----------------------------------------
		float* getpRightButtomU();

		//----------------------------------------
		//! @brief �E��V�����擾�֐�
		//! @details
		//! @param void �Ȃ�
		//! @retval float* �E��V����
		//----------------------------------------
		float* getpRightButtomV();
	};


//====================
// �ϐ�
//====================
private:
	int width_;										//!< ��
	int height_;									//!< ����
	int division_num_;								//!< ������
	std::vector<UV> uv_;							//!< UV�z��
	LPDIRECT3DTEXTURE9 texture_handler_ = nullptr;	//!< �e�N�X�`���n���h��
	std::string map_key_name_;						//!< �}�b�v�p�L�[��
	int reference_counter_ = 0;						//!< �Q�ƃJ�E���^


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief ���擾�֐�
	//! @details
	//! @param void �Ȃ� 
	//! @retval int ��
	//----------------------------------------
	int	getWidth();

	//----------------------------------------
	//! @brief �����擾�֐�
	//! @details
	//! @param void �Ȃ� 
	//! @retval int ����
	//----------------------------------------
	int	getHeight();

	//----------------------------------------
	//! @brief �������擾�֐�
	//! @details
	//! @param void �Ȃ� 
	//! @retval int ������
	//----------------------------------------
	int getDivisionNum();

	//----------------------------------------
	//! @brief �������ݒ�֐�
	//! @details
	//! @param division_num        ������
	//! @param division_num_width  ���̕�����
	//! @param division_num_height �c�̕�����
	//! @retval void �Ȃ�
	//----------------------------------------
	void setDivisionNum(int division_num, int division_num_width,
						int division_num_height);

    //----------------------------------------
    //! @brief UV�擾�֐�
    //! @details
    //! @param index �C���f�b�N�X 
    //! @retval UV* UV
    //----------------------------------------
	UV* getpUV(int index);

	//----------------------------------------
	//! @brief �e�N�X�`���n���h���擾�֐�
	//! @details
	//! @param void �Ȃ� 
	//! @retval LPDIRECT3DTEXTURE9 �e�N�X�`���n���h��
	//----------------------------------------
	LPDIRECT3DTEXTURE9 getpHandler();

	//----------------------------------------
	//! @brief �A�j���[�V�������ݒ�֐�
	//! @details
	//! @param animation_count �A�j���[�V�����J�E���^
	//! @param animation_speed �A�j���[�V�������x
	//! @retval int �A�j���[�V������
	//----------------------------------------
	int getAnimationNum(int animation_count, int animation_speed);


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param *file_path    �t�@�C���p�X
	//! @param *map_key_name �}�b�v�p�L�[��
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init(std::string* file_path, const std::string* map_key_name);

	//----------------------------------------
	//! @brief ����֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Release();

	//----------------------------------------
	//! @brief ��������֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void ForcedRelease();

	//----------------------------------------
	//! @brief �Q�ƃJ�E���^�ǉ��֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void AddReferenceCounter();

private:
	//----------------------------------------
	//! @brief �e�N�X�`���n���h�������֐�
	//! @details
	//! @param *file_path �t�@�C���p�X
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateTextureHandler(std::string* file_path);

	//----------------------------------------
	//! @brief �e�N�X�`����񐶐��֐�
	//! @details
	//! @param *file_path �t�@�C���p�X
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateTextureInformation(std::string* file_path);
};



#endif