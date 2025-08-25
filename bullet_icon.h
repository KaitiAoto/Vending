//==============================
//
// ��[����[restock.h]
// Author:kaiti
//
//==============================
#ifndef _BULLET_ICON_H_
#define _BULLET_ICON_H_

#include "main.h"
#include "object2D.h"
#include "bullet.h"

#define BULLETICON_SIZE (80)

//�I�u�W�F�N�g2D�N���X
class CBulletIcon:public CObject2D
{
public:

	//�����o�֐�
	CBulletIcon(int nPriority = 7);
	~CBulletIcon();

	static CBulletIcon* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void ChangeIcon(CBullet::TYPE type);

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

	CBullet::TYPE m_type;
};

#endif