//================================================================================
//
//    �v���C���[�`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/03/27
//
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "PlayerDraw.h"

#include <ComponentManager/DrawManager/Shader/VertexShader/VertexShaderBumpMapping/VertexShaderBumpMapping.h>
#include <SafeRelease/SafeRelease.h>
#include <ModelX/ModelXManager/ModelXManager.h>
#include <MdBin/MdBinManager/MdBinManager.h>



//****************************************
// �萔��`
//****************************************
const std::string PlayerDraw::MODEL_NAME = "knight_low/knight_low.X";
const std::string PlayerDraw::TEXTURE_PATH = "resource/ModelX/";
const std::string PlayerDraw::NORMAL_TEXTURE_MODEL = "knight_low/knight_01.png";
const std::string PlayerDraw::NORMAL_TEXTURE_SWORD = "knight_low/sword_01.png";



//****************************************
// ��ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +�������֐�
//--------------------------------------------------
void PlayerDraw::Init()
{
	// �I�[�_�[���X�g�ݒ�
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::OPACITY);
	getpDrawOrderList()->getpRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	//getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::VERTEX_BUMP_MAPPING);
	//getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::PIXEL_BUMP_MAPPING);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::ANIMATED_DEFAULT);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::DEFAULT);

	// X���f���o�^
	player_model_ = ModelXManager::getpInstance()->getpObject(&MODEL_NAME);

	// ���_�錾�p���b�V���X�V
	VertexShaderBumpMapping::UpdateMeshDeclaration(player_model_);

	// �@���}�b�v�̃��[�h
	normal_texture_[0] = TextureManager::getpInstance()->getpObject(&NORMAL_TEXTURE_MODEL, &TEXTURE_PATH);
	normal_texture_[1] = TextureManager::getpInstance()->getpObject(&NORMAL_TEXTURE_SWORD, &TEXTURE_PATH);

	// �e�X�g�p�I�u�W�F�N�g
	//std::string test = "neko_anime_hasiru3/neko_anime_hasiru3.mdbin_l";
	std::string test = "unitychan_Jump/unitychan_Jump.mdbin_l";
	//std::string test = "Unarmed Equip Over Shoulder/Unarmed Equip Over Shoulder.mdbin_l";
	//std::string test = "unitychan/unitychan.mdbin_l";
	//std::string test = "goblin-sapper/goblin-sapper.mdbin_l";
	//std::string test = "humanoid/humanoid.mdbin_l";
	test_object_ = MdBinManager::getpInstance()->getpObject(&test);
}



//--------------------------------------------------
// +�I���֐�
//--------------------------------------------------
void PlayerDraw::Uninit()
{
	SafeRelease::PlusRelease(&player_model_);

	for (int i = 0; i < 2; i++)
	{

		SafeRelease::PlusRelease(&normal_texture_[i]);
	}

	//�e�X�g�p
	SafeRelease::PlusRelease(&test_object_);
}

void PlayerDraw::Update()
{
	frame_ = ++count_ % 30;
}


//--------------------------------------------------
// +�`��֐�
//--------------------------------------------------
void PlayerDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;

	// ���݂̃��b�V���̕`��
	//player_model_->getpMesh()->DrawSubset(mesh_index);
	
	test_object_->Draw(mesh_index);
}



//--------------------------------------------------
// +���b�V�����擾�֐�
//--------------------------------------------------
unsigned PlayerDraw::getMeshNum(unsigned object_index)
{
	object_index = object_index;

	//return player_model_->getMeshNum();
	
	return test_object_->getMeshNum();
}



unsigned PlayerDraw::getBoneNum(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;

	return test_object_->getpMesh(mesh_index)->getBoneArraySize();
}



//--------------------------------------------------
// +�s��擾�֐�
//--------------------------------------------------
MATRIX* PlayerDraw::getpMatrix(unsigned object_index)
{
	object_index = object_index;

	return getpGameObject()->GetTransform()->getpWorldMatrix();
}



MATRIX* PlayerDraw::getpBoneMatrix(unsigned object_index, unsigned mesh_index,
								   unsigned bone_index)
{
	object_index = object_index;

	return test_object_->getpMesh(mesh_index)->getpBone(bone_index)
		->getpAnimationMatrix(0);// frame_);
}



//--------------------------------------------------
// +�}�e���A���擾�֐�
//--------------------------------------------------
D3DMATERIAL9* PlayerDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;

	//return player_model_->getpMaterial(mesh_index);

	return test_object_->getpMaterial(mesh_index);
}



//--------------------------------------------------
// +�f�B�q���[�Y�e�N�X�`���擾�֐�
//--------------------------------------------------
LPDIRECT3DTEXTURE9 PlayerDraw::getpDiffuseTexture(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;

	//return player_model_->getpDiffuseTextureObject(mesh_index)->getpHandler();

	return test_object_->getpDiffuseTextureHandler(mesh_index);
}



//--------------------------------------------------
// +�@���e�N�X�`���擾�֐�
//--------------------------------------------------
LPDIRECT3DTEXTURE9 PlayerDraw::getpNormalTexture(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;

	return normal_texture_[mesh_index]->getpHandler();
}