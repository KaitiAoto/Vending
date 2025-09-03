//==============================
//
// �v���C���[[player.cpp]
// Author:kaiti
//
//==============================
#include "player.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "effect.h"
#include "score_manager.h"
#include "enemy.h"
#include "debugproc.h"
#include "camera.h"
#include "sound.h"
#include "object3D.h"
#include "enemy_base.h"
#include "objectBillboard.h"
#include "collision.h"
#include "particle.h"
#include "collision.h"
#include "vender.h"
#include "sold_out.h"

//�ÓI�����o�ϐ�
bool CPlayer::m_bUse = true;
//==================
// �R���X�g���N�^
//==================
CPlayer::CPlayer(int nPriority):CObject(nPriority)
{
	//�l���N���A
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_type = TYPE_A;
	m_Bullet = CBullet::TYPE_CAN;

	m_bUse = true;
	m_State = STATE_NONE;
	m_nCntState = 0;

	m_nLife = 0;
	m_fSpeed = 0;
	m_nCntContents = 0;

	m_nNumModel = 0;
	m_mtxWorld = {};

	for (int nCnt = 0; nCnt < PLAYER_MODEL; nCnt++)
	{
		m_apModel[nCnt] = {};
	}
	m_pMotion = nullptr;

	m_pShadow = NULL;

	m_nCntStackt = 0;

	m_BaseColor = { 1.0f,1.0f,1.0f,1.0f };
	m_DamageColor = { 1.0f, 1.0f, 1.0f,0.0f };
}
//================
// �f�X�g���N�^
//================
CPlayer::~CPlayer()
{
}
//===========
// ��������
//===========
CPlayer* CPlayer::Create(const char* pFileName, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CPlayer* pPlayer;
	//�C���X�^���X����
	pPlayer = new CPlayer;
	//������
	if (FAILED(pPlayer->Init(pFileName, pos, rot)))
	{
		delete pPlayer;
		return nullptr;
	}
	return pPlayer;
}
//===============
// ����������
//===============
HRESULT CPlayer::Init(const char* pFileName, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//�ʒu�E�����ݒ�
	m_pos = pos;
	m_rot = rot;
	m_posOffSet = m_pos;

	//���f������
	for (int nCnt = 0; nCnt < PLAYER_MODEL; nCnt++)
	{
		if (m_apModel[nCnt] == NULL)
		{
			m_apModel[nCnt] = nullptr;
		}
	}

	//���f���ǂݍ���
	CModel::Load(pFileName, m_apModel, m_nNumModel);
	//���[�V�����ǂݍ���
	m_pMotion = CMotion::Load(pFileName);
	for (int nCnt = 0; nCnt < PLAYER_MODEL; nCnt++)
	{
		m_size = m_apModel[nCnt]->SetSize();
		m_apModel[nCnt]->SetColorChange(true);
	}

	float fRadius = max(m_size.x, max(m_size.y, m_size.z)) * 0.5f;
	m_pShadow = CShadow::Create(m_pos, m_rot, fRadius);

	//m_pShadowS = CShadowS::Create(m_pos, m_rot, fRadius);

	m_nLife = PLAYER_LIFE;
	m_fSpeed = PLAYER_SPEED;
	m_nCntContents = MAX_RESTOCK / 10;
	m_fShotTimer = 0.0f;

	SetObjType(TYPE_PLAYER);//�I�u�W�F�N�g�̃^�C�v
	return S_OK;
}
//============
// �I������
//============
void CPlayer::Uninit(void)
{
	m_bUse = false;

	//���f���S�I��
	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{
			m_apModel[nCnt]->Uninit();
			delete m_apModel[nCnt];
			m_apModel[nCnt] = nullptr;
		}
	}
	//���[�V�����j��
	if (m_pMotion != nullptr)
	{
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	//�e�j��
	if (m_pShadow != nullptr)
	{
		m_pShadow = nullptr;
	}
	if (m_pShadowS != nullptr)
	{
		m_pShadowS->Uninit();
		delete m_pShadowS;
		m_pShadowS = nullptr;
	}

	CObject::Release();
}
//============
// �X�V����
//============
void CPlayer::Update(void)
{
	if (m_bUse == true)
	{
		//�s��
		Action();

		//�ړ�
		Move();

		if (m_nLife <= 0)
		{
			m_bUse = false;
		}

		if (m_State == STATE_HIT)
		{
			Blink();
		}
		m_nCntState--;
		if (m_nCntState <= 0)
		{
			m_nCntState = 0;
			State(STATE_NONE);
		}

		//���[�V�����X�V
		if (m_pMotion != nullptr)
		{
			m_pMotion->Update(m_nNumModel, m_apModel);
		}
		if (m_pShadow != nullptr)
		{
			m_pShadow->SetPos(D3DXVECTOR3(m_pos.x, 0.3f, m_pos.z));
			//m_pShadow->SetPos(m_pos);
		}
	}
	else if(m_bUse == false)
	{
		CGame::SetMode(CGame::MODE_FIN);
	}
}
//============
// �`�揈��
//============
void CPlayer::Draw(void)
{
	CDebugProc* pDegub = CManager::GetDebug();
	pDegub->Print("�v���C���[�̈ʒu�F%.1f,%.1f,%.1f", m_pos.x, m_pos.y, m_pos.z);
	pDegub->Print("�v���C���[�̊p�x�F%.1f,%.1f,%.1f", m_rot.x, m_rot.y, m_rot.z);
	pDegub->Print("�v���C���[�̈ړ��ʁF%.1f,%.1f,%.1f", m_move.x, m_move.y, m_move.z);
	pDegub->Print("�v���C���[�̃T�C�Y�F%.1f,%.1f,%.1f", m_size.x, m_size.y, m_size.z);
	pDegub->Print("�v���C���[��HP�F%d", m_nLife);
	pDegub->Print("�v���C���[�̒��g�F%d", m_nCntContents);
	if (m_State == STATE_HIT)
	{
		pDegub->Print("�_���[�W�q�b�g");
	}


	//�f�o�C�X�̎擾
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;
	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽓]
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���f���S�`��
	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
	{
		if (m_apModel[nCnt] != NULL)
		{
			m_apModel[nCnt]->Draw();
		}
	}
	
	if (m_pShadowS != nullptr)
	{
		m_pShadowS->Set(m_pos, m_rot);
		m_pShadowS->Draw();
	}
}
//===================
// ���g����ɂ���
//===================
void CPlayer::ClearContents(void)
{
	// ���g���P�O�ȏ�Ȃ�
	int nContents = m_nCntContents;

	if (m_nCntContents >= 10)
	{
		nContents = 10;
	}
	float rot = D3DX_PI / (nContents / 2);
	for (int nCnt = 0; nCnt < nContents; nCnt++)
	{
		CBullet* pBullet = nullptr;
		pBullet = CBullet::Create(m_pos, { m_rot.x,m_rot.y + (rot * nCnt),m_rot.z }, CBullet::USER_PLAYER);
		pBullet->SetSkill(true);
	}
	
	// ���g���O��
	m_nCntContents = 0;

	//�`���[�g���A���N���A����
	if (CGame::GetMode() == CGame::MODE_TUTORIAL)
	{
		CTutorial* pTutorial = CGame::GetTutorial();
		if (pTutorial != nullptr)
		{
			if (pTutorial->GetType() == CTutorial::TYPE_CONTENTS)
			{
				CGame::GetTutorial()->SetClear(true);
			}
		}
	}
}
//===========
// �ړ�����
//===========
void CPlayer::Move(void)
{
	//�L�[�擾
	CInputKey* pInputKey = CManager::GetInputKey();
	//�p�b�h
	CInputPad* pInputPad = CManager::GetInputPad();
	//�}�E�X�擾
	CInputMouse* pInputMouse = CManager::GetInputMouse();

	CCamera* pCamera = CManager::GetCamera();
	D3DXVECTOR3 CameraRot = pCamera->GetRot();

	//�L�[�ړ�
	if (pInputKey->GetPress(DIK_A) == true)
	{//��
		if (pInputKey->GetPress(DIK_W) == true)
		{
			m_move.x += sinf(CameraRot.y - D3DX_PI * 0.25f) * m_fSpeed;
			m_move.z += cosf(CameraRot.y - D3DX_PI * 0.25f) * m_fSpeed;

			m_rotDest.y = CameraRot.y + D3DX_PI * 0.75f;
		}
		else if (pInputKey->GetPress(DIK_S) == true)
		{
			m_move.x += sinf(CameraRot.y - D3DX_PI * 0.75f) * m_fSpeed;
			m_move.z += cosf(CameraRot.y - D3DX_PI * 0.75f) * m_fSpeed;

			m_rotDest.y = CameraRot.y + D3DX_PI * 0.25f;
		}
		else
		{
			m_move.x += cosf(CameraRot.y - D3DX_PI) * m_fSpeed;
			m_move.z -= sinf(CameraRot.y - D3DX_PI) * m_fSpeed;

			m_rotDest.y = CameraRot.y + D3DX_PI / 2;
		}
	}
	if (pInputKey->GetPress(DIK_D) == true)
	{//�E
		if (pInputKey->GetPress(DIK_W) == true)
		{
			m_move.x -= sinf(CameraRot.y - D3DX_PI * 0.75f) * m_fSpeed;
			m_move.z -= cosf(CameraRot.y - D3DX_PI * 0.75f) * m_fSpeed;

			m_rotDest.y = CameraRot.y - D3DX_PI * 0.75f;
		}
		else if (pInputKey->GetPress(DIK_S) == true)
		{
			m_move.x -= sinf(CameraRot.y - D3DX_PI * 0.25f) * m_fSpeed;
			m_move.z -= cosf(CameraRot.y - D3DX_PI * 0.25f) * m_fSpeed;

			m_rotDest.y = CameraRot.y - D3DX_PI * 0.25f;
		}
		else
		{
			m_move.x -= cosf(CameraRot.y - D3DX_PI) * m_fSpeed;
			m_move.z += sinf(CameraRot.y - D3DX_PI) * m_fSpeed;

			m_rotDest.y = CameraRot.y - D3DX_PI / 2;
		}
	}
	if (pInputKey->GetPress(DIK_W) == true)
	{//�O
		if (pInputKey->GetPress(DIK_A) == false && pInputKey->GetPress(DIK_D) == false)
		{
			m_move.x -= sinf(CameraRot.y - D3DX_PI) * m_fSpeed;
			m_move.z -= cosf(CameraRot.y - D3DX_PI) * m_fSpeed;

			m_rotDest.y = CameraRot.y - D3DX_PI;
		}
	}
	if (pInputKey->GetPress(DIK_S) == true)
	{//��
		if (pInputKey->GetPress(DIK_A) == false && pInputKey->GetPress(DIK_D) == false)
		{
			m_move.x += sinf(CameraRot.y - D3DX_PI) * m_fSpeed;
			m_move.z += cosf(CameraRot.y - D3DX_PI) * m_fSpeed;

			m_rotDest.y = CameraRot.y;
		}
	}

	if (pInputPad != nullptr)
	{
		// �X�e�B�b�N���͂ɂ��ړ�
		const float DEADZONE = 10000.0f;  // �f�b�h�]�[��
		XINPUT_STATE* pJoyState = pInputPad->GetJoyStickAngle();
		SHORT lx = pJoyState->Gamepad.sThumbLX;
		SHORT ly = pJoyState->Gamepad.sThumbLY;

		float fLX = (abs(lx) > DEADZONE) ? lx / 32768.0f : 0.0f;
		float fLY = (abs(ly) > DEADZONE) ? ly / 32768.0f : 0.0f;

		if (fLX != 0.0f || fLY != 0.0f)
		{
			// �J�����̉�]�Ɋ�Â����X�e�B�b�N���������[���h�����ɕϊ�
			float angle = atan2f(fLX, fLY);  // �X�e�B�b�N�̊p�x�i���W�A���j
			float rotY = CameraRot.y + angle;

			m_move.x += sinf(rotY) * m_fSpeed;
			m_move.z += cosf(rotY) * m_fSpeed;

			m_rotDest.y = rotY + D3DX_PI;
		}

		const float sensitivity = 0.05f; // ���x�����p
		float rx = pInputPad->GetRightStickX(); // ��
		// �f�b�h�]�[������
		const float deadZone = 0.2f;
		if (fabsf(rx) > deadZone)
		{
			m_rot.y += rx * sensitivity;
		}
	}

	//�}�E�X�̍��E�ړ��Ŏ��_����
	if (pInputMouse != nullptr)
	{
		int mouseMoveX = pInputMouse->GetRelX();

		const float sensitivity = 0.0003f; // ���x�����p

		m_rotDest.y += mouseMoveX * sensitivity;
	}
	if (pInputPad != nullptr)
	{
		const float sensitivity = 0.05f; // ���x�����p

		float rx = pInputPad->GetRightStickX(); // ��

		// �f�b�h�]�[������
		const float deadZone = 0.2f;
		if (fabsf(rx) > deadZone)
		{
			m_rotDest.y += rx * sensitivity;
		}
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

	//�����Ă�����
	if (m_move.x != 0 || m_move.z != 0)
	{//���[�V������MOVE��
		if (m_pMotion->GetType() != CMotion::TYPE_MOVE)
		{
			m_pMotion->SetType(CMotion::TYPE_MOVE);
		}
		//m_pMotion->SetType(CMotion::TYPE_MOVE);
		m_bMove = true;
	}
	else
	{
		if (m_pMotion->GetType() != CMotion::TYPE_NEUTRAL)
		{
			m_pMotion->SetType(CMotion::TYPE_NEUTRAL);
		}
		m_bMove = false;
	}
	//�O��̈ʒu�ۑ�
	m_posOld = m_pos;
	
	//�ʒu�X�V
	m_pos += m_move;

	//�����蔻��
	bool bColl = Collision();
	CheckStack(bColl, m_bMove);
	
	if (m_pos.y < 0.0f)
	{
		m_pos.y = 0.0f;
		m_move.y = 0.0f;
	}
	
	//�ړ��ʏ�����
	m_move.x = 0.0f;
	m_move.z = 0.0f;
}
//==================
// �A�N�V��������
//==================
void CPlayer::Action(void)
{
	//�L�[�擾
	 CInputKey* pInputKey = CManager::GetInputKey();
	//�}�E�X�擾
	CInputMouse* pInputMouse = CManager::GetInputMouse();
	//�p�b�h
	CInputPad* pInputPad = CManager::GetInputPad();

	CSound* pSound = CManager::GetSound();

	//�e����
	if (pInputMouse->GetPress(0) == true || pInputPad->GetR2Press(30) == true)
	{
		if (m_nCntContents > 0)
		{//���g����
			m_fShotTimer -= SHOT_TIMESUB;
			if (m_fShotTimer <= 0.0f)
			{
				CBullet::Create(m_pos, m_rot, CBullet::USER_PLAYER);
				m_nCntContents--;

				pSound->PlaySound(CSound::SOUND_LABEL_SHOT);

				m_fShotTimer = SHOT_INTERVAL;

				//�`���[�g���A���N���A����
				if (CGame::GetMode() == CGame::MODE_TUTORIAL)
				{
					CTutorial* pTutorial = CGame::GetTutorial();
					if (pTutorial != nullptr)
					{
						if (pTutorial->GetType() == CTutorial::TYPE_BULLET)
						{
							CGame::GetTutorial()->SetClear(true);
						}
					}
				}
			}
		}
		else
		{
			if (CSoldOut::GetUse() == false)
			{
				CSoldOut::Create();
			}

			pSound->PlaySound(CSound::SOUND_LABEL_MISS);
		}
	}
	else
	{
		m_fShotTimer = 0.0f;
	}


#ifdef _DEBUG
	//�p�[�e�B�N��
	if (pInputKey->GetTrigger(DIK_2) == true)
	{
		CParticle::Create({ m_pos.x, m_pos.y + (m_size.y / 2), m_pos.z }, m_rot, D3DXCOLOR(1.0f, 0.8f, 0.2f, 1.0f), 1, 8.0f, CParticle::TYPE_SPRAY);
	}

	if (pInputKey->GetTrigger(DIK_3) == true)
	{
		CEffectCircle::Create(m_pos, m_rot, 30.0f, D3DXCOLOR(0.8f, 0.5f, 0.0f, 0.3f), CMeshCircle::TYPE_BOTHSIDES, CEffectCircle::TYPE_UPDOWN);
	}

	if (pInputKey->GetTrigger(DIK_0) == true)
	{
		m_nLife -= 10;
	}
	CScoreMana* pScore = CGame::GetBreakCnt();
	CScoreMana* pScore1= CGame::GetTotalScore();

	if (pInputKey->GetTrigger(DIK_9) == true)
	{
		pScore->AddScore(1);
	}
	if (pInputKey->GetTrigger(DIK_8) == true)
	{
		pScore1->AddScore(1);	
	}
	CDebugProc* pDegub = CManager::GetDebug();
	pDegub->Print("�j�󐔁F%d", pScore->GetScore());
	pDegub->Print("�g�[�^���F%d", pScore1->GetScore());


#endif
}
//================
// �_���[�W����
//================
void CPlayer::Hit(const int nDamage)
{
	CSound* pSound = CManager::GetSound();

	if (m_State == STATE_NONE)
	{
		m_nLife -= nDamage;

		CGame::GetFlash()->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f));

		if (m_nLife > 0)
		{
			State(STATE_HIT);
		}
		if (m_nLife <= 0)
		{
			m_nLife = 0;
			State(STATE_DEAD);
		}

		pSound->PlaySound(CSound::SOUND_LABEL_HIT);
	}
}
//===============
// �_�ŏ���
//===============
void CPlayer::Blink(void)
{
	const int nBlinkFrame = 5;//�_�Ńt���[����

	if ((m_nCntState / nBlinkFrame) % 2 == 0)
	{//�_���[�W�F�ɂ���
		for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
		{
			if (m_apModel[nCnt] != NULL)
			{
				m_apModel[nCnt]->SetColor(m_DamageColor);
			}
		}
	}
	else
	{//�ʏ�F�ɖ߂�
		for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
		{
			if (m_apModel[nCnt] != NULL)
			{
				m_apModel[nCnt]->SetColor(m_BaseColor);
			}
		}
	}
}
//=================
// ��ԑJ�ڏ���
//=================
void CPlayer::State(STATE state)
{
	m_State = state;

	switch (m_State)
	{
	case STATE_NONE:
		for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
		{
			if (m_apModel[nCnt] != NULL)
			{
				m_apModel[nCnt]->SetColor(m_BaseColor);
			}
		}
		break;
	case STATE_HIT:
		m_nCntState = 60;
		break;
	case STATE_DEAD:
		m_bUse = false;
		break;

	default:
		break;
	}
}
//====================
// �����蔻��
//====================
bool CPlayer::Collision(void)
{
	CDebugProc* pDebug = CManager::GetDebug();
	CCollision* pColl = CGame::GetColl();

	bool hit = false;
	const int maxIterations = 3;
	D3DXVECTOR3 moveVec = m_pos - m_posOld;

	// ������OBB���𐶐��i1��ōςށj
	D3DXVECTOR3 axes0[3];
	{
		D3DXMATRIX rotMtx;
		D3DXMatrixRotationYawPitchRoll(&rotMtx, m_rot.y, m_rot.x, m_rot.z);
		axes0[0] = D3DXVECTOR3(rotMtx._11, rotMtx._12, rotMtx._13);
		axes0[1] = D3DXVECTOR3(rotMtx._21, rotMtx._22, rotMtx._23);
		axes0[2] = D3DXVECTOR3(rotMtx._31, rotMtx._32, rotMtx._33);
		for (int i = 0; i < 3; ++i) D3DXVec3Normalize(&axes0[i], &axes0[i]);
	}

	for (int iter = 0; iter < maxIterations; ++iter)
	{
		bool anyHit = false;

		// �����ΏۂɑΉ����邽�߁A���񂷂ׂă`�F�b�N
		std::vector<D3DXVECTOR3> contactNormals;

		D3DXVECTOR3 normal;
		if (pColl->ToEnemy(m_pos, m_rot, m_size, TYPE_PLAYER, normal)) {
			contactNormals.push_back(normal);
			anyHit = true;
			hit = true;
		}
		if (pColl->ToVender(m_pos, m_rot, m_size, TYPE_PLAYER, normal)) {
			contactNormals.push_back(normal);
			anyHit = true;
			hit = true;
		}
		if (pColl->ToStage(m_pos, m_rot, m_size, normal)) {
			contactNormals.push_back(normal);
			anyHit = true;
			hit = true;
		}

		if (!anyHit)
			break;

		// �S�Փ˖@���ɑ΂��ď��Ԃɉ����߂��{�X���C�h���s��
		for (const auto& contactNormalRaw : contactNormals)
		{
			D3DXVECTOR3 contactNormal = contactNormalRaw;

			// �ړ������Ƌt�Ȃ�@�����]
			if (D3DXVec3Dot(&moveVec, &contactNormal) > 0.0f)
				contactNormal *= -1.0f;

			// penetration �����߂�
			float penetration = 0.0f;
			pColl->OverlapOnAxis(
				moveVec, contactNormal,
				axes0, m_size,
				axes0, m_size,
				penetration
			);
			if (penetration > 0.001f)
				m_pos += contactNormal * penetration;

			// �X���C�h����
			moveVec = m_pos - m_posOld;
			float dot = D3DXVec3Dot(&moveVec, &contactNormal);
			D3DXVECTOR3 slideVec = moveVec - contactNormal * dot;

			m_pos = m_posOld + slideVec;
			moveVec = slideVec;
		}
	}

	// �M�~�b�N�͉����߂��s�v
	pColl->ToGimmick(m_pos, m_size, TYPE_PLAYER);

	if (hit) pDebug->Print("HIT");
	return hit;
}

//========================
// �X�^�b�N�`�F�b�N����
//========================
void CPlayer::CheckStack(bool bColl, bool bMove)
{
	if (bColl == true && bMove == false)
	{
		m_nCntStackt++;

		// ���t���[���ȏ�X�^�b�N���Ă�����~�o
		if (m_nCntStackt >= 180)
		{
			RecoverFromStuck();
			m_nCntStackt = 0;
		}
	}
	else
	{
		m_nCntStackt = 0;
	}
}
//======================
// �X�^�b�N�~�o����
//======================
void CPlayer::RecoverFromStuck(void)
{
	// �f�o�b�O���O�o��
	CDebugProc* pDebug = CManager::GetDebug();
	pDebug->Print("�X�^�b�N���o�F���J�o�����s");

	// �����ړ���
	m_pos = m_posOffSet;
	m_move = D3DXVECTOR3(0, 0, 0);

	// �e�̈ʒu���X�V
	if (m_pShadow)
	{
		m_pShadow->SetPos(m_pos);
	}

	CScoreMana* pTotalScore = CGame::GetTotalScore();
	pTotalScore->AddScore(1);
}