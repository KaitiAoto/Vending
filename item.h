//==============================
//
// �A�C�e��[item.h]
// Author : Kaiti Aoto
//
//==============================

// ��d�C���N���[�h�h�~
#ifndef _ITEM_H_
#define _ITEM_H_

// �C���N���[�h
#include "main.h"
#include "object.h"
#include "model.h"
#include "player.h"

// �}�N����`
#define ITEM_LIFE (1200)
#define ITEM_HEAL (PLAYER_LIFE / 4)
#define ITEM_BULLET (10)
// �A�C�e���N���X
class CItem:public CObject
{
public:
	// ���
	typedef enum
	{
		TYPE_BULLET = 0,
		TYPE_LIFE,
		TYPE_MAX
	}TYPE;

	// �����o�֐�
	CItem(int nPriority = PRIORITY_ITEM);
	~CItem();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Bonus(void);

	// �擾
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
	TYPE GetType(void) { return m_type; }
	bool GetUse(void) { return m_bUse; }
	// �ݒ�
	void SetUse(bool bUse) { m_bUse = bUse; }

	// �ÓI�����o�֐�
	static CItem* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, TYPE type);

private:
	void Move(void);

	// �����o�ϐ�
	D3DXVECTOR3 m_pos;		// �ʒu(�I�t�Z�b�g)
	D3DXVECTOR3 m_rot;		// ����
	D3DXVECTOR3 m_move;		// �ړ���
	D3DXVECTOR3 m_rotDest;	// �ڕW�̌���
	D3DXVECTOR3 m_size;		// �T�C�Y
	D3DXMATRIX m_mtxWorld;	// ���[���h�}�g���b�N�X

	CModel* m_pModel;		// ���f���ւ̃|�C���^
	int m_nLife;			// ����
	TYPE m_type;			// ���
	bool m_bUse;			// �g�p���Ă��邩
	float m_fFloatTime;		// ���V����
};

#endif