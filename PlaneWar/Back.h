#pragma once
#include "GameObject.h"
#include "Resource.h"
class CBack : public CGameObject
{
public:
	CBack(int x = 0, int y = 0);
	~CBack();

public:
	//绘制对象
	BOOL Draw(CDC* pDC, BOOL bPause, int iIndex = 0);

	//获得矩形区域
	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + GAME_WIDTH, m_ptPos.y + GAME_HEIGHT));
	}
	static BOOL LoadImage();
private:
	static CImageList m_Images[5];
};

