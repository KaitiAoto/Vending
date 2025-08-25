//================================
//
//�@�J��������[camera.h]
//�@Author:kaiti
//
//================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"


//�N���X
class CCamera
{
public:

	//�����o�֐�
	CCamera();
	//���z�֐�
	~CCamera();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void UpdateMenu(void);
	void Set(void);
	D3DXVECTOR3 GetRot(void) { return m_rot; }

	void SetPosV(D3DXVECTOR3 posV) { m_posV = posV; }
	void SetPosR(D3DXVECTOR3 posR) { m_posR = posR; }
private:
	D3DXVECTOR3 m_posV;//���_
	D3DXVECTOR3 m_posR;//�����_
	D3DXVECTOR3 m_posVDest;//���_
	D3DXVECTOR3 m_posRDest;//�����_

	D3DXVECTOR3 m_vecU;//������x�N�g��
	D3DXMATRIX m_mtxProjection;//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;//�r���[�}�g���b�N�X
	D3DXVECTOR3 m_rot;//����
	float m_fDistance;//���_���璍���_�̋���

	D3DXVECTOR3 m_posVOffSet;//���_
};

#endif