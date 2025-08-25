//==============================
//
// �����Ȃ���[wall_invisible.cpp]
// Author:kaiti
//
//==============================
#include "wall_invisible.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "debugproc.h"
#include "input.h"
//==================
// �R���X�g���N�^
//==================
CInvisibleWall::CInvisibleWall(int nPriority):CObject3D(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
	m_bUse = true;
	m_nIdxTex = 0;
	m_bDraw = false;
}
//================
// �f�X�g���N�^
//================
CInvisibleWall::~CInvisibleWall()
{
}
//===========
// ��������
//===========
CInvisibleWall* CInvisibleWall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight)
{
	CInvisibleWall* pEffect;
	//
	pEffect = new CInvisibleWall;
	//������
	if (FAILED(pEffect->Init(pos, rot, fWidth, fHeight)))
	{
		delete pEffect;
		return nullptr;
	}

	return pEffect;
}
D3DXVECTOR3 CInvisibleWall::GetSize()
{
	return D3DXVECTOR3(m_fWidth * 2.0f, m_fHeight * 2.0f, 10.0f);
}
//===============
// ����������
//===============
HRESULT CInvisibleWall::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight)
{
	m_pos = pos;
	m_rot = rot;
	m_fWidth = fWidth;
	m_fHeight = fHeight;

	CObject3D::Init(NULL, m_pos, m_rot, m_fWidth, m_fHeight, CObject3D::TYPE_WALL);
	SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

	SetObjType(CObject::TYPE_WALL);
	
	return S_OK;
}
//============
// �I������
//============
void CInvisibleWall::Uninit(void)
{
	CObject3D::Uninit();
}
//============
// �X�V����
//============
void CInvisibleWall::Update(void)
{
#ifdef _DEBUG
	CInputKey* pInputKey = CManager::GetInputKey();
	if (pInputKey->GetTrigger(DIK_F2) == true)
	{//bUse�؂�ւ�
		m_bDraw = !m_bDraw;
	}
#endif

}
//============
// �`�揈��
//============
void CInvisibleWall::Draw(void)
{
	//CDebugProc* pDegub = CManager::GetDebug();
	//pDegub->Print("�ǂ̈ʒu�F%.1f,%.1f,%.1f", m_pos.x, m_pos.y, m_pos.z);

	if (m_bDraw == true)
	{
		CObject3D::Draw();
	}
}