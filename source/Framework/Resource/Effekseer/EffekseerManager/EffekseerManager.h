//================================================================================
//!	@file	 EffekseerManager.h
//!	@brief	 �G�t�F�N�V�A�}�l�[�W��Class
//! @details Singleton
//!	@author  Kai Araki									@date 2019/1/11
//================================================================================
#ifndef	_EFFEKSEER_MANAGER_H_
#define _EFFEKSEER_MANAGER_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <string>
#include <list>
#include <unordered_map>

#include "../EffekseerObject.h"



//************************************************************														   
//! @brief   �G�t�F�N�V�A�}�l�[�W��Class(Singleton)
//!
//! @details �G�t�F�N�V�A�̃}�l�[�W��Class(Singleton)
//************************************************************
class EffekseerManager
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
	static EffekseerManager* instance_;	//!< �C���X�^���X


//====================
// static�v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �C���X�^���X�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval EffekseerManager* �C���X�^���X
	//----------------------------------------
	static EffekseerManager* getpInstance();


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
	std::unordered_map<std::string, EffekseerObject*> object_map_;	//!< �I�u�W�F�N�g�}�b�v
	std::list<EffekseerObject*> disposable_object_;					//!< �g���̂ăI�u�W�F�N�g���X�g
	Effekseer::Matrix44 view_matrix_;								//!< �r���[�s��
	Effekseer::Matrix44 projection_matrix_;							//!< �v���W�F�N�V�����s��


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �I�u�W�F�N�g�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval TextureObject* �I�u�W�F�N�g�擾
	//----------------------------------------
	EffekseerObject* getpObject(const std::string* key_name,
								const std::string* file_path = nullptr);

	//----------------------------------------
	//! @brief �g���̂ăI�u�W�F�N�g�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval TextureObject* �I�u�W�F�N�g�擾
	//----------------------------------------
	EffekseerObject* getpDisposableObject(const std::string* key_name,
										  const std::string* file_path = nullptr);


//====================
// �֐�
//====================
private:
	//----------------------------------------
	//! @brief �R���X�g���N�^
	//! @param void �Ȃ�
	//----------------------------------------
	EffekseerManager();


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
	//! @brief �X�V�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Update();

	//----------------------------------------
	//! @brief �`��֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Draw();

	//----------------------------------------
	//! @brief �}�b�v�������֐�
	//! @details
	//! @param *key_name  �L�[��
	//! @param *file_path �t�@�C���p�X
	//! @retval void �Ȃ�
	//----------------------------------------
	void ReleaseFromTheMap(std::string* key_name);

	//----------------------------------------
	//! @brief �r���[�s�񐶐��֐�
	//! @details
	//! @param camera_position �J�������W
	//! @param look_at_point   �����_
	//! @param camera_up       �J�����̏�x�N�g��
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateViewMatrix(Vec3 camera_position, Vec3 look_at_point, Vec3 camera_up);

	//----------------------------------------
	//! @brief �v���W�F�N�V�����s�񐶐��֐�
	//! @details
	//! @param angle_of_view_ ��p
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateProjectionMatrix(int angle_of_view_);

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
};



#endif