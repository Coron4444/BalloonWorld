//================================================================================
//
//    �[�x�o�b�t�@�V���h�E
//    Author : Araki Kai                                �쐬�� : 2018/09/24
//
//================================================================================



//======================================================================
//
// �O���[�o���ϐ�
//
//======================================================================

// �ϊ��s��
float4x4 MATRIX_WVP;
float4x4 MATRIX_WLP;
float4x4 MATRIX_WLPB;

// �����o�[�g�g�U���ˏƖ�
float4 LAMBERT_DIFFUSE_LIGHT_VECTOR = {1.0f, 0.0f, 0.0f, 1.0f};
float4 LAMBERT_DIFFUSE_LIGHT_COLOR 	= {1.0f, 1.0f, 1.0f, 1.0f};

// �f�J�[���e�N�X�`��
texture DECALE_TEXTURE;

// �T���v��( �e�N�X�`����ǂݍ��ނƂ��̐ݒ�A�g�p����e�N�X�`����T���v���X�e�[�g�̐ݒ������)
sampler DECALE_SAMPLER = sampler_state{Texture = <DECALE_TEXTURE>;
							     	   MinFilter = LINEAR;
							           MagFilter = LINEAR;
							           MipFilter = NONE;
							     	   AddressU = Clamp;
							     	   AddressV = Clamp;};


// �V���h�E�}�b�v
texture SHADOW_MAP;

// �T���v��( �e�N�X�`����ǂݍ��ނƂ��̐ݒ�A�g�p����e�N�X�`����T���v���X�e�[�g�̐ݒ������)
sampler SHADOW_MAP_SAMPLER = sampler_state{Texture = <SHADOW_MAP>;
							     	       MinFilter = LINEAR;
							               MagFilter = LINEAR;
							               MipFilter = NONE;
							     	       AddressU = Clamp;
							     	       AddressV = Clamp;};


//======================================================================
//
// �\���̐錾
//
//======================================================================

// ���_�V�F�[�_�ւ̓���
struct VsIn_Pass0
{
	float4 position_ : POSITION;
	float3 normal_   : NORMAL;
};

struct VsIn_Pass1
{
	float4 position_ : POSITION;
	float3 normal_	 : NORMAL;
	float2 decal_texture_  : TEXCOORD0;
}


// ���_�V�F�[�_����̏o��(�s�N�Z���V�F�[�_�̓���)
struct VsOut_Pass0
{
	float4 position_      : POSITION; 
	float4 shadow_map_uv_ : TEXCOORD0;
};

struct VsOut_Pass1
{
	float4 position_       : POSITION;
	float4 diffuse_        : COLOR0;
	float4 ambient_		   : COLOR1;
	float4 decale_texture_ : TEXCOORD0;
	float4 shadow_map_uv_  : TEXCOORD1;
	float4 depth_          : TEXCOORD2;
};



//======================================================================
//
// ���_�V�F�[�_��`
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ���_�V�F�[�_�֐�(�p�X0) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

VsOut_Pass0 Vs_Pass0(VsInput_Pass0 input)
{
//------------------------------------------------------------
// ������

	// �o�̓f�[�^�̍쐬
	VsOut_Pass0 output = (VsOut_Pass0)0;


//------------------------------------------------------------
// ���W�ϊ�

	// �ʒu���W��WVP�s��ŕϊ�
	float4 temp_position = mul(input.position_, MATRIX_WVP);


//------------------------------------------------------------
// �o�̓f�[�^�쐬

	// �ʒu���W
	output.position_ = temp_position;

	// ���C�g�ʒu����̋������o�͂���ׂɎˉe��ԍ��W���e�N�X�`�����W�Ƃ���
	// ���̂܂܏o�͂���
	output.shadow_map_uv_ = temp_position;

	return output;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ���_�V�F�[�_�֐�(�p�X1) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

VsOut_Pass1 Vs_Pass1(VsInput_Pass1 input)
{
//------------------------------------------------------------
// ������

	// �o�̓f�[�^�̍쐬
	VsOut_Pass1 output = (VsOut_Pass1)0;


//------------------------------------------------------------
// ���W�ϊ�

	// �ʒu���W��WVP�s��ŕϊ�
	float4 temp_position = mul(input.position_, MATRIX_WVP);


//------------------------------------------------------------
// �o�̓f�[�^�쐬

	// �ʒu���W
	output.position_ = temp_position;

	// �F
	// �����̔䗦��ۑ�
	float ambient_ratio = LAMBERT_DIFFUSE_LIGHT_VECTOR.w;

	// ���C�g�x�N�g���𔽓]
	float4 inverse_light_vector4 = -LAMBERT_DIFFUSE_LIGHT_VECTOR;

	// �F�̌v�Z(���l�����䗦���|�����Ă��܂����߁A���l�͕ʓr���)
	output.diffuse_   = LAMBERT_DIFFUSE_LIGHT_COLOR * max(dot(input.normal_, inverse_light_vector4), 0);
	output.diffuse_.w = LAMBERT_DIFFUSE_LIGHT_COLOR.w;
	output.ambient_   = LAMBERT_DIFFUSE_LIGHT_COLOR * ambient_ratio;
	output.ambient_.w = LAMBERT_DIFFUSE_LIGHT_COLOR.w;

	// �V���h�E�}�b�v
	output.shadow_map_uv_ = mul(input.position_, MATRIX_WLPB);

	// ��r�̂��߂̐[�x�l
	output.depth_ = mul(input.positon_, MATRIX_WLP);

	// �f�J�[���e�N�X�`��
	output_.decale_texture_ = input_.decal_texture_;

	return output;
}



//======================================================================
//
// �s�N�Z���V�F�[�_��`
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �s�N�Z���V�F�[�_�֐�(�p�X0) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

float4 Ps_Pass0(VsOut_Pass0 vs_output) : COLOR
{
	// �`�悷��F�̓��C�g���W����̋����Ƃ���
	float4 ps_output;

	// Z���W��W�l�Ŋ���ƁA0~1�͈̔͂̐[�x�l�ƂȂ�
	ps_output = vs_output.shadow_map_uv.z / vs_output.shadow_map_uv.w;

	return ps_output;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �s�N�Z���V�F�[�_�֐�(�p�X1) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

float4 Ps_Pass1(VsOut_Pass1 vs_output) : COLOR
{
	// tex2Dproj�́A�Y���I�u�W�F�N�g�Ƀe�N�X�`���𓊉e����悤�Ȍ`�Ńe�N�Z�����t�F�b�`���܂�
	//�܂�A�������W�n�Ō����ꍇ�ɁA�Y���̃e�N�Z�����ǂ��Ȃ邩�A���v�Z���Ă���킯�ł�
	float  shadow = tex2Dproj(SHADOW_MAP_SAMPLER, vs_output.shadow_map_uv_).x;
	float4 decale = tex2D(DECALE_SAMPLER, vs_output.decale_texture_)

	float4 color = vs_output.ambient_ + (shadow * vs_output);
	

	return ps_output;
}

//======================================================================
//
// �e�N�j�b�N��`
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �e�N�j�b�N(�����_�����O���@���܂Ƃ߂�����) ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

technique Techique01
{
	pass Pass0
	{
		VertexShader = compile vs_3_0 Vs_Pass0();
		PixelShader  = compile ps_3_0 Ps_Pass0();
	}
}