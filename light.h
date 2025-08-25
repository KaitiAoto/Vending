//================================
//
//�@���C�g����[light.h]
//�@Author:kaiti
//
//================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "main.h"

#define MAX_LIGHT (3)

//�N���X
class CLight
{
public:

	//�����o�֐�
	CLight();
	//���z�֐�
	~CLight();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	void SetColor(D3DXCOLOR col);
private:
	D3DLIGHT9 m_light[MAX_LIGHT]; //���C�g���

};

#endif