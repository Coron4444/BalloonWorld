//================================================================================
//
//    �[�x�o�b�t�@�V���h�E�I�u�W�F�N�g�N���X
//    Author : Araki Kai                                �쐬�� : 2018/09/24
//
//================================================================================

#ifndef	_DEPTH_BUFFER_SHADOW_OBJECT_H_
#define _DEPTH_BUFFER_SHADOW_OBJECT_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include <ResourceManager\ResourceManager.h>



//======================================================================
//
// �N���X�錾
//
//======================================================================

class Camera;
class DrawComponent;



/*****************************************************************************//**
* @brief
* �[�x�o�b�t�@�V���h�E�I�u�W�F�N�g�N���X
*
* �V���h�E�}�b�v��p�����e������
* �����_�����O�񐔁F2��
* 1��� : �V���h�E�}�b�v�̍쐬
* 2��� : �V���h�E�}�b�v�̐[�x�l�ƃI�u�W�F�N�g�̐[�x�l���r���Ȃ��烌���_�����O
*********************************************************************************/

class DepthBufferShadowObject
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �萔
	static const char* EFFECT_PATH;
	static const D3DVERTEXELEMENT9 DECLARATION[];
	static const Vec2 SHADOW_MAP_SIZE;

//------------------------------------------------------------
private :
	// �f�t�H���g�R���X�g���N�^
	DepthBufferShadowObject() = delete;

	// �R�s�[�R���X�g���N�^
	DepthBufferShadowObject(const DepthBufferShadowObject& class_name) = delete;

	// ������Z�q�̃I�[�o�[���[�h
	DepthBufferShadowObject& operator = (const DepthBufferShadowObject& class_name) = delete;

	
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// ���J�����o�֐�
	static void Init();
	static void Uninit();

	static void SetRenderTarget();
	static void SetOldRenderTarget();
	static void Draw_Pass0(DrawComponent* draw_component, Camera* camera);
	static void Draw_Pass1(DrawComponent* draw_component, Camera* camera);


//------------------------------------------------------------
private :
	// �����o�ϐ�	
	static LPDIRECT3DDEVICE9 device_;

	// �v�Z�p
	static D3DXMATRIX math_matrix_;

	// ���_�錾�I�u�W�F�N�g
	static IDirect3DVertexDeclaration9* declaration_object_;

	// �V���h�E�}�b�v
	static LPDIRECT3DTEXTURE9 shadow_map_;
	static LPDIRECT3DSURFACE9 shadow_map_render_target_surface_;
	static LPDIRECT3DSURFACE9 shadow_map_depth_buffer_surface_;
	static D3DVIEWPORT9       shadow_map_view_port_;
	static Camera             shadow_map_camera_;


	// ���̃����_�����O�^�[�Q�b�g
	static LPDIRECT3DSURFACE9 old_render_target_surface_;
	static LPDIRECT3DSURFACE9 old_depth_buffer_surface_;
	static D3DVIEWPORT9       old_view_port_;



	// �G�t�F�N�g�t�@�C���n���h���Q
	static LPD3DXEFFECT effect_;
	static D3DXHANDLE   technique_;
	static D3DXHANDLE   matrix_WVP_;
	static D3DXHANDLE   lambert_diffuse_light_vector_;
	static D3DXHANDLE   lambert_diffuse_light_color_;
	static D3DXHANDLE   camera_position_;
	static D3DXHANDLE   decale_texture_;
	static D3DXHANDLE   normal_texture_;

};



#endif
