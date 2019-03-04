//================================================================================
//!	@file	 PlayerDraw.cpp
//!	@brief	 プレイヤー描画Class
//! @details 
//!	@author  Kai Araki									@date 2018/03/27
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../PlayerDraw.h"
#include "../Player.h"

#include <GameEngine/Draw/DrawManager/Shader/VertexShader/VertexShaderBumpMapping.h>



//****************************************
// 定数定義
//****************************************
const std::string PlayerDraw::MODEL_NAME = "knight_low/knight_low.X";
const std::string PlayerDraw::TEXTURE_PATH = "resource/ModelX/";
const std::string PlayerDraw::NORMAL_TEXTURE_MODEL = "knight_low/knight_01.png";
const std::string PlayerDraw::NORMAL_TEXTURE_SWORD = "knight_low/sword_01.png";



//****************************************
// プロパティ定義
//****************************************
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



MATRIX* PlayerDraw::getpMatrix(unsigned object_index)
{
	object_index = object_index;

	return getpGameObject()->getpTransform()->getpWorldMatrix();
}



MATRIX* PlayerDraw::getpBoneMatrix(unsigned object_index, unsigned mesh_index,
								   unsigned bone_index)
{
	object_index = object_index;

	return test_object_->getpMesh(mesh_index)->getpBone(bone_index)
		->getpAnimationMatrix(pattern_num_);
}



D3DMATERIAL9* PlayerDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;

	//return player_model_->getpMaterial(mesh_index);
	return test_object_->getpMaterial(mesh_index);
}



LPDIRECT3DTEXTURE9 PlayerDraw::getpDiffuseTexture(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;

	//return player_model_->getpDiffuseTextureObject(mesh_index)->getpHandler();
	return test_object_->getpDiffuseTextureHandler(mesh_index);
}



LPDIRECT3DTEXTURE9 PlayerDraw::getpNormalTexture(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;

	return normal_texture_[mesh_index]->getpHandler();
}



//****************************************
// 関数定義
//****************************************
void PlayerDraw::Init()
{
	// オーダーリスト設定
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::OPACITY);
	getpDrawOrderList()->getpRenderTargetFlag()->setFlag(DrawOrderList::RENDER_TARGET_MAIN);
	//getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::BLINN_PHONG);
	//getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::BLINN_PHONG);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::ANIMATED_DEFAULT);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::DEFAULT);

	// Xモデル登録
	player_model_ = ModelXManager::getpInstance()->getpObject(&MODEL_NAME);

	// 頂点宣言用メッシュ更新
	VertexShaderBumpMapping::UpdateMeshDeclaration(player_model_);

	// 法線マップのロード
	normal_texture_[0] = TextureManager::getpInstance()->getpObject(&NORMAL_TEXTURE_MODEL, &TEXTURE_PATH);
	normal_texture_[1] = TextureManager::getpInstance()->getpObject(&NORMAL_TEXTURE_SWORD, &TEXTURE_PATH);

	// テスト用オブジェクト
	std::string test = "neko_anime_hasiru3/neko_anime_hasiru3.mdbin_l";
	test_object_ = MdBinManager::getpInstance()->getpObject(&test);

	player_ = (Player*)getpGameObject();
}



void PlayerDraw::Uninit()
{
	SafeRelease::PlusRelease(&player_model_);

	for (int i = 0; i < 2; i++)
	{

		SafeRelease::PlusRelease(&normal_texture_[i]);
	}

	//テスト用
	SafeRelease::PlusRelease(&test_object_);
}



void PlayerDraw::Update()
{
	int animation_speed = 1;
	pattern_num_ = player_->getAnimCount() / animation_speed % test_object_->getAnimationFrameNum();
}



void PlayerDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	//player_model_->getpMesh()->DrawSubset(mesh_index);
	test_object_->Draw(mesh_index);
}