//==============================
//
// �G���_[enemy_base.h]
// Author:kaiti
//
//==============================
#ifndef _ENEMY_BASE_H_
#define _ENEMY_BASE_H_

#include "main.h"
#include "object.h"
#include "model.h"
#include "enemy_manager.h"
#include "meshcylinder.h"
#include "gauge_enemy.h"
#include "map_enemybase.h"

#define ENEMY_BASE_LIFE (120)
#define ENEMY_SPAN (240)
#define ENEMYBASE_RESPAWN (3600)

//�I�u�W�F�N�g2D�N���X
class CEnemyBase:public CObject
{
public:
	typedef enum
	{
		TYPE_A = 0,
		TYPE_B,

		TYPE_MAX
	}TYPE;

	//�����o�֐�
	CEnemyBase(int nPriority = PRIORITY_ENEMYBASE);
	~CEnemyBase();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEnemyBase* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);
	D3DXVECTOR3 GetSize(void) { return m_size; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	void Hit(const int nDamage);
	D3DXMATRIX GetMtx(void) { return m_mtxWorld; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	bool GetUse(void) { return m_bUse; }
	void SetRespawn(bool bUse) { m_bRespawn = bUse; }

private:
	void CreateEnemy(void);

	//�����o�ϐ�
	D3DXVECTOR3 m_pos;					//�ʒu(�I�t�Z�b�g)
	D3DXVECTOR3 m_rot;					//����
	D3DXVECTOR3 m_size;					//�T�C�Y

	D3DXMATRIX m_mtxWorld;				//���[���h�}�g���b�N�X

	CModel* m_pModel;	//���f���ւ̃|�C���^
	CModel* m_pBreakModel;	//���f���ւ̃|�C���^

	int m_nLife;			//����
	TYPE m_type;			//���
	bool m_bUse;			//�g�p���Ă��邩
	int m_nPriority;
	int m_nCntSpan;
	int m_nRespawn;
	bool m_bRespawn;

	CEnemyGauge* m_pGauge;

	CMapEnemyBase* m_pMapIcon;
};

#endif