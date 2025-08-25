//=====================================
//
// �G�}�l�[�W���[[enemy_manager.h]
// Author:kaiti
//
//=====================================
#ifndef ENEMY_MANAGER_H_
#define ENEMY_MANAGER_H_

#include "main.h"
#include "enemy.h"

//#define ENEMY_SPAN (300)

//�I�u�W�F�N�g2D�N���X
class CEnemyMana
{
public:

	//�����o�֐�
	CEnemyMana();
	~CEnemyMana();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	static CEnemyMana* Create();
	static void Add(void) { m_nCntEnemy++; }
	static void Sub(void) { m_nCntEnemy--; }
private:
	//�����o�ϐ�
	static CEnemyMana* m_pEnemyMane;	//�I�u�W�F�N�g�ւ̃|�C���^
	static int m_nCntEnemy;

	int m_nCntSpan;
};

#endif