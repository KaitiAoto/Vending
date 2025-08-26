//==============================
//
// ��[����[restock.h]
// Author:kaiti
//
//==============================
#ifndef _BUFF_ICON_H_
#define _BUFF_ICON_H_

#include "main.h"
#include "object2D.h"
#include "buff.h"

#define BUFF_X (200)
#define BUFF_Y (50)

//�I�u�W�F�N�g2D�N���X
class CBuffIcon:public CObject2D
{
public:
	//���
	typedef enum
	{
		STATE_STAY = 0,
		STATE_SLIDEIN,
		STATE_SLIDEOUT,
		STATE_MAX
	}STATE;


	//�����o�֐�
	CBuffIcon(int nPriority = 7);
	~CBuffIcon();

	static CBuffIcon* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�擾����
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	bool GetUse(void){return m_bUse;}
	//�ݒ菈��

	void SetUse(bool bUse) { m_bUse = bUse; }
private:
	void Move(void);

	//�����o�ϐ�
	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_posStay;	//�ʒu
	D3DXVECTOR3 m_posOut;	//�ʒu

	D3DXVECTOR3 m_rot;	//�p�x

	bool m_bUse;
	bool m_bClear;
	int m_nIdxTex;

	CBuff::TYPE m_type;
	const char* m_apFileName[CBuff::TYPE_MAX];

	int m_nTime;

	STATE m_state;
};

#endif