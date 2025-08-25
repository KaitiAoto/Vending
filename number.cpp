//=====================
//
// ����[number.h]
// Author:kaiti
//
//=====================
#include "number.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
//�ÓI�����o�ϐ�

//==================
// �R���X�g���N�^
//==================
CNumber::CNumber()
{
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nIdxTex = 0;
}
//================
// �f�X�g���N�^
//================
CNumber::~CNumber()
{
}
//===========
// ��������
//===========
CNumber* CNumber::Create(const char* pFilename, D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CNumber* pNumber;
	pNumber = new CNumber;
	//������
	pNumber->Init(pFilename, pos, fWidth, fHeight);
	return pNumber;
}
//===============
// ����������
//===============
HRESULT CNumber::Init(const char* pFilename, D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();
	//�e�N�X�`���擾
	CTexture* pTex = CManager::GetTex();

	//�l����
	m_pos = pos;
	m_fWidth = fWidth;
	m_fHeight = fHeight;
	
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	
	//���_���W
	pVtx[0].pos.x = m_pos.x - fWidth;
	pVtx[0].pos.y = m_pos.y - fHeight;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + fWidth;
	pVtx[1].pos.y = m_pos.y - fHeight;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x - fWidth;
	pVtx[2].pos.y = m_pos.y + fHeight;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + fWidth;
	pVtx[3].pos.y = m_pos.y + fHeight;
	pVtx[3].pos.z = 0.0f;
	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
	SetTex(0.0f, 0.1f, 0.0f, 1.0f);
	
	m_nIdxTex = pTex->Register(pFilename);
	return S_OK;
}
//============
// �I������
//============
void CNumber::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	//CObject::Release();
}
//============
// �X�V����
//============
void CNumber::Update(void)
{

}
//============
// �`�揈��
//============
void CNumber::Draw(void)
{
	//�f�o�C�X�̎擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();
	//�e�N�X�`���擾
	CTexture* pTex = CManager::GetTex();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
	
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTex->GetAddress(m_nIdxTex));

	//�`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
void CNumber::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W
	pVtx[0].pos.x = m_pos.x - m_fWidth;
	pVtx[0].pos.y = m_pos.y - m_fHeight;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + m_fWidth;
	pVtx[1].pos.y = m_pos.y - m_fHeight;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x - m_fWidth;
	pVtx[2].pos.y = m_pos.y + m_fHeight;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + m_fWidth;
	pVtx[3].pos.y = m_pos.y + m_fHeight;
	pVtx[3].pos.z = 0.0f;

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}
//=====================
// �e�N�X�`�����W�ݒ�
//=====================
void CNumber::SetTex(float U1, float U2, float V1, float V2)
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
void CNumber::SetColor(D3DCOLOR fColor)
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