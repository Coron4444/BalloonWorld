//================================================================================
//!	@file	 DrawManager.h
//!	@brief	 描画マネージャーClass
//! @details 
//!	@author  Kai Araki									@date 2019/01/19
//================================================================================
#ifndef	_DRAW_MANAGER_H_
#define _DRAW_MANAGER_H_



//****************************************
// インクルード文
//****************************************
#include "fade.h"
#include "../Camera/Camera.h"
#include "../Camera/CameraState_CrawlUp.h"
#include "../Camera/CameraState_HomingTarget.h"
#include "../Camera/CameraState_Normal.h"



//****************************************
// クラス宣言
//****************************************
class DrawBase;
class DrawCommonData;
class ShaderManager;
class RenderTargetMain;
class RenderTargetShadowMap;
class MotionBlur;
class RenderTexturePolygon;
class GameObjectBase;



//************************************************************														   
//! @brief   描画マネージャーlass
//!
//! @details 登録されている描画基底クラスを管理するClass
//************************************************************
class DrawManager
{
//====================
// 列挙型定義
//====================
public:
	enum class RenderTargetType
	{
		NONE = -1,
		MAIN,
		SHADOW_MAP,
		MAX
	};


//====================
// 定数
//====================
public:
	static const unsigned DRAW_ARRAY_NUM = 10000;	//!< 配列数


//====================
// 変数
//====================
private:
	LimitedPointerArray<DrawBase*, DRAW_ARRAY_NUM> all_draw_;		//!< 全描画配列
	LimitedPointerArray<DrawBase*, DRAW_ARRAY_NUM> await_add_;		//!< 追加待ち配列
	LimitedPointerArray<DrawBase*, DRAW_ARRAY_NUM> await_release_;	//!< 解放待ち配列

	Camera* camera_[(int)RenderTargetType::MAX];				//!< カメラ群
	Fade* fade_;												//!< フェード
	DrawCommonData* common_data_ = nullptr;						//!< 共通データ
	ShaderManager* shader_manager_ = nullptr;					//!< シェーダーマネージャ
	RenderTargetMain* render_target_main_ = nullptr;			//!< レンダーターゲットメイン
	RenderTargetShadowMap* render_target_shadow_map_ = nullptr;	//!< レンダーターゲットシャドウマップ
	MotionBlur* motion_blur_ = nullptr;							//!< モーションブラー
	LPDIRECT3DSURFACE9 back_buffer_surface_ = nullptr;			//!< BackBufferサーフェス
	LPDIRECT3DSURFACE9 back_buffer_stencil_surface_ = nullptr;	//!< BackBufferステンシルサーフェス
	D3DVIEWPORT9 back_buffer_view_port_;						//!< BackBufferビューポート
	RenderTexturePolygon* back_buffer_polygon_ = nullptr;		//!< BackBuffer用ポリゴン
	LPDIRECT3DDEVICE9 device_ = nullptr;						//!< デバイス


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief 描画共通データ取得関数
	//! @details
	//! @param void なし
	//! @retval DrawCommonData* 描画共通データ
	//----------------------------------------
	DrawCommonData* getpDrawCommonData();

	//----------------------------------------
	//! @brief カメラ取得関数
	//! @details
	//! @param type レンダーターゲットタイプ
	//! @retval Camera* カメラ
	//----------------------------------------
	Camera* getpCamera(RenderTargetType type);


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Init();

	//----------------------------------------
	//! @brief 終了関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Uninit();

	//----------------------------------------
	//! @brief シーン変更時の終了関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void UninitWhenChangeScene();

	//----------------------------------------
	//! @brief 更新関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Update();

	//----------------------------------------
	//! @brief 描画関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Draw();

	//----------------------------------------
	//! @brief 描画基底クラスの追加関数
	//! @details
	//! @param *draw 描画基底クラス
	//! @retval void なし
	//----------------------------------------
	void AddDrawBaseToArray(DrawBase* draw);

	//----------------------------------------
	//! @brief 描画基底クラスの上書き関数
	//! @details
	//! @param *game_object ゲームオブジェクト
	//! @param *new_draw    新規描画基底クラス
	//! @retval void なし
	//----------------------------------------
	void OverwriteArrayDrawBase(GameObjectBase* game_object,
								DrawBase* new_draw);

	//----------------------------------------
	//! @brief 描画基底クラスの解放関数
	//! @details
	//! @param *draw 描画基底クラス
	//! @retval void なし
	//----------------------------------------
	void ReleaseDrawBaseFromArray(DrawBase* draw);
	
	//----------------------------------------
	//! @brief フェードインスタート関数
	//! @details
	//! @param type  タイプ
	//! @param size  拡縮
	//! @param color 色
	//! @param speed フェード速度
	//! @retval void なし
	//----------------------------------------
	void StartFadeIn(Fade::Type type, Vec2 size, XColor4 color, float speed);

	//----------------------------------------
	//! @brief フェードアウトスタート関数
	//! @details
	//! @param type  タイプ
	//! @param size  拡縮
	//! @param color 色
	//! @param speed フェード速度
	//! @retval void なし
	//----------------------------------------
	void StartFadeOut(Fade::Type type, Vec2 size, XColor4 color, float speed);

	//----------------------------------------
	//! @brief フェード終了確認関数
	//! @details
	//! @param void なし
	//! @retval bool フェード終了の有無
	//----------------------------------------
	bool IsFadeEnd();

	//----------------------------------------
	//! @brief フェードステート判定関数
	//! @details
	//! @param state ステート
	//! @retval bool 引数と合っていればtrue
	//----------------------------------------
	bool IsFadeState(Fade::State state);

private:
	//----------------------------------------
	//! @brief 追加待ち配列の中身を追加関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void AddContentsOfAwaitAddArray();

	//----------------------------------------
	//! @brief 解放待ち配列の中身を解放関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void ReleaseContentsOfAwaitReleaseArray();

	//----------------------------------------
	//! @brief 全描画基底クラス更新関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void UpdateAllDrawBase();

	//----------------------------------------
	//! @brief 全レンダーターゲットリセット関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void ResetAllRenderTarget();

	//----------------------------------------
	//! @brief 描画基底クラス振り分け関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void DistributeDrawBase();

	//----------------------------------------
	//! @brief 全レンダーターゲット更新関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void UpdateAllRenderTarget();

	//----------------------------------------
	//! @brief BackBuffer描画関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void DrawBackBuffer();

	//----------------------------------------
	//! @brief フェード描画関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void DrawFade();
};



#endif
