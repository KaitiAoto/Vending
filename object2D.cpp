//==============================
//
// �I�u�W�F�N�g2D[object2D.cpp]
// Author:kaiti
//
//==============================
#include "object2D.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
//==================
// �R���X�g���N�^
//==================
CObject2D::CObject2D(int nPriority):CObject(nPriority)
{
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fLength = 0.0f;
	m_fAngle = 0.0f;
	m_nIdxTex = 0;
	m_bUse = true;
}
//================
// �f�X�g���N�^
//================
CObject2D::~CObject2D()
{
}
//===========
// ��������
//===========
CObject2D* CObject2D::Create(const char* pTexName, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight)
{
	CObject2D* pObject2D;
	pObject2D = new CObject2D;
	//������
	pObject2D->Init(pTexName, pos, rot, fWidth, fHeight);
	return pObject2D;
}
CObject2D* CObject2D::Create(const char* pTexName, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, int nPriority)
{
	CObject2D* pObject2D;
	pObject2D = new CObject2D(nPriority);
	//������
	pObject2D->Init(pTexName, pos, rot, fWidth, fHeight);
	return pObject2D;
}

//===============
// ����������
//===============
HRESULT CObject2D::Init(const char* pTexName, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//�l����
	m_pos = pos;
	m_rot = rot;
	m_bUse = true;
	m_fLength = sqrtf(fWidth * fWidth + fHeight * fHeight) / 2.0f;
	m_fAngle = atan2f(fWidth, fHeight);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);
	//�o�b�t�@�ݒ�
	SetBuff(m_pVtxBuff);
	//���_���W�ݒ�
	Set(m_pos, m_rot);
	//�J���[�ݒ�
	SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
	//�e�N�X�`�����W�ݒ�
	SetTex(0.0f, 1.0f, 0.0f, 1.0f);

	//�e�N�X�`�����蓖��
	CTexture* pTex = CManager::GetTex();
	m_nIdxTex = pTex->Register(pTexName);

	return S_OK;
}
//============
// �I������
//============
void CObject2D::Uninit(void)
{
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
void CObject2D::Update(void)
{

}
//============
// �`�揈��
//============
void CObject2D::Draw(void)
{
	//�f�o�C�X�̎擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	CTexture* pTex = CManager::GetTex();
	if (m_bUse == true)
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		LPDIRECT3DTEXTURE9 tex = pTex->GetAddress(m_nIdxTex);
		if (tex != NULL)
		{
			pDevice->SetTexture(0, tex);
		}
		else
		{
			pDevice->SetTexture(0, NULL);
		}

		//// �e�N�X�`���Ȃ��ł��`�悷��悤�A�K�؂ɐݒ�
		//if (!tex) {
		//	// �e�N�X�`���Ȃ��p�̃����_�[�X�e�[�g�ݒ�
		//	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG2);
		//	pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		//}
		//else {
		//	// �e�N�X�`������̏ꍇ�i�ʏ�j
		//	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		//	pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		//	pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		//}

		//�`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}
//=====================
// �e�N�X�`�����W�ݒ�
//=====================
void CObject2D::SetTex(float U1, float U2, float V1, float V2)
{
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(U1, V1);
	pVtx[1].tex = D3DXVECTOR2(U2, V1);
	pVtx[2].tex = D3DXVECTOR2(U1, V2);
	pVtx[3].tex = D3DXVECTOR2(U2, V2);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}
//=====================
// �J���[�ݒ�
//=====================
void CObject2D::SetColor(D3DCOLOR fColor)
{
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W
	pVtx[0].col = fColor;
	pVtx[1].col = fColor;
	pVtx[2].col = fColor;
	pVtx[3].col = fColor;

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}
//=====================
// �J���[�ݒ�
//=====================
void CObject2D::SetColor(D3DXCOLOR fColor)
{
	SetColor(D3DCOLOR_COLORVALUE(fColor.r, fColor.g, fColor.b, fColor.a));
}

//==============
// �T�C�Y�ݒ�
//==============
void CObject2D::SetSize(float fWidth, float fHeight)
{
	m_fLength = sqrtf(fWidth * fWidth + fHeight * fHeight) / 2.0f;
	m_fAngle = atan2f(fWidth, fHeight);

	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z + (-D3DX_PI + m_fAngle)) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z + (-D3DX_PI + m_fAngle)) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + (-D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + (-D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.z = 0.0f;
	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

}
//=============
// �ݒ菈��
//=============
void CObject2D::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_pos = pos;
	m_rot = rot;

	//���_���W
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z + (-D3DX_PI + m_fAngle)) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z + (-D3DX_PI + m_fAngle)) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + (-D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + (-D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.z = 0.0f;
	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}