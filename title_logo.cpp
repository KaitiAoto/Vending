//==============================
//
// ��[����[restock.cpp]
// Author : Kaiti Aoto
//
//==============================
#include "title_logo.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "debugproc.h"
#include "easing.h"

//==================
// �R���X�g���N�^
//==================
CTitleLogo::CTitleLogo(int nPriority):CObject2D(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nTime = 0;
	m_bUse = true;
	m_AnimCnt = 0;
}
//================
// �f�X�g���N�^
//================
CTitleLogo::~CTitleLogo()
{
}
//===========
// ��������
//===========
CTitleLogo* CTitleLogo::Create(const char* pTexName, D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CTitleLogo* pObject2D;
	pObject2D = new CTitleLogo;
	//������
	pObject2D->Init(pTexName, pos, fWidth, fHeight);
	return pObject2D;
}
//===============
// ����������
//===============
HRESULT CTitleLogo::Init(const char* pTexName, D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	//�l����
	m_pos = D3DXVECTOR3(pos.x, -fHeight, pos.z);
	m_posStay = pos;
	m_nTime = 0;
	m_bStop = false;

	CObject2D::Init(pTexName, m_pos, m_rot, fWidth, fHeight);

	//�I�u�W�F�N�g�̎�ސݒ�
	SetObjType(TYPE_UI);

	return S_OK;
}
//============
// �I������
//============
void CTitleLogo::Uninit(void)
{
	CObject2D::Uninit();
}
//============
// �X�V����
//============
void CTitleLogo::Update(void)
{
	if (m_AnimCnt < 75.0f)
	{
		m_AnimCnt++;
	}
	else
	{
		m_bStop = true;
	}
	
	m_pos.y = m_posStay.y * CEasing::OutBounce((float)m_AnimCnt / 75.0f);

	CObject2D::SetPos(m_pos);

	if (m_bUse == false)
	{
		Uninit();
	}
}
//============
// �`�揈��
//============
void CTitleLogo::Draw(void)
{
	if (m_bUse == true)
	{
		CObject2D::Draw();
	}
}