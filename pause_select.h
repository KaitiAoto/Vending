//=================================
//
// �|�[�Y�I��[pause_select.h]
// Author:kaiti
//
//=================================
#ifndef _PAUSE_SELECT_H_
#define _PAUSE_SELECT_H_

#include "main.h"
#include "object2D.h"

//�I�u�W�F�N�g2D�N���X
class CPauseSelect:public CObject2D
{
public:

	//�����o�֐�
	CPauseSelect(int nPriority = 10);
	~CPauseSelect();
	HRESULT Init(const char* pTexName, D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPauseSelect* Create(const char* pTexName, D3DXVECTOR3 pos, float fWidth, float fHeight);
private:
	//�����o�ϐ�
};

#endif