#pragma once
#include "GameObject.h"
#include "resource.h"

class CBullet : public CGameObject
{
public:
	CBullet(int x, int y, double v, double h, int time);
	~CBullet();

	BOOL Draw(CDC* pDC, BOOL bPause, int iIndex);

	static BOOL LoadImage();

	CRect GetRect()
	{
		//高度在判断碰撞是没有影响
		return CRect(m_ptPos, CPoint(m_ptPos.x + BULLET_LENGTH, m_ptPos.y + BULLET_LENGTH));
	}
private:
	static const int BULLET_LENGTH = 20;
	static CImageList m_Images[4];
	double m_iVor, m_iHor;
	int m_iV;
	int m_iTime, m_iWait, m_iIndex;
};

