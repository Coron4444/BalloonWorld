//================================================================================
//!	@file	 Fade.h
//!	@brief	 �t�F�[�hClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================
#ifndef	_FADE_H_
#define _FADE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <string>

#include <Component/Draw/DrawNull/DrawNull.h>
#include <Vector3D.h>
#include <Transform\Transform.h>
#include <Polygon\PlanePolygon\PlanePolygon.h>



//****************************************
// �N���X�錾
//****************************************
class PlanePolygon;
class TextureObject;


//************************************************************														   
//! @brief   �t�F�[�hClass
//!
//! @details �t�F�[�h��Class
//************************************************************
class Fade : public DrawNull
{
//====================
// �񋓌^��`
//====================
public:
	enum Type
	{
		TYPE_NONE = -1,
		TYPE_NORMAL,
		TYPE_TRANSITION_01,
		TYPE_MAX
	};

	enum State
	{
		STATE_NONE = -1,
		STATE_FADE_IN,
		STATE_FADE_OUT,
		STATE_MAX
	};


//====================
// �萔
//====================
public:
	static const std::string TEXTURE_PATH;					//!< �e�N�X�`���p�X
	static const std::string TEXTURE_NAME_TRANSITION_01;	//!< �e�N�X�`����


//====================
// �ϐ�
//====================
private:
	Type type_;										//!< �^�C�v
	State state_;									//!< �X�e�[�g
	PlanePolygon plane_polygon_;					//!< �|���S��
	Transform transform_;							//!< ���
	TextureObject* transition01_texture_ = nullptr;	//!< �e�N�X�`���I�u�W�F�N�g
	XColor4 color_;									//!< �F
	float speed_;									//!< �t�F�[�h���x
	bool end_flag_;									//!< �I���t���O


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief �s��擾�֐�
	//! @details
	//! @param object_index �I�u�W�F�N�g�C���f�b�N�X
	//! @retval MATRIX* �s��
	//----------------------------------------
	MATRIX* getpMatrix(unsigned object_index) override;

	//----------------------------------------
	//! @brief �}�e���A���擾�֐�
	//! @details
	//! @param object_index �I�u�W�F�N�g�C���f�b�N�X
	//! @param mesh_index   ���b�V���C���f�b�N�X
	//! @retval D3DMATERIAL9* �}�e���A��
	//----------------------------------------
	D3DMATERIAL9* getpMaterial(unsigned object_index, unsigned mesh_index) override;

	//----------------------------------------
	//! @brief �^�C�v�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Type* �^�C�v
	//----------------------------------------
	const Type* getpType() const;
	
	//----------------------------------------
	//! @brief �X�e�[�g�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval State* �X�e�[�g
	//----------------------------------------
	const State* getpState() const;
	
	//----------------------------------------
	//! @brief �I���t���O�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval bool �I���t���O
	//----------------------------------------
	bool getpEndFlag() const;
	
	//----------------------------------------
	//! @brief ��Ԏ擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Transform* ���
	//----------------------------------------
	Transform* getpTransform();
	
	//----------------------------------------
	//! @brief �e�N�X�`���I�u�W�F�N�g�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval TextureObject* �e�N�X�`���I�u�W�F�N�g
	//----------------------------------------
	TextureObject* getpTransition01Object();


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param type  �^�C�v
	//! @param state �X�e�[�g
	//! @param size  �g�k
	//! @param color �F
	//! @param speed �t�F�[�h���x
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init(Type type, State state, Vec2 size, XColor4 color, float speed);

	//----------------------------------------
	//! @brief �I���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Uninit() override;

	//----------------------------------------
	//! @brief �X�V�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Update() override;

	//----------------------------------------
	//! @brief �`��֐�
	//! @details
	//! @param object_index �I�u�W�F�N�g�C���f�b�N�X
	//! @param mesh_index   ���b�V���C���f�b�N�X
	//! @retval void �Ȃ�
	//----------------------------------------
	void Draw(unsigned object_index, unsigned mesh_index) override;
};



#endif