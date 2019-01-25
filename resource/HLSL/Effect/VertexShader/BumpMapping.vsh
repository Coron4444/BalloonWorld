//================================================================================
//
//    �o���v�}�b�s���O���_�V�F�[�_�[
//    Author : Araki Kai                                �쐬�� : 2018/08/07
//
//================================================================================



//****************************************
// �O���[�o���ϐ�
//****************************************
// �ϊ��s��
float4x4 MATRIX_WORLD;
float4x4 MATRIX_VIEW;
float4x4 MATRIX_PROJECTION;

// �����o�[�g�g�U�Ɩ�(���C�g�x�N�g���̓v���O�����Ő��K��)
float4 LAMBERT_DIFFUSE_LIGHT_VECTOR = { 1.0f, 0.0f, 0.0f, 1.0f };
float4 LAMBERT_DIFFUSE_LIGHT_COLOR = { 1.0f, 1.0f, 1.0f, 1.0f };

// �J�������W
float3 CAMERA_POSITION = { 0.0f, 0.0f, 0.0f };



//****************************************
// �\���̒�`
//****************************************
struct InputVertexShader
{
    float4 position_ : POSITION; // ���[�J�����W
    float3 normal_ : NORMAL; // �@���x�N�g��
    float3 tangent_ : TANGENT0; // �ڃx�N�g��
    float2 texcoord_ : TEXCOORD0; // �@���x�N�g��
};


struct OutputVertexShader
{
    float4 position_ : POSITION;
    float4 color_ : COLOR0;
    float2 texcoord_ : TEXCOORD0; // �@���x�N�g��
    float3 eye_vector_ : TEXCOORD1; // �����x�N�g��
    float3 light_vector_ : TEXCOORD2; // ���C�g�x�N�g��
};



//****************************************
// ���_�V�F�[�_�[
//****************************************
//--------------------------------------------------
// +�G���g���֐�
//--------------------------------------------------
OutputVertexShader MainVertexShader(InputVertexShader input)
{
//------------------------------------------------------------
// ������

	// �o�̓f�[�^�̍쐬
    OutputVertexShader output = (OutputVertexShader) 0;


//------------------------------------------------------------
// ���W�ϊ�
    
    output.position_ = mul(input.position_, MATRIX_WORLD);
    output.position_ = mul(output.position_, MATRIX_VIEW);
    output.position_ = mul(output.position_, MATRIX_PROJECTION);



//------------------------------------------------------------
// ���b�V���̐F

    output.color_ = LAMBERT_DIFFUSE_LIGHT_COLOR;

	
//------------------------------------------------------------
// �f�J�[���p�e�N�X�`�����W

    output.texcoord_ = input.texcoord_;


//------------------------------------------------------------
// ���_��ԍ��W�n�̊��x�N�g���̌v�Z

	// �]�@���̎Z�o
    float3 binormal = cross(input.normal_, input.tangent_);


//------------------------------------------------------------
// �����x�N�g���ƃ��C�g�x�N�g���𒸓_��ԍ��W�n�ɕϊ�

	// �����x�N�g��
    float3 eye_vector = CAMERA_POSITION - input.position_.xyz;
    output.eye_vector_.x = dot(eye_vector, input.tangent_);
    output.eye_vector_.y = dot(eye_vector, binormal);
    output.eye_vector_.z = dot(eye_vector, input.normal_);

	// ���C�g�x�N�g��
    float3 light_vector = -LAMBERT_DIFFUSE_LIGHT_VECTOR.xyz;
    output.light_vector_.x = dot(light_vector, input.tangent_);
    output.light_vector_.y = dot(light_vector, binormal);
    output.light_vector_.z = dot(light_vector, input.normal_);

    return output;
}