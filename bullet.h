//==============================
//
// �e[bullet.h]
// Author:kaiti
//
//==============================
#ifndef _BULET_H_
#define _BULET_H_

#include "main.h"
#include "object.h"
#include "model.h"
#include "effect.h"
// �}�N����`
#define BULET_SIZE (30)
#define BULLET_LIFE (200)
#define BULLET_ATTACK (10)
#define BULLET_SPEED (3.5f)

// �e�N���X
class CBullet:public CObject
{
public:
	// ���[�U�[
	typedef enum
	{
		USER_PLAYER = 0,
		USER_ENEMY,
		USER_MAX
	}USER;
	// ���
	typedef enum
	{
		TYPE_CAN = 0,
		TYPE_ICE,
		TYPE_CAPSULE,
		TYPE_PETBOTTLE,
		TYPE_DUST,
		TYPE_SNACK,
		TYPE_CIGARET,
		TYPE_CARD,
		TYPE_BOTTLE,
		TYPE_MAX
	}TYPE;

	// �����o�֐�
	CBullet(int nPriority = PRIORITY_BULLET);
	~CBullet();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, USER user);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBullet* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, USER user);

	// �擾
	int GetUser(void) { return m_user; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
	TYPE GetType(void) { return m_type; }
	bool GetUse(void) { return m_bUse; }

	// �ݒ�
	void SetUser(USER user) { m_user = user; };
	void SetUse(bool bUse) { m_bUse = bUse; }

private:
	void Move(void);
	void MoveBounce(void);
	bool Collision(void);
	const char* SetPlayerBullet(void);

	// �����o�ϐ�
	D3DXVECTOR3 m_pos;					// �ʒu(�I�t�Z�b�g)
	D3DXVECTOR3 m_rot;					// ����
	D3DXVECTOR3 m_move;					// �ړ���
	D3DXMATRIX m_mtxWorld;				// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_rotDest;				// �ڕW�̌���
	D3DXVECTOR3 m_size;					// �T�C�Y

	CModel* m_pModel;					// ���f���ւ̃|�C���^
	int m_nLife;						// ����
	TYPE m_type;						// ���
	USER m_user;						// ���[�U�[
	bool m_bUse;						// �g�p���Ă��邩
};

#endif