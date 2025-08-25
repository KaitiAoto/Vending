//================================
//
// �^�C�g������[title.cpp]
// Author:kaiti
//
//================================
#include "fade.h"
#include "manager.h"
#include "renderer.h"

//==================
// �R���X�g���N�^
//==================
CFade::CFade()
{
	
}
//================
// �f�X�g���N�^
//================
CFade::~CFade()
{
}
//
//
//
CFade* CFade::Create(CScene::MODE modeNext)
{
	CFade* pFade = new CFade;

	if (pFade)
	{
		pFade->Init(modeNext);
	}

	return pFade;
}
void CFade::Set(CScene::MODE modeNext)
{
	m_fade = FADE_OUT;
	m_modeNext = modeNext;
}
//=======================
// ������
//=======================
void CFade::Init(CScene::MODE modeNext)
{
	//�f�o�C�X�̎擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();


	m_modeNext = modeNext;
}
//=============
// �I������
//=============
void CFade::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}
//=======================
// �X�V
//=======================
void CFade::Update(void)
{
	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)
		{//�t�F�[�h�C��
			m_col.a -= 0.03f;
			if (m_col.a <= 0.0f)
			{
				m_col.a = 0.0f;
				m_fade = FADE_NONE;
			}
		}
		else if (m_fade == FADE_OUT)
		{//�t�F�[�h�A�E�g
			m_col.a += 0.03f;
			if (m_col.a >= 1.0f)
			{
				m_col.a = 1.0f;
				m_fade = FADE_IN;
				//���[�h�̐ݒ�
				CManager::SetMode(m_modeNext);
				return;
			}
		}
		SetColor(m_col);
	}
}
//=======================
// �`��
//=======================
void CFade::Draw(void)
{
	//�f�o�C�X�̎擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	//�`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}
void CFade::SetColor(D3DXCOLOR col)
{
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

}
