//==============================
//
// �o�t�A�C�R��[buff_icon.cpp]
// Author : Kaiti Aoto
//
//==============================

// �C���N���[�h
#include "buff_icon.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "debugproc.h"
#include "input.h"

//==================
// �R���X�g���N�^
//==================
CBuffIcon::CBuffIcon(int nPriority):CObject2D(nPriority)
{
	// �l���N���A
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bUse = true;
	m_bClear = false;
	m_type = CBuff::TYPE_NONE;
	m_nIdxTex = 0;
}
//================
// �f�X�g���N�^
//================
CBuffIcon::~CBuffIcon()
{
}
//===========
// ��������
//===========
CBuffIcon* CBuffIcon::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// ����
	CBuffIcon* pBuffIcon = new CBuffIcon;
	//������
	if (FAILED(pBuffIcon->Init(pos, fWidth, fHeight)))
	{// NULL�`�F�b�N
		delete pBuffIcon;
		return nullptr;
	}
	return pBuffIcon;	// �|�C���^��Ԃ�
}
//===============
// ����������
//===============
HRESULT CBuffIcon::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	//�l����
	m_posStay = pos;
	m_posOut = pos + D3DXVECTOR3(-fWidth, 0.0f, 0.0f);
	m_pos = m_posOut;

	// �����o�ϐ���������
	m_state = STATE_SLIDEIN;	// ��Ԃ��X���C�h�C����
	m_bUse = true;				// �g�p�����Ԃ�
	m_bClear = false;			// �N���A���Ă��Ȃ���Ԃ�

	// �e�N�X�`����
	const char* apFileName[CBuff::TYPE_MAX] =
	{
		"data\\TEXTURE\\speedUP00.png",
	};

	// �e�N�X�`������o�^
	for (int nCnt = 0; nCnt < CBuff::TYPE_MAX; nCnt++)
	{	
		m_apFileName[nCnt] = apFileName[nCnt];
	}

	// �I�u�W�F�N�g2D�̏�����
	CObject2D::Init(m_apFileName[m_type], pos, m_rot, fWidth, fHeight);

	//�e�N�X�`�����蓖��
	CTexture* pTex = CManager::GetTex();				// �e�N�X�`���̃|�C���^�擾
	m_nIdxTex = pTex->Register(m_apFileName[m_type]);	// �e�N�X�`�����蓖��
	CObject2D::SetIdxTex(m_nIdxTex);					// �I�u�W�F�N�g2D�̃C���f�b�N�X�ԍ���ݒ�

	//�I�u�W�F�N�g�̎�ސݒ�
	SetObjType(TYPE_UI);

	return S_OK;
}
//============
// �I������
//============
void CBuffIcon::Uninit(void)
{
	// �I�u�W�F�N�g2D�̏I������
	CObject2D::Uninit();
}
//============
// �X�V����
//============
void CBuffIcon::Update(void)
{
	const float fSpeed = 8.0f;	// �X���C�h�X�s�[�h

	// ���
	switch (m_state)
	{
	// �ҋ@
	case STATE_STAY:
	{
		CBuff::TYPE type = CGame::GetBuff()->GetType();	// ���݂̃o�t�̎�ނ��擾

		// �����o�t���������Ă��Ȃ����
		if (type == CBuff::TYPE_NONE)
		{
			m_bClear = true;	// ���葫�Ă����Ԃɂ���
		}
		// �N���A���Ă����
		if (m_bClear == true)
		{
			m_state = STATE_SLIDEOUT;	// ��Ԃ��X���C�h�A�E�g��
		}
		break;
	}
	// �X���C�h�C��
	case STATE_SLIDEIN:
		// �g�p���Ă����
		if (m_bUse == true)
		{
			// �ړ�
			m_pos.x += fSpeed;
			
			// ���݂̈ʒu���ҋ@�ʒu�ȏ�Ȃ�
			if (m_pos.x >= m_posStay.x)
			{
				m_state = STATE_STAY;	// ��Ԃ�ҋ@��
				m_pos = m_posStay;		// ���݂̈ʒu��ҋ@�ʒu��
			}
		}
		break;
	// �X���C�h�A�E�g
	case STATE_SLIDEOUT:
		// �g�p���Ă����
		if (m_bUse == true)
		{
			// �ړ�
			m_pos.x -= fSpeed;
			
			// ���݂̈ʒu����ʊO�ʒu�ȉ��Ȃ�
			if (m_pos.x <= m_posOut.x)
			{
				m_pos = m_posOut;	// ���݂̈ʒu����ʊO�ʒu��
				m_bClear = false;	// �N���A���Ă��Ȃ���Ԃ�
				m_bUse = false;		// �g�p���Ă��Ȃ���Ԃ�
			}
		}
		break;
	default:
		break;
	}

	// �I�u�W�F�N�g2D�̈ʒu��ݒ�
	CObject2D::SetPos(m_pos);

	// �g�p���Ă��Ȃ����
	if (m_bUse == false)
	{
		// �I������
		Uninit();
	}
}
//============
// �`�揈��
//============
void CBuffIcon::Draw(void)
{
	// �g�p���ē����
	if (m_bUse == true)
	{
		// �I�u�W�F�N�g2D�̕`��
		CObject2D::Draw();
	}
}