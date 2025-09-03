//==============================
//
//  �Q�[�W����[Gauge.cpp]
//  Author : Kaiti Aoto
//
//==============================
#include "gauge_billboard.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
//==================
// �R���X�g���N�^
//==================
CGaugeBillboard::CGaugeBillboard()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pVtxBuff = NULL;
	m_nIdxTex = 0;
	m_Base = 0;
	m_fHeight = 0;
}
//================
// �f�X�g���N�^
//================
CGaugeBillboard::~CGaugeBillboard()
{
}
//===========
// ��������
//===========
CGaugeBillboard* CGaugeBillboard::Create(D3DXVECTOR3 pos, float base, float fHeight, D3DXCOLOR col)
{
	CGaugeBillboard* pGause;
	//
	pGause = new CGaugeBillboard;
	//������
	if (FAILED(pGause->Init(pos, base, fHeight,col)))
	{
		delete pGause;
		return nullptr;
	}

	//�e�N�X�`�����蓖��
	CTexture* pTex = CManager::GetTex();
	pGause->m_nIdxTex = pTex->Register("data\\TEXTURE\\gauge00.jpeg");

	return pGause;
}
//=============
// ����������
//=============
HRESULT CGaugeBillboard::Init(D3DXVECTOR3 pos, float base, float fHeight, D3DXCOLOR col)
{
	//�f�o�C�X�̎擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	m_pos = pos;
	m_Base = base;
	m_fHeight = fHeight;
	m_col = col;
	m_fWidth = -(GAUGE_X * m_Base) / 2;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	Set();

	return S_OK;
}
//==========
// �I������
//==========
void CGaugeBillboard::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}
//==========
// �X�V����
//==========
void CGaugeBillboard::Update(void)
{

}
//===========
// �`�揈��
//===========
void CGaugeBillboard::Draw(void)
{
	//�f�o�C�X�̎擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//�e�N�X�`���擾
	CTexture* pTex = CManager::GetTex();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	D3DXMATRIX mtxView;
	//�r���[�}�g���b�N�X�擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�J�����̋t�s���ݒ�
	m_mtxWorld._11 = mtxView._11;
	m_mtxWorld._12 = mtxView._21;
	m_mtxWorld._13 = mtxView._31;
	m_mtxWorld._21 = mtxView._12;
	m_mtxWorld._22 = mtxView._22;
	m_mtxWorld._23 = mtxView._32;
	m_mtxWorld._31 = mtxView._13;
	m_mtxWorld._32 = mtxView._23;
	m_mtxWorld._33 = mtxView._33;

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTex->GetAddress(m_nIdxTex));

	//�|���S����`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//���C�g��L���ɖ߂�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
//
//
//
void CGaugeBillboard::Set()
{
	VERTEX_3D* pVtx = NULL;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	float fullHalfWidth = (GAUGE_X * m_Base) / 2.0f;
	float currentHalfWidth = fullHalfWidth * m_rate;

	// �E�[�Œ�A���[���E���ֈړ������ďk�߂�
	pVtx[0].pos = D3DXVECTOR3(-fullHalfWidth, m_fHeight, 0.0f);                          // ����
	pVtx[1].pos = D3DXVECTOR3(-fullHalfWidth + currentHalfWidth * 2.0f, m_fHeight, 0.0f);  // �E��
	pVtx[2].pos = D3DXVECTOR3(-fullHalfWidth, -m_fHeight, 0.0f);                         // ����
	pVtx[3].pos = D3DXVECTOR3(-fullHalfWidth + currentHalfWidth * 2.0f, -m_fHeight, 0.0f);  // �E��

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

}