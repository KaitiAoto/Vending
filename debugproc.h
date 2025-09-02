//===========================================
//
// �f�o�b�O�\��[debugproc.h]
// Author:kaiti
//
//===========================================

// ��d�C���N���[�h�h�~
#ifndef _DEBUGPROC_H_
#define _DEBUGPROC_H_

// �C���N���[�h
#include "main.h"

// �}�N����`
#define MAX_DEBUGLINE (20)

// �f�o�b�O�N���X
class CDebugProc
{
public:

	// �����o�֐�
	CDebugProc();
	~CDebugProc();

	// �ÓI�����o�֐�
	static void Init(void);
	static void Uninit(void);
	static void Print(const char* fmt, ...);
	static void Draw(void);
private:
	// �ÓI�����o�ϐ�
	static LPD3DXFONT m_pFont;		// �t�H���g
	static char m_aStr[MAX_WORD];	// ������
	static int m_LineCount;			// ��J�E���g
	static bool m_bUse;				// �g�p���Ă��邩
};

#endif