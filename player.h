//==============================
//
// プレイヤー[player.h]
// Author:kaiti
//
//==============================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "object.h"
#include "model.h"
#include "motion.h"
#include "bullet.h"
#include "shadow.h"
#include "gauge.h"
#include "shadowS.h"

#define PLAYER_SIZE (100)
#define PLAYER_LIFE (20)
#define PLAYER_MODEL (1)
#define PLAYER_SPEED (2.5f)
#define PLAYER_JUMP (7.8f)

//プレイヤークラス
class CPlayer:public CObject
{
public:
	//種類
	typedef enum
	{
		TYPE_A = 0,
		TYPE_B,
		TYPE_MAX
	}TYPE;
	//状態
	typedef enum
	{
		STATE_NONE = 0,
		STATE_HIT,
		STATE_ACTION,
		STATE_DEAD,
		STATE_MAX
	}STATE;

	//メンバ関数
	CPlayer(int nPriority = PRIORITY_PLAYER);
	~CPlayer();
	static CPlayer* Create(const char* pFileName, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	HRESULT Init(const char* pFileName, D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	void Uninit(void);
	void Update(void);
	void Draw(void);

	//設定
	void SetType(TYPE type) { m_type = type; };
	void SetBulletType(CBullet::TYPE type) { m_Bullet = type; }
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetPosOffSet(D3DXVECTOR3 pos) { m_posOffSet = pos; }
	void SetUse(void) {m_bUse = true; m_nLife = PLAYER_LIFE;}
	//void SetLanding(bool bLanding) { m_bLanding = bLanding; }
	void SetPosY(float Y) { m_pos.y = Y; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	void MovePos(D3DXVECTOR3 move) { m_pos += move; }
	void SetTargetPos(D3DXVECTOR3 pos) { m_TargetPos = pos; }

	//取得
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
	D3DXVECTOR3 GetPosOld(void) { return m_posOld; }
	D3DXVECTOR3 GetPosOffSet(void) { return m_posOffSet; }
	int GetContents(void) { return m_nCntContents; }
	int GetNumModel(void) { return m_nNumModel; }
	static bool GetUse(void) { return m_bUse; }
	CBullet::TYPE GetMyBullet(void) { return m_Bullet; }
	D3DXMATRIX GetMtx(void) { return m_mtxWorld; }
	int GetLife(void) { return m_nLife; }

	void AddContents(int nAdd) { m_nCntContents += nAdd; if (m_nCntContents >= 99) { m_nCntContents = 99; } }
	void ClearContents(void) { m_nCntContents = 0; }
	void Heal(int nHeal) { m_nLife += nHeal; if (m_nLife >= PLAYER_LIFE) { m_nLife = PLAYER_LIFE; } }

	void AddSpeed(float fAddSpeed) { m_fSpeed += fAddSpeed; }

	void Hit(const int nDamage);
	void HitBack(void);
private:
	void Move(void);
	void Action(void);
	bool Collision(void);
	void State(STATE state);
	void CheckStack(bool bColl, bool bMove);
	void RecoverFromStuck(void);

	//メンバ変数
	D3DXVECTOR3 m_pos;					//位置
	D3DXVECTOR3 m_posOld;				//前回の位置
	D3DXVECTOR3 m_posOffSet;			//位置(オフセット)
	D3DXVECTOR3 m_rot;					//向き
	D3DXVECTOR3 m_rotDest;				//目標の向き
	D3DXVECTOR3 m_move;					//移動量
	D3DXVECTOR3 m_size;					//サイズ
	D3DXMATRIX m_mtxWorld;				//ワールドマトリックス
	D3DXVECTOR3 m_TargetPos;

	float m_fLength;					//対角線の長さ
	float m_fAngle;						//対角線の角度
	int m_nCntState;					//状態カウンター
	int m_nPriority;					//描画順
	STATE m_State;						//状態
	TYPE m_type;						//種類
	static bool m_bUse;					//使用しているか
	//bool m_bJump;						//ジャンプしているか
	//bool m_bLanding;					//着地判定

	//ステータス
	int m_nLife;						//ライフ
	float m_fSpeed;						//移動速度

	//モデル
	CModel* m_apModel[PLAYER_MODEL];	//モデルへのポインタ
	int m_nNumModel;					//モデル最大数
	CMotion* m_pMotion;					//モーションへのポインタ

	//弾
	CBullet::TYPE m_Bullet;				//弾の種類
	int m_nCntContents;					//中身の残量
	float m_fShotTimer;
	const float SHOT_INTERVAL = 1.0f;
	const float SHOT_TIMESUB = 0.05f;

	CShadow* m_pShadow;					//影へのポインタ
	CShadowS* m_pShadowS;					//影へのポインタ

	int m_nCnStackt;					//スタックカウント
};

#endif