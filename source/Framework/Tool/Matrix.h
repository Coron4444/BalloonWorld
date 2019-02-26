//================================================================================
//!	@file	 Matrix.h
//!	@brief	 行列Class
//! @details 
//!	@author  Kai Araki									@date 2019/02/23
//================================================================================
#ifndef	_MATRIX_H_
#define _MATRIX_H_



//****************************************
// インクルード文
//****************************************
#include "Vector3D.h"



//****************************************
// 型定義
//****************************************
using MATRIX = D3DXMATRIX;



//************************************************************														   
//! @brief   行列Class
//!
//! @details 行列のClass
//************************************************************
class Matrix : public MATRIX
{
//====================
// 定数
//====================
private:
	static const Vector3D DEFAULT_RIGHT;	//!< 既定右ベクトル
	static const Vector3D DEFAULT_UP;		//!< 既定上ベクトル
	static const Vector3D DEFAULT_FORWARD;	//!< 既定前ベクトル


//====================
// 変数
//====================
private:
	Vector3D right_;			//!< 右ベクトル
	Vector3D up_;				//!< 上ベクトル
	Vector3D forward_;			//!< 前ベクトル
	Vector3D default_right_;	//!< 既定右ベクトル
	Vector3D default_up_;		//!< 既定上ベクトル
	Vector3D default_forward_;	//!< 既定前ベクトル


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief 11成分取得関数
	//! @details
	//! @param void なし
	//! @retval float 11成分
	//----------------------------------------
	float get11() const;

	//----------------------------------------
	//! @brief 11成分設定関数
	//! @details
	//! @param value 11成分
	//! @retval void なし
	//----------------------------------------
	void set11(float value);

	//----------------------------------------
	//! @brief 12成分取得関数
	//! @details
	//! @param void なし
	//! @retval float 12成分
	//----------------------------------------
	float get12() const;

	//----------------------------------------
	//! @brief 12成分設定関数
	//! @details
	//! @param value 12成分
	//! @retval void なし
	//----------------------------------------
	void set12(float value);

	//----------------------------------------
	//! @brief 13成分取得関数
	//! @details
	//! @param void なし
	//! @retval float 13成分
	//----------------------------------------
	float get13() const;

	//----------------------------------------
	//! @brief 13成分設定関数
	//! @details
	//! @param value 13成分
	//! @retval void なし
	//----------------------------------------
	void set13(float value);

	//----------------------------------------
	//! @brief 14成分取得関数
	//! @details
	//! @param void なし
	//! @retval float 14成分
	//----------------------------------------
	float get14() const;

	//----------------------------------------
	//! @brief 14成分設定関数
	//! @details
	//! @param value 14成分
	//! @retval void なし
	//----------------------------------------
	void set14(float value);

	//----------------------------------------
	//! @brief 21成分取得関数
	//! @details
	//! @param void なし
	//! @retval float 21成分
	//----------------------------------------
	float get21() const;

	//----------------------------------------
	//! @brief 21成分設定関数
	//! @details
	//! @param value 21成分
	//! @retval void なし
	//----------------------------------------
	void set21(float value);

	//----------------------------------------
	//! @brief 22成分取得関数
	//! @details
	//! @param void なし
	//! @retval float 22成分
	//----------------------------------------
	float get22() const;

	//----------------------------------------
	//! @brief 22成分設定関数
	//! @details
	//! @param value 22成分
	//! @retval void なし
	//----------------------------------------
	void set22(float value);

	//----------------------------------------
	//! @brief 23成分取得関数
	//! @details
	//! @param void なし
	//! @retval float 23成分
	//----------------------------------------
	float get23() const;

	//----------------------------------------
	//! @brief 23成分設定関数
	//! @details
	//! @param value 23成分
	//! @retval void なし
	//----------------------------------------
	void set23(float value);

	//----------------------------------------
	//! @brief 24成分取得関数
	//! @details
	//! @param void なし
	//! @retval float 24成分
	//----------------------------------------
	float get24() const;

	//----------------------------------------
	//! @brief 24成分設定関数
	//! @details
	//! @param value 24成分
	//! @retval void なし
	//----------------------------------------
	void set24(float value);

	//----------------------------------------
	//! @brief 31成分取得関数
	//! @details
	//! @param void なし
	//! @retval float 31成分
	//----------------------------------------
	float get31() const;

	//----------------------------------------
	//! @brief 31成分設定関数
	//! @details
	//! @param value 31成分
	//! @retval void なし
	//----------------------------------------
	void set31(float value);

	//----------------------------------------
	//! @brief 32成分取得関数
	//! @details
	//! @param void なし
	//! @retval float 32成分
	//----------------------------------------
	float get32() const;

	//----------------------------------------
	//! @brief 32成分設定関数
	//! @details
	//! @param value 32成分
	//! @retval void なし
	//----------------------------------------
	void set32(float value);

	//----------------------------------------
	//! @brief 33成分取得関数
	//! @details
	//! @param void なし
	//! @retval float 33成分
	//----------------------------------------
	float get33() const;

	//----------------------------------------
	//! @brief 33成分設定関数
	//! @details
	//! @param value 33成分
	//! @retval void なし
	//----------------------------------------
	void set33(float value);

	//----------------------------------------
	//! @brief 34成分取得関数
	//! @details
	//! @param void なし
	//! @retval float 34成分
	//----------------------------------------
	float get34() const;

	//----------------------------------------
	//! @brief 34成分設定関数
	//! @details
	//! @param value 34成分
	//! @retval void なし
	//----------------------------------------
	void set34(float value);

	//----------------------------------------
	//! @brief 41成分取得関数
	//! @details
	//! @param void なし
	//! @retval float 41成分
	//----------------------------------------
	float get41() const;

	//----------------------------------------
	//! @brief 41成分設定関数
	//! @details
	//! @param value 41成分
	//! @retval void なし
	//----------------------------------------
	void set41(float value);

	//----------------------------------------
	//! @brief 42成分取得関数
	//! @details
	//! @param void なし
	//! @retval float 42成分
	//----------------------------------------
	float get42() const;

	//----------------------------------------
	//! @brief 42成分設定関数
	//! @details
	//! @param value 42成分
	//! @retval void なし
	//----------------------------------------
	void set42(float value);

	//----------------------------------------
	//! @brief 43成分取得関数
	//! @details
	//! @param void なし
	//! @retval float 43成分
	//----------------------------------------
	float get43() const;

	//----------------------------------------
	//! @brief 43成分設定関数
	//! @details
	//! @param value 43成分
	//! @retval void なし
	//----------------------------------------
	void set43(float value);

	//----------------------------------------
	//! @brief 44成分取得関数
	//! @details
	//! @param void なし
	//! @retval float 44成分
	//----------------------------------------
	float get44() const;

	//----------------------------------------
	//! @brief 44成分設定関数
	//! @details
	//! @param value 44成分
	//! @retval void なし
	//----------------------------------------
	void set44(float value);

	//----------------------------------------
	//! @brief 座標取得取得関数
	//! @details
	//! @param void
	//! @retval Vector3D 座標
	//----------------------------------------
	Vector3D getPosition();

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
// 演算子
//====================
public:
	//----------------------------------------
	//! @brief *演算子
	//! @details
	//! @param &matrix 行列
	//! @retval Matrix 乗算後の行列
	//----------------------------------------
	Matrix operator * (const Matrix& matrix) const;


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief コンストラクタ
	//! @details
	//! @param void なし
	//----------------------------------------
	Matrix();

	//----------------------------------------
	//! @brief 単一floatコンストラクタ
	//! @details
	//! @param value 成分
	//----------------------------------------
	Matrix(const float* value);

	//----------------------------------------
	//! @brief 単一float16コンストラクタ
	//! @details
	//! @param value 成分
	//----------------------------------------
	Matrix(const Float16* value);

	//----------------------------------------
	//! @brief 行列コンストラクタ
	//! @details
	//! @param matrix 行列
	//----------------------------------------
	Matrix(const Matrix& matrix);

	//----------------------------------------
	//! @brief 複数floatコンストラクタ
	//! @details
	//! @param value11 11成分
	//! @param value12 12成分
	//! @param value13 13成分
	//! @param value14 14成分
	//! @param value21 21成分
	//! @param value22 22成分
	//! @param value23 23成分
	//! @param value24 24成分
	//! @param value31 31成分
	//! @param value32 32成分
	//! @param value33 33成分
	//! @param value34 34成分
	//! @param value41 41成分
	//! @param value42 42成分
	//! @param value43 43成分
	//! @param value44 44成分
	//----------------------------------------
	Matrix(float value11, float value12, float value13, float value14,
		   float value21, float value22, float value23, float value24,
		   float value31, float value32, float value33, float value34,
		   float value41, float value42, float value43, float value44);

	//----------------------------------------
	//! @brief デストラクタ
	//! @details
	//! @param matrix 行列
	//----------------------------------------
	~Matrix();

	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Init();

	//----------------------------------------
	//! @brief 座標行列作成関数
	//! @details
	//! @param *position 座標
	//! @retval void なし
	//----------------------------------------
	void CreatePosition(Vector3D* position);

	//----------------------------------------
	//! @brief 拡縮行列作成関数
	//! @details
	//! @param *scale 拡縮
	//! @retval void なし
	//----------------------------------------
	void CreateScale(Vector3D* scale);

	//----------------------------------------
	//! @brief X軸回転行列作成関数
	//! @details
	//! @param radian 角度
	//! @retval void なし
	//----------------------------------------
	void CreateRotationAxisX(float radian);

	//----------------------------------------
	//! @brief Z軸回転行列作成関数
	//! @details
	//! @param radian 角度
	//! @retval void なし
	//----------------------------------------
	void CreateRotationAxisY(float radian);

	//----------------------------------------
	//! @brief Z軸回転行列作成関数
	//! @details
	//! @param radian 角度
	//! @retval void なし
	//----------------------------------------
	void CreateRotationAxisZ(float radian);

	//----------------------------------------
	//! @brief 任意軸回転行列作成関数
	//! @details
	//! @param axis   軸
	//! @param radian 角度
	//! @retval void なし
	//----------------------------------------
	void CreateRotationAxisAny(Vector3D axis, float radian);

	//----------------------------------------
	//! @brief 回転行列作成関数
	//! @details
	//! @param *quaternion クォータニオン
	//! @retval void なし
	//----------------------------------------
	void CreateRotationQuaternion(Quaternion* quaternion);

	//----------------------------------------
	//! @brief ワールド行列作成関数
	//! @details
	//! @param *scale    拡縮行列
	//! @param *rotation 回転行列
	//! @param *position 座標行列
	//! @retval void なし
	//----------------------------------------
	void CreateWorld(Matrix* scale, Matrix* rotation, Matrix* position);

	//----------------------------------------
	//! @brief ビュー行列作成関数
	//! @details
	//! @param *position     座標
	//! @param *gazing_point 注視点
	//! @param *up           上方向
	//! @retval void なし
	//----------------------------------------
	void CreateView(Vector3D* position, Vector3D* gazing_point, Vector3D* up);

	//----------------------------------------
	//! @brief 左手座標系透視投影プロジェクション行列作成関数
	//! @details
	//! @param angle_of_view 画角
	//! @param screen_width  スクリーン幅
	//! @param screen_height スクリーン高さ
	//! @param near_clip     ニアクリップ
	//! @param far_clip      ファークリップ
	//! @retval void なし
	//----------------------------------------
	void CreateProjectionPerspectiveFovLH(float angle_of_view, float screen_width,
										  float screen_height, float near_clip,
										  float far_clip);

	//----------------------------------------
	//! @brief 正射影プロジェクション行列作成関数
	//! @details
	//! @param angle_of_view 画角
	//! @param screen_width  スクリーン幅
	//! @param screen_height スクリーン高さ
	//! @param near_clip     ニアクリップ
	//! @param far_clip      ファークリップ
	//! @retval void なし
	//----------------------------------------
	void CreateProjectionOrtho(float angle_of_view, float screen_width,
							   float screen_height, float near_clip,
							   float far_clip);

	//----------------------------------------
	//! @brief 2Dプロジェクション行列作成関数
	//! @details
	//! @param screen_width  スクリーン幅
	//! @param screen_height スクリーン高さ
	//! @retval void なし
	//----------------------------------------
	void CreateProjection2D(float screen_width, float screen_height);

	//----------------------------------------
	//! @brief 逆行列化関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void ChangeInverse();

	//----------------------------------------
	//! @brief 転置行列化関数
	//! @details
	//! @param is_position_off 平行移動OFFフラグ
	//! @retval void なし
	//----------------------------------------
	void ChangeTranspose(bool is_position_off = false);

	//----------------------------------------
	//! @brief 親行列追加関数
	//! @details
	//! @param matrix 親行列
	//! @retval void なし
	//----------------------------------------
	void AddParentMatrix(Matrix* matrix);

	//----------------------------------------
	//! @brief 子行列追加関数
	//! @details
	//! @param matrix 子行列
	//! @retval void なし
	//----------------------------------------
	void AddChildMatrix(Matrix* matrix);

private:
	//----------------------------------------
	//! @brief 軸作成関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void CreateAxis();

	//----------------------------------------
	//! @brief ビュー軸作成関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void CreateViewAxis();
};



#endif