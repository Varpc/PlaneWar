#pragma once
#include "GameBomb.h"
#include "resource.h"

class CEnBomb0 : public CGameBomb
{
public:
	CEnBomb0(int x = 0, int y = 0);
	~CEnBomb0();
public:
	BOOL Draw(CDC* pDC, BOOL bPause, int nIndex = 0);

	CRect GetRect();
	static BOOL LoadImage();
private:
	static CImageList m_Images;
};
