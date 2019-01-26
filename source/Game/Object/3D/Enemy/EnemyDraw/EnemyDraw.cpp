//================================================================================
//
//    �G�`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/07/24
//
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "EnemyDraw.h"



//****************************************
// ��ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +�������֐�
//--------------------------------------------------
void EnemyDraw::Init()
{
	// �I�[�_�[���X�g�ݒ�
	getpDrawOrderList()->setDrawType(DrawOrderList::DrawType::TRANSPARENCY);
	getpDrawOrderList()->getpRenderTargetFlag()->Set(DrawOrderList::RENDER_TARGET_BACK_BUFFER);
	getpDrawOrderList()->setVertexShaderType(ShaderManager::VertexShaderType::FIXED);
	getpDrawOrderList()->setPixelShaderType(ShaderManager::PixelShaderType::FIXED);

	// �_�E���L���X�g
	enemy_ = (Enemy*)getpGameObject();
}



//--------------------------------------------------
// +�I���֐�
//--------------------------------------------------
void EnemyDraw::Uninit()
{
	
}



//--------------------------------------------------
// +�`��֐�
//--------------------------------------------------
void EnemyDraw::Draw(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;
	
	// �L���[�u�`��
	enemy_->cube_polygon_->Draw();
}



//--------------------------------------------------
// +���b�V�����擾�֐�
//--------------------------------------------------
unsigned EnemyDraw::getMeshNum(unsigned object_index)
{
	object_index = object_index;

	return enemy_->cube_polygon_->getMeshNum();
}



//--------------------------------------------------
// +�s��擾�֐�
//--------------------------------------------------
MATRIX* EnemyDraw::getpMatrix(unsigned object_index)
{
	object_index = object_index;

	return enemy_->GetTransform()->getpWorldMatrix();
}



//--------------------------------------------------
// +�}�e���A���擾�֐�
//--------------------------------------------------
D3DMATERIAL9* EnemyDraw::getpMaterial(unsigned object_index, unsigned mesh_index)
{
	object_index = object_index;
	mesh_index = mesh_index;

	return enemy_->cube_polygon_->GetMaterial();
}