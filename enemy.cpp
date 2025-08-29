//==============================
//
// �G[enemy.cpp]
// Author:kaiti
//
//==============================
#include "enemy.h"
#include "renderer.h"
#include "manager.h"
#include "explosion.h"
#include "effect.h"
#include "particle.h"
#include "player.h"
#include "debugproc.h"
#include "collision.h"
#include "matchup.h"
#include "score_manager.h"
//==================
// �R���X�g���N�^
//==================
CEnemy::CEnemy(int nPriority) :CObject(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_mtxWorld = {};

	m_pModel = NULL;

	m_nLife = 0;

	m_type = TYPE_LIGHTER;

	m_bUse = true;
	
	m_nPriority = nPriority;
	
	m_State = STATE_NONE;
	m_nCntState = 0;

}
//================
// �f�X�g���N�^
//================
CEnemy::~CEnemy()
{

}
//===========
// ��������
//===========
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE type)
{
	CEnemy* pBullet = new CEnemy;
	if (!pBullet)
		return nullptr;

	if (FAILED(pBullet->Init(pos, rot, type)))
	{
		delete pBullet;
		return nullptr;
	}

	return pBullet;
}
//===============
// ����������
//===============
HRESULT CEnemy::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, TYPE type)
{
	m_pos = pos;
	m_rot = rot;
	m_move = D3DXVECTOR3(sinf(m_rot.y - D3DX_PI) * 1.5f, 3.0f, cosf(m_rot.y - D3DX_PI) * 1.5f);
	m_nLife = ENEMY_LIFE;
	m_bUse = true;
	m_type = type;
	m_State = STATE_STAY;
	m_nStayCounter = rand() % 120 + 60;
	m_fRandomAngle = D3DXToRadian(rand() % 360);

	//���f������
	const char* pFilename = "data\\MODEL\\lighter00.x";
	pFilename = SetModelName();//���f����

	m_pModel = CModel::Create(pFilename, m_pos, m_rot);
	m_size = m_pModel->SetSize();
	
	m_posHalf = D3DXVECTOR3(m_pos.x, m_pos.y + (m_size.y / 2), m_pos.z);

	float GeuseBase = m_nLife / 10.0f;
	m_pGauge = CEnemyGauge::Create(D3DXVECTOR3(m_pos.x, m_pos.y + (m_size.y / 1.5f), m_pos.z), GeuseBase, 5.0f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));

	//�I�u�W�F�N�g�̎�ސݒ�
	SetObjType(TYPE_ENEMY);

	return S_OK;
}
//============
// �I������
//============
void CEnemy::Uninit(void)
{
	if (m_pModel != NULL)
	{
		m_pModel->Uninit();
		delete m_pModel;
		m_pModel = NULL;
	}

	if (m_pGauge != NULL)
	{
		m_pGauge->Uninit();
	}

	CObject::Release();
}
//============
// �X�V����
//============
void CEnemy::Update(void)
{
	if (m_bUse == true)
	{
		float rate = (float)m_nLife / (float)ENEMY_LIFE;
		rate = max(0.0f, min(rate, 1.0f));

		m_pGauge->SetPos(D3DXVECTOR3(m_pos.x, m_pos.y + (m_size.y * 1.5f), m_pos.z));
		m_pGauge->SetRate(rate);

		switch (m_State)
		{
		case STATE_STAY:
			//�ړ�
			Move();
			break;
		case STATE_MOVE:
			//�ړ�
			Move();
			break;
		case STATE_HIT:
			m_nCntState--;
			if (m_nCntState <= 0)
			{
				m_nCntState = 0;
				State(STATE_STAY);
			}
			break;

		default:
			break;
		}
		
		if (m_State != STATE_HIT)
		{
			m_pModel->SetColorChange(false);
		}
		if (m_State == STATE_STAY)
		{
			m_pGauge->SetDraw(false);
		}
		else
		{
			m_pGauge->SetDraw(true);
		}

		//�����蔻��
		Collision();

		//����
		if (m_nLife <= 0)
		{
			CParticle::Create(m_posHalf, m_rot, D3DCOLOR_RGBA(255, 1, 1, 255), 15, 5, CParticle::TYPE_NONE);

			m_bUse = false;
			m_pGauge->SetDraw(false);
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
void CEnemy::Draw(void)
{
	if (m_bUse == true)
	{
		//�f�o�C�X�̎擾
		CRenderer* pRenderer = CManager::GetRenderer();
		LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

		//�v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxRot, mtxTrans;
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtxWorld);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		//���f���`��
		m_pModel->Draw();
	}
}
//===========
// �ړ�����
//===========
void CEnemy::Move(void)
{
	CPlayer* pPlayer = CGame::GetPlayer();
	D3DXVECTOR3 PlayerPos = pPlayer->GetPos();
	D3DXVECTOR3 PlayerRot = pPlayer->GetRot();
	if (m_State == STATE_MOVE)
	{//�v���C���[�Ɍ������ē���
		if(m_type == TYPE_TORNADO || m_type == TYPE_MAGNET || m_type == TYPE_MONEY1)
		{
			Move_Charge();
		}
		else if (m_type == TYPE_RANGE || m_type == TYPE_KETTLE || m_type == TYPE_MONEY0)
		{
			Move_Jump();
		}
		else if (m_type == TYPE_LIGHTER || m_type == TYPE_SPRAY || m_type == TYPE_EXT)
		{
			Move_Shot();
		}
		else
		{
			Move_Normal();
		}
	}
	else if (m_State == STATE_STAY)
	{
		//�����_���ɓ���
		m_nStayCounter--;
		if (m_nStayCounter <= 0)
		{
			// ��莞�Ԃ��ƂɃ����_���������X�V
			m_fRandomAngle = D3DXToRadian(rand() % 360);
			m_nStayCounter = rand() % 120 + 60;
		}

		// �����_�������ɂ�����蓮��
		float moveSpeed = 0.05f;
		m_move.x = cosf(m_fRandomAngle) * moveSpeed;
		m_move.z = sinf(m_fRandomAngle) * moveSpeed;

		m_rotDest.y = atan2f(m_move.x, m_move.z) + D3DX_PI;
	}

	D3DXVECTOR3 toPlayer = PlayerPos - m_pos;
	float distance = D3DXVec3Length(&toPlayer);
	float fRadius = max(m_size.x, max(m_size.y, m_size.z)) * 10.0f;

	if (distance <= fRadius)
	{
		State(STATE_MOVE);
	}
	else if (distance > fRadius)
	{
		State(STATE_STAY);
	}


	//�p�x�̐��K��
	if (m_rotDest.y - m_rot.y > D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}
	else if (m_rotDest.y - m_rot.y < -D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}

	m_rot += (m_rotDest - m_rot) * 0.5f;

	m_move.y -= GRAVITY; //�d�͉��Z

	//�O��̈ʒu�ۑ�
	m_posOld = m_pos;

	m_pos += m_move;

	if (m_pos.y < 0.0f)
	{
		m_pos.y = 0.0f;
	}

	m_posHalf = D3DXVECTOR3(m_pos.x, m_pos.y + (m_size.y / 2), m_pos.z);
	m_pModel->Set(m_pos, m_rot);
}
//================
// �ʏ�ړ�����
//================
void CEnemy::Move_Normal(void)
{
	CPlayer* pPlayer = CGame::GetPlayer();
	D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

	// �v���C���[�ւ̕����x�N�g��
	D3DXVECTOR3 toPlayer = PlayerPos - m_pos;
	// ���K��
	D3DXVec3Normalize(&toPlayer, &toPlayer);

	//�ړ���
	m_move.x = toPlayer.x * ENEMY_SPEED;
	m_move.z = toPlayer.z * ENEMY_SPEED;
	////�p�x
	float angle = atan2f(toPlayer.x, toPlayer.z);
	m_rotDest.y = angle + D3DX_PI;
}
//===============
// �ːi�ړ�����
//===============
void CEnemy::Move_Charge(void)
{
	// �ÓI�ϐ��œːi�^�ҋ@�̏�Ԃƃ^�C�}�[��ێ�
	static bool isCharging = false;
	static int chargeTimer = 0;
	
	const float chargeframe = 90.0f;
	const int chargeTime = 90;
	const int waitTime = 120;

	// �v���C���[�̏��擾
	CPlayer* pPlayer = CGame::GetPlayer();
	D3DXVECTOR3 playerPos = pPlayer->GetPos();

	// �v���C���[�ւ̕����x�N�g��
	D3DXVECTOR3 toPlayer = playerPos - m_pos;
	float distance = D3DXVec3Length(&toPlayer);
	D3DXVec3Normalize(&toPlayer, &toPlayer);

	if (!isCharging)
	{
		// �ːi�J�n
		// ������2�{����i�ޑ��x��ݒ�
		float chargeDistance = distance * 2.0f;
		float Speed = chargeDistance / chargeframe;

		m_move.x = toPlayer.x * Speed;
		m_move.z = toPlayer.z * Speed;
		m_rotDest.y = atan2f(toPlayer.x, toPlayer.z) + D3DX_PI;

		isCharging = true;
		chargeTimer = chargeTime; // �ːi����
	}
	else
	{
		if (chargeTimer > 0)
		{
			// �ːi���i���̂܂ܑ��x�ێ��j
			chargeTimer--;
		}
		else
		{
			// �ːi�I�� �� �ҋ@
			m_move.x = 0.0f;
			m_move.z = 0.0f;

			static int waitTimer = 0;
			waitTimer++;

			if (waitTimer > waitTime) // ��1�b�ҋ@
			{
				waitTimer = 0;
				isCharging = false; // �ēːi�J�n
			}
		}
	}
}
//=====================
// �W�����v�ړ�����
//=====================
void CEnemy::Move_Jump(void)
{
	static int state = 0;       // 0: �ڋߒ�, 1: �W�����v��, 2: �ҋ@��
	static int timer = 0;
	static bool canJump = true;

	const float JumpRange = 75.0f;
	const float JumpMove = 22.5f;
	const float JumpFrame = 30.0f;
	const int waitTime = 60;

	CPlayer* pPlayer = CGame::GetPlayer();
	D3DXVECTOR3 playerPos = pPlayer->GetPos();
	D3DXVECTOR3 toPlayer = playerPos - m_pos;
	float distance = D3DXVec3Length(&toPlayer);

	switch (state)
	{
	case 0: // �ڋ�
	{
		D3DXVec3Normalize(&toPlayer, &toPlayer);
		m_move.x = toPlayer.x * ENEMY_SPEED;
		m_move.z = toPlayer.z * ENEMY_SPEED;
		m_rotDest.y = atan2f(toPlayer.x, toPlayer.z) + D3DX_PI;

		if (distance < JumpRange && canJump)
		{
			float jumpSpeedH = distance / JumpFrame;
			m_move.x = toPlayer.x * jumpSpeedH;
			m_move.z = toPlayer.z * jumpSpeedH;

			m_move.y = JumpMove;

			canJump = false;
			state = 1;
		}
	}
	break;

	case 1: // �W�����v��
		m_move.y -= GRAVITY;  // �d�͉��Z

		if (m_pos.y <= 0.0f)
		{
			m_pos.y = 0.0f;
			m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			timer = waitTime;
			state = 2;
		}
		break;

	case 2: // �ҋ@��
		timer--;
		if (timer <= 0)
		{
			canJump = true;
			state = 0;
		}
		break;
	}
}
//====================
// �V���b�g�ړ�����
//====================
void CEnemy::Move_Shot(void)
{
	const float AttackRange = 80.0f;  // �˒�����
	const float StopSpeed = 0.0f;      // �ˌ����͎~�܂�
	const float MoveSpeed = ENEMY_SPEED;
	const int ShotTime = 60;

	static int ShotTimer = 0;

	CPlayer* pPlayer = CGame::GetPlayer();
	D3DXVECTOR3 playerPos = pPlayer->GetPos();
	D3DXVECTOR3 toPlayer = playerPos - m_pos;
	float distance = D3DXVec3Length(&toPlayer);


	if (ShotTimer > 0)
	{
		ShotTimer--;
	}

	if (distance <= AttackRange)
	{
		// �͈͓� �� �ړ���~���Ēe����
		m_move = D3DXVECTOR3(0, 0, 0);

		// �G�̌������v���C���[�����ɃZ�b�g
		D3DXVECTOR3 dir = toPlayer;
		D3DXVec3Normalize(&dir, &dir);
		m_rotDest.y = atan2f(dir.x, dir.z) + D3DX_PI;

		if (ShotTimer <= 0)
		{
			CBullet::Create({ m_pos.x, m_pos.y + (m_size.y / 2), m_pos.z }, m_rot, CBullet::USER_ENEMY);
			
			D3DXCOLOR col;
			if (m_type == TYPE_LIGHTER)
			{
				col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			}
			else if(m_type == TYPE_SPRAY)
			{
				col = D3DXCOLOR(1.0f, 0.8f, 0.2f, 1.0f);
			}
			else if (m_type == TYPE_EXT)
			{
				col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}

			// �X�v���[�p�[�e�B�N������
			CParticle::Create({ m_pos.x, m_pos.y + (m_size.y / 2), m_pos.z }, m_rot, col, 1, 8.0f, CParticle::TYPE_SPRAY);

			ShotTimer = ShotTime;
		}
	}
	else
	{
		// �͈͊O �� �v���C���[�Ɍ������Ĉړ�
		D3DXVECTOR3 dir = toPlayer;
		D3DXVec3Normalize(&dir, &dir);

		m_move.x = dir.x * MoveSpeed;
		m_move.z = dir.z * MoveSpeed;

		// �������v���C���[�����Ɍ�����
		m_rotDest.y = atan2f(dir.x, dir.z) + D3DX_PI;
	}
}
//====================
// �G�Ƃ̓����蔻��
//====================
bool CEnemy::Collision(void)
{
	//�����蔻��̃|�C���^�擾
	CCollision* pColl = CGame::GetColl();

	D3DXVECTOR3 contactNormal;

	bool bColl = pColl->ToPlayer(m_pos, m_size,this);
	//���̋@�Ƃ̔���
	bool bCOLL = pColl->ToVender(m_pos, m_rot, m_size, TYPE_ENEMY, contactNormal);
	//
	bool bCollStage = pColl->ToStage(m_pos, m_rot, m_size, contactNormal);
	//
	bool bCollGimmick = pColl->ToGimmick(m_pos, m_size, TYPE_ENEMY);

	if (bColl == true || bCOLL == true || bCollStage == true)
	{
		m_pos = m_posOld;
	}

	if (bCollGimmick == true)
	{
		Hit(1);
	}

	return bColl;
}
//================
// �_���[�W����
//================
void CEnemy::Hit(const int nDamage)
{
	CSound* pSound = CManager::GetSound();

	CScoreMana* pTotalScore = CGame::GetTotalScore();

	m_nLife -= nDamage;

	if (m_nLife > 0)
	{
		if (m_State != STATE_HIT)
		{
			m_pModel->SetColorChange(true);

			State(STATE_HIT);

			if (nDamage == BULLET_ATTACK)
			{//�ʏ�_��
				m_pModel->SetColor(D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f));
				
				CParticle::Create(m_posHalf, m_rot, D3DCOLOR_RGBA(255, 255, 1, 255), 5, 5, CParticle::TYPE_NONE);
				
				pSound->PlaySound(CSound::SOUND_LABEL_DAMAGE);

				pTotalScore->AddScore(200);
			}
			else if (nDamage == BULLET_ATTACK * ADVANTAGE)
			{//���ʔ��Q
				m_pModel->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
				
				CParticle::Create(m_posHalf, m_rot, D3DCOLOR_RGBA(255, 127, 1, 255), 5, 8, CParticle::TYPE_NONE);
				
				pSound->PlaySound(CSound::SOUND_LABEL_CRITICAL);

				pTotalScore->AddScore(400);
			}
			else if (nDamage == BULLET_ATTACK / DISADVANTAGE)
			{//���ʂ��܂ЂƂ�
				m_pModel->SetColor(D3DXCOLOR(0.4f, 0.4f, 0.9f, 1.0f));
				CParticle::Create(m_posHalf, m_rot, D3DCOLOR_RGBA(1, 127, 255, 255), 5, 3, CParticle::TYPE_NONE);
				pSound->PlaySound(CSound::SOUND_LABEL_RESIST);

				pTotalScore->AddScore(50);
			}
			else if (nDamage <= 0)
			{//�m�[�_��
				m_pModel->SetColor(D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f));

				pSound->PlaySound(CSound::SOUND_LABEL_NODAMAGE);
			}
			else
			{
				if (nDamage > 0)
				{
					m_pModel->SetColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
					CParticle::Create(m_posHalf, m_rot, D3DCOLOR_RGBA(255, 1, 255, 255), 5, 3, CParticle::TYPE_NONE);
					pSound->PlaySound(CSound::SOUND_LABEL_DAMAGE);

					pTotalScore->AddScore(100);
				}
			}
		}
	}
	if (m_nLife <= 0)
	{
		State(STATE_DEAD);
		pSound->PlaySound(CSound::SOUND_LABEL_KILL);

		pTotalScore->AddScore(1000);
	}
}
//=================
// ��ԑJ�ڏ���
//=================
void CEnemy::State(STATE state)
{
	m_State = state;

	switch (m_State)
	{
	case STATE_NONE:
		m_pModel->SetColorChange(false);
		break;
	case STATE_HIT:
		m_nCntState = 45;
		break;
	case STATE_DEAD:
		ItemSet();
		m_bUse = false;
		break;

	default:
		break;
	}
}
//
//
//
void CEnemy::ItemSet()
{
	int nItem;
	srand((unsigned int)time(NULL));
	nItem = rand() % 3 + 1;

	if (nItem == 1)
	{// 1/3 �ŃA�C�e������
		int itemType = rand() % 100 + 1;
		if (itemType <= 35)
		{
			CItem::Create(m_pos, m_rot, CItem::TYPE_LIFE);
		}
		else
		{
			CItem::Create(m_pos, m_rot, CItem::TYPE_BULLET);
		}
	}

}
//===========================
// �^�C�v���Ƃ̃��f�����ݒ�
//===========================
const char* CEnemy::SetModelName(void)
{
	const char* pFilename = "data\\MODEL\\lighter00.x";

	switch (m_type)
	{
	case TYPE_LIGHTER:
		pFilename = "data\\MODEL\\lighter00.x";
		break;
	case TYPE_MONEY0:
		pFilename = "data\\MODEL\\money00.x";
		break;
	case TYPE_MONEY1:
		pFilename = "data\\MODEL\\money01.x";
		break;
	case TYPE_MAGNET:
		pFilename = "data\\MODEL\\magnet00.x";
		break;
	case TYPE_TORNADO:
		pFilename = "data\\MODEL\\tornado00.x";
		break;
	case TYPE_SPRAY:
		pFilename = "data\\MODEL\\spray00.x";
		break;
	case TYPE_EXT:
		pFilename = "data\\MODEL\\extinguisher00.x";
		break;
	case TYPE_KETTLE:
		pFilename = "data\\MODEL\\kettle00.x";
		break;
	case TYPE_RANGE:
		pFilename = "data\\MODEL\\microwave00.x";
		break;


	default:
		break;
	}

	return pFilename;

}