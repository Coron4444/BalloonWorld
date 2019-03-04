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
#include "../DrawNull.h"



//****************************************
// �N���X�錾
//****************************************
class PlanePolygon;
class Transform;
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
	enum class Type
	{
		NONE = -1,
		NORMAL,
		TRANSITION_01,
		MAX
	};

	enum class State
	{
		NONE = -1,
		FADE_IN,
		FADE_OUT,
		MAX
	};


//====================
// �萔
//====================
public:
	static const std::string TEXTURE_NAME_LOAD;				//!< Load�e�N�X�`����
	static const std::string TEXTURE_NAME_TRANSITION_01;	//!< �e�N�X�`����


//====================
// �ϐ�
//====================
private:
	Type type_;										//!< �^�C�v
	State state_;									//!< �X�e�[�g
	PlanePolygon* plane_polygon_ = nullptr;			//!< �|���S��
	Transform* transform_ = nullptr;				//!< ���
	TextureObject* load_texture_ = nullptr;			//!< Load�e�N�X�`���I�u�W�F�N�g
	TextureObject* transition01_texture_ = nullptr;	//!< �e�N�X�`���I�u�W�F�N�g
	XColor4 color_;									//!< �F
	float speed_;									//!< �t�F�[�h���x
	bool end_flag_ = true;							//!< �I���t���O
	Interpolation<float> inter_container_;			//!< ��ԃR���e�i
	Interpolation<float>::Iterator inter_iter_;		//!< ��ԃC�e���[�^


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
	Type* getpType();

	//----------------------------------------
	//! @brief �X�e�[�g�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval State* �X�e�[�g
	//----------------------------------------
	State* getpState();

	//----------------------------------------
	//! @brief �I���t���O�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval bool �I���t���O
	//----------------------------------------
	bool getpEndFlag();

	//----------------------------------------
	//! @brief ��Ԏ擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval Transform* ���
	//----------------------------------------
	Transform* getpTransform();

	//----------------------------------------
	//! @brief �f�B�q���[�Y�e�N�X�`���擾�֐�
	//! @details
	//! @param object_index �I�u�W�F�N�g�C���f�b�N�X
	//! @param mesh_index   ���b�V���C���f�b�N�X
	//! @retval LPDIRECT3DTEXTURE9 �f�B�q���[�Y�e�N�X�`��
	//----------------------------------------
	LPDIRECT3DTEXTURE9 getpDiffuseTexture(unsigned object_index,
										  unsigned mesh_index) override;


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

	//----------------------------------------
	//! @brief �X�^�[�g�֐�
	//! @details
	//! @param type  �^�C�v
	//! @param state �X�e�[�g
	//! @param size  �g�k
	//! @param color �F
	//! @param speed �t�F�[�h���x
	//! @retval void �Ȃ�
	//----------------------------------------
	void Start(Type type, State state, Vec2 size, XColor4 color, float speed);
};



#endif