//===================
//
// �^�C�}�[[timer.h]
// Author:kaiti
//
//===================
#include "arrow.h"
#include "game.h"

//==================
// �R���X�g���N�^
//==================
CArrow::CArrow(int nPriority) :CObject3D(nPriority)
{
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
//===========
// ��������
//===========
CArrow* CArrow::Create(D3DXVECTOR3 pos)
{
	CArrow* pObject2D;
	pObject2D = new CArrow;
	//������
	pObject2D->Init(pos);
	return pObject2D;
}
//===============
// ����������
//===============
HRESULT CArrow::Init(D3DXVECTOR3 pos)
{
	m_bUse = true;
	m_pos = pos;

	m_TargetPos = CGame::GetStart()->GetPos();

	const float fWidth = 25.0f;
	const float fHeight = 25.0f;

	CObject3D::Init("data\\TEXTURE\\arrow00.png", pos, { 0.0f, 0.0f, 0.0f }, fWidth, fHeight, CObject3D::TYPE_SHADOW);

	//�I�u�W�F�N�g�̎�ސݒ�
	SetObjType(TYPE_UI);

	return S_OK;
}
//============
// �I������
//============
void CArrow::Uninit(void)
{
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
	//�����x�N�g��
	D3DXVECTOR3 toTarget = m_TargetPos - m_pos;
	//���K��
	D3DXVec3Normalize(&toTarget, &toTarget);

	float angle = atan2f(toTarget.x, toTarget.z);
	m_rot.y = angle - D3DX_PI / 2;

	CObject3D::SetRot(m_rot);

	//---------------
	// �ʒu
	//---------------
	CPlayer* pPlayer = CGame::GetPlayer();
	m_pos = pPlayer->GetPos();

	CObject3D::SetPos({ m_pos.x, m_pos.y + (pPlayer->GetSize().y * 2), m_pos.z });


	if (CGame::GetMode() == CGame::MODE_PLAY)
	{
		m_bUse = false;
	}

	if (m_bUse == false)
	{
		Uninit();
	}
}
//============
// �`�揈��
//============
void CArrow::Draw(void)
{
	if (m_bUse == true)
	{
		CObject3D::Draw();
	}
}