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
CEnemyBaseGauge* CEnemyBaseGauge::Create(D3DXVECTOR3 pos, float base, float fHeight, D3DXCOLOR col, CBullet::TYPE type, CEnemyBase* pEnemyBase)
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
HRESULT CEnemyBaseGauge::Init(D3DXVECTOR3 pos, float base, float fHeight, D3DXCOLOR col, CBullet::TYPE type)
{
	m_pos = pos;
	m_Base = base;
	m_fHeight = fHeight;
	m_col = col;

	m_pGauge = CGaugeBillboard::Create(m_pos, m_Base, m_fHeight, m_col);

	const char* pTexName = {};	// �e�N�X�`�����i�[�p�ϐ�

	// ��ޕʂɃe�N�X�`�������w��
	switch (type)
	{
	case CBullet::TYPE_CAN:
		pTexName = "data\\TEXTURE\\bullet00.png";
		break;
	case CBullet::TYPE_ICE:
		pTexName = "data\\TEXTURE\\bullet01.png";
		break;
	case CBullet::TYPE_CAPSULE:
		pTexName = "data\\TEXTURE\\bullet02.png";
		break;
	case CBullet::TYPE_PETBOTTLE:
		pTexName = "data\\TEXTURE\\bullet03.png";
		break;
	case CBullet::TYPE_DUST:
		pTexName = "data\\TEXTURE\\bullet04.png";
		break;
	case CBullet::TYPE_SNACK:
		pTexName = "data\\TEXTURE\\bullet05.png";
		break;
	case CBullet::TYPE_CIGARET:
		pTexName = "data\\TEXTURE\\bullet06.png";
		break;
	case CBullet::TYPE_CARD:
		pTexName = "data\\TEXTURE\\card00.jpg";
		break;
	case CBullet::TYPE_BOTTLE:
		pTexName = "data\\TEXTURE\\bullet08.png";
		break;
	default:
		break;
	}

	m_pIcon = CObjectBillboard::Create(pTexName, m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_fHeight, m_fHeight, 7);

	//CObject2D::Create("data\\TEXTURE\\gaugeHP01.png", D3DXVECTOR3(m_pos.x + (m_Base * GAUGE_X / 2.2f) + 10.0f, m_pos.y, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), (float)(m_Base * GAUGE_X) * 1.17f, (m_fHeight * 2) + 50.0f);

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

		m_pIcon->SetPos(m_pos);
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