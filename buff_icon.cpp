//==============================
//
// ��[����[restock.cpp]
// Author:kaiti
//
//==============================
#include "buff_icon.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "debugproc.h"
#include "input.h"

//==================
// �R���X�g���N�^
//==================
CBuffIcon::CBuffIcon(int nPriority):CObject2D(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bUse = true;
	m_bClear = false;
	m_type = CBuff::TYPE_NONE;

	m_nIdxTex = 0;
}
//================
// �f�X�g���N�^
//================
CBuffIcon::~CBuffIcon()
{
}
//===========
// ��������
//===========
CBuffIcon* CBuffIcon::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CBuffIcon* pObject2D;
	pObject2D = new CBuffIcon;
	//������
	pObject2D->Init(pos, fWidth, fHeight);
	return pObject2D;
}
//===============
// ����������
//===============
HRESULT CBuffIcon::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//�l����
	m_posStay = pos;
	m_posOut = pos + D3DXVECTOR3(-fWidth, 0.0f, 0.0f);

	m_pos = m_posOut;

	m_state = STATE_SLIDEIN;

	m_bUse = true;
	m_bClear = false;

	const char* apFileName[CBuff::TYPE_MAX] =
	{
		"data\\TEXTURE\\speedUP00.png",
	};

	for (int nCnt = 0; nCnt < CBuff::TYPE_MAX; nCnt++)
	{
		m_apFileName[nCnt] = apFileName[nCnt];
	}

	CObject2D::Init(m_apFileName[m_type], pos, m_rot, fWidth, fHeight);

	//�e�N�X�`�����蓖��
	CTexture* pTex = CManager::GetTex();
	m_nIdxTex = pTex->Register(m_apFileName[m_type]);
	CObject2D::SetIdxTex(m_nIdxTex);

	//�I�u�W�F�N�g�̎�ސݒ�
	SetObjType(TYPE_UI);

	return S_OK;
}
//============
// �I������
//============
void CBuffIcon::Uninit(void)
{
	CObject2D::Uninit();
}
//============
// �X�V����
//============
void CBuffIcon::Update(void)
{
	const float fSpeed = 8.0f;

	switch (m_state)
	{
	case STATE_STAY:
	{
		CBuff::TYPE type = CGame::GetBuff()->GetType();
		if (type == CBuff::TYPE_NONE)
		{
			m_bClear = true;
		}
		if (m_bClear == true)
		{
			m_state = STATE_SLIDEOUT;
		}
		break;
	}
	case STATE_SLIDEIN:
		if (m_bUse == true)
		{
			m_pos.x += fSpeed;
			if (m_pos.x >= m_posStay.x)
			{
				m_state = STATE_STAY;
				m_pos = m_posStay;
			}
		}
		break;
	case STATE_SLIDEOUT:
		m_pos.x -= fSpeed;
		if (m_pos.x <= m_posOut.x)
		{
			m_pos = m_posOut;
			m_bClear = false;
			m_bUse = false;
		}

		break;

	default:
		break;
	}

	CObject2D::SetPos(m_pos);

	if (m_bUse == false)
	{
		Uninit();
	}
}
//============
// �`�揈��
//============
void CBuffIcon::Draw(void)
{
	if (m_bUse == true)
	{
		CObject2D::Draw();
	}
}

void CBuffIcon::Move(void)
{


}