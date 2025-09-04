//==============================
//
// �e[bullet.cpp]
// Author : Kaiti Aoto
//
//==============================

// �C���N���[�h
#include "bullet.h"
#include "renderer.h"
#include "manager.h"
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
	// �l���N���A
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_mtxWorld = {};
	m_pModel = NULL;
	m_type = TYPE_CAN;
	m_user = USER_PLAYER;
	m_nLife = 0;
	m_bUse = true;
	m_bSkill = false;
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
	// ����
	CBullet* pBullet = new CBullet;
	// ������
	if (FAILED(pBullet->Init(pos, rot, user)))
	{// NULL�`�F�b�N
		delete pBullet;
		return nullptr;
	}
	return pBullet;	// �|�C���^��Ԃ�
}
//===============
// ����������
//===============
HRESULT CBullet::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, USER user)
{
	// �l����
	m_pos = pos;
	m_rot = rot;
	m_user = user;

	// �����o�ϐ���������
	m_bUse = true;		// �g�p���Ă����Ԃɂ���
	m_bSkill = false;	// �X�L���ł͂Ȃ���Ԃɂ���

	// ���f�����i�[�p�ϐ������̏�����
	const char* pFilename = "data\\MODEL\\can00.x";
	
	// �ړ��ʂ�ݒ�
	m_move = D3DXVECTOR3(sinf(m_rot.y - D3DX_PI) * BULLET_SPEED, 0.0f, cosf(m_rot.y - D3DX_PI) * BULLET_SPEED);

	// ���[�U�[���v���C���[�Ȃ�
	if (m_user == USER_PLAYER)
	{
		pFilename = SetPlayerBullet();	// ���f�����ݒ�
		m_move.y = 5.0f;				// �x���̈ړ��ʂ�ύX
		m_nLife = BULLET_LIFE;			// ������ݒ�
	}
	// ���[�U�[���G�Ȃ�
	else if (m_user == USER_ENEMY)
	{
		m_nLife = BULLET_LIFE / 7;	// ������ݒ�
	}

	// ���f������
	m_pModel = CModel::Create(pFilename, m_pos, m_rot);
	// �T�C�Y��ݒ�
	m_size = m_pModel->SetSize() * 2;

	// �I�u�W�F�N�g�̎�ސݒ�
	SetObjType(TYPE_BULLET);
	
	return S_OK;
}
//============
// �I������
//============
void CBullet::Uninit(void)
{	
	if (m_pModel != NULL)
	{// NULL�`�F�b�N
		// ���f���̏I���������j��
		m_pModel->Uninit();
		delete m_pModel;
		m_pModel = NULL;
	}

	// �I�u�W�F�N�g�̔j��
	CObject::Release();
}
//============
// �X�V����
//============
void CBullet::Update(void)
{
	// �g�p���Ă����
	if (m_bUse == true)
	{
		// ���[�U�[���v���C���[�Ȃ�
		if (m_user == USER_PLAYER)
		{
			// �o�E���h�ړ�
			MoveBounce();

			// �G�t�F�N�g����
			CEffect::Create(
				D3DXVECTOR3(m_pos.x, m_pos.y + 1.0f, m_pos.z), 
				m_rot, 
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DCOLOR_RGBA(1, 127, 255, 255), 
				60, 
				EFFECT_SIZE);
		}
		// ���[�U�[���G�Ȃ�
		else if(m_user == USER_ENEMY)
		{
			// �ړ�
			Move();
		}
		// �����蔻��
		Collision();

		// ���������炷
		m_nLife--;
		// �������O�ȉ��Ȃ�
		if (m_nLife <= 0)
		{
			m_bUse = false;	// �g�p���Ă��Ȃ���Ԃ�
		}
	}
	// �g���Ă��Ȃ��Ȃ�
	else if (m_bUse == false)
	{
		// �I������
		Uninit();
		return;
	}
}
//============
// �`�揈��
//============
void CBullet::Draw(void)
{
	// �g�p���Ă����
	if (m_bUse == true)
	{
		// �f�o�C�X�̎擾
		CRenderer* pRenderer = CManager::GetRenderer();
		LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

		// �v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxTrans;
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtxWorld);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		// ���[�U�[���v���C���[�Ȃ�
		if (m_user == USER_PLAYER)
		{
			// ���f���`��
			m_pModel->Draw();
		}
	}
}
//===========
// �ړ�����
//===========
void CBullet::Move(void)
{
	// �ʒu�X�V
	m_pos += m_move;

	// ���f���̈ʒu�X�V
	m_pModel->Set(m_pos, m_rot);
}
//==================
// �o�E���h�ړ�
//==================
void CBullet::MoveBounce(void)
{
	const float fRestitution = 0.8f;	// �����W��
	const float fMinY = 0.2f;			// �x���̍Œ�ړ���

	// �d�͉��Z
	m_move.y -= GRAVITY;

	// �ʒu�X�V
	m_pos += m_move;

	// �n�ʂƂ̏Փ�
	if (m_pos.y < 0.0f)
	{
		m_pos.y = 0.0f;	// �ʒu��n�ʂƓ����ɂ���

		// Y���x�̔��]
		m_move.y *= -fRestitution;

		// �ړ��ʂ����ʏ������Ȃ�����
		if (fabs(m_move.y) < fMinY)
		{
			m_move.y = 0.0f;	// Y���̈ړ��ʂ��O��
		}
	}

	// ���f���̈ʒu�X�V
	m_pModel->Set(m_pos, m_rot);
}
//====================
// �G�Ƃ̓����蔻��
//====================
bool CBullet::Collision(void)
{
	// �����蔻��̃|�C���^�擾
	CCollision* pColl = CGame::GetColl();

	D3DXVECTOR3 contactNormal;	// �ڐG�@��

	// �����蔻�茟�m�p
	bool bCollEnemy = false;	// �G�T�C�h
	bool bCollPlayer = false;	// �v���C���[
	bool bCollStage = false;	// �X�e�[�W
	bool bCollVender = false;	// ���̋@
	bool bAnyColl = false;		// ��L�̔��肪���邩�𒲂ׂ�p

	// ���[�U�[���v���C���[�Ȃ�
	if (m_user == USER_PLAYER)
	{
		// �G�T�C�h�Ƃ̔���
		if (m_bSkill != true)
		{
			bCollEnemy = pColl->ToEnemy(m_pos, m_rot, m_size, TYPE_BULLET, contactNormal);
		}
		// ���̋@�Ƃ̔���
		bCollVender = pColl->ToVender(m_pos, m_rot, m_size, TYPE_BULLET, contactNormal);
		// �X�e�[�W�Ƃ̔���
		bCollStage = pColl->ToStage(m_pos, m_rot, m_size, contactNormal);
	}
	// ���[�U�[���G�Ȃ�
	else if (m_user == USER_ENEMY)
	{
		// �v���C���[�Ƃ̔���
		bCollPlayer = pColl->EnemyBullet(m_pos, m_size);
	}

	// �����ɓ���������
	if (bCollEnemy == true || bCollVender == true || bCollStage == true || bCollPlayer == true)
	{
		// �I������
		Uninit();

		bAnyColl = true;	// ����L���Ԃ�
	}

	return bAnyColl;	 // �����Ԃ�
}
//======================================
// �v���C���[�̒e�̎�ނ��Ƃ̃��f����
//======================================
const char* CBullet::SetPlayerBullet(void)
{
	// �v���C���[���擾
	CPlayer* pPlayer = CGame::GetPlayer();

	// ���f�����i�[�p�ϐ������̏�����
	const char* pFilename = "data\\MODEL\\can00.x";

	// ���̒e�̎�ނ��擾
	m_type = pPlayer->GetMyBullet();

	// ��ނ��ƂɃ��f�������擾
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
	
	return pFilename;	// ���f������Ԃ�
}