//==============================
//
//  �^�C�}�[����[.cpp]
//  Author : Kaiti Aoto
//
//==============================
#include "gauge_reset.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "object2D.h"
#include "input.h"
//==================
// �R���X�g���N�^
//==================
CResetGauge::CResetGauge(int nPriority) :CObject(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Base = 0;
	m_fHeight = 0;
}
//================
// �f�X�g���N�^
//================
CResetGauge::~CResetGauge()
{
}
//===========
// ��������
//===========
CResetGauge* CResetGauge::Create(D3DXVECTOR3 pos, float base, float fHeight, D3DXCOLOR col)
{
	CResetGauge* pGause;
	//
	pGause = new CResetGauge;
	//������
	if (FAILED(pGause->Init(pos, base, fHeight, col)))
	{
		delete pGause;
		return nullptr;
	}

	return pGause;
}
//=============
// ����������
//=============
HRESULT CResetGauge::Init(D3DXVECTOR3 pos, float base, float fHeight, D3DXCOLOR col)
{
	m_pos = pos;
	m_Base = base;
	m_fHeight = fHeight;
	m_col = col;
	m_bUse = false;
	m_pGauge = CGauge::Create(m_pos, m_Base, m_fHeight, m_col);
	m_pObj2D = CObject2D::Create("data\\TEXTURE\\reset00.png", D3DXVECTOR3(m_pos.x + 150.0f, m_pos.y, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 250, 50, 7);

	//�I�u�W�F�N�g�̎�ސݒ�
	//SetObjType(TYPE_GAUGE);

	return S_OK;
}
//==========
// �I������
//==========
void CResetGauge::Uninit(void)
{
	if (m_pGauge != nullptr)
	{
		m_pGauge->Uninit();
		delete m_pGauge;
		m_pGauge = nullptr;
	}
	CObject::Release();
}
//==========
// �X�V����
//==========
void CResetGauge::Update(void)
{
	//�L�[�擾
	CInputKey* pInputKey = CManager::GetInputKey();
	//�p�b�h
	CInputPad* pPad = CManager::GetInputPad();

	//�v���C���[���擾
	CPlayer* pPlayer = CGame::GetPlayer();

	int nCntContents = pPlayer->GetContents();

	if (nCntContents > 0)
	{//���g����
		if (pInputKey->GetPress(DIK_F) == true || pPad->GetPress(CInputPad::JOYKEY_Y) == true)
		{//�e������
			m_bUse = true;
			m_nCntReset++;
			m_Base += 0.15f;
			if (m_nCntReset >= 90)
			{//��莞�Ԍo�߂Œ��g���O��
				pPlayer->ClearContents();
				m_nCntReset = 0;
			}
		}
		else
		{
			m_nCntReset = 0;
			m_Base = 0;
			m_bUse = false;
		}
	}
	else
	{
		m_nCntReset = 0;
		m_Base = 0;
		m_bUse = false;
	}

	m_pObj2D->SetUse(m_bUse);
	m_pGauge->SetBase(m_Base);
	m_pGauge->Set();
}
//===========
// �`�揈��
//===========
void CResetGauge::Draw(void)
{
	if (m_bUse == true)
	{
		m_pGauge->Draw();
	}
}