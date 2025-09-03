//==============================
//
// �I�u�W�F�N�g[object.h]
// Author : Kaiti Aoto
//
//==============================

// ��d�C���N���[�h�h�~
#ifndef _OBJECT_H_
#define _OBJECT_H_

// �C���N���[�h
#include "main.h"

// �}�N����`
#define NUM_PRIORITY (11)

#define PRIORITY_PLAYER (6)
#define PRIORITY_BULLET (5)
#define PRIORITY_ENEMY (5)
#define PRIORITY_ENEMYBASE (6)
#define PRIORITY_VENDER (5)
#define PRIORITY_STAGE (4)
#define PRIORITY_GIMMIC (5)
#define PRIORITY_ITEM (5)
#define PRIORITY_START (4)

// �I�u�W�F�N�g�N���X
class CObject
{
public:

	// ���
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_PLAYER,
		TYPE_ENEMY,
		TYPE_ENEMY_BASE,
		TYPE_BULLET,
		TYPE_VENDER,
		TYPE_GIMMICK,
		TYPE_SHADOW,
		TYPE_STAGE,
		TYPE_FIELD,
		TYPE_WALL,
		TYPE_START,
		TYPE_EFFECT,
		TYPE_ITEM,
		TYPE_NUMBER,
		TYPE_SCORE,
		TYPE_TIME,
		TYPE_RESTOCK,
		TYPE_BULLETCNT,
		TYPE_GAUGE,
		TYPE_UI,
		TYPE_MAX
	}TYPE;

	// �����o�֐�
	CObject(int nPriority = 3);
	// ���z�֐�
	virtual ~CObject();

	// �������z�֐�
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	// �ݒ�
	void SetObjType(TYPE type) { m_Objtype = type; }
	// �擾
	TYPE GetObjType(void) { return m_Objtype; }
	int GetPrio(void) { return m_nPriority; }
	CObject* GetNext(void) { return m_pNext; }

	// �ÓI�����o�֐�
	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);
	static CObject* GetTop(int nPrio) { return m_apTop[nPrio];}

protected:
	void Release(void);

private:
	static void DeathCheck(void);

	// �����o�ϐ�
	CObject* m_pPrev;						// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CObject* m_pNext;						// ���̃I�u�W�F�N�g�ւ̃|�C���^
	TYPE m_Objtype;							// ���
	int m_nPriority;						// �`�揇
	bool m_bDeath;							// ���S�t���O

	// �ÓI�����o�ϐ�
	static CObject* m_apTop[NUM_PRIORITY];	// �擪�I�u�W�F�N�g�ւ̃|�C���^
	static CObject* m_apCur[NUM_PRIORITY];	// �Ō���I�u�W�F�N�g�ւ̃|�C���^
	static int m_nNumAll;					// �ő吔

};

#endif