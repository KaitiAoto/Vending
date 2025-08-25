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

	if (m_bUse == false)
	{
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

void CTutorial::Move(void)
{


}

void CTutorial::CheckClear(void)
{
	//�L�[�擾
	CInputKey* pInputKey = CManager::GetInputKey();
	//�}�E�X�擾
	CInputMouse* pInputMouse = CManager::GetInputMouse();
	//�p�b�h
	CInputPad* pInputPad = CManager::GetInputPad();

	switch (m_type)
	{
	case TYPE_MOVE:
	{
		//�v���C���[�ړ��ŃN���A
		if (pInputKey->GetTrigger(DIK_W) == true || pInputKey->GetTrigger(DIK_A) == true || pInputKey->GetTrigger(DIK_S) == true || pInputKey->GetTrigger(DIK_D) == true)
		{
			m_bClear = true;
		}

		const float DEADZONE = 3000.0f;  // �f�b�h�]�[��
		XINPUT_STATE* pJoyState = pInputPad->GetJoyStickAngle();
		SHORT lx = pJoyState->Gamepad.sThumbLX;
		SHORT ly = pJoyState->Gamepad.sThumbLY;

		float fLX = (abs(lx) > DEADZONE) ? lx / 32768.0f : 0.0f;
		float fLY = (abs(ly) > DEADZONE) ? ly / 32768.0f : 0.0f;

		if (fLX != 0.0f || fLY != 0.0f)
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
	//case TYPE_JUMP:
	//	//�W�����v�ŃN���A
	//	if (pInputKey->GetTrigger(DIK_SPACE) == true || pInputPad->GetTrigger(CInputPad::JOYKEY_A) == true)
	//	{
	//		m_bClear = true;
	//	}
	//	break;
	case TYPE_BULLET:
		//�e���˂ŃN���A
		if (pInputMouse->GetTrigger(0) == true || pInputPad->GetTrigger(CInputPad::JOYKEY_B) == true)
		{
			m_bClear = true;
		}
		break;
	case TYPE_RESTOCK:
		//��[�ŃN���A
		if (pInputKey->GetTrigger(DIK_F) == true || pInputPad->GetTrigger(CInputPad::JOYKEY_Y) == true)
		{
			m_bClear = true;
		}
		break;
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
