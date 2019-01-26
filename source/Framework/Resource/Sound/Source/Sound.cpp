//================================================================================
//
//    �T�E���h�����w�b�_
//    Author : Araki Kai                                �쐬�� : 2017/07/24
//
//================================================================================



//**********************************************************************
//
// �C���N���[�h��
//
//**********************************************************************

#include < XAudio2.h >

#include "Sound.h"



//**********************************************************************
//
// �\���̐錾
//
//**********************************************************************

// �p�����[�^
typedef struct
{
	char *pFilename;	// �t�@�C����
	int nCntLoop;		// ���[�v�J�E���g
} SOUNDPARAM;



//**********************************************************************
//
// �v���g�^�C�v�錾
//
//**********************************************************************

//================================================================================
//
// [ �`�����N�̃`�F�b�N ]
//
// � ���� �
//
// �hFile              : �t�@�C���n���h��
// �format             : �t�@�C���t�H�[�}�b�g
// �pChunkSize         : �`�����N�T�C�Y
// �pChunkDataPosition : �`�����N�f�[�^�̏ꏊ
//
// � �߂�l �
//
// �HRESULT�^ : �G���[�`�F�b�N�p
//
//�y �ڍ� �z
//
// ��`�����N�f�[�^���`�F�b�N����
//
//================================================================================

HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);



//================================================================================
//
// [ �`�����N�̓ǂݍ��� ]
//
// � ���� �
//
// �hFile          : �t�@�C���n���h��
// �pBuffer        : �ǂݍ��ݐ�o�b�t�@
// �dwBuffersize   : �ǂݍ��ݐ�o�b�t�@�̃T�C�Y
// �dwBufferoffset : �ǂݍ��ݐ�o�b�t�@�̃I�t�Z�b�g
//
// � �߂�l �
//
// �HRESULT�^ : �G���[�`�F�b�N�p
//
//�y �ڍ� �z
//
// ��`�����N�f�[�^��ǂݍ���
//
//================================================================================

HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);



//**********************************************************************
//
// �O���[�o���ϐ�
//
//**********************************************************************

IXAudio2 *g_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
IXAudio2MasteringVoice *g_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X
IXAudio2SourceVoice *g_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X
BYTE *g_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^
DWORD g_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y

// �e���f�ނ̃p�����[�^
SOUNDPARAM g_aParam[SOUND_LABEL_MAX] =
{
	{"resource/Music/BGM/Title.wav",  -1},
	{"resource/Music/BGM/Stage1.wav", -1},	
	{"resource/Music/BGM/Stage2.wav", -1},	
	{"resource/Music/BGM/Stage3.wav", -1},
	{"resource/Music/BGM/Clear.wav",  -1},


	{"resource/music/SE/ketei.wav",           0 },
	{"resource/music/SE/cursor.wav",           0 },
	{"resource/music/SE/open.wav",           0 },
	{"resource/music/SE/toziru.wav",           0 },
	{"resource/music/SE/tobira_on.wav",           0 },
	{"resource/music/SE/jump.wav",           0 },
	{"resource/music/SE/damage.wav",           0 },
	{"resource/music/SE/deth.wav",           0 },
	{"resource/music/SE/charge.wav",           0 },
	{"resource/music/SE/Shot.wav",           0 },
	{"resource/music/SE/kotei.wav",           0 },
	{"resource/music/SE/Release.wav",           0 },
	{"resource/music/SE/Clear.wav",           0 },
	{"resource/music/SE/Switch.wav",           0 },
	{"resource/music/SE/break.wav",           0 },
	{"resource/music/SE/Recovery.wav",           0 },
	{"resource/music/SE/hansya.wav",           0 },
	{"resource/music/SE/CheckPoint.wav",           0 },
	{"resource/music/SE/Dog_damage.wav",           0 },
	{"resource/music/SE/Dog_yarare.wav",           0 },
	{"resource/music/SE/Monkey_damage.wav",           0 },
	{"resource/music/SE/Monkey_nage.wav",           0 },
	{"resource/music/SE/Monkey_yarare.wav",           0 },
};



//================================================================================
//
// [ �T�E���h�������֐� ]
//
// � ���� �
//
// �hWnd : �E�B���h�E�n���h��
//
// � �߂�l �
//
// �HRESULT�^ : �G���[�`�F�b�N�p
//
//�y �ڍ� �z
//
// ��T�E���h���g�p���邽�߂̏�����
//
//================================================================================

HRESULT InitSound(HWND hWnd)
{
	HRESULT hr;

	// COM���C�u�����̏�����
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio2�I�u�W�F�N�g�̍쐬
	hr = XAudio2Create(&g_pXAudio2, 0);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "XAudio2�I�u�W�F�N�g�̍쐬�Ɏ��s�I", "�x���I", MB_ICONWARNING);

		// COM���C�u�����̏I������
		CoUninitialize();

		return E_FAIL;
	}
	
	// �}�X�^�[�{�C�X�̐���
	hr = g_pXAudio2->CreateMasteringVoice(&g_pMasteringVoice);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "�}�X�^�[�{�C�X�̐����Ɏ��s�I", "�x���I", MB_ICONWARNING);

		if(g_pXAudio2)
		{
			// XAudio2�I�u�W�F�N�g�̊J��
			g_pXAudio2->Release();
			g_pXAudio2 = NULL;
		}

		// COM���C�u�����̏I������
		CoUninitialize();

		return E_FAIL;
	}

	// �T�E���h�f�[�^�̏�����
	for(int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		HANDLE hFile;
		DWORD dwChunkSize = 0;
		DWORD dwChunkPosition = 0;
		DWORD dwFiletype;
		WAVEFORMATEXTENSIBLE wfx;
		XAUDIO2_BUFFER buffer;

		// �o�b�t�@�̃N���A
		memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

		// �T�E���h�f�[�^�t�@�C���̐���
		hFile = CreateFile(g_aParam[nCntSound].pFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		if(hFile == INVALID_HANDLE_VALUE)
		{
			MessageBox(hWnd, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}
		if(SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		{// �t�@�C���|�C���^��擪�Ɉړ�
			MessageBox(hWnd, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}
	
		// WAVE�t�@�C���̃`�F�b�N
		hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
		hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
		if(dwFiletype != 'EVAW')
		{
			MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(3)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
	
		// �t�H�[�}�b�g�`�F�b�N
		hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
		hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		// �I�[�f�B�I�f�[�^�ǂݍ���
		hr = CheckChunk(hFile, 'atad', &g_aSizeAudio[nCntSound], &dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
		g_apDataAudio[nCntSound] = (BYTE*)malloc(g_aSizeAudio[nCntSound]);
		hr = ReadChunkData(hFile, g_apDataAudio[nCntSound], g_aSizeAudio[nCntSound], dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
	
		// �\�[�X�{�C�X�̐���
		hr = g_pXAudio2->CreateSourceVoice(&g_apSourceVoice[nCntSound], &(wfx.Format));
		if(FAILED(hr))
		{
			MessageBox(hWnd, "�\�[�X�{�C�X�̐����Ɏ��s�I", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		// �o�b�t�@�̒l�ݒ�
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
		buffer.AudioBytes = g_aSizeAudio[nCntSound];
		buffer.pAudioData = g_apDataAudio[nCntSound];
		buffer.Flags      = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount  = g_aParam[nCntSound].nCntLoop;

		// �I�[�f�B�I�o�b�t�@�̓o�^
		g_apSourceVoice[nCntSound]->SubmitSourceBuffer(&buffer);
	}

	return S_OK;
}



//================================================================================
//
// [ �T�E���h�I�������֐� ]
//
// � ���� �
//
// ��Ȃ�
//
// � �߂�l �
//
// ��Ȃ�
//
//�y �ڍ� �z
//
// ��T�E���h�̎g�p���I������Ƃ��̏���
//
//================================================================================

void UninitSound(void)
{
	// �ꎞ��~
	for(int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if(g_apSourceVoice[nCntSound])
		{
			// �ꎞ��~
			g_apSourceVoice[nCntSound]->Stop(0);
	
			// �\�[�X�{�C�X�̔j��
			g_apSourceVoice[nCntSound]->DestroyVoice();
			g_apSourceVoice[nCntSound] = NULL;
	
			// �I�[�f�B�I�f�[�^�̊J��
			free(g_apDataAudio[nCntSound]);
			g_apDataAudio[nCntSound] = NULL;
		}
	}
	
	// �}�X�^�[�{�C�X�̔j��
	g_pMasteringVoice->DestroyVoice();
	g_pMasteringVoice = NULL;
	
	if(g_pXAudio2)
	{
		// XAudio2�I�u�W�F�N�g�̊J��
		g_pXAudio2->Release();
		g_pXAudio2 = NULL;
	}
	
	// COM���C�u�����̏I������
	CoUninitialize();
}



//================================================================================
//
// [ �Z�O�����g�Đ�or��~�֐� ]
//
// � ���� �
//
// �label : �w�b�_�Œ�`���ꂽ�T�E���h�t�@�C���̔ԍ�
//
// � �߂�l �
//
// �HRESULT�^ : �G���[�`�F�b�N�p
//
//�y �ڍ� �z
//
// ��Z�O�����g�̍Đ�������
// ��Đ����̏ꍇ�͒�~����
//
//================================================================================

HRESULT PlaySound(SOUND_LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	// �o�b�t�@�̒l�ݒ�
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = g_aSizeAudio[label];
	buffer.pAudioData = g_apDataAudio[label];
	buffer.Flags      = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount  = g_aParam[label].nCntLoop;

	// ��Ԏ擾
	g_apSourceVoice[label]->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		g_apSourceVoice[label]->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		g_apSourceVoice[label]->FlushSourceBuffers();
	}

	// �I�[�f�B�I�o�b�t�@�̓o�^
	g_apSourceVoice[label]->SubmitSourceBuffer(&buffer);

	// �Đ�
	g_apSourceVoice[label]->Start(0);

	return S_OK;
}



//================================================================================
//
// [ �Z�O�����g��~�֐�( �ʎw�� ) ]
//
// � ���� �
//
// �label : �w�b�_�Œ�`���ꂽ�T�E���h�t�@�C���̔ԍ�
//
// � �߂�l �
//
// ��Ȃ�
//
//�y �ڍ� �z
//
// ��Z�O�����g���ʂɒ�~����
//
//================================================================================

void StopSound(SOUND_LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;

	// ��Ԏ擾
	g_apSourceVoice[label]->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		g_apSourceVoice[label]->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		g_apSourceVoice[label]->FlushSourceBuffers();
	}
}



//================================================================================
//
// [ �Z�O�����g��~�֐�( �S�� ) ]
//
// � ���� �
//
// ��Ȃ�
//
// � �߂�l �
//
// ��Ȃ�
//
//�y �ڍ� �z
//
// ��S�ẴZ�O�����g���~����
//
//================================================================================

void StopSound(void)
{
	// �ꎞ��~
	for(int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if(g_apSourceVoice[nCntSound])
		{
			// �ꎞ��~
			g_apSourceVoice[nCntSound]->Stop(0);
		}
	}
}



//================================================================================
//
// [ �`�����N�̃`�F�b�N ]
//
// � ���� �
//
// �hFile              : �t�@�C���n���h��
// �format             : �t�@�C���t�H�[�}�b�g
// �pChunkSize         : �`�����N�T�C�Y
// �pChunkDataPosition : �`�����N�f�[�^�̏ꏊ
//
// � �߂�l �
//
// �HRESULT�^ : �G���[�`�F�b�N�p
//
//�y �ڍ� �z
//
// ��`�����N�f�[�^���`�F�b�N����
//
//================================================================================

HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;
	
	if(SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^��擪�Ɉړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	while(hr == S_OK)
	{
		if(ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if(ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�f�[�^�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch(dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize  = dwChunkDataSize;
			dwChunkDataSize = 4;
			if(ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// �t�@�C���^�C�v�̓ǂݍ���
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if(SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// �t�@�C���|�C���^���`�����N�f�[�^���ړ�
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += sizeof(DWORD) * 2;
		if(dwChunkType == format)
		{
			*pChunkSize         = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if(dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}
	
	return S_OK;
}



//================================================================================
//
// [ �`�����N�̓ǂݍ��� ]
//
// � ���� �
//
// �hFile          : �t�@�C���n���h��
// �pBuffer        : �ǂݍ��ݐ�o�b�t�@
// �dwBuffersize   : �ǂݍ��ݐ�o�b�t�@�̃T�C�Y
// �dwBufferoffset : �ǂݍ��ݐ�o�b�t�@�̃I�t�Z�b�g
//
// � �߂�l �
//
// �HRESULT�^ : �G���[�`�F�b�N�p
//
//�y �ڍ� �z
//
// ��`�����N�f�[�^��ǂݍ���
//
//================================================================================

HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;
	
	if(SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^���w��ʒu�܂ňړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if(ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// �f�[�^�̓ǂݍ���
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	return S_OK;
}

