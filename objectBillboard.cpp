//=====================================
//
// �r���{�[�h�\������[billboard.cpp]
// Author : Kaiti Aoto
//
//=====================================
#include "objectBillboard.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"

//================
// �R���X�g���N�^
//================
CObjectBillboard::CObjectBillboard(int nPriority):CObject(nPriority)
{
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_mtxWorld = {};
	m_nIdxTex = 0;
}
//================
// �f�X�g���N�^
//================
CObjectBillboard::~CObjectBillboard()
{
}
//===========
// ��������
//===========
CObjectBillboard* CObjectBillboard::Create(const char* pTexName, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight)
{
	CObjectBillboard* pObject2D;
	pObject2D = new CObjectBillboard;
	//������
		//������
	if (FAILED(pObject2D->Init(pTexName, pos, rot, fWidth, fHeight)))
	{
		delete pObject2D;
		return nullptr;
	}

	return pObject2D;
}
CObjectBillboard* CObjectBillboard::Create(const char* pTexName, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, int nPriority)
{
	CObjectBillboard* pObject2D;
	pObject2D = new CObjectBillboard(nPriority);
	//������
		//������
	if (FAILED(pObject2D->Init(pTexName, pos, rot, fWidth, fHeight)))
	{
		delete pObject2D;
		return nullptr;
	}

	return pObject2D;
}
//==================
// ����������
//==================
HRESULT CObjectBillboard::Init(const char* pTexName, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight)
{
	//�f�o�C�X�̎擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	m_pos = pos;
	m_rot = rot;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_3D,
		                        D3DPOOL_MANAGED,
		                        &m_pVtxBuff,
		                        NULL);
	VERTEX_3D* pVtx = NULL;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(- fWidth, + fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+ fWidth, + fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(- fWidth, - fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+ fWidth, - fHeight, 0.0f);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	//�e�N�X�`�����蓖��
	CTexture* pTex = CManager::GetTex();
	m_nIdxTex = pTex->Register(pTexName);

	return S_OK;
}
//==============
// �I������
//==============
void CObjectBillboard::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	CObject::Release();
}
//=============
// �X�V����
//=============
void CObjectBillboard::Update(void)
{

}
//============
// �`�揈��
//============
void CObjectBillboard::Draw(void)
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
//=============
// �ݒ菈��
//=============
void CObjectBillboard::SetSize(float fRadius)
{
	VERTEX_3D* pVtx = NULL;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x-fRadius, m_pos.y+fRadius, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x+fRadius, m_pos.y+fRadius, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x -fRadius, m_pos.y-fRadius, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x+fRadius, m_pos.y-fRadius, 0.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}
void CObjectBillboard::SetColor(D3DXCOLOR col)
{
	VERTEX_3D* pVtx = NULL;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̐ݒ�
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}