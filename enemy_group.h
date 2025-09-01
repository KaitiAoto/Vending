//==============================
//
// �G�O���[�v[enemy_group.h]
// Author:kaiti
//
//==============================
#ifndef _ENEMY_GROUP_H_
#define _ENEMY_GROUP_H_

#include "main.h"
#include "object.h"
// �}�N����`
#define ENEMYGROUP_RESPAWN (2400)

// �G�O���[�v�N���X
class CEnemyGroup:public CObject
{
public:
	// �����o�֐�
	CEnemyGroup(int nPriority = PRIORITY_ENEMYBASE);
	~CEnemyGroup();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEnemyGroup* Create(const D3DXVECTOR3 pos);
	
	// �ݒ�
	void SetRespawn(bool bUse) { m_bRespawn = bUse; }

	// �擾
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	bool GetUse(void) { return m_bUse; }

	void SubMyEnemy(void) { m_MyEnemy--; }
private:
	void CreateEnemy(void);

	// �����o�ϐ�
	D3DXVECTOR3 m_pos;		// �ʒu
	bool m_bUse;			// �g�p���Ă��邩
	bool m_bRespawn;		// �����ł��邩
	int m_nRespawn;			// �����܂ł̎��ԃJ�E���g
	int m_MyEnemy;			// �O���[�v�Ɋ܂܂��G��
};

#endif