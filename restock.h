//==============================
//
// ��[����[restock.h]
// Author:kaiti
//
//==============================
#ifndef RESTOCK_H_
#define RESTOCK_H_

#include "main.h"
#include "object2D.h"
#include "bullet.h"
#include "vender.h"

#define RESTOCK_SIZE (150)

//�I�u�W�F�N�g2D�N���X
class CRestock:public CObject2D
{
public:

	//�����o�֐�
	CRestock(int nPriority = 7);
	~CRestock();

	static CRestock* Create(const char* pTexName, D3DXVECTOR3 pos, float fWidth, float fHeight);
	HRESULT Init(const char* pTexName, D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Set(int nRestock, CBullet::TYPE type, CVender* pVender);

	//�擾����
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	bool GetUse(void){return m_bUse;}
	//�ݒ菈��

	void SetIdxTex(const int nIdxTex) { m_nIdxTex = nIdxTex; }
	void SetUse(bool bUse) { m_bUse = bUse; }
private:
	
	//�����o�ϐ�
	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_rot;	//�p�x

	int m_nIdxTex;
	bool m_bUse;
};

#endif