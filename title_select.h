//===================================
//
// タイトル選択[title_select.h]
// Author:kaiti
//
//====================================
#ifndef _TITLE_SELECT_H_
#define _TITLE_SELECT_H_

#include "main.h"
#include "object.h"
#include "object2D.h"

#define T_SELECT_X (250)
#define T_SELECT_Y (100)

//オブジェクト2Dクラス
class CTitleSelect:public CObject
{
public:
	typedef enum
	{
		SELECT_GAME = 0,
		SELECT_END,
		SELECT_MAX
	}SELECT;


	//メンバ関数
	CTitleSelect(int nPriority = 7);
	~CTitleSelect();

	static CTitleSelect* Create(D3DXVECTOR3 pos);
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

	CObject2D* m_pSelect[SELECT_MAX];
	CObject2D* m_pCursor;

	int m_Select;
};

#endif