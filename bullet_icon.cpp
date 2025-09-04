//==============================
//
// �e�A�C�R��[bullet_icon.h]
// Author : Kaiti Aoto
//
//==============================

// �C���N���[�h
#include "bullet_icon.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "player.h"
#include "debugproc.h"

//==================
// �R���X�g���N�^
//==================
CBulletIcon::CBulletIcon(int nPriority):CObject2D(nPriority)
{
	// �l���N���A
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bUse = false;
}
//================
// �f�X�g���N�^
//================
CBulletIcon::~CBulletIcon()
{
}
//===========
// ��������
//===========
CBulletIcon* CBulletIcon::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// ����
	CBulletIcon* pBulletIcon = new CBulletIcon;
	//������
	if (FAILED(pBulletIcon->Init(pos, fWidth, fHeight)))
	{// NULL�`�F�b�N
		delete pBulletIcon;
		return nullptr;
	}
	return pBulletIcon;	// �|�C���^��Ԃ�
}
//===============
// ����������
//===============
HRESULT CBulletIcon::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	//�l����
	m_pos = pos;

	// �����o�ϐ���������
	m_bUse = false;

	// �I�u�W�F�N�g2D�̏�����
	CObject2D::Init("data\\TEXTURE\\bullet00.png", pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), fWidth, fHeight);

	// �A�C�R����؂�ւ�
	ChangeIcon(CBullet::TYPE_CAN);

	// �I�u�W�F�N�g�̎�ސݒ�
	SetObjType(TYPE_RESTOCK);

	return S_OK;
}
//============
// �I������
//============
void CBulletIcon::Uninit(void)
{
	// �I�u�W�F�N�g2D�̏I������
	CObject2D::Uninit();
}
//============
// �X�V����
//============
void CBulletIcon::Update(void)
{	
	//�v���C���[���擾
	CPlayer* pPlayer = CGame::GetPlayer();
	// ���̒��g�̐����擾
	int nCntContens = pPlayer->GetContents();

	// ���g�������
	if (nCntContens > 0)
	{
		m_bUse = true;						// �g�p���Ă����Ԃɂ���
		m_type = pPlayer->GetMyBullet();	// ��ނ��v���C���[�Ɠ����ɂ���
		// �e�N�X�`���؂�ւ�
		ChangeIcon(m_type);
	}
	// ���g���Ȃ����
	else if (nCntContens <= 0)
	{
		m_bUse = false;	// �g�p���Ă��Ȃ���Ԃɂ���
	}
}
//============
// �`�揈��
//============
void CBulletIcon::Draw(void)
{
	// �g�p���Ă����
	if (m_bUse == true)
	{
		// �I�u�W�F�N�g2D�̕`��
		CObject2D::Draw();
	}
}
//==================
// �A�C�R���؂�ւ�
//==================
void CBulletIcon::ChangeIcon(CBullet::TYPE type)
{
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

	// �e�N�X�`�����蓖��
	CTexture* pTex = CManager::GetTex();	// �e�N�X�`���̃|�C���^�擾
	int nIdxTex = pTex->Register(pTexName);	// �e�N�X�`�����蓖��
	CObject2D::SetIdxTex(nIdxTex);			// �I�u�W�F�N�g2D�̃C���f�b�N�X�ԍ���ݒ�
}
