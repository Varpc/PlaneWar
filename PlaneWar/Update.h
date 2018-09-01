#pragma once
#include "GameProp.h"
#include "resource.h"

class CUpdate :
	public CGameProp
{
public:
	CUpdate();
	~CUpdate();
public:
	BOOL Draw(CDC* pDC, BOOL bPause, int nIndex);

	//获得矩形区域
	CRect GetRect();
	static BOOL LoadImage();
private:
	static CImageList m_Images;

};

