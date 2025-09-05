//==============================
//
//  �^�C�}�[����[.cpp]
//  Author : Kaiti Aoto
//
//==============================
#include "gauge_enemybase.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "texture.h"
#include "object2D.h"
#include "map_enemybase.h"

//==================
// �R���X�g���N�^
//==================
CEnemyBaseGauge::CEnemyBaseGauge(int nPriority):CObject(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Base = 0;
	m_fHeight = 0;
	m_pGauge = nullptr;
}
//================
// �f�X�g���N�^
//================
CEnemyBaseGauge::~CEnemyBaseGauge()
{
}
//===========
// ��������
//===========
CEnemyBaseGauge* CEnemyBaseGauge::Create(D3DXVECTOR3 pos, float base, float fHeight, D3DXCOLOR col, TYPE type, CEnemyBase* pEnemyBase)
{
	CEnemyBaseGauge* pGause;
	//
	pGause = new CEnemyBaseGauge;
	//������
	if (FAILED(pGause->Init(pos, base, fHeight, col,type)))
	{
		delete pGause;
		return nullptr;
	}
	pGause->m_pEnemyBase = pEnemyBase;
	return pGause;
}
//=============
// ����������
//=============
HRESULT CEnemyBaseGauge::Init(D3DXVECTOR3 pos, float base, float fHeight, D3DXCOLOR col, TYPE type)
{
	m_pos = pos;
	m_Base = base;
	m_fHeight = fHeight;
	m_col = col;
	m_pGauge = CGaugeBillboard::Create(m_pos, m_Base, m_fHeight, m_col);
	m_type = type;

	const char* pTexName = {};	// �e�N�X�`�����i�[�p�ϐ�
	
	// ��ޕʂɃe�N�X�`�������w��
	switch (type)
	{
	case TYPE_DRINK:
		pTexName = "data\\TEXTURE\\stock00.png";
		break;
	case TYPE_FOOD:
		pTexName = "data\\TEXTURE\\stock01.png";
		break;
	case TYPE_GENERAL:
		pTexName = "data\\TEXTURE\\stock02.png";
		break;
	default:
		break;
	}

	m_pIcon = CObjectBillboard::Create(pTexName, m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_fHeight * 3.0f, m_fHeight, 7);

	//�I�u�W�F�N�g�̎�ސݒ�
	SetObjType(TYPE_GAUGE);

	return S_OK;
}
//==========
// �I������
//==========
void CEnemyBaseGauge::Uninit(void)
{
	if (m_pGauge != nullptr)
	{
		m_pGauge->Uninit();
		delete m_pGauge;
		m_pGauge = nullptr;
	}
	CObject::Release();
}
//==========
// �X�V����
//==========
void CEnemyBaseGauge::Update(void)
{
	if (m_rate > 0.7f)
	{
		// ���邢���F
		m_col = D3DXCOLOR(0.0f, 1.0f, 0.0f,1.0f);

		m_pEnemyBase->GetMapIcon()->SetBlink(false);
	}
	else if (m_rate > 0.4f)
	{
		// �I�����W
		m_col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

		m_pEnemyBase->GetMapIcon()->SetBlink(false);
	}
	else if (m_rate > 0.1f)
	{
		// �s���N���̐�
		m_col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		m_pEnemyBase->GetMapIcon()->SetBlink(true);
	}

	if (m_bDraw == true)
	{
		m_pGauge->SetBase(m_Base);
		m_pGauge->SetRate(m_rate);
		m_pGauge->SetColor(m_col);
		m_pGauge->SetPos(m_pos);
		m_pGauge->Set();
	}

	m_pIcon->SetDraw(m_bDraw);
}
//===========
// �`�揈��
//===========
void CEnemyBaseGauge::Draw(void)
{
	if (m_bDraw == true)
	{
		m_pGauge->Draw();
	}
}