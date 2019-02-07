//================================================================================
//!	@file	 BulletPhysicsDebug.cpp
//!	@brief	 �o���b�g�t�B�W�b�N�X�f�o�b�OClass
//! @details 
//!	@author  Kai Araki									@date 2019/02/07
//================================================================================


//****************************************
// �C���N���[�h��
//****************************************
#include "../BulletPhysicsDebug.h"
#include "../../../Draw/Camera/Camera.h"



//****************************************
// �֐���`
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

	// ���_������
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
	// ���_�X�V
	vertex_[0].posisiont_ = Vec3((float)from.getX(), (float)from.getY(), (float)from.getZ());
	vertex_[0].color_ = (Color4)XColor4((float)color.getX(), (float)color.getY(), (float)color.getZ(), 1.0f);
	vertex_[1].posisiont_ = Vec3((float)to.getX(), (float)to.getY(), (float)to.getZ());
	vertex_[1].color_ = (Color4)XColor4((float)color.getX(), (float)color.getY(), (float)color.getZ(), 1.0f);

	// ��
	device_->DrawPrimitiveUP(D3DPT_LINELIST, 1, &vertex_[0],
							 sizeof(RendererDirectX9::VERTEX_3D));


}



void BulletPhysicsDebug::DrawSettingBefore(Camera* camera)
{
	// FVF�̐ݒ�(�f�o�C�X�̕��ɒ��_�̑�����������)
	device_->SetFVF(RendererDirectX9::FVF_VERTEX_3D);

	// �e�N�X�`����OFF
	device_->SetTexture(0, NULL);

	// �@�������1�ɐ��K��
	device_->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
	
	// �J�����ݒ�
	camera->setType(Camera::Type::PERSPECTIVE);

	// �V�F�[�_�[�ݒ�
	device_->SetVertexShader(nullptr);
	device_->SetPixelShader(nullptr);

	// �s��̃Z�b�g
	device_->SetTransform(D3DTS_VIEW, camera->getpViewMatrix());
	device_->SetTransform(D3DTS_PROJECTION, camera->getpProjectionMatrix());
	device_->SetTransform(D3DTS_WORLD, transform_.getpWorldMatrix());

	// ���C�e�B���O��OFF�ɂ���
	device_->SetRenderState(D3DRS_LIGHTING, FALSE);
}



void BulletPhysicsDebug::DrawSettingAfter()
{
	// ���C�e�B���O��ON�ɂ���
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