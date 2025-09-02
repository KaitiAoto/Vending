//===========================================
//
// �^�C�}�[�}�l�[�W���[[timer_manager.cpp]
// Author:kaiti
//
//===========================================
#include "timer_manager.h"
#include "renderer.h"
#include "manager.h"
#include "object.h"
#include "debugproc.h"
//�ÓI�����o�ϐ�
int CTimerMana::m_nTimer = 0;
CTimer* CTimerMana::m_pSecond[TIME_DIGIT] = {};
CTimer* CTimerMana::m_pMinute[TIME_DIGIT] = {};
int CTimerMana::m_nCntTime = 0;
int CTimerMana::m_nDrawSecond = 0;
int CTimerMana::m_nDrawMinute = 0;

//==================
// �R���X�g���N�^
//==================
CTimerMana::CTimerMana()
{

}
//================
// �f�X�g���N�^
//================
CTimerMana::~CTimerMana()
{
}
//===========
// ��������
//===========
CTimerMana* CTimerMana::Create(D3DXVECTOR3 pos)
{
	CTimerMana* pTimerMane = new CTimerMana;

	for (int nCnt = 0; nCnt < TIME_DIGIT; nCnt++)
	{
		m_pMinute[nCnt] = CTimer::Create(D3DXVECTOR3(pos.x + (nCnt * TIMER_SIZE * 2.5f), pos.y, 0.0f));
	}

	CObject2D::Create("data\\TEXTURE\\colon00.png", D3DXVECTOR3(SCREEN_WIDTH / 2, pos.y, 0.0f), { 0.0f,0.0f,0.0f }, TIMER_SIZE * 1.5f, TIMER_SIZE * 1.5f, 7);

	pos.x += (2.5 * TIMER_SIZE * 2.5f);

	for (int nCnt = 0; nCnt < TIME_DIGIT; nCnt++)
	{
		m_pSecond[nCnt] = CTimer::Create(D3DXVECTOR3(pos.x + (nCnt * TIMER_SIZE * 2.5f), pos.y, 0.0f));
	}

	pTimerMane->Init();

	return pTimerMane;
}
//===============
// ����������
//===============
HRESULT CTimerMana::Init(void)
{
	//������
	m_nTimer = 0;
	CTimerMana::AddTime(GAME_TIME);
	return S_OK;
}
//============
// �I������
//============
void CTimerMana::Uninit(void)
{

}
//============
// �X�V����
//============
void CTimerMana::Update(void)
{
	m_nCntTime++;
	if (m_nCntTime >= 60)
	{
		m_nCntTime = 0;
		CTimerMana::AddTime(-1);
	}
	if (m_nTimer <= 0)
	{
		m_nTimer = 0;
		CGame::SetMode(CGame::MODE_FIN);
	}

	CDebugProc* pDegub = CManager::GetDebug();
	pDegub->Print("���F�b��%d,%d", m_nDrawMinute, m_nDrawSecond);

}
//============
// �`�揈��
//============
void CTimerMana::Draw(void)
{
}
//==============
// �X�R�A���Z
//==============
void CTimerMana::AddTime(int nAdd)
{
	m_nTimer += nAdd;

	if (m_nTimer <= 0)
	{
		m_nTimer = 0;
	}

	m_nDrawMinute = m_nTimer / 60;
	m_nDrawSecond = m_nTimer % 60;

	Second();
	Minute();
}
//==============================
// �b�P�ʂ̃e�N�X�`���؂�ւ�
//==============================
void CTimerMana::Second(void)
{
	int aPosTexU[TIME_DIGIT]; //������

	int nData = TIMERDATA * 10;
	int nData2 = TIMERDATA;
	for (int nCnt = 0; nCnt < TIME_DIGIT; nCnt++)
	{
		if (m_pSecond[nCnt] != nullptr)
		{
			CNumber* pNumber = m_pSecond[nCnt]->GetNumber();

			aPosTexU[nCnt] = m_nDrawSecond % nData / nData2;
			nData /= 10;
			nData2 /= 10;

			pNumber->SetTex((aPosTexU[nCnt] * 0.1f), (aPosTexU[nCnt] * 0.1f) + 0.1f, 0.0f, 1.0f);
		}
	}
}
//==============================
// ���P�ʂ̃e�N�X�`���؂�ւ�
//==============================
void CTimerMana::Minute(void)
{
	int aPosTexU[TIME_DIGIT]; //������

	int nData = TIMERDATA * 10;
	int nData2 = TIMERDATA;
	for (int nCnt = 0; nCnt < TIME_DIGIT; nCnt++)
	{
		if (m_pMinute[nCnt] != nullptr)
		{
			CNumber* pNumber = m_pMinute[nCnt]->GetNumber();

			aPosTexU[nCnt] = m_nDrawMinute % nData / nData2;
			nData /= 10;
			nData2 /= 10;

			pNumber->SetTex((aPosTexU[nCnt] * 0.1f), (aPosTexU[nCnt] * 0.1f) + 0.1f, 0.0f, 1.0f);
		}
	}
}
