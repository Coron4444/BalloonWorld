//================================================================================
//!	@file	 Default.vsh
//!	@brief	 デフォルトVertexShader
//! @details 
//!	@author  Kai Araki									@date 2019/02/19
//================================================================================



//****************************************
// グローバル変数
//****************************************
// 変換行列
float4x4 MATRIX_WORLD;
float4x4 MATRIX_VIEW;
float4x4 MATRIX_PROJECTION;

// マテリアル
float4 MATERIAL_DIFFUSE = {1.0f, 1.0f, 1.0f, 1.0f};

// ディレクショナルライトベクトル(プログラム上で正規化済みが渡される)
float4 DIRECTIONAL_LIGHT_VECTOR = {1.0f, 0.0f, 0.0f, 1.0f};



//************************************************************														   
//! @brief   インプットStruct
//!
//! @details インプットのStruct
//************************************************************
struct Input
{
    float4 position_ : POSITION;    //!< ローカル座標
    float4 normal_   : NORMAL;      //!< 法線
    float4 color_    : COLOR0;      //!< 色
    float2 uv_       : TEXCOORD0;   //!< UV
};



//************************************************************														   
//! @brief   アウトプットStruct
//!
//! @details アウトプットのStruct
//************************************************************
struct Output
{
    float4 position_  : POSITION;  //!< 変換済み座標
    float4 color_     : COLOR0;    //!< 色
    float2 ps_uv_     : TEXCOORD0; //!< PS用UV
};



//****************************************
// 関数宣言
//****************************************
void CalculateWorldPosition(Input input, inout Output output);
void CalculateLambertDiffuseLighting(Input input, inout float4 color);


//--------------------------------------------------
//! @brief エントリー関数
//! @details
//! @param input   入力データ 
//! @retval Output 出力データ
//--------------------------------------------------
Output MainVertexShader(Input input)
{
	// 出力データの初期化
    Output output = (Output)0;

    // ワールド座標算出
    CalculateWorldPosition(input, output);

    // ランバート拡散照明での色算出
    float4 lambert_color;
    CalculateLambertDiffuseLighting(input, lambert_color);
    output.color_ = lambert_color;

    // PSへ渡す値の代入
    output.ps_uv_ = input.uv_;

    return output;
}



//--------------------------------------------------
//! @brief ワールド座標算出関数
//! @details
//! @param input  入力データ
//! @param output 出力データ
//! @retval void なし
//--------------------------------------------------
void CalculateWorldPosition(Input input, inout Output output)
{
    // ワールド座標算出
    input.position_.w = 1.0f;
    output.position_ = mul(input.position_, MATRIX_WORLD);
    output.position_ = mul(output.position_, MATRIX_VIEW);
    output.position_ = mul(output.position_, MATRIX_PROJECTION);
}



//--------------------------------------------------
//! @brief ランバート拡散照明での色算出関数
//! @details
//! @param input 入力データ
//! @param color 出力色
//! @retval void なし
//--------------------------------------------------
void CalculateLambertDiffuseLighting(Input input, inout float4 color)
{
    // 環境光の強さの比率を保存
    float ambient_ratio = DIRECTIONAL_LIGHT_VECTOR.w;

    // ディレクショナルライトベクトルを反転
    float4 inverse_light_vector = -DIRECTIONAL_LIGHT_VECTOR;

    // 色の計算
    color = MATERIAL_DIFFUSE * max(ambient_ratio, 
                                   dot(input.normal_, inverse_light_vector));

    // α値も補正の環境光の比率の影響を受けてしまうので別途代入し直す
    color.a = MATERIAL_DIFFUSE.a;
}