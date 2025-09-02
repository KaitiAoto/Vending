//================================================================
//
// 弾数カウンターマネージャー[bullet_counter_manager.h]
// Author:kaiti
//
//================================================================

// 二重インクルード防止
#ifndef _BULLET_COUNTER_MANAGER_H_
#define _BULLET_COUNTER_MANAGER_H_

// インクルード
#include "main.h"
#include "bullet_counter.h"
#include "bullet_icon.h"

// マクロ定義
#define MAX_BULLETCNT (2)
#define BULLETCNTDATA (10)

// 弾数カウンターマネージャークラス
class CBulletCntMana
{
public:

	//メンバ関数
	CBulletCntMana();
	~CBulletCntMana();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CBulletCntMana* Create(D3DXVECTOR3 pos);
	static void SetBulletCount(void);

private:
	//静的メンバ変数
	static int m_nCount;								// カウント
	static CBullerCounter* m_pTimer[MAX_BULLETCNT];		// カウンターへのポインタ
	static CBulletIcon* m_pIcon;						// 弾アイコンへのポインタ
};

#endif