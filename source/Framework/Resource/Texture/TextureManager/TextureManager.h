//================================================================================
//!	@file	 TextureManager.h
//!	@brief	 �e�N�X�`���}�l�[�W��Class
//! @details Singleton
//!	@author  Kai Araki									@date 2019/1/11
//================================================================================
#ifndef	_TEXTURE_MANAGER_H_
#define _TEXTURE_MANAGER_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "../TextureObject.h"



//************************************************************														   
//! @brief   �e�N�X�`���}�l�[�W��Class(Singleton)
//!
//! @details �e�N�X�`���̃}�l�[�W��Class(Singleton)
//************************************************************
class TextureManager
{
//====================
// �萔
//====================
private:
	static const std::string DEFAULT_PATH;		//!< ����p�X


//====================
// static�ϐ�
//====================
private:
	static TextureManager* instance_;	//!< �C���X�^���X


//====================
// static�v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �C���X�^���X�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval TextureManager* �C���X�^���X
	//----------------------------------------
	static TextureManager* getpInstance();


//====================
// static�֐�
//====================
public:
	//----------------------------------------
	//! @brief �C���X�^���X����֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	static void ReleaseInstance();


//====================
// �ϐ�
//====================
private:
	std::unordered_map<std::string, TextureObject*> object_map_;	//!< �I�u�W�F�N�g�}�b�v


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �I�u�W�F�N�g�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval TextureObject* �I�u�W�F�N�g
	//----------------------------------------
	TextureObject* getpObject(const std::string* key_name, 
							  const std::string* file_path = nullptr);


//====================
// �֐�
//====================
private:
	//----------------------------------------
	//! @brief �R���X�g���N�^
	//! @param void �Ȃ�
	//----------------------------------------
	TextureManager();

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
	//! @brief �}�b�v�������֐�
	//! @details
	//! @param *key_name �L�[��
	//! @param *file_path �t�@�C���p�X
	//! @retval void �Ȃ�
	//----------------------------------------
	void ReleaseFromTheMap(std::string* key_name);

private:
	//----------------------------------------
	//! @brief �t���p�X�����֐�
	//! @details
	//! @param *key_name  �L�[��
	//! @param *file_path �t�@�C���p�X
	//! @retval std::string �t���p�X
	//----------------------------------------
	std::string CreateFilePath(const std::string* key_name, 
							   const std::string* file_path);


//====================
// �����ς݊֐�
//====================
private:
	TextureManager(const TextureManager& class_name) = delete;
	TextureManager& operator = (const TextureManager& class_name) = delete;
};



#endif