//================================
//
// ���U���g����[result.cpp]
// Author:kaiti
//
//================================
#include "pause.h"
#include "manager.h"
#include "object2D.h"
#include "renderer.h"
//
CPauseMana* CPause::m_pPauseMana = NULL;
CClick* CPause::m_pClick = NULL;

//==================
// �R���X�g���N�^
//==================
CPause::CPause()
{

}
//================
// �f�X�g���N�^
//================
CPause::~CPause()
{
}
//
//
//
CPause* CPause::Create()
{
	CPause* pPause = new CPause;

	if (pPause != nullptr)
	{
		pPause->Init();
	}

	return pPause;
}
//=======================
// ������
//=======================
void CPause::Init(void)
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
	pVtx[0].col = D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.5f);
	pVtx[1].col = D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.5f);
	pVtx[2].col = D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.5f);
	pVtx[3].col = D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.5f);
	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();


	if (m_pPauseMana == nullptr)
	{
		m_pPauseMana = CPauseMana::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2.0f, 0.0f));
	}

	m_pClick = CClick::Create("data\\TEXTURE\\next00.png", D3DXVECTOR3(SCREEN_WIDTH - (CLICK_SIZE_X / 1.5f), SCREEN_HEIGHT - (CLICK_SIZE_Y / 1.5f), 0.0f), CLICK_SIZE_X, CLICK_SIZE_Y);
	m_pClick->SetUse(false);
}
//=============
// �I������
//=============
void CPause::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	if (m_pPauseMana != nullptr)
	{
		m_pPauseMana->Uninit();
		delete m_pPauseMana;
		m_pPauseMana = nullptr;
	}
}
//=======================
// �X�V
//=======================
void CPause::Update(void)
{
	if (CManager::GetPause() == true)
	{
		if (m_pPauseMana != nullptr)
		{
			m_pPauseMana->Update();
			m_pClick->Update();
		}
	}
	m_pClick->SetUse(CManager::GetPause());
}
//=======================
// �`��
//=======================
void CPause::Draw(void)
{
	if (CManager::GetPause() == true)
	{

	}
}

