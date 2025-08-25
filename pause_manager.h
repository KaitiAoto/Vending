//===================================
//
// タイトル選択[title_select.h]
// Author:kaiti
//
//====================================
#ifndef _PAUSE_MANAGER_H_
#define _PAUSE_MANAGER_H_

#include "main.h"
#include "object.h"
#include "pause_select.h"

#define P_SELECT_X (250)
#define P_SELECT_Y (100)

//オブジェクト2Dクラス
class CPauseMana
{
public:
	typedef enum
	{
		SELECT_CONTNUE = 0,
		SELECT_RESTART,
		SELECT_END,
		SELECT_MAX
	}SELECT;


	//メンバ関数
	CPauseMana();
	~CPauseMana();

	static CPauseMana* Create(D3DXVECTOR3 pos);
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//取得処理
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	//設定処理
private:
	void Select(void);
	
	//メンバ変数
	D3DXVECTOR3 m_pos;	//位置
	D3DXVECTOR3 m_rot;	//角度

	CPauseSelect* m_pSelect[SELECT_MAX];
	CObject2D* m_pBack;

	int m_Select;
};

#endif