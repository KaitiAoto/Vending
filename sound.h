//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : 
//
//=============================================================================

// ��d�C���N���[�h�h�~
#ifndef _SOUND_H_
#define _SOUND_H_

// �C���N���[�h
#include "main.h"
#include "xaudio2.h"

// �T�E���h�N���X
class CSound
{
public:
	//*****************************************************************************
	// �T�E���h�ꗗ
	//*****************************************************************************
	typedef enum
	{
		// BGM
		SOUND_LABEL_TITLE = 0,
		SOUND_LABEL_GAME,
		SOUND_LABEL_RESULT,
		// SE
		SOUND_LABEL_BREAK,
		SOUND_LABEL_CAR,
		SOUND_LABEL_CRITICAL,
		SOUND_LABEL_DAMAGE,
		SOUND_LABEL_HIT,
		SOUND_LABEL_NODAMAGE,
		SOUND_LABEL_RESIST,
		SOUND_LABEL_RESTOCK,
		SOUND_LABEL_SHOT,
		SOUND_LABEL_CONFIRM,
		SOUND_LABEL_TITLELOGO,
		SOUND_LABEL_KILL,
		SOUND_LABEL_ITEM,
		SOUND_LABEL_MISS,
		SOUND_LABEL_START,
		SOUND_LABEL_FINISH,
		SOUND_LABEL_SELECT,

		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	//*****************************************************************************
	// �T�E���h���̍\���̒�`
	//*****************************************************************************
	typedef struct
	{
		const char* pFilename;	// �t�@�C����
		int nCntLoop;			// ���[�v�J�E���g
	} SOUNDINFO;

	CSound();
	~CSound();

	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	void Stop(void);
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

private:
	IXAudio2* m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice* m_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice* m_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X
	BYTE* m_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y

	// �T�E���h�̏��
	SOUNDINFO m_aSoundInfo[SOUND_LABEL_MAX] =
	{
		// BGM
		{"data/SOUND/BGM/title00.wav", -1},
		{"data/SOUND/BGM/game00.wav", -1},
		{"data/SOUND/BGM/result00.wav", -1},

		// SE
		{"data/SOUND/SE/break00.wav", 0},
		{"data/SOUND/SE/car00.wav", 0},
		{"data/SOUND/SE/critical00.wav", 0},
		{"data/SOUND/SE/Damage00.wav", 0},
		{"data/SOUND/SE/hit00.wav", 0},
		{"data/SOUND/SE/NoDamage00.wav", 0},
		{"data/SOUND/SE/Resist00 .wav", 0},
		{"data/SOUND/SE/restock00.wav", 0},
		{"data/SOUND/SE/shot00.wav", 0},
		{"data/SOUND/SE/switch00.wav", 0},
		{"data/SOUND/SE/title00.wav", 0},
		{"data/SOUND/SE/kill00.wav", 0},
		{"data/SOUND/SE/item00.wav", 0},
		{"data/SOUND/SE/miss00.wav", 0},
		{"data/SOUND/SE/start00.wav", 0},
		{"data/SOUND/SE/finish00.wav", 0},
		{"data/SOUND/SE/select00.wav", 0},

	};
};

#endif
