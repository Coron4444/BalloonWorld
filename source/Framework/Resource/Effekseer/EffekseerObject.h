//================================================================================
//!	@file	 EffekseerObject.h
//!	@brief	 �G�t�F�N�V�A�I�u�W�F�N�gClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/01
//================================================================================
#ifndef	_EFFEKSEER_OBJECT_H_
#define _EFFEKSEER_OBJECT_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <string>
#include <vector>
#pragma warning(push)
#pragma warning(disable: 4100)
#pragma warning(disable: 4099)
#include "Effekseer.h"
#include "EffekseerRendererDX9.h"
#pragma warning(pop)

#include <Tool/Transform.h>



//************************************************************														   
//! @brief   �G�t�F�N�V�A�I�u�W�F�N�gClass
//!
//! @details �G�t�F�N�V�A�̃I�u�W�F�N�gClass
//************************************************************
class EffekseerObject
{
//====================
// �萔
//====================
private:
	static const int MAX_SPRITE_NUM;	//!< �ő�X�v���C�g��


//====================
// �ϐ�
//====================
private:
	EffekseerRendererDX9::Renderer* effekseer_renderer_ = nullptr;	//!< �����_���[
	Effekseer::Manager*	effekseer_manager_ = nullptr;				//!< �}�l�[�W��
	Effekseer::Effect* effekseer_effect_ = nullptr;					//!< �G�t�F�N�g
	Effekseer::Handle effekseer_handle_;							//!< �n���h��
	Effekseer::Matrix43	world_matrix_;								//!< �s��
	bool is_disposable_ = false;	//!< �g���̂ăt���O
	bool is_playing_ = false;		//!< �Đ��t���O
	bool is_pause_ = false;			//!< ��~�t���O
	bool is_repeat_ = false;		//!< ���s�[�g�t���O
	Transform transform_;			//!< �ό`
	std::string map_key_name_;		//!< �}�b�v�p�L�[��
	int reference_counter_ = 0;		//!< �Q�ƃJ�E���^


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �g���̂ăt���O�ݒ�֐�
	//! @details
	//! @param value �g���̂ăt���O�̒l 
	//! @retval void �Ȃ�
	//----------------------------------------
	void setDisposable(bool value);

	//----------------------------------------
	//! @brief �Đ����t���O�擾�֐�
	//! @details
	//! @param void �Ȃ� 
	//! @retval bool �Đ����̗L��
	//----------------------------------------
	bool getpIsPlaying();

	//----------------------------------------
	//! @brief ���s�[�g�t���O�ݒ�֐�
	//! @details
	//! @param value ���s�[�g�t���O�̒l
	//! @retval void �Ȃ�
	//----------------------------------------
	void setIsRepeat(bool value);

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
	//! @brief �Đ��֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Play();

	//----------------------------------------
	//! @brief ��~�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Stop();

	//----------------------------------------
	//! @brief �ꎞ��~�֐�
	//! @details
	//! @param is_pause �ꎞ��~�t���O
	//! @retval void �Ȃ�
	//----------------------------------------
	void Pause(bool is_pause);

	//----------------------------------------
	//! @brief ���x�ύX�֐�
	//! @details
	//! @param velocity ���x
	//! @retval void �Ȃ�
	//----------------------------------------
	void ChangeVelocity(float velocity);

	//----------------------------------------
	//! @brief �F�ύX�֐�
	//! @details
	//! @param r ��
	//! @param g ��
	//! @param b ��
	//! @param a ���ߓx
	//! @retval void �Ȃ�
	//----------------------------------------
	void ChangeColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

	//----------------------------------------
	//! @brief �r���[�s��ύX�֐�
	//! @details
	//! @param velocity ���x
	//! @retval void �Ȃ�
	//----------------------------------------
	void ChangeViewMatrix(Effekseer::Matrix44* view_matrix);

	//----------------------------------------
	//! @brief �v���W�F�N�V�����s��ύX�֐�
	//! @details
	//! @param velocity ���x
	//! @retval void �Ȃ�
	//----------------------------------------
	void ChangeProjectionMatrix(Effekseer::Matrix44* projection_matrix);
	
private:
	//----------------------------------------
	//! @brief �����_���[&�}�l�[�W�������֐�
	//! @details
	//! @param *file_path �t�@�C���p�X
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateRendererAndManager();

	//----------------------------------------
	//! @brief �G�t�F�N�g�����֐�
	//! @details
	//! @param *file_path �t�@�C���p�X
	//! @retval void �Ȃ�
	//----------------------------------------
	void CreateEffect(std::string* file_path);

	//----------------------------------------
	//! @brief ���[���h�s��ύX�֐�
	//! @details
	//! @param *file_path �t�@�C���p�X
	//! @retval void �Ȃ�
	//----------------------------------------
	void ChangeWorldMatrix(MATRIX* world_matrix);
};



#endif