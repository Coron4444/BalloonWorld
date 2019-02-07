//================================================================================
//!	@file	 ShaderManager.cpp
//!	@brief	 シェーダーマネージャClass
//! @details 
//!	@author  Kai Araki									@date 2019/01/19
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "../ShaderManager.h"
#include "../../VertexShader/VertexShaderNull.h"
#include "../../VertexShader/VertexShaderFixed.h"
#include "../../VertexShader/VertexShaderAnimatedDefault.h"
#include "../../VertexShader/VertexShaderBumpMapping.h"
#include "../../PixelShader/PixelShaderNull.h"
#include "../../PixelShader/PixelShaderDefault.h"
#include "../../PixelShader/PixelShaderBumpMapping.h"
#include "../../../../DrawBase.h"

#include <Tool/SafeRelease.h>



//****************************************
// 関数定義
//****************************************
void ShaderManager::Init(DrawCommonData* common_data)
{
	InitVertexShader(common_data);
	InitPixelShader(common_data);
}



void ShaderManager::Uninit()
{
	UninitVertexShader();
	UninitPixelShader();
}



void ShaderManager::ShaderSetToDevice(DrawBase* draw,
									  VertexShaderType forced_vertex,
									  PixelShaderType forced_pixel)
{
	// 強制の代入
	forced_vertex_ = forced_vertex;
	forced_pixel_ = forced_pixel;
	
	// シェーダーセット
	VertexShaderSetToDevice(draw);
	PixelShaderSetToDevice(draw);
}



void ShaderManager::ObjectSetting(DrawBase* draw, Camera* camera,
								  unsigned object_index)
{
	ObjectSettingVertexShader(draw, camera, object_index);
	ObjectSettingPixelShader(draw, camera, object_index);
}



void ShaderManager::MeshSetting(DrawBase* draw, Camera* camera,
								unsigned object_index, unsigned mesh_index)
{
	MeshSettingVertexShader(draw, camera, object_index, mesh_index);
	MeshSettingPixelShader(draw, camera, object_index, mesh_index);
}



void ShaderManager::InitVertexShader(DrawCommonData* common_data)
{
	// 生成
	vertex_shader_[(int)VertexShaderType::FIXED] = new VertexShaderFixed();
	vertex_shader_[(int)VertexShaderType::ANIMATED_DEFAULT] = new VertexShaderAnimatedDefault();
	vertex_shader_[(int)VertexShaderType::BUMP_MAPPING] = new VertexShaderBumpMapping();

	// 初期化
	for (int i = 0; i < (int)VertexShaderType::MAX; i++)
	{
		vertex_shader_[i]->setDrawCommonData(common_data);
		vertex_shader_[i]->Init();
	}
}



void ShaderManager::InitPixelShader(DrawCommonData* common_data)
{
	// 生成
	pixel_shader_[(int)PixelShaderType::FIXED] = new PixelShaderNull();
	pixel_shader_[(int)PixelShaderType::DEFAULT] = new PixelShaderDefault();
	pixel_shader_[(int)PixelShaderType::BUMP_MAPPING] = new PixelShaderBumpMapping();

	// 初期化
	for (int i = 0; i < (int)PixelShaderType::MAX; i++)
	{
		pixel_shader_[i]->setDrawCommonData(common_data);
		pixel_shader_[i]->Init();
	}
}



void ShaderManager::UninitVertexShader()
{
	for (int i = 0; i < (int)VertexShaderType::MAX; i++)
	{
		SafeRelease::PlusUninit(&vertex_shader_[i]);
	}
}



void ShaderManager::UninitPixelShader()
{
	for (int i = 0; i < (int)PixelShaderType::MAX; i++)
	{
		SafeRelease::PlusUninit(&pixel_shader_[i]);
	}
}



void ShaderManager::VertexShaderSetToDevice(DrawBase* draw)
{
	int type = 0;
	if (draw != nullptr)
	{
		type = (forced_vertex_ != VertexShaderType::NONE) ? (int)forced_vertex_ : (int)draw->getpDrawOrderList()->getVertexShaderType();
	}
	else
	{
		type = (int)forced_vertex_;
	}
	vertex_shader_[type]->ShaderSetToDevice();
}



void ShaderManager::PixelShaderSetToDevice(DrawBase* draw)
{
	int type = 0;
	if (draw != nullptr)
	{
		type = (forced_pixel_ != PixelShaderType::NONE) ? (int)forced_pixel_ : (int)draw->getpDrawOrderList()->getPixelShaderType();
	}
	else
	{
		type = (int)forced_pixel_;
	}
	pixel_shader_[type]->ShaderSetToDevice();
}



void ShaderManager::ObjectSettingVertexShader(DrawBase* draw, Camera* camera,
											  unsigned object_index)
{
	int type = 0;
	if (draw != nullptr)
	{
		type = (forced_vertex_ != VertexShaderType::NONE) ? (int)forced_vertex_ : (int)draw->getpDrawOrderList()->getVertexShaderType();
	}
	else
	{
		type = (int)forced_vertex_;
	}
	vertex_shader_[type]->ObjectSetting(draw, camera, object_index);
}



void ShaderManager::ObjectSettingPixelShader(DrawBase* draw, Camera* camera,
											 unsigned object_index)
{
	int type = 0;
	if (draw != nullptr)
	{
		type = (forced_pixel_ != PixelShaderType::NONE) ? (int)forced_pixel_ : (int)draw->getpDrawOrderList()->getPixelShaderType();
	}
	else
	{
		type = (int)forced_pixel_;
	}
	pixel_shader_[type]->ObjectSetting(draw, camera, object_index);
}



void ShaderManager::MeshSettingVertexShader(DrawBase* draw, Camera* camera,
											unsigned object_index, unsigned mesh_index)
{
	int type = 0;
	if (draw != nullptr)
	{
		type = (forced_vertex_ != VertexShaderType::NONE) ? (int)forced_vertex_ : (int)draw->getpDrawOrderList()->getVertexShaderType();
	}
	else
	{
		type = (int)forced_vertex_;
	}
	vertex_shader_[type]->MeshSetting(draw, camera, object_index, mesh_index);
}



void ShaderManager::MeshSettingPixelShader(DrawBase* draw, Camera* camera,
										   unsigned object_index, unsigned mesh_index)
{
	int type = 0;
	if (draw != nullptr)
	{
		type = (forced_pixel_ != PixelShaderType::NONE) ? (int)forced_pixel_ : (int)draw->getpDrawOrderList()->getPixelShaderType();
	}
	else
	{
		type = (int)forced_pixel_;
	}
	pixel_shader_[type]->MeshSetting(draw, camera, object_index, mesh_index);
}