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