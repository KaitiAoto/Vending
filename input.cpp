//===========================
//
//  ���͏���[input.cpp]
//  Author:kaiti
//
//===========================
#include "input.h"
//�ÓI�����o�ϐ�
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//==================
// �R���X�g���N�^
//==================
CInput::CInput()
{
}
//================
// �f�X�g���N�^
//================
CInput::~CInput()
{
}
//=======================
// ����������
//=======================
HRESULT CInput::Init(HINSTANCE hInstance)
{
	if (m_pInput == NULL)
	{
		//������
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}
	return S_OK;
}
//=======================
// �I������
//=======================
void CInput::Uninit(void)
{
	////���̓f�o�C�X�̔j��
	//if (m_pDevice != NULL)
	//{
	//	m_pDevice->Unacquire();
	//	m_pDevice->Release();
	//	m_pDevice = NULL;
	//}
	//DirectInput�I�u�W�F�N�g�̔j��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}


//==========================================
// 
// �L�[����
// 
//==========================================
//==================
// �R���X�g���N�^
//==================
CInputKey::CInputKey()
{
	memset(m_aKeyState, 0, sizeof(m_aKeyState));
	memset(m_aOldState, 0, sizeof(m_aOldState));
}
//================
// �f�X�g���N�^
//================
CInputKey::~CInputKey()
{
}
//=======================
//�L�[�{�[�h�̏���������
//=======================
HRESULT CInputKey::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance);

	//
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//�������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	m_pDevice->Acquire();

	return S_OK;
}
//=======================
//�L�[�{�[�h�̏I������
//=======================
void CInputKey::Uninit(void)
{
	//���̓f�o�C�X�̔j��
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	CInput::Uninit();
}
//=======================
//�L�[�{�[�h�̍X�V����
//=======================
void CInputKey::Update(void)
{
	if (!m_pDevice)
		return; // NULL �`�F�b�N

	BYTE aKeyState[NUM_KEY_MAX] = {};
	memcpy(m_aOldState, m_aKeyState, sizeof(m_aKeyState));

	HRESULT hr = m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0]);
	if (FAILED(hr)) 
	{
		m_pDevice->Acquire();
		hr = m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0]); // �Ď擾
		OutputDebugStringA("GetDeviceState failed. Trying to Acquire...\n");
	}
	if (SUCCEEDED(hr)) 
	{
		memcpy(m_aKeyState, aKeyState, sizeof(m_aKeyState));
	}
	else 
	{
		memset(m_aKeyState, 0, sizeof(m_aKeyState));  // ���s���̓N���A
	}

	//HRESULT hr = m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0]);
	//if (SUCCEEDED(hr))
	//{
	//	memcpy(m_aKeyState, aKeyState, sizeof(m_aKeyState));
	//}
	//else
	//{
	//	m_pDevice->Acquire();
	//	//m_pDevice = NULL;
	//	memset(m_aKeyState, 0, sizeof(m_aKeyState));  // ��Ԃ��N���A
	//}
}
//==============================
//�L�[�{�[�h�̃v���X�����擾
//==============================
bool CInputKey::GetPress(int nKey)
{
	return(m_aKeyState[nKey] & 0x080) ? true : false;
}
//================================
//�L�[�{�[�h�̃g���K�[�����擾
//================================
bool CInputKey::GetTrigger(int nKey)
{
	bool Trigger = false;
	if (m_aKeyState[nKey] & 0x80 && !(m_aOldState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}
bool CInputKey::GetRelease(int nKey)
{
	bool Trigger = false;
	if (m_aOldState[nKey] & 0x80 && !(m_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}
bool CInputKey::GetRepeat(int nKey)
{
	bool Trigger = false;
	if (m_aOldState[nKey] & 0x80 && (m_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}


//===================================
// 
// �R���g���[���[
// 
//===================================
//==================
// �R���X�g���N�^
//==================
CInputPad::CInputPad()
{
	m_joyKeyState = {};
	m_joyKeyStateTrigger = {};
}
//================
// �f�X�g���N�^
//================
CInputPad::~CInputPad()
{
}
//============================
//�R���g���[���[�̏���������
//============================
HRESULT CInputPad::Init(HINSTANCE hInstance)
{
	CInput::Init(hInstance);
	//�������̃N���A
	memset(&m_joyKeyState, 0, sizeof(XINPUT_STATE));
	memset(&m_joyKeyStateTrigger, 0, sizeof(XINPUT_STATE));

	//XInput�̃X�e�[�g��ݒ�(�L��)
	XInputEnable(true);

	return S_OK;
}
//============================
//�R���g���[���[�̏I������
//============================
void CInputPad::Uninit(void)
{
	//XInput�̃X�e�[�g��ݒ�(����)
	XInputEnable(false);

	CInput::Uninit();
}
//============================
//�R���g���[���[�̍X�V����
//============================
void CInputPad::Update(void)
{
	XINPUT_STATE joykeyState;
	//
	if (XInputGetState(0, &joykeyState) == ERROR_SUCCESS)
	{
		WORD Button = joykeyState.Gamepad.wButtons;
		WORD OldButton = m_joyKeyState.Gamepad.wButtons;

		m_joyKeyStateTrigger.Gamepad.wButtons = Button & ~OldButton;

		m_prevLY = m_joyKeyState.Gamepad.sThumbLY;

		// R/L2�g���K�[�̑O��l��ۑ�
		m_prevR2Trigger = m_joyKeyState.Gamepad.bRightTrigger;
		m_prevL2Trigger = m_joyKeyState.Gamepad.bLeftTrigger;

		m_joyKeyState = joykeyState;
	}
}
//=================================
//�R���g���[���[�̃v���X�����擾
//=================================
bool CInputPad::GetPress(JOYKEY key)
{
	return (m_joyKeyState.Gamepad.wButtons &(0x01 << key)) ? true : false;
}
//===================================
//�W���C�p�b�h�̃g���K�[�����擾
//===================================
bool CInputPad::GetTrigger(JOYKEY key)
{
	return(m_joyKeyStateTrigger.Gamepad.wButtons & (0x01 << key)) ? true : false;
}
bool CInputPad::GetJoyStick()
{
	bool joykey = false;

	if (m_joyKeyState.Gamepad.sThumbLX >= 100 
		|| m_joyKeyState.Gamepad.sThumbLX <= -100 
		|| m_joyKeyState.Gamepad.sThumbLY >= 100 
		|| m_joyKeyState.Gamepad.sThumbLY <= -100)
	{
		joykey = true;
	}
	return joykey;
}
XINPUT_STATE* CInputPad::GetJoyStickAngle(void)
{
	return &m_joyKeyState;
}
float CInputPad::GetRightStickX()
{
	return (m_joyKeyState.Gamepad.sThumbRX / 32768.0f);
}
float CInputPad::GetRightStickY()
{
	return (m_joyKeyState.Gamepad.sThumbRY / 32768.0f);
}
bool CInputPad::GetStickTriggerUp()
{
	const int DEADZONE = 10000;
	SHORT cur = m_joyKeyState.Gamepad.sThumbLY;
	return (cur > DEADZONE && m_prevLY <= DEADZONE);
}
bool CInputPad::GetStickTriggerDown()
{
	const int DEADZONE = 10000;
	SHORT cur = m_joyKeyState.Gamepad.sThumbLY;
	return (cur < -DEADZONE && m_prevLY >= -DEADZONE);
}

bool CInputPad::GetR2Trigger(BYTE threshold)
{
	return (m_joyKeyState.Gamepad.bRightTrigger > threshold && m_prevR2Trigger <= threshold);
}

bool CInputPad::GetL2Trigger(BYTE threshold)
{
	return (m_joyKeyState.Gamepad.bLeftTrigger > threshold && m_prevL2Trigger <= threshold);
}

bool CInputPad::GetR2Press(BYTE threshold)
{
	return (m_joyKeyState.Gamepad.bRightTrigger > threshold);
}

bool CInputPad::GetL2Press(BYTE threshold)
{
	return (m_joyKeyState.Gamepad.bLeftTrigger > threshold);
}


//==========================================
// 
// �}�E�X
// 
//==========================================
//==================
// �R���X�g���N�^
//==================
CInputMouse::CInputMouse()
{
	memset(m_aButtonState, 0, sizeof(m_aButtonState));
	memset(m_aOldButtonState, 0, sizeof(m_aOldButtonState));
	m_mouseX = 0;
	m_mouseY = 0;
	m_relX = 0;
	m_relY = 0;
}
//================
// �f�X�g���N�^
//================
CInputMouse::~CInputMouse()
{
}
//=======================
// �}�E�X�̏���������
//=======================
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance);

	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse2))) // �}�E�X2�{�^���ȏ�Ή��t�H�[�}�b�g
	{
		return E_FAIL;
	}
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
	{
		return E_FAIL;
	}
	m_pDevice->Acquire();

	return S_OK;
}
//=======================
// �}�E�X�̏I������
//=======================
void CInputMouse::Uninit(void)
{
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}
	CInput::Uninit();
}
//=======================
// �}�E�X�̍X�V����
//=======================
void CInputMouse::Update(void)
{
	if (!m_pDevice)
		return;

	DIMOUSESTATE2 mouseState = {};
	memcpy(m_aOldButtonState, m_aButtonState, sizeof(m_aButtonState));

	HRESULT hr = m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE2), &mouseState);
	if (FAILED(hr))
	{
		m_pDevice->Acquire();
		hr = m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE2), &mouseState);
		OutputDebugStringA("Mouse GetDeviceState failed. Trying to Acquire...\n");
	}
	if (SUCCEEDED(hr))
	{
		for (int i = 0; i < 8; ++i) // �{�^�����͍ő�8��
		{
			m_aButtonState[i] = (mouseState.rgbButtons[i] & 0x80) ? true : false;
		}
		// ���Έړ���
		m_relX = mouseState.lX;
		m_relY = mouseState.lY;

		// �}�E�X���W�̗ݐύX�V
		m_mouseX += m_relX;
		m_mouseY += m_relY;

		//�z�C�[���̕ω��ʂ��L�^
		m_wheel = mouseState.lZ;
	}
	else
	{
		memset(m_aButtonState, 0, sizeof(m_aButtonState));
		m_relX = 0;
		m_relY = 0;
	}
}
//=======================
// �}�E�X�̃{�^����������
//=======================
bool CInputMouse::GetPress(int button)
{
	if (button < 0 || button >= 8) return false;
	return m_aButtonState[button];
}
//=======================
// �}�E�X�̃{�^���g���K�[����
//=======================
bool CInputMouse::GetTrigger(int button)
{
	if (button < 0 || button >= 8) return false;
	return (m_aButtonState[button] && !m_aOldButtonState[button]);
}
//=======================
// �}�E�X�̃{�^�������[�X����
//=======================
bool CInputMouse::GetRelease(int button)
{
	if (button < 0 || button >= 8) return false;
	return (!m_aButtonState[button] && m_aOldButtonState[button]);
}
//=======================
// �}�E�X�̑��Έړ��ʎ擾
//=======================
int CInputMouse::GetRelX(void)
{
	return m_relX;
}
int CInputMouse::GetRelY(void)
{
	return m_relY;
}
//=======================
// �}�E�X�̐�΍��W�擾�i�ݐϒl�j
//=======================
int CInputMouse::GetX(void)
{
	return m_mouseX;
}
int CInputMouse::GetY(void)
{
	return m_mouseY;
}
//
//
//
int CInputMouse::GetWheel(void)
{
	return m_wheel;
}