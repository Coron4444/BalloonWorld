//================================================================================
//!	@file	 stdafx.h
//!	@brief	 プリコンパイル済みヘッダ
//! @details 
//!	@author  Kai Araki									@date 2019/02/27
//================================================================================
#ifndef	_STDAFX_H_
#define _STDAFX_H_



//****************************************
// インクルード文
//****************************************
#include <stdio.h>
#include <math.h>
#include <vector>
#include <list>
#include <string>
#include <unordered_map>
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#ifdef _DEBUG
#include <Tool/Debug/ImGUI/imgui.h>
#include <Tool/Debug/ImGUI/imgui_impl_dx9.h>
#endif

#include <Tool/Vector3D.h>
#include <Tool/Matrix.h>
#include <Tool/Transform.h>
#include <Tool/Axis.h>
#include <Tool/BitFlag.h>
#include <Tool/Interpolation.h>
#include <Tool/LimitedPointerArray.h>
#include <Tool/MeterToFrame.h>
#include <Tool/Physics.h>
#include <Tool/QuadraticEquation.h>
#include <Tool/Random.h>
#include <Tool/ReferenceList.h>
#include <Tool/SafeRelease.h>
#include <Tool/TimeToFrame.h>

#include <GameEngine/GameEngine.h>
#include <GameEngine/Renderer/Renderer.h>
#include <GameEngine/Input/InputManager/InputManager.h>

#include <Resource/Effekseer/EffekseerManager/EffekseerManager.h>
#include <Resource/MdBin/MdBinManager/MdBinManager.h>
#include <Resource/ModelX/ModelXManager/ModelXManager.h>
#include <Resource/Polygon/CubePolygon.h>
#include <Resource/Polygon/GridPolygon.h>
#include <Resource/Polygon/MeshPlanePolygon.h>
#include <Resource/Polygon/PlanePolygon.h>
#include <Resource/Polygon/NumbersPolygon.h>
#include <Resource/Sound/SoundManager.h>
#include <Resource/Texture/TextureManager/TextureManager.h>



#endif