#pragma once
#include "GameBomb.h"

class CBomb1 : public CGameBomb
{
public:
	CBomb1(int x, int y, int left, int right, int hor);
	~CBomb1();
public:
	BOOL Draw(CDC* pDC, BOOL bPause, int nIndex = 0);

	CRect GetRect();
	static BOOL LoadImage();
private:
	static CImageList m_Images;
	int m_nLeft, m_nRight; //×Óµ¯±ß½ç

};
