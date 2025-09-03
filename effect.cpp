//==============================
//
// �G�t�F�N�g[effect.cpp]
// Author : Kaiti Aoto
//
//==============================
#include "effect.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
//==================
// �R���X�g���N�^
//==================
CEffect::CEffect(int nPriority):CObject(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_fLength = 0;
	m_fAngle = atan2f(EFFECT_SIZE, EFFECT_SIZE);
	m_fRadius = 0;

	m_bUse = false;
	m_pVtxBuff = NULL;
	m_nIdxTex = 0;
	m_nLife = 0;
}
//================
// �f�X�g���N�^
//================
CEffect::~CEffect()
{
}
//===========
// ��������
//===========
CEffect* CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, D3DXCOLOR col, int nLife, float fRadius)
{
	CEffect* pEffect = nullptr;
	//
	pEffect = new CEffect;
	//������
	if (FAILED(pEffect->Init(pos, rot, move, col,nLife, fRadius)))
	{
		delete pEffect;
		return nullptr;
	}

	return pEffect;
}
CEffect* CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, D3DXCOLOR col, int nLife, float fRadius, int nPriority)
{
	CEffect* pEffect = nullptr;
	//
	pEffect = new CEffect(nPriority);
	//������
	if (FAILED(pEffect->Init(pos, rot, move, col, nLife, fRadius)))
	{
		delete pEffect;
		return nullptr;
	}

	return pEffect;
}
//===============
// ����������
//===============
HRESULT CEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, D3DXCOLOR col, int nLife, float fRadius)
{
	m_pos = pos;
	m_rot = rot;
	m_fRadius = fRadius;
	m_col = col;
	m_fLength=(sqrtf(fRadius * fRadius + fRadius * fRadius) / 2.0f);
	m_move = move;
	m_nLife = nLife;
	m_bUse = true;
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
	pVtx[0].pos = D3DXVECTOR3(- fRadius,+ fRadius, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+ fRadius,+ fRadius, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(- fRadius,- fRadius, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+ fRadius,- fRadius, 0.0f);

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

	//�e�N�X�`�����蓖��
	CTexture* pTex = CManager::GetTex();
	m_nIdxTex = pTex->Register("data\\TEXTURE\\effect000.png");

	SetObjType(TYPE_EFFECT);
	
	return S_OK;
}
//============
// �I������
//============
void CEffect::Uninit(void)
{
	m_bUse = false;
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	CObject::Release();
}
//============
// �X�V����
//============
void CEffect::Update(void)
{
	if (m_bUse == true)
	{
		m_pos += m_move;

		m_fRadius -= 0.1f;
		if (m_fRadius <= 0.0f)
		{
			m_fRadius = 0.0f;
			m_bUse = false;
			return;
		}

		m_col.a -= 0.01f;
		if (m_col.a <= 0.0f)
		{
			m_col.a = 0.0f;
			m_bUse = false;
			return;
		}

		//m_nLife--;
		//if (m_nLife <= 0)
		//{
		//	m_nLife = 0;
		//	m_bUse = false;
		//}

		SetSize(m_fRadius);
		SetColor(m_col);
	}
	else
	{
		Uninit();
		return;
	}
}
//============
// �`�揈��
//============
void CEffect::Draw(void)
{
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//�e�N�X�`���擾
	CTexture* pTex = CManager::GetTex();

	if (m_bUse == true)
	{
		//���C�g�𖳌��ɂ���
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		//�y�e�X�g
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

		//ALPHA�e�X�g�̐ݒ�
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		//���Z����
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

		//�v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxRot, mtxTrans;

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

		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

		//���C�g��L���ɖ߂�
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}
}
//===========
// �傫��
//===========
void CEffect::SetSize(float fRadius)
{
	VERTEX_3D* pVtx = NULL;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(- fRadius,+ fRadius, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+ fRadius,+ fRadius, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(- fRadius,- fRadius, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+ fRadius,- fRadius, 0.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}
//======
// �F
//======
void CEffect::SetColor(D3DXCOLOR col)
{
	m_col = col;
	VERTEX_3D* pVtx = NULL;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}