//================================================================================
//!	@file	 BulletPhysicsDebug.cpp
//!	@brief	 バレットフィジックスデバッグClass
//! @details 
//!	@author  Kai Araki									@date 2019/02/07
//================================================================================


//****************************************
// インクルード文
//****************************************
#include "../BulletPhysicsDebug.h"
#include "../../../Draw/Camera/Camera.h"



//****************************************
// 関数定義
//****************************************
int BulletPhysicsDebug::getDebugMode() const
{
	return debug_mode_;
}



void BulletPhysicsDebug::setDebugMode(int value)
{
	debug_mode_ = value;
}



void BulletPhysicsDebug::Init()
{
	Renderer::getpInstance()->getDevice(&device_);
	if (device_ == nullptr)
	{
		MessageBox(nullptr, "NotGetDevice!(BulletPhysicsDebug.cpp)", "Error", MB_OK);
		return;
	}

	// 頂点初期化
	for (int i = 0; i < 2; i++)
	{
		vertex_[i].posisiont_ = Vec3(0.0f, 0.0f, 0.0f);
		vertex_[i].color_ = 0xffffffff;
		vertex_[i].normal_ = Vec3(0.0f, 0.0f, 0.0f);
		vertex_[i].texcoord_ = Vec2(0.0f, 0.0f);
	}
}



void BulletPhysicsDebug::drawLine(const btVector3& from, const btVector3& to,
								  const btVector3& color)
{
	// 頂点更新
	vertex_[0].posisiont_ = Vec3((float)from.getX(), (float)from.getY(), (float)from.getZ());
	vertex_[0].color_ = (Color4)XColor4((float)color.getX(), (float)color.getY(), (float)color.getZ(), 1.0f);
	vertex_[1].posisiont_ = Vec3((float)to.getX(), (float)to.getY(), (float)to.getZ());
	vertex_[1].color_ = (Color4)XColor4((float)color.getX(), (float)color.getY(), (float)color.getZ(), 1.0f);

	// 線
	device_->DrawPrimitiveUP(D3DPT_LINELIST, 1, &vertex_[0],
							 sizeof(RendererDirectX9::VERTEX_3D));


}



void BulletPhysicsDebug::DrawSettingBefore(Camera* camera)
{
	// FVFの設定(デバイスの方に頂点の属性を教える)
	device_->SetFVF(RendererDirectX9::FVF_VERTEX_3D);

	// テクスチャをOFF
	device_->SetTexture(0, NULL);

	// 法線を常に1に正規化
	device_->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
	
	// カメラ設定
	camera->setType(Camera::Type::PERSPECTIVE);

	// シェーダー設定
	device_->SetVertexShader(nullptr);
	device_->SetPixelShader(nullptr);

	// 行列のセット
	device_->SetTransform(D3DTS_VIEW, camera->getpViewMatrix());
	device_->SetTransform(D3DTS_PROJECTION, camera->getpProjectionMatrix());
	device_->SetTransform(D3DTS_WORLD, transform_.getpWorldMatrix());

	// ライティングをOFFにする
	device_->SetRenderState(D3DRS_LIGHTING, FALSE);
}



void BulletPhysicsDebug::DrawSettingAfter()
{
	// ライティングをONにする
	device_->SetRenderState(D3DRS_LIGHTING, TRUE);
}



void BulletPhysicsDebug::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB,
										  btScalar distance, int lifeTime, const btVector3& color)
{
	PointOnB.getX();
	normalOnB.getX();
	distance = distance;
	lifeTime = lifeTime;
	color.getX();
}



void BulletPhysicsDebug::reportErrorWarning(const char* warningString)
{
	char a = *warningString;
	a = a;
}



void BulletPhysicsDebug::draw3dText(const btVector3& location, const char* textString)
{
	location.getX();
	char a = *textString;
	a = a;
}