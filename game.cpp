//================================
//
// �Q�[������[game.cpp]
// Author : Kaiti Aoto
//
//================================
#include "game.h"
#include "manager.h"
#include "fade.h"

//�ÓI�����o�ϐ�
CPlayer* CGame::m_pPlayer = nullptr;
CTimerMana* CGame::m_pTimer = nullptr;
CObject3D* CGame::m_pObj3D = nullptr;
CScoreMana* CGame::m_pBreakCnt = nullptr;
CScoreMana* CGame::m_pTotalScore = nullptr;
CBulletCntMana* CGame::m_pBulletCount = nullptr;
CCollision* CGame::m_pColl = nullptr;
CMatchUp* CGame::m_pMatchup = nullptr;
CHpGauge* CGame::m_pHpGauge = nullptr;
CLoadStage* CGame::m_pStage = nullptr;
CStart* CGame::m_pStart = nullptr;
CResetGauge* CGame::m_pReset = nullptr;
CMap* CGame::m_pMap = nullptr;
CBuff* CGame::m_pBuff = nullptr;
CScreenFlash* CGame::m_pScreenFlash = nullptr;
CTutorial* CGame::m_pTutprial = nullptr;

CPause* CGame::m_pPause = nullptr;

CGame::MODE CGame::m_mode = CGame::MODE_NONE;
//==================
// �R���X�g���N�^
//==================
CGame::CGame():CScene(CScene::MODE_GAME)
{
}
//================
// �f�X�g���N�^
//================
CGame::~CGame()
{
}
//=======================
// ������
//=======================
void CGame::Init(void)
{
	//�����蔻�萶��
	if (m_pColl == nullptr)
	{
		m_pColl = new CCollision;
	}

	//��������
	if (m_pMatchup == nullptr)
	{
		m_pMatchup = new CMatchUp;
	}


	//�^�C�}�[����
	if (m_pTimer == nullptr)
	{
		m_pTimer = CTimerMana::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - (TIMER_SIZE * 4.5), 40.0f, 0.0f));
	}

	const float ScoreX = 950.0f;
	//�X�R�A����
	if (m_pBreakCnt == nullptr)
	{
		m_pBreakCnt = CScoreMana::Create(D3DXVECTOR3(ScoreX, 90.0f, 0.0f), SCORE_SIZE, SCORE_SIZE, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 2);
		CObject2D::Create("data\\TEXTURE\\conveni_icon00.png", D3DXVECTOR3(ScoreX - (SCORE_SIZE * 2), 90.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCORE_SIZE * 2, SCORE_SIZE * 2, 8);
	}
	//�X�R�A����
	if (m_pTotalScore == nullptr)
	{
		m_pTotalScore = CScoreMana::Create(D3DXVECTOR3(ScoreX, 40.0f, 0.0f), SCORE_SIZE, SCORE_SIZE, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 6);
		CObject2D::Create("data\\TEXTURE\\icon_star.png", D3DXVECTOR3(ScoreX - (SCORE_SIZE * 2), 40.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCORE_SIZE * 2, SCORE_SIZE * 2, 8);
	}

	//�e���J�E���g����
	if (m_pBulletCount == nullptr)
	{
		m_pBulletCount = CBulletCntMana::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + (BULLET_COUNT_SIZE * 1.0f), SCREEN_HEIGHT / 1.25f, 0.0f));
	}

	if (m_pHpGauge == nullptr)
	{
		m_pHpGauge = CHpGauge::Create(D3DXVECTOR3(50.0f, 40.0f, 0.0f), PLAYER_LIFE, GAUGE_Y, D3DCOLOR_RGBA(1, 255, 1, 255));
	}

	if (m_pReset == nullptr)
	{
		m_pReset = CResetGauge::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - (BULLET_COUNT_SIZE * 5), SCREEN_HEIGHT / 1.25f - 50.0f, 0.0f), 0, GAUGE_Y, D3DCOLOR_RGBA(255, 255, 1, 255));
	}

	if (m_pBuff == nullptr)
	{
		m_pBuff = new CBuff;
	}

	m_pMap = CMap::Create(D3DXVECTOR3(1150.0f, 600.0f, 0.0f), 200.0f, 200.0f);

	if (m_pStage == nullptr)
	{
		m_pStage = new CLoadStage;

		m_pStage->Load("data\\STAGE\\model01.txt");
	}

	//�v���C���[
	if (m_pPlayer == nullptr)
	{
		m_pPlayer = CPlayer::Create("data\\STAGE\\motion_vending.txt", D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	m_pStart = CStart::Create("data\\MODEL\\barricade00.x", D3DXVECTOR3(-870.0f, 0.0f, -880.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f));
	
	CEnemyGroup::Create(D3DXVECTOR3(-150.0f, 0.0f, -550.0f));
	CEnemyGroup::Create(D3DXVECTOR3(-500.0f, 0.0f, 0.0f));
	CEnemyGroup::Create(D3DXVECTOR3(-170.0f, 0.0f, 550.0f));
	CEnemyGroup::Create(D3DXVECTOR3(-700.0f, 0.0f, 750.0f));
	CEnemyGroup::Create(D3DXVECTOR3(560.0f, 0.0f, -190.0f));
	CEnemyGroup::Create(D3DXVECTOR3(300.0f, 0.0f, -700.0f));
	CEnemyGroup::Create(D3DXVECTOR3(70.0f, 0.0f, -50.0f));
	CEnemyGroup::Create(D3DXVECTOR3(800.0f, 0.0f, 700.0f));
	CEnemyGroup::Create(D3DXVECTOR3(100.0f, 0.0f, 550.0f));


	CObject3D::Create("data\\TEXTURE\\field00.jpeg", D3DXVECTOR3(0.0f, -0.1f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3000, 3000, CObject3D::TYPE_FIELD);
	CMeshCylinder::Create("data\\TEXTURE\\city00.png", D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2900, 200, D3DXCOLOR(1.0, 1.0, 1.0, 1.0), CMeshCylinder::TYPE_IN);
	CMeshSphere::Create("data\\TEXTURE\\sky001.jpg", D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3000, 3000, D3DXCOLOR(1.0, 1.0, 1.0, 1.0), CMeshSphere::TYPE_HALF_TOP);

	if (m_pPause == nullptr)
	{
		m_pPause = CPause::Create();
	}

	m_pTutprial = CTutorial::Create(D3DXVECTOR3(TUTORIAL_SIZE / 1.5f, SCREEN_HEIGHT - (TUTORIAL_SIZE / 1.5f), 0.0f), TUTORIAL_SIZE, TUTORIAL_SIZE);

	CStartUI::Create("data\\TEXTURE\\tutorial_start00.png", D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), STARTUI_SIZE_X, STARTUI_SIZE_Y);
	
	m_pScreenFlash = CScreenFlash::Create();

	SetMode(MODE_TUTORIAL);

	CSound* pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_GAME);
}
//=============
// �I������
//=============
void CGame::Uninit(void)
{
	if (m_pStage != nullptr)
	{
		m_pStage->Unload();
		delete m_pStage;
		m_pStage = nullptr;
	}

	//
	if (m_pHpGauge != nullptr)
	{
		m_pHpGauge = nullptr;
	}

	////�X�R�A�j��
	//if (m_pRestock != NULL)
	//{
	//	m_pRestock = NULL;
	//}

	//�X�R�A�j��
	if (m_pBreakCnt != nullptr)
	{
		//�X�R�A�I������
		m_pBreakCnt->Uninit();

		delete m_pBreakCnt;
		m_pBreakCnt = nullptr;
	}
	//�X�R�A�j��
	if (m_pTotalScore != nullptr)
	{
		//�X�R�A�I������
		m_pTotalScore->Uninit();

		delete m_pTotalScore;
		m_pTotalScore = nullptr;
	}

	//�^�C�}�[�j��
	if (m_pTimer != nullptr)
	{
		//�^�C�}�[�I������
		m_pTimer->Uninit();

		delete m_pTimer;
		m_pTimer = nullptr;
	}

	//�e���J�E���^�[�j��
	if (m_pBulletCount != nullptr)
	{
		//�e���J�E���^�[�I������
		m_pBulletCount->Uninit();

		delete m_pBulletCount;
		m_pBulletCount = nullptr;
	}


	//�����蔻��
	if (m_pColl != nullptr)
	{
		delete m_pColl;
		m_pColl = nullptr;
	}

	//�����}�l�[�W���[
	if (m_pMatchup != nullptr)
	{
		delete m_pMatchup;
		m_pMatchup = nullptr;
	}

	if (m_pReset != nullptr)
	{
		m_pReset = nullptr;
	}

	//
	if (m_pBuff != nullptr)
	{
		delete m_pBuff;
		m_pBuff = nullptr;
	}

	if (m_pPause != nullptr)
	{
		m_pPause->Uninit();
		delete m_pPause;
		m_pPause = nullptr;
	}

	CObject::Release();
}
//=======================
// �}�l�[�W���[�̍X�V
//=======================
void CGame::Update(void)
{
	//�L�[�擾
	CInputKey* pInputKey = CManager::GetInputKey();
	//�p�b�h
	CInputPad* pInputPad = CManager::GetInputPad();

	CFade* pFade = CManager::GetFade();

	if (m_mode == MODE_FIN)
	{
		pFade->Set(CScene::MODE_RESULT);
		return;
	}
	else if (m_mode == MODE_BACK)
	{
		pFade->Set(CScene::MODE_TITLE);
		return;
	}
	else if (m_mode == MODE_PLAY)
	{
		bool bStart = m_pStart->GetStart();
		if (bStart == true)
		{
			if (m_pTimer != nullptr)
			{
				//�^�C�}�[�X�V
				m_pTimer->Update();
			}
		}
		if (m_pHpGauge != nullptr)
		{
			//
			m_pHpGauge->Update();
		}
		if (m_pBuff != nullptr)
		{
			m_pBuff->Update(1.0f / 60.0f);
		}

		CSell::Update();
	}
	if (m_pBreakCnt != nullptr)
	{
		m_pBreakCnt->Update();
	}
	if (m_pTotalScore != nullptr)
	{
		m_pTotalScore->Update();
	}

	if (m_pBulletCount != nullptr)
	{
		//�e���J�E���g�X�V
		m_pBulletCount->Update();
	}

	if (pInputKey->GetTrigger(DIK_P) == true || pInputPad->GetTrigger(CInputPad::JOYKEY_START) == true)
	{
		CManager::SetPause(true);
	}

	if (pInputKey->GetTrigger(DIK_F3) == true)
	{
		pFade->Set(CScene::MODE_RANKING);
		return;
	}

}
//=======================
// �}�l�[�W���[�̕`��
//=======================
void CGame::Draw(void)
{

}