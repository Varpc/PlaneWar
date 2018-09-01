#pragma once
#include "GameObject.h"

class CTimer : public CGameObject
{
public:
	CTimer(int x = 0, int y = 0, int time = 0);
	~CTimer();
public:
	BOOL Draw(CDC* pDC, BOOL bPause, int nIndex);
	CRect GetRect();
	static BOOL LoadImage();
private:
	static CImageList m_Images;
	int m_nTime;
	int m_nWait;
	int m_nTemp[4];
};

