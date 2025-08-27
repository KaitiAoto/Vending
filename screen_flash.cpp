//==============================
//
// ��[����[restock.cpp]
// Author:kaiti
//
//==============================
#include "screen_flash.h"
#include "renderer.h"
#include "manager.h"
#include "debugproc.h"

//==================
// �R���X�g���N�^
//==================
CScreenFlash::CScreenFlash(int nPriority):CObject2D(nPriority)
{
	m_bUse = false;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
}
//================
// �f�X�g���N�^
//================
CScreenFlash::~CScreenFlash()
{
}
//===========
// ��������
//===========
CScreenFlash* CScreenFlash::Create(void)
{
	CScreenFlash* pObject2D;
	pObject2D = new CScreenFlash;
	//������
	pObject2D->Init();
	return pObject2D;
}
//===============
// ����������
//===============
HRESULT CScreenFlash::Init(void)
{
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	m_bUse = false;

	CObject2D::Init(nullptr, { SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f }, { 0.0f,0.0f,0.0f }, SCREEN_WIDTH, SCREEN_HEIGHT);
	//�I�u�W�F�N�g�̎�ސݒ�
	SetObjType(TYPE_UI);

	return S_OK;
}
//============
// �I������
//============
void CScreenFlash::Uninit(void)
{
	CObject2D::Uninit();
}
//============
// �X�V����
//============
void CScreenFlash::Update(void)
{
	const float SubAlpha = 0.01f;

	m_col.a -= SubAlpha;

	if (m_col.a <= 0.0f)
	{
		m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		m_bUse = false;
	}

	CObject2D::SetColor(m_col);
}
//============
// �`�揈��
//============
void CScreenFlash::Draw(void)
{
	if (m_bUse == true)
	{
		CObject2D::Draw();
	}
}