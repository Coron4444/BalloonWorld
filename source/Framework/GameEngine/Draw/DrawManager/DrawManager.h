//================================================================================
//!	@file	 DrawManager.h
//!	@brief	 �`��}�l�[�W���[Class
//! @details 
//!	@author  Kai Araki									@date 2019/01/19
//================================================================================
#ifndef	_DRAW_MANAGER_H_
#define _DRAW_MANAGER_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "fade.h"
#include "../Camera/Camera.h"
#include "../Camera/CameraState_CrawlUp.h"
#include "../Camera/CameraState_HomingTarget.h"
#include "../Camera/CameraState_Normal.h"



//****************************************
// �N���X�錾
//****************************************
class DrawBase;
class DrawCommonData;
class ShaderManager;
class RenderTargetMain;
class RenderTargetShadowMap;
class MotionBlur;
class RenderTexturePolygon;
class GameObjectBase;



//************************************************************														   
//! @brief   �`��}�l�[�W���[lass
//!
//! @details �o�^����Ă���`����N���X���Ǘ�����Class
//************************************************************
class DrawManager
{
//====================
// �񋓌^��`
//====================
public:
	enum class RenderTargetType
	{
		NONE = -1,
		MAIN,
		SHADOW_MAP,
		MAX
	};


//====================
// �萔
//====================
public:
	static const unsigned DRAW_ARRAY_NUM = 10000;	//!< �z��


//====================
// �ϐ�
//====================
private:
	LimitedPointerArray<DrawBase*, DRAW_ARRAY_NUM> all_draw_;		//!< �S�`��z��
	LimitedPointerArray<DrawBase*, DRAW_ARRAY_NUM> await_add_;		//!< �ǉ��҂��z��
	LimitedPointerArray<DrawBase*, DRAW_ARRAY_NUM> await_release_;	//!< ����҂��z��

	Camera* camera_[(int)RenderTargetType::MAX];				//!< �J�����Q
	Fade* fade_;												//!< �t�F�[�h
	DrawCommonData* common_data_ = nullptr;						//!< ���ʃf�[�^
	ShaderManager* shader_manager_ = nullptr;					//!< �V�F�[�_�[�}�l�[�W��
	RenderTargetMain* render_target_main_ = nullptr;			//!< �����_�[�^�[�Q�b�g���C��
	RenderTargetShadowMap* render_target_shadow_map_ = nullptr;	//!< �����_�[�^�[�Q�b�g�V���h�E�}�b�v
	MotionBlur* motion_blur_ = nullptr;							//!< ���[�V�����u���[
	LPDIRECT3DSURFACE9 back_buffer_surface_ = nullptr;			//!< BackBuffer�T�[�t�F�X
	LPDIRECT3DSURFACE9 back_buffer_stencil_surface_ = nullptr;	//!< BackBuffer�X�e���V���T�[�t�F�X
	D3DVIEWPORT9 back_buffer_view_port_;						//!< BackBuffer�r���[�|�[�g
	RenderTexturePolygon* back_buffer_polygon_ = nullptr;		//!< BackBuffer�p�|���S��
	LPDIRECT3DDEVICE9 device_ = nullptr;						//!< �f�o�C�X


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �`�拤�ʃf�[�^�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval DrawCommonData* �`�拤�ʃf�[�^
	//----------------------------------------
	DrawCommonData* getpDrawCommonData();

	//----------------------------------------
	//! @brief �J�����擾�֐�
	//! @details
	//! @param type �����_�[�^�[�Q�b�g�^�C�v
	//! @retval Camera* �J����
	//----------------------------------------
	Camera* getpCamera(RenderTargetType type);


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init();

	//----------------------------------------
	//! @brief �I���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Uninit();

	//----------------------------------------
	//! @brief �V�[���ύX���̏I���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void UninitWhenChangeScene();

	//----------------------------------------
	//! @brief �X�V�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Update();

	//----------------------------------------
	//! @brief �`��֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Draw();

	//----------------------------------------
	//! @brief �`����N���X�̒ǉ��֐�
	//! @details
	//! @param *draw �`����N���X
	//! @retval void �Ȃ�
	//----------------------------------------
	void AddDrawBaseToArray(DrawBase* draw);

	//----------------------------------------
	//! @brief �`����N���X�̏㏑���֐�
	//! @details
	//! @param *game_object �Q�[���I�u�W�F�N�g
	//! @param *new_draw    �V�K�`����N���X
	//! @retval void �Ȃ�
	//----------------------------------------
	void OverwriteArrayDrawBase(GameObjectBase* game_object,
								DrawBase* new_draw);

	//----------------------------------------
	//! @brief �`����N���X�̉���֐�
	//! @details
	//! @param *draw �`����N���X
	//! @retval void �Ȃ�
	//----------------------------------------
	void ReleaseDrawBaseFromArray(DrawBase* draw);
	
	//----------------------------------------
	//! @brief �t�F�[�h�C���X�^�[�g�֐�
	//! @details
	//! @param type  �^�C�v
	//! @param size  �g�k
	//! @param color �F
	//! @param speed �t�F�[�h���x
	//! @retval void �Ȃ�
	//----------------------------------------
	void StartFadeIn(Fade::Type type, Vec2 size, XColor4 color, float speed);

	//----------------------------------------
	//! @brief �t�F�[�h�A�E�g�X�^�[�g�֐�
	//! @details
	//! @param type  �^�C�v
	//! @param size  �g�k
	//! @param color �F
	//! @param speed �t�F�[�h���x
	//! @retval void �Ȃ�
	//----------------------------------------
	void StartFadeOut(Fade::Type type, Vec2 size, XColor4 color, float speed);

	//----------------------------------------
	//! @brief �t�F�[�h�I���m�F�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval bool �t�F�[�h�I���̗L��
	//----------------------------------------
	bool IsFadeEnd();

	//----------------------------------------
	//! @brief �t�F�[�h�X�e�[�g����֐�
	//! @details
	//! @param state �X�e�[�g
	//! @retval bool �����ƍ����Ă����true
	//----------------------------------------
	bool IsFadeState(Fade::State state);

private:
	//----------------------------------------
	//! @brief �ǉ��҂��z��̒��g��ǉ��֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void AddContentsOfAwaitAddArray();

	//----------------------------------------
	//! @brief ����҂��z��̒��g������֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void ReleaseContentsOfAwaitReleaseArray();

	//----------------------------------------
	//! @brief �S�`����N���X�X�V�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void UpdateAllDrawBase();

	//----------------------------------------
	//! @brief �S�����_�[�^�[�Q�b�g���Z�b�g�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void ResetAllRenderTarget();

	//----------------------------------------
	//! @brief �`����N���X�U�蕪���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void DistributeDrawBase();

	//----------------------------------------
	//! @brief �S�����_�[�^�[�Q�b�g�X�V�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void UpdateAllRenderTarget();

	//----------------------------------------
	//! @brief BackBuffer�`��֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void DrawBackBuffer();

	//----------------------------------------
	//! @brief �t�F�[�h�`��֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void DrawFade();
};



#endif
