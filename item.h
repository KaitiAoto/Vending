//==============================
//
// �e[bullet.h]
// Author:kaiti
//
//==============================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"
#include "object.h"
#include "model.h"
#include "player.h"

#define ITEM_LIFE (1200)
#define ITEM_HEAL (PLAYER_LIFE / 4)
#define ITEM_BULLET (10)
//�I�u�W�F�N�g2D�N���X
class CItem:public CObject
{
public:
	//���
	typedef enum
	{
		TYPE_BULLET = 0,
		TYPE_LIFE,
		TYPE_MAX
	}TYPE;

	//�����o�֐�
	CItem(int nPriority = PRIORITY_ITEM);
	~CItem();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CItem* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, TYPE type);

	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
	TYPE GetType(void) { return m_type; }
	void SetUse(bool bUse) { m_bUse = bUse; }
	bool GetUse(void) { return m_bUse; }
	void Bonus(void);

private:
	void Move(void);

	//�����o�ϐ�
	D3DXVECTOR3 m_pos;					//�ʒu(�I�t�Z�b�g)
	D3DXVECTOR3 m_rot;					//����
	D3DXVECTOR3 m_move;					//�ړ���
	D3DXMATRIX m_mtxWorld;				//���[���h�}�g���b�N�X
	D3DXVECTOR3 m_rotDest;				//�ڕW�̌���
	D3DXVECTOR3 m_size;					//�T�C�Y

	CModel* m_pModel;	//���f���ւ̃|�C���^

	int m_nLife;			//����
	TYPE m_type;			//���
	bool m_bUse;			//�g�p���Ă��邩

	float m_fFloatTime;
};

#endif