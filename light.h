//================================
//
//�@���C�g����[light.h]
//�@Author : Kaiti Aoto
//
//================================

// ��d�C���N���[�h�h�~
#ifndef _LIGHT_H_
#define _LIGHT_H_

// �C���N���[�h
#include "main.h"

// �}�N����`
#define MAX_LIGHT (3)

// �N���X
class CLight
{
public:

	// �����o�֐�
	CLight();
	// ���z�֐�
	~CLight();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	// �ݒ�
	void SetColor(D3DXCOLOR col);
private:
	// �����o�ϐ�
	D3DLIGHT9 m_light[MAX_LIGHT]; // ���C�g���

};

#endif