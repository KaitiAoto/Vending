//================================
//
// ���U���g����[result.cpp]
// Author:kaiti
//
//================================
#include "ranking.h"
#include "manager.h"
#include "object2D.h"
#include "click.h"
//
CLoadStage* CRanking::m_pStage = NULL;
CRankMana* CRanking::m_pBreakRank = NULL;
CRankMana* CRanking::m_pTotalRank = NULL;
//==================
// �R���X�g���N�^
//==================
CRanking::CRanking():CScene(CScene::MODE_RANKING)
{
	m_nCntStay = 0;
}
//================
// �f�X�g���N�^
//================
CRanking::~CRanking()
{
}
//=======================
// ������
//=======================
void CRanking::Init(void)
{
	m_nCntStay = RANK_STAY;

	m_pBreakRank = CRankMana::Create(D3DXVECTOR3(SCREEN_WIDTH / 1.25f, SCREEN_HEIGHT / 3.5f, 0.0f), "data\\TEXT\\BreakRank.txt");
	m_pTotalRank = CRankMana::Create(D3DXVECTOR3(SCREEN_WIDTH / 4.0f, SCREEN_HEIGHT / 3.5f, 0.0f), "data\\TEXT\\TotalRank.txt");

	CClick::Create("data\\TEXTURE\\next00.png", D3DXVECTOR3(SCREEN_WIDTH - (CLICK_SIZE_X / 1.5f), SCREEN_HEIGHT - (CLICK_SIZE_Y / 1.5f), 0.0f), CLICK_SIZE_X, CLICK_SIZE_Y);

	if (m_pStage == NULL)
	{
		m_pStage = new CLoadStage;

		m_pStage->Load("data\\STAGE\\model01.txt");
	}
	CObject3D::Create("data\\TEXTURE\\field00.jpeg", D3DXVECTOR3(0.0f, -0.1f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3000, 3000, CObject3D::TYPE_FIELD);
	CMeshCylinder::Create("data\\TEXTURE\\city01.png", D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2900, 200, D3DXCOLOR(1.0, 1.0, 1.0, 1.0), CMeshCylinder::TYPE_IN);
	CMeshSphere::Create("data\\TEXTURE\\sky002.jpg", D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3000, 3000, D3DXCOLOR(1.0, 1.0, 1.0, 1.0), CMeshSphere::TYPE_HALF_TOP);
}
//=============
// �I������
//=============
void CRanking::Uninit(void)
{
	if (m_pStage != NULL)
	{
		m_pStage->Unload();
		delete m_pStage;
		m_pStage = nullptr;
	}
	if (m_pBreakRank != NULL)
	{
		m_pBreakRank->Uninit();
		delete m_pBreakRank;
		m_pBreakRank = nullptr;
	}
	if (m_pTotalRank != NULL)
	{
		m_pTotalRank->Uninit();
		delete m_pTotalRank;
		m_pTotalRank = nullptr;
	}

	CObject::Release();
}
//=======================
// �X�V
//=======================
void CRanking::Update(void)
{
	m_pBreakRank->Update();
	m_pTotalRank->Update();

	m_nCntStay--;
	if (m_nCntStay <= 0)
	{
		m_nCntStay = 0;
		//�}�E�X�擾
		CInputMouse* pInputMouse = CManager::GetInputMouse();
		//�p�b�h
		CInputPad* pPad = CManager::GetInputPad();

		if (pInputMouse->GetTrigger(0) == true || pPad->GetTrigger(CInputPad::JOYKEY_A) == true)
		{
			CFade* pFade = CManager::GetFade();

			pFade->Set(CScene::MODE_TITLE);
		}
	}
}
//=======================
// �`��
//=======================
void CRanking::Draw(void)
{

}
//===================================
// ����̃X�R�A����RankMana�̐ݒ�
//===================================
void CRanking::SetNowScore(int nBreakScore, int nTotalScore)
{
	m_pBreakRank->Set(nBreakScore);//����̃X�R�A��ۑ�
	m_pBreakRank->SetRankIn(nBreakScore);//�����N�C��������

	m_pTotalRank->Set(nTotalScore);//����̃X�R�A��ۑ�
	m_pTotalRank->SetRankIn(nTotalScore);//�����N�C��������
}