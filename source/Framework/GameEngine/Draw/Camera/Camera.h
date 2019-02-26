//================================================================================
//!	@file	 Camera.h
//!	@brief	 カメラClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================
#ifndef	_CAMERA_H_
#define _CAMERA_H_



//****************************************
// インクルード文
//****************************************
#include <Tool/Axis.h>
#include <Tool/Vector3D.h>
#include <Tool/Matrix.h>



//************************************************************														   
//! @brief   カメラClass
//!
//! @details カメラのClass
//************************************************************
class Camera
{
//====================
// クラス定義
//====================
public:
	//****************************************														   
	//! @brief カメラステートClass
	//!
	//! @details カメラステートのClass
	//****************************************
	class State
	{
	//====================
	// 変数
	//====================
	private:
		Camera* camera_;			//!< カメラ
		bool is_input_ = true;		//!< 入力フラグ
		bool is_update_ = true;		//!< 更新フラグ


	//====================
	// プロパティ
	//====================
	public:
		//----------------------------------------
		//! @brief 入力フラグ取得関数
		//! @details
		//! @param void なし
		//! @retval bool 入力フラグ
		//----------------------------------------
		bool getIsInput();

		//----------------------------------------
		//! @brief 入力フラグ取得関数
		//! @details
		//! @param value 入力フラグ
		//! @retval void なし
		//----------------------------------------
		void setIsInput(bool value);

		//----------------------------------------
		//! @brief 更新フラグ取得関数
		//! @details
		//! @param void なし
		//! @retval bool 更新フラグ
		//----------------------------------------
		bool getIsUpdate();

		//----------------------------------------
		//! @brief 更新フラグ取得関数
		//! @details
		//! @param value 更新フラグ
		//! @retval void なし
		//----------------------------------------
		void setIsUpdate(bool value);

		//----------------------------------------
		//! @brief カメラ取得関数
		//! @details
		//! @param void なし
		//! @retval Camera* カメラ
		//----------------------------------------
		Camera* getpCamera();

		//----------------------------------------
		//! @brief カメラ設定関数
		//! @details
		//! @param *value カメラ
		//! @retval void なし
		//----------------------------------------
		void setCamera(Camera* value);


	//====================
	// 関数
	//====================
	public:
		//----------------------------------------
		//! @brief デストラクタ
		//! @details
		//! @param void なし
		//----------------------------------------
		virtual ~State() = 0;

		//----------------------------------------
		//! @brief 初期化関数
		//! @details
		//! @param void なし
		//! @retval void なし
		//----------------------------------------
		virtual void Init() = 0;

		//----------------------------------------
		//! @brief 終了関数
		//! @details
		//! @param void なし
		//! @retval void なし
		//----------------------------------------
		virtual void Uninit() = 0;

		//----------------------------------------
		//! @brief 更新関数
		//! @details
		//! @param void なし
		//! @retval void なし
		//----------------------------------------
		virtual void Update() = 0;
	};


//====================
// 列挙型定義
//====================
public:
	enum class Type
	{
		NONE = -1,
		PERSPECTIVE,
		ORTHO,
		TWO_DIMENSIONAL,
		MAX
	};


//====================
// 変数
//====================
public:
	static const float NEAR_CLIPPING_PLANE;		//!< 近面クリップ
	static const float FAR_CLIPPING_PLANE;		//!< 遠面クリップ
	static const float DEFAULT_ANGLE_OF_VIEW;	//!< 画角


//====================
// 変数
//====================
private:
	Vector3D position_;					//!< 座標
	Vector3D gazing_point_;				//!< 注視点
	Vector3D up_;						//!< 上方向
	float angle_of_view_;				//!< 画角
	Matrix view_;						//!< ビュー行列
	Matrix view_2D_;					//!< ビュー行列(2D)
	Matrix projection_perspective_;		//!< プロジェクション行列(透視投影)
	Matrix projection_ortho_;			//!< プロジェクション行列(正射影)
	Matrix projection_2D_;				//!< プロジェクション行列(2D)
	State* state_;						//!< ステート
	Type type_;							//!< タイプ


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief ビュー行列取得関数
	//! @details
	//! @param void なし
	//! @retval Matrix* ビュー行列
	//----------------------------------------
	Matrix* getpViewMatrix();

	//----------------------------------------
	//! @brief プロジェクション行列取得関数
	//! @details
	//! @param void なし
	//! @retval Matrix* プロジェクション行列
	//----------------------------------------
	Matrix* getpProjectionMatrix();

	//----------------------------------------
	//! @brief 座標取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D* 座標
	//----------------------------------------
	Vector3D* getpPosition();
	
	//----------------------------------------
	//! @brief 注視点取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D* 注視点
	//----------------------------------------
	Vector3D* getpGazingPoint();
	
	//----------------------------------------
	//! @brief 画角取得関数
	//! @details
	//! @param void なし
	//! @retval float 画角
	//----------------------------------------
	float getAngleOfView();
	
	//----------------------------------------
	//! @brief 画角設定関数
	//! @details
	//! @param value 画角
	//! @retval void なし
	//----------------------------------------
	void setAngleOfView(float value);
	
	//----------------------------------------
	//! @brief ステート取得関数
	//! @details
	//! @param void なし
	//! @retval State* ステート
	//----------------------------------------
	State* getpState();

	//----------------------------------------
	//! @brief ステート設定関数
	//! @details
	//! @param *value ステート
	//! @retval void なし
	//----------------------------------------
	void setState(State* value);
	
	//----------------------------------------
	//! @brief タイプ取得関数
	//! @details
	//! @param void なし
	//! @retval Type タイプ
	//----------------------------------------
	Type getType();
	
	//----------------------------------------
	//! @brief タイプ設定関数
	//! @details
	//! @param value タイプ
	//! @retval void なし
	//----------------------------------------
	void setType(Type value);

	//----------------------------------------
	//! @brief 右ベクトル取得関数
	//! @details
	//! @param void
	//! @retval Vector3D* 右ベクトル
	//----------------------------------------
	Vector3D* getpRight();

	//----------------------------------------
	//! @brief 上ベクトル取得関数
	//! @details
	//! @param void
	//! @retval Vector3D* 上ベクトル
	//----------------------------------------
	Vector3D* getpUp();

	//----------------------------------------
	//! @brief 前ベクトル取得関数
	//! @details
	//! @param void
	//! @retval Vector3D* 前ベクトル
	//----------------------------------------
	Vector3D* getpForward();

	//----------------------------------------
	//! @brief 既定前ベクトル取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D* 既定前ベクトル
	//----------------------------------------
	Vector3D* getpDefaultForward();

	//----------------------------------------
	//! @brief 既定上ベクトル取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D* 既定上ベクトル
	//----------------------------------------
	Vector3D* getpDefaultUp();

	//----------------------------------------
	//! @brief 既定右ベクトル取得関数
	//! @details
	//! @param void なし
	//! @retval Vector3D* 既定右ベクトル
	//----------------------------------------
	Vector3D* getpDefaultRight();


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief コンストラクタ
	//! @details
	//! @param void なし
	//----------------------------------------
	Camera();

	//----------------------------------------
	//! @brief デストラクタ
	//! @details
	//! @param void なし
	//----------------------------------------
	~Camera();


	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param state        ステート
	//! @param position     座標
	//! @param gazing_point 注視点
	//! @param up           上ベクトル
	//! @retval void なし
	//----------------------------------------
	void Init(State* state, Vector3D position = {0.0f, 0.0f, -10.0f},
			  Vector3D gazing_point = {0.0f, 0.0f, 0.0f}, 
			  Vector3D up = {0.0f, 1.0f, 0.0f});

	//----------------------------------------
	//! @brief 初期化関数
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
	//! @brief ビュー行列作成関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void CreateViewMatrix();

	//----------------------------------------
	//! @brief 透視投影プロジェクション行列作成関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void CreateProjectionMatrixPerspectiveFov();

	//----------------------------------------
	//! @brief 正射影プロジェクション行列作成関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void CreateProjectionMatrixOrtho();

	//----------------------------------------
	//! @brief 2Dプロジェクション行列作成関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void CreateProjectionMatrix2D();
};



#endif