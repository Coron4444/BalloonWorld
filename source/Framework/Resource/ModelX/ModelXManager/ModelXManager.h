//================================================================================
//!	@file	 ModelXManager.h
//!	@brief	 X���f���}�l�[�W��Class
//! @details Singleton
//!	@author  Kai Araki									@date 2019/1/11
//================================================================================
#ifndef	_MODEL_X_MANAGER_H_
#define _MODEL_X_MANAGER_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "../ModelXObject.h"



//************************************************************														   
//! @brief   X���f���}�l�[�W��Class(Singleton)
//!
//! @details X���f���̃}�l�[�W��Class(Singleton)
//************************************************************
class ModelXManager
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
	static ModelXManager* instance_;	//!< �C���X�^���X


//====================
// static�v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �C���X�^���X�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval ModelXManager* �C���X�^���X
	//----------------------------------------
	static ModelXManager* getpInstance();


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
	std::unordered_map<std::string, ModelXObject*> object_map_;		//!< �I�u�W�F�N�g�}�b�v


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �I�u�W�F�N�g�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval ModelXObject* �I�u�W�F�N�g
	//----------------------------------------
	ModelXObject* getpObject(const std::string* key_name,
							 const std::string* file_path = nullptr);


//====================
// �֐�
//====================
private:
	//----------------------------------------
	//! @brief �R���X�g���N�^
	//! @param void �Ȃ�
	//----------------------------------------
	ModelXManager();

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
	ModelXManager(const ModelXManager& class_name) = delete;
	ModelXManager& operator = (const ModelXManager& class_name) = delete;
};



#endif