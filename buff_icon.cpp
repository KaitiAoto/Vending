//==============================
//
// �o�t�A�C�R��[buff_icon.h]
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

	m_state = STATE_SLIDEIN;	// ��Ԃ��X���C�h�C����
	m_bUse = true;				// �g�p�����Ԃ�
	m_bClear = false;			// �N���A���Ă��Ȃ���Ԃ�

	// �e�N�X�`����
	const char* apFileName[CBuff::TYPE_MAX] =
	{
		"data\\TEXTURE\\speedUP00.png",
	};

	for (int nCnt = 0; nCnt < CBuff::TYPE_MAX; nCnt++)
	{// �e�N�X�`������o�^
		m_apFileName[nCnt] = apFileName[nCnt];
	}

	// �I�u�W�F�N�g2D�̏�����
	CObject2D::Init(m_apFileName[m_type], pos, m_rot, fWidth, fHeight);

	//�e�N�X�`�����蓖��
	CTexture* pTex = CManager::GetTex();
	m_nIdxTex = pTex->Register(m_apFileName[m_type]);
	CObject2D::SetIdxTex(m_nIdxTex);

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

		if (type == CBuff::TYPE_NONE)
		{// �����o�t���������Ă��Ȃ����
			m_bClear = true;	// ���葫�Ă����Ԃɂ���
		}
		if (m_bClear == true)
		{// �N���A���Ă����
			m_state = STATE_SLIDEOUT;	// ��Ԃ��X���C�h�A�E�g��
		}
		break;
	}
	// �X���C�h�C��
	case STATE_SLIDEIN:
		if (m_bUse == true)
		{// �g�p���Ă����
			// �ړ�
			m_pos.x += fSpeed;
			
			if (m_pos.x >= m_posStay.x)
			{// ���݂̈ʒu���ҋ@�ʒu�ȏ�Ȃ�
				m_state = STATE_STAY;	// ��Ԃ�ҋ@��
				m_pos = m_posStay;		// ���݂̈ʒu��ҋ@�ʒu��
			}
		}
		break;
	// �X���C�h�A�E�g
	case STATE_SLIDEOUT:
		if (m_bUse == true)
		{// �g�p���Ă����
			// �ړ�
			m_pos.x -= fSpeed;
			
			if (m_pos.x <= m_posOut.x)
			{// ���݂̈ʒu����ʊO�ʒu�ȉ��Ȃ�
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

	if (m_bUse == false)
	{// �g�p���Ă��Ȃ����
		// �I������
		Uninit();
	}
}
//============
// �`�揈��
//============
void CBuffIcon::Draw(void)
{
	if (m_bUse == true)
	{// �g�p���ē����
		// �I�u�W�F�N�g2D�̕`��
		CObject2D::Draw();
	}
}