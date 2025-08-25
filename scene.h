//================================
//
// ÉVÅ[Éìèàóù[scene.h]
// Author:kaiti
//
//================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"
#include "object.h"


class CScene:public CObject
{
public:
	typedef enum
	{
		MODE_TITLE=0,
		MODE_GAME,
		MODE_RESULT,
		MODE_RANKING,

		MODE_END,
		MODE_MAX
	}MODE;

	CScene(MODE mode);
	virtual ~CScene() = 0;
	virtual void Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	static CScene* Create(MODE mode);


	MODE GetMode(void) { return  m_mode; }
private:
	MODE m_mode;
};


#endif