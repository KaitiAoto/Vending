//==============================
//
// �v���C���[[player.h]
// Author:kaiti
//
//==============================

// ��d�C���N���[�h�h�~
#ifndef _PLAYER_H_
#define _PLAYER_H_

// �C���N���[�h
#include "main.h"
#include "object.h"
#include "model.h"
#include "motion.h"
#include "bullet.h"
#include "shadow.h"
#include "gauge.h"
#include "shadowS.h"

// �}�N����`
#define PLAYER_SIZE (100)
#define PLAYER_LIFE (20)
#define PLAYER_MODEL (1)
#define PLAYER_SPEED (2.5f)
#define PLAYER_JUMP (7.8f)

// �v���C���[�N���X
class CPlayer:public CObject
{
public:
	// ���
	typedef enum
	{
		TYPE_A = 0,
		TYPE_B,
		TYPE_MAX
	}TYPE;
	// ���
	typedef enum
	{
		STATE_NONE = 0,
		STATE_HIT,
		STATE_ACTION,
		STATE_DEAD,
		STATE_MAX
	}STATE;

	// �����o�֐�
	CPlayer(int nPriority = PRIORITY_PLAYER);
	~CPlayer();

	HRESULT Init(const char* pFileName, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void AddContents(int nAdd) { m_nCntContents += nAdd; if (m_nCntContents >= 99) { m_nCntContents = 99; } }
	void ClearContents(void);
	void Heal(int nHeal) { m_nLife += nHeal; if (m_nLife >= PLAYER_LIFE) { m_nLife = PLAYER_LIFE; } }
	void AddSpeed(float fAddSpeed) { m_fSpeed += fAddSpeed; }
	void Hit(const int nDamage);

	// �ݒ�
	void SetType(TYPE type) { m_type = type; };
	void SetBulletType(CBullet::TYPE type) { m_Bullet = type; }
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetPosOffSet(D3DXVECTOR3 pos) { m_posOffSet = pos; }
	void SetPosY(float Y) { m_pos.y = Y; }
	void SetTargetPos(D3DXVECTOR3 pos) { m_TargetPos = pos; }
	void SetUse(void) {m_bUse = true; m_nLife = PLAYER_LIFE;}
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	void MovePos(D3DXVECTOR3 move) { m_pos += move; }

	// �擾
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
	D3DXVECTOR3 GetPosOld(void) { return m_posOld; }
	D3DXVECTOR3 GetPosOffSet(void) { return m_posOffSet; }
	D3DXMATRIX GetMtx(void) { return m_mtxWorld; }
	CBullet::TYPE GetMyBullet(void) { return m_Bullet; }
	STATE GetState(void) { return m_State; }
	bool GetbMove(void) { return m_bMove; }
	int GetContents(void) { return m_nCntContents; }
	int GetNumModel(void) { return m_nNumModel; }
	int GetLife(void) { return m_nLife; }

	// �ÓI�����o�֐�
	static CPlayer* Create(const char* pFileName, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	static bool GetUse(void) { return m_bUse; }

private:
	void Move(void);
	void Action(void);
	bool Collision(void);
	void State(STATE state);
	void CheckStack(bool bColl, bool bMove);
	void RecoverFromStuck(void);
	void Blink(void);

	// �����o�ϐ�
	D3DXVECTOR3 m_pos;					// �ʒu
	D3DXVECTOR3 m_posOld;				// �O��̈ʒu
	D3DXVECTOR3 m_posOffSet;			// �ʒu(�I�t�Z�b�g)
	D3DXVECTOR3 m_rot;					// ����
	D3DXVECTOR3 m_rotDest;				// �ڕW�̌���
	D3DXVECTOR3 m_move;					// �ړ���
	D3DXVECTOR3 m_size;					// �T�C�Y
	D3DXVECTOR3 m_TargetPos;			// �ڕW�̈ʒu
	D3DXMATRIX m_mtxWorld;				// ���[���h�}�g���b�N�X
	D3DXCOLOR m_BaseColor;				// �ʏ�̐F
	D3DXCOLOR m_DamageColor;			// �_���[�W���̐F

	STATE m_State;						// ���
	TYPE m_type;						// ���
	CShadow* m_pShadow;					// �e�ւ̃|�C���^
	CShadowS* m_pShadowS;				// �X�e���V���e�ւ̃|�C���^
	int m_nCntState;					// ��ԃJ�E���^�[
	int m_nCntStackt;					// �X�^�b�N�J�E���g
	bool m_bMove;						// �ړ����Ă��邩
	// �X�e�[�^�X
	int m_nLife;						// ���C�t
	float m_fSpeed;						// �ړ����x
	// ���f��
	CModel* m_apModel[PLAYER_MODEL];	// ���f���ւ̃|�C���^
	CMotion* m_pMotion;					// ���[�V�����ւ̃|�C���^
	int m_nNumModel;					// ���f���ő吔
	// �e
	CBullet::TYPE m_Bullet;				// �e�̎��
	int m_nCntContents;					// ���g�̎c��
	float m_fShotTimer;					// ���ˊԊu�J�E���g
	const float SHOT_INTERVAL = 1.0f;	// ���ˊԊu
	const float SHOT_TIMESUB = 0.05f;	// ���ˎ��Ԃ����炷�l

	// �ÓI�����o�ϐ�
	static bool m_bUse;					// �g�p���Ă��邩
};

#endif