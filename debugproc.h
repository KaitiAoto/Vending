//===========================================
//
// �f�o�b�O�\��[debugproc.h]
// Author:kaiti
//
//===========================================
#ifndef _DEBUGPROC_H_
#define _DEBUGPROC_H_

#include "main.h"

#define MAX_DEBUGLINE (20)
//�f�o�b�O�N���X
class CDebugProc
{
public:

	//�����o�֐�
	CDebugProc();
	~CDebugProc();

	static void Init(void);
	static void Uninit(void);
	static void Print(const char* fmt, ...);
	static void Draw(void);
private:
	//�����o�ϐ�
	static LPD3DXFONT m_pFont;
	static char m_aStr[MAX_WORD];
	static int m_LineCount;
	static bool m_bUse;
};

#endif