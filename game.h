//================================
//
// �Q�[������[game.cpp]
// Author:kaiti
//
//================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
#include "scene.h"
#include "object.h"
#include "object2D.h"
#include "player.h"
#include "input.h"
#include "effect.h"
#include "score_manager.h"
#include "timer_manager.h"
#include "texture.h"
#include "camera.h"
#include "light.h"
#include "object3D.h"
#include "objectX.h"
#include "objectBillboard.h"
#include "sound.h"
#include "meshfield.h"
#include "enemy_base.h"
#include "vender.h"
#include "bullet_counter_manager.h"
#include "restock.h"
#include "collision.h"
#include "debugproc.h"
#include "matchup.h"
#include "meshcylinder.h"
#include "meshsphere.h"
#include "gauge_hp.h"
#include "loadstage.h"
#include "wall_invisible.h"
#include "gimmick.h"
#include "start.h"
#include "gauge_reset.h"
#include "pause.h"
#include "gauge_enemy.h"
#include "item.h"
#include "particle.h"
#include "tutorial.h"
#include "meshcircle.h"
#include "effect_circle.h"
#include "minimap.h"
#include "startUI.h"
#include "buff.h"
#include "screen_flash.h"
#include "enemy_group.h"

// �}�N����`
#define GAME_TIME (180)

// �O���錾
class CScene;

// �Q�[���N���X
class CGame:public CScene
{
public:
	// ���[�h
	typedef enum
	{
		MODE_NONE=0,
		MODE_PLAY,
		MODE_FIN,
		MODE_PAUSE,
		MODE_BACK,
		MODE_TUTORIAL,
		MODE_MAX
	}MODE;

	// �����o�֐�
	CGame();
	~CGame();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static void SetPlayer(CPlayer* player) { m_pPlayer = player; }
	// �ÓI�����o�֐�
	static CPlayer* GetPlayer(void) { return m_pPlayer; }
	static CTimerMana* GetTime(void) { return m_pTimer; }
	static CObject3D* GetObj3D(void) { return m_pObj3D; }
	static CScoreMana* GetBreakCnt(void) { return m_pBreakCnt; }
	static CScoreMana* GetTotalScore(void) { return m_pTotalScore; }
	static CCollision* GetColl(void) { return m_pColl; }
	static CMatchUp* GetMatchup(void) { return m_pMatchup; }
	static CHpGauge* GetHpGauge(void) { return m_pHpGauge; }
	static CStart* GetStart(void) { return m_pStart; }
	static CResetGauge* GetReset(void) { return m_pReset; }
	static CMap* GetMap(void) { return m_pMap; }
	static CBuff* GetBuff(void) { return m_pBuff; }
	static CScreenFlash* GetFlash(void) { return m_pScreenFlash; }
	static CTutorial* GetTutorial(void) { return m_pTutprial; }

	static CPause* GetPause(void) { return m_pPause; }

	static void SetMode(MODE mode) { m_mode = mode; }
	static MODE GetMode(void) { return m_mode; }
private:

	// �ÓI�����o�ϐ�
	static CPlayer* m_pPlayer;					// �v���C���[�ւ̃|�C���^
	static CTimerMana* m_pTimer;				// �^�C�}�[�ւ̃|�C���^
	static CObject3D* m_pObj3D;					// 3D�I�u�W�F�N�g�ւ̃|�C���^
	static CScoreMana* m_pBreakCnt;				// �j��X�R�A�ւ̃|�C���^
	static CScoreMana* m_pTotalScore;			// �g�[�^���X�R�A�ւ̃|�C���^
	static CBulletCntMana* m_pBulletCount;		// �e���J�E���^�[�ւ̃|�C���^
	static CCollision* m_pColl;					// �����蔻��ւ̃|�C���^
	static CMatchUp* m_pMatchup;				// �^�C�v�����ւ̃|�C���^
	static CHpGauge* m_pHpGauge;				// HP�Q�[�W�ւ̃|�C���^
	static CLoadStage* m_pStage;				// �X�e�[�W�ǂݍ��݂ւ̃|�C���^
	static CStart* m_pStart;					// �X�^�[�g�ւ̃|�C���^
	static CResetGauge* m_pReset;				// ���Z�b�g�Q�[�W�ւ̃|�C���^
	static CMap* m_pMap;						// �}�b�v�ւ̃|�C���^
	static CBuff* m_pBuff;						// �o�t�ւ̃|�C���^
	static CScreenFlash* m_pScreenFlash;		// ��ʓ_�łւ̃|�C���^
	static CTutorial* m_pTutprial;				// �`���[�g���A���ւ̃|�C���^
	static CPause* m_pPause;					// �|�[�Y�ւ̃|�C���^

	static MODE m_mode;							// �Q�[�����[�h

};

#endif