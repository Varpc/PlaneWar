#pragma once
#include "GameBomb.h"
#include "resource.h"

class CEnBomb1 : public CGameBomb
{
public:
	CEnBomb1(int x = 0, int y = 0);
	~CEnBomb1();
public:
	BOOL Draw(CDC* pDC, BOOL bPause, int nIndex = 0);

	CRect GetRect();
	static BOOL LoadImage();
private:
	static CImageList m_Images;
};

