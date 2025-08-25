//==============================
//
// ��[����[restock.h]
// Author:kaiti
//
//==============================
#ifndef _STARTUI_H_
#define _STARTUI_H_

#include "main.h"
#include "object2D.h"

#define STARTUI_SIZE_X (600)
#define STARTUI_SIZE_Y (300)

//�I�u�W�F�N�g2D�N���X
class CStartUI:public CObject2D
{
public:

	//�����o�֐�
	CStartUI(int nPriority = 7);
	~CStartUI();

	static CStartUI* Create(const char* pTexName, D3DXVECTOR3 pos, float fWidth, float fHeight);
	HRESULT Init(const char* pTexName, D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�擾����
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	//�ݒ菈��

private:
	void Move(void);

	//�����o�ϐ�
	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_posStay;	//�ʒu
	D3DXVECTOR3 m_rot;	//�p�x

	bool m_bStop;
	bool m_bUse;
	int m_nTime;
};

#endif