#pragma once
#include "GameProp.h"

class CChangeBomb :
	public CGameProp
{
public:
	CChangeBomb();
	~CChangeBomb();
public:
	BOOL Draw(CDC* pDC, BOOL bPause, int nIndex);

	//获得矩形区域
	CRect GetRect();
	static BOOL LoadImage();
private:
	static CImageList m_Images;
};

