////===================
//
// �e���J�E���^�[[timer.h]
// Author:kaiti
//
//===================
#ifndef _BULLET_COUNTER_H_
#define _BULLET_COUNTER_H_

#include "main.h"
#include "number.h"
#include "object.h"

#define BULLET_COUNT_SIZE (30)

//�I�u�W�F�N�g2D�N���X
class CBullerCounter :public CObject
{
public:

	//�����o�֐�
	CBullerCounter(int nPriority = 7);
	~CBullerCounter();
	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBullerCounter* Create(D3DXVECTOR3 pos);
	static int GetPriority(void) { return m_nPriority; }
	CNumber* GetNumber(void) { return m_pNumber; }
private:
	//�����o�ϐ�
	static int m_nPriority;
	CNumber* m_pNumber;
};

#endif