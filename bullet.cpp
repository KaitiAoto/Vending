//==============================
//
// �e[bullet.cpp]
// Author:kaiti
//
//==============================
#include "bullet.h"
#include "renderer.h"
#include "manager.h"
#include "explosion.h"
#include "enemy.h"
#include "particle.h"
#include "player.h"
#include "debugproc.h"
#include "collision.h"
#include "easing.h"
//==================
// �R���X�g���N�^
//==================
CBullet::CBullet(int nPriority):CObject(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_mtxWorld = {};

	m_pModel = NULL;

	m_nLife = 0;

	m_type = TYPE_CAN;
	m_user = USER_PLAYER;

	m_bUse = true;

	m_nPriority = nPriority;

	m_nAttack = 0;
}
//================
// �f�X�g���N�^
//================
CBullet::~CBullet()
{

}
//===========
// ��������
//===========
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, USER user)
{
	CBullet* pBullet = new CBullet;
	if (!pBullet)
		return nullptr;

	if (FAILED(pBullet->Init(pos, rot, user)))
	{
		delete pBullet;
		return nullptr;
	}

	return pBullet;
}
//===============
// ����������
//===============
HRESULT CBullet::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, USER user)
{
	m_pos = pos;
	m_rot = rot;
	m_bUse = true;
	m_user = user;
	m_nAttack = 1;

	//���f������
	const char* pFilename = "data\\MODEL\\can00.x";
	if (m_user == USER_PLAYER)
	{
		pFilename = SetPlayerBullet();
		m_move = D3DXVECTOR3(sinf(m_rot.y - D3DX_PI) * BULLET_SPEED, 5.0f, cosf(m_rot.y - D3DX_PI) * BULLET_SPEED);
		m_nLife = BULLET_LIFE;
	}
	else if (m_user == USER_ENEMY)
	{
		pFilename = SetPlayerBullet();
		m_move = D3DXVECTOR3(sinf(m_rot.y - D3DX_PI) * BULLET_SPEED, 0.0f, cosf(m_rot.y - D3DX_PI) * BULLET_SPEED);
		m_nLife = BULLET_LIFE / 7;
	}

	m_pModel = CModel::Create(pFilename, m_pos, m_rot);
	m_size = m_pModel->SetSize() * 2;

	//�I�u�W�F�N�g�̎�ސݒ�
	SetObjType(TYPE_BULLET);
	
	return S_OK;
}
//============
// �I������
//============
void CBullet::Uninit(void)
{
	if (m_pModel != NULL)
	{
		m_pModel->Uninit();
		delete m_pModel;
		m_pModel = NULL;
	}

	CObject::Release();
}
//============
// �X�V����
//============
void CBullet::Update(void)
{
	if (m_bUse == true)
	{
		if (m_user == USER_PLAYER)
		{
			//�ړ�
			MoveBounce();
			CEffect::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 1.0f, m_pos.z), m_rot, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(1, 127, 255, 255), 60, EFFECT_SIZE);
		}
		else if(m_user == USER_ENEMY)
		{
			Move();
		}

		Collision();
		//����
		m_nLife--;
		if (m_nLife <= 0)
		{
			m_bUse = false;
		}
	}
	else if (m_bUse == false)
	{//�g���Ă��Ȃ��Ȃ�
		Uninit();
		return;
	}
}
//============
// �`�揈��
//============
void CBullet::Draw(void)
{
	if (m_bUse == true)
	{
		//�f�o�C�X�̎擾
		CRenderer* pRenderer = CManager::GetRenderer();
		LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

		//�v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxTrans;
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtxWorld);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		if (m_user == USER_PLAYER)
		{
			//���f���`��
			m_pModel->Draw();
		}
	}
}
//===========
// �ړ�����
//===========
void CBullet::Move(void)
{
	m_pos += m_move;

	m_pModel->Set(m_pos, m_rot);
}
//
//
//
void CBullet::MoveBounce(void)
{
	const float restitution = 0.8f; // �����W���i0.0�`1.0�j
	const float groundY = 0.0f;

	m_move.y -= GRAVITY; //�d�͉��Z

	m_pos += m_move;

	// �n�ʂƂ̏Փˁi�o�E���h�����j
	if (m_pos.y < groundY)
	{
		m_pos.y = groundY;

		// Y���x�̔��]�i�o�E���h�j
		m_move.y *= -restitution;

		// ���˕Ԃ肪�������Ȃ�����~�߂�
		if (fabs(m_move.y) < 0.2f)
		{
			m_move.y = 0.0f;
		}
	}

	m_pModel->Set(m_pos, m_rot);
}
//====================
// �G�Ƃ̓����蔻��
//====================
bool CBullet::Collision(void)
{
	//�����蔻��̃|�C���^�擾
	CCollision* pColl = CGame::GetColl();

	D3DXVECTOR3 contactNormal;

	bool bCollEnemy = false;
	bool bCollVender = false;
	bool bCollStage = false;
	bool bCollPlayer = false;

	if (m_user == USER_PLAYER)
	{
		//�G�T�C�h�Ƃ̔���
		bCollEnemy = pColl->ToEnemy(m_pos, m_rot, m_size, TYPE_BULLET, contactNormal);
		//���̋@�Ƃ̔���
		bCollVender = pColl->ToVender(m_pos, m_rot, m_size, TYPE_BULLET, contactNormal);
		//
		bCollStage = pColl->ToStage(m_pos, m_rot, m_size, contactNormal);
	}
	else if (m_user == USER_ENEMY)
	{
		bCollPlayer = pColl->EnemyBullet(m_pos, m_size);
	}

	if (bCollEnemy == true || bCollVender == true || bCollStage == true || bCollPlayer == true)
	{
		Uninit();
	}

	return bCollEnemy;
}
//======================================
// �v���C���[�̒e�̎�ނ��Ƃ̃��f����
//======================================
const char* CBullet::SetPlayerBullet(void)
{
	//�v���C���[���擾
	CPlayer* pPlayer = CGame::GetPlayer();

	const char* pFilename = "data\\MODEL\\can00.x";

	m_type = pPlayer->GetMyBullet();

	switch (m_type)
	{
	case TYPE_CAN:
		pFilename = "data\\MODEL\\can00.x";
		break;
	case TYPE_ICE:
		pFilename = "data\\MODEL\\ice00.x";
		break;
	case TYPE_CAPSULE:
		pFilename = "data\\MODEL\\capsule00.x";
		break;
	case TYPE_PETBOTTLE:
		pFilename = "data\\MODEL\\pet_bottle00.x";
		break;
	case TYPE_DUST:
		pFilename = "data\\MODEL\\can01.x";
		break;
	case TYPE_SNACK:
		pFilename = "data\\MODEL\\snack00.x";
		break;
	case TYPE_CIGARET:
		pFilename = "data\\MODEL\\cigarette00.x";
		break;
	case TYPE_CARD:
		pFilename = "data\\MODEL\\card00.x";
		break;
	case TYPE_BOTTLE:
		pFilename = "data\\MODEL\\bottle00.x";
		break;

	default:
		break;
	}
	
	return pFilename;
}