//==============================
//
// ��[����[restock.cpp]
// Author:kaiti
//
//==============================
#include "tutorial.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "debugproc.h"
#include "input.h"

//==================
// �R���X�g���N�^
//==================
CTutorial::CTutorial(int nPriority):CObject2D(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bUse = true;
	m_bClear = false;
	m_type = TYPE_MOVE;

	m_nIdxTex = 0;
}
//================
// �f�X�g���N�^
//================
CTutorial::~CTutorial()
{
}
//===========
// ��������
//===========
CTutorial* CTutorial::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CTutorial* pObject2D;
	pObject2D = new CTutorial;
	//������
	pObject2D->Init(pos, fWidth, fHeight);
	return pObject2D;
}
//===============
// ����������
//===============
HRESULT CTutorial::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//�l����
	m_posStay = pos;
	m_posOut = pos + D3DXVECTOR3(-fWidth, 0.0f, 0.0f);

	m_pos = m_posOut;;

	m_state = STATE_SLIDEIN;

	m_bUse = true;
	m_bClear = false;
	m_nTime = 0;

	m_nCntTime = 0;
	m_col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

	const char* apFileName[TYPE_MAX] =
	{
		"data\\TEXTURE\\tutorial00.jpg",
		"data\\TEXTURE\\tutorial01.jpg",
		//"data\\TEXTURE\\tutorial02.jpg",
		"data\\TEXTURE\\tutorial03.jpg",
		"data\\TEXTURE\\tutorial04.jpg",
		"data\\TEXTURE\\tutorial05.jpg",

	};

	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_apFileName[nCnt] = apFileName[nCnt];
	}

	CObject2D::Init(m_apFileName[m_type], pos, m_rot, fWidth, fHeight);
	
	m_pBack = CObject2D::Create(NULL, pos, m_rot, fWidth * 1.05f, fHeight * 1.05f, 7);

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
void CTutorial::Uninit(void)
{
	CObject2D::Uninit();
}
//============
// �X�V����
//============
void CTutorial::Update(void)
{
	const float fSpeed = 8.0f;
	//�e�N�X�`�����蓖��
	CTexture* pTex = CManager::GetTex();

	switch (m_state)
	{
	case STATE_STAY:
		CheckClear();

		if (m_bClear == true)
		{
			m_state = STATE_SLIDEOUT;
		}
		break;
	case STATE_SLIDEIN:
		if (m_bUse == true)
		{
			m_pos.x += fSpeed;
			if (m_pos.x == m_posStay.x)
			{
				m_state = STATE_STAY;
				m_pos = m_posStay;
			}
		}
		break;
	case STATE_SLIDEOUT:
		m_pos.x -= fSpeed;
		if (m_pos.x == m_posOut.x)
		{
			m_pos = m_posOut;

			//�e�N�X�`��������
			m_type = static_cast<TYPE>(m_type + 1);
			if (m_type != TYPE_MAX)
			{
				m_nIdxTex = pTex->Register(m_apFileName[m_type]);
				CObject2D::SetIdxTex(m_nIdxTex);

				m_state = STATE_SLIDEIN;
			}
			else
			{
				CGame::GetStart()->SetDraw(false);

				m_bUse = false;
			}
			m_bClear = false;
		}
		break;

	default:
		break;
	}

	CObject2D::SetPos(m_pos);
	m_pBack->SetPos(m_pos);
	
	m_nCntTime++;
	BackBlink();

	if (m_bUse == false)
	{
		CObject2D::SetUse(false);
		m_pBack->SetUse(false);
		Uninit();
	}
}
//============
// �`�揈��
//============
void CTutorial::Draw(void)
{
	if (m_bUse == true)
	{
		CObject2D::Draw();
	}
}
//==============
// �w�i�_��
//==============
void CTutorial::BackBlink(void)
{
	// �_�ł��鑬��
	const float Speed = 0.02f;

	m_col.a = 1.0f * fabsf(sinf(Speed * m_nCntTime));

	// �F��ݒ�
	m_pBack->SetColor(m_col);
}
//==================
// �N���A�`�F�b�N
//==================
void CTutorial::CheckClear(void)
{
	//�}�E�X�擾
	CInputMouse* pInputMouse = CManager::GetInputMouse();
	//�p�b�h
	CInputPad* pInputPad = CManager::GetInputPad();

	CPlayer* pPlayer = CGame::GetPlayer();

	switch (m_type)
	{
	case TYPE_MOVE:
	{
		//�v���C���[�ړ��ŃN���A
		if(pPlayer->GetbMove())
		{
			m_bClear = true;
		}
		break;
	}
	case TYPE_CAMERA:
	{
		//�J��������ŃN���A
		if (pInputMouse->GetRelX() != 0)
		{
			m_bClear = true;
		}

		float rx = pInputPad->GetRightStickX(); // ��
		float ry = pInputPad->GetRightStickY(); // �c

		// �f�b�h�]�[�������i�킸���ȌX���ɂ��듮��h�~�j
		const float deadZone = 0.2f;
		if (fabsf(rx) > deadZone || fabsf(ry) > deadZone)
		{
			m_bClear = true;
		}

		break;
	}
	case TYPE_MATCHUP:
		//���Ԍo�߂ŃN���A
		m_nTime++;
		if (m_nTime >= 180)
		{
			m_bClear = true;
			m_nTime = 0;
		}
		break;
	default:
		break;
	}

}
