//================================================================================
//
//    �o���v�}�b�s���O
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

// �f�J�[���e�N�X�`��
texture DECALE_TEXTURE;

// �T���v��( �e�N�X�`����ǂݍ��ނƂ��̐ݒ�A�g�p����e�N�X�`����T���v���X�e�[�g�̐ݒ������)
sampler DECALE_SAMPLER = sampler_state{Texture = <DECALE_TEXTURE>;
							     	   MinFilter = LINEAR;
							           MagFilter = LINEAR;
							           MipFilter = NONE;
							     	   AddressU = Clamp;
							     	   AddressV = Clamp;};

// �@���}�b�v
texture NORMAL_TEXTURE;
// �T���v��( �e�N�X�`����ǂݍ��ނƂ��̐ݒ�A�g�p����e�N�X�`����T���v���X�e�[�g�̐ݒ������)
sampler NORMAL_SAMPLER = sampler_state{Texture = <NORMAL_TEXTURE>;
							     	   MinFilter = LINEAR;
							    	   MagFilter = LINEAR;
							     	   MipFilter = NONE;
							     	   AddressU = Clamp;
							     	   AddressV = Clamp;};


//**********************************************************************
//
// �\���̐錾
//
//**********************************************************************

// ���_�V�F�[�_�ւ̓���
struct Input_VS
{
	float4 position_ : POSITION;	// ���[�J�����W
	float3 normal_   : NORMAL;		// �@���x�N�g��
	float3 tangent_  : TANGENT0;	// �ڃx�N�g��
	float2 texcoord_ : TEXCOORD0;	// �@���x�N�g��
};


// ���_�V�F�[�_����̏o��(�s�N�Z���V�F�[�_�̓���)
struct Output_VS
{
	float4 position_     : POSITION;
	float4 color_	     : COLOR0;
	float2 texcoord_     : TEXCOORD0;	// �@���x�N�g��
	float3 eye_vector_   : TEXCOORD1;
	float3 light_vector_ : TEXCOORD2;
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
// ���b�V���̐F

	output.color_ = LAMBERT_DIFFUSE_LIGHT_COLOR;

	
//------------------------------------------------------------
// �f�J�[���p�e�N�X�`�����W

	output.texcoord_ = input.texcoord_;


//------------------------------------------------------------
// ���_��ԍ��W�n�̊��x�N�g���̌v�Z

	// �@���x�N�g��
	float3 normal = input.normal_;
	
	// �ڃx�N�g��
	float3 tangent = input.tangent_;

	// �]�@���̎Z�o
	float3 binormal = cross(normal, tangent);


//------------------------------------------------------------
// �����x�N�g���ƃ��C�g�x�N�g���𒸓_��ԍ��W�n�ɕϊ�

	// �����x�N�g��
	float3 eye_vector = CAMERA_POSITION - input.position_.xyz;
	output.eye_vector_.x = dot(eye_vector, tangent);
	output.eye_vector_.y = dot(eye_vector, binormal);
	output.eye_vector_.z = dot(eye_vector, normal);

	// ���C�g�x�N�g��
	float3 light_vector = -LAMBERT_DIFFUSE_LIGHT_VECTOR.xyz;
	output.light_vector_.x = dot(light_vector, tangent);
	output.light_vector_.y = dot(light_vector, binormal);
	output.light_vector_.z = dot(light_vector, normal);

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
// �o���v�}�b�s���O

	// �@���}�b�v����̖@��(�e�N�X�`����0~1�ׁ̈A2�{����-1.0f���邱�Ƃ�-1~1�͈̔͂ɂ���)
	float normal = 2.0f * tex2D(NORMAL_SAMPLER, input.texcoord_).xyz - 1.0f;

	// ���C�g�x�N�g��
	float3 light_vector = normalize(input.light_vector_);

	// ���˃x�N�g��
	float3 refraction_vector = reflect(-normalize(input.eye_vector_), normal);

	// �����̋���
	float ambient = -LAMBERT_DIFFUSE_LIGHT_VECTOR.w;

	//return input.color_;//tex2D(DECALE_SAMPLER, input.texcoord_);

	input.color_ = input.color_ * tex2D(DECALE_SAMPLER, input.texcoord_)			// �����o�[�g�Ɩ��ɂ͒��_�F�ƃe�N�X�`���̐F����������
			* (max(0, dot(normal, light_vector)) + ambient)					
			+ 0.3f * pow(max(0, dot(refraction_vector, light_vector)), 8);

	input.color_.w = 1.0f;
	return input.color_;
//	return input.color_ * tex2D(DECALE_SAMPLER, input.texcoord_)			// �����o�[�g�Ɩ��ɂ͒��_�F�ƃe�N�X�`���̐F����������
//			* (max(0, dot(normal, light_vector)) + ambient)					
//			+ 0.3f * pow(max(0, dot(refraction_vector, light_vector)), 8);	// Phong���ʔ��ˌ�
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