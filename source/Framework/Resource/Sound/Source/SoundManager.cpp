//================================================================================
//!	@file	 SoundManager.cpp
//!	@brief	 �T�E���h�}�l�[�W��Class
//! @details Singleton
//!	@author  Kai Araki									@date 2017/07/24
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../SoundManager.h"

#include <Tool/SafeRelease.h>



//****************************************
// �萔��`
//****************************************
const SoundManager::Parameter SoundManager::PARAMETER_ARRAY[(int)SoundManager::Type::MAX] =
{
	{"resource/Music/BGM/Title.wav", -1},
	{"resource/Music/BGM/Tutorial.wav", -1},
	{"resource/Music/BGM/Stage.wav", -1},
	{"resource/Music/BGM/Result.wav", -1},
	{"resource/Music/SE/01_Ketei.wav", 0},
	{"resource/Music/SE/02_Cursor.wav", 0},
	{"resource/Music/SE/03_ScoreUp.wav", 0},
	{"resource/Music/SE/04_Damage.wav", 0},
	{"resource/Music/SE/05_Open.wav", 0},
	{"resource/Music/SE/06_Close.wav", 0},
	{"resource/Music/SE/07_Clear.wav", 0},
	{"resource/Music/SE/08_Purge.wav", 0},
};



//****************************************
// static�ϐ���`
//****************************************
SoundManager* SoundManager::instance_ = nullptr;



//****************************************
// static�v���p�e�B��`
//****************************************
SoundManager* SoundManager::getpInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new SoundManager();
	}
	return instance_;
}



//****************************************
// static�֐���`
//****************************************
void SoundManager::ReleaseInstance()
{
	SafeRelease::Normal(&instance_);
}



//****************************************
// �֐���`
//****************************************
SoundManager::SoundManager()
{
}



HRESULT SoundManager::Init(HWND hWnd)
{
	HRESULT hr;

	// COM���C�u�����̏�����
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio2�I�u�W�F�N�g�̍쐬
	hr = XAudio2Create(&x_audio_, 0);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "XAudio2�I�u�W�F�N�g�̍쐬�Ɏ��s�I", "�x���I", MB_ICONWARNING);

		// COM���C�u�����̏I������
		CoUninitialize();

		return E_FAIL;
	}

	// �}�X�^�[�{�C�X�̐���
	hr = x_audio_->CreateMasteringVoice(&mastering_voice_);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "�}�X�^�[�{�C�X�̐����Ɏ��s�I", "�x���I", MB_ICONWARNING);

		if (x_audio_)
		{
			// XAudio2�I�u�W�F�N�g�̊J��
			x_audio_->Release();
			x_audio_ = NULL;
		}

		// COM���C�u�����̏I������
		CoUninitialize();

		return E_FAIL;
	}

	// �T�E���h�f�[�^�̏�����
	for (int nCntSound = 0; nCntSound < (int)SoundManager::Type::MAX; nCntSound++)
	{
		HANDLE file_handle;
		DWORD dwChunkSize = 0;
		DWORD dwChunkPosition = 0;
		DWORD dwFiletype;
		WAVEFORMATEXTENSIBLE wfx;
		XAUDIO2_BUFFER buffer;

		// �o�b�t�@�̃N���A
		memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

		// �T�E���h�f�[�^�t�@�C���̐���
		file_handle = CreateFile(PARAMETER_ARRAY[nCntSound].file_name_, GENERIC_READ,
								 FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		if (file_handle == INVALID_HANDLE_VALUE)
		{
			MessageBox(hWnd, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}
		if (SetFilePointer(file_handle, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		{// �t�@�C���|�C���^��擪�Ɉړ�
			MessageBox(hWnd, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}

		// WAVE�t�@�C���̃`�F�b�N
		hr = CheckChunk(file_handle, 'FFIR', &dwChunkSize, &dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
		hr = ReadChunk(file_handle, &dwFiletype, sizeof(DWORD), dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
		if (dwFiletype != 'EVAW')
		{
			MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(3)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		// �t�H�[�}�b�g�`�F�b�N
		hr = CheckChunk(file_handle, ' tmf', &dwChunkSize, &dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
		hr = ReadChunk(file_handle, &wfx, dwChunkSize, dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		// �I�[�f�B�I�f�[�^�ǂݍ���
		hr = CheckChunk(file_handle, 'atad', &size_audio_[nCntSound], &dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
		data_audio_[nCntSound] = (BYTE*)malloc(size_audio_[nCntSound]);
		hr = ReadChunk(file_handle, data_audio_[nCntSound], size_audio_[nCntSound], dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		// �\�[�X�{�C�X�̐���
		hr = x_audio_->CreateSourceVoice(&source_voice_[nCntSound], &(wfx.Format));
		if (FAILED(hr))
		{
			MessageBox(hWnd, "�\�[�X�{�C�X�̐����Ɏ��s�I", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		// �o�b�t�@�̒l�ݒ�
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
		buffer.AudioBytes = size_audio_[nCntSound];
		buffer.pAudioData = data_audio_[nCntSound];
		buffer.Flags = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount = PARAMETER_ARRAY[nCntSound].loop_count_;

		// �I�[�f�B�I�o�b�t�@�̓o�^
		source_voice_[nCntSound]->SubmitSourceBuffer(&buffer);
	}

	return S_OK;
}



void SoundManager::Uninit()
{
	// �ꎞ��~
	for (int nCntSound = 0; nCntSound < (int)SoundManager::Type::MAX; nCntSound++)
	{
		if (source_voice_[nCntSound])
		{
			// �ꎞ��~
			source_voice_[nCntSound]->Stop(0);

			// �\�[�X�{�C�X�̔j��
			source_voice_[nCntSound]->DestroyVoice();
			source_voice_[nCntSound] = NULL;

			// �I�[�f�B�I�f�[�^�̊J��
			free(data_audio_[nCntSound]);
			data_audio_[nCntSound] = NULL;
		}
	}

	// �}�X�^�[�{�C�X�̔j��
	mastering_voice_->DestroyVoice();
	mastering_voice_ = NULL;

	if (x_audio_)
	{
		// XAudio2�I�u�W�F�N�g�̊J��
		x_audio_->Release();
		x_audio_ = NULL;
	}

	// COM���C�u�����̏I������
	CoUninitialize();
}



HRESULT SoundManager::PlayOrStop(Type type)
{
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	// �o�b�t�@�̒l�ݒ�
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = size_audio_[(int)type];
	buffer.pAudioData = data_audio_[(int)type];
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = PARAMETER_ARRAY[(int)type].loop_count_;

	// ��Ԏ擾
	source_voice_[(int)type]->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		source_voice_[(int)type]->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		source_voice_[(int)type]->FlushSourceBuffers();
	}

	// �I�[�f�B�I�o�b�t�@�̓o�^
	source_voice_[(int)type]->SubmitSourceBuffer(&buffer);

	// �Đ�
	source_voice_[(int)type]->Start(0);

	return S_OK;
}



void SoundManager::Stop(Type type)
{
	XAUDIO2_VOICE_STATE xa2state;

	// ��Ԏ擾
	source_voice_[(int)type]->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		source_voice_[(int)type]->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		source_voice_[(int)type]->FlushSourceBuffers();
	}
}



void SoundManager::AllStop()
{
	// �ꎞ��~
	for (int nCntSound = 0; nCntSound < (int)SoundManager::Type::MAX; nCntSound++)
	{
		if (source_voice_[nCntSound])
		{
			// �ꎞ��~
			source_voice_[nCntSound]->Stop(0);
		}
	}
}



HRESULT SoundManager::CheckChunk(HANDLE file_handle, DWORD format, DWORD* chunk_size,
								 DWORD* chunk_data_position)
{
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;

	if (SetFilePointer(file_handle, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^��擪�Ɉړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}

	while (hr == S_OK)
	{
		if (ReadFile(file_handle, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if (ReadFile(file_handle, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�f�[�^�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch (dwChunkType)
		{
			case 'FFIR':
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if (ReadFile(file_handle, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// �t�@�C���^�C�v�̓ǂݍ���
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

			default:
			if (SetFilePointer(file_handle, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// �t�@�C���|�C���^���`�����N�f�[�^���ړ�
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += sizeof(DWORD) * 2;
		if (dwChunkType == format)
		{
			*chunk_size = dwChunkDataSize;
			*chunk_data_position = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if (dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}

	return S_OK;
}



HRESULT SoundManager::ReadChunk(HANDLE file_handle, void* buffer, DWORD buffer_size,
								DWORD buffer_offset)
{
	DWORD dwRead;

	if (SetFilePointer(file_handle, buffer_offset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^���w��ʒu�܂ňړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if (ReadFile(file_handle, buffer, buffer_size, &dwRead, NULL) == 0)
	{// �f�[�^�̓ǂݍ���
		return HRESULT_FROM_WIN32(GetLastError());
	}

	return S_OK;
}

