//===================================
//
// �^�C�g���I��[title_select.cpp]
// Author:kaiti
//
//====================================
#include "title_select.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "debugproc.h"
#include "input.h"
#include "title_logo.h"
#include "title.h"
//==================
// �R���X�g���N�^
//==================
CTitleSelect::CTitleSelect(int nPriority):CObject(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Select = SELECT_GAME;
}
//================
// �f�X�g���N�^
//================
CTitleSelect::~CTitleSelect()
{
}
//===========
// ��������
//===========
CTitleSelect* CTitleSelect::Create(D3DXVECTOR3 pos)
{
	CTitleSelect* pObject2D = nullptr;
	pObject2D = new CTitleSelect;
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
HRESULT CTitleSelect::Init(D3DXVECTOR3 pos)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//�l����
	m_pos = pos;

	m_pCursor = CObject2D::Create("data\\TEXTURE\\select00.png", m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), T_SELECT_X, T_SELECT_Y, 7);

	m_pSelect[SELECT_GAME] = CObject2D::Create("data\\TEXTURE\\start00.png", m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), T_SELECT_X, T_SELECT_Y, 8);
	m_pSelect[SELECT_END] = CObject2D::Create("data\\TEXTURE\\end00.png", D3DXVECTOR3(m_pos.x, m_pos.y + T_SELECT_Y, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), T_SELECT_X, T_SELECT_Y, 8);

	//�I�u�W�F�N�g�̎�ސݒ�
	SetObjType(TYPE_UI);

	return S_OK;
}
//============
// �I������
//============
void CTitleSelect::Uninit(void)
{

	CObject::Release();
}
//============
// �X�V����
//============
void CTitleSelect::Update(void)
{
	Select();

	m_pCursor->SetPos(m_pSelect[m_Select]->GetPos());

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
}
//============
// �`�揈��
//============
void CTitleSelect::Draw(void)
{
}
//
//
//
void CTitleSelect::Select(void)
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


	if (pInputKey->GetTrigger(DIK_W) == true || pPad->GetStickTriggerUp() == true || wheel > 0)
	{
		m_Select--;
		if (m_Select < 0) m_Select = SELECT_MAX - 1;

		pSound->PlaySound(CSound::SOUND_LABEL_SELECT);
	}
	else if (pInputKey->GetTrigger(DIK_S) == true || pPad->GetStickTriggerDown() == true || wheel < 0)
	{
		m_Select++;
		if (m_Select >= SELECT_MAX) m_Select = SELECT_GAME;

		pSound->PlaySound(CSound::SOUND_LABEL_SELECT);
	}

	if (CTitle::GetLogo()->GetStop() == true)
	{
		if (pInputMouse->GetTrigger(0) == true || pPad->GetTrigger(CInputPad::JOYKEY_A) == true)
		{
			switch (m_Select)
			{
			case SELECT_GAME:
				pFade->Set(CScene::MODE_GAME);
				break;
			case SELECT_END:
				PostQuitMessage(0);
				break;
			default:
				break;
			}

			pSound->PlaySound(CSound::SOUND_LABEL_CONFIRM);
		}
	}
}
