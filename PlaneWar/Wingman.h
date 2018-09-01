#pragma once
#include "GameBomb.h"

class CWingman : public CGameBomb
{
public:
	CWingman(int x = 0, int y = 0);
	~CWingman();
public:
	BOOL Draw(CDC* pDC, BOOL bPause, int nIndex = 0);

	CRect GetRect();
	static BOOL LoadImage();
private:
	static CImageList m_Images;
};

