//==============================
//
// プレイヤー[player.h]
// Author:kaiti
//
//==============================

// 二重インクルード防止
#ifndef _PLAYER_H_
#define _PLAYER_H_

// インクルード
#include "main.h"
#include "object.h"
#include "model.h"
#include "motion.h"
#include "bullet.h"
#include "shadow.h"
#include "gauge.h"
#include "shadowS.h"

// マクロ定義
#define PLAYER_SIZE (100)
#define PLAYER_LIFE (20)
#define PLAYER_MODEL (1)
#define PLAYER_SPEED (2.5f)
#define PLAYER_JUMP (7.8f)

// プレイヤークラス
class CPlayer:public CObject
{
public:
	// 種類
	typedef enum
	{
		TYPE_A = 0,
		TYPE_B,
		TYPE_MAX
	}TYPE;
	// 状態
	typedef enum
	{
		STATE_NONE = 0,
		STATE_HIT,
		STATE_ACTION,
		STATE_DEAD,
		STATE_MAX
	}STATE;

	// メンバ関数
	CPlayer(int nPriority = PRIORITY_PLAYER);
	~CPlayer();

	HRESULT Init(const char* pFileName, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void AddContents(int nAdd) { m_nCntContents += nAdd; if (m_nCntContents >= 99) { m_nCntContents = 99; } }
	void ClearContents(void);
	void Heal(int nHeal) { m_nLife += nHeal; if (m_nLife >= PLAYER_LIFE) { m_nLife = PLAYER_LIFE; } }
	void AddSpeed(float fAddSpeed) { m_fSpeed += fAddSpeed; }
	void Hit(const int nDamage);

	// 設定
	void SetType(TYPE type) { m_type = type; };
	void SetBulletType(CBullet::TYPE type) { m_Bullet = type; }
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetPosOffSet(D3DXVECTOR3 pos) { m_posOffSet = pos; }
	void SetPosY(float Y) { m_pos.y = Y; }
	void SetTargetPos(D3DXVECTOR3 pos) { m_TargetPos = pos; }
	void SetUse(void) {m_bUse = true; m_nLife = PLAYER_LIFE;}
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	void MovePos(D3DXVECTOR3 move) { m_pos += move; }

	// 取得
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
	D3DXVECTOR3 GetPosOld(void) { return m_posOld; }
	D3DXVECTOR3 GetPosOffSet(void) { return m_posOffSet; }
	D3DXMATRIX GetMtx(void) { return m_mtxWorld; }
	CBullet::TYPE GetMyBullet(void) { return m_Bullet; }
	STATE GetState(void) { return m_State; }
	bool GetbMove(void) { return m_bMove; }
	int GetContents(void) { return m_nCntContents; }
	int GetNumModel(void) { return m_nNumModel; }
	int GetLife(void) { return m_nLife; }

	// 静的メンバ関数
	static CPlayer* Create(const char* pFileName, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	static bool GetUse(void) { return m_bUse; }

private:
	void Move(void);
	void Action(void);
	bool Collision(void);
	void State(STATE state);
	void CheckStack(bool bColl, bool bMove);
	void RecoverFromStuck(void);
	void Blink(void);

	// メンバ変数
	D3DXVECTOR3 m_pos;					// 位置
	D3DXVECTOR3 m_posOld;				// 前回の位置
	D3DXVECTOR3 m_posOffSet;			// 位置(オフセット)
	D3DXVECTOR3 m_rot;					// 向き
	D3DXVECTOR3 m_rotDest;				// 目標の向き
	D3DXVECTOR3 m_move;					// 移動量
	D3DXVECTOR3 m_size;					// サイズ
	D3DXVECTOR3 m_TargetPos;			// 目標の位置
	D3DXMATRIX m_mtxWorld;				// ワールドマトリックス
	D3DXCOLOR m_BaseColor;				// 通常の色
	D3DXCOLOR m_DamageColor;			// ダメージ時の色

	STATE m_State;						// 状態
	TYPE m_type;						// 種類
	CShadow* m_pShadow;					// 影へのポインタ
	CShadowS* m_pShadowS;				// ステンシル影へのポインタ
	int m_nCntState;					// 状態カウンター
	int m_nCntStackt;					// スタックカウント
	bool m_bMove;						// 移動しているか
	// ステータス
	int m_nLife;						// ライフ
	float m_fSpeed;						// 移動速度
	// モデル
	CModel* m_apModel[PLAYER_MODEL];	// モデルへのポインタ
	CMotion* m_pMotion;					// モーションへのポインタ
	int m_nNumModel;					// モデル最大数
	// 弾
	CBullet::TYPE m_Bullet;				// 弾の種類
	int m_nCntContents;					// 中身の残量
	float m_fShotTimer;					// 発射間隔カウント
	const float SHOT_INTERVAL = 1.0f;	// 発射間隔
	const float SHOT_TIMESUB = 0.05f;	// 発射時間を減らす値

	// 静的メンバ変数
	static bool m_bUse;					// 使用しているか
};

#endif