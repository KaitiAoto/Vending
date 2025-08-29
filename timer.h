//===================
//
// �^�C�}�[[timer.h]
// Author:kaiti
//
//===================
#ifndef _TIMER_H_
#define _TIMER_H_

#include "main.h"
#include "number.h"
#include "object.h"

#define TIMER_SIZE (25)

//�I�u�W�F�N�g2D�N���X
class CTimer:public CObject
{
public:

	//�����o�֐�
	CTimer(int nPriority = 7);
	~CTimer();
	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTimer* Create(D3DXVECTOR3 pos);
	static int GetPriority(void) { return m_nPriority; }
	CNumber* GetNumber(void){return m_pNumber;}
private:
	//�����o�ϐ�
	static int m_nPriority;
	CNumber* m_pNumber;
};

#endif