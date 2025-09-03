//============================
//
// ���[arrow.cpp]
// Author : Kaiti Aoto
//
//============================

// �C���N���[�h
#include "arrow.h"
#include "game.h"

//==================
// �R���X�g���N�^
//==================
CArrow::CArrow(int nPriority) :CObject3D(nPriority)
{
	// �l���N���A
	m_bUse = true;
	m_pos = { 0.0f,0.0f,0.0f };
	m_rot = { 0.0f,0.0f,0.0f };
	m_TargetPos = { 0.0f,0.0f,0.0f };
}
//================
// �f�X�g���N�^
//================
CArrow::~CArrow()
{
}
//==============
// ��������
//==============
CArrow* CArrow::Create(D3DXVECTOR3 pos)
{
	// ����
	CArrow* pArrow = new CArrow;
	// ������
	if (FAILED(pArrow->Init(pos)))
	{// NULL�`�F�b�N
		delete pArrow;
		return nullptr;
	}
	return pArrow;	// �|�C���^��Ԃ�
}
//===============
// ����������
//===============
HRESULT CArrow::Init(D3DXVECTOR3 pos)
{
	// �����o�ϐ���������
	m_bUse = true;
	m_pos = pos;
	m_TargetPos = CGame::GetStart()->GetPos();

	const float fWidth = 25.0f;		// ���̒���
	const float fHeight = 25.0f;	// �c�̒���

	// 3D�I�u�W�F�N�g�̏�����
	CObject3D::Init("data\\TEXTURE\\arrow00.png", pos, { 0.0f, 0.0f, 0.0f }, fWidth, fHeight, CObject3D::TYPE_SHADOW);

	// �I�u�W�F�N�g�̎�ސݒ�
	SetObjType(TYPE_UI);

	return S_OK;
}
//============
// �I������
//============
void CArrow::Uninit(void)
{
	// 3D�I�u�W�F�N�g�̏I������
	CObject3D::Uninit();
}
//============
// �X�V����
//============
void CArrow::Update(void)
{
	//--------------
	// ����
	//--------------
	// �����x�N�g��
	D3DXVECTOR3 toTarget = m_TargetPos - m_pos;
	// ���K��
	D3DXVec3Normalize(&toTarget, &toTarget);
	float angle = atan2f(toTarget.x, toTarget.z);
	m_rot.y = angle - D3DX_PI / 2;	// �l����

	//������ݒ�
	CObject3D::SetRot(m_rot);

	//---------------
	// �ʒu
	//---------------
	// �v���C���[�擾
	CPlayer* pPlayer = CGame::GetPlayer();
	m_pos = pPlayer->GetPos();// �v���C���[�̈ʒu����
	// �ʒu��ݒ�
	CObject3D::SetPos({ m_pos.x, m_pos.y + (pPlayer->GetSize().y * 2), m_pos.z });

	// �Q�[���̃��[�h��PLAY�Ȃ�
	if (CGame::GetMode() == CGame::MODE_PLAY)
	{
		m_bUse = false;// �g��Ȃ�����
	}
	// �g���Ă��Ȃ����
	if (m_bUse == false)
	{
		// �I������
		Uninit();
	}
}
//============
// �`�揈��
//============
void CArrow::Draw(void)
{
	// �g���Ă�����
	if (m_bUse == true)
	{
		CObject3D::Draw(); // 3D�I�u�W�F�N�g�̕`��
	}
}