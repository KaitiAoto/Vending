//================================
//
// �}�l�[�W���[����[manager.h]
// Author:kaiti
//
//================================

// ��d�C���N���[�h�h�~
#ifndef _MANAGER_H_
#define _MANAGER_H_

// �C���N���[�h
#include "main.h"
#include "scene.h"
#include "game.h"
#include "fade.h"
#include "result.h"
#include "ranking.h"

// �}�N����`
#define GRAVITY (0.7f)

// �O���錾
class CRenderer;
class CInputKey;
class CInputMouse;
class CInputPad;
class CCamera;
class CTexture;
class CSound;
class CLight;
class CDebugProc;
class CScene;

// �}�l�[�W���[�N���X
class CManager
{
public:

	// �����o�֐�
	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInstance,HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	// �擾
	static CRenderer* GetRenderer(void) { return m_pRenderer; }
	static CInputKey* GetInputKey(void) { return m_pInputKey; }
	static CInputMouse* GetInputMouse(void) { return m_pInputMouse; }
	static CInputPad* GetInputPad(void) { return m_pInputPad; }
	static CCamera* GetCamera(void) { return m_pCamera; }
	static CLight* GetLight(void) { return m_pLight; }
	static CTexture* GetTex(void) { return m_pTex; }
	static CSound* GetSound(void) { return m_pSound; }
	static CDebugProc* GetDebug(void) { return m_pDebug; }
	static CFade* GetFade(void) { return m_pFade; }
	static CScene* GetScene(void) { return m_pScene; }
	
	static CScene::MODE GetMode(void) { return m_pScene->GetMode(); };
	static bool GetPause(void) { return m_bPause; }

	// �ݒ�
	static void SetMode(CScene::MODE mode);
	static void SetPause(bool bPause) { m_bPause = bPause; }

private:
	//�����o�֐�
	HRESULT CreatePointa(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void ReleasePointa(void);

	//�ÓI�����o�ϐ�
	static CRenderer* m_pRenderer;			// �����_���[�ւ̃|�C���^
	static CInputKey* m_pInputKey;			// �L�[���͂ւ̃|�C���^
	static CInputMouse* m_pInputMouse;		// �}�E�X���͂ւ̃|�C���^
	static CInputPad* m_pInputPad;			// �p�b�h���͂ւ̃|�C���^
	static CTexture* m_pTex;				// �e�N�X�`���ւ̃|�C���^
	static CCamera* m_pCamera;				// �J�����ւ̃|�C���^
	static CLight* m_pLight;				// ���C�g�ւ̃|�C���^
	static CSound* m_pSound;				// �T�E���h�ւ̃|�C���^
	static CDebugProc* m_pDebug;			// �f�o�b�O�ւ̃|�C���^
	static CFade* m_pFade;					// �t�F�[�h�ւ̃|�C���^
	static CScene* m_pScene;				// �V�[���ւ̃|�C���^

	static bool m_bPause;					// �|�[�Y����

};

#endif