//================================================================================
//!	@file	 ShaderManager.h
//!	@brief	 �V�F�[�_�[�}�l�[�W��Class
//! @details 
//!	@author  Kai Araki									@date 2019/01/19
//================================================================================
#ifndef	_SHADER_MANAGER_H_
#define _SHADER_MANAGER_H_



//****************************************
// �N���X�錾
//****************************************
class DrawBase;
class Camera;
class DrawCommonData;
class VertexShaderBase;
class PixelShaderBase;



//************************************************************														   
//! @brief   �V�F�[�_�[�}�l�[�W��Class
//!
//! @details �V�F�[�_�[�̃}�l�[�W��Class
//************************************************************
class ShaderManager
{
//==============================
// �񋓌^��`
//==============================
public:
	enum class VertexShaderType
	{
		NONE = -1,
		FIXED,
		ANIMATED_DEFAULT,
		BLINN_PHONG,
		BUMP_MAPPING,
		COOK_TORRANCE,
		MAX
	};

	enum class PixelShaderType
	{
		NONE = -1,
		FIXED,
		DEFAULT,
		BLINN_PHONG,
		BUMP_MAPPING,
		COOK_TORRANCE,
		MAX
	};


//====================
// �ϐ�
//====================
private:
	VertexShaderBase* vertex_shader_[(int)VertexShaderType::MAX] = {nullptr};	//!< ���_�V�F�[�_�[
	PixelShaderBase* pixel_shader_[(int)PixelShaderType::MAX] = {nullptr};		//!< �s�N�Z���V�F�[�_�[
	VertexShaderType forced_vertex_;			//!< �������_�V�F�[�_�[�^�C�v
	PixelShaderType forced_pixel_;				//!< �����s�N�Z���V�F�[�_�[�^�C�v
	

//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �������֐�
	//! @details
	//! @param *common_data �`�拤�ʃf�[�^
	//! @retval void �Ȃ�
	//----------------------------------------
	void Init(DrawCommonData* common_data);

	//----------------------------------------
	//! @brief �I���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Uninit();

	//----------------------------------------
	//! @brief �f�o�C�X�ɃV�F�[�_�[�ݒ�֐�
	//! @details
	//! @param *draw          �`����N���X
	//! @param forced_vertex_ �������_�V�F�[�_�[�^�C�v
	//! @param forced_pixel_  �����s�N�Z���V�F�[�_�[�^�C�v
	//! @retval void �Ȃ�
	//----------------------------------------
	void ShaderSetToDevice(DrawBase* draw,
						   VertexShaderType forced_vertex,
						   PixelShaderType forced_pixel);

	//----------------------------------------
	//! @brief �I�u�W�F�N�g�ݒ�֐�
	//! @details
	//! @param *draw		�`����N���X
	//! @param *camera		�J����
	//! @param object_index	�`��I�u�W�F�N�g�C���f�b�N�X
	//! @retval void �Ȃ�
	//----------------------------------------
	void ObjectSetting(DrawBase* draw, Camera* camera, unsigned object_index);

	//----------------------------------------
	//! @brief ���b�V���ݒ�֐�
	//! @details
	//! @param *draw		�`����N���X
	//! @param *camera		�J����
	//! @param object_index	�`��I�u�W�F�N�g�C���f�b�N�X
	//! @param mesh_index	���b�V���C���f�b�N�X
	//! @retval void �Ȃ�
	//----------------------------------------
	void MeshSetting(DrawBase* draw, Camera* camera, 
					 unsigned object_index, unsigned mesh_index);

private:
	//----------------------------------------
	//! @brief ���_�V�F�[�_�[�������֐�
	//! @details
	//! @param *common_data �`�拤�ʃf�[�^
	//! @retval void �Ȃ�
	//----------------------------------------
	void InitVertexShader(DrawCommonData* common_data);

	//----------------------------------------
	//! @brief �s�N�Z���V�F�[�_�[�������֐�
	//! @details
	//! @param *common_data �`�拤�ʃf�[�^
	//! @retval void �Ȃ�
	//----------------------------------------
	void InitPixelShader(DrawCommonData* common_data);

	//----------------------------------------
	//! @brief ���_�V�F�[�_�[�I���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void UninitVertexShader();

	//----------------------------------------
	//! @brief �s�N�Z���V�F�[�_�[�I���֐�
	//! @details
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void UninitPixelShader();

	//----------------------------------------
	//! @brief �f�o�C�X�ɒ��_�V�F�[�_�[�ݒ�֐�
	//! @details
	//! @param *draw �`����N���X
	//! @retval void �Ȃ�
	//----------------------------------------
	void VertexShaderSetToDevice(DrawBase* draw);

	//----------------------------------------
	//! @brief �f�o�C�X�Ƀs�N�Z���V�F�[�_�[�ݒ�֐�
	//! @details
	//! @param *draw �`����N���X
	//! @retval void �Ȃ�
	//----------------------------------------
	void PixelShaderSetToDevice(DrawBase* draw);

	//----------------------------------------
	//! @brief ���_�V�F�[�_�[�̃I�u�W�F�N�g�ݒ�֐�
	//! @details
	//! @param *draw		�`����N���X
	//! @param *camera		�J����
	//! @param object_index	�`��I�u�W�F�N�g�C���f�b�N�X
	//! @retval void �Ȃ�
	//----------------------------------------
	void ObjectSettingVertexShader(DrawBase* draw, Camera* camera,
								   unsigned object_index);

	//----------------------------------------
	//! @brief �s�N�Z���V�F�[�_�[�̃I�u�W�F�N�g�ݒ�֐�
	//! @details
	//! @param *draw		�`����N���X
	//! @param *camera		�J����
	//! @param object_index	�`��I�u�W�F�N�g�C���f�b�N�X
	//! @retval void �Ȃ�
	//----------------------------------------
	void ObjectSettingPixelShader(DrawBase* draw, Camera* camera,
								  unsigned object_index);

	//----------------------------------------
	//! @brief ���_�V�F�[�_�[�̃��b�V���ݒ�֐�
	//! @details
	//! @param *draw		�`����N���X
	//! @param *camera		�J����
	//! @param object_index	�`��I�u�W�F�N�g�C���f�b�N�X
	//! @param mesh_index	���b�V���C���f�b�N�X
	//! @retval void �Ȃ�
	//----------------------------------------
	void MeshSettingVertexShader(DrawBase* draw, Camera* camera,
								 unsigned object_index, unsigned mesh_index);

	//----------------------------------------
	//! @brief �s�N�Z���V�F�[�_�[�̃��b�V���ݒ�֐�
	//! @details
	//! @param *draw		�`����N���X
	//! @param *camera		�J����
	//! @param object_index	�`��I�u�W�F�N�g�C���f�b�N�X
	//! @param mesh_index	���b�V���C���f�b�N�X
	//! @retval void �Ȃ�
	//----------------------------------------
	void MeshSettingPixelShader(DrawBase* draw, Camera* camera,
								unsigned object_index, unsigned mesh_index);
};



#endif
