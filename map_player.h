//==============================
//
// ��[����[restock.h]
// Author:kaiti
//
//==============================
#ifndef _MAP_PLAYER_H_
#define _MAP_PLAYER_H_

#include "main.h"
#include "object2D.h"
#include "bullet.h"

//�I�u�W�F�N�g2D�N���X
class CMapPlayer:public CObject2D
{
public:

	//�����o�֐�
	CMapPlayer(int nPriority = 8);
	~CMapPlayer();

	static CMapPlayer* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�擾����
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	bool GetUse(void){return m_bUse;}
	//�ݒ菈��

	void SetIdxTex(const int nIdxTex) { m_nIdxTex = nIdxTex; }
	void SetUse(bool bUse) { m_bUse = bUse; }
private:
	
	//�����o�ϐ�
	D3DXVECTOR3 m_pos;	//�ʒu

	int m_nIdxTex;
	bool m_bUse;
};

#endif