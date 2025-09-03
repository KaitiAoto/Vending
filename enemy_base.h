//==============================
//
// �G���_[enemy_base.h]
// Author : Kaiti Aoto
//
//==============================

// ��d�C���N���[�h�h�~
#ifndef _ENEMY_BASE_H_
#define _ENEMY_BASE_H_

// �C���N���[�h
#include "main.h"
#include "object.h"
#include "model.h"
#include "enemy_manager.h"
#include "meshcylinder.h"
#include "gauge_enemy.h"
#include "map_enemybase.h"

// �}�N����`
#define ENEMY_BASE_LIFE (120)
#define ENEMY_SPAN (300)
#define ENEMYBASE_RESPAWN (2400)

// �G���_�N���X
class CEnemyBase:public CObject
{
public:
	// �����o�֐�
	CEnemyBase(int nPriority = PRIORITY_ENEMYBASE);
	~CEnemyBase();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(const int nDamage);	

	// �ݒ�
	void SetRespawn(bool bUse) { m_bRespawn = bUse; }
	// �擾
	D3DXVECTOR3 GetSize(void) { return m_size; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXMATRIX GetMtx(void) { return m_mtxWorld; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	bool GetUse(void) { return m_bUse; }

	// �ÓI�����o�֐�
	static CEnemyBase* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);

private:
	void CreateEnemy(void);

	// �����o�ϐ�
	D3DXVECTOR3 m_pos;			// �ʒu
	D3DXVECTOR3 m_rot;			// ����
	D3DXVECTOR3 m_size;			// �T�C�Y

	D3DXMATRIX m_mtxWorld;		// ���[���h�}�g���b�N�X
	CModel* m_pModel;			// �ʏ펞�̃��f���ւ̃|�C���^
	CModel* m_pBreakModel;		// �j�󎞂̃��f���ւ̃|�C���^
	int m_nLife;				// ����
	int m_nCntSpan;				// �G�������ԃJ�E���g
	int m_nRespawn;				// �����܂ł̎���
	bool m_bUse;				// �g�p���Ă��邩
	bool m_bRespawn;			// �����ł��邩
	CEnemyGauge* m_pGauge;		// �Q�[�W�ւ̃|�C���^
	CMapEnemyBase* m_pMapIcon;	// �}�b�v�A�C�R���ւ̃|�C���^
};

#endif