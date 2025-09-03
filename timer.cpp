//=======================
//
// �^�C�}�[[timer.cpp]
// Author:kaiti
//
//=======================
#include "timer.h"
#include "renderer.h"
#include "manager.h"
#include "timer_manager.h"

//==================
// �R���X�g���N�^
//==================
CTimer::CTimer(int nPriority) :CObject(nPriority)
{
	m_pNumber = nullptr;
}
//================
// �f�X�g���N�^
//================
CTimer::~CTimer()
{
}
//===========
// ��������
//===========
CTimer* CTimer::Create(D3DXVECTOR3 pos)
{
	CTimer* pScore = new CTimer;
	//������
	pScore->Init(pos, TIMER_SIZE, TIMER_SIZE);

	return pScore;
}
//===============
// ����������
//===============
HRESULT CTimer::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	//������
	m_pNumber = CNumber::Create("data\\TEXTURE\\number002.png", pos, fWidth, fHeight);
	
	SetObjType(TYPE_TIME);

	return S_OK;
}
//============
// �I������
//============
void CTimer::Uninit(void)
{
	if (m_pNumber != nullptr)
	{
		m_pNumber->Uninit();
		delete m_pNumber;
		m_pNumber = nullptr;
	}
	CObject::Release();
}
//============
// �X�V����
//============
void CTimer::Update(void)
{
}
//============
// �`�揈��
//============
void CTimer::Draw(void)
{
	if (m_pNumber != nullptr)
	{
		m_pNumber->Draw();
	}
}