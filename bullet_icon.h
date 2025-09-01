//==============================
//
// 弾アイコン[bullet_icon.h]
// Author:kaiti
//
//==============================
#ifndef _BULLET_ICON_H_
#define _BULLET_ICON_H_

#include "main.h"
#include "object2D.h"
#include "bullet.h"
// マクロ定義
#define BULLETICON_SIZE (80)

// 弾アイコンクラス
class CBulletIcon:public CObject2D
{
public:

	// メンバ関数
	CBulletIcon(int nPriority = 7);
	~CBulletIcon();

	static CBulletIcon* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void ChangeIcon(CBullet::TYPE type);

	// 取得処理
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	bool GetUse(void){return m_bUse;}
	// 設定処理
	void SetUse(bool bUse) { m_bUse = bUse; }
private:
	
	// メンバ変数
	D3DXVECTOR3 m_pos;		// 位置
	bool m_bUse;			// 使用しているか
	CBullet::TYPE m_type;	// 種類
};

#endif