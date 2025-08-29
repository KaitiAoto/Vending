//===================================
//
// �^�C�g���I��[title_select.cpp]
// Author:kaiti
//
//====================================
#include "pause_manager.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "debugproc.h"
#include "input.h"

//==================
// �R���X�g���N�^
//==================
CPauseMana::CPauseMana()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Select = SELECT_CONTNUE;
}
//================
// �f�X�g���N�^
//================
CPauseMana::~CPauseMana()
{
}
//===========
// ��������
//===========
CPauseMana* CPauseMana::Create(D3DXVECTOR3 pos)
{
	CPauseMana* pObject2D = nullptr;
	pObject2D = new CPauseMana;
	if (pObject2D != nullptr)
	{
		//������
		pObject2D->Init(pos);
	}
	return pObject2D;
}
//===============
// ����������
//===============
HRESULT CPauseMana::Init(D3DXVECTOR3 pos)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//�l����
	m_pos = pos;

	m_pBack = CObject2D::Create("data\\TEXTURE\\gauge00.jpeg", pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, 10);
	m_pBack->SetColor(D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.0f));

	m_pSelect[SELECT_CONTNUE] = CPauseSelect::Create("data\\TEXTURE\\contnue00.png", D3DXVECTOR3(m_pos.x, m_pos.y + (P_SELECT_Y * SELECT_CONTNUE), m_pos.z), P_SELECT_X, P_SELECT_Y);
	m_pSelect[SELECT_RESTART] = CPauseSelect::Create("data\\TEXTURE\\restart00.png", D3DXVECTOR3(m_pos.x, m_pos.y + (P_SELECT_Y * SELECT_RESTART), m_pos.z), P_SELECT_X, P_SELECT_Y);
	m_pSelect[SELECT_END] = CPauseSelect::Create("data\\TEXTURE\\end00.png", D3DXVECTOR3(m_pos.x, m_pos.y + (P_SELECT_Y * SELECT_END), m_pos.z), P_SELECT_X, P_SELECT_Y);

	return S_OK;
}
//============
// �I������
//============
void CPauseMana::Uninit(void)
{
}
//============
// �X�V����
//============
void CPauseMana::Update(void)
{
	Select();

	for (int nCnt = 0; nCnt < SELECT_MAX; nCnt++)
	{
		if (m_Select == nCnt)
		{
			m_pSelect[nCnt]->SetColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		}
		else
		{
			m_pSelect[nCnt]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}

	//�L�[�擾
	CInputKey* pInputKey = CManager::GetInputKey();
	//�p�b�h
	CInputPad* pPad = CManager::GetInputPad();

	if (pInputKey->GetTrigger(DIK_P) == true || pPad->GetTrigger(CInputPad::JOYKEY_START) == true)
	{
		CManager::SetPause(false);
	}
	if (CManager::GetPause() == true)
	{
		m_pBack->SetColor(D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.5f));
	}
	else
	{
		m_pBack->SetColor(D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.0f));
	}
}
//============
// �`�揈��
//============
void CPauseMana::Draw(void)
{
}
//
//
//
void CPauseMana::Select(void)
{
	//�L�[�擾
	CInputKey* pInputKey = CManager::GetInputKey();
	//�}�E�X�擾
	CInputMouse* pInputMouse = CManager::GetInputMouse();
	//�p�b�h
	CInputPad* pPad = CManager::GetInputPad();

	CSound* pSound = CManager::GetSound();

	CFade* pFade = CManager::GetFade();

	int wheel = 0;
	wheel =	pInputMouse->GetWheel();

	//�㉺�I��
	if (pInputKey->GetTrigger(DIK_W) == true || pPad->GetStickTriggerUp() == true || wheel > 0)
	{
		m_Select--;
		if (m_Select < 0) m_Select = SELECT_MAX - 1;

		pSound->PlaySound(CSound::SOUND_LABEL_SELECT);
	}
	else if (pInputKey->GetTrigger(DIK_S) == true || pPad->GetStickTriggerDown() == true || wheel < 0)
	{
		m_Select++;
		if (m_Select >= SELECT_MAX) m_Select = SELECT_CONTNUE;

		pSound->PlaySound(CSound::SOUND_LABEL_SELECT);
	}

	//����
	if (pInputMouse->GetTrigger(0) == true || pPad->GetTrigger(CInputPad::JOYKEY_A) == true)
	{
		switch (m_Select)
		{
		case SELECT_CONTNUE:
			break;
		case SELECT_RESTART:
			pFade->Set(CScene::MODE_GAME);
			break;
		case SELECT_END:
			CGame::SetMode(CGame::MODE_BACK);
			break;
		default:
			break;
		}
		CManager::SetPause(false);

		pSound->PlaySound(CSound::SOUND_LABEL_CONFIRM);
	}
}
