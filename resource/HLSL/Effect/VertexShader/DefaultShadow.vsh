//================================================================================
//!	@file	 DefaultShadow.vsh
//!	@brief	 デフォルト影VertexShader
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
float4x4 LIGHT_VIEW;
float4x4 LIGHT_PROJECTION;
float4x4 TEXTURE_PROJECTION;

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
    float4 position_         : POSITION;  //!< 変換済み座標
    float4 color_            : COLOR0;    //!< 色
    float2 ps_uv_            : TEXCOORD0; //!< PS用UV
    float4 ps_diffuse_       : TEXCOORD1; //!< PS用ディヒューズ
    float4 ps_ambient_       : TEXCOORD2; //!< PS用アンビエント
    float4 ps_shadow_map_uv_ : TEXCOORD3; //!< PS用シャドウマップUV
    float4 ps_depth_         : TEXCOORD4; //!< PS用深度値
};



//****************************************
// 関数宣言
//****************************************
void CalculateWorldPosition(Input input, inout Output output);
void CalculateShadowMapUV(Input input, inout Output output);
void CalculateDepth(Input input, inout Output output);
void CalculateLambertDiffuseLighting(Input input, inout Output output);


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

    // シャドウマップUV算出
    CalculateShadowMapUV(input, output);

    CalculateDepth(input, output);

    // ランバート拡散照明での色算出
    CalculateLambertDiffuseLighting(input, output);
    
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
//! @brief シャドウマップUV算出関数
//! @details
//! @param input  入力データ
//! @param output 出力データ
//! @retval void なし
//--------------------------------------------------
void CalculateShadowMapUV(Input input, inout Output output)
{
    input.position_.w = 1.0f;
    output.ps_shadow_map_uv_ = mul(input.position_, MATRIX_WORLD);
    output.ps_shadow_map_uv_ = mul(output.ps_shadow_map_uv_, LIGHT_VIEW);
    output.ps_shadow_map_uv_ = mul(output.ps_shadow_map_uv_, LIGHT_PROJECTION);
    output.ps_shadow_map_uv_ = mul(output.ps_shadow_map_uv_, TEXTURE_PROJECTION);
}



//--------------------------------------------------
//! @brief 深度値算出関数
//! @details
//! @param input  入力データ
//! @param output 出力データ
//! @retval void なし
//--------------------------------------------------
void CalculateDepth(Input input, inout Output output)
{
    input.position_.w = 1.0f;
    output.ps_depth_ = mul(input.position_, MATRIX_WORLD);
    output.ps_depth_ = mul(output.ps_depth_, LIGHT_VIEW);
    output.ps_depth_ = mul(output.ps_depth_, LIGHT_PROJECTION);
}



//--------------------------------------------------
//! @brief ランバート拡散照明での色算出関数
//! @details
//! @param input  入力データ
//! @param output 出力データ
//! @retval void なし
//--------------------------------------------------
void CalculateLambertDiffuseLighting(Input input, inout Output output)
{
    // 環境光の強さの比率を保存
    float ambient_ratio = DIRECTIONAL_LIGHT_VECTOR.w;

    // ディレクショナルライトベクトルを反転
    float4 inverse_light_vector = -DIRECTIONAL_LIGHT_VECTOR;

    // 色の計算
    output.ps_diffuse_ = MATERIAL_DIFFUSE * max(dot(input.normal_, inverse_light_vector), 0);
    output.ps_ambient_ = MATERIAL_DIFFUSE * ambient_ratio;

    // α値も補正の環境光の比率の影響を受けてしまうので別途代入し直す
    output.ps_diffuse_.a = MATERIAL_DIFFUSE.a;
    output.ps_ambient_.a = MATERIAL_DIFFUSE.a;
}