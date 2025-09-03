//==============================
//
// ��[����[restock.cpp]
// Author : Kaiti Aoto
//
//==============================
#include "restock.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "player.h"
#include "debugproc.h"
#include "input.h"

//==================
// �R���X�g���N�^
//==================
CRestock::CRestock(int nPriority):CObject2D(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nIdxTex = 0;
	m_bUse = false;
}
//================
// �f�X�g���N�^
//================
CRestock::~CRestock()
{
}
//===========
// ��������
//===========
CRestock* CRestock::Create(const char* pTexName, D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CRestock* pObject2D;
	pObject2D = new CRestock;
	//������
	pObject2D->Init(pTexName, pos, fWidth, fHeight);
	return pObject2D;
}
//===============
// ����������
//===============
HRESULT CRestock::Init(const char* pTexName, D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//�l����
	m_pos = pos;
	m_bUse = false;

	CObject2D::Init(pTexName, pos, m_rot, fWidth, fHeight);

	//�e�N�X�`�����蓖��
	CTexture* pTex = CManager::GetTex();
	m_nIdxTex = pTex->Register(pTexName);

	//�I�u�W�F�N�g�̎�ސݒ�
	SetObjType(TYPE_RESTOCK);

	return S_OK;
}
//============
// �I������
//============
void CRestock::Uninit(void)
{
	CObject2D::Uninit();
}
//============
// �X�V����
//============
void CRestock::Update(void)
{

}
//============
// �`�揈��
//============
void CRestock::Draw(void)
{
	if (m_bUse == true)
	{
		CObject2D::Draw();
	}
}
//=============
// �ݒ菈��
//=============
void CRestock::Set(int nRestock, CBullet::TYPE type, CVender* pVender)
{
	CDebugProc* pDegub = CManager::GetDebug();

	//�L�[�擾
	CInputKey* pInputKey = CManager::GetInputKey();
	//�p�b�h
	CInputPad* pInputPad = CManager::GetInputPad();

	//�v���C���[���擾
	CPlayer* pPlayer = CGame::GetPlayer();

	CScoreMana* pTotalScore = CGame::GetTotalScore();

	pDegub->Print("��[�\");
	m_bUse = true;
	if (pInputKey->GetTrigger(DIK_F) == true || pInputPad->GetTrigger(CInputPad::JOYKEY_Y) == true)
	{
		//���g��[
		pPlayer->AddContents(nRestock);
		//��ސݒ�
		pPlayer->SetBulletType(type);

		pVender->SetUseRestock(false);
		m_bUse = false;

		CGame::GetFlash()->SetColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.5f));

		CSound* pSound = CManager::GetSound();
		pSound->PlaySound(CSound::SOUND_LABEL_RESTOCK);

		pTotalScore->AddScore(50);

		//�`���[�g���A���N���A����
		if (CGame::GetMode() == CGame::MODE_TUTORIAL)
		{
			CTutorial* pTutorial = CGame::GetTutorial();
			if (pTutorial != nullptr)
			{
				if (pTutorial->GetType() == CTutorial::TYPE_RESTOCK)
				{
					CGame::GetTutorial()->SetClear(true);
				}
			}
		}
	}
}