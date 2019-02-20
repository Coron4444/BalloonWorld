//================================================================================
//!	@file	 Default.vsh
//!	@brief	 �f�t�H���gVertexShader
//! @details 
//!	@author  Kai Araki									@date 2019/02/19
//================================================================================



//****************************************
// �O���[�o���ϐ�
//****************************************
// �ϊ��s��
float4x4 MATRIX_WORLD;
float4x4 MATRIX_VIEW;
float4x4 MATRIX_PROJECTION;

// �}�e���A��
float4 MATERIAL_DIFFUSE = {1.0f, 1.0f, 1.0f, 1.0f};

// �f�B���N�V���i�����C�g�x�N�g��(�v���O������Ő��K���ς݂��n�����)
float4 DIRECTIONAL_LIGHT_VECTOR = {1.0f, 0.0f, 0.0f, 1.0f};



//************************************************************														   
//! @brief   �C���v�b�gStruct
//!
//! @details �C���v�b�g��Struct
//************************************************************
struct Input
{
    float4 position_ : POSITION;    //!< ���[�J�����W
    float4 normal_   : NORMAL;      //!< �@��
    float4 color_    : COLOR0;      //!< �F
    float2 uv_       : TEXCOORD0;   //!< UV
};



//************************************************************														   
//! @brief   �A�E�g�v�b�gStruct
//!
//! @details �A�E�g�v�b�g��Struct
//************************************************************
struct Output
{
    float4 position_  : POSITION;  //!< �ϊ��ςݍ��W
    float4 color_     : COLOR0;    //!< �F
    float2 ps_uv_     : TEXCOORD0; //!< PS�pUV
};



//****************************************
// �֐��錾
//****************************************
void CalculateWorldPosition(Input input, inout Output output);
void CalculateLambertDiffuseLighting(Input input, inout float4 color);


//--------------------------------------------------
//! @brief �G���g���[�֐�
//! @details
//! @param input   ���̓f�[�^ 
//! @retval Output �o�̓f�[�^
//--------------------------------------------------
Output MainVertexShader(Input input)
{
	// �o�̓f�[�^�̏�����
    Output output = (Output)0;

    // ���[���h���W�Z�o
    CalculateWorldPosition(input, output);

    // �����o�[�g�g�U�Ɩ��ł̐F�Z�o
    float4 lambert_color;
    CalculateLambertDiffuseLighting(input, lambert_color);
    output.color_ = lambert_color;

    // PS�֓n���l�̑��
    output.ps_uv_ = input.uv_;

    return output;
}



//--------------------------------------------------
//! @brief ���[���h���W�Z�o�֐�
//! @details
//! @param input  ���̓f�[�^
//! @param output �o�̓f�[�^
//! @retval void �Ȃ�
//--------------------------------------------------
void CalculateWorldPosition(Input input, inout Output output)
{
    // ���[���h���W�Z�o
    input.position_.w = 1.0f;
    output.position_ = mul(input.position_, MATRIX_WORLD);
    output.position_ = mul(output.position_, MATRIX_VIEW);
    output.position_ = mul(output.position_, MATRIX_PROJECTION);
}



//--------------------------------------------------
//! @brief �����o�[�g�g�U�Ɩ��ł̐F�Z�o�֐�
//! @details
//! @param input ���̓f�[�^
//! @param color �o�͐F
//! @retval void �Ȃ�
//--------------------------------------------------
void CalculateLambertDiffuseLighting(Input input, inout float4 color)
{
    // �����̋����̔䗦��ۑ�
    float ambient_ratio = DIRECTIONAL_LIGHT_VECTOR.w;

    // �f�B���N�V���i�����C�g�x�N�g���𔽓]
    float4 inverse_light_vector = -DIRECTIONAL_LIGHT_VECTOR;

    // �F�̌v�Z
    color = MATERIAL_DIFFUSE * max(ambient_ratio, 
                                   dot(input.normal_, inverse_light_vector));

    // ���l���␳�̊����̔䗦�̉e�����󂯂Ă��܂��̂ŕʓr���������
    color.a = MATERIAL_DIFFUSE.a;
}