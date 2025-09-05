//====================================
//
// �}�b�v�̓G���_[map_enemybase.h]
// Author : Kaiti Aoto
//
//====================================

// ��d�C���N���[�h�h�~
#ifndef _MAP_ENEMYBASE_H_
#define _MAP_ENEMYBASE_H_

// �C���N���[�h
#include "main.h"
#include "object2D.h"
#include "bullet.h"

// �}�b�v�̓G���_�N���X
class CMapEnemyBase:public CObject2D
{
public:

	// �����o�֐�
	CMapEnemyBase(int nPriority = 8);
	~CMapEnemyBase();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �擾����
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	bool GetUse(void){return m_bUse;}	
	// �ݒ菈��
	void SetIdxTex(const int nIdxTex) { m_nIdxTex = nIdxTex; }
	void SetUse(bool bUse) { m_bUse = bUse; }
	void SetBlink(bool bBlink) { m_bBlink = bBlink; }
	// �ÓI�����o�ϐ�
	static CMapEnemyBase* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

private:
	
	// �����o�ϐ�
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXCOLOR m_col;	// �F
	int m_nIdxTex;		// �e�N�X�`���̃C���f�b�N�X�ԍ�
	int m_nCntTime;		// �J�E���^�[
	bool m_bUse;		// �g�p���Ă��邩
	bool m_bBlink;		// �_�ł��邩�ǂ���
};

#endif