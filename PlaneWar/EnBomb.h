#pragma once
#include "GameBomb.h"

class CEnBomb : public CGameBomb
{
public:
	CEnBomb(int x = 0, int y = 0, double hor = 0);
	~CEnBomb();
public:
	BOOL Draw(CDC* pDC, BOOL bPause, int nIndex = 0);

	CRect GetRect();
	static BOOL LoadImage();
private:
	static CImageList m_Images;
};

