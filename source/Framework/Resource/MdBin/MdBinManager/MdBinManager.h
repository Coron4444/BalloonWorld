//================================================================================
//!	@file	 MdBinManager.h
//!	@brief	 �o�C�i���[���f���}�l�[�W��Class
//! @details Singleton
//!	@author  Kai Araki									@date 2019/1/11
//================================================================================
#ifndef	_MD_BIN_MANAGER_H_
#define _MD_BIN_MANAGER_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <string>
#include <vector>
#include <unordered_map>

#include <MdBin/MdBinObject/MdBinObject.h>
#include <Texture/TextureManager/TextureManager.h>



//************************************************************														   
//! @brief   �o�C�i���[���f���}�l�[�W��Class
//!
//! @details �o�C�i���[���f���̃}�l�[�W��Class(Singleton)
//************************************************************
class MdBinManager
{
//====================
// �萔
//====================
private:
	static const std::string DEFAULT_PATH;					//!< ����p�X


//====================
// static�ϐ�
//====================
private:
	static MdBinManager* instance_;	//!< �C���X�^���X


//====================
// static�v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �C���X�^���X�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval MdBinManager* �C���X�^���X
	//----------------------------------------
	static MdBinManager* getpInstance();


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
	std::unordered_map<std::string, MdBinObject*> object_map_;		//!< �I�u�W�F�N�g�}�b�v
	

//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �I�u�W�F�N�g�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval MdBinObject* �I�u�W�F�N�g
	//----------------------------------------
	MdBinObject* getpObject(const std::string* key_name,
							const std::string* file_path = nullptr);


//====================
// �֐�
//====================
private:
	//----------------------------------------
	//! @brief �R���X�g���N�^
	//! @param void �Ȃ�
	//----------------------------------------
	MdBinManager();

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
	//! @param *key_name  �L�[��
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
	MdBinManager(const MdBinManager& class_name) = delete;
	MdBinManager& operator = (const MdBinManager& class_name) = delete;
};



#endif