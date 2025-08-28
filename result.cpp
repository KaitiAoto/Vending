//================================
//
// ���U���g����[result.cpp]
// Author:kaiti
//
//================================
#include "result.h"
#include "manager.h"
#include "renderer.h"
#include "object2D.h"
#include "ranking.h"
#include "click.h"
//
CLoadStage* CResult::m_pStage = NULL;
CScoreMana* CResult::m_pBreakCnt = nullptr;
CScoreMana* CResult::m_pTotalScore = nullptr;

//==================
// �R���X�g���N�^
//==================
CResult::CResult():CScene(CScene::MODE_RESULT)
{
	m_nCntStay = 0;
}
//================
// �f�X�g���N�^
//================
CResult::~CResult()
{
}
//=======================
// ������
//=======================
void CResult::Init(void)
{
	CManager::GetLight()->SetColor(D3DXCOLOR(0.8f, 0.4f, 0.0f, 1.0f));

	m_nCntStay = RESULT_STAY;

	CObject2D::Create("data\\TEXTURE\\result01.png", D3DXVECTOR3(SCREEN_WIDTH / 2.75f, SCREEN_HEIGHT / 2.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 500.0f, 100.0f, 7);
	CObject2D::Create("data\\TEXTURE\\result01.png", D3DXVECTOR3(SCREEN_WIDTH / 2.75f, SCREEN_HEIGHT / 1.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 500.0f, 100.0f, 7);

	CClick::Create("data\\TEXTURE\\next00.png", D3DXVECTOR3(SCREEN_WIDTH - (CLICK_SIZE_X / 1.5f), SCREEN_HEIGHT - (CLICK_SIZE_Y / 1.5f), 0.0f), CLICK_SIZE_X, CLICK_SIZE_Y);

	//�X�R�A����
	if (m_pBreakCnt == NULL)
	{
		m_pBreakCnt = CScoreMana::Create(D3DXVECTOR3(SCREEN_WIDTH / 1.5f, SCREEN_HEIGHT / 2.5f, 0.0f), SCORE_SIZE * 2.0f, SCORE_SIZE * 2.0f, 2);
	}
	if (m_pTotalScore == NULL)
	{
		m_pTotalScore = CScoreMana::Create(D3DXVECTOR3(SCREEN_WIDTH / 1.5f, SCREEN_HEIGHT / 1.5f, 0.0f), SCORE_SIZE * 2.0f, SCORE_SIZE * 2.0f, 2);
	}

	if (m_pStage == NULL)
	{
		m_pStage = new CLoadStage;

		m_pStage->Load("data\\STAGE\\model01.txt");
	}


	CObject3D::Create("data\\TEXTURE\\field00.jpeg", D3DXVECTOR3(0.0f, -0.1f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3000, 3000, CObject3D::TYPE_FIELD);
	CMeshCylinder::Create("data\\TEXTURE\\city01.png", D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2900, 200, D3DXCOLOR(1.0, 1.0, 1.0, 1.0), CMeshCylinder::TYPE_IN);
	CMeshSphere::Create("data\\TEXTURE\\sky002.jpg", D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3000, 3000, D3DXCOLOR(1.0, 1.0, 1.0, 1.0), CMeshSphere::TYPE_HALF_TOP);

	CSound* pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_RESULT);
}
//=============
// �I������
//=============
void CResult::Uninit(void)
{
	if (m_pStage != NULL)
	{
		m_pStage->Unload();
		delete m_pStage;
		m_pStage = nullptr;
	}
	//�X�R�A�j��
	if (m_pBreakCnt != NULL)
	{
		//�X�R�A�I������
		m_pBreakCnt->Uninit();

		delete m_pBreakCnt;
		m_pBreakCnt = NULL;
	}
	if (m_pTotalScore != NULL)
	{
		//�X�R�A�I������
		m_pTotalScore->Uninit();

		delete m_pTotalScore;
		m_pTotalScore = NULL;
	}

	CObject::Release();
}
//=======================
// �X�V
//=======================
void CResult::Update(void)
{
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

			pFade->Set(CScene::MODE_RANKING);
		}
	}
}
//=======================
// �`��
//=======================
void CResult::Draw(void)
{

}