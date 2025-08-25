//==============================
//
// ����[explosion.cpp]
// Author:kaiti
//
//==============================
#include "explosion.h"
#include "renderer.h"
#include "manager.h"
//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = NULL;
//==================
// �R���X�g���N�^
//==================
CExplosion::CExplosion(int nPriority) :
	m_fAngle(atan2f(EXPLOSION_SIZE, EXPLOSION_SIZE))
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_fLength = 0;

	m_nCntAnim = 0;
	m_nPattermAnim = 0;
	m_type = TYPE_A;
	m_nLife = 0;

	m_bUse = true;
}
//================
// �f�X�g���N�^
//================
CExplosion::~CExplosion()
{
}
//===========
// ��������
//===========
CExplosion* CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE type)
{
	CExplosion* pBullet;
	//
	pBullet = new CExplosion;
	//������
	pBullet->SetType(type);
	//������
	if (FAILED(pBullet->Init(pos, rot, EXPLOSION_SIZE, EXPLOSION_SIZE)))
	{
		delete pBullet;
		return nullptr;
	}

	//�e�N�X�`��
	pBullet->BindTexture(m_pTexture);

	return pBullet;
}
//=====================
// �e�N�X�`���ǂݍ���
//=====================
HRESULT CExplosion::Load(void)
{
	//�f�o�C�X�̎擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\explosion000.png",
		&m_pTexture);

	return S_OK;
}
//=================
// �e�N�X�`���j��
//=================
void CExplosion::Unload(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
HRESULT CExplosion::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	return S_OK;
}
//===============
// ����������
//===============
HRESULT CExplosion::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight)
{
	m_move = D3DXVECTOR3(sinf(rot.z + D3DX_PI) * 2.0f, cosf(rot.z + D3DX_PI) * 2.0f, 0.0f);
	m_nLife = EXPLOSION_LIFE;

	m_fLength=(sqrtf(EXPLOSION_SIZE * EXPLOSION_SIZE + EXPLOSION_SIZE * EXPLOSION_SIZE) / 2.0f);
	
	//������
	CObject2D::Init(pos, rot, fWidth, fHeight);
	
	//�e�N�X�`���ݒ�
	SetTex(0.0f,0.125f,0.0f, 1.0f);

	if (m_type == TYPE_A)
	{
		SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
	}
	else if (m_type == TYPE_B)
	{
		SetColor(D3DCOLOR_RGBA(255, 0, 0, 255));
	}
	SetObjType(TYPE_EXPLOSION);

	return S_OK;
}
//============
// �I������
//============
void CExplosion::Uninit(void)
{
	CObject2D::Uninit();
}
//============
// �X�V����
//============
void CExplosion::Update(void)
{
	if (m_bUse == true)
	{
		//�A�j���[�V����
		Animation();

		//����
		if (m_nLife <= 0)
		{
			m_bUse = false;
		}
	}
	else if (m_bUse == false)
	{//�g���Ă��Ȃ��Ȃ�
		Uninit();
	}
}
//============
// �`�揈��
//============
void CExplosion::Draw(void)
{
	if (m_bUse == true)
	{
		CObject2D::Draw();
	}
}
//======================
// �A�j���[�V��������
//======================
void CExplosion::Animation(void)
{
	m_nCntAnim++;
	if ((m_nCntAnim % 10) == 0)
	{//��莞�Ԍo��
		//�p�^�[��No���X�V
		m_nPattermAnim = (m_nPattermAnim + 1) % 8;

		SetTex((m_nPattermAnim % 8) * 0.125f, (m_nPattermAnim % 8) * 0.125f + 0.125f, 0.0f, 1.0f);
	}
	if (m_nCntAnim == 64)
	{
		m_nLife = 0;
	}
}
