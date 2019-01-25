//================================================================================
//
//    �[�x�o�b�t�@�V���h�E�I�u�W�F�N�g�N���X
//    Author : Araki Kai                                �쐬�� : 2018/09/24
//
//================================================================================



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include <assert.h>

#include "DepthBufferShadowObject.h"

#include <main.h>
#include <ComponentManager\DrawComponentManager\Camera\Camera.h>
#include <Component/DrawComponent/DrawComponent.h>
#include <GameObjectOrigin/GameObjectOrigin.h>

#include <Transform\Transform.h>



//======================================================================
//
// �萔��`
//
//======================================================================

const char* DepthBufferShadowObject::EFFECT_PATH = "resource/HLSL/Effect/obj/BumpMapping.obj";
const D3DVERTEXELEMENT9 DepthBufferShadowObject::DECLARATION[] 
	= {{0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
	   {0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0},
	   D3DDECL_END()
      };

const Vec2 DepthBufferShadowObject::SHADOW_MAP_SIZE(SCREEN_WIDTH, SCREEN_HEIGHT);


//======================================================================
//
// �ÓI�����o�ϐ���`
//
//======================================================================

LPDIRECT3DDEVICE9 DepthBufferShadowObject::device_;

D3DXMATRIX DepthBufferShadowObject::math_matrix_;

IDirect3DVertexDeclaration9* DepthBufferShadowObject::declaration_object_;

LPDIRECT3DTEXTURE9 DepthBufferShadowObject::shadow_map_;
LPDIRECT3DSURFACE9 DepthBufferShadowObject::shadow_map_render_target_surface_;
LPDIRECT3DSURFACE9 DepthBufferShadowObject::shadow_map_depth_buffer_surface_;
D3DVIEWPORT9	   DepthBufferShadowObject::shadow_map_view_port_;
Camera			   DepthBufferShadowObject::shadow_map_camera_(nullptr, Camera::Type::NONE);

LPDIRECT3DSURFACE9 DepthBufferShadowObject::old_render_target_surface_;
LPDIRECT3DSURFACE9 DepthBufferShadowObject::old_depth_buffer_surface_;
D3DVIEWPORT9	   DepthBufferShadowObject::old_view_port_;

LPD3DXEFFECT DepthBufferShadowObject::effect_;
D3DXHANDLE   DepthBufferShadowObject::technique_;
D3DXHANDLE   DepthBufferShadowObject::matrix_WVP_;
D3DXHANDLE   DepthBufferShadowObject::lambert_diffuse_light_vector_;
D3DXHANDLE   DepthBufferShadowObject::lambert_diffuse_light_color_;
D3DXHANDLE   DepthBufferShadowObject::camera_position_;
D3DXHANDLE   DepthBufferShadowObject::decale_texture_;
D3DXHANDLE   DepthBufferShadowObject::normal_texture_;




//======================================================================
//
// �ÓI�����o�֐���`
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void DepthBufferShadowObject::Init()
{
	// �f�o�C�X�̎擾
	device_ = RendererDirectX9::GetDevice();
	assert(device_ != nullptr && "�f�o�C�X�̎擾�Ɏ��s(FixedPipelineObject.cpp)");

	// ���_�錾�I�u�W�F�N�g�̐���
	HRESULT hr = device_->CreateVertexDeclaration(DECLARATION, &declaration_object_);
	

#ifdef _DEBUG
	assert(SUCCEEDED(hr) && "���_�錾�I�u�W�F�N�g�̐����Ɏ��s(FixedPipelineObject.cpp)");
#else
	hr = hr;
#endif

	// �G�t�F�N�g�t�@�C���̓ǂݍ���
	FILE* file_pointer = nullptr;
	file_pointer = fopen(EFFECT_PATH, "rb");
	if (file_pointer == nullptr)
	{
		MessageBox(nullptr, "�G�t�F�N�g�t�@�C���̓ǂݍ��݂Ɏ��s", "Error(DepthBufferShadowObject.cpp)", MB_OK);
	}

	// �t�@�C���|�C���^�[�̈ʒu����t�@�C���T�C�Y���擾����(�o�C�i���\�t�@�C���ł��邽�ߗL��)
	fseek(file_pointer, 0, SEEK_END);
	long file_size = ftell(file_pointer);
	fseek(file_pointer, 0, SEEK_SET);
	
	// �t�@�C���̓ǂݍ���
	char* file_data = new char[file_size];
	fread(file_data, file_size, sizeof(char), file_pointer);
	fclose(file_pointer);

	// �G�t�F�N�g�t�@�C���n���h���̎擾
	LPD3DXBUFFER error_message = nullptr;
	HRESULT h_result = D3DXCreateEffect(device_,			// �f�o�C�X
										file_data,			// �R���p�C���ς�fx�f�[�^
										file_size,			// �R���p�C���ς�fx�f�[�^�̃T�C�Y
										nullptr,			// �v���v���Z�b�T��`�ւ̃|�C���^
										nullptr,			// �I�v�V�����̃C���^�t�F�[�X�ւ̃|�C���^
										0,					// D3DXSHADER�Ŏ��ʂ����R���p�C���I�v�V����
										nullptr,			// ���L�����Ŏg��ID3DXEffectPool�I�u�W�F�N�g�ւ̃|�C���^
										&effect_,			// �R���p�C�����ꂽ�G�t�F�N�g�̊i�[��
										&error_message);	// �R���p�C���G���[�ꗗ�̊i�[��
	if (FAILED(h_result))
	{
		MessageBox(nullptr, "�G�t�F�N�g�t�@�C���n���h���̎擾�Ɏ��s", "Error(DepthBufferShadowObject.cpp)", MB_OK);
	}

	// �e�N�j�b�N�n���h���̎擾
	technique_  = effect_->GetTechniqueByName("Techique01");
	
	// �萔�n���h���̎擾
	matrix_WVP_					  = effect_->GetParameterByName(NULL, "MATRIX_WVP");
	lambert_diffuse_light_vector_ = effect_->GetParameterByName(NULL, "LAMBERT_DIFFUSE_LIGHT_VECTOR");
	lambert_diffuse_light_color_  = effect_->GetParameterByName(NULL, "LAMBERT_DIFFUSE_LIGHT_COLOR");
	camera_position_			  = effect_->GetParameterByName(NULL, "CAMERA_POSITION");
	decale_texture_			      = effect_->GetParameterByName(NULL, "DECALE_TEXTURE");
	normal_texture_			      = effect_->GetParameterByName(NULL, "NORMAL_TEXTURE");

	// �e��J��
	SafeReleaseDirectX9(&error_message);
	delete[] file_data;

	// �V���h�E�}�b�v�̍쐬
	h_result = device_->CreateTexture(SHADOW_MAP_SIZE.x, SHADOW_MAP_SIZE.y,
									  1,
									  D3DUSAGE_RENDERTARGET,
									  D3DFMT_A8R8G8B8,
									  D3DPOOL_DEFAULT,
									  &shadow_map_,
									  NULL);

	if (FAILED(h_result))
	{
		MessageBox(nullptr, "�V���h�E�}�b�v�̍쐬�Ɏ��s", "Error(DepthBufferShadowObject.cpp)", MB_OK);
	}

	// �V���h�E�}�b�v���烌���_�����O�^�[�Q�b�g�T�[�t�F�X���擾����
	h_result = shadow_map_->GetSurfaceLevel(0, &shadow_map_render_target_surface_);

	if (FAILED(h_result))
	{
		MessageBox(nullptr, "�V���h�E�}�b�v�̃T�[�t�F�X�擾�Ɏ��s", "Error(DepthBufferShadowObject.cpp)", MB_OK);
	}
	
	// �V���h�E�}�b�v�Ɠ����傫�������[�x�o�b�t�@�T�[�t�F�X�̍쐬(�[�x�o�b�t�@����������Z�e�X�g���L�����Z������邽��)
	h_result = device_->CreateDepthStencilSurface(SHADOW_MAP_SIZE.x, SHADOW_MAP_SIZE.y,
												  D3DFMT_D16,								
												  D3DMULTISAMPLE_NONE,
												  0,
												  TRUE,
												  &shadow_map_depth_buffer_surface_,		
												  NULL);

	if (FAILED(h_result))
	{
		MessageBox(nullptr, "�V���h�E�}�b�v�̐[�x�o�b�t�@�T�[�t�F�X�̍쐬�Ɏ��s", "Error(DepthBufferShadowObject.cpp)", MB_OK);
	}

	// �r���[�|�[�g�̍쐬(��ʂ̑傫���ƈႤ�ꍇ�͕K�v)
	shadow_map_view_port_ = {0, 0,									// ������W
							 SHADOW_MAP_SIZE.x, SHADOW_MAP_SIZE.y,	// ������
							 0.0f, 1.0f};							// �O�ʁA���

	// ���̃����_�[�^�[�Q�b�g���擾
	device_->GetRenderTarget(0, &old_render_target_surface_);
	device_->GetDepthStencilSurface(&old_depth_buffer_surface_);
	device_->GetViewport(&old_view_port_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �I�������֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void DepthBufferShadowObject::Uninit()
{
	// �e��J��
	SafeReleaseDirectX9(&effect_);
	SafeReleaseDirectX9(&shadow_map_);
	SafeReleaseDirectX9(&shadow_map_render_target_surface_);
	SafeReleaseDirectX9(&shadow_map_render_target_surface_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �����_�[�^�[�Q�b�g�ݒ�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void DepthBufferShadowObject::SetRenderTarget()
{
	// �����_�[�^�[�Q�b�g�̕ύX
	device_->SetRenderTarget(0, shadow_map_render_target_surface_);
	device_->SetDepthStencilSurface(shadow_map_depth_buffer_surface_);
	device_->SetViewport(&shadow_map_view_port_);

	// �V���h�E�}�b�v�̃N���A
	device_->Clear(0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(1, 1, 1, 1),
		1.0f,
		0);

	// ���C�g�������猩���ˉe��Ԃւ̍s��
	*shadow_map_camera_.GetPositon() = {10.0f, 10.0f, 0.0f};
	shadow_map_camera_.CreateViewMatrix();
	shadow_map_camera_.CreateProjectionMatrix(0.25f * D3DX_PI, 1.0f, 5.0f, 12.0f);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �Â������_�[�^�[�Q�b�g�ݒ�֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void DepthBufferShadowObject::SetOldRenderTarget()
{
	// �����_�[�^�[�Q�b�g�̕ύX
	device_->SetRenderTarget(0, old_render_target_surface_);
	device_->SetDepthStencilSurface(old_depth_buffer_surface_);
	device_->SetViewport(&old_view_port_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �`��֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void DepthBufferShadowObject::Draw_Pass0(DrawComponent* draw_component, Camera* camera)
{	
	// �e�N�j�b�N�ݒ�
	effect_->SetTechnique(technique_);
	
	// �V�F�[�_�[�ł̃����_�����O�J�n
	effect_->Begin(nullptr, 0);
	
	// �p�X��ݒ�
	effect_->BeginPass(0);

	// ���_�錾
	device_->SetVertexDeclaration(declaration_object_);
	
	// ���[���h�ϊ��s��(WVP)���Z�b�g
	D3DXMatrixMultiply(&math_matrix_, draw_component->GetGameObjectOrigin()->GetTransform()->GetWorldMatrix(), shadow_map_camera_.GetViewMatrix());
	D3DXMatrixMultiply(&math_matrix_, &math_matrix_, shadow_map_camera_.GetProjectionMatrix());
	effect_->SetMatrix(matrix_WVP_, &math_matrix_);

	// ���b�V�������`��
	Vec4 temp_vector;
	for (unsigned i = 0; i < draw_component->GetMeshNum(); i++)
	{
		// �V�F�[�_�[�̐ݒ�m��
		effect_->CommitChanges();
		
		// �`��
		draw_component->Draw(i);
	}
	
	
	// �p�X������
	effect_->EndPass();

	// �V�F�[�_�[�ł̃����_�����O�I��
	effect_->End();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ �`��֐� ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void DepthBufferShadowObject::Draw_Pass0(DrawComponent* draw_component, Camera* camera)
{
	// �e�N�j�b�N�ݒ�
	effect_->SetTechnique(technique_);

	// �V�F�[�_�[�ł̃����_�����O�J�n
	effect_->Begin(nullptr, 0);

	// �p�X��ݒ�
	effect_->BeginPass(0);

	// �`��

	// ���[���h�ϊ��s��(WVP)���Z�b�g
	D3DXMatrixMultiply(&math_matrix_, draw_component->GetGameObjectOrigin()->GetTransform()->GetWorldMatrix(), camera->GetViewMatrix());
	D3DXMatrixMultiply(&math_matrix_, &math_matrix_, camera->GetProjectionMatrix());
	effect_->SetMatrix(matrix_WVP_, &math_matrix_);

	// ���C�g�������Z�b�g
	D3DXMatrixIdentity(&math_matrix_);
	Vec4 light_position(0.5f, -1.0f, 0.8f, 0.0f);
	D3DXMatrixInverse(&math_matrix_, nullptr, draw_component->GetGameObjectOrigin()->GetTransform()->GetWorldMatrix());
	D3DXVec4Transform(&light_position, &light_position, &math_matrix_);
	D3DXVec3Normalize((Vec3*)&light_position, (Vec3*)&light_position);
	light_position.w = -0.7f;		// �����̔䗦
	effect_->SetVector(lambert_diffuse_light_vector_, &light_position);

	// ���_�̐ݒ�(�I�u�W�F�N�g���Ƃ̃��[�J�����W�ł̃J�����̍��W���擾����)
	D3DXMatrixIdentity(&math_matrix_);
	D3DXMatrixMultiply(&math_matrix_, draw_component->GetGameObjectOrigin()->GetTransform()->GetWorldMatrix(), camera->GetViewMatrix());
	D3DXMatrixInverse(&math_matrix_, nullptr, &math_matrix_);
	Vec4 object_local_camera_position(0.0f, 0.0f, 0.0f, 1.0f);
	D3DXVec4Transform(&object_local_camera_position, &object_local_camera_position, &math_matrix_);
	effect_->SetVector(camera_position_, &object_local_camera_position);

	// ���_�錾
	device_->SetVertexDeclaration(declaration_object_);

	// ���b�V�������`��
	Vec4 temp_vector;
	for (unsigned i = 0; i < draw_component->GetMeshNum(); i++)
	{
		// �f�B�q���[�Y�F�̐ݒ�
		temp_vector.x = draw_component->GetMaterial(i)->Diffuse.r;
		temp_vector.y = draw_component->GetMaterial(i)->Diffuse.g;
		temp_vector.z = draw_component->GetMaterial(i)->Diffuse.b;
		temp_vector.w = draw_component->GetMaterial(i)->Diffuse.a;
		effect_->SetVector(lambert_diffuse_light_color_, &temp_vector);

		// �f�J�[���e�N�X�`���̐ݒ�
		LPDIRECT3DTEXTURE9 temp = draw_component->GetDecaleTexture(i);
		temp = temp;
		effect_->SetTexture(decale_texture_, temp);

		// �@���}�b�v�̐ݒ�
		effect_->SetTexture(normal_texture_, draw_component->GetNormalTexture(i));

		// �V�F�[�_�[�̐ݒ�m��
		effect_->CommitChanges();

		// �`��
		draw_component->Draw(i);
	}

	// �p�X������
	effect_->EndPass();

	// �V�F�[�_�[�ł̃����_�����O�I��
	effect_->End();
}