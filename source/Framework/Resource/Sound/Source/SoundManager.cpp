//================================================================================
//!	@file	 SoundManager.cpp
//!	@brief	 サウンドマネージャClass
//! @details Singleton
//!	@author  Kai Araki									@date 2017/07/24
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../SoundManager.h"

#include <Tool/SafeRelease.h>



//****************************************
// 定数定義
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
// static変数定義
//****************************************
SoundManager* SoundManager::instance_ = nullptr;



//****************************************
// staticプロパティ定義
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
// static関数定義
//****************************************
void SoundManager::ReleaseInstance()
{
	SafeRelease::Normal(&instance_);
}



//****************************************
// 関数定義
//****************************************
SoundManager::SoundManager()
{
}



HRESULT SoundManager::Init(HWND hWnd)
{
	HRESULT hr;

	// COMライブラリの初期化
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio2オブジェクトの作成
	hr = XAudio2Create(&x_audio_, 0);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "XAudio2オブジェクトの作成に失敗！", "警告！", MB_ICONWARNING);

		// COMライブラリの終了処理
		CoUninitialize();

		return E_FAIL;
	}

	// マスターボイスの生成
	hr = x_audio_->CreateMasteringVoice(&mastering_voice_);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "マスターボイスの生成に失敗！", "警告！", MB_ICONWARNING);

		if (x_audio_)
		{
			// XAudio2オブジェクトの開放
			x_audio_->Release();
			x_audio_ = NULL;
		}

		// COMライブラリの終了処理
		CoUninitialize();

		return E_FAIL;
	}

	// サウンドデータの初期化
	for (int nCntSound = 0; nCntSound < (int)SoundManager::Type::MAX; nCntSound++)
	{
		HANDLE file_handle;
		DWORD dwChunkSize = 0;
		DWORD dwChunkPosition = 0;
		DWORD dwFiletype;
		WAVEFORMATEXTENSIBLE wfx;
		XAUDIO2_BUFFER buffer;

		// バッファのクリア
		memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

		// サウンドデータファイルの生成
		file_handle = CreateFile(PARAMETER_ARRAY[nCntSound].file_name_, GENERIC_READ,
								 FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		if (file_handle == INVALID_HANDLE_VALUE)
		{
			MessageBox(hWnd, "サウンドデータファイルの生成に失敗！(1)", "警告！", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}
		if (SetFilePointer(file_handle, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		{// ファイルポインタを先頭に移動
			MessageBox(hWnd, "サウンドデータファイルの生成に失敗！(2)", "警告！", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}

		// WAVEファイルのチェック
		hr = CheckChunk(file_handle, 'FFIR', &dwChunkSize, &dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "WAVEファイルのチェックに失敗！(1)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}
		hr = ReadChunk(file_handle, &dwFiletype, sizeof(DWORD), dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "WAVEファイルのチェックに失敗！(2)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}
		if (dwFiletype != 'EVAW')
		{
			MessageBox(hWnd, "WAVEファイルのチェックに失敗！(3)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}

		// フォーマットチェック
		hr = CheckChunk(file_handle, ' tmf', &dwChunkSize, &dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "フォーマットチェックに失敗！(1)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}
		hr = ReadChunk(file_handle, &wfx, dwChunkSize, dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "フォーマットチェックに失敗！(2)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}

		// オーディオデータ読み込み
		hr = CheckChunk(file_handle, 'atad', &size_audio_[nCntSound], &dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "オーディオデータ読み込みに失敗！(1)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}
		data_audio_[nCntSound] = (BYTE*)malloc(size_audio_[nCntSound]);
		hr = ReadChunk(file_handle, data_audio_[nCntSound], size_audio_[nCntSound], dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "オーディオデータ読み込みに失敗！(2)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}

		// ソースボイスの生成
		hr = x_audio_->CreateSourceVoice(&source_voice_[nCntSound], &(wfx.Format));
		if (FAILED(hr))
		{
			MessageBox(hWnd, "ソースボイスの生成に失敗！", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}

		// バッファの値設定
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
		buffer.AudioBytes = size_audio_[nCntSound];
		buffer.pAudioData = data_audio_[nCntSound];
		buffer.Flags = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount = PARAMETER_ARRAY[nCntSound].loop_count_;

		// オーディオバッファの登録
		source_voice_[nCntSound]->SubmitSourceBuffer(&buffer);
	}

	return S_OK;
}



void SoundManager::Uninit()
{
	// 一時停止
	for (int nCntSound = 0; nCntSound < (int)SoundManager::Type::MAX; nCntSound++)
	{
		if (source_voice_[nCntSound])
		{
			// 一時停止
			source_voice_[nCntSound]->Stop(0);

			// ソースボイスの破棄
			source_voice_[nCntSound]->DestroyVoice();
			source_voice_[nCntSound] = NULL;

			// オーディオデータの開放
			free(data_audio_[nCntSound]);
			data_audio_[nCntSound] = NULL;
		}
	}

	// マスターボイスの破棄
	mastering_voice_->DestroyVoice();
	mastering_voice_ = NULL;

	if (x_audio_)
	{
		// XAudio2オブジェクトの開放
		x_audio_->Release();
		x_audio_ = NULL;
	}

	// COMライブラリの終了処理
	CoUninitialize();
}



HRESULT SoundManager::PlayOrStop(Type type)
{
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	// バッファの値設定
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = size_audio_[(int)type];
	buffer.pAudioData = data_audio_[(int)type];
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = PARAMETER_ARRAY[(int)type].loop_count_;

	// 状態取得
	source_voice_[(int)type]->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// 再生中
		// 一時停止
		source_voice_[(int)type]->Stop(0);

		// オーディオバッファの削除
		source_voice_[(int)type]->FlushSourceBuffers();
	}

	// オーディオバッファの登録
	source_voice_[(int)type]->SubmitSourceBuffer(&buffer);

	// 再生
	source_voice_[(int)type]->Start(0);

	return S_OK;
}



void SoundManager::Stop(Type type)
{
	XAUDIO2_VOICE_STATE xa2state;

	// 状態取得
	source_voice_[(int)type]->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// 再生中
		// 一時停止
		source_voice_[(int)type]->Stop(0);

		// オーディオバッファの削除
		source_voice_[(int)type]->FlushSourceBuffers();
	}
}



void SoundManager::AllStop()
{
	// 一時停止
	for (int nCntSound = 0; nCntSound < (int)SoundManager::Type::MAX; nCntSound++)
	{
		if (source_voice_[nCntSound])
		{
			// 一時停止
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
	{// ファイルポインタを先頭に移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	while (hr == S_OK)
	{
		if (ReadFile(file_handle, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if (ReadFile(file_handle, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクデータの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch (dwChunkType)
		{
			case 'FFIR':
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if (ReadFile(file_handle, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// ファイルタイプの読み込み
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

			default:
			if (SetFilePointer(file_handle, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// ファイルポインタをチャンクデータ分移動
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
	{// ファイルポインタを指定位置まで移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if (ReadFile(file_handle, buffer, buffer_size, &dwRead, NULL) == 0)
	{// データの読み込み
		return HRESULT_FROM_WIN32(GetLastError());
	}

	return S_OK;
}

