//================================================================================
//
//    FBX���f���}�l�[�W���N���X�w�b�_
//    Author : Araki Kai                                �쐬�� : 2018/01/21
//
//================================================================================

#ifndef	_MODEL_FBX_MANAGER_H_
#define _MODEL_FBX_MANAGER_H_



//**********************************************************************
//
// �C���N���[�h��
//
//**********************************************************************

#include <string>
#include <vector>
#include <unordered_map>



//**********************************************************************
//
// �N���X��`
//
//**********************************************************************

class ModelFBXObject;
class TextureManager;



//**********************************************************************
//
// �N���X��`
//
//**********************************************************************

class ModelFBXManager
{
// ============================================================
public :
	// �R���X�g���N�^
	ModelFBXManager(TextureManager* texture_manager);


// ============================================================
public :
	// �f�X�g���N�^
	virtual ~ModelFBXManager();


// ============================================================
public :
	// �����o�ϐ�
	void RegistrationModelFBXObject(const std::string* key_name, const std::string* file_path = nullptr);

	ModelFBXObject* GetModelFBXObject(const std::string* key_name);
	void SetModelFBXObject(const std::string* key_name);
	
	
// ============================================================
private :
	// �����o�ϐ�
	std::unordered_map<std::string, ModelFBXObject*> model_map_;
	TextureManager*									 texture_manager_;
};



#endif