//================================================================================
//!	@file	 MotionBlur.h
//!	@brief	 モーションブラーClass
//! @details 
//!	@author  Kai Araki									@date 2019/01/28
//================================================================================
#ifndef	_MOTION_BLUR_H_
#define _MOTION_BLUR_H_



//****************************************
// クラス宣言
//****************************************
class Camera;
class DrawCommonData;
class ShaderManager;
class RenderTexturePolygon;



//************************************************************														   
//! @brief   モーションブラーClass
//!
//! @details モーションブラーのClass
//************************************************************
class MotionBlur
{
//====================
// 変数
//====================
private:
	Camera* camera_ = nullptr;					//!< カメラ
	DrawCommonData* common_data_ = nullptr;		//!< 描画共通データ
	ShaderManager* shader_manager_ = nullptr;	//!< シェーダーマネージャ
	RenderTexturePolygon* polygon_ = nullptr;	//!< 表示用ポリゴン


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief カメラ設定関数
	//! @details
	//! @param *value カメラ
	//! @retval void なし
	//----------------------------------------
	void setCamera(Camera* value);
	
	//----------------------------------------
	//! @brief 描画共通データ設定関数
	//! @details
	//! @param *value 描画共通データ
	//! @retval void なし
	//----------------------------------------
	void setDrawCommonData(DrawCommonData* value);

	//----------------------------------------
	//! @brief シェーダーマネージャ設定関数
	//! @details
	//! @param value シェーダーマネージャ
	//! @retval void なし
	//----------------------------------------
	void setShaderManager(ShaderManager* value);


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
	//! @brief シーン変更時の終了関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void UninitWhenChangeScene();

	//----------------------------------------
	//! @brief 終了関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Uninit();

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
	//! @brief 後更新関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void LateUpdate();
};



#endif
