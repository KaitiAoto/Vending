//==============================
//
// �e[shadow.cpp]
// Author:kaiti
//
//==============================
#include "shadow.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
//==================
// �R���X�g���N�^
//==================
CShadow::CShadow(int nPriority):CObject3D(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_fLength = 0;
	m_fRadius = 0;

	m_bUse = true;
	m_nIdxTex = 0;
}
//================
// �f�X�g���N�^
//================
CShadow::~CShadow()
{
}
//===========
// ��������
//===========
CShadow* CShadow::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius)
{
	CShadow* pEffect;
	//
	pEffect = new CShadow;
	//������
	if (FAILED(pEffect->Init(pos, rot, fRadius)))
	{
		delete pEffect;
		return nullptr;
	}

	return pEffect;
}
//===============
// ����������
//===============
HRESULT CShadow::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius)
{
	m_pos = pos;
	m_rot = rot;
	m_fRadius = fRadius;
	m_fLength=(sqrtf(fRadius * fRadius + fRadius * fRadius) / 2.0f);

	CObject3D::Init("data\\TEXTURE\\shadow000.jpg", m_pos, rot, fRadius, fRadius, CObject3D::TYPE_SHADOW);

	SetObjType(CObject::TYPE_SHADOW);
	
	return S_OK;
}
//============
// �I������
//============
void CShadow::Uninit(void)
{
	CObject3D::Uninit();
}
//============
// �X�V����
//============
void CShadow::Update(void)
{
	if (m_bUse == true)
	{
		SetPos(D3DXVECTOR3(m_pos.x, 0.1f, m_pos.z));
	}
	else if (m_bUse == false)
	{//�g���Ă��Ȃ��Ȃ�
		Uninit();
	}
}
//============
// �`�揈��
//============
void CShadow::Draw(void)
{
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	if (m_bUse == true)
	{
		//���Z�����̐ݒ�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

		CObject3D::Draw();

		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

		//�ݒ�����ɖ߂�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
}