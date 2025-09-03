//===========================================
//
// �^�C�}�[�}�l�[�W���[[timer_manager.cpp]
// Author : Kaiti Aoto
//
//===========================================
#include "bullet_counter_manager.h"
#include "renderer.h"
#include "manager.h"
#include "object.h"
#include "player.h"
//�ÓI�����o�ϐ�
int CBulletCntMana::m_nCount = 0;
CBullerCounter* CBulletCntMana::m_pTimer[MAX_BULLETCNT] = {};
CBulletIcon* CBulletCntMana::m_pIcon = NULL;
//==================
// �R���X�g���N�^
//==================
CBulletCntMana::CBulletCntMana()
{

}
//================
// �f�X�g���N�^
//================
CBulletCntMana::~CBulletCntMana()
{
}
//===========
// ��������
//===========
CBulletCntMana* CBulletCntMana::Create(D3DXVECTOR3 pos)
{
	CBulletCntMana* pTimerMane = new CBulletCntMana;

	m_pIcon = CBulletIcon::Create(D3DXVECTOR3(pos.x - (BULLET_COUNT_SIZE * 4.5f), pos.y, 0.0f), BULLETICON_SIZE, BULLETICON_SIZE);
	CObject2D::Create("data\\TEXTURE\\multiply00.png",D3DXVECTOR3(pos.x - (BULLET_COUNT_SIZE * 2.0f), pos.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BULLETICON_SIZE, BULLETICON_SIZE, 7);

	for (int nCnt = 0; nCnt < MAX_BULLETCNT; nCnt++)
	{
		m_pTimer[nCnt] = CBullerCounter::Create(D3DXVECTOR3(pos.x + (nCnt * BULLET_COUNT_SIZE * 2.5f), pos.y, 0.0f));
	}

	pTimerMane->Init();

	return pTimerMane;
}
//===============
// ����������
//===============
HRESULT CBulletCntMana::Init(void)
{
	//������

	return S_OK;
}
//============
// �I������
//============
void CBulletCntMana::Uninit(void)
{

}
//============
// �X�V����
//============
void CBulletCntMana::Update(void)
{
	//�v���C���[���擾
	CPlayer* pPlayer = CGame::GetPlayer();
	m_nCount = pPlayer->GetContents();
	SetBulletCount();
}
//============
// �`�揈��
//============
void CBulletCntMana::Draw(void)
{
}
//==============
// �X�R�A���Z
//==============
void CBulletCntMana::SetBulletCount(void)
{
	int aPosTexU[MAX_BULLETCNT] = {}; //������
	if (m_nCount <= 0)
	{
		m_nCount = 0;
	}

	int nData = BULLETCNTDATA * 10;
	int nData2 = BULLETCNTDATA;
	for (int nCnt = 0; nCnt < MAX_BULLETCNT; nCnt++)
	{
		if (m_pTimer[nCnt] != nullptr)
		{
			CNumber* pNumber = m_pTimer[nCnt]->GetNumber();

			aPosTexU[nCnt] = m_nCount % nData / nData2;
			nData /= 10;
			nData2 /= 10;

			pNumber->SetTex((aPosTexU[nCnt] * 0.1f), (aPosTexU[nCnt] * 0.1f) + 0.1f, 0.0f, 1.0f);
		}
	}
}