//================================
//
//�@�J��������[camera.h]
//�@Author:kaiti
//
//================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//�J�����N���X
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
	D3DXVECTOR3 GetRot(void) { return m_rot; }

	void Set(void);
	void SetPosV(D3DXVECTOR3 posV) { m_posV = posV; }
	void SetPosR(D3DXVECTOR3 posR) { m_posR = posR; }
private:
	// �����o�ϐ�
	D3DXVECTOR3 m_posV;			// ���_
	D3DXVECTOR3 m_posR;			// �����_
	D3DXVECTOR3 m_posVDest;		// ���_
	D3DXVECTOR3 m_posRDest;		// �����_
	D3DXVECTOR3 m_vecU;			// ������x�N�g��
	D3DXVECTOR3 m_posVOffSet;	// ���_
	D3DXVECTOR3 m_rot;			// ����

	D3DXMATRIX m_mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;		// �r���[�}�g���b�N�X
	float m_fDistance;			// ���_���璍���_�̋���

};

#endif