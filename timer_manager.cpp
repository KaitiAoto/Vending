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
//�ÓI�����o�ϐ�
int CTimerMana::m_nTimer = 0;
CTimer* CTimerMana::m_pTimer[MAX_TIMER] = {};
int CTimerMana::m_nCntTime = 0;

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

	for (int nCnt = 0; nCnt < MAX_TIMER; nCnt++)
	{
		m_pTimer[nCnt] = CTimer::Create(D3DXVECTOR3(pos.x + (nCnt * TIMER_SIZE * 2.5f), pos.y, 0.0f));
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
	//for (int nCnt = 0; nCnt < MAX_TIMER; nCnt++)
	//{
	//	if (m_pTimer[nCnt] != nullptr)
	//	{
	//		m_pTimer[nCnt]->Uninit();
	//	}
	//}
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
		//CTimerMana::AddTime(60);

		CGame::SetMode(CGame::MODE_FIN);
	}
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

	int aPosTexU[MAX_TIMER]; //������
	if (m_nTimer <= 0)
	{
		m_nTimer = 0;
	}

	int nData = TIMERDATA * 10;
	int nData2 = TIMERDATA;
	for (int nCnt = 0; nCnt < MAX_TIMER; nCnt++)
	{
		if (m_pTimer[nCnt] != nullptr)
		{
			CNumber* pNumber = m_pTimer[nCnt]->GetNumber();

			aPosTexU[nCnt] = m_nTimer % nData / nData2;
			nData /= 10;
			nData2 /= 10;

			pNumber->SetTex((aPosTexU[nCnt] * 0.1f), (aPosTexU[nCnt] * 0.1f) + 0.1f, 0.0f, 1.0f);
		}
	}
}
