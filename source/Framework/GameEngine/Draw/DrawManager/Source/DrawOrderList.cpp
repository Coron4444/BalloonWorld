//================================================================================
//!	@file	 DrawOrderList.cpp
//!	@brief	 描画注文リストClass
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================


//****************************************
// インクルード文
//****************************************
#include "../DrawOrderList.h"



//****************************************
// プロパティ定義
//****************************************
ShaderManager::VertexShaderType DrawOrderList::getVertexShaderType()
{ 
	return vertex_shader_type_;
}



void DrawOrderList::setVertexShaderType(ShaderManager::VertexShaderType value)
{
	vertex_shader_type_ = value; 
}



ShaderManager::PixelShaderType DrawOrderList::getPixelShaderType()
{ 
	return pixel_shader_type_;
}



void DrawOrderList::setPixelShaderType(ShaderManager::PixelShaderType value)
{ 
	pixel_shader_type_ = value;
}



DrawOrderList::DrawType DrawOrderList::getDrawType()
{ 
	return draw_type_; 
}



void DrawOrderList::setDrawType(DrawOrderList::DrawType value)
{ 
	draw_type_ = value; 
}



DrawOrderList::DrawType DrawOrderList::getTempChangeDrawType()
{
	return temp_change_draw_type_;
}



void DrawOrderList::setTempChangeDrawType(DrawOrderList::DrawType value)
{
	temp_change_draw_type_ = value;
}



BitFlag* DrawOrderList::getpRenderTargetFlag()
{ 
	return &render_target_flag_; 
}



bool DrawOrderList::getIsBillboard()
{ 
	return is_billboard_;
}



void DrawOrderList::setIsBillboard(bool value)
{ 
	is_billboard_ = value;
}



bool DrawOrderList::getIsLighting()
{ 
	return is_lighting_; 
}



void DrawOrderList::setIsLighting(bool value)
{
	is_lighting_ = value;
}



bool DrawOrderList::getIsAnimation()
{
	return is_animation_;
}



void DrawOrderList::setIsAnimation(bool value)
{
	is_animation_ = value;
}



int DrawOrderList::getLayerNum()
{ 
	return layer_num_;
}



void DrawOrderList::setLayerNum(int value)
{
	layer_num_ = value; 
}