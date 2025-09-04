//================================================================
//
// �e���J�E���^�[�}�l�[�W���[[bullet_counter_manager.cpp]
// Author : Kaiti Aoto
//
//================================================================

// �C���N���[�h
#include "bullet_counter_manager.h"
#include "renderer.h"
#include "manager.h"
#include "object.h"
#include "player.h"

// �ÓI�����o�ϐ�
int CBulletCntMana::m_nCount = 0;
CBullerCounter* CBulletCntMana::m_pCounter[MAX_BULLETCNT] = {};
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
	// ����
	CBulletCntMana* pBulletCntMana = new CBulletCntMana;
	// ������
	if (FAILED(pBulletCntMana->Init(pos)))
	{// NULL�`�F�b�N
		delete pBulletCntMana;
		return nullptr;
	}
	return pBulletCntMana;	// �|�C���^��Ԃ�
}
//===============
// ����������
//===============
HRESULT CBulletCntMana::Init(D3DXVECTOR3 pos)
{
	// �e�A�C�R������
	m_pIcon = CBulletIcon::Create(D3DXVECTOR3(pos.x - (BULLET_COUNT_SIZE * 4.5f), pos.y, 0.0f), BULLETICON_SIZE, BULLETICON_SIZE);

	// �~����
	CObject2D::Create("data\\TEXTURE\\multiply00.png", D3DXVECTOR3(pos.x - (BULLET_COUNT_SIZE * 2.0f), pos.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BULLETICON_SIZE, BULLETICON_SIZE, 8);

	// �������J�E���^�[����
	for (int nCnt = 0; nCnt < MAX_BULLETCNT; nCnt++)
	{
		m_pCounter[nCnt] = CBullerCounter::Create(D3DXVECTOR3(pos.x + (nCnt * BULLET_COUNT_SIZE * 2.5f), pos.y, 0.0f));
	}

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
	// �v���C���[���擾
	CPlayer* pPlayer = CGame::GetPlayer();

	// ���݂̏��������擾
	m_nCount = pPlayer->GetContents();
	
	// �J�E���^�[�X�V
	UpdateCounter();
}
//============
// �`�揈��
//============
void CBulletCntMana::Draw(void)
{
}
//===================
// �J�E���^�[�X�V
//===================
void CBulletCntMana::UpdateCounter(void)
{	
	int aPosTexU[MAX_BULLETCNT] = {};	// �e���̒l�i�[�p�ϐ�
	// �e���̒l�v�Z�p��l�ϐ�
	int nData = BULLETCNTDATA * 10;
	int nData2 = BULLETCNTDATA;

	// ���g���O�Ȃ�
	if (m_nCount <= 0)
	{
		m_nCount = 0;	// �O�ɐݒ�
	}

	// �e�N�X�`���؂�ւ�
	for (int nCnt = 0; nCnt < MAX_BULLETCNT; nCnt++)
	{
		if (m_pCounter[nCnt] != nullptr)
		{// NULL�`�F�b�N
			// �����̃|�C���^�擾
			CNumber* pNumber = m_pCounter[nCnt]->GetNumber();

			// ���P���̒l���v�Z
			aPosTexU[nCnt] = m_nCount % nData / nData2;

			// ���̌��p�Ɋ�l��1/10����
			nData /= 10;
			nData2 /= 10;

			// �e�N�X�`���؂�ւ�
			pNumber->SetTex((aPosTexU[nCnt] * 0.1f), (aPosTexU[nCnt] * 0.1f) + 0.1f, 0.0f, 1.0f);
		}
	}
}