//==============================
//
// ��[����[restock.h]
// Author:kaiti
//
//==============================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"
#include "object2D.h"

#define TUTORIAL_SIZE (200)

//�I�u�W�F�N�g2D�N���X
class CTutorial:public CObject2D
{
public:
	//���
	typedef enum
	{
		TYPE_MOVE = 0,
		TYPE_CAMERA,
		//TYPE_JUMP,
		TYPE_BULLET,
		TYPE_RESTOCK,
		TYPE_MATCHUP,
		TYPE_MAX
	}TYPE;
	//���
	typedef enum
	{
		STATE_STAY = 0,
		STATE_SLIDEIN,
		STATE_SLIDEOUT,
		STATE_MAX
	}STATE;


	//�����o�֐�
	CTutorial(int nPriority = 7);
	~CTutorial();

	static CTutorial* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
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

	void CheckClear(void);

	//�����o�ϐ�
	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_posStay;	//�ʒu
	D3DXVECTOR3 m_posOut;	//�ʒu

	D3DXVECTOR3 m_rot;	//�p�x

	bool m_bUse;
	bool m_bClear;
	int m_nIdxTex;

	TYPE m_type;
	const char* m_apFileName[TYPE_MAX];

	int m_nTime;

	STATE m_state;
};

#endif