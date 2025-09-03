//==============================
//
// ��[����[restock.cpp]
// Author : Kaiti Aoto
//
//==============================
#include "sold_out.h"
#include "renderer.h"
#include "manager.h"
#include "debugproc.h"

//
bool CSoldOut::m_bUse = false;

//==================
// �R���X�g���N�^
//==================
CSoldOut::CSoldOut(int nPriority):CObject2D(nPriority)
{
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
}
//================
// �f�X�g���N�^
//================
CSoldOut::~CSoldOut()
{
}
//===========
// ��������
//===========
CSoldOut* CSoldOut::Create(void)
{
	CSoldOut* pObject2D;
	pObject2D = new CSoldOut;
	//������
	pObject2D->Init();
	return pObject2D;
}
//===============
// ����������
//===============
HRESULT CSoldOut::Init(void)
{
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_bUse = true;

	const float fWidth = 200.0f;
	const float fHeight = 120.0f;

	CObject2D::Init("data\\TEXTURE\\empty00.png", { SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2 - 100.0f, 0.0f }, { 0.0f,0.0f,0.0f }, fWidth, fHeight);

	//�I�u�W�F�N�g�̎�ސݒ�
	SetObjType(TYPE_UI);

	return S_OK;
}
//============
// �I������
//============
void CSoldOut::Uninit(void)
{
	CObject2D::Uninit();
}
//============
// �X�V����
//============
void CSoldOut::Update(void)
{
	const float SubAlpha = 0.01f;

	m_col.a -= SubAlpha;

	if (m_col.a <= 0.0f)
	{
		m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		m_bUse = false;
	}

	CObject2D::SetColor(m_col);

	if (m_bUse == false)
	{
		Uninit();
	}
}
//============
// �`�揈��
//============
void CSoldOut::Draw(void)
{
	if (m_bUse == true)
	{
		if (CManager::GetPause() != true)
		{
			CObject2D::SetUse(true);
			CObject2D::Draw();
		}
		else
		{
			CObject2D::SetUse(false);
		}
	}
}