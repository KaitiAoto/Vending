//==============================
//
// �G���_[enemy_base.h]
// Author:kaiti
//
//==============================
#ifndef _ENEMY_GROUP_H_
#define _ENEMY_GROUP_H_

#include "main.h"
#include "object.h"

#define ENEMYGROUP_RESPAWN (2400)

//�I�u�W�F�N�g2D�N���X
class CEnemyGroup:public CObject
{
public:
	//�����o�֐�
	CEnemyGroup(int nPriority = PRIORITY_ENEMYBASE);
	~CEnemyGroup();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEnemyGroup* Create(const D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	bool GetUse(void) { return m_bUse; }
	void SetRespawn(bool bUse) { m_bRespawn = bUse; }

	void SubMyEnemy(void) { m_MyEnemy--; }
private:
	void CreateEnemy(void);

	//�����o�ϐ�
	D3DXVECTOR3 m_pos;					//�ʒu(�I�t�Z�b�g)

	bool m_bUse;			//�g�p���Ă��邩
	int m_nRespawn;
	bool m_bRespawn;

	int m_MyEnemy;
};

#endif