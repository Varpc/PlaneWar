#pragma once
#include "GameBomb.h"

class CBomb0 : public CGameBomb
{
public:
	CBomb0(int x = 0, int y = 0, double hor = 0);
	~CBomb0();
public:
	BOOL Draw(CDC* pDC, BOOL bPause, int nIndex = 0);

	CRect GetRect();
	static BOOL LoadImage();
private:
	static CImageList m_Images;
};

