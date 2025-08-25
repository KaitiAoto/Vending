//==============================
//
// �����_�����O[renderer.h]
// Author:kaiti
//
//==============================
#ifndef RENDERER_H_
#define RENDERER_H_

#include "main.h"

//�����_�����O�̃N���X
class CRenderer
{
public:

	//�����o�֐�
	CRenderer();
	~CRenderer();
	HRESULT Init(HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	LPDIRECT3DDEVICE9 GetDevice(void) {return m_pD3DDevice;}

	void ChangeTarget(D3DXVECTOR3 posV, D3DXVECTOR3 posR, D3DXVECTOR3 VecU);
	LPDIRECT3DTEXTURE9 GetTexMT(void) { return m_pTexMT; }
private:	
	//�����o�ϐ�
	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pD3DDevice;

	LPDIRECT3DTEXTURE9 m_pTexMT;
	LPDIRECT3DSURFACE9 m_pRendMT;
	LPDIRECT3DSURFACE9 m_pZBuffMT;
	D3DVIEWPORT9 m_viewportMT;


	//LPD3DXFONT m_pFont = NULL;//�t�H���g�ւ̃|�C���^
	//int m_nCntFPS = 0;//FPS�J�E���^
	//DWORD dwFrameCount; //�t���[���J�E���g
	//DWORD dwFPSLastTime;//
	//DWORD dwCurrentTime;
	//DWORD dwExecLastTime;

};

#endif