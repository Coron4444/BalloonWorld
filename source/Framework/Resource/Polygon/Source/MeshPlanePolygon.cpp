//================================================================================
//!	@file	 MeshPlanePolygon.cpp
//!	@brief	 ���b�V�����ʃ|���S��Class
//! @details 
//!	@author  Kai Araki									@date 2017/11/22
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "../MeshPlanePolygon.h"

#include <Tool/SafeRelease.h>



//****************************************
// �萔��`
//****************************************
const float MeshPlanePolygon::TEXTURE_WIDTH = 1.0f;
const float MeshPlanePolygon::TEXTURE_HEIGHT = 1.0f;

const float MeshPlanePolygon::MESH_MIN = 1.0f;

const float field_height[100000] = {0.0f};
/*const float field_height[121] =
{
	//0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	//0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	//0.0f, 1.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 1.0f, 0.0f,
	//0.0f, 1.0f, 2.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 2.0f, 1.0f, 0.0f,
	//0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 4.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f,
	//0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f,
	//0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 4.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f,
	//0.0f, 1.0f, 2.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 2.0f, 1.0f, 0.0f,
	//0.0f, 1.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 1.0f, 0.0f,
	//0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	//0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,

	-0.6f, -0.8f, -1.0f, -0.4f, -0.2f, 0.0f, 0.2f, 0.4f, 1.0f, 0.6f, 0.2f,
	-0.6f, -0.8f, -1.0f, -0.4f, -0.2f, 0.0f, 0.2f, 0.4f, 1.0f, 0.6f, 0.2f,
	-0.6f, -0.8f, -1.0f, -0.4f, -0.2f, 0.0f, 0.2f, 0.4f, 1.0f, 0.6f, 0.2f,
	-0.6f, -0.8f, -1.0f, -0.4f, -0.2f, 0.0f, 0.2f, 0.4f, 1.0f, 0.6f, 0.2f,
	-0.6f, -0.8f, -1.0f, -0.4f, -0.2f, 0.0f, 0.2f, 0.4f, 1.0f, 0.6f, 0.2f,
	-0.6f, -0.8f, -1.0f, -0.4f, -0.2f, 0.0f, 0.2f, 0.4f, 1.0f, 0.6f, 0.2f,
	-0.6f, -0.8f, -1.0f, -0.4f, -0.2f, 0.0f, 0.2f, 0.4f, 1.0f, 0.6f, 0.2f,
	-0.6f, -0.8f, -1.0f, -0.4f, -0.2f, 0.0f, 0.2f, 0.4f, 1.0f, 0.6f, 0.2f,
	-0.6f, -0.8f, -1.0f, -0.4f, -0.2f, 0.0f, 0.2f, 0.4f, 1.0f, 0.6f, 0.2f,
	-0.6f, -0.8f, -1.0f, -0.4f, -0.2f, 0.0f, 0.2f, 0.4f, 1.0f, 0.6f, 0.2f,
	-0.6f, -0.8f, -1.0f, -0.4f, -0.2f, 0.0f, 0.2f, 0.4f, 1.0f, 0.6f, 0.2f
};*/



//****************************************
// �v���p�e�B��`
//****************************************
void MeshPlanePolygon::setColor(XColor4 value)
{
	for (auto& contents : vertex_)
	{
		contents.color_ = (Color4)value;
	}
	RegistrationVertex();
	material_.Diffuse = value;
	material_.Ambient = value;
}



unsigned MeshPlanePolygon::getMeshNum()
{
	return 1;
}



D3DMATERIAL9* MeshPlanePolygon::getpMaterial()
{
	return &material_;
}



float MeshPlanePolygon::getHeight(Vec3 position)
{
	// ���W����G���A���Z�o���v�Z
	int left_up_index = 0;
	int right_bottom_index = 0;
	for (int i = 0; i < (int)(mesh_num_.x * mesh_num_.y); i++)
	{
		// ���㒸�_�̊m�F
		left_up_index = i + (i / ((int)mesh_num_.x));
		if (vertex_[left_up_index].posisiont_.x > position.x) continue;
		if (vertex_[left_up_index].posisiont_.z < position.z) continue;

		// �E�����_�̊m�F
		right_bottom_index = left_up_index + (int)mesh_num_.x + 2;
		if (vertex_[right_bottom_index].posisiont_.x < position.x) continue;
		if (vertex_[right_bottom_index].posisiont_.z > position.z) continue;

		// �����̎O�p�`(N���Ń��b�V��������Ă��邽��)
		if (CalculationHeight(&position, left_up_index, right_bottom_index, right_bottom_index - 1))
		{
			return position.y;
		}

		// �E��̎O�p�`(N���Ń��b�V��������Ă��邽��)
		if (CalculationHeight(&position, left_up_index, left_up_index + 1, right_bottom_index))
		{
			return position.y;
		}
	}

	return position.y = -100.0f;
}



//****************************************
// �֐���`
//****************************************
void MeshPlanePolygon::Init(Vec2 mesh_num, Vec2 mesh_scale, XColor4 color)
{
	// ���b�V���t�B�[���h�̐��`�F�b�N
	mesh_num_.x = max(mesh_num.x, MESH_MIN);
	mesh_num_.y = max(mesh_num.y, MESH_MIN);

	// ���b�V���t�B�[���h�̃X�P�[���`�F�b�N
	mesh_scale.x = max(mesh_scale.x, MESH_MIN);
	mesh_scale.y = max(mesh_scale.y, MESH_MIN);

	CreateVertex(mesh_num_, mesh_scale, (Color4)color);
	CreateIndex(mesh_num_);
	CreatePrimitiveNum(mesh_num_);
	CreateMaterial();

	Renderer::getpInstance()->getDevice(&device_);
	if (device_ == nullptr)
	{
		MessageBox(nullptr, "NotGetDevice!(MeshPlanePolygon.cpp)", "Error", MB_OK);
		return;
	}
	AccessVRAM();
}



void MeshPlanePolygon::Uninit()
{
	SafeRelease::PlusRelease(&vertex_buffer_);
	SafeRelease::PlusRelease(&index_buffer_);
}



void MeshPlanePolygon::Draw()
{
	// FVF�̐ݒ�(�f�o�C�X�̕��ɒ��_�̑�����������)
	device_->SetFVF(RendererDirectX9::FVF_VERTEX_3D);

	// ���_�o�b�t�@���g��GPU�ƃo�[�e�b�N�X�o�b�t�@�̃p�C�v���C��
	// �g�������Ȃ�������NULL�������
	device_->SetStreamSource(0,										// �p�C�v���C���ԍ�
							 vertex_buffer_,						// �o�[�e�b�N�X�o�b�t�@�ϐ���
							 0,										// �ǂ����痬�����ނ�
							 sizeof(RendererDirectX9::VERTEX_3D));	// �X�g���C�h�l(�ׂ̒��_�܂ł̒�����1���_�̑傫��)


	 // �C���f�b�N�X�ŕ`��
	device_->SetIndices(index_buffer_);
	device_->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
								  0,					// �Z�b�g�X�g���[������ǂꂭ�炢����Ă��邩
								  0,					// �C���f�b�N�X�ň�ԏ������l
								  (UINT)vertex_.size(),	// ���_��
								  0,					// �X�^�[�g�C���f�b�N�X�ԍ�
								  primitive_num_);		// �v���~�e�B�u��
}



void MeshPlanePolygon::DrawWireFrame()
{
	device_->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	Draw();
	device_->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}



void MeshPlanePolygon::CreateVertex(Vec2 mesh_num, Vec2 mesh_scale, Color4 color)
{
	// ���_���̌���
	int temp_vertex_num = 4 + 2 * (((int)mesh_num.x) - 1);
	temp_vertex_num += temp_vertex_num / 2 * (((int)mesh_num.y) - 1);
	vertex_.resize(temp_vertex_num);

	// ���_���̓���
	float coordinate_x = -((mesh_scale.x / 2) * ((int)mesh_num.x));
	float coordinate_z = ((mesh_scale.y / 2) * ((int)mesh_num.y));
	float tex_widht = 0.0f;
	float tex_heihgt = 0.0f;
	int   x_count = 0;

	for (std::vector<RendererDirectX9::VERTEX_3D>::size_type i = 0; i < vertex_.size(); i++)
	{
		vertex_[i].posisiont_ = Vec3(coordinate_x, field_height[i], coordinate_z);
		vertex_[i].color_ = color;
		vertex_[i].texcoord_ = Vec2(tex_widht, tex_heihgt);
		coordinate_x += mesh_scale.x;
		tex_widht += TEXTURE_WIDTH;

		bool is_x_end = x_count == ((int)mesh_num.x);
		if (is_x_end)
		{
			x_count = 0;
			coordinate_x = -((mesh_scale.x / 2) * ((int)mesh_num.x));
			tex_widht = 0.0f;
			coordinate_z += -mesh_scale.y;
			tex_heihgt += TEXTURE_HEIGHT;
		}
		else
		{
			x_count++;
		}
	}


	// �@���v�Z
	for (std::vector<RendererDirectX9::VERTEX_3D>::size_type i = 0; i < vertex_.size(); i++)
	{
		// �t�B�[���h�̌��[�̒��_
		if (i / (unsigned)(mesh_num.x + 1.0f) == 0)
		{
			vertex_[i].normal_ = Vec3(0.0f, 1.0f, 0.0f);
			continue;
		}

		// �t�B�[���h�̑O�[�̒��_
		if (i / (unsigned)(mesh_num.x + 1.0f) == (unsigned)mesh_num.y)
		{
			vertex_[i].normal_ = Vec3(0.0f, 1.0f, 0.0f);
			continue;
		}

		// �t�B�[���h�̍��[�̒��_
		if (i % (unsigned)(mesh_num.x + 1.0f) == 0)
		{
			vertex_[i].normal_ = Vec3(0.0f, 1.0f, 0.0f);
			continue;
		}

		// �t�B�[���h�̉E�[�̒��_
		if (i % (unsigned)(mesh_num.x + 1.0f) == (unsigned)mesh_num.x)
		{
			vertex_[i].normal_ = Vec3(0.0f, 1.0f, 0.0f);
			continue;
		}

		// ����ȊO�̒��_
		// x����
		Vec3 temp_vector = vertex_[i + 1].posisiont_ - vertex_[i - 1].posisiont_;
		Vec3 normal_x = Vec3(-temp_vector.y, temp_vector.x, 0.0f);

		// z����
		temp_vector = vertex_[i - 5].posisiont_ - vertex_[i + 5].posisiont_;
		Vec3 normal_z = Vec3(0.0f, temp_vector.z, -temp_vector.y);
		Vector3D normal = normal_x + normal_z;
		vertex_[i].normal_ = *normal.ChangeNormalize();
	}
}



void MeshPlanePolygon::CreateIndex(Vec2 mesh_num)
{
	// �C���f�b�N�X���̌���
	int temp_index_num = 4 + 2 * (((int)mesh_num.x) - 1);
	temp_index_num += temp_index_num * (((int)mesh_num.y) - 1);
	temp_index_num += 2 * (((int)mesh_num.y) - 1);
	index_.resize(temp_index_num);


	// �C���f�b�N�X�̓���
	WORD down_num = (WORD)(((int)mesh_num.x) + 1);
	WORD up_num = 0;
	int  x_num = ((int)mesh_num.x) + 1;
	int  y_num = ((int)mesh_num.y);

	for (std::vector< WORD >::size_type i = 0; i < index_.size(); i++)
	{
		index_[i] = down_num;
		i++;
		index_[i] = up_num;
		down_num++;
		up_num++;
		x_num--;

		bool is_end_x = x_num == 0;
		if (is_end_x)
		{
			y_num--;

			bool is_remain_y = y_num != 0;
			if (is_remain_y)
			{
				i++;
				index_[i] = up_num - 1;
				i++;
				index_[i] = down_num;
				x_num = ((int)mesh_num.x) + 1;
			}
		}
	}
}



void MeshPlanePolygon::CreatePrimitiveNum(Vec2 mesh_num)
{
	// �v���~�e�B�u���̌���
	primitive_num_ = 2 * ((int)mesh_num.x) * ((int)mesh_num.y);
	primitive_num_ += 4 * (((int)mesh_num.y) - 1);
}



void MeshPlanePolygon::CreateMaterial()
{
	// �}�e���A���̐ݒ�
	ZeroMemory(&material_, sizeof(material_));	// �������̃A�h���X����sizeof()����0�Ŗ��߂�(�N���X�ɂ͎g��Ȃ�)

	// �}�e���A���J���[�𔒂ɂ���
	material_.Diffuse.r = 1.0f;
	material_.Diffuse.g = 1.0f;
	material_.Diffuse.b = 1.0f;
	material_.Diffuse.a = 1.0f;

	// �A���r�G���g�}�e���A���̐ݒ�
	material_.Ambient.r = 1.0f;
	material_.Ambient.g = 1.0f;
	material_.Ambient.b = 1.0f;
	material_.Ambient.a = 1.0f;
}



void MeshPlanePolygon::AccessVRAM()
{
	// VRAM�̃��������m��(GPU�Ɉ˗�)(���_�o�b�t�@�̍쐬)
	HRESULT  hr = device_->CreateVertexBuffer(sizeof(RendererDirectX9::VERTEX_3D) * (int)vertex_.size(),	// �؂肽��baf�̗�(�o�C�g)�A�܂�1���_�̗e�ʁ~�K�v���_��
											  D3DUSAGE_WRITEONLY,											// �g�p�p�r(����͏������݂̂݁AGPU�������������������񂾃f�[�^��ǂ�ł̓_��(�l���s��))
											  RendererDirectX9::FVF_VERTEX_3D,								// ���_����
											  D3DPOOL_MANAGED,												// ���_�o�b�t�@�̊Ǘ����@( MANAGED�͊Ǘ���Direct3D�ɂ��C���Ƃ����Ӗ� )
											  &vertex_buffer_,												// �Ǘ��҂̋��ꏊ�̃�����(�|�C���^�̃|�C���^)(�S�Ă͂���̒l��m�邽�߂̍��)
											  NULL);														// �Ȃ��H

	if (FAILED(hr))
	{
		MessageBox(NULL, "Vertex buffer was not created.", "Error", MB_OK);
	}


	// VRAM�̃��������m��(GPU�Ɉ˗�)(�C���f�b�N�X�o�b�t�@�̍쐬)
	hr = device_->CreateIndexBuffer(sizeof(WORD) * (int)index_.size(),	// �؂肽��baf�̗�(�o�C�g)�A�܂�1���_�̗e�ʁ~�K�v���_��
									D3DUSAGE_WRITEONLY,					// �g�p�p�r(����͏������݂̂݁AGPU�������������������񂾃f�[�^��ǂ�ł̓_��(�l���s��))
									D3DFMT_INDEX16,						// ���_�t�H�[�}�b�g(WORD�^������16�ADWORD�^�Ȃ�32)
									D3DPOOL_MANAGED,					// ���_�o�b�t�@�̊Ǘ����@( MANAGED�͊Ǘ���Direct3D�ɂ��C���Ƃ����Ӗ� )
									&index_buffer_,						// �Ǘ��҂̋��ꏊ�̃�����(�|�C���^�̃|�C���^)(�S�Ă͂���̒l��m�邽�߂̍��)
									NULL);								// �Ȃ��H

	if (FAILED(hr))
	{
		MessageBox(NULL, "Index buffer was not created.", "Error", MB_OK);
	}

	RegistrationVertex();
	RegistrationIndex();
}



void MeshPlanePolygon::RegistrationVertex()
{
	// ���_�̓o�^
	// ���z�A�h���X�����炤���_�|�C���^
	RendererDirectX9::VERTEX_3D* temp_vertex;

	// ���b�N����
	vertex_buffer_->Lock(0,						// �ǂ����烍�b�N��������
						 0,						// �ǂ̂��炢�؂肽����(0��VertexBuffer�S��)
						 (void**)&temp_vertex,	// ���b�N�����VRAM�̉��z�A�h���X�����炦��(���ۂɏ�������ł���킯�ł͂Ȃ�)
						 D3DLOCK_DISCARD);		// 0�ł��悢

	for (std::vector<RendererDirectX9::VERTEX_3D>::size_type i = 0; i < vertex_.size(); i++)
	{
		temp_vertex[i] = vertex_[i];
	}

	// �A�����b�N
	vertex_buffer_->Unlock();
}



void MeshPlanePolygon::RegistrationIndex()
{
	// �C���f�b�N�X�̓o�^
	// ���z�A�h���X�����炤���_�|�C���^ 
	LPWORD temp_index;

	// ���b�N����
	index_buffer_->Lock(0,						// �ǂ����烍�b�N��������
						0,						// �ǂ̂��炢�؂肽����(0��VertexBuffer�S��)
						(void**)&temp_index,	// ���b�N�����VRAM�̉��z�A�h���X�����炦��(���ۂɏ�������ł���킯�ł͂Ȃ�)
						D3DLOCK_DISCARD);		// 0�ł��悢

	for (std::vector<WORD>::size_type i = 0; i < index_.size(); i++)
	{
		temp_index[i] = index_[i];

	}

	// �A�����b�N
	index_buffer_->Unlock();
}



bool MeshPlanePolygon::CalculationHeight(Vec3* position, int index0, 
										 int index1, int index2)
{
	// �O�p�`�̊e�ӂɉ����x�N�g�����Z�o
	Vector3D v01 = vertex_[index1].posisiont_ - vertex_[index0].posisiont_;
	Vector3D v12 = vertex_[index2].posisiont_ - vertex_[index1].posisiont_;
	Vector3D v20 = vertex_[index0].posisiont_ - vertex_[index2].posisiont_;

	// �e���_���玩���ւ̃x�N�g��
	Vector3D v0p = *position - vertex_[index0].posisiont_;
	Vector3D v1p = *position - vertex_[index1].posisiont_;
	Vector3D v2p = *position - vertex_[index2].posisiont_;

	// ��L2�̊O�ς����߂�(2D�O��)
	float c0 = (v01.x * v0p.z) - (v01.z * v0p.x);
	float c1 = (v12.x * v1p.z) - (v12.z * v1p.x);
	float c2 = (v20.x * v2p.z) - (v20.z * v2p.x);

	// �������|���S�����ɂ���ꍇ
	if (c0 <= 0.0f && c1 <= 0.0f && c2 <= 0.0f)
	{
		// y���W�����߂�
		
		Vec3 temp_normal = Vector3D::CreateCross(&v01, &v12);
		Vec3 p0 = vertex_[index0].posisiont_;
		position->y = p0.y - ((temp_normal.x * (position->x - p0.x) +
							   temp_normal.z * (position->z - p0.z)) / temp_normal.y);
		return true;
	}
	return false;
}