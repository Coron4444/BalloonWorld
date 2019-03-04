//================================================================================
//!	@file	 ShadowMap.vsh
//!	@brief	 �V���h�E�}�b�v���_�V�F�[�_
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



//************************************************************														   
//! @brief   �C���v�b�gStruct
//!
//! @details �C���v�b�g��Struct
//************************************************************
struct Input
{
    float4 position_    : POSITION;         //!< ���[�J�����W
};



//************************************************************														   
//! @brief   �A�E�g�v�b�gStruct
//!
//! @details �A�E�g�v�b�g��Struct
//************************************************************
struct Output
{
    float4 position_     : POSITION;    //!< �ϊ��ςݍ��W
    float4 ps_depth_     : TEXCOORD0;   //!< �[�x�l
};



//****************************************
// �֐��錾
//****************************************
void CalculateWorldPosition(Input input, inout Output output);



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

    // �ϊ��ςݒ��_��[�x�l�Ƃ���
    output.ps_depth_ = output.position_;
    
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