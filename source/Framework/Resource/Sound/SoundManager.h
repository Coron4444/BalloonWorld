//================================================================================
//!	@file	 SoundManager.h
//!	@brief	 サウンドマネージャClass
//! @details Singleton
//!	@author  Kai Araki									@date 2017/07/24
//================================================================================
#ifndef _SOUND_H_
#define _SOUND_H_



//****************************************
// インクルード文
//****************************************
#include <Windows.h>
#include <XAudio2.h>



//************************************************************														   
//! @brief   サウンドマネージャClass(Singleton)
//!
//! @details サウンドのマネージャClass(Singleton)
//************************************************************
class SoundManager
{
//====================
// 構造体定義
//====================
public:
	//****************************************											   
	//! @brief   パラメーターClass
	//!
	//! @details サウンドのパラメーターClass
	//****************************************
	struct Parameter
	{
	//====================
	// 変数
	//====================
	public:
		char* file_name_;	//!< ファイル名
		int loop_count_;	//!< ループカウント
	};


//====================
// 列挙型定義
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
// 定数
//====================
private:
	static const Parameter PARAMETER_ARRAY[(int)Type::MAX];		//!< パラメーター配列


//====================
// static変数
//====================
private:
	static SoundManager* instance_;		//!< インスタンス


//====================
// staticプロパティ
//====================
public:
	//----------------------------------------
	//! @brief インスタンス取得関数
	//! @details
	//! @param void なし
	//! @retval SoundManager* インスタンス
	//----------------------------------------
	static SoundManager* getpInstance();


//====================
// static関数
//====================
public:
	//----------------------------------------
	//! @brief インスタンス解放関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	static void ReleaseInstance();


//====================
// 変数
//====================
private:
	IXAudio2* x_audio_ = nullptr;									//!< XAudio2オブジェクトインターフェイス
	IXAudio2MasteringVoice* mastering_voice_ = nullptr;				//!< マスターボイス
	IXAudio2SourceVoice* source_voice_[(int)Type::MAX] = {nullptr};	//!< ソースボイス
	BYTE* data_audio_[(int)Type::MAX] = {nullptr};					//!< オーディオデータ
	DWORD size_audio_[(int)Type::MAX] = {0};						//!< オーディオデータサイズ


//====================
// 関数
//====================
private:
	//----------------------------------------
	//! @brief コンストラクタ
	//! @param void なし
	//----------------------------------------
	SoundManager();

public:
	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param hWnd ウィンドウハンドル
	//! @retval HRESULT エラーチェック用
	//----------------------------------------
	HRESULT Init(HWND hWnd);

   //----------------------------------------
   //! @brief 終了関数
   //! @details
   //! @param void なし
   //! @retval void なし
   //----------------------------------------
	void Uninit();

	//----------------------------------------
	//! @brief 再生or停止関数
	//! @details
	//! @param type サウンドタイプ
	//! @retval HRESULT エラーチェック用
	//----------------------------------------
	HRESULT PlayOrStop(Type type);

	//----------------------------------------
	//! @brief 停止関数
	//! @details
	//! @param type サウンドタイプ
	//! @retval void なし
	//----------------------------------------
	void Stop(Type type);

	//----------------------------------------
	//! @brief 停止関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void AllStop();

private:
	//----------------------------------------
	//! @brief チャンクチェック関数
	//! @details
	//! @param file_handle         ファイルハンドル
	//! @param format              フォーマット
	//! @param chunk_size          チャンクサイズ
	//! @param chunk_data_position チャンクデータの場所
	//! @retval HRESULT エラーチェック用
	//----------------------------------------
	HRESULT CheckChunk(HANDLE file_handle, DWORD format, DWORD* chunk_size,
					   DWORD* chunk_data_position);

	//----------------------------------------
	//! @brief チャンク読み込み関数
	//! @details
	//! @param file_handle   ファイルハンドル
	//! @param buffer        読み込み先バッファ
	//! @param buffer_size   読み込み先バッファのサイズ
	//! @param buffer_offset 読み込み先バッファのオフセット
	//! @retval HRESULT エラーチェック用
	//----------------------------------------
	HRESULT ReadChunk(HANDLE file_handle, void* buffer, DWORD buffer_size,
					  DWORD buffer_offset);


//====================
// 消去済み関数
//====================
private:
	SoundManager(const SoundManager& class_name) = delete;
	SoundManager& operator = (const SoundManager& class_name) = delete;
};



#endif
