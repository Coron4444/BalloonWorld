//================================================================================
//!	@file	 AnimatedDefault.vsh
//!	@brief	 �A�j���[�V�����t���f�t�H���g���_�V�F�[�_
//! @details 
//!	@author  Kai Araki									@date 2019/1/19
//================================================================================



//****************************************
// �O���[�o���ϐ�
//****************************************
// �ϊ��s��
float4x4 MATRIX_WORLD;
float4x4 MATRIX_VIEW;
float4x4 MATRIX_PROJECTION;
float4x4 MATRIX_BONE[55];
int BONE_NUM = {4};




//************************************************************														   
//! @brief   �C���v�b�gStruct
//!
//! @details �C���v�b�g��Struct
//************************************************************
struct Input
{
    float4 position_    : POSITION;         //!< ���[�J�����W
    float3 normal_      : NORMAL;           //!< �@���x�N�g��
    float4 color_       : COLOR0;           //!< �F
    float2 uv_          : TEXCOORD0;        //!< UV
    float4 bone_weight_ : BLENDWEIGHT;      //!< �{�[���̏d��
    int4 bone_index_    : BLENDINDICES;     //!< �{�[���C���f�b�N�X
};



//************************************************************														   
//! @brief   �A�E�g�v�b�gStruct
//!
//! @details �A�E�g�v�b�g��Struct
//************************************************************
struct Output
{
    float4 position_     : POSITION;    //!< �ϊ��ςݍ��W
    float4 color_        : COLOR0;      //!< �F
    float2 uv_           : TEXCOORD0;   //!< uv
};



//****************************************
// �֐��錾
//****************************************
void CalculateWorldPosition(Input input, inout Output output);
void CalculateBoneMatrix(Input input, inout float4x4 bone_matrix);



//****************************************
// �֐���`
//****************************************
//--------------------------------------------------
//! @brief �G���g���[�֐�
//! @details
//! @param input ���̓f�[�^ 
//! @retval Output �o�̓f�[�^
//--------------------------------------------------
Output MainVertexShader(Input input)
{
	// �o�̓f�[�^�̏�����
    Output output = (Output)0;

    // ���[���h���W�Z�o
    CalculateWorldPosition(input, output);

    // ���_�F
    output.color_ = input.color_;

    // UV
    output.uv_ = input.uv_;

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
    // �{�[���s��Z�o
    float4x4 bone_matrix = (float4x4)0;              
    CalculateBoneMatrix(input, bone_matrix);

    // ���[���h���W�Z�o
    input.position_.w = 1.0f;
    output.position_ = mul(input.position_, bone_matrix);
    output.position_ = mul(output.position_, MATRIX_WORLD);
    output.position_ = mul(output.position_, MATRIX_VIEW);
    output.position_ = mul(output.position_, MATRIX_PROJECTION);
}



//--------------------------------------------------
//! @brief �{�[���s��Z�o�֐�
//! @details
//! @param input  ���̓f�[�^
//! @param bone_matrix �{�[���s��
//! @retval void �Ȃ�
//--------------------------------------------------
void CalculateBoneMatrix(Input input, inout float4x4 bone_matrix)
{
    float weight[4] = (float[4])input.bone_weight_;     // �d�݂�z��ɕ���
    float total_bone_weight = 0.0f;                     // �d�݂̍��v
    int bone_index;                                     // �{�[���C���f�b�N�X
    int blend_num = 4;                                  // �u�����h��
    int blend_num_minus_one = blend_num - 1;            // �u�����h���1

    // �{�[���s��(�{�[�����1)�u�����h
    for (int i = 0; i < blend_num_minus_one; i++)
    {
        total_bone_weight += weight[i];
        bone_index = input.bone_index_[i];
        bone_matrix += MATRIX_BONE[bone_index] * weight[i];
    }

    // �Ō�̃{�[���s����u�����h
    float last_weight = 1.0f - total_bone_weight;
    bone_index = input.bone_index_[blend_num_minus_one];
    bone_matrix += MATRIX_BONE[bone_index] * last_weight;
}