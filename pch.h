//====================================
//
// �v���R���p�C���w�b�_�[ [pch.h]
// Author:kaiti
//
//====================================

// ��d�C���N���[�h�h�~
#ifndef _PCH_H_
#define _PCH_H_

#define DIRECTINPUT_VERSION (0x0800)

// �C���N���[�h
#include <stdio.h>
#include <string.h>
#include<Windows.h>
#include<time.h>
#include "d3dx9.h"
#include <crtdbg.h>
#include <random>
#include <chrono>
#include "dinput.h"
#include "Xinput.h"

// ���C�u�����̃����N
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"xinput.lib")

// �}�N����`
#define CLASS_NAME "WindowsClass"
#define WINDOW_NAME "���̋@GUN��RUN"
#define SCREEN_WIDTH (1280)
#define SCREEN_HEIGHT (720)
#define MAX_WORD (1024)
#define _CRTDBG_MAP_ALLOC
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)//���W�E�@���E�J���[�E�e�N�X�`��

// ���_���(2D)�̍\����
typedef struct
{
	D3DXVECTOR3 pos;	 // ���_���W
	float rhw;			 // �@���x�N�g��
	D3DCOLOR col;		 // ���_�J���[
	D3DXVECTOR2 tex;	 // �e�N�X�`�����W
}VERTEX_2D;

// ���_���(3D)�̍\����
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	D3DXVECTOR3 nor;	// �@���x�N�g��
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
}VERTEX_3D;

#endif