//================================================================================
//
//    �S�[���`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/11/28
//
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "GoalDraw.h"

#include <Effekseer/EffekseerManager/EffekseerManager.h>



//****************************************
// �萔��`
//****************************************
const std::string GoalDraw::EFFECT = "CoinEffect/CoinEffect.efk";



//****************************************
// ��ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +�������֐�
//--------------------------------------------------
void GoalDraw::Init()
{
	// �I�[�_�[���X�g�ݒ�
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::TRANSPARENCY);
	getpDrawOrderList()->getpRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::FIXED);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::FIXED);

	// �_�E���L���X�g
	goal_ = (Goal*)getpGameObject();

	// �L���[�u�|���S���̐���
	cube_polygon_ = new CubePolygon();
	cube_polygon_->SetColor(XColor4(0.5f, 1.0f, 1.0f, 1.0f));

	// �G�t�F�N�g�̓ǂݍ���
	effekseer_object_ = EffekseerManager::getpInstance()->getpObject(&EFFECT);
	effekseer_object_->ChangeColor(255, 255, 255, 255);
	Vector3D* goal_position = goal_->GetTransform()->GetPosition();
	*effekseer_object_->getpTransform()->GetPosition() = *goal_position;
	effekseer_object_->getpTransform()->UpdateWorldMatrixSRT();
	effekseer_object_->setIsRepeat(true);
	effekseer_object_->Play();
}



//--------------------------------------------------
// +�I���֐�
//--------------------------------------------------
void GoalDraw::Uninit()
{
	// �e�����
	SafeRelease::Normal(&cube_polygon_);

	SafeRelease::PlusRelease(&effekseer_object_);
}



//--------------------------------------------------
// +�X�V�֐�
//--------------------------------------------------
void GoalDraw::Update()
{
	// �G�t�F�N�g���W�X�V
	Vector3D* goal_position = goal_->GetTransform()->GetPosition();
	*effekseer_object_->getpTransform()->GetPosition() = *goal_position;
	effekseer_object_->getpTransform()->UpdateWorldMatrixSRT();
}



//--------------------------------------------------
// +�`��֐�
//--------------------------------------------------
void GoalDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;
	
	// �L���[�u�`��
	cube_polygon_->Draw();
}



//--------------------------------------------------
// +���b�V�����擾�֐�
//--------------------------------------------------
unsigned GoalDraw::getMeshNum(unsigned object_index)
{
	object_index = object_index;

	return cube_polygon_->getMeshNum();
}



//--------------------------------------------------
// +�s��擾�֐�
//--------------------------------------------------
MATRIX* GoalDraw::getpMatrix(unsigned object_index)
{
	object_index = object_index;

	return goal_->GetTransform()->getpWorldMatrix();
}



//--------------------------------------------------
// +�}�e���A���擾�֐�
//--------------------------------------------------
D3DMATERIAL9* GoalDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return cube_polygon_->GetMaterial();
}