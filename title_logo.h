//==============================
//
// ��[����[restock.h]
// Author:kaiti
//
//==============================
#ifndef _TITLE_LOGO_H_
#define _TITLE_LOGO_H_

#include "main.h"
#include "object2D.h"

#define LOGO_SIZE_X (450)
#define LOGO_SIZE_Y (300)

//�I�u�W�F�N�g2D�N���X
class CTitleLogo:public CObject2D
{
public:

	//�����o�֐�
	CTitleLogo(int nPriority = 8);
	~CTitleLogo();

	static CTitleLogo* Create(const char* pTexName, D3DXVECTOR3 pos, float fWidth, float fHeight);
	HRESULT Init(const char* pTexName, D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�擾����
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	bool GetStop(void) { return m_bStop; }
	//�ݒ菈��

private:

	//�����o�ϐ�
	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_posStay;	//�ʒu
	D3DXVECTOR3 m_rot;	//�p�x
	D3DXVECTOR3 m_move;					//�ړ���

	bool m_bUse;
	int m_nTime;

	int m_AnimCnt;

	bool m_bStop;
};

#endif