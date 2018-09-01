#pragma once
#include "GameObject.h"
#include "resource.h"

class CQBomb : public CGameObject
{
public:
	CQBomb(int x, int y);
	~CQBomb(void);

	BOOL Draw(CDC* pDC, BOOL bPause, int iIndex);

	static BOOL LoadImage();

	CRect GetRect()
	{
		//高度在判断碰撞是没有影响
		return CRect(m_ptPos, CPoint(m_ptPos.x + 10, m_ptPos.y + BOMB_HEIGHT));
	}

private:
	static const int BOMB_HEIGHT = 20;
	static CImageList m_Images;
	int m_iY;
};

