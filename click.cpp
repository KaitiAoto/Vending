//==============================
//
// ��[����[restock.cpp]
// Author:kaiti
//
//==============================
#include "click.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "debugproc.h"

//==================
// �R���X�g���N�^
//==================
CClick::CClick(int nPriority):CObject2D(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bUse = true;
}
//================
// �f�X�g���N�^
//================
CClick::~CClick()
{
}
//===========
// ��������
//===========
CClick* CClick::Create(const char* pTexName, D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CClick* pObject2D;
	pObject2D = new CClick;
	//������
	pObject2D->Init(pTexName, pos, fWidth, fHeight);
	return pObject2D;
}
//===============
// ����������
//===============
HRESULT CClick::Init(const char* pTexName, D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	//�l����
	m_pos = pos;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_bSub = true;

	CObject2D::Init(pTexName, m_pos, D3DXVECTOR3(0.0f,0.0f,0.0f), fWidth, fHeight);

	//�I�u�W�F�N�g�̎�ސݒ�
	SetObjType(TYPE_UI);

	return S_OK;
}
//============
// �I������
//============
void CClick::Uninit(void)
{
	CObject2D::Uninit();
}
//============
// �X�V����
//============
void CClick::Update(void)
{
	Blink();
}
//============
// �`�揈��
//============
void CClick::Draw(void)
{
	//�f�o�C�X�̎擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	if (m_bUse == true)
	{
		//ALPHA�e�X�g�̐ݒ�
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		CObject2D::Draw();

		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	}
}

//===========
// �_��
//===========
void CClick::Blink(void)
{
	const float Sub = 0.025f;

	m_col.a += (m_bSub ? -Sub : Sub);

	if (m_col.a <= 0.0f)
	{
		m_col.a = 0.0f;
		m_bSub = false;
	}
	else if (m_col.a >= 1.0f)
	{
		m_col.a = 1.0f;
		m_bSub = true;
	}

	CObject2D::SetColor(m_col);
}
