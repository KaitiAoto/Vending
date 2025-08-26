//==========================
//
//  入力処理[input.h]
//  Author:kaiti
//
//==========================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"


#define NUM_KEY_MAX (256)

//入力クラス
class CInput
{
public:

	//メンバ関数
	CInput();
	virtual ~CInput() = 0;
	virtual HRESULT Init(HINSTANCE hInstance);
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;

protected:
	static LPDIRECTINPUT8 m_pInput;
};

//キー入力クラス
class CInputKey :public CInput
{
public:

	//メンバ関数
	CInputKey();
	~CInputKey();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);
	bool GetRepeat(int nKey);

private:
	//メンバ変数
	BYTE m_aKeyState[NUM_KEY_MAX];
	BYTE m_aOldState[NUM_KEY_MAX];

	LPDIRECTINPUTDEVICE8 m_pDevice;
};

//パッドクラス
class CInputPad :public CInput
{
public:
	//キーの種類
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

	//メンバ関数
	CInputPad();
	~CInputPad();
	HRESULT Init(HINSTANCE hInstance);
	void Uninit(void);
	void Update(void);
	bool GetPress(JOYKEY nKey);
	bool GetTrigger(JOYKEY nKey);
	bool GetJoyStick();
	XINPUT_STATE* GetJoyStickAngle(void);
	float GetRightStickX();
	float GetRightStickY();

	bool GetStickTriggerUp();
	bool GetStickTriggerDown();
private:
	//メンバ変数
	XINPUT_STATE m_joyKeyState;
	XINPUT_STATE m_joyKeyStateTrigger;//ジョイパッドのトリガー

	SHORT m_prevLY;
};

//マウスクラス
class CInputMouse :public CInput
{
public:

	//メンバ関数
	CInputMouse();
	~CInputMouse();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);
	bool GetRepeat(int nKey);

	int GetRelX(void);
	int GetRelY(void);

	int GetX(void);
	int GetY(void);

	int GetWheel(void);
	void ResetWheel(void) { m_wheel = 0; };

private:

	BYTE m_aButtonState[8];
	BYTE m_aOldButtonState[8];

	int m_relX;
	int m_relY;
	int m_mouseX;
	int m_mouseY;
	int m_wheel;  // ホイールの1フレーム変化量
	//メンバ変数
	LPDIRECTINPUTDEVICE8 m_pDevice;
};

#endif
