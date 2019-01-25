//================================================================================
//
//    �N�b�N�E�g�����X�������˃��f���V�F�[�_�[(�J���[�V�t�g�L)
//    Author : Araki Kai                                �쐬�� : 2018/08/07
//
//================================================================================



//**********************************************************************
//
// �O���[�o���ϐ�
//
//**********************************************************************

// �ϊ��s��
float4x4 MATRIX_WVP;

// �����o�[�g�g�U�Ɩ�(���C�g�x�N�g���̓v���O�����Ő��K��)
float4 LAMBERT_DIFFUSE_LIGHT_VECTOR = {1.0f, 0.0f, 0.0f, 1.0f};
float4 LAMBERT_DIFFUSE_LIGHT_COLOR 	= {1.0f, 1.0f, 1.0f, 1.0f};

// �J�������W
float3 CAMERA_POSITION = {0.0f, 0.0f, 0.0f};



//**********************************************************************
//
// �\���̐錾
//
//**********************************************************************

// ���_�V�F�[�_�ւ̓���
struct Input_VS
{
	float4 position_ : POSITION;
	float4 normal_   : NORMAL;
};


// ���_�V�F�[�_����̏o��(�s�N�Z���V�F�[�_�̓���)
struct Output_VS
{
	float4 position_  : POSITION;
	float4 color_	  : COLOR0;
	float3 normal_	  : TEXCOORD0;
	float3 position3_ : TEXCOORD1;
};



//**********************************************************************
//
// ���_�V�F�[�_��`
//
//**********************************************************************

//================================================================================
//
// [ ���C�����_�V�F�[�_�֐� ]
//
//================================================================================

Output_VS mainVS(Input_VS input)
{
//------------------------------------------------------------
// ������

	// �o�̓f�[�^�̍쐬
	Output_VS output = (Output_VS)0;


//------------------------------------------------------------
// ���W�ϊ�

	// ���W��WVP�s��ŕϊ�
	output.position_ = mul(input.position_, MATRIX_WVP);


//------------------------------------------------------------
// �����o�[�g�g�U�Ɩ�

	// �����̔䗦��ۑ�
	float ambient_ratio = LAMBERT_DIFFUSE_LIGHT_VECTOR.w;

	// ���C�g�x�N�g���𔽓]
	float4 inverse_light_vector4 = -LAMBERT_DIFFUSE_LIGHT_VECTOR;

	// �F�̌v�Z(���l�����䗦���|�����Ă��܂����߁A���l�͕ʓr���)
	output.color_ = LAMBERT_DIFFUSE_LIGHT_COLOR * max(ambient_ratio, dot(input.normal_, inverse_light_vector4));
	output.color_.w = LAMBERT_DIFFUSE_LIGHT_COLOR.w;

	
//------------------------------------------------------------
// �s�N�Z���V�F�[�_�[�ɓn���l�v�Z

	// ���W
	output.position3_ = input.position_.xyz;

	// �@��
	output.normal_ = input.normal_.xyz;

	return output;
}



//**********************************************************************
//
// �s�N�Z���V�F�[�_��`
//
//**********************************************************************

//================================================================================
//
// [ ���C���s�N�Z���V�F�[�_�֐� ]
//
//================================================================================

float4 mainPS(Output_VS input) : COLOR
{
//------------------------------------------------------------
// �N�b�N�E�g�����X��������

	// �@���𐳋K��
	input.normal_ = normalize(input.normal_);

	// ���C�g�x�N�g���𔽓]
	float3 inverse_light_vector3 = -LAMBERT_DIFFUSE_LIGHT_VECTOR;

	// �����x�N�g���̍쐬
	float3 eye_vector = normalize(CAMERA_POSITION - input.position3_);

	// �n�[�t�x�N�g���̍쐬
	float3 half_vector = normalize(inverse_light_vector3 + eye_vector);

	// �e��p�x(cos��)�̎Z�o
	float dot_normal_eye   = dot(input.normal_, eye_vector);
	float dot_normal_half  = dot(input.normal_, half_vector);
	float dot_normal_light = dot(input.normal_, inverse_light_vector3);
	float dot_eye_half     = dot(eye_vector, half_vector);
	float dot_light_half   = dot(inverse_light_vector3, half_vector);

	// Beckmann���z�֐�(�}�C�N���t�@�Z�b�g���z�֐��̈��)�̎Z�o
	const float roughness = 0.3f;		// �r��
	float squaring_dot_normal_half = dot_normal_half * dot_normal_half;
	float beckmann_distribution_function = exp(-(1 - squaring_dot_normal_half) / (squaring_dot_normal_half * roughness * roughness))
												/ (4 * roughness * roughness * squaring_dot_normal_half * squaring_dot_normal_half);

	// �􉽌������̎Z�o
	float geometric_decay_rate = min(1, min((2 * dot_normal_half * dot_normal_eye) / dot_eye_half, (2 * dot_normal_half * dot_normal_light) / dot_eye_half));

	// �t���l�����ˌW��
	const float refraction = 5.0f;		// ���ܗ�(������グ��ƒ��S����̐F�̗̈悪�L���Ȃ�)
	float g = (refraction * refraction) + (dot_light_half * dot_light_half) - 1;
	float g_plus_c  = g + dot_light_half;
	float g_minus_c = g - dot_light_half;
	float cg_plus_cc_minus_1 = dot_light_half * g_plus_c - 1;
	float cg_minus_cc_plus_1 = dot_light_half * g_minus_c + 1;
	float fresnel = 0.5f * ((g_minus_c * g_minus_c) * (1 + (cg_plus_cc_minus_1 * cg_plus_cc_minus_1) / (cg_minus_cc_plus_1 * cg_minus_cc_plus_1))
						/ (g_plus_c * g_plus_c));
	
	// ���_�Ƃقړ����������烉�C�g�𓖂Ă����̃t���l�����ˌW��
	float fresnel0 = ((refraction - 1) * (refraction - 1)) / ((refraction + 1) * (refraction + 1));

	// �����̐F
	float4 light_color = {0.3f, 0.3f, 1.0f, 1.0f};		// ���ˌ��̐F
	float4 color0      = {0.9f * light_color.x,			// ���ʂ���light_color�̐F�̌������������Ƃ��̋��ʔ��ːF
						  0.8f * light_color.y, 
						  0.3f * light_color.z, 
						  1.0f};

	// �J���[�V�t�g���l�������F�̎Z�o
	float color_Shift = color0 + (light_color - color0) * max(0, fresnel - fresnel0) / (1 - fresnel0);

	input.color_ += color_Shift * max(0, (beckmann_distribution_function * geometric_decay_rate * fresnel) / dot_normal_eye);

	return input.color_;
}



//**********************************************************************
//
// �e�N�j�b�N��`
//
//**********************************************************************

//================================================================================
//
// [ �e�N�j�b�N(�����_�����O���@���܂Ƃ߂�����) ]
//
//================================================================================

technique Techique01
{
	pass P0
	{
		VertexShader = compile vs_2_0 mainVS();
		PixelShader  = compile ps_2_0 mainPS();
	}
}