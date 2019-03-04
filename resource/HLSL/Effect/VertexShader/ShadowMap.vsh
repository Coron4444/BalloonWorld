//================================================================================
//!	@file	 ShadowMap.vsh
//!	@brief	 シャドウマップ頂点シェーダ
//! @details 
//!	@author  Kai Araki									@date 2019/1/19
//================================================================================



//****************************************
// グローバル変数
//****************************************
// 変換行列
float4x4 MATRIX_WORLD;
float4x4 MATRIX_VIEW;
float4x4 MATRIX_PROJECTION;



//************************************************************														   
//! @brief   インプットStruct
//!
//! @details インプットのStruct
//************************************************************
struct Input
{
    float4 position_    : POSITION;         //!< ローカル座標
};



//************************************************************														   
//! @brief   アウトプットStruct
//!
//! @details アウトプットのStruct
//************************************************************
struct Output
{
    float4 position_     : POSITION;    //!< 変換済み座標
    float4 ps_depth_     : TEXCOORD0;   //!< 深度値
};



//****************************************
// 関数宣言
//****************************************
void CalculateWorldPosition(Input input, inout Output output);



//****************************************
// 関数定義
//****************************************
//--------------------------------------------------
//! @brief エントリー関数
//! @details
//! @param input 入力データ 
//! @retval Output 出力データ
//--------------------------------------------------
Output MainVertexShader(Input input)
{
	// 出力データの初期化
    Output output = (Output)0;

    // ワールド座標算出
    CalculateWorldPosition(input, output);

    // 変換済み頂点を深度値とする
    output.ps_depth_ = output.position_;
    
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