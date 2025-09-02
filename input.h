//==========================
//
//  ���͏���[input.h]
//  Author:kaiti
//
//==========================

// ��d�C���N���[�h�h�~
#ifndef _INPUT_H_
#define _INPUT_H_

// �C���N���[�h
#include "main.h"

// �}�N����`
#define NUM_KEY_MAX (256)

// ���̓N���X
class CInput
{
public:

	// �����o�֐�
	CInput();
	virtual ~CInput() = 0;
	virtual HRESULT Init(HINSTANCE hInstance);
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;

protected:
	// �ÓI�����o�ϐ�
	static LPDIRECTINPUT8 m_pInput; // ����
};

// �L�[���̓N���X
class CInputKey :public CInput
{
public:

	// �����o�֐�
	CInputKey();
	~CInputKey();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	// �擾
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);
	bool GetRepeat(int nKey);

private:
	// �����o�ϐ�
	BYTE m_aKeyState[NUM_KEY_MAX];	// �L�[�̏��
	BYTE m_aOldState[NUM_KEY_MAX];	// �O�̏��

	LPDIRECTINPUTDEVICE8 m_pDevice;	// �f�o�C�X
};

// �p�b�h�N���X
class CInputPad :public CInput
{
public:
	// �L�[�̎��
	typedef enum
	{
		JOYKEY_UP = 0,
		JOYKEY_DOWN,
		JOYKEY_LEFT,
		JOYKEY_RIGET,
		JOYKEY_START,
		JOYKEY_BACK,
		JOYKEY_L3,
		JOYKEY_R3,
		JOYKEY_L1,
		JOYKEY_R1,
		JOYKEY_L2,
		JOYKEY_R2,
		JOYKEY_A,
		JOYKEY_B,
		JOYKEY_X,
		JOYKEY_Y,
		JOYKEY_MAX
	}JOYKEY;

	// �����o�֐�
	CInputPad();
	~CInputPad();
	HRESULT Init(HINSTANCE hInstance);
	void Uninit(void);
	void Update(void);

	// �擾
	bool GetPress(JOYKEY nKey);
	bool GetTrigger(JOYKEY nKey);
	bool GetJoyStick();
	bool GetStickTriggerUp();
	bool GetStickTriggerDown();
	XINPUT_STATE* GetJoyStickAngle(void);
	float GetRightStickX();
	float GetRightStickY();
private:
	// �����o�ϐ�
	XINPUT_STATE m_joyKeyState;			// �W���C�p�b�h�̏��
	XINPUT_STATE m_joyKeyStateTrigger;	// �W���C�p�b�h�̃g���K�[

	SHORT m_prevLY;						// ���X�e�B�b�N�̂x
};

// �}�E�X�N���X
class CInputMouse :public CInput
{
public:

	// �����o�֐�
	CInputMouse();
	~CInputMouse();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	void ResetWheel(void) { m_wheel = 0; };

	// �擾
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);
	bool GetRepeat(int nKey);
	int GetRelX(void);
	int GetRelY(void);
	int GetX(void);
	int GetY(void);
	int GetWheel(void);

private:

	// �����o�ϐ�
	BYTE m_aButtonState[8];				// ���݂̃{�^�����
	BYTE m_aOldButtonState[8];			// �O�t���[���̃{�^�����
	int m_relX;							// �ړ��ʁiX���j
	int m_relY;							// �ړ��ʁiY���j
	int m_mouseX;						// �J�[�\���̐�Έʒu�iX���W�j
	int m_mouseY;						// �J�[�\���̐�Έʒu�iY���W�j
	int m_wheel;						// �z�C�[����1�t���[���ω���
	LPDIRECTINPUTDEVICE8 m_pDevice;		// �f�o�C�X
};

#endif
