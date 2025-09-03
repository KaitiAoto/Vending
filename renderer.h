//==============================
//
// �����_�����O[renderer.h]
// Author : Kaiti Aoto
//
//==============================

// ��d�C���N���[�h�h�~
#ifndef _RENDERER_H_
#define _RENDERER_H_

// �C���N���[�h
#include "main.h"

// �����_�����O�̃N���X
class CRenderer
{
public:

	// �����o�֐�
	CRenderer();
	~CRenderer();
	HRESULT Init(HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void ChangeTarget(D3DXVECTOR3 posV, D3DXVECTOR3 posR, D3DXVECTOR3 VecU);

	// �擾
	LPDIRECT3DDEVICE9 GetDevice(void) {return m_pD3DDevice;}
	LPDIRECT3DTEXTURE9 GetTexMT(void) { return m_pTexMT; }
private:	
	// �����o�ϐ�
	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pD3DDevice;

	LPDIRECT3DTEXTURE9 m_pTexMT;
	LPDIRECT3DSURFACE9 m_pRendMT;
	LPDIRECT3DSURFACE9 m_pZBuffMT;
	D3DVIEWPORT9 m_viewportMT;
};

#endif