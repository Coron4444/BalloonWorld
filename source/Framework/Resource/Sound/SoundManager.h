//================================================================================
//!	@file	 SoundManager.h
//!	@brief	 �T�E���h�}�l�[�W��Class
//! @details Singleton
//!	@author  Kai Araki									@date 2017/07/24
//================================================================================
#ifndef _SOUND_H_
#define _SOUND_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <Windows.h>
#include <XAudio2.h>



//************************************************************														   
//! @brief   �T�E���h�}�l�[�W��Class(Singleton)
//!
//! @details �T�E���h�̃}�l�[�W��Class(Singleton)
//************************************************************
class SoundManager
{
//====================
// �\���̒�`
//====================
public:
	//****************************************											   
	//! @brief   �p�����[�^�[Class
	//!
	//! @details �T�E���h�̃p�����[�^�[Class
	//****************************************
	struct Parameter
	{
	//====================
	// �ϐ�
	//====================
	public:
		char* file_name_;	//!< �t�@�C����
		int loop_count_;	//!< ���[�v�J�E���g
	};


//====================
// �񋓌^��`
//====================
public:
	enum class Type
	{
		NONE = -1,
		BGM_TITLE,
		BGM_TUTORIAL,
		BGM_STAGE,
		BGM_RESULT,
		SE_KETEI,
		SE_CURSOR,
		SE_SCORE_UP,
		SE_DAMAGE,
		SE_OPEN,
		SE_CLOSE,
		SE_CLEAR,
		SE_PURGE,
		MAX
	};


//====================
// �萔
//====================
private:
	static const Parameter PARAMETER_ARRAY[(int)Type::MAX];		//!< �p�����[�^�[�z��


//====================
// static�ϐ�
//====================
private:
	static SoundManager* instance_;		//!< �C���X�^���X


//====================
// static�v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �C���X�^���X�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval SoundManager* �C���X�^���X
	//----------------------------------------
	static SoundManager* getpInstance();


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
	IXAudio2* x_audio_ = nullptr;									//!< XAudio2�I�u�W�F�N�g�C���^�[�t�F�C�X
	IXAudio2MasteringVoice* mastering_voice_ = nullptr;				//!< �}�X�^�[�{�C�X
	IXAudio2SourceVoice* source_voice_[(int)Type::MAX] = {nullptr};	//!< �\�[�X�{�C�X
	BYTE* data_audio_[(int)Type::MAX] = {nullptr};					//!< �I�[�f�B�I�f�[�^
	DWORD size_audio_[(int)Type::MAX] = {0};						//!< �I�[�f�B�I�f�[�^�T�C�Y


//====================
// �֐�
//====================
private:
	//----------------------------------------
	//! @brief �R���X�g���N�^
	//! @param void �Ȃ�
	//----------------------------------------
	SoundManager();

public:
	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param hWnd �E�B���h�E�n���h��
	//! @retval HRESULT �G���[�`�F�b�N�p
	//----------------------------------------
	HRESULT Init(HWND hWnd);

   //----------------------------------------
   //! @brief �I���֐�
   //! @details
   //! @param void �Ȃ�
   //! @retval void �Ȃ�
   //----------------------------------------
	void Uninit();

	//----------------------------------------
	//! @brief �Đ�or��~�֐�
	//! @details
	//! @param type �T�E���h�^�C�v
	//! @retval HRESULT �G���[�`�F�b�N�p
	//----------------------------------------
	HRESULT PlayOrStop(Type type);

	//----------------------------------------
	//! @brief ��~�֐�
	//! @details
	//! @param type �T�E���h�^�C�v
	//! @retval void �Ȃ�
	//----------------------------------------
	void Stop(Type type);

	//----------------------------------------
	//! @brief ��~�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void AllStop();

private:
	//----------------------------------------
	//! @brief �`�����N�`�F�b�N�֐�
	//! @details
	//! @param file_handle         �t�@�C���n���h��
	//! @param format              �t�H�[�}�b�g
	//! @param chunk_size          �`�����N�T�C�Y
	//! @param chunk_data_position �`�����N�f�[�^�̏ꏊ
	//! @retval HRESULT �G���[�`�F�b�N�p
	//----------------------------------------
	HRESULT CheckChunk(HANDLE file_handle, DWORD format, DWORD* chunk_size,
					   DWORD* chunk_data_position);

	//----------------------------------------
	//! @brief �`�����N�ǂݍ��݊֐�
	//! @details
	//! @param file_handle   �t�@�C���n���h��
	//! @param buffer        �ǂݍ��ݐ�o�b�t�@
	//! @param buffer_size   �ǂݍ��ݐ�o�b�t�@�̃T�C�Y
	//! @param buffer_offset �ǂݍ��ݐ�o�b�t�@�̃I�t�Z�b�g
	//! @retval HRESULT �G���[�`�F�b�N�p
	//----------------------------------------
	HRESULT ReadChunk(HANDLE file_handle, void* buffer, DWORD buffer_size,
					  DWORD buffer_offset);


//====================
// �����ς݊֐�
//====================
private:
	SoundManager(const SoundManager& class_name) = delete;
	SoundManager& operator = (const SoundManager& class_name) = delete;
};



#endif
