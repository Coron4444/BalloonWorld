//================================================================================
//!	@file	 DrawOrderList.h
//!	@brief	 �`�撍�����X�gClass
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================
#ifndef	_DRAW_ORDER_LIST_H_
#define _DRAW_ORDER_LIST_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "Shader/ShaderManager/ShaderManager.h"



//************************************************************														   
//! @brief   �`�撍�����X�gClass
//!
//! @details �`��Ɋւ��钍�����X�gClass
//************************************************************
class DrawOrderList
{
//====================
// �񋓌^��`
//====================
public:
	// �`��^�C�v
	enum DrawType
	{
		NONE = -1,
		OPACITY,
		TRANSPARENCY,
		TWO_DIMENSIONAL,
		MAX
	};

	
//====================
// �萔
//====================
public:
	static const unsigned RENDER_TARGET_MAIN = 1 << 0;
	static const unsigned RENDER_TARGET_SHADOW_MAP = 1 << 1;


//====================
// �ϐ�
//====================
private:
	DrawType draw_type_ = DrawType::OPACITY;			//!< �`��̎��
	DrawType temp_change_draw_type_ = DrawType::NONE;	//!< �ꎞ�ύX�`��̎��
	ShaderManager::VertexShaderType vertex_shader_type_ = ShaderManager::VertexShaderType::FIXED;	//!< ���_�V�F�[�_�[�^�C�v
	ShaderManager::PixelShaderType pixel_shader_type_ = ShaderManager::PixelShaderType::FIXED;		//!< �s�N�Z���V�F�[�_�[�^�C�v
	BitFlag render_target_flag_;		//!< �����_�[�^�[�Q�b�g�t���O
	bool is_billboard_ = false;			//!< �r���{�[�h�t���O
	bool is_lighting_ = true;			//!< ���C���e�B���O�t���O
	bool is_animation_ = false;			//!< �A�j���[�V�����t���O
	int layer_num_ = 0;					//!< ���C���[��


//====================
// �v���p�e�B
//====================
public:
	//----------------------------------------
	//! @brief ���_�V�F�[�_�[�̎�ގ擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval ShaderManager::VertexShaderType ���_�V�F�[�_�[�̎��
	//----------------------------------------
	ShaderManager::VertexShaderType getVertexShaderType();
	
	//----------------------------------------
	//! @brief ���_�V�F�[�_�[�^�C�v�ݒ�֐�
	//! @details
	//! @param value ���_�V�F�[�_�[�^�C�v
	//! @retval void �Ȃ�
	//----------------------------------------
	void setVertexShaderType(ShaderManager::VertexShaderType value);
	
	//----------------------------------------
	//! @brief �s�N�Z���V�F�[�_�[�̎�ގ擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval ShaderManager::PixelShaderType �s�N�Z���V�F�[�_�[�̎��
	//----------------------------------------
	ShaderManager::PixelShaderType getPixelShaderType();
	
	//----------------------------------------
	//! @brief �s�N�Z���V�F�[�_�[�^�C�v�ݒ�֐�
	//! @details
	//! @param value �s�N�Z���V�F�[�_�[�^�C�v
	//! @retval void �Ȃ�
	//----------------------------------------
	void setPixelShaderType(ShaderManager::PixelShaderType value);
	
	//----------------------------------------
	//! @brief �`��^�C�v�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval DrawType �`��^�C�v
	//----------------------------------------
	DrawType getDrawType();
	
	//----------------------------------------
	//! @brief �`��^�C�v�ݒ�֐�
	//! @details
	//! @param value �`��^�C�v
	//! @retval void �Ȃ�
	//----------------------------------------
	void setDrawType(DrawType value);

	//----------------------------------------
	//! @brief �ꎞ�ύX�`��^�C�v�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval DrawType �ꎞ�ύX�`��^�C�v
	//----------------------------------------
	DrawType getTempChangeDrawType();

	//----------------------------------------
	//! @brief �ꎞ�ύX�`��^�C�v�ݒ�֐�
	//! @details
	//! @param value �ꎞ�ύX�`��^�C�v
	//! @retval void �Ȃ�
	//----------------------------------------
	void setTempChangeDrawType(DrawType value);
	
	//----------------------------------------
	//! @brief �����_�[�^�[�Q�b�g�t���O�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval BitFlag* �����_�[�^�[�Q�b�g�t���O
	//----------------------------------------
	BitFlag* getpRenderTargetFlag();
	
	//----------------------------------------
	//! @brief �r���{�[�h�t���O�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval bool �r���{�[�h�t���O
	//----------------------------------------
	bool getIsBillboard();
	
	//----------------------------------------
	//! @brief �r���{�[�h�t���O�ݒ�֐�
	//! @details
	//! @param value �r���{�[�h�t���O
	//! @retval void �Ȃ�
	//----------------------------------------
	void setIsBillboard(bool value);
	
	//----------------------------------------
	//! @brief ���C�e�B���O�t���O�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval bool ���C�e�B���O�t���O
	//----------------------------------------
	bool getIsLighting();
	
	//----------------------------------------
	//! @brief ���C�e�B���O�t���O�ݒ�֐�
	//! @details
	//! @param value ���C�e�B���O�t���O
	//! @retval void �Ȃ�
	//----------------------------------------
	void setIsLighting(bool value);
	
	//----------------------------------------
	//! @brief �A�j���[�V�����t���O�擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval bool �A�j���[�V�����t���O
	//----------------------------------------
	bool getIsAnimation();

	//----------------------------------------
	//! @brief �A�j���[�V�����t���O�ݒ�֐�
	//! @details
	//! @param value �A�j���[�V�����t���O
	//! @retval void �Ȃ�
	//----------------------------------------
	void setIsAnimation(bool value);

	//----------------------------------------
	//! @brief ���C���[���擾�֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval int ���C���[��
	//----------------------------------------
	int getLayerNum();
	
	//----------------------------------------
	//! @brief ���C���[���ݒ�֐�
	//! @details
	//! @param value ���C���[��
	//! @retval void �Ȃ�
	//----------------------------------------
	void setLayerNum(int value);
};



#endif