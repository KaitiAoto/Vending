//=====================
//
// C++[main.cpp]
// Author : Kaiti Aoto
//
//=====================
#include "main.h"
#include "manager.h"
//�v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//=============
// ���C���֐�
//=============
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR ipCmdLine, _In_ int nCmdShow)
{
	//_CrtSetBreakAlloc(229);
	//_CrtSetBreakAlloc(1871);

	// ���������[�N���o�p�t���O�̐ݒ�
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);

	CManager* pManager = NULL;

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL,IDI_APPLICATION),
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL,IDI_APPLICATION)
	};

	HWND hWnd;
	MSG msg;

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	//�E�C���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�C���h�E�𐶐�
	hWnd = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(rect.right - rect.left),
		(rect.bottom - rect.top),
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowCursor(FALSE);
	bool bCursor = false;

	//�}�l�[�W���[�̐���
	pManager = new CManager;
	//�}�l�[�W���[�̏�����
	pManager->Init(hInstance, hWnd, TRUE);

	DWORD dwCurrentTime;
	DWORD dwExecLastTime;
	//����\��ݒ�
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();

#ifndef _DEBUG
	ShowWindow(hWnd, SW_SHOWMAXIMIZED);
#endif

#ifdef _DEBUG
	//�E�C���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);
#endif

	UpdateWindow(hWnd);

	DWORD dwFrameCount; //�t���[���J�E���g
	DWORD dwFPSLastTime;//

	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	int nCntFPS = 0;

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//DirectX�̏���
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5�b�o��
				nCntFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				//�}�l�[�W���[�X�V����
				pManager->Update();

				if (pManager->GetInputKey()->GetTrigger(DIK_F4))
				{
					bCursor = !bCursor;
					ShowCursor(bCursor);
				}

				if (bCursor == false)
				{
					// �Q�[����ʂ̒����ɃJ�[�\�����Z�b�g�����
					int centerX = SCREEN_WIDTH / 2;
					int centerY = SCREEN_HEIGHT / 2;

					// �N���C�A���g�̈�̒������X�N���[�����W�ɕϊ�
					POINT pt = { centerX, centerY };
					ClientToScreen(hWnd, &pt);

					// �J�[�\���ʒu���Z�b�g
					SetCursorPos(pt.x, pt.y);
				}
#ifdef _DEBUG
				if (pManager->GetInputKey()->GetTrigger(DIK_F10))
				{
					ShowWindow(hWnd, SW_SHOWMAXIMIZED);
				}
#endif

				//�}�l�[�W���[�`�揈��
				pManager->Draw();
				pManager->GetDebug()->Print("FPS�F%d", nCntFPS);

				dwFrameCount++;

				Sleep(1);  // CPU���׌y��
			}
		}
	}

	//�}�l�[�W���[�̔j��
	if (pManager != NULL)
	{
		//�}�l�[�W���[�̏I������
		pManager->Uninit();

		delete pManager;
		pManager = NULL;
	}

	ShowCursor(TRUE);

	timeEndPeriod(1);

	//�E�C���h�E�N���X�̉���
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return(int)msg.wParam;
}
//=======================
//�E�C���h�E�v���V�[�W��
//=======================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		//WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN: //�L�[�����̃��b�Z�[�W
		switch (wParam)
		{
		case VK_ESCAPE://[ESC]�L�[�������ꂽ�ꍇ
			DestroyWindow(hWnd);
			break;

		default:
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}