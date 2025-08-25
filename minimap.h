//==============================
//
// íe[bullet.h]
// Author:kaiti
//
//==============================
#ifndef _MINIMAP_H_
#define _MINIMAP_H_

#include "object.h"
#include "map_player.h"

class CMap:public CObject
{
public:
	CMap();
	~CMap();

	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CMap* Create(const D3DXVECTOR3 pos, float fWidth, float fHeight);

	static CMapPlayer* GetMapPlayer(void) { return m_pMapPlayer; }


	D3DXVECTOR3 GetPos(void) { return m_pos; }

	float GetWidth(void) { return m_fWidth; }
	float GetHeight(void) { return m_fHeight; }
private:
	//ÉÅÉìÉoïœêî
	D3DXVECTOR3 m_pos;	//à íu

	float m_fWidth;
	float m_fHeight;

	static CMapPlayer* m_pMapPlayer;
};

#endif